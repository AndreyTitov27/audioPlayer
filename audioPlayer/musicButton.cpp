#include "musicButton.hpp"

MusicButton* MusicButton::lastMusicButton = nullptr;

MusicButton::MusicButton(const QString titleText, const int& index, const QString track,
    QMediaPlayer* player, int& mainWindowCurrentTrack, MainWindow* mainWindowInstance, QWidget* parent)
    : QWidget(parent), trackPath(track), numberRef(mainWindowCurrentTrack), mainWindowInstance(mainWindowInstance) {
    setAcceptDrops(true);
    setFixedHeight(40);

    this->player = player;
    layout = new QVBoxLayout(this);
    layoutH = new QHBoxLayout();
    number = new QLabel();
    title = new QLabel();
    title->setText(titleText);
    title->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    number->setText(QString::number(index));
    numberInt = index;
    checkBox = new QCheckBox();
    checkBox->setText("");
    checkBox->setFixedSize(20, 20);
    checkBox->setStyleSheet(musicCheckBoxStyle);
    checkBox->setVisible(false);

    layoutH->addWidget(checkBox, Qt::AlignLeft);
    layoutH->addWidget(number, Qt::AlignLeft);
    layoutH->addWidget(title);
    layout->addLayout(layoutH);
    setLayout(layout);
    setStyleSheet(musicButtonStyle);
}

void MusicButton::setActive(bool active) {
    if (!this) return;

    setStyleSheet(active ? musicButtonClickedStyle : musicButtonStyle);
}

void MusicButton::setTrackNumber(int num) {
    numberInt = num;
    number->setText(QString::number(num));
}
void MusicButton::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::LeftButton) {
        if (lastMusicButton != nullptr && lastMusicButton != this)
            lastMusicButton->setActive(false);
        numberRef = numberInt - 1;
        player->setSource(QUrl::fromLocalFile(trackPath));
        player->play();
        mainWindowInstance->getPlayPauseButton()->setIcon(QIcon("resources/icons/pause.svg"));
        setStyleSheet(musicButtonClickedStyle);
        lastMusicButton = this;
    }
}
void MusicButton::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (!mainWindowInstance->tracksDragging) {
            if (lastMusicButton != nullptr && lastMusicButton != this)
                lastMusicButton->setActive(false);
            numberRef = numberInt - 1;
            player->setSource(QUrl::fromLocalFile(trackPath));
            mainWindowInstance->getPlayPauseButton()->setIcon(QIcon("resources/icons/play.svg"));
            setStyleSheet(musicButtonClickedStyle);
            lastMusicButton = this;
        }
        else {
            dragStartPosition = event->pos();
            initialCursorPosition = event->globalPosition().toPoint(); // Запоминаем начальное положение курсора
        }
    }
    QWidget::mousePressEvent(event);
}

void MusicButton::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton)) {
        return;
    }
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) {
        return;
    }
    if (mainWindowInstance->tracksDragging) {
        QDrag* drag = new QDrag(this);
        QMimeData* mimeData = new QMimeData;

        mimeData->setText(trackPath);
        drag->setMimeData(mimeData);

        QPixmap pixmap = this->grab();
        drag->setPixmap(pixmap);

        drag->exec(Qt::MoveAction);
    }
    QWidget::mouseMoveEvent(event);
}

void MusicButton::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void MusicButton::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void MusicButton::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasText()) {
        QWidget* sourceWidget = static_cast<QWidget*>(event->source());
        if (sourceWidget && sourceWidget != this) {
            QVBoxLayout* parentLayout = mainWindowInstance->getTracksScrollAreaLayout();
            if (parentLayout) {
                int sourceIndex = parentLayout->indexOf(sourceWidget);
                int targetIndex = parentLayout->indexOf(this);
                qDebug() << "sourceIndex = " << sourceIndex << " targetIndex = " << targetIndex;

                QList<MusicButton*>* playlistButtons = mainWindowInstance->getPlaylistList()->at(mainWindowInstance->currentPlaylistNumber)->getList();
                MusicButton* movedButton = dynamic_cast<MusicButton*>(sourceWidget);
                if (movedButton && playlistButtons) {
                    // Найти текущий индекс кнопки в списке
                    int movedButtonIndex = playlistButtons->indexOf(movedButton);
                    playlistButtons->move(sourceIndex, targetIndex);
                }

                // Теперь обновляем лейаут
                parentLayout->removeWidget(sourceWidget);
                sourceWidget->setParent(nullptr);
                parentLayout->insertWidget(targetIndex, sourceWidget);

                // Обновляем индексы кнопок и сохраняем настройки
                mainWindowInstance->updateMusicButtonIndices();

                if (mainWindowInstance->currentTrackNumber == sourceIndex)
                    mainWindowInstance->currentTrackNumber = targetIndex;

                saveSettings(mainWindowInstance);
            }
        }
        event->acceptProposedAction();
    }
}

