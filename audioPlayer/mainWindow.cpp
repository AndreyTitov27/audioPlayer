#include "mainWindow.hpp"
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <iostream>

void MainWindow::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		QRect windowRect = rect();
		if (titleBar->geometry().contains(event->pos())) {
			dragging = true;
			dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
			event->accept();
		}
		else if (event->pos().x() >= windowRect.width() - resizeMargin &&
			event->pos().y() >= windowRect.height() - resizeMargin) {
			resizing = true;
			dragPosition = event->globalPosition().toPoint();
			resizeDirection = ResizeBottomRight;
			event->accept();
		}
		else if (event->pos().x() <= resizeMargin &&
			event->pos().y() <= resizeMargin) {
			resizing = true;
			dragPosition = event->globalPosition().toPoint();
			resizeDirection = ResizeTopLeft;
			event->accept();
		}
		else if (event->pos().x() <= resizeMargin &&
			event->pos().y() >= windowRect.height() - resizeMargin) {
			resizing = true;
			dragPosition = event->globalPosition().toPoint();
			resizeDirection = ResizeBottomLeft;
			event->accept();
		}
		else if (event->pos().x() >= windowRect.width() - resizeMargin &&
			event->pos().y() <= resizeMargin) {
			resizing = true;
			dragPosition = event->globalPosition().toPoint();
			resizeDirection = ResizeTopRight;
			event->accept();
		}
		else {
			resizeDirection = NoResize;
		}
	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		dragging = false;
		resizing = false;
		setCursor(Qt::ArrowCursor);
	}
}
void MainWindow::mouseMoveEvent(QMouseEvent* event) {
	if (dragging && !isMaximized()) {
		move(event->globalPosition().toPoint() - dragPosition);
		event->accept();
	}
	else if (resizing) {
		QPoint offset = event->globalPosition().toPoint() - dragPosition;
		QSize newSize = size();
		QPoint newTopLeft = pos();

		switch (resizeDirection) {
		case ResizeBottomRight:
			newSize += QSize(offset.x(), offset.y());
			break;
		case ResizeTopLeft:
			newSize -= QSize(offset.x(), offset.y());
			newTopLeft = pos() + offset;
			break;
		case ResizeTopRight:
			newSize += QSize(offset.x(), -offset.y());
			newTopLeft.setY(pos().y() + offset.y());
			break;
		case ResizeBottomLeft:
			newSize += QSize(-offset.x(), offset.y());
			newTopLeft.setX(pos().x() + offset.x());
			break;
		default:
			break;
		}

		resize(newSize);
		move(newTopLeft);
		dragPosition = event->globalPosition().toPoint();
		event->accept();
	}
	else {
		updateCursorShape(event->pos());
	}
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton && titleBar->geometry().contains(event->pos())) {
		maximize();
	}
}
void MainWindow::resizeEvent(QResizeEvent* event) {
	QMainWindow::resizeEvent(event);
}
void MainWindow::changeEvent(QEvent* event) {
	if (event->type() == QEvent::WindowStateChange) {
		if (isMaximized()) {
			qDebug() << "Maximized";
		}
		else if (isMinimized()) {
			qDebug() << "Minimized";
		}
		else {
			qDebug() << "Restored";
			if (lastState != Qt::WindowNoState) {
				animateRestore();
			}
		}
		lastState = windowState();
	}
	QWidget::changeEvent(event);
}

void MainWindow::updateCursorShape(const QPoint& pos) {
	QRect windowRect = rect();
	if (pos.x() <= resizeMargin && pos.y() <= resizeMargin) {
		setCursor(Qt::SizeFDiagCursor);
	}
	else if (pos.x() >= windowRect.width() - resizeMargin && pos.y() <= resizeMargin) {
		setCursor(Qt::SizeBDiagCursor);
	}
	else if (pos.x() <= resizeMargin && pos.y() >= windowRect.height() - resizeMargin) {
		setCursor(Qt::SizeBDiagCursor);
	}
	else if (pos.x() >= windowRect.width() - resizeMargin && pos.y() >= windowRect.y() - resizeMargin) {
		setCursor(Qt::SizeFDiagCursor);
	}
	else if (pos.x() <= resizeMargin) {
		setCursor(Qt::SizeHorCursor);
	}
	else if (pos.x() >= windowRect.width() - resizeMargin) {
		setCursor(Qt::SizeHorCursor);
	}
	else if (pos.y() <= resizeMargin) {
		setCursor(Qt::SizeVerCursor);
	}
	else if (pos.y() >= windowRect.height() - resizeMargin) {
		setCursor(Qt::SizeVerCursor);
	}
	else {
		setCursor(Qt::ArrowCursor);
	}
}
void MainWindow::minimize() {
	animateMinimize();
}
void MainWindow::maximize() {
	if (isMaximized()) {
		animateRestore();
	}
	else {
		animateMaximize();
	}
}

void MainWindow::animateMinimize() {
	if (windowOpacity() != 0.0) {
		if (isMaximized()) {
			minimizedFromMaximized = true;
		}
		showNormal();
		animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(300);
		animation->setStartValue(1.0);
		animation->setEndValue(0.0);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		connect(animation, &QPropertyAnimation::finished, this, &MainWindow::showMinimized);
		//QTimer::singleShot(300, this, &MainWindow::showMinimized);
	}
}
void MainWindow::animateMaximize() {
	if (windowState() != Qt::WindowMaximized) {

		lastRect = geometry();
		animation = new QPropertyAnimation(this, "geometry");
		animation->setDuration(300);
		animation->setStartValue(geometry());
		QRect screenRect = QApplication::primaryScreen()->availableGeometry();
		animation->setEndValue(screenRect);
		animation->setEasingCurve(QEasingCurve::InOutQuad);
		animation->start(QAbstractAnimation::DeleteWhenStopped);
	}

	connect(animation, &QPropertyAnimation::finished, this, &MainWindow::showMaximized);
	//QTimer::singleShot(300, this, &MainWindow::showMaximized);
}
void MainWindow::animateRestore() {
	if (windowOpacity() == 0.0) {
		if (minimizedFromMaximized) {
			showMaximized();
			minimizedFromMaximized = false;
		}
		else {
			showNormal();
		}
		animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(300);
		animation->setStartValue(0.0);
		animation->setEndValue(1.0);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		/*if (minimizedFromMaximized) {
			connect(animation, &QPropertyAnimation::finished, this, &MainWindow::showMaximized);
		}
		else {
			connect(animation, &QPropertyAnimation::finished, this, &MainWindow::showNormal);
		}*/
		//QTimer::singleShot(300, this, &QWidget::showNormal);
	}
	else {
		animation = new QPropertyAnimation(this, "geometry");
		animation->setDuration(300);
		animation->setStartValue(geometry());
		animation->setEndValue(lastRect);
		animation->setEasingCurve(QEasingCurve::InOutQuad);
		animation->start(QAbstractAnimation::DeleteWhenStopped);

		connect(animation, &QPropertyAnimation::finished, this, &MainWindow::showNormal);
		//QTimer::singleShot(300, this, &QWidget::showNormal);
	}
}
void MainWindow::animateClose() {
	animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(300);
	animation->setStartValue(1.0);
	animation->setEndValue(0.0);
	animation->start(QAbstractAnimation::DeleteWhenStopped);

	QTimer::singleShot(300, this, &QApplication::quit);
}

MainWindow::MainWindow() {
	dragging = false;
	resizing = false;
	resizeMargin = 10;
	resizeDirection = NoResize;
	minimizedFromMaximized = false;

	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	centralWidget->setStyleSheet(
		"border-radius: 15px;"
		"background-color: #262121;"
	);
	

	centralWidget->setLayout(mainLayout);

	titleBar = new QWidget(this);
	titleBar->setStyleSheet(
		"border-top-left-radius: 10px;"
		"border-top-right-radius: 10px;"
		"border-bottom-left-radius: 0px;"
		"border-bottom-right-radius: 0px;"
		"background-color: #373333;"
		"color: #FDFAFA;"
	);
	titleBar->setFixedHeight(35);

	titleLayout = new QHBoxLayout(titleBar);
	titleLayout->setContentsMargins(0, 0, 0, 0);
	titleLayout->setSpacing(0);

	minimizeButton = new QPushButton(QString::fromUtf8(u8"\u2014"), this);
	QFont minimizeButtonFont = minimizeButton->font();
	minimizeButtonFont.setPointSize(10);
	minimizeButton->setFont(minimizeButtonFont);
	maximizeButton = new QPushButton(QString::fromUtf8(u8"\u2610"), this);
	QFont maximizeButtonFont = maximizeButton->font();
	maximizeButtonFont.setPointSize(10);
	maximizeButton->setFont(maximizeButtonFont);
	closeButton = new QPushButton(QString::fromUtf8(u8"\u2A09"), this);
	QFont closeButtonFont = closeButton->font();
	closeButtonFont.setPointSize(10);
	closeButton->setFont(closeButtonFont);

	minimizeButton->setFixedSize(45, 35);
	minimizeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 0px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #433B3B;"
		"    padding: 4px 9px;"
		"}"
	);
	maximizeButton->setFixedSize(45, 35);
	maximizeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 0px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #433B3B;"
		"    padding: 4px 9px;"
		"}"
	);
	closeButton->setFixedSize(45, 35);
	closeButton->setStyleSheet(
		"QPushButton {"
		"    background-color: #373333;"
		"    color: #ecf0f1;"
		"    border-radius: 0px;"
		"    border-top-right-radius: 10px;"
		"    padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"    background-color: #494242;"
		"}"
		"QPushButton:pressed {"
		"    background-color: #C11314;"
		"    padding: 4px 9px;"
		"}"
	);

	titleLayout->addWidget(minimizeButton);
	titleLayout->addWidget(maximizeButton);
	titleLayout->addWidget(closeButton);
	titleLayout->setAlignment(Qt::AlignRight);
	
	titleBar->setLayout(titleLayout);

	mainLayout->addWidget(titleBar);

	contentWidget = new QWidget(this);

	mainLayout->addWidget(contentWidget);

	setCentralWidget(centralWidget);

	connect(minimizeButton, &QPushButton::clicked, this, &MainWindow::minimize);
	connect(maximizeButton, &QPushButton::clicked, this, &MainWindow::maximize);
	connect(closeButton, &QPushButton::clicked, this, &MainWindow::animateClose);
	resize(600, 400);
	setMinimumSize(400, 300);
	show();
}