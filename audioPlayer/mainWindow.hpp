#pragma once

#include <QtWidgets/QApplication>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtGui/QScreen>
#include <QtWidgets/QSpacerItem>
#include <QtGui/QWindow>
#include <QtGui/qevent.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <Windows.h>
#include <Windowsx.h>
#include <vector>
//
#include "musicButton.hpp"
#include "playlistButton.hpp"
#include "settingsWindow.hpp"
#include "downloadingWindow.hpp"
#include "fileFuctions.hpp"
#include "styles.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QInputDialog>
#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaMetaData>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtCore/QList>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QMessageBox>

#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/qevent.h>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>

class MusicButton;
class PlaylistButton;
class SettingsWindow;
class DownloadingWindow;
class MainWindow : public QMainWindow {

    HWND m_hwnd;
    int m_resize_border_width;

    QPushButton* m_minimize_btn;
    QPushButton* m_maximize_btn;
    QPushButton* m_close_btn;
    
    QWidget* m_content_widget;
    QWidget* m_titlebar_widget;
    QHBoxLayout* m_custom_titlebar_layout;

public:
    int trackNumber;
    int currentTrackNumber;
    int playlistNumber;
    int currentPlaylistNumber;
    bool removeTracksSelectionMode;
    bool removePlaylistSelectionMode;
    bool tracksDragging;
    bool isTrackDownloading;

    MainWindow(QWidget* parent = nullptr);
    void setResizeBorderWidth(const int& resize_border_width);
    void setTitlebarHeight(const int& titlebar_height);
    QWidget& getContentWidget();
    QWidget& getTitlebarWidget();
    QHBoxLayout& getCustomTitlebarLayout();
    //
    void setCurrentTrackNumber(int index) {
        currentTrackNumber = index;
    }
    QPushButton* getPlayPauseButton() { return playStopButton; }
    void setVolume(float vol);
    float getVolume() { return audioOutput->volume(); }

    QMediaPlayer* getPlayer() { return player; }
    QScrollArea* getTracksScrollArea() { return tracksScrollArea; }
    QVBoxLayout* getTracksScrollAreaLayout() { return tracksScrollAreaLayout; }
    int getRepeatMode() { return repeatMode; }
    void setRepeatMode(int mode);

    QList<PlaylistButton*>* getPlaylistList() { return playlistList; }
    void updateStyles();

    QVBoxLayout* getPlaylistButtonsScrollAreaLayout() { return playlistButtonsScrollAreaLayout; }
    void updateMusicButtonIndices();

private:
    int repeatMode;
    bool showPlaylistsFlag;

    QWidget* entireWidget;
    QVBoxLayout* entireLayout;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QHBoxLayout* topLayout;
    QVBoxLayout* topLeftLayout;
    QHBoxLayout* settingsButtonLayout;
    QVBoxLayout* settingsButtonLayoutV;
    QPushButton* settingsButton;
    QPushButton* downloadTrackButton;
    QHBoxLayout* trackCoverLayoutH;
    QVBoxLayout* trackCoverLayoutV;
    QLabel* trackCoverLabel;
    QImage coverImage;

    QVBoxLayout* topRightLayout;
    QHBoxLayout* tracksPlaylistsLayout;
    QScrollArea* tracksScrollArea;
    QWidget* tracksScrollAreaWidget;
    QVBoxLayout* tracksScrollAreaLayout;

    QScrollArea* playlistButtonsScrollArea;
    QWidget* playlistButtonsScrollAreaWidget;
    QVBoxLayout* playlistButtonsScrollAreaLayout;

    QVBoxLayout* bottomLayout;
    QHBoxLayout* bottomUpLayout;
    QPushButton* showPlaylistsButton;
    QPushButton* addTrackButton;
    QPushButton* removeTrackButton;
    QPushButton* moveTrackButton;
    //
    QPushButton* addPlaylistButton;
    QPushButton* removePlaylistButton;
    //
    QHBoxLayout* manageTracksLayoutH;
    QVBoxLayout* manageTracksLayoutV;

    QHBoxLayout* bottomDownLayout;
    QVBoxLayout* bottomDownLeftLayout;
    QPushButton* previousTrackButton;
    QPushButton* playStopButton;
    QPushButton* nextTrackButton;
    QHBoxLayout* playerButtonsLayoutH;
    QVBoxLayout* playerButtonsLayoutV;
    QPushButton* repeatButton;
    QHBoxLayout* repeatButtonLayout;

    QVBoxLayout* bottomDownRightLayout;
    QSlider* trackPositionSlider;
    QVBoxLayout* trackPositionSliderLayout;
    QSlider* trackVolumeSlider;
    QVBoxLayout* trackVolumeSliderLayout;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QList<PlaylistButton*>* playlistList;

    SettingsWindow* settingsWindow = nullptr;
    DownloadingWindow* downloadingWindow = nullptr;

    void initializeWidgets();
    void initializeTitlebar();
    void createPlaylistsLayout();
    //
    bool isMaximized;
    bool nativeEvent(const QByteArray& event_type, void* message, qintptr* result) override;
    bool event(QEvent* evt);
    bool determineNonClickableWidgetUnderMouse(QLayout* layout, int x, int y);
    void setWidgetsActiveStateInCustomTitlebar(QLayout* layout, bool active_state);
    void onScreenChanged(QScreen* screen);
    void onMinimizeButtonClicked();
    void onMaximizeButtonClicked();
    void onCloseButtonClicked();

private slots:
    void showPlaylists();
    void addPlaylist();
    void removePlaylist();

    void addTracks();
    void removeTracks();
    void moveTracks();

    void play();
    void previousTrack();
    void nextTrack();
    void repeat();

    void setTrackPosition(int pos);
    void updateSliderPosition(qint64 pos);
    void updateSliderRange(qint64 duration);

    void setTrackVolume(int volume);

    void processMetaData();

    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void openSettingsWindow();
    void openDownloadingWindow();

    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
};
