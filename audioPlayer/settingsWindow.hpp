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
	QHBoxLayout* firstLayout;
	QLabel* firstLine;
	QPushButton* firstButton;

	QHBoxLayout* secondLayout;
	QLabel* secondLine;
	QPushButton* secondButton;

	QHBoxLayout* thirdLayout;
	QLabel* thirdLine;
	QPushButton* thirdButton;

	QHBoxLayout* fourthLayout;
	QLabel* fourthLine;
	QPushButton* fourthButton;

	QHBoxLayout* fifthLayout;
	QLabel* fifthLine;
	QPushButton* fifthButton;

	QHBoxLayout* sixthLayout;
	QLabel* sixthLine;
	QPushButton* sixthButton;
	//
	QColor color;
	QColor lastColor;

	void updateStyles();

private slots:
	void pickColor();
};
