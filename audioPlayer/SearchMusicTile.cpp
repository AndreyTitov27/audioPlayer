#include "SearchMusicTile.h"

int SearchMusicTile::numberStatic = -1;
SearchMusicTile::SearchMusicTile(const QString& _title, const QString& _author,
	const QString& coverPath, const QString& _link,
	SearchWindow* searchWindowInstance, QWidget* parent) : link(_link),
	searchWindowInstance(searchWindowInstance) {
	numberStatic++;
	index = numberStatic;
	setFixedSize(160, 250);
	mainLayout = new QVBoxLayout(this);
	textLayout = new QVBoxLayout();
	this->setLayout(mainLayout);
	
	title = new QLabel(_title);
	author = new QLabel(_author);
	cover = QImage(coverPath);
	coverLabel = new QLabel();
	coverLabel->setFixedSize(150, 150);
	coverLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	coverLabel->setScaledContents(true);
	coverLabel->setPixmap(QPixmap::fromImage(cover));

	mainLayout->setAlignment(Qt::AlignHCenter);
	mainLayout->addWidget(coverLabel);
	mainLayout->addLayout(textLayout);
	textLayout->addWidget(title);
	textLayout->addWidget(author);
	textLayout->setAlignment(Qt::AlignCenter);
}
void SearchMusicTile::mouseReleaseEvent(QMouseEvent* event) {
	searchWindowInstance->downloadTrackFromSearch(this);
}