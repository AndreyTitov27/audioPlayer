#include "mainWindow.hpp"
#include <QtWidgets/QApplication>
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow mainWindow;
	return app.exec();
}