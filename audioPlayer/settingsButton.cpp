#include "settingsButton.hpp"

SettingsButton::SettingsButton(const QString& _text, SettingsWindow* settingsWindowInstance, QWidget* parent)
	: QWidget(parent), settingsWindowInstance(settingsWindowInstance) {
	mainLayout = new QHBoxLayout(this);
	text = new QLabel(_text);
	
	mainLayout->addWidget(text);
	text->setAlignment(Qt::AlignLeft);
	setStyleSheet(manageButtonsStyle);
}

void SettingsButton::mousePressEvent(QMouseEvent* event) {

	settingsWindowInstance->showCustomizeOptions();

	QWidget::mousePressEvent(event);
}