#pragma once
#include "downloadingWindow.hpp"
#include "SearchWindow.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>

class SearchWindow;
class SearchMusicTile : public QWidget {
public:
	SearchMusicTile(const QString& _title, const QString& _author,
		const QString& coverPath, const QString& _link,
		SearchWindow* searchWindowInstance, QWidget* parent = nullptr);
	QString getLink() const { return link; }
	int getIndex() const { return index; }
	void decreaseNumberStatic() { numberStatic--; }

private:
	static int numberStatic;
	int index;
	SearchWindow* searchWindowInstance;
	QVBoxLayout* mainLayout;
	QVBoxLayout* textLayout;
	QLabel* title;
	QLabel* author;
	QLabel* coverLabel;
	QImage cover;
	QString link;

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
};

