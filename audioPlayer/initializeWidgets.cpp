#include "mainWindow.hpp"

void MainWindow::initializeWidgets() {
	settingsWindow = new SettingsWindow(this, this);
	downloadingWindow = new DownloadingWindow(this, this);

	centralWidget = new QWidget(this);
	//centralWidget->setStyleSheet("border: 1px solid #5DE2E7;");
	mainLayout = new QVBoxLayout(centralWidget);

	topLayout = new QHBoxLayout();
	topLeftLayout = new QVBoxLayout();
	settingsButtonLayout = new QHBoxLayout();
	settingsButton = new QPushButton(QIcon("resources/icons/settings.svg"), "", this);
	downloadTrackButton = new QPushButton(QIcon("resources/icons/web.svg"), "", this);
	trackCoverLayoutV = new QVBoxLayout();
	trackCoverLayoutH = new QHBoxLayout();
	trackCoverLabel = new QLabel();

	topRightLayout = new QVBoxLayout();
	tracksPlaylistsLayout = new QHBoxLayout();
	tracksScrollArea = new QScrollArea();
	tracksScrollAreaWidget = new QWidget();
	tracksScrollAreaLayout = new QVBoxLayout(tracksScrollAreaWidget);
	//
	playlistButtonsScrollArea = new QScrollArea();
	playlistButtonsScrollAreaWidget = new QWidget();
	playlistButtonsScrollAreaLayout = new QVBoxLayout(playlistButtonsScrollAreaWidget);

	bottomLayout = new QVBoxLayout();
	bottomUpLayout = new QHBoxLayout();
	showPlaylistsButton = new QPushButton(QIcon("resources/icons/playlist.svg"), "");
	showPlaylistsButton->setIconSize(QSize(25, 25));
	addTrackButton = new QPushButton(QIcon("resources/icons/add.svg"), "");
	addTrackButton->setIconSize(QSize(25, 25));
	removeTrackButton = new QPushButton(QIcon("resources/icons/remove.svg"), "");
	removeTrackButton->setIconSize(QSize(25, 25));
	moveTrackButton = new QPushButton(QIcon("resources/icons/move.svg"), "");
	moveTrackButton->setIconSize(QSize(25, 25));
	//
	addPlaylistButton = new QPushButton(QIcon("resources/icons/addPlaylist.svg"), "");
	addPlaylistButton->setIconSize(QSize(25, 25));
	removePlaylistButton = new QPushButton(QIcon("resources/icons/removePlaylist.svg"), "");
	removePlaylistButton->setIconSize(QSize(25, 25));
	manageTracksLayoutV = new QVBoxLayout();
	manageTracksLayoutH = new QHBoxLayout();

	bottomDownLayout = new QHBoxLayout();
	bottomDownLeftLayout = new QVBoxLayout();
	previousTrackButton = new QPushButton(QIcon("resources/icons/previous.svg"), "", this);
	previousTrackButton->setIconSize(QSize(25, 25));
	playStopButton = new QPushButton(QIcon("resources/icons/play.svg"), "", this);
	playStopButton->setIconSize(QSize(25, 25));
	nextTrackButton = new QPushButton(QIcon("resources/icons/next.svg"), "", this);
	nextTrackButton->setIconSize(QSize(25, 25));
	playerButtonsLayoutV = new QVBoxLayout();
	playerButtonsLayoutH = new QHBoxLayout();
	repeatButton = new QPushButton(QIcon("resources/icons/repeatOff.svg"), "", this);
	repeatButton->setIconSize(QSize(25, 25));
	repeatButtonLayout = new QHBoxLayout();

	bottomDownRightLayout = new QVBoxLayout();
	trackPositionSlider = new QSlider(Qt::Horizontal, this);
	trackPositionSliderLayout = new QVBoxLayout();
	trackVolumeSlider = new QSlider(Qt::Horizontal, this);
	trackVolumeSliderLayout = new QVBoxLayout();

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);
	playlistList = new QList<PlaylistButton*>();

	settingsWindow->setVisible(false);
	downloadingWindow->setVisible(false);

	mainLayout->addLayout(topLayout, 1);
	topLayout->addLayout(topLeftLayout);
	topLeftLayout->addLayout(settingsButtonLayout);
	settingsButtonLayout->addWidget(settingsButton);
	settingsButtonLayout->addWidget(downloadTrackButton);
	topLeftLayout->addLayout(trackCoverLayoutV);
	trackCoverLayoutH->addWidget(trackCoverLabel);
	trackCoverLayoutV->addLayout(trackCoverLayoutH);

	topLayout->addLayout(topRightLayout);
	topRightLayout->addLayout(tracksPlaylistsLayout);
	tracksPlaylistsLayout->addWidget(playlistButtonsScrollArea, 1);
	playlistButtonsScrollArea->setWidget(playlistButtonsScrollAreaWidget);
	playlistButtonsScrollAreaWidget->setLayout(playlistButtonsScrollAreaLayout);

	tracksPlaylistsLayout->addWidget(tracksScrollArea, 2);
	tracksScrollArea->setWidget(tracksScrollAreaWidget);
	tracksScrollAreaWidget->setLayout(tracksScrollAreaLayout);

	playlistButtonsScrollArea->setVisible(false);

	mainLayout->addLayout(bottomLayout);

	bottomLayout->addLayout(bottomDownLayout);
	bottomDownLayout->addLayout(bottomDownLeftLayout);
	bottomDownLeftLayout->addLayout(playerButtonsLayoutV);
	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutV->addLayout(playerButtonsLayoutH);
	bottomDownLeftLayout->addLayout(repeatButtonLayout);
	repeatButtonLayout->addWidget(repeatButton, Qt::AlignHCenter);

	bottomDownLayout->addLayout(bottomDownRightLayout);
	//
	bottomDownRightLayout->addLayout(manageTracksLayoutV);
	manageTracksLayoutV->addLayout(manageTracksLayoutH);
	manageTracksLayoutH->addWidget(addPlaylistButton);
	manageTracksLayoutH->addWidget(removePlaylistButton);
	manageTracksLayoutH->addWidget(showPlaylistsButton);
	manageTracksLayoutH->addWidget(addTrackButton);
	manageTracksLayoutH->addWidget(removeTrackButton);
	manageTracksLayoutH->addWidget(moveTrackButton);
	//
	addPlaylistButton->setVisible(false);
	removePlaylistButton->setVisible(false);

	bottomDownRightLayout->addLayout(trackPositionSliderLayout);
	bottomDownRightLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));
	bottomDownRightLayout->addLayout(trackVolumeSliderLayout);
	bottomDownRightLayout->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));

	setCentralWidget(centralWidget);
}