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
/*void MainWindow::removeTracks() {
	removeSelectionMode = !removeSelectionMode;
	if (removeSelectionMode) {
		for (MusicButton* button : *playlist) {
			button->showCheckBox(true);
		}
	}
	else {
		bool setFirst = false;
		QList<MusicButton*>* buttonsToRemove = new QList<MusicButton*>();
		for (int i = 0; i < playlist->size(); i++) {
			MusicButton* button = playlist->at(i);
			if (button->isChecked()) {
				buttonsToRemove->append(button);
				if (QUrl(button->getTrackPath()) == player->source())
					setFirst = true;
			}
		}
		for (MusicButton* button : *buttonsToRemove) {
			playlist->removeOne(button);
			trackNumber--;
			delete button;
		}
		buttonsToRemove->clear();
		for (MusicButton* button : *playlist) {
			button->showCheckBox(false);
		}
		for (int i = 0; i < playlist->size(); i++) {
			playlist->at(i)->setTrackNumber(i + 1);
		}
		if (setFirst)
			player->setSource(QUrl::fromLocalFile(playlist->first()->getTrackPath()));
	}
}*/

void MainWindow::removeTracks() {
	/*removeSelectionMode = !removeSelectionMode;
	if (removeSelectionMode) {
		for (MusicButton* button : *playlist) {
			button->showCheckBox(true);
		}
	}
	else {
		bool setFirst = false;
		bool setFirstLastMusicButton = false;
		QList<MusicButton*>* buttonsToRemove = new QList<MusicButton*>();
		for (int i = playlist->size() - 1; i >= 0; i--) {
			MusicButton* button = playlist->at(i);
			if (button->isChecked()) {
				buttonsToRemove->append(button);
				if (player->source() == QUrl(button->getTrackPath())) {
					qDebug() << "current track deleted";
					player->stop();
					playStopButton->setIcon(QIcon("resources/icons/play.svg"));
					setFirst = true;
				}
			}
			else {
				button->showCheckBox(false);
			}
		}
		for (MusicButton* button : *buttonsToRemove) {
			playlist->removeOne(button);
			trackNumber--;
			delete button;
		}
		buttonsToRemove->clear();
		for (int i = 0; i < playlist->size(); i++) {
			playlist->at(i)->setTrackNumber(i + 1);
		}
		for (int i = 0; i < playlist->size() - 1; i++) {
			if (player->source() == QUrl(playlist->at(i)->getTrackPath()) && playlist->size() > 1) {
				currentTrackNumber = playlist->at(i)->getTrackNumber() - 1;
				break;
			}
		}
		if (setFirst) {
			if (!playlist->isEmpty()) {
				player->setSource(QUrl::fromLocalFile(playlist->first()->getTrackPath()));
				playlist->first()->setActive(true);
				currentTrackNumber = 0;
			}
			else {
				player->stop();
				player->setSource(QUrl());
				currentTrackNumber = -1;
			}
		}
	}*/
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