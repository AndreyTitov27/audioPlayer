#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"

void MainWindow::showFileOptions() {
	if (!isShownFileOptions) {
		isShownFileOptions = true;
		selectSingleTrackButton = new QPushButton("Select single track", this);
		selectSingleTrackButton->setMinimumSize(120, 30);
		selectSingleTrackButton->setMaximumSize(400, 35);
		selectSingleTrackButton->setStyleSheet(manageButtonsStyle);
		connect(selectSingleTrackButton, &QPushButton::clicked, this, &MainWindow::selectSingleFile);

		selectMultipleTracksButton = new QPushButton("Select multiple tracks", this);
		selectMultipleTracksButton->setMinimumSize(120, 30);
		selectMultipleTracksButton->setMaximumSize(400, 35);
		selectMultipleTracksButton->setStyleSheet(manageButtonsStyle);
		connect(selectMultipleTracksButton, &QPushButton::clicked, this, &MainWindow::selectMultipleFiles);

		addTrackOptionsLayout->addWidget(selectSingleTrackButton);
		addTrackOptionsLayout->addWidget(selectMultipleTracksButton);
	}
	else {
		isShownFileOptions = false;
		delete selectSingleTrackButton;
		delete selectMultipleTracksButton;
	}
}
void MainWindow::selectSingleFile() {
	isShownFileOptions = false;
	delete selectSingleTrackButton;
	delete selectMultipleTracksButton;

	QString filePath = QFileDialog::getOpenFileName(this, "Select Single File", QString(),
		"Audio Files (*.mp3 *.wav);;All Files (*)");
	if (!filePath.isEmpty()) {
		QFileInfo fileInfo(filePath);
		MusicButton* newMusicButton = new MusicButton(fileInfo.completeBaseName(), this);
		tracksLayout->addWidget(newMusicButton);
		qDebug() << "Selected file: " << fileInfo.completeBaseName();
	}
}
void MainWindow::selectMultipleFiles() {
	QStringList filePaths = QFileDialog::getOpenFileNames(this, "Select Multiple Files", QString(),
		"Audio Files (*.mp3 *.wav);;All Files (*)");
	if (!filePaths.isEmpty()) {
		qDebug() << "Selected files: " << filePaths;
	}
}