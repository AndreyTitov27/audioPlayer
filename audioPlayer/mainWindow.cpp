#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"
#include <QtCore/QUrl>

MainWindow::MainWindow() {
	isShownFileOptions = false;
	trackNumber = -1;
	currentTrackNumber = -1;

	player = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);
	player->setAudioOutput(audioOutput);
	playlist = new QList<MusicButton*>;
	trackPositionSlider = new QSlider(Qt::Horizontal, this);
	trackVolumeSlider = new QSlider(Qt::Horizontal, this);

	trackPositionSlider->setRange(0, player->duration() / 1000);
	trackVolumeSlider->setRange(0, 100);
	trackVolumeSlider->setValue(50);
	trackVolumeSlider->setMinimumWidth(120);
	trackVolumeSlider->setMaximumWidth(120);
	trackVolumeSlider->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

	trackPositionSliderLayout = new QVBoxLayout();
	trackVolumeSliderLayout = new QVBoxLayout();

	trackPositionSliderLayout->addWidget(trackPositionSlider);
	trackVolumeSliderLayout->addWidget(trackVolumeSlider);
	trackVolumeSliderLayout->setAlignment(Qt::AlignLeft);

	connect(player, &QMediaPlayer::metaDataChanged, this, &MainWindow::processMetaData);

	connect(trackPositionSlider, &QSlider::sliderMoved, this, &MainWindow::setTrackPosition);
	connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSliderPosition);
	connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateSliderRange);

	connect(trackVolumeSlider, &QSlider::valueChanged, this, &MainWindow::setTrackVolume);

	playerButtonsLayoutV = new QVBoxLayout();
	playerButtonsLayoutH = new QHBoxLayout();

	centralWidget = new QWidget(this);
	centralWidget->setStyleSheet("border: 1px solid #5DE2E7;");
	mainLayout = new QVBoxLayout(centralWidget);
	bottomLayout = new QHBoxLayout();
	bottomLayout->setAlignment(Qt::AlignBottom);
	bottomLeftLayout = new QVBoxLayout();
	bottomLeftLayout->setAlignment(Qt::AlignBottom);
	bottomRightLayout = new QVBoxLayout();
	bottomRightLayout->setAlignment(Qt::AlignBottom);
	bottomLayout->addLayout(bottomLeftLayout);
	bottomLayout->addLayout(bottomRightLayout);
	overBottomLayout = new QHBoxLayout();
	overBottomLayout->setAlignment(Qt::AlignBottom);

	centralLayoutH = new QHBoxLayout();
	centralLayoutH->setAlignment(Qt::AlignBottom);
	leftLayout = new QVBoxLayout();
	leftLayout->setAlignment(Qt::AlignLeft);
	rightLayout = new QVBoxLayout();
	rightLayout->setAlignment(Qt::AlignBottom);
	setCentralWidget(centralWidget);

	manageTracksLayoutV = new QVBoxLayout();
	manageTracksLayoutH = new QHBoxLayout();
	tracksLayout = new QVBoxLayout();

	tracksScrollArea = new QScrollArea();
	tracksScrollAreaWidget = new QWidget();
	tracksScrollAreaLayout = new QVBoxLayout(tracksScrollAreaWidget);
	tracksScrollAreaLayout->setAlignment(Qt::AlignTop);
	tracksScrollArea->setWidget(tracksScrollAreaWidget);
	tracksScrollArea->setWidgetResizable(true);
	tracksScrollArea->setStyleSheet(scrollAreaStyle);
	tracksScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	tracksLayout->addWidget(tracksScrollArea);

	previousTrackButton = new QPushButton("<-", this);
	previousTrackButton->setFixedSize(50, 50);
	previousTrackButton->setStyleSheet(playerButtonsStyle);
	connect(previousTrackButton, &QPushButton::clicked, this, &MainWindow::previousTrack);

	playStopButton = new QPushButton(">", this);
	playStopButton->setFixedSize(50, 50);
	playStopButton->setStyleSheet(playerButtonsStyle);
	connect(playStopButton, &QPushButton::clicked, this, &MainWindow::play);

	nextTrackButton = new QPushButton("->", this);
	nextTrackButton->setFixedSize(50, 50);
	nextTrackButton->setStyleSheet(playerButtonsStyle);
	connect(nextTrackButton, &QPushButton::clicked, this, &MainWindow::nextTrack);

	loopButton = new QPushButton("O", this);
	loopButton->setFixedSize(50, 35);
	loopButton->setStyleSheet(manageButtonsStyle);

	loopButtonLayout = new QVBoxLayout();
	loopButtonLayout->addWidget(loopButton, Qt::AlignRight);


	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutH->setAlignment(Qt::AlignBottom);

	trackCoverLayoutV = new QVBoxLayout();
	trackCoverLayoutH = new QHBoxLayout();
	trackCoverLabel = new QLabel();

	trackCoverLabel->setAlignment(Qt::AlignCenter);
	trackCoverLabel->setMinimumSize(100, 100);
	trackCoverLabel->setMaximumSize(200, 200);
	trackCoverLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	trackCoverLabel->setScaledContents(true);
	trackCoverLayoutV->addLayout(trackCoverLayoutH);
	trackCoverLayoutH->addWidget(trackCoverLabel);
	trackCoverLayoutV->setAlignment(Qt::AlignTop);
	trackCoverLayoutH->setAlignment(Qt::AlignLeft);

	//manageTracksLayoutV->addLayout(manageTracksLayoutH);
	manageTracksLayoutV->setAlignment(Qt::AlignBottom);
	manageTracksLayoutH->setAlignment(Qt::AlignRight);

	QFont manageTrackButtonsFont;
	manageTrackButtonsFont.setPointSize(14);

	addTrackButton = new QPushButton("+");
	addTrackButton->setMinimumSize(35, 35);
	addTrackButton->setMaximumSize(50, 50);
	//addTrackButton->setFixedSize(35, 35);
	addTrackButton->setFont(manageTrackButtonsFont);
	addTrackButton->setStyleSheet(manageButtonsStyle);
	addTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	connect(addTrackButton, &QPushButton::clicked, this, &MainWindow::selectMultipleFiles);

	removeTrackButton = new QPushButton("-");
	removeTrackButton->setMinimumSize(35, 35);
	removeTrackButton->setMaximumSize(50, 50);
	//removeTrackButton->setFixedSize(35, 35);
	removeTrackButton->setFont(manageTrackButtonsFont);
	removeTrackButton->setStyleSheet(manageButtonsStyle);
	removeTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	moveTrackButton = new QPushButton("%");
	moveTrackButton->setMinimumSize(35, 35);
	moveTrackButton->setMaximumSize(50, 50);
	//moveTrackButton->setFixedSize(35, 35);
	moveTrackButton->setFont(manageTrackButtonsFont);
	moveTrackButton->setStyleSheet(manageButtonsStyle);
	moveTrackButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	manageTracksLayoutH->addWidget(addTrackButton, Qt::AlignBottom);
	manageTracksLayoutH->addWidget(removeTrackButton, Qt::AlignBottom);
	manageTracksLayoutH->addWidget(moveTrackButton, Qt::AlignBottom);

	bottomLeftLayout->addLayout(playerButtonsLayoutH);
	bottomLeftLayout->addLayout(loopButtonLayout);
	bottomRightLayout->addLayout(trackPositionSliderLayout);
	bottomRightLayout->addItem(new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum));
	bottomRightLayout->addLayout(trackVolumeSliderLayout);
	bottomRightLayout->addItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum));

	//overBottomLayout->addLayout(manageTracksLayoutV);
	superBottomLayout = new QVBoxLayout();
	superBottomLayout->addLayout(manageTracksLayoutH);
	superBottomLayout->addLayout(bottomLayout);
	superBottomLayout->setAlignment(Qt::AlignBottom);

	centralLayoutH->addLayout(leftLayout);
	centralLayoutH->addLayout(rightLayout);

	leftLayout->addLayout(trackCoverLayoutV);

	rightLayout->addLayout(tracksLayout);

	mainLayout->addLayout(centralLayoutH);
	//mainLayout->addLayout(manageTracksLayoutH); // was overBottomLayout
	mainLayout->addLayout(superBottomLayout);

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