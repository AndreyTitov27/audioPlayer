#pragma once
#include <QtCore/QString>

namespace colors {
	namespace manageTracksButtons {
		extern QString backgroundColor;
		extern QString hoverColor;
		extern QString pressedColor;
	}
	namespace playerButtons {
		extern QString backgroundColor;
		extern QString hoverColor;
		extern QString pressColor;
	}
	namespace generators {
		extern void generateManageButtonsStyle();
		extern void generatePlayerButtonsStyle();
	}
}
extern QString manageButtonsStyle;
extern QString playerButtonsStyle;
extern QString musicButtonStyle;
extern QString musicButtonClickedStyle;
extern QString musicCheckBoxStyle;
extern QString scrollAreaStyle;
