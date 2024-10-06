#include "styles.hpp"

QString colors::backgroundColor = "#1e1e1e";

QString colors::manageTracksButtons::backgroundColor = "#373333";
QString colors::manageTracksButtons::hoverColor = "#494242";
QString colors::manageTracksButtons::pressColor = "#433B3B";

QString colors::playerButtons::backgroundColor = "#373333";
QString colors::playerButtons::hoverColor = "#494242";
QString colors::playerButtons::pressColor = "#433B3B";

QString colors::musicButtons::defaultBackgroundColor = "#4C4747";
QString colors::musicButtons::defaultHoverColor = "#746C6C";
QString colors::musicButtons::selectedBackgroundColor = "#D20103";
QString colors::musicButtons::selectedHoverColor = "#FD0003";

QString colors::titlebar::backgroundColor = "#272222";
QString colors::titlebar::minMaxButtonsHoverColor = "#393333";
QString colors::titlebar::minMaxButtonsPressColor = "#2D2828";
QString colors::titlebar::closeButtonHoverColor = "#CB2626";
QString colors::titlebar::closeButtonPressColor = "#B92828";

QString backgroundColorStyle = "background-color: " + colors::backgroundColor + ";";

QString manageButtonsStyle = ""
"QPushButton {"
"background-color: " + colors::manageTracksButtons::backgroundColor + ";"
"color: #ecf0f1;"
"border-radius: 0px;"
"padding: 5px 10px;"
"}"
"QPushButton:hover {"
"background-color: " + colors::manageTracksButtons::hoverColor + ";"
"}"
"QPushButton:pressed {"
"background-color: " + colors::manageTracksButtons::pressColor + ";"
"padding: 4px 9px;"
"}";
QString playerButtonsStyle = ""
"QPushButton {"
"background-color: " + colors::playerButtons::backgroundColor + ";"
"color: #ecf0f1;"
"border-radius: 25px;"
"padding 5px 10px;"
"}"
"QPushButton:hover {"
"background-color: " + colors::playerButtons::hoverColor + ";"
"}"
"QPushButton:pressed {"
"background-color: " + colors::playerButtons::pressColor + ";"
"padding: 4px 9px;"
"}";
QString musicButtonStyle = ""
	"QWidget {"
		"background-color: " + colors::musicButtons::defaultBackgroundColor + ";"
		"color: #ecf0f1;"
	"}"
	"QWidget:hover {"
		"background-color: " + colors::musicButtons::defaultHoverColor + ";"
	"}"
	"QLabel {"
		"background-color: transparent;"
	"}";
QString musicButtonClickedStyle = ""
	"QWidget {"
		"background-color: " + colors::musicButtons::selectedBackgroundColor + ";"
		"color: #ecf0f1;"
	"}"
	"QWidget:hover {"
		"background-color: " + colors::musicButtons::selectedHoverColor + ";"
	"}"
	"QLabel {"
		"background-color: transparent;"
	"}";
QString musicCheckBoxStyle = ""
"QCheckBox {"
"background-color: transparent;"
"}";
QString playlistButtonStyle = ""
"QWidget {"
"background-color: #4C4747;"
"color: #ecf0f1;"
"}"
"QWidget:hover {"
"background-color: #746C6C;"
"}"
"QLabel {"
"background-color: transparent;"
"}";
QString playlistButtonClickedStyle = ""
"QWidget {"
"background-color: #D20103;"
"color: #ecf0f1;"
"}"
"QWidget:hover {"
"background-color: #FD0003;"
"}"
"QLabel {"
"background-color: transparent;"
"}";
QString scrollAreaStyle = R"(
	QScrollBar:vertical, QScrollBar:horizontal {
		background-color: transparent;
		border: none;
		width: 10px;
		height: 12px;
		margin: 0px;
		border-radius: 6px;
	}
	QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
		background-color: #655E5E;
		border-radius: 5px;
		min-height: 20px;
		min-width: 10px;
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
QString titleBarColorStyle = "background-color: " + colors::titlebar::backgroundColor + ";";
QString minMaxButtonsStyle = ""
    "QPushButton {"
        "background-color: " + colors::titlebar::backgroundColor + ";"
        "border-radius: 0px;"
    "}"
    "QPushButton:hover {"
        "background-color: " + colors::titlebar::minMaxButtonsHoverColor + ";"
    "}"
    "QPushButton:pressed {"
        "background-color: " + colors::titlebar::minMaxButtonsPressColor + ";"
    "}";
QString closeButtonStyle = ""
    "QPushButton {"
        "background-color: " + colors::titlebar::backgroundColor + ";"
        "border-radius: 0px;"
    "}"
    "QPushButton:hover {"
        "background-color: " + colors::titlebar::closeButtonHoverColor + ";"
    "}"
    "QPushButton:pressed {"
        "background-color: " + colors::titlebar::closeButtonPressColor + ";"
    "}";
void colors::generators::generateManageButtonsStyle() {
	manageButtonsStyle = ""
		"QPushButton {"
		"background-color: " + colors::manageTracksButtons::backgroundColor + ";"
		"color: #ecf0f1;"
		"border-radius: 0px;"
		"padding: 5px 10px;"
		"}"
		"QPushButton:hover {"
		"background-color: " + colors::manageTracksButtons::hoverColor + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + colors::manageTracksButtons::pressColor + ";"
		"padding: 4px 9px;"
		"}";
}
void colors::generators::generatePlayerButtonsStyle() {
	playerButtonsStyle = ""
		"QPushButton {"
		"background-color: " + colors::playerButtons::backgroundColor + ";"
		"color: #ecf0f1;"
		"border-radius: 25px;"
		"padding 5px 10px;"
		"}"
		"QPushButton:hover {"
		"background-color: " + colors::playerButtons::hoverColor + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + colors::playerButtons::pressColor + ";"
		"padding: 4px 9px;"
		"}";
}
void colors::generators::generateMusicButtonsStyle() {
	musicButtonStyle = ""
		"QWidget {"
		"background-color: " + colors::musicButtons::defaultBackgroundColor + ";"
		"color: #ecf0f1;"
		"}"
		"QWidget:hover {"
		"background-color: " + colors::musicButtons::defaultHoverColor + ";"
		"}"
		"QLabel {"
		"background-color: transparent;"
		"}";
	musicButtonClickedStyle = ""
		"QWidget {"
		"background-color: " + colors::musicButtons::selectedBackgroundColor + ";"
		"color: #ecf0f1;"
		"}"
		"QWidget:hover {"
		"background-color: " + colors::musicButtons::selectedHoverColor + ";"
		"}"
		"QLabel {"
		"background-color: transparent;"
		"}";
}
void colors::generators::generateTitleBarStyle() {
	titleBarColorStyle = "background-color: " + colors::titlebar::backgroundColor + ";";
	minMaxButtonsStyle = ""
		"QPushButton {"
		"background-color: " + colors::titlebar::backgroundColor + ";"
		"border-radius: 0px;"
		"}"
		"QPushButton:hover {"
		"background-color: " + colors::titlebar::minMaxButtonsHoverColor + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + colors::titlebar::minMaxButtonsPressColor + ";"
		"}";
	closeButtonStyle = ""
		"QPushButton {"
		"background-color: " + colors::titlebar::backgroundColor + ";"
		"border-radius: 0px;"
		"}"
		"QPushButton:hover {"
		"background-color: " + colors::titlebar::closeButtonHoverColor + ";"
		"}"
		"QPushButton:pressed {"
		"background-color: " + colors::titlebar::closeButtonPressColor + ";"
		"}";
}
