#pragma once
#include "mainWindow.hpp"
#include "styles.hpp"
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtGui/QMouseEvent>
#include <QtGui/QDrag>
#include <QtWidgets/QScrollBar>

class MainWindow;
class MusicButton : public QWidget {
public:
	MusicButton(const QString titleText, const int& index, const QString track, QMediaPlayer* player,
		int& mainWindowCurrentTrack, MainWindow* mainWindowInstance, QWidget* parent = nullptr);
	QString getTrackPath() {
		return trackPath;
	}
	static MusicButton* lastMusicButton;
	void setActive(bool active);
	int getTrackNumber() { return numberInt; }
	void setTrackNumber(int num);

	bool isChecked() const { return checkBox->isChecked(); }
	void showCheckBox(bool show) { checkBox->setVisible(show); }
private:
	MainWindow* mainWindowInstance;
	QMediaPlayer* player;
	QString trackPath;
	QVBoxLayout* layout;
	QHBoxLayout* layoutH;
	QLabel* title;
	QLabel* number;
	QCheckBox* checkBox;
	int numberInt;
	int& numberRef;
	QPoint dragStartPosition;
	QPoint initialCursorPosition;
	QPoint localCursorPos;

private slots:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dragMoveEvent(QDragMoveEvent* event) override;
	void dropEvent(QDropEvent* event) override;
};
