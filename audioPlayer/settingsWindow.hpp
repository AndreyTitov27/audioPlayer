#pragma once
#include "mainWindow.hpp"
#include "settingsButton.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QColorDialog>

class MainWindow;
class SettingsButton;
class SettingsWindow : public QMainWindow {
public:
	SettingsWindow(MainWindow* mainWindowInstance, QMainWindow* parent = nullptr);
	void showCustomizeOptions();

private:
	MainWindow* mainWindowInstance;
	QWidget* centralWidget;
	QHBoxLayout* mainLayout;
	QVBoxLayout* leftLayout;
	//
	SettingsButton* customizeButton;
	//
	QVBoxLayout* rightLayout;
	QWidget* rightCentralWidget;
	QVBoxLayout* rightCentralLayout;
	//
	QHBoxLayout* layout1;
	QLabel* line1;
	QPushButton* button1;

	QHBoxLayout* layout2;
	QLabel* line2;
	QPushButton* button2;

	QHBoxLayout* layout3;
	QLabel* line3;
	QPushButton* button3;

	QHBoxLayout* layout4;
	QLabel* line4;
	QPushButton* button4;

	QHBoxLayout* layout5;
	QLabel* line5;
	QPushButton* button5;

	QHBoxLayout* layout6;
	QLabel* line6;
	QPushButton* button6;

	QHBoxLayout* layout7;
	QLabel* line7;
	QPushButton* button7;

	QHBoxLayout* layout8;
	QLabel* line8;
	QPushButton* button8;

	QHBoxLayout* layout9;
	QLabel* line9;
	QPushButton* button9;

	QHBoxLayout* layout10;
	QLabel* line10;
	QPushButton* button10;

	QHBoxLayout* layout11;
	QLabel* line11;
	QPushButton* button11;

	QHBoxLayout* layout12;
	QLabel* line12;
	QPushButton* button12;
	//
	QColor color;
	QColor lastColor;

	void updateStyles();

private slots:
	void pickColor();
};
