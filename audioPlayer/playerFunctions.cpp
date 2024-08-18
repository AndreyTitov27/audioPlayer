#include "mainWindow.hpp"
#include "musicButton.hpp"

void MainWindow::play() {
	if (playlist->isEmpty()) return;

	if (!player->isPlaying()) {
		player->play();
	}
	else {
		player->pause();
	}
}
void MainWindow::previousTrack() {
	bool isPlaying;
	if (playlist->isEmpty()) return;

	isPlaying = player->isPlaying() ? true : false;
	player->stop();
	if (currentTrackNumber != 0) {
		if (currentTrackNumber >= 0) {
			MusicButton* prevTrack = playlist->at(currentTrackNumber);
			prevTrack->setActive(false);
			currentTrackNumber--;
		}
		else {
			currentTrackNumber = playlist->size() - 1;
		}
		MusicButton* track = playlist->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	else {
		MusicButton* prevTrack = playlist->at(currentTrackNumber);
		prevTrack->setActive(false);
		currentTrackNumber = playlist->size() - 1;
		MusicButton* track = playlist->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	if (isPlaying) player->play();
}
void MainWindow::nextTrack() {
	bool isPlaying;
	if (playlist->isEmpty()) return;

	isPlaying = player->isPlaying() ? true : false;
	player->stop();
	if (currentTrackNumber != playlist->size() - 1) {
		if (currentTrackNumber >= 0) {
			MusicButton* prevTrack = playlist->at(currentTrackNumber);
			prevTrack->setActive(false);
			currentTrackNumber++;
		}
		else {
			currentTrackNumber = 0;
		}
		MusicButton* track = playlist->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	else {
		MusicButton* prevTrack = playlist->at(currentTrackNumber);
		prevTrack->setActive(false);
		currentTrackNumber = 0;
		MusicButton* track = playlist->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	if (isPlaying) player->play();
}
void MainWindow::repeat() {
	repeatMode = repeatMode == 2 ? 0 : ++repeatMode;
	switch (repeatMode) {
	case 0:
		player->setLoops(QMediaPlayer::Once);
		repeatButton->setIcon(QIcon("resources/icons/repeatOff.svg"));
		break;
	case 1:
		player->setLoops(QMediaPlayer::Infinite);
		repeatButton->setIcon(QIcon("resources/icons/repeatOne.svg"));
		break;
	case 2:
		player->setLoops(QMediaPlayer::Once);
		repeatButton->setIcon(QIcon("resources/icons/repeatAll.svg"));
		break;
	default:
		break;
	}
}