#include "mainWindow.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow mainWindow;
	QWidget* non_clickable = new QWidget(&mainWindow);
	non_clickable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	non_clickable->setProperty("clickable widget", false);
	mainWindow.getCustomTitlebarLayout().addWidget(non_clickable);

	auto pal = mainWindow.getTitlebarWidget().palette();
	pal.setColor(QPalette::Window, QColor("#272222"));
	mainWindow.getTitlebarWidget().setAutoFillBackground(true);
	mainWindow.getTitlebarWidget().setPalette(pal);

	return app.exec();
}
/*TODO
��� ����������� ������� ���������� ������, ���� �� ��������� � ����
����� ������ ������, ������ ������� � ������ �����
*/