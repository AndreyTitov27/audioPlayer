#ifndef STYLES_HPP
#define STYLES_HPP
#include <QtCore/QString>

const QString manageButtonsStyle = R"(
	QPushButton {
		background-color: #373333;
		color: #ecf0f1;
		border-radius: 0px;
		padding: 5px 10px;
	}
	QPushButton:hover {
		background-color: #494242;
	}
	QPushButton:pressed {
		background-color: #433B3B;
		padding: 4px 9px;
	}
)";
const QString playerButtonsStyle = R"(
	QPushButton {
		background-color: #373333;
		color: #ecf0f1;
		border-radius: 25px;
		padding 5px 10px;
	}
	QPushButton:hover {
		background-color: #494242;
	}
	QPushButton:pressed {
		background-color: #433B3B;
		padding: 4px 9px;
	}
)";
const QString musicButtonStyle = R"(
	QWidget {
		background-color: #4C4747;
		color: #ecf0f1;
	}
	QWidget:hover {
		background-color: #746C6C;
	}
	QLabel {
		background-color: transparent;
	}
)";
const QString musicButtonClickedStyle = R"(
	QWidget {
		background-color: #D20103;
		color: #ecf0f1;
	}
	QWidget:hover {
		background-color: #FD0003;
	}
	QLabel {
		background-color: transparent;
	}
)";
const QString scrollAreaStyle = R"(
	QScrollBar:vertical, QScrollBar:horizontal {
		background-color: transparent;
		border: none;
		width: 12px;
		height: 12px;
		margin: 0px;
		border-radius: 6px;
	}
	QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
		background-color: #655E5E;
		border-radius: 6px;
		min-height: 20px;
		min-width: 12px;
	}
	QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover {
		background-color: #817B7B;
	}
	QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
	QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
		background: none;
		border: 0;
	}
	QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical,
	QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {
		background: none;
		border: 0;
	}
	QScrollBar::add-page:vertical {
		background: #403939;
		border-top-left-radius: 0;
		border-top-right-radius: 0;
		border-bottom-left-radius: 6px;
		border-bottom-right-radius: 6px;
	}
	QScrollBar::sub-page:vertical {
		background: #403939;
		border-bottom-left-radius: 0;
		border-bottom-right-radius: 0;
		border-top-left-radius: 6px;
		border-top-right-radius: 6px;
	}
	QScrollBar::add-page:horizontal {
		background: #403939;
		border-top-left-radius: 0;
		border-top-right-radius: 6px;
		border-bottom-left-radius: 0;
		border-bottom-right-radius: 6px;
	}
	QScrollBar::sub-page:horizontal {
		background: #403939;
		border-top-left-radius: 6px;
		border-top-right-radius: ;
		border-bottom-left-radius: 6px;
		border-bottom-right-radius: 0;
	}
)";
#endif // !STYLES_HPP
