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
	layout1 = nullptr;

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
	if (layout1 == nullptr) {
		layout1 = new QHBoxLayout();
		line1 = new QLabel("Select buttons background color:");
		line1->setAlignment(Qt::AlignLeft);
		button1 = new QPushButton("pick");
		button1->setStyleSheet(manageButtonsStyle);
		connect(button1, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout1->addWidget(line1, Qt::AlignLeft);
		layout1->addWidget(button1);

		layout2 = new QHBoxLayout();
		line2 = new QLabel("Select buttons hover color:");
		line2->setAlignment(Qt::AlignLeft);
		button2 = new QPushButton("pick");
		button2->setStyleSheet(manageButtonsStyle);
		connect(button2, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout2->addWidget(line2, Qt::AlignLeft);
		layout2->addWidget(button2);

		layout3 = new QHBoxLayout();
		line3 = new QLabel("Select buttons press color:");
		line3->setAlignment(Qt::AlignLeft);
		button3 = new QPushButton("pick");
		button3->setStyleSheet(manageButtonsStyle);
		connect(button3, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout3->addWidget(line3, Qt::AlignLeft);
		layout3->addWidget(button3);

		layout4 = new QHBoxLayout();
		line4 = new QLabel("Select music button default background color:");
		line4->setAlignment(Qt::AlignLeft);
		button4 = new QPushButton("pick");
		button4->setStyleSheet(manageButtonsStyle);
		connect(button4, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout4->addWidget(line4, Qt::AlignLeft);
		layout4->addWidget(button4);

		layout5 = new QHBoxLayout();
		line5 = new QLabel("Select music button default hover color:");
		button5 = new QPushButton("pick");
		button5->setStyleSheet(manageButtonsStyle);
		connect(button5, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout5->addWidget(line5, Qt::AlignLeft);
		layout5->addWidget(button5);

		layout6 = new QHBoxLayout();
		line6 = new QLabel("Select music button selected background color:");
		button6 = new QPushButton("pick");
		button6->setStyleSheet(manageButtonsStyle);
		connect(button6, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout6->addWidget(line6, Qt::AlignLeft);
		layout6->addWidget(button6);

		layout7 = new QHBoxLayout();
		line7 = new QLabel("Select music button selected hover color:");
		button7 = new QPushButton("pick");
		button7->setStyleSheet(manageButtonsStyle);
		connect(button7, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout7->addWidget(line7, Qt::AlignLeft);
		layout7->addWidget(button7);

		layout8 = new QHBoxLayout();
		line8 = new QLabel("Select title bar color:");
		button8 = new QPushButton("pick");
		button8->setStyleSheet(manageButtonsStyle);
		connect(button8, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout8->addWidget(line8, Qt::AlignLeft);
		layout8->addWidget(button8);

		layout9 = new QHBoxLayout();
		line9 = new QLabel("Select minimize/maximize button hover color:");
		button9 = new QPushButton("pick");
		button9->setStyleSheet(manageButtonsStyle);
		connect(button9, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout9->addWidget(line9, Qt::AlignLeft);
		layout9->addWidget(button9);

		layout10 = new QHBoxLayout();
		line10 = new QLabel("Select minimize/maximize button press color:");
		button10 = new QPushButton("pick");
		button10->setStyleSheet(manageButtonsStyle);
		connect(button10, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout10->addWidget(line10, Qt::AlignLeft);
		layout10->addWidget(button10);

		layout11 = new QHBoxLayout();
		line11 = new QLabel("Select close button hover color:");
		button11 = new QPushButton("pick");
		button11->setStyleSheet(manageButtonsStyle);
		connect(button11, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout11->addWidget(line11, Qt::AlignLeft);
		layout11->addWidget(button11);

		layout12 = new QHBoxLayout();
		line12 = new QLabel("Select close button press color:");
		button12 = new QPushButton("pick");
		button12->setStyleSheet(manageButtonsStyle);
		connect(button12, &QPushButton::clicked, this, &SettingsWindow::pickColor);
		layout12->addWidget(line12, Qt::AlignLeft);
		layout12->addWidget(button12);

		rightCentralLayout->addLayout(layout1);
		rightCentralLayout->addLayout(layout2);
		rightCentralLayout->addLayout(layout3);
		rightCentralLayout->addLayout(layout4);
		rightCentralLayout->addLayout(layout5);
		rightCentralLayout->addLayout(layout6);
		rightCentralLayout->addLayout(layout7);
		rightCentralLayout->addLayout(layout8);
		rightCentralLayout->addLayout(layout9);
		rightCentralLayout->addLayout(layout10);
		rightCentralLayout->addLayout(layout11);
		rightCentralLayout->addLayout(layout12);
	}
}

void SettingsWindow::pickColor() {
	color = QColorDialog::getColor(lastColor, this, "Select a color");
	lastColor = color.isValid() ? color : lastColor;
	if (color.isValid()) {
		QPushButton* button = qobject_cast<QPushButton*>(sender());
		if (button == button1) {
			colors::manageTracksButtons::backgroundColor = color.name();
			colors::playerButtons::backgroundColor = color.name();
		}
		else if (button == button2) {
			colors::manageTracksButtons::hoverColor = color.name();
			colors::playerButtons::hoverColor = color.name();
		}
		else if (button == button3) {
			colors::manageTracksButtons::pressColor = color.name();
			colors::playerButtons::pressColor = color.name();
		}
		else if (button == button4) colors::musicButtons::defaultBackgroundColor = color.name();
		else if (button == button5) colors::musicButtons::defaultHoverColor = color.name();
		else if (button == button6) colors::musicButtons::selectedBackgroundColor = color.name();
		else if (button == button7) colors::musicButtons::selectedHoverColor = color.name();
		else if (button == button8) colors::titlebar::backgroundColor = color.name();
		else if (button == button9) colors::titlebar::minMaxButtonsHoverColor = color.name();
		else if (button == button10) colors::titlebar::minMaxButtonsPressColor = color.name();
		else if (button == button11) colors::titlebar::closeButtonHoverColor = color.name();
		else if (button == button12) colors::titlebar::closeButtonPressColor = color.name();

		colors::generators::generateManageButtonsStyle();
		colors::generators::generatePlayerButtonsStyle();
		colors::generators::generateMusicButtonsStyle();
		colors::generators::generateTitleBarStyle();

		mainWindowInstance->updateStyles();
		updateStyles();
	}
}
void SettingsWindow::updateStyles() {
	if (button1) {
		button1->setStyleSheet(manageButtonsStyle);
		button2->setStyleSheet(manageButtonsStyle);
		button3->setStyleSheet(manageButtonsStyle);
		button4->setStyleSheet(manageButtonsStyle);
		button5->setStyleSheet(manageButtonsStyle);
		button6->setStyleSheet(manageButtonsStyle);
		button7->setStyleSheet(manageButtonsStyle);
		button8->setStyleSheet(manageButtonsStyle);
		button9->setStyleSheet(manageButtonsStyle);
		button10->setStyleSheet(manageButtonsStyle);
		button11->setStyleSheet(manageButtonsStyle);
		button12->setStyleSheet(manageButtonsStyle);
	}
}