#include "mainWindow.hpp"

MainWindow::MainWindow() {

	initializeWidgets();

	trackNumber = -1;
	currentTrackNumber = -1;
	playlistNumber = -1;
	currentPlaylistNumber = -1;
	repeatMode = 0;
	removeSelectionMode = false;
	showPlaylistsFlag = false;
	isTrackDownloading = false;

	topLayout->setAlignment(Qt::AlignBottom);
	settingsButtonLayout->setAlignment(Qt::AlignLeft);
	settingsButton->setFixedSize(10, 10);
	settingsButton->setIconSize(QSize(10, 10));
	connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);

	downloadTrackButton->setFixedSize(10, 10);
	downloadTrackButton->setIconSize(QSize(10, 10));
	connect(downloadTrackButton, &QPushButton::clicked, this, &MainWindow::openDownloadingWindow);

	trackCoverLabel->setAlignment(Qt::AlignCenter);
	trackCoverLabel->setFixedSize(200, 200);
	trackCoverLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	trackCoverLabel->setScaledContents(true);
	coverImage = QImage("resources/defaultCover.png");
	trackCoverLabel->setPixmap(QPixmap::fromImage(coverImage));
	trackCoverLayoutV->setAlignment(Qt::AlignTop);
	trackCoverLayoutH->setAlignment(Qt::AlignLeft);

	tracksPlaylistsLayout->setAlignment(Qt::AlignRight);
	tracksPlaylistsLayout->setSpacing(0);
	tracksScrollAreaLayout->setAlignment(Qt::AlignTop);
	tracksScrollArea->setWidgetResizable(true);
	tracksScrollArea->setStyleSheet(scrollAreaStyle);
	tracksScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	playlistButtonsScrollAreaLayout->setAlignment(Qt::AlignTop);
	playlistButtonsScrollAreaLayout->setContentsMargins(0, 9, 0, 0);
	playlistButtonsScrollArea->setWidgetResizable(true);
	playlistButtonsScrollArea->setStyleSheet(scrollAreaStyle);
	playlistButtonsScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	playlistButtonsScrollArea->setContentsMargins(0, 0, 0, 0);
	playlistButtonsScrollAreaWidget->setContentsMargins(0, 0, 0, 0);

	bottomLayout->setAlignment(Qt::AlignBottom);
	bottomUpLayout->setAlignment(Qt::AlignBottom);
	bottomDownRightLayout->setAlignment(Qt::AlignBottom);

	previousTrackButton->setFixedSize(50, 50);
	previousTrackButton->setStyleSheet(playerButtonsStyle);
	connect(previousTrackButton, &QPushButton::clicked, this, &MainWindow::previousTrack);

	playStopButton->setFixedSize(50, 50);
	playStopButton->setStyleSheet(playerButtonsStyle);
	connect(playStopButton, &QPushButton::clicked, this, &MainWindow::play);

	nextTrackButton->setFixedSize(50, 50);
	nextTrackButton->setStyleSheet(playerButtonsStyle);
	connect(nextTrackButton, &QPushButton::clicked, this, &MainWindow::nextTrack);

	repeatButton->setFixedSize(35, 35);
	repeatButton->setStyleSheet(manageButtonsStyle);

	connect(repeatButton, &QPushButton::clicked, this, &MainWindow::repeat);

	repeatButtonLayout->addWidget(repeatButton, Qt::AlignRight);


	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutH->setAlignment(Qt::AlignBottom);

	manageTracksLayoutV->setAlignment(Qt::AlignBottom);
	manageTracksLayoutH->setAlignment(Qt::AlignRight);

	QFont manageTrackButtonsFont;
	manageTrackButtonsFont.setPointSize(14);

	showPlaylistsButton->setFixedSize(35, 35);
	showPlaylistsButton->setStyleSheet(manageButtonsStyle);
	showPlaylistsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connect(showPlaylistsButton, &QPushButton::clicked, this, &MainWindow::showPlaylists);

	addPlaylistButton->setFixedSize(35, 35);
	addPlaylistButton->setStyleSheet(manageButtonsStyle);
	addPlaylistButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connect(addPlaylistButton, &QPushButton::clicked, this, &MainWindow::addPlaylist);

	removePlaylistButton->setFixedSize(35, 35);
	removePlaylistButton->setStyleSheet(manageButtonsStyle);
	removePlaylistButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//connect(removePlaylistButton, &QPushButton::clicked, this, &MainWindow::removePlaylist);

	addTrackButton->setFixedSize(35, 35);
	addTrackButton->setFont(manageTrackButtonsFont);
	addTrackButton->setStyleSheet(manageButtonsStyle);
	addTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connect(addTrackButton, &QPushButton::clicked, this, &MainWindow::addTracks);

	removeTrackButton->setFixedSize(35, 35);
	removeTrackButton->setFont(manageTrackButtonsFont);
	removeTrackButton->setStyleSheet(manageButtonsStyle);
	removeTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//connect(removeTrackButton, &QPushButton::clicked, this, &MainWindow::removeTracks);

	moveTrackButton->setFixedSize(35, 35);
	moveTrackButton->setFont(manageTrackButtonsFont);
	moveTrackButton->setStyleSheet(manageButtonsStyle);
	moveTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	player->setAudioOutput(audioOutput);

	trackPositionSlider->setRange(0, player->duration() / 1000);
	trackVolumeSlider->setRange(0, 100);
	trackVolumeSlider->setValue(50);
	trackVolumeSlider->setMinimumWidth(120);
	trackVolumeSlider->setMaximumWidth(120);
	trackVolumeSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

	trackPositionSliderLayout->addWidget(trackPositionSlider);
	trackVolumeSliderLayout->addWidget(trackVolumeSlider);
	trackVolumeSliderLayout->setAlignment(Qt::AlignLeft);

	connect(player, &QMediaPlayer::metaDataChanged, this, &MainWindow::processMetaData);

	connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);

	connect(trackPositionSlider, &QSlider::sliderMoved, this, &MainWindow::setTrackPosition);
	connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSliderPosition);
	connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateSliderRange);

	connect(trackVolumeSlider, &QSlider::valueChanged, this, &MainWindow::setTrackVolume);

	loadSettings(this);

	{
		if (playlistList->isEmpty()) {
			playlistNumber++;
			currentPlaylistNumber++;
			PlaylistButton* newPlaylistButton = new PlaylistButton("Default", playlistNumber + 1, currentPlaylistNumber, this);
			playlistList->append(newPlaylistButton);
			playlistButtonsScrollAreaLayout->addWidget(newPlaylistButton);
			PlaylistButton::lastPlaylistButton = newPlaylistButton;
			newPlaylistButton->setStyleSheet(playlistButtonClickedStyle);
		}
		else {
			currentPlaylistNumber = 0;
			PlaylistButton::lastPlaylistButton = playlistList->first();
			playlistList->first()->setStyleSheet(playlistButtonClickedStyle);
			for (MusicButton* button : *playlistList->at(currentPlaylistNumber)->getList()) {
				button->setVisible(true);
			}
		}
	}

	setMinimumSize(500, 350);
	resize(600, 400);
	show();
}
void MainWindow::showPlaylists() {
	showPlaylistsFlag = !showPlaylistsFlag;
	if (showPlaylistsFlag) {
		playlistButtonsScrollArea->setVisible(true);
		addPlaylistButton->setVisible(true);
		removePlaylistButton->setVisible(true);
	}
	else {
		playlistButtonsScrollArea->setVisible(false);
		addPlaylistButton->setVisible(false);
		removePlaylistButton->setVisible(false);
	}
}
void MainWindow::createPlaylistsLayout() {

}
void MainWindow::setVolume(float vol) {
	audioOutput->setVolume(vol);
	trackVolumeSlider->setValue(vol * 100);
}
void MainWindow::setRepeatMode(int mode) {
	repeatMode = mode;
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
void MainWindow::updateStyles() {
	showPlaylistsButton->setStyleSheet(manageButtonsStyle);
	addTrackButton->setStyleSheet(manageButtonsStyle);
	removeTrackButton->setStyleSheet(manageButtonsStyle);
	moveTrackButton->setStyleSheet(manageButtonsStyle);
	repeatButton->setStyleSheet(manageButtonsStyle);

	previousTrackButton->setStyleSheet(playerButtonsStyle);
	playStopButton->setStyleSheet(playerButtonsStyle);
	nextTrackButton->setStyleSheet(playerButtonsStyle);
}

void MainWindow::setTrackPosition(int pos) {
	player->setPosition((qint64)pos * 1000);
}
void MainWindow::updateSliderPosition(qint64 pos) {
	trackPositionSlider->setValue(pos / 1000);
}
void MainWindow::updateSliderRange(qint64 duration) {
	trackPositionSlider->setRange(0, duration / 1000);
}

void MainWindow::setTrackVolume(int volume) {
	audioOutput->setVolume(volume / 100.0F);
}

void MainWindow::processMetaData() {
	coverImage = player->metaData().value(QMediaMetaData::ThumbnailImage).value<QImage>();
	if (coverImage.isNull()) {
		coverImage = QImage("resources/defaultCover.png");
	}
	trackCoverLabel->setPixmap(QPixmap::fromImage(coverImage));
}
void MainWindow::openSettingsWindow() {
	settingsWindow->setVisible(true);
}
void MainWindow::openDownloadingWindow() {
	if (!isTrackDownloading) {
		downloadingWindow->setVisible(true);
	}
	else {
		QMessageBox msgBox(this);
		msgBox.setWindowTitle("Information");
		msgBox.setText("Track is Downloading");
		msgBox.setIcon(QMessageBox::Information);
		msgBox.exec();
	}
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	if (!coverImage.isNull()) {
		trackCoverLabel->setPixmap(QPixmap::fromImage(coverImage).scaled(trackCoverLabel->size(),
			Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	QMainWindow::resizeEvent(event);
	qDebug() << "current track: " << currentTrackNumber;
	qDebug() << "current playlist: " << currentPlaylistNumber;
}
void MainWindow::closeEvent(QCloseEvent* event) {
	saveSettings(this);
	QMainWindow::closeEvent(event);
}