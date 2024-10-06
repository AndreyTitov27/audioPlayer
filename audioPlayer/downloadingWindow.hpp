#pragma once
#include "mainWindow.hpp"
#include "SearchWindow.h"
#include "SearchMusicTile.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtGui/qevent.h>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <fstream>
#include <filesystem>

class MainWindow;
class SearchWindow;
class SearchMusicTile;
class DownloadingWindow : public QMainWindow {
public:
	DownloadingWindow(MainWindow* mainWindowInstance, QMainWindow* parent = nullptr);

private:
	MainWindow* mainWindowInstance;
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout* searchButtonLayout;
	QPushButton* searchButton;
	QHBoxLayout* inputLayout;
	QHBoxLayout* inputButtonLayout;
	QLineEdit* input;
	QPushButton* inputButton;
	SearchWindow* searchWindow = nullptr;

private slots:
	void downloadTrackFromLink();
	void openSearchWindow();
};