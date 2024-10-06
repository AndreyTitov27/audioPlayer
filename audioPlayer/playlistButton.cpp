#include "playlistButton.hpp"

PlaylistButton* PlaylistButton::lastPlaylistButton = nullptr;
PlaylistButton::PlaylistButton(const QString& text, const int& index, int& mainWindowCurrentPlaylist, MainWindow* mainWindowInstance, QWidget* parent)
	: QWidget(parent), mainWindowInstance(mainWindowInstance), numberInt(index), numberRef(mainWindowCurrentPlaylist) {
	setFixedHeight(40);
	layout = new QHBoxLayout(this);
	number = new QLabel(QString::number(index));
	title = new QLabel(text);
	list = new QList<MusicButton*>();
	trackNumber = new int(-1);

	number->setFixedWidth(8);
	number->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	title->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	checkBox = new QCheckBox();
	checkBox->setText("");
	checkBox->setFixedSize(20, 20);
	checkBox->setStyleSheet(musicCheckBoxStyle);
	checkBox->setVisible(false);

	layout->addWidget(checkBox, Qt::AlignLeft);
	layout->addWidget(number);
	layout->addWidget(title);

	setLayout(layout);
	setStyleSheet(playlistButtonStyle);
}
void PlaylistButton::setActive(bool active) {
	if (!this) return;

		bool isActive = active;
		setStyleSheet(isActive ? playlistButtonClickedStyle : playlistButtonStyle);
}
void PlaylistButton::setPlaylistNumber(int num) {
	numberInt = num;
	number->setText(QString::number(num));
}
void PlaylistButton::showMusicButtons() {
	if (lastPlaylistButton != nullptr || lastPlaylistButton != this) lastPlaylistButton->setActive(false);
	if (mainWindowInstance->removeTracksSelectionMode) {
		mainWindowInstance->removeTracksSelectionMode = false;
		for (MusicButton* button : *lastPlaylistButton->getList()) {
			button->showCheckBox(false);
		}
	}
	setActive(true);
	for (int i = 0; i < mainWindowInstance->getPlaylistList()->at(numberRef)->list->size(); i++) {
		mainWindowInstance->getPlaylistList()->at(numberRef)->list->at(i)->setVisible(false);
	}
	numberRef = numberInt - 1;
	for (MusicButton* button : *list) {
		button->setVisible(true);
	}
	lastPlaylistButton = this;
}
void PlaylistButton::mousePressEvent(QMouseEvent* event) {
	showMusicButtons();
	QWidget::mousePressEvent(event);
}