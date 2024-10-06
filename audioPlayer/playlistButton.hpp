#pragma once
#include "mainWindow.hpp"
#include "musicButton.hpp"
#include "styles.hpp"
#include <QtWidgets/QCheckBox>
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
	void setActive(bool active);
	QString getTitle() { return title->text(); }
	int* getTrackNumber() const { return trackNumber; }
	int getPlaylistNumber() const { return numberInt; }
	void setPlaylistNumber(int num);
	bool isChecked() const { return checkBox->isChecked(); }
	void showCheckBox(bool show) { checkBox->setVisible(show); }
	void showMusicButtons();

private:
	MainWindow* mainWindowInstance;
	QHBoxLayout* layout;
	QLabel* number;
	int* trackNumber;
	int numberInt;
	int& numberRef;
	QLabel* title;
	QList<MusicButton*>* list;
	QCheckBox* checkBox;


protected:
	void mousePressEvent(QMouseEvent* event) override;
};