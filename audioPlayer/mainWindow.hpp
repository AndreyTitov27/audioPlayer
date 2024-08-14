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
    MainWindow();
    void setCurrentTrackNumber(int index) {
        currentTrackNumber = index;
    }

private:
    bool isShownFileOptions;
    int trackNumber;
    int currentTrackNumber;
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* manageTracksLayoutH;
    QVBoxLayout* manageTracksLayoutV;
    QVBoxLayout* tracksLayout;
    QHBoxLayout* playerButtonsLayoutH;
    QVBoxLayout* playerButtonsLayoutV;

    QScrollArea* tracksScrollArea;
    QWidget* tracksScrollAreaWidget;
    QVBoxLayout* tracksScrollAreaLayout;

    QVBoxLayout* superBottomLayout;
    QHBoxLayout* bottomLayout;
    QVBoxLayout* bottomLeftLayout;
    QVBoxLayout* bottomRightLayout;
    QHBoxLayout* overBottomLayout;
    QHBoxLayout* centralLayoutH;
    QVBoxLayout* leftLayout;
    QVBoxLayout* rightLayout;

    QPushButton* addTrackButton;
    QPushButton* removeTrackButton;
    QPushButton* moveTrackButton;

    QPushButton* previousTrackButton;
    QPushButton* playStopButton;
    QPushButton* nextTrackButton;
    QPushButton* loopButton;

    QVBoxLayout* loopButtonLayout;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    QList<MusicButton*>* playlist;
    QSlider* trackPositionSlider;
    QVBoxLayout* trackPositionSliderLayout;
    QSlider* trackVolumeSlider;
    QVBoxLayout* trackVolumeSliderLayout;

    QHBoxLayout* trackCoverLayoutH;
    QVBoxLayout* trackCoverLayoutV;
    QLabel* trackCoverLabel;
    QImage coverImage;

private slots:
    void selectMultipleFiles();

    void play();
    void pause();
    void previousTrack();
    void nextTrack();
    void loop();

    void setTrackPosition(int pos);
    void updateSliderPosition(qint64 pos);
    void updateSliderRange(qint64 duration);

    void setTrackVolume(int volume);

    void processMetaData();

    void resizeEvent(QResizeEvent* event) override;
};
