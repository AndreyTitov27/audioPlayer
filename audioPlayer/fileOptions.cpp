#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "playlistButton.hpp"
#include "styles.hpp"

void MainWindow::addTracks() {
	QString defaultPath = QDir::homePath();
	QList<QString>* filePaths = new QList<QString>(QFileDialog::getOpenFileNames(this, "Select Multiple Files", defaultPath,
		"Audio Files (*.mp3 *.wav);;All Files (*)"));
	if (!filePaths->isEmpty()) {
		QList<QString>* filesToRemove = new QList<QString>();
		for (QString _path : *filePaths) {
			for (MusicButton* musicButton : *playlistList->at(currentPlaylistNumber)->getList()) {
				if (_path == musicButton->getTrackPath()) {
					filesToRemove->append(_path);
				}
			}
		}
		for (QString file : *filesToRemove) {
			filePaths->removeOne(file);
		}
		for (int i = 0; i < filePaths->size(); i++) {
			(*playlistList->at(currentPlaylistNumber)->getTrackNumber())++;
			QFileInfo fileInfo(filePaths->at(i));
			MusicButton* newMusicButton = new MusicButton(fileInfo.completeBaseName(),
				*playlistList->at(currentPlaylistNumber)->getTrackNumber() + 1, filePaths->at(i), player, currentTrackNumber, this, this);
			playlistList->at(currentPlaylistNumber)->getList()->append(newMusicButton);
			tracksScrollAreaLayout->addWidget(newMusicButton);
			qDebug() << "Selected files: " << filePaths->at(i);
		}
	}
}
void MainWindow::removeTracks() {
	removeSelectionMode = !removeSelectionMode;
	if (removeSelectionMode) {
		for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
			button->showCheckBox(true);
		}
	}
	else {
		QList<MusicButton*>* buttonsToRemove = new QList<MusicButton*>();
		for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
			if (button->isChecked()) {
				buttonsToRemove->append(button);
			}
		}
		for (MusicButton* button : *buttonsToRemove) {
			playlistList->at(currentPlaylistNumber)->getList()->removeOne(button);
			(*playlistList->at(currentPlaylistNumber)->getTrackNumber())--;
			delete button;
		}
		for (int i = 0; i < playlistList->at(currentPlaylistNumber)->getList()->size(); i++) {
			playlistList->at(currentPlaylistNumber)->getList()->at(i)->setTrackNumber(i + 1);
		}
		for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
			if (player->source() == QUrl::fromLocalFile(button->getTrackPath())) {
				currentTrackNumber = button->getTrackNumber() - 1;
				break;
			}
			else {
				if (!playlistList->at(currentPlaylistNumber)->getList()->isEmpty() && currentTrackNumber != -1) {
					currentTrackNumber = 0;
					player->setSource(QUrl::fromLocalFile(playlistList->
						at(currentPlaylistNumber)->getList()->at(currentTrackNumber)->getTrackPath()));
					playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber)->setActive(true);
					playStopButton->setIcon(QIcon("resources/icons/play.svg"));
				}
				else {
					currentTrackNumber = -1;
				}
			}
		}
		for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
			button->showCheckBox(false);
		}
	}
}
void MainWindow::addPlaylist() {
	bool isOk;
	QString title = QInputDialog::getText(this, "Enter Text", "Enter Text", QLineEdit::Normal, "", &isOk);
	if (isOk && !title.isEmpty()) {
		playlistNumber++;
		PlaylistButton* newPlaylistButton = new PlaylistButton(title, playlistNumber + 1, currentPlaylistNumber, this);
		playlistList->append(newPlaylistButton);
		playlistButtonsScrollAreaLayout->addWidget(newPlaylistButton);
	}
}