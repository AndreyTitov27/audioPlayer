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
	removeTracksSelectionMode = !removeTracksSelectionMode;
	if (removeTracksSelectionMode) {
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
		for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
			button->showCheckBox(false);
		}
		if (buttonsToRemove->isEmpty()) {
			return;
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
					MusicButton::lastMusicButton = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
					playStopButton->setIcon(QIcon("resources/icons/play.svg"));
				}
				else {
					currentTrackNumber = -1;
				}
			}
		}
	}
}
void MainWindow::moveTracks() {
	tracksDragging = !tracksDragging;
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
void MainWindow::removePlaylist() {
	removePlaylistSelectionMode = !removePlaylistSelectionMode;
	if (removePlaylistSelectionMode) {
		for (PlaylistButton* playlist : *playlistList) {
			playlist->showCheckBox(true);
		}
	}
	else {
		QList<PlaylistButton*>* playlistsToRemove = new QList<PlaylistButton*>();
		for (PlaylistButton* playlist : *playlistList) {
			if (playlist->isChecked()) {
				playlistsToRemove->append(playlist);
			}
		}
		for (PlaylistButton* playlist : *playlistList) {
			playlist->showCheckBox(false);
		}
		if (playlistsToRemove->isEmpty()) {
			return;
		}
		for (PlaylistButton* playlist : *playlistsToRemove) {
			for (MusicButton* button : *playlist->getList()) {
				playlist->getList()->removeOne(button);
				delete button;
			}
			if (playlist == playlistList->at(currentPlaylistNumber)) {
				currentPlaylistNumber = 0;
				playlistList->at(currentPlaylistNumber)->showMusicButtons();
			}
			playlistNumber--;
			playlistList->removeOne(playlist);
			delete playlist;
		}
		for (int i = 0; i < playlistList->size(); i++) {
			playlistList->at(i)->setPlaylistNumber(i + 1);
		}
	}
}