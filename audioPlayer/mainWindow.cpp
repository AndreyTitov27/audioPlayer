#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"
#include <QtCore/QUrl>

MainWindow::MainWindow() {
	trackNumber = -1;
	currentTrackNumber = -1;

	centralWidget = new QWidget(this);
	//centralWidget->setStyleSheet("border: 1px solid #5DE2E7;");
	mainLayout = new QVBoxLayout(centralWidget);

	topLayout = new QHBoxLayout();
	topLeftLayout = new QVBoxLayout();
	trackCoverLayoutV = new QVBoxLayout();
	trackCoverLayoutH = new QHBoxLayout();
	trackCoverLabel = new QLabel();

	topRightLayout = new QVBoxLayout();
	tracksLayout = new QVBoxLayout();
	tracksScrollArea = new QScrollArea();
	tracksScrollAreaWidget = new QWidget();
	tracksScrollAreaLayout = new QVBoxLayout(tracksScrollAreaWidget);

	bottomLayout = new QVBoxLayout();
	bottomUpLayout = new QHBoxLayout();
	addTrackButton = new QPushButton("+");
	removeTrackButton = new QPushButton("-");
	moveTrackButton = new QPushButton("%");
	manageTracksLayoutV = new QVBoxLayout();
	manageTracksLayoutH = new QHBoxLayout();

	bottomDownLayout = new QHBoxLayout();
	bottomDownLeftLayout = new QVBoxLayout();
	previousTrackButton = new QPushButton("<-", this);
	playStopButton = new QPushButton(">", this);
	nextTrackButton = new QPushButton("->", this);
	playerButtonsLayoutV = new QVBoxLayout();
	playerButtonsLayoutH = new QHBoxLayout();
	loopButton = new QPushButton("O", this);
	loopButtonLayout = new QVBoxLayout();

	bottomDownRightLayout = new QVBoxLayout();
	trackPositionSlider = new QSlider(Qt::Horizontal, this);
	trackPositionSliderLayout = new QVBoxLayout();
	trackVolumeSlider = new QSlider(Qt::Horizontal, this);
	trackVolumeSliderLayout = new QVBoxLayout();

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);
	playlist = new QList<MusicButton*>;

	
	mainLayout->addLayout(topLayout);
	topLayout->addLayout(topLeftLayout);
	topLeftLayout->addLayout(trackCoverLayoutV);
	trackCoverLayoutH->addWidget(trackCoverLabel);
	trackCoverLayoutV->addLayout(trackCoverLayoutH);

	topLayout->addLayout(topRightLayout);
	topRightLayout->addLayout(tracksLayout);
	tracksLayout->addWidget(tracksScrollArea);
	tracksScrollArea->setWidget(tracksScrollAreaWidget);
	//tracksScrollAreaLayout->addWidget(tracksScrollAreaWidget);
	tracksScrollAreaWidget->setLayout(tracksScrollAreaLayout);

	mainLayout->addLayout(bottomLayout);
	//bottomLayout->addLayout(bottomUpLayout);
	//bottomUpLayout->addLayout(manageTracksLayoutV);
	//manageTracksLayoutH->addWidget(addTrackButton);
	//manageTracksLayoutH->addWidget(removeTrackButton);
	//manageTracksLayoutH->addWidget(moveTrackButton);
	//manageTracksLayoutV->addLayout(manageTracksLayoutH);

	//
	bottomLayout->addLayout(bottomDownLayout);
	bottomDownLayout->addLayout(bottomDownLeftLayout);
	bottomDownLeftLayout->addLayout(playerButtonsLayoutV);
	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutV->addLayout(playerButtonsLayoutH);
	bottomDownLeftLayout->addLayout(loopButtonLayout);
	loopButtonLayout->addWidget(loopButton);

	bottomDownLayout->addLayout(bottomDownRightLayout);
	//
	manageTracksLayoutH->addWidget(addTrackButton);
	manageTracksLayoutH->addWidget(removeTrackButton);
	manageTracksLayoutH->addWidget(moveTrackButton);
	manageTracksLayoutV->addLayout(manageTracksLayoutH);
	bottomDownRightLayout->addLayout(manageTracksLayoutV);
	//
	bottomDownRightLayout->addLayout(trackPositionSliderLayout);
	bottomDownRightLayout->addLayout(trackVolumeSliderLayout);
	
	setCentralWidget(centralWidget);

	topLayout->setAlignment(Qt::AlignTop);
	trackCoverLabel->setAlignment(Qt::AlignCenter);
	trackCoverLabel->setMinimumSize(100, 100);
	trackCoverLabel->setMaximumSize(200, 200);
	trackCoverLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	trackCoverLabel->setScaledContents(true);
	trackCoverLayoutV->setAlignment(Qt::AlignTop);
	trackCoverLayoutH->setAlignment(Qt::AlignLeft);
	

	tracksLayout->setAlignment(Qt::AlignRight);
	tracksScrollAreaLayout->setAlignment(Qt::AlignTop);
	tracksScrollArea->setWidgetResizable(true);
	tracksScrollArea->setStyleSheet(scrollAreaStyle);
	tracksScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

	loopButton->setFixedSize(35, 35);
	loopButton->setStyleSheet(manageButtonsStyle);

	connect(loopButton, &QPushButton::clicked, this, &MainWindow::loop);

	loopButtonLayout->addWidget(loopButton, Qt::AlignRight);


	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutH->setAlignment(Qt::AlignBottom);

	

	

	//manageTracksLayoutV->addLayout(manageTracksLayoutH);
	manageTracksLayoutV->setAlignment(Qt::AlignBottom);
	manageTracksLayoutH->setAlignment(Qt::AlignRight);

	QFont manageTrackButtonsFont;
	manageTrackButtonsFont.setPointSize(14);

	
	addTrackButton->setMinimumSize(35, 35);
	addTrackButton->setMaximumSize(50, 50);
	//addTrackButton->setFixedSize(35, 35);
	addTrackButton->setFont(manageTrackButtonsFont);
	addTrackButton->setStyleSheet(manageButtonsStyle);
	addTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	connect(addTrackButton, &QPushButton::clicked, this, &MainWindow::selectMultipleFiles);

	
	removeTrackButton->setMinimumSize(35, 35);
	removeTrackButton->setMaximumSize(50, 50);
	//removeTrackButton->setFixedSize(35, 35);
	removeTrackButton->setFont(manageTrackButtonsFont);
	removeTrackButton->setStyleSheet(manageButtonsStyle);
	removeTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	
	moveTrackButton->setMinimumSize(35, 35);
	moveTrackButton->setMaximumSize(50, 50);
	//moveTrackButton->setFixedSize(35, 35);
	moveTrackButton->setFont(manageTrackButtonsFont);
	moveTrackButton->setStyleSheet(manageButtonsStyle);
	moveTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	//manageTracksLayoutH->addWidget(addTrackButton);
	//manageTracksLayoutH->addWidget(removeTrackButton);
	//manageTracksLayoutH->addWidget(moveTrackButton);


	//overBottomLayout->addLayout(manageTracksLayoutV);

	//mainLayout->addLayout(manageTracksLayoutH); // was overBottomLayout

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

	connect(trackPositionSlider, &QSlider::sliderMoved, this, &MainWindow::setTrackPosition);
	connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSliderPosition);
	connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateSliderRange);

	connect(trackVolumeSlider, &QSlider::valueChanged, this, &MainWindow::setTrackVolume);

	setMinimumSize(500, 350);
	resize(600, 400);
	show();
}

void MainWindow::play() {
	if (!playlist->isEmpty()) {
		if (!player->isPlaying()) {

			player->play();
		}
		else {
			player->pause();
		}
	}
}
void MainWindow::pause() {
	player->pause();
}
void MainWindow::previousTrack() {
	player->pause();
	if (playlist->at(currentTrackNumber - 2) != nullptr) {
		MusicButton* track = playlist->at(currentTrackNumber - 2);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
	}
	else {
		MusicButton* track = playlist->last();
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
	}
	player->play();
}
void MainWindow::nextTrack() {
	player->stop();
	if (playlist->at(currentTrackNumber) != nullptr) {
		MusicButton* track = playlist->at(currentTrackNumber);
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
	}
	else {
		MusicButton* track = playlist->first();
		QString trackPath = track->getTrackPath();
		player->setSource(QUrl::fromLocalFile(trackPath));
	}
	player->play();
}
void MainWindow::loop() {
	player->setLoops(QMediaPlayer::Infinite);
	loopButton->setText("1");
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
	trackCoverLabel->setPixmap(QPixmap::fromImage(coverImage));
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	if (!coverImage.isNull()) {
		trackCoverLabel->setPixmap(QPixmap::fromImage(coverImage).scaled(trackCoverLabel->size(),
			Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	QMainWindow::resizeEvent(event);
	qDebug() << currentTrackNumber;
}