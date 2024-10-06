#pragma once
#include "mainWindow.hpp"
#include "downloadingWindow.hpp"
#include "SearchMusicTile.h"
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QProgressBar>

class SearchMusicTile;
class SearchWindow : public QMainWindow {
public:
	SearchWindow(MainWindow* mainWindowInstanceSearch, QMainWindow* parentInstance, QMainWindow* parent = nullptr);
	void downloadTrackFromSearch(SearchMusicTile* tile);

private:
	QMainWindow* parentInstance;
	MainWindow* mainWindowInstanceSearch;
	QProgressDialog* progressDialog;
	QList<SearchMusicTile*>* tilesList;
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout* searchLayout;
	QLineEdit* input;
	QPushButton* inputButton;
	QWidget* scrollAreaWidget;
	QScrollArea* scrollArea;
	QVBoxLayout* scrollAreaLayout;

private slots:
	void search();

protected:
	void closeEvent(QCloseEvent* event) override;

};

