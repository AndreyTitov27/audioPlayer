#pragma once
#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QMouseEvent>

class MainWindow;
class MusicButton;
class PlaylistButton : public QWidget {
public:
	PlaylistButton(const QString& text, const int& index, int& mainWindowCurrentPlaylist,
		MainWindow* mainWindowInstance, QWidget* parent = nullptr);
	QList<MusicButton*>* getList() { return list; }
	static PlaylistButton* lastPlaylistButton;
	int* getTrackNumber() { return trackNumber; }
	QString getTitle() { return title->text(); }

private:
	MainWindow* mainWindowInstance;
	QHBoxLayout* layout;
	QLabel* number;
	int* trackNumber;
	int numberInt;
	int& numberRef;
	QLabel* title;
	QList<MusicButton*>* list;

protected:
	void mousePressEvent(QMouseEvent* event) override;
};