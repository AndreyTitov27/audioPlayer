#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"

void MainWindow::selectMultipleFiles() {
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