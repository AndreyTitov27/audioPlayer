#ifndef MUSIC_BUTTON_HPP
#define MUSIC_BUTTON_HPP
#pragma once
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtGui/qevent.h>
#include <QtMultimedia/QMediaPlayer>
class MusicButton : public QWidget {
public:
	MusicButton(const QString titleText, const int& index, const QString track, QMediaPlayer* player, int& mainWindowCurrentTrack, QWidget* parent = nullptr);
	QString getTrackPath() {
		return trackPath;
	}
	void setActive(bool active);
private:
	static MusicButton* lastMusicButton;
	bool isActive;
	QMediaPlayer* player;
	QString trackPath;
	QLabel* title;
	QLabel* number;
	int numberInt;
	int& numberRef;
	QVBoxLayout* layout;
	QHBoxLayout* layoutH;

private slots:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
};
#endif // !MUSIC_BUTTON_HPP
