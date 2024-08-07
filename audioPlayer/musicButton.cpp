#include "musicButton.hpp"

MusicButton::MusicButton(const QString& titleText, QWidget* parent) : QWidget(parent) {
	setFixedHeight(40);
	layout = new QVBoxLayout(this);
	title = new QLabel(this);
	title->setText(titleText);
	layout->addWidget(title);
	setLayout(layout);
	setStyleSheet("background-color: #4C4747;");
}