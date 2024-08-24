#pragma once
#include "musicButton.hpp"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFileInfo>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QMediaMetaData>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtCore/QList>
#include <QtWidgets/QScrollArea>

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtGui/QResizeEvent>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QParallelAnimationGroup>
#include <QtGui/qevent.h>
#include <QtWidgets/QMenuBar>

class MainWindow : public QMainWindow {
public:
    int trackNumber;
    int currentTrackNumber;
    MainWindow();
    void setCurrentTrackNumber(int index) {
        currentTrackNumber = index;
    }
    void setVolume(float vol);
    float getVolume() { return audioOutput->volume(); }
    
    QMediaPlayer* getPlayer() { return player; }
    QList<MusicButton*>* getPlaylist() { return playlist; }
    QVBoxLayout* getTracksScrollAreaLayout() { return tracksScrollAreaLayout; }
    int getRepeatMode() { return repeatMode; }
    void setRepeatMode(int mode);

private:
    int repeatMode;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QHBoxLayout* topLayout;
    QVBoxLayout* topLeftLayout;
    QHBoxLayout* trackCoverLayoutH;
    QVBoxLayout* trackCoverLayoutV;
    QLabel* trackCoverLabel;
    QImage coverImage;

    QVBoxLayout* topRightLayout;
    QVBoxLayout* tracksLayout;
    QScrollArea* tracksScrollArea;
    QWidget* tracksScrollAreaWidget;
    QVBoxLayout* tracksScrollAreaLayout;

    QVBoxLayout* bottomLayout;
    QHBoxLayout* bottomUpLayout;
    QPushButton* addTrackButton;
    QPushButton* removeTrackButton;
    QPushButton* moveTrackButton;
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
    QList<MusicButton*>* playlist;

private slots:
    void selectFiles();

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

    void resizeEvent(QResizeEvent* event) override;

    void closeEvent(QCloseEvent* event) override;
};
