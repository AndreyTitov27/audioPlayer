#include "mainWindow.hpp"
#include <QtWidgets/QStyle>

void MainWindow::minimize() {
	showMinimized();
}
void MainWindow::maximize() {
	if (isMaximized()) {
		showNormal();
	}
	else {
		showMaximized();
	}
}
MainWindow::MainWindow() {
	setWindowFlags(Qt::FramelessWindowHint);
	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	centralWidget->setLayout(mainLayout);

	titleBar = new QWidget(this);
	titleBar->setStyleSheet("background-color: #373333; color: #FDFAFA;");
	titleBar->setFixedHeight(35);

	titleLayout = new QHBoxLayout(titleBar);
	titleLayout->setContentsMargins(0, 0, 0, 0);
	titleLayout->setSpacing(0);

	minimizeButton = new QPushButton(QString::fromUtf8(u8"\u2014"), this);
	QFont minimizeButtonFont = minimizeButton->font();
	minimizeButtonFont.setPointSize(10);
	minimizeButton->setFont(minimizeButtonFont);
	maximizeButton = new QPushButton(QString::fromUtf8(u8"\u2610"), this);
	QFont maximizeButtonFont = maximizeButton->font();
	maximizeButtonFont.setPointSize(10);
	maximizeButton->setFont(maximizeButtonFont);
	closeButton = new QPushButton(QString::fromUtf8(u8"\u2A09"), this);
	QFont closeButtonFont = closeButton->font();
	closeButtonFont.setPointSize(10);
	closeButton->setFont(closeButtonFont);

	minimizeButton->setFixedSize(45, 35);
	minimizeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 5px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #433B3B;"
		"    padding: 4px 9px;"
		"}"
	);
	maximizeButton->setFixedSize(45, 35);
	maximizeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 5px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #433B3B;"
		"    padding: 4px 9px;"
		"}"
	);
	closeButton->setFixedSize(45, 35);
	closeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 5px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #C11314;"
		"    padding: 4px 9px;"
		"}"
	);

	titleLayout->addWidget(minimizeButton);
	titleLayout->addWidget(maximizeButton);
	titleLayout->addWidget(closeButton);
	titleLayout->setAlignment(Qt::AlignRight);
	
	titleBar->setLayout(titleLayout);

	mainLayout->addWidget(titleBar);

	contentWidget = new QWidget(this);

	mainLayout->addWidget(contentWidget);

	setCentralWidget(centralWidget);

	connect(minimizeButton, &QPushButton::clicked, this, &MainWindow::minimize);
	connect(maximizeButton, &QPushButton::clicked, this, &MainWindow::maximize);
	connect(closeButton, &QPushButton::clicked, this, &MainWindow::close);
	resize(600, 400);
	show();
}