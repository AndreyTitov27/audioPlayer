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

		//selectSingleTrackButton->raise();
		//selectMultipleTracksButton->raise();
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
		trackNumber++;
		QFileInfo fileInfo(filePath);
		MusicButton* newMusicButton = new MusicButton(fileInfo.completeBaseName(), trackNumber + 1, filePath, player, currentTrackNumber, this);
		playlist->append(newMusicButton);
		tracksScrollAreaLayout->addWidget(newMusicButton);
		//tracksLayout->addWidget(newMusicButton);
		qDebug() << "Selected file: " << playlist->at(trackNumber)->getTrackPath();
	}
}
void MainWindow::selectMultipleFiles() {
	isShownFileOptions = false;
	delete selectSingleTrackButton;
	delete selectMultipleTracksButton;

	QList<QString>* filePaths = new QList<QString>(QFileDialog::getOpenFileNames(this, "Select Multiple Files", QString(),
		"Audio Files (*.mp3 *.wav);;All Files (*)"));
	if (!filePaths->isEmpty()) {
		for (int i = 0; i < filePaths->size(); i++) {
			trackNumber++;
			QFileInfo fileInfo(filePaths->at(i));
			MusicButton* newMusicButton = new MusicButton(fileInfo.completeBaseName(), trackNumber + 1, filePaths->at(i), player, currentTrackNumber, this);
			playlist->append(newMusicButton);
			tracksScrollAreaLayout->addWidget(newMusicButton);
			qDebug() << "Selected files: " << filePaths->at(i);
		}
	}
}