#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <QtCore/QFileInfo>
#include <QtMultimedia/QMediaPlayer>

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


private:
    bool isShownFileOptions;
    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* manageTracksLayoutH;
    QVBoxLayout* manageTracksLayoutV;
    QVBoxLayout* tracksLayout;
    QHBoxLayout* playerButtonsLayoutH;
    QVBoxLayout* playerButtonsLayoutV;

    QPushButton* addTrackButton;
    QPushButton* removeTrackButton;
    QVBoxLayout* addTrackOptionsLayout;
    QPushButton* selectSingleTrackButton;
    QPushButton* selectMultipleTracksButton;

    QPushButton* previousTrackButton;
    QPushButton* playStopButton;
    QPushButton* nextTrackButton;

    QMediaPlayer* player;
    QStringList* playlist;

private slots:
    void showFileOptions();
    void selectSingleFile();
    void selectMultipleFiles();
};
