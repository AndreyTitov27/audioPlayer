#include "mainWindow.hpp"

void MainWindow::initializeTitlebar() {
    // Set window shadows.
    const MARGINS aero_shadow_on = { 1, 1, 1, 1 };
    ::DwmExtendFrameIntoClientArea(m_hwnd, &aero_shadow_on);

    connect(windowHandle(), &QWindow::screenChanged, this, &MainWindow::onScreenChanged);

    // Add widget. (Initialize central widget)
    entireWidget = new QWidget(this);
    setCentralWidget(entireWidget);

    // Layout for entire widgets.
    entireLayout = new QVBoxLayout();
    entireWidget->setLayout(entireLayout);
    entireLayout->setContentsMargins(0, 0, 0, 0);

    // Initialize title bar widget
    m_titlebar_widget = new QWidget();
    entireLayout->addWidget(m_titlebar_widget);
    m_titlebar_widget->setFixedHeight(35); // Default title bar height is 35
    m_titlebar_widget->setContentsMargins(0, 0, 0, 0);
    m_titlebar_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Layout for title bar
    QHBoxLayout* titlebar_layout = new QHBoxLayout();
    m_titlebar_widget->setLayout(titlebar_layout);
    titlebar_layout->setContentsMargins(0, 0, 0, 0);
    titlebar_layout->setSpacing(0);

    QWidget* custom_titlebar_widget = new QWidget();
    titlebar_layout->addWidget(custom_titlebar_widget);
    custom_titlebar_widget->setContentsMargins(0, 0, 0, 0);
    custom_titlebar_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Minimize button setup.
    m_minimize_btn = new QPushButton(QIcon("resources/icons/minimize.svg"), "", this);
    m_minimize_btn->setIconSize(QSize(20, 20));
    titlebar_layout->addWidget(m_minimize_btn);
    m_minimize_btn->setFixedWidth(46);
    m_minimize_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_minimize_btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_minimize_btn->setStyleSheet(minMaxButtonsStyle);

    // Maximize button setup.
    m_maximize_btn = new QPushButton(QIcon("resources/icons/maximize.svg"), "", this);
    m_maximize_btn->setIconSize(QSize(16, 16));
    titlebar_layout->addWidget(m_maximize_btn);
    m_maximize_btn->setFixedWidth(46);
    m_maximize_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    //m_maximize_btn->setCheckable(true);
    m_maximize_btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_maximize_btn->setStyleSheet(minMaxButtonsStyle);

    // Close button setup.
    m_close_btn = new QPushButton(QIcon("resources/icons/close.svg"), "", this);
    m_close_btn->setIconSize(QSize(20, 20));
    titlebar_layout->addWidget(m_close_btn);
    m_close_btn->setFixedWidth(46);
    m_close_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_close_btn->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    m_close_btn->setStyleSheet(closeButtonStyle);

    // Layout for title bar customization.
    m_custom_titlebar_layout = new QHBoxLayout(custom_titlebar_widget);
    custom_titlebar_widget->setLayout(m_custom_titlebar_layout);
    m_custom_titlebar_layout->setContentsMargins(0, 0, 0, 0);
    m_custom_titlebar_layout->setSpacing(0);
    m_custom_titlebar_layout->setAlignment(Qt::AlignLeft);

    QObject::connect(m_minimize_btn, &QPushButton::clicked, this, &MainWindow::onMinimizeButtonClicked);
    QObject::connect(m_maximize_btn, &QPushButton::clicked, this, &MainWindow::onMaximizeButtonClicked);
    QObject::connect(m_close_btn, &QPushButton::clicked, this, &MainWindow::onCloseButtonClicked);

    entireLayout->setAlignment(titlebar_layout, Qt::AlignTop);

    // Set default title bar color.
    m_titlebar_widget->setStyleSheet(titleBarColorStyle);
}

bool MainWindow::nativeEvent(const QByteArray& event_type, void* message, qintptr* result) {
    MSG* msg = (MSG*)message;

    if (msg->message == WM_NCCALCSIZE) {
        // Remove the default window frame by hooking the WM_NCCALCSIZE message.
        if (msg->lParam) {
            WINDOWPLACEMENT wp;
            GetWindowPlacement(m_hwnd, &wp);

            if (wp.showCmd == SW_MAXIMIZE) {
                NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)msg->lParam;
                sz->rgrc[0].left += 8;
                sz->rgrc[0].top += 8;
                sz->rgrc[0].right -= 8;
                sz->rgrc[0].bottom -= 8;
            }
        }
        return true;
    }
    else if (msg->message == WM_NCHITTEST) {
        // Process the mouse when it is on the window border.
        RECT winrect;
        GetWindowRect(msg->hwnd, &winrect);
        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);
        long local_x = x - winrect.left;
        long local_y = y - winrect.top;

        if (x >= winrect.left && x < winrect.left + m_resize_border_width &&
            y < winrect.bottom && y >= winrect.bottom - m_resize_border_width) {
            *result = HTBOTTOMLEFT;
            return true;
        }
        else if (x < winrect.right && x >= winrect.right - m_resize_border_width &&
            y < winrect.bottom && y >= winrect.bottom - m_resize_border_width) {
            *result = HTBOTTOMRIGHT;
            return true;
        }
        else if (x >= winrect.left && x < winrect.left + m_resize_border_width &&
            y >= winrect.top && y < winrect.top + m_resize_border_width) {
            *result = HTTOPLEFT;
            return true;
        }
        else if (x < winrect.right && x >= winrect.right - m_resize_border_width &&
            y >= winrect.top && y < winrect.top + m_resize_border_width) {
            *result = HTTOPRIGHT;
            return true;
        }
        else if (x >= winrect.left && x < winrect.left + m_resize_border_width) {
            *result = HTLEFT;
            return true;
        }
        else if (x < winrect.right && x >= winrect.right - m_resize_border_width) {
            *result = HTRIGHT;
            return true;
        }
        else if (y < winrect.bottom && y >= winrect.bottom - m_resize_border_width) {
            *result = HTBOTTOM;
            return true;
        }
        else if (y >= winrect.top && y < winrect.top + m_resize_border_width) {
            *result = HTTOP;
            return true;
        }

        // Check the area where the user can click to move the window.
        if (determineNonClickableWidgetUnderMouse(m_custom_titlebar_layout, local_x, local_y)) {
            *result = HTCAPTION;
            return true;
        }

        *result = HTTRANSPARENT;
    }
    else if (msg->message == WM_SIZE) {
        if (m_maximize_btn) {
            WINDOWPLACEMENT wp;
            GetWindowPlacement(m_hwnd, &wp);
            if (wp.showCmd == SW_MAXIMIZE) {
                isMaximized = true;
                m_maximize_btn->setIcon(QIcon("resources/icons/restore.svg"));
            }
            else {
                isMaximized = false;
                m_maximize_btn->setIcon(QIcon("resources/icons/maximize.svg"));
            }
            m_maximize_btn->setChecked(wp.showCmd == SW_MAXIMIZE);
        }
    }
    return false;
}
// This is used to change the `active` state of widgets in custom title bar.
bool MainWindow::event(QEvent* evt) {
    switch (evt->type())
    {
    case QEvent::WindowActivate: {
        setWidgetsActiveStateInCustomTitlebar(m_custom_titlebar_layout, true);
        break;
    }

    case QEvent::WindowDeactivate: {
        setWidgetsActiveStateInCustomTitlebar(m_custom_titlebar_layout, false);
        break;
    }

    default:
        break;
    }
    return QMainWindow::event(evt);
}

// Determine whether the current mouse coordinate is on the non-clickable widget or not using a recursive method.
bool MainWindow::determineNonClickableWidgetUnderMouse(QLayout* layout, int x, int y) {
    if (!layout->count() && layout->geometry().contains(x, y)) {
        return true;
    }
    for (int i = 0; i < layout->count(); i++) {
        auto item = layout->itemAt(i)->widget();
        if (item) {
            if (item->geometry().contains(x, y))
                return !item->property("clickable widget").toBool();
        }
        else {
            auto child_layout = layout->itemAt(i)->layout();
            if (child_layout && child_layout->geometry().contains(x, y))
                return determineNonClickableWidgetUnderMouse(child_layout, x, y);
        }
    }
    return false;
}

// Set `active' state using recursive method.
void MainWindow::setWidgetsActiveStateInCustomTitlebar(QLayout* layout, bool active_state) {
    for (size_t i = 0; i < layout->count(); i++) {
        auto item = layout->itemAt(i)->widget();
        if (item)
        {
            item->setProperty("active", active_state);
            item->setStyleSheet(item->styleSheet());
        }
        else
        {
            auto child_layout = layout->itemAt(i)->layout();
            if (child_layout)
                setWidgetsActiveStateInCustomTitlebar(child_layout, active_state);
        }
    }
}
QWidget& MainWindow::getContentWidget() {
    return *m_content_widget;
}

QWidget& MainWindow::getTitlebarWidget() {
    return *m_titlebar_widget;
}

QHBoxLayout& MainWindow::getCustomTitlebarLayout() {
    return *m_custom_titlebar_layout;
}

void MainWindow::setResizeBorderWidth(const int& resize_border_width) {
    m_resize_border_width = resize_border_width;
}

void MainWindow::setTitlebarHeight(const int& titlebar_height) {
    m_titlebar_widget->setFixedHeight(titlebar_height);
}

// Render again when frame is moved to another monitor.
void MainWindow::onScreenChanged(QScreen* screen) {
    SetWindowPos(m_hwnd, NULL, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
        SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE);
}

void MainWindow::onMinimizeButtonClicked() {
    SendMessage(m_hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void MainWindow::onMaximizeButtonClicked() {
    isMaximized = !isMaximized;
    m_maximize_btn->setIcon(isMaximized ? QIcon("resources/icons/restore.svg") : QIcon("resources/icons/maximize.svg"));
    SendMessage(m_hwnd, WM_SYSCOMMAND, isMaximized ? SC_MAXIMIZE : SC_RESTORE, 0);

    // Remove the hover state from the maximize button.
    m_maximize_btn->setAttribute(Qt::WA_UnderMouse, false);
}

void MainWindow::onCloseButtonClicked() {
    SendMessage(m_hwnd, WM_CLOSE, 0, 0);
}