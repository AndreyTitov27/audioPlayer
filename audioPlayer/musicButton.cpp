#include "musicButton.hpp"

MusicButton* MusicButton::lastMusicButton = nullptr;
MusicButton::MusicButton(const QString titleText, const int& index, const QString track,
	QMediaPlayer* player, int& mainWindowCurrentTrack, MainWindow* mainWindowInstance, QWidget* parent)
	: QWidget(parent), trackPath{ track }, numberRef(mainWindowCurrentTrack),
	mainWindowInstance(mainWindowInstance) {
	setFixedHeight(40);
	this->player = player;
	layout = new QVBoxLayout(this);
	layoutH = new QHBoxLayout();
	number = new QLabel();
	title = new QLabel();
	title->setText(titleText);
	title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	number->setText(QString::number(index));
	numberInt = index;
	checkBox = new QCheckBox();
	checkBox->setText("");
	checkBox->setFixedSize(20, 20);
	checkBox->setStyleSheet(musicCheckBoxStyle);
	checkBox->setVisible(false);

	layoutH->addWidget(checkBox, Qt::AlignLeft);
	layoutH->addWidget(number, Qt::AlignLeft);
	layoutH->addWidget(title);
	layout->addLayout(layoutH);
	setLayout(layout);
	setStyleSheet(musicButtonStyle);

}
void MusicButton::setActive(bool active) {
	if (!this) return;

	bool isActive = active;
	setStyleSheet(isActive ? musicButtonClickedStyle : musicButtonStyle);
}
void MusicButton::setTrackNumber(int num) {
	numberInt = num;
	number->setText(QString::number(num));
}
void MusicButton::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		if (lastMusicButton != nullptr && lastMusicButton != this)
			lastMusicButton->setActive(false);
		numberRef = numberInt - 1;
		player->setSource(QUrl::fromLocalFile(trackPath));
		mainWindowInstance->getPlayPauseButton()->setIcon(QIcon("resources/icons/play.svg"));
		setStyleSheet(musicButtonClickedStyle);
		lastMusicButton = this;
	}
	qDebug() << trackPath;
	QWidget::mousePressEvent(event);
}
void MusicButton::mouseDoubleClickEvent(QMouseEvent* event) {
	if (event->buttons() == Qt::LeftButton) {
		if (lastMusicButton != nullptr && lastMusicButton != this)
			lastMusicButton->setActive(false);
		numberRef = numberInt - 1;
		player->setSource(QUrl::fromLocalFile(trackPath));
		player->play();
		mainWindowInstance->getPlayPauseButton()->setIcon(QIcon("resources/icons/pause.svg"));
		setStyleSheet(musicButtonClickedStyle);
		lastMusicButton = this;
	}
}