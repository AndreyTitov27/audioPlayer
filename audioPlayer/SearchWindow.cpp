#include "SearchWindow.h"

SearchWindow::SearchWindow(MainWindow* mainWindowInstanceSearch, QMainWindow* parentInstance,
	QMainWindow* parent) : mainWindowInstanceSearch(mainWindowInstanceSearch), parentInstance(parentInstance) {
	resize(600, 400);
	setWindowTitle("Searcher");
	tilesList = new QList<SearchMusicTile*>();
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);
	searchLayout = new QHBoxLayout();
	input = new QLineEdit();
	inputButton = new QPushButton("search");
	connect(inputButton, &QPushButton::clicked, this, &SearchWindow::search);
	scrollArea = new QScrollArea(this);
	scrollAreaWidget = new QWidget();
	scrollAreaLayout = new QVBoxLayout(scrollAreaWidget);

	scrollArea->setWidget(scrollAreaWidget);
	scrollAreaWidget->setLayout(scrollAreaLayout);

	scrollArea->setWidgetResizable(true);
	scrollArea->setStyleSheet(scrollAreaStyle);

	mainLayout->addLayout(searchLayout);
	searchLayout->setAlignment(Qt::AlignTop);
	searchLayout->addWidget(input);
	searchLayout->addWidget(inputButton);
	mainLayout->addWidget(scrollArea);
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setCentralWidget(centralWidget);
	show();
}
void SearchWindow::search() {
	if (!tilesList->isEmpty()) {
		for (SearchMusicTile* tile : *tilesList) {
			tilesList->removeOne(tile);
			delete tile;
		}
	}
	std::string filePath = "resources/audioDownloading/searchQuery.txt";
	if (std::filesystem::exists(filePath)) {
		std::ofstream file(filePath);
		if (file.is_open()) {
			std::string query = input->text().toUtf8().constData();
			file << query << std::endl;
			file.close();
		}
	}
	progressDialog = new QProgressDialog(this);
	progressDialog->setWindowTitle("Searching");
	progressDialog->setLabelText("Searching...");
	progressDialog->setCancelButton(nullptr);
	progressDialog->setRange(0, 0);
	progressDialog->setMinimumDuration(0);
	progressDialog->setWindowModality(Qt::WindowModal);
	progressDialog->findChild<QProgressBar*>()->setAlignment(Qt::AlignCenter);
	progressDialog->setFixedSize(300, 100);
	progressDialog->show();
	QFuture<void> future = QtConcurrent::run([this, filePath]() {
		std::system("resources\\audioDownloading\\audioSearcher.exe");
	});
	QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
	connect(watcher, &QFutureWatcher<void>::finished, [this]() {
		progressDialog->close();
		delete progressDialog;
		std::string filePath = "resources/audioDownloading/searchResults.txt";
		if (std::filesystem::exists(filePath)) {
			std::fstream file(filePath);
			if (file.is_open()) {
				std::string line;
				QString author;
				QString title;
				QString link;
				while (std::getline(file, line)) {
					qDebug() << line;
					if (line.find("Artists: ", 0) == 0) {
						author = QString::fromUtf8(line.substr(9, line.find("Title: ") - 10));
						qDebug() << "author " << author;
						line = line.substr(line.find("Title: "));
					}
					if (line.rfind("Title: ", 0) == 0) {
						title = QString::fromUtf8(line.substr(7, line.find("Link: ") - 8));
						qDebug() << "title " << title;
						line = line.substr(line.find("Link: "));
					}
					if (line.rfind("Link: ", 0) == 0) {
						link = QString::fromUtf8(line.substr(6, line.find("\n") - 7));
						qDebug() << "link " << link;
					}
					SearchMusicTile* musicTile = new SearchMusicTile(title, author,
						QString("resources/audioDownloading/searchResultsCovers/" +
							author + " - " + title + ".jpg"), link, this, this);
					tilesList->append(musicTile);
					scrollAreaLayout->addWidget(musicTile);
				}
			}
		}
	});
	watcher->setFuture(future);
}
void SearchWindow::closeEvent(QCloseEvent* event) {
	event->accept();
	std::ofstream fileOut("resources/audioDownloading/input.txt");
	if (fileOut.is_open()) {
		fileOut.clear();
		fileOut.close();
	}
	std::ofstream searchResultsFile("resources/audioDownloading/searchResults.txt");
	if (searchResultsFile.is_open()) {
		searchResultsFile.clear();
		searchResultsFile.close();
	}
	std::ofstream searchQueryFile("resources/audioDownloading/searchQuery.txt");
	if (searchQueryFile.is_open()) {
		searchQueryFile.clear();
		searchQueryFile.close();
	}
	for (const auto& entry :
		std::filesystem::directory_iterator("resources/audioDownloading/searchResultsCovers")) {
		std::filesystem::remove_all(entry);
	}
	this->deleteLater();
}
void SearchWindow::downloadTrackFromSearch(SearchMusicTile* tile) {
	std::string filePath = "resources/audioDownloading/input.txt";
	if (std::filesystem::exists(filePath)) {
		std::fstream file(filePath);
		if (file.is_open()) {
			std::string link = tilesList->at(tile->getIndex())->getLink().toUtf8().constData();
			if (link.starts_with("https://www.youtube.com") ||
				link.starts_with("https://youtu.be") || link.starts_with("https://music.youtube.com")) {
				file << link << std::endl;
				file.close();
			}
			else {
				file.close();
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
	parentInstance->setVisible(false);

	QFuture<void> future = QtConcurrent::run([this, filePath]() {
		std::ifstream fileIn(filePath);
		if (fileIn.is_open()) {
			std::string line;
			std::getline(fileIn, line);
			if (line.starts_with("https://www.youtube.com") ||
				line.starts_with("https://youtu.be") || line.starts_with("https://music.youtube.com")) {
				fileIn.close();
				mainWindowInstanceSearch->isTrackDownloading = true;
				std::system("resources\\audioDownloading\\audioDownloader.exe");
			}
		}
		});

	QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
	connect(watcher, &QFutureWatcher<void>::finished, [this, watcher, filePath, directory]() {
		mainWindowInstanceSearch->isTrackDownloading = false;
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
		std::ofstream searchResultsFile("resources/audioDownloading/searchResults.txt");
		if (searchResultsFile.is_open()) {
			searchResultsFile.clear();
			searchResultsFile.close();
		}
		std::ofstream searchQueryFile("resources/audioDownloading/searchQuery.txt");
		if (searchQueryFile.is_open()) {
			searchQueryFile.clear();
			searchQueryFile.close();
		}
		for (const auto& entry :
			std::filesystem::directory_iterator("resources/audioDownloading/searchResultsCovers")) {
			std::filesystem::remove_all(entry);
		}
		for (SearchMusicTile* i : *tilesList) {
			i->decreaseNumberStatic();
			tilesList->removeOne(i);
			delete i;
		}
		watcher->deleteLater();
	});
	watcher->setFuture(future);
}