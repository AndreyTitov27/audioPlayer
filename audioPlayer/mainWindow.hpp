#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QSequentialAnimationGroup>
#include <QtGui/qevent.h>
#include <QtWidgets/QMenuBar>

class MainWindow : public QMainWindow {
private:
	void updateCursorShape(const QPoint& pos);
	void animateMinimize();
	void animateMaximize();
	void animateClose();
	void animateRestore();

	bool dragging;
	bool resizing;
	int resizeMargin;
	QRect lastRect;
	QRect resizeRect;
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QWidget* titleBar;
	QHBoxLayout* titleLayout;
	QPushButton* minimizeButton;
	QPushButton* maximizeButton;
	QPushButton* closeButton;
	QWidget* contentWidget;
	QPoint dragPosition;
	QPropertyAnimation* animation;
	QSequentialAnimationGroup* animationGroup;

	Qt::WindowStates lastState = Qt::WindowNoState;
	bool minimizedFromMaximized;
	
	enum resizeDirection {
		NoResize,
		ResizeTopLeft,
		ResizeTop,
		ResizeTopRight,
		ResizeRight,
		ResizeBottomRight,
		ResizeBottom,
		ResizeBottomLeft,
		ResizeLeft
	};
	resizeDirection resizeDirection;

public:
	MainWindow();
protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void changeEvent(QEvent* event) override;
private slots:
	void minimize();
	void maximize();
};
#endif // !MAIN_WINDOW_HPP
