#pragma once
#include <QtCore/QString>

namespace colors {
	extern QString backgroundColor;
	namespace manageTracksButtons {
		extern QString backgroundColor;
		extern QString hoverColor;
		extern QString pressColor;
	}
	namespace playerButtons {
		extern QString backgroundColor;
		extern QString hoverColor;
		extern QString pressColor;
	}
	namespace musicButtons {
		extern QString defaultBackgroundColor;
		extern QString defaultHoverColor;
		extern QString selectedBackgroundColor;
		extern QString selectedHoverColor;
	}
	namespace titlebar {
		extern QString backgroundColor;
		extern QString minMaxButtonsHoverColor;
		extern QString minMaxButtonsPressColor;
		extern QString closeButtonHoverColor;
		extern QString closeButtonPressColor;
	}
	namespace generators {
		extern void generateManageButtonsStyle();
		extern void generatePlayerButtonsStyle();
		extern void generateMusicButtonsStyle();
		extern void generateTitleBarStyle();
	}
}
extern QString backgroundColorStyle;
extern QString manageButtonsStyle;
extern QString playerButtonsStyle;
extern QString musicButtonStyle;
extern QString musicButtonClickedStyle;
extern QString musicCheckBoxStyle;
extern QString playlistButtonStyle;
extern QString playlistButtonClickedStyle;
extern QString scrollAreaStyle;
extern QString titleBarColorStyle;
extern QString minMaxButtonsStyle;
extern QString closeButtonStyle;
