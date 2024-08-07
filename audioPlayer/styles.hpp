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
#endif // !STYLES_HPP
