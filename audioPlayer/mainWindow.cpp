#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"

MainWindow::MainWindow() {
	selectSingleTrackButton = nullptr;
	selectMultipleTracksButton = nullptr;

	isShownFileOptions = false;

	centralWidget = new QWidget(this);
	centralWidget->setStyleSheet("border: 1px solid #5DE2E7;");
	mainLayout = new QVBoxLayout(centralWidget);
	setCentralWidget(centralWidget);

	manageTracksLayoutV = new QVBoxLayout();
	manageTracksLayoutH = new QHBoxLayout();
	tracksLayout = new QVBoxLayout();
	addTrackOptionsLayout = new QVBoxLayout();
	addTrackOptionsLayout->setAlignment(Qt::AlignLeft);

	playerButtonsLayoutV = new QVBoxLayout();
	playerButtonsLayoutH = new QHBoxLayout();

	previousTrackButton = new QPushButton("<-", this);
	previousTrackButton->setFixedSize(50, 50);
	previousTrackButton->setStyleSheet(playerButtonsStyle);
	playStopButton = new QPushButton(">", this);
	playStopButton->setFixedSize(50, 50);
	playStopButton->setStyleSheet(playerButtonsStyle);
	nextTrackButton = new QPushButton("->", this);
	nextTrackButton->setFixedSize(50, 50);
	nextTrackButton->setStyleSheet(playerButtonsStyle);
	playerButtonsLayoutH->addWidget(previousTrackButton);
	playerButtonsLayoutH->addWidget(playStopButton);
	playerButtonsLayoutH->addWidget(nextTrackButton);
	playerButtonsLayoutH->setAlignment(Qt::AlignCenter);

	playerButtonsLayoutV->addLayout(playerButtonsLayoutH);
	playerButtonsLayoutV->setAlignment(Qt::AlignBottom);

	mainLayout->addLayout(tracksLayout);
	manageTracksLayoutV->addLayout(addTrackOptionsLayout);
	manageTracksLayoutV->addLayout(manageTracksLayoutH);

	manageTracksLayoutV->setAlignment(Qt::AlignBottom);
	manageTracksLayoutH->setAlignment(Qt::AlignLeft);

	QFont manageTrackButtonsFont;
	manageTrackButtonsFont.setPointSize(14);

	addTrackButton = new QPushButton("+");
	addTrackButton->setFixedSize(40, 40);
	addTrackButton->setFont(manageTrackButtonsFont);
	addTrackButton->setStyleSheet(manageButtonsStyle);
	
	connect(addTrackButton, &QPushButton::clicked, this, &MainWindow::showFileOptions);

	removeTrackButton = new QPushButton("-");
	removeTrackButton->setFixedSize(40, 40);
	removeTrackButton->setFont(manageTrackButtonsFont);
	removeTrackButton->setStyleSheet(manageButtonsStyle);

	manageTracksLayoutH->addWidget(addTrackButton);
	manageTracksLayoutH->addWidget(removeTrackButton);
	
	mainLayout->addLayout(playerButtonsLayoutV);
	mainLayout->addLayout(manageTracksLayoutV);

	setMinimumSize(400, 250);
	resize(600, 400);
	show();
}
