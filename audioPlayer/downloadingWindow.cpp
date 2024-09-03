#include "downloadingWindow.hpp"

DownloadingWindow::DownloadingWindow(MainWindow* mainWindowInstance, QMainWindow* parent)
	: QMainWindow(parent), mainWindowInstance(mainWindowInstance) {
	setWindowTitle("Track Downloader");
	setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);
	inputLayout = new QHBoxLayout();
	inputButtonLayout = new QHBoxLayout();
	input = new QLineEdit();
	inputButton = new QPushButton("download");

	inputButton->setFixedWidth(100);
	inputButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	connect(inputButton, &QPushButton::clicked, this, &DownloadingWindow::downloadTrack);
	inputLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	inputButtonLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

	mainLayout->addLayout(inputLayout);
	inputLayout->addWidget(input);
	mainLayout->addLayout(inputButtonLayout);
	inputButtonLayout->addWidget(inputButton);

	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	setFixedSize(400, 200);
}

void DownloadingWindow::downloadTrack() {
	std::string filePath = "resources/audioDownloading/input.txt";
	if (std::filesystem::exists(filePath)) {
		std::fstream file(filePath);
		if (file.is_open()) {
			std::string link = input->text().toUtf8().constData();
			if (link.starts_with("https://www.youtube.com") ||
				link.starts_with("https://youtu.be") || link.starts_with("https://music.youtube.com")) {
				file << link << std::endl;
				file.close();
			}
			else {
				file.close();
				input->setText("");
				QMessageBox msgBox(this);
				msgBox.setWindowTitle("Information");
				msgBox.setText("Paste youtube or youtube music link");
				msgBox.setIcon(QMessageBox::Information);
				msgBox.exec();
				return;
			}
		}
	}

	QString defaultPath = QDir::homePath();
	QString Qdirectory = QFileDialog::getExistingDirectory(this, "Select Directory", defaultPath);
	if (Qdirectory.isEmpty()) {
		return;
	}
	std::string directory = Qdirectory.toUtf8().constData();

	input->setText("");
	this->setVisible(false);

	QFuture<void> future = QtConcurrent::run([this, filePath]() {
		std::ifstream fileIn(filePath);
		if (fileIn.is_open()) {
			std::string line;
			std::getline(fileIn, line);
			if (line.starts_with("https://www.youtube.com") ||
				line.starts_with("https://youtu.be") || line.starts_with("https://music.youtube.com")) {
				fileIn.close();
				mainWindowInstance->isTrackDownloading = true;
				std::system("resources\\audioDownloading\\audioDownloader.exe");
			}

		}
		});

	QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
	connect(watcher, &QFutureWatcher<void>::finished, [this, watcher, filePath, directory]() {
		mainWindowInstance->isTrackDownloading = false;
		for (const auto& entry : std::filesystem::directory_iterator("resources/audioDownloading/tracks")) {
			std::filesystem::path filePath = entry.path();
			std::filesystem::path destinationPath = directory / filePath.filename();
			std::filesystem::rename(filePath, destinationPath);
		}
		QMessageBox msgBox(this);
		msgBox.setWindowTitle("Information");
		msgBox.setText("Track has been downloaded");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
		std::ofstream fileOut(filePath);
		if (fileOut.is_open()) {
			fileOut.clear();
			fileOut.close();
		}
		watcher->deleteLater();
		});
	watcher->setFuture(future);

}