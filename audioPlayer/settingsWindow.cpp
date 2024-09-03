#include "settingsWindow.hpp"

SettingsWindow::SettingsWindow(MainWindow* mainWindowInstance, QMainWindow* parent)
	: QMainWindow(parent), mainWindowInstance(mainWindowInstance) {
	lastColor = Qt::white;
	setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	centralWidget = new QWidget(this);
	mainLayout = new QHBoxLayout(centralWidget);
	leftLayout = new QVBoxLayout();
	customizeButton = new SettingsButton(QString("Customize"), this);
	rightLayout = new QVBoxLayout();
	rightCentralWidget = new QWidget();
	rightCentralLayout = new QVBoxLayout();
	firstLayout = nullptr;

	mainLayout->addLayout(leftLayout);
	leftLayout->addWidget(customizeButton);

	mainLayout->addLayout(rightLayout);
	rightLayout->addWidget(rightCentralWidget);
	rightCentralWidget->setLayout(rightCentralLayout);

	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);

	rightCentralWidget->setStyleSheet("background-color: #292323;");
	rightCentralWidget->setFixedSize(400, 400);
	rightCentralLayout->setAlignment(Qt::AlignTop);

	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
	setFixedSize(600, 400);
}

void SettingsWindow::showCustomizeOptions() {
	if (firstLayout == nullptr) {
		firstLayout = new QHBoxLayout();
		firstLine = new QLabel("Select buttons background color:");
		firstLine->setAlignment(Qt::AlignLeft);
		firstButton = new QPushButton("pick");
		firstButton->setStyleSheet(manageButtonsStyle);
		connect(firstButton, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		firstLayout->addWidget(firstLine, Qt::AlignLeft);
		firstLayout->addWidget(firstButton);

		secondLayout = new QHBoxLayout();
		secondLine = new QLabel("Select buttons hover color:");
		secondLine->setAlignment(Qt::AlignLeft);
		secondButton = new QPushButton("pick");
		secondButton->setStyleSheet(manageButtonsStyle);
		connect(secondButton, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		secondLayout->addWidget(secondLine, Qt::AlignLeft);
		secondLayout->addWidget(secondButton);

		thirdLayout = new QHBoxLayout();
		thirdLine = new QLabel("Select buttons press color:");
		thirdLine->setAlignment(Qt::AlignLeft);
		thirdButton = new QPushButton("pick");
		thirdButton->setStyleSheet(manageButtonsStyle);
		connect(thirdButton, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		thirdLayout->addWidget(thirdLine, Qt::AlignLeft);
		thirdLayout->addWidget(thirdButton);

		fourthLayout = new QHBoxLayout();
		fourthLine = new QLabel("Select round buttons background color:");
		fourthLine->setAlignment(Qt::AlignLeft);
		fourthButton = new QPushButton("pick");
		fourthButton->setStyleSheet(manageButtonsStyle);
		connect(fourthButton, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		fourthLayout->addWidget(fourthLine, Qt::AlignLeft);
		fourthLayout->addWidget(fourthButton);

		rightCentralLayout->addLayout(firstLayout);
		rightCentralLayout->addLayout(secondLayout);
		rightCentralLayout->addLayout(thirdLayout);
		rightCentralLayout->addLayout(fourthLayout);
	}
}

void SettingsWindow::pickColor() {
	color = QColorDialog::getColor(lastColor, this, "Select a color");
	lastColor = color.isValid() ? color : lastColor;
	if (color.isValid()) {
		QPushButton* button = qobject_cast<QPushButton*>(sender());
		if (button == firstButton) colors::manageTracksButtons::backgroundColor = color.name();
		else if (button == secondButton) colors::manageTracksButtons::hoverColor = color.name();
		else if (button == thirdButton) colors::manageTracksButtons::pressedColor = color.name();

		else if (button == fourthButton) colors::playerButtons::backgroundColor = color.name();

		colors::generators::generateManageButtonsStyle();
		colors::generators::generatePlayerButtonsStyle();

		mainWindowInstance->updateStyles();
		updateStyles();
	}
}
void SettingsWindow::updateStyles() {
	if (firstButton) {
		firstButton->setStyleSheet(manageButtonsStyle);
		secondButton->setStyleSheet(manageButtonsStyle);
		thirdButton->setStyleSheet(manageButtonsStyle);
		fourthButton->setStyleSheet(manageButtonsStyle);
	}
}