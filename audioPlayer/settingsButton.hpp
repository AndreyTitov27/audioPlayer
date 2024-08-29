#pragma once
#include "settingsWindow.hpp"
#include "styles.hpp"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QMouseEvent>

class SettingsWindow;
class SettingsButton : public QWidget {
public:
	SettingsButton(const QString& _text, SettingsWindow* settingsWindowInstance, QWidget* parent = nullptr);


private:
	SettingsWindow* settingsWindowInstance;
	QHBoxLayout* mainLayout;
	QLabel* text;

	void mousePressEvent(QMouseEvent* event) override;
};