#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMenuBar>

//class QWidget;
class MainWindow : public QMainWindow {
private:
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QWidget* titleBar;
	QHBoxLayout* titleLayout;
	QPushButton* minimizeButton;
	QPushButton* maximizeButton;
	QPushButton* closeButton;
	QWidget* contentWidget;

public:
	MainWindow();
private slots:
	void minimize();
	void maximize();
};
#endif // !MAIN_WINDOW_HPP
