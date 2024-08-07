#ifndef MUSIC_BUTTON_HPP
#define MUSIC_BUTTON_HPP
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
class MusicButton : public QWidget {
public:
	MusicButton(const QString& titleText, QWidget* parent = nullptr);
private:
	QVBoxLayout* layout;
	QLabel* title;
};
#endif // !MUSIC_BUTTON_HPP
