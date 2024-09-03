#pragma once
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
public:
    int trackNumber;
    int currentTrackNumber;
    int playlistNumber;
    int currentPlaylistNumber;
    bool removeSelectionMode;
    bool isTrackDownloading;
    MainWindow();
    void setCurrentTrackNumber(int index) {
        currentTrackNumber = index;
    }
    QPushButton* getPlayPauseButton() { return playStopButton; }
    void setVolume(float vol);
    float getVolume() { return audioOutput->volume(); }

    QMediaPlayer* getPlayer() { return player; }
    QVBoxLayout* getTracksScrollAreaLayout() { return tracksScrollAreaLayout; }
    int getRepeatMode() { return repeatMode; }
    void setRepeatMode(int mode);

    QList<PlaylistButton*>* getPlaylistList() { return playlistList; }
    void updateStyles();

    QVBoxLayout* getPlaylistButtonsScrollAreaLayout() { return playlistButtonsScrollAreaLayout; }

private:
    int repeatMode;
    bool showPlaylistsFlag;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QHBoxLayout* topLayout;
    QVBoxLayout* topLeftLayout;
    QHBoxLayout* settingsButtonLayout;
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
    void createPlaylistsLayout();

private slots:
    void showPlaylists();
    void addPlaylist();
    //void removePlaylist();

    void addTracks();
    void removeTracks();

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
