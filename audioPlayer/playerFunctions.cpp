#include "mainWindow.hpp"
#include "musicButton.hpp"

void MainWindow::play() {
	if (playlistList->at(currentPlaylistNumber)->getList()->isEmpty()) return;

	if (player->source().isEmpty()) {
		nextTrack();
		player->play();
		playStopButton->setIcon(QIcon("resources/icons/pause.svg"));
	}
	else if (!player->isPlaying() && !player->source().isEmpty()) {
		player->play();
		playStopButton->setIcon(QIcon("resources/icons/pause.svg"));
	}
	else {
		player->pause();
		playStopButton->setIcon(QIcon("resources/icons/play.svg"));
	}
}
void MainWindow::previousTrack() {
	bool isPlaying;
	if (playlistList->at(currentPlaylistNumber)->getList()->isEmpty()) return;

	isPlaying = player->isPlaying() ? true : false;
	player->stop();
	if (currentTrackNumber != 0) {
		if (currentTrackNumber >= 0) {
			MusicButton* prevTrack = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
			prevTrack->setActive(false);
			currentTrackNumber--;
		}
		else {
			currentTrackNumber = playlistList->at(currentPlaylistNumber)->getList()->size() - 1;
		}
		MusicButton* track = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	else {
		MusicButton* prevTrack = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
		prevTrack->setActive(false);
		currentTrackNumber = playlistList->at(currentPlaylistNumber)->getList()->size() - 1;
		MusicButton* track = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	if (isPlaying) player->play();
}
void MainWindow::nextTrack() {
	bool isPlaying;
	if (playlistList->at(currentPlaylistNumber)->getList()->isEmpty()) return;

	isPlaying = player->isPlaying() ? true : false;
	player->stop();
	if (currentTrackNumber != playlistList->at(currentPlaylistNumber)->getList()->size() - 1) {
		if (currentTrackNumber >= 0) {
			MusicButton* prevTrack = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
			prevTrack->setActive(false);
			currentTrackNumber++;
		}
		else {
			currentTrackNumber = 0;
		}
		MusicButton* track = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
		track->setActive(true);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
		MusicButton::lastMusicButton = track;
	}
	else {
		MusicButton* prevTrack = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
		prevTrack->setActive(false);
		currentTrackNumber = 0;
		MusicButton* track = playlistList->at(currentPlaylistNumber)->getList()->at(currentTrackNumber);
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
void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
	if (status == QMediaPlayer::EndOfMedia) {
		switch (repeatMode) {
		case 0:
			playStopButton->setIcon(QIcon("resources/icons/play.svg"));
			break;
		case 2:
			nextTrack();
			player->play();
			break;
		default:
			break;
		}
	}
}