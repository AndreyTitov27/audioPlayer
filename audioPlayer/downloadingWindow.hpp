#pragma once
#include "mainWindow.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>
#include <QtConcurrent/QtConcurrent>
#include <fstream>
#include <filesystem>

class MainWindow;
class DownloadingWindow : public QMainWindow {
public:
	DownloadingWindow(MainWindow* mainWindowInstance, QMainWindow* parent = nullptr);

private:
	MainWindow* mainWindowInstance;
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QHBoxLayout* inputLayout;
	QHBoxLayout* inputButtonLayout;
	QLineEdit* input;
	QPushButton* inputButton;

private slots:
	void downloadTrack();
};