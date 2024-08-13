#include "musicButton.hpp"
#include "mainWindow.hpp"
#include "styles.hpp"

MusicButton::MusicButton(const QString titleText, const int& index, const QString track, QMediaPlayer* player, int& mainWindowCurrentTrack, QWidget* parent) : QWidget(parent), trackPath{track}, numberRef(mainWindowCurrentTrack), isActive(false) {
	setFixedHeight(40);
	this->player = player;
	layout = new QVBoxLayout(this);
	layoutH = new QHBoxLayout();
	title = new QLabel();
	number = new QLabel();
	title->setText(titleText);
	title->setAlignment(Qt::AlignRight);
	number->setText(QString::number(index));
	numberInt = index;
	layoutH->addWidget(number);
	layoutH->addWidget(title);
	layout->addLayout(layoutH);
	setLayout(layout);
	setStyleSheet(musicButtonStyle);

}
void MusicButton::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		numberRef = numberInt;
		isActive = true;
		player->setSource(trackPath);
		setStyleSheet(musicButtonClickedStyle);
	}
	QWidget::mousePressEvent(event);
}
void MusicButton::mouseDoubleClickEvent(QMouseEvent* event) {
	if (event->buttons() == Qt::LeftButton) {
		numberRef = numberInt;
		player->setSource(trackPath);
		player->play();
		setStyleSheet(musicButtonClickedStyle);
	}
}