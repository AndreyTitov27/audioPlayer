#include "fileFuctions.hpp"

void loadSettings(MainWindow* mainWindowInstance) {
	std::ifstream file("resources/settings.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.rfind("playlist-", 0) == 0) {
				mainWindowInstance->playlistNumber++;
				PlaylistButton* newPlaylistButton = new PlaylistButton(QString::fromUtf8(line.substr(9, line.find(":") - 9)),
					mainWindowInstance->playlistNumber + 1, mainWindowInstance->currentPlaylistNumber,
					mainWindowInstance, mainWindowInstance);
				mainWindowInstance->getPlaylistList()->append(newPlaylistButton);
				mainWindowInstance->getPlaylistButtonsScrollAreaLayout()->addWidget(newPlaylistButton);
			}
			if (line.ends_with(".mp3") || line.ends_with(".wav")) {
				if (std::filesystem::exists(line)) {
					(*mainWindowInstance->getPlaylistList()->at(mainWindowInstance->playlistNumber)->getTrackNumber())++;
					QString path = QString::fromUtf8(line);
					QFileInfo fileInfo(path);
					MusicButton* musicButton = new MusicButton(fileInfo.completeBaseName(),
						*mainWindowInstance->getPlaylistList()->at(mainWindowInstance->playlistNumber)->getTrackNumber() + 1,
						path, mainWindowInstance->getPlayer(), mainWindowInstance->currentTrackNumber,
						mainWindowInstance, mainWindowInstance);
					musicButton->setVisible(false);
					mainWindowInstance->getPlaylistList()->at(mainWindowInstance->playlistNumber)->getList()->append(musicButton);
					mainWindowInstance->getTracksScrollAreaLayout()->addWidget(musicButton);
				}
			}
			/*if (line.ends_with(".mp3") || line.ends_with(".wav")) {
				if (std::filesystem::exists(line)) {
					mainWindowInstance->trackNumber++;
					QString path = QString::fromUtf8(line);
					QFileInfo fileInfo(path);
					MusicButton* musicButton = new MusicButton(fileInfo.completeBaseName(),
						mainWindowInstance->trackNumber + 1, path, mainWindowInstance->getPlayer(),
						mainWindowInstance->currentTrackNumber, mainWindowInstance, mainWindowInstance);
					mainWindowInstance->getPlaylist()->append(musicButton);
					mainWindowInstance->getTracksScrollAreaLayout()->addWidget(musicButton);
				}
			}*/
			if (line.rfind("volume: ", 0) == 0) {
				mainWindowInstance->setVolume(std::stof(line.substr(8)));
			}
			if (line.rfind("repeat mode: ", 0) == 0) {
				mainWindowInstance->setRepeatMode(std::stoi(line.substr(13)));
			}
		}
		file.close();
	}
}
void saveSettings(MainWindow* mainWindowInstance) {
	std::ofstream file("resources/settings.txt");
	if (file.is_open()) {
		if (!mainWindowInstance->getPlaylistList()->isEmpty()) {
			for (int i = 0; i < mainWindowInstance->getPlaylistList()->size(); i++) {
				file << "playlist-" << mainWindowInstance->getPlaylistList()->at(i)->
					getTitle().toUtf8().constData() << ":" << std::endl;
				if (!mainWindowInstance->getPlaylistList()->at(i)->getList()->isEmpty()) {
					for (int j = 0; j < mainWindowInstance->getPlaylistList()->at(i)->getList()->size(); j++) {
						file << mainWindowInstance->getPlaylistList()->at(i)->
							getList()->at(j)->getTrackPath().toUtf8().constData() << std::endl;
					}
				}
			}
		}
		/*if (!mainWindowInstance->getPlaylist()->isEmpty()) {
			for (int i = 0; i < mainWindowInstance->getPlaylist()->size(); i++) {
				file << mainWindowInstance->getPlaylist()->at(i)->getTrackPath().toUtf8().constData() << std::endl;
			}
		}*/
		file << "volume: " << mainWindowInstance->getVolume() << std::endl;
		file << "repeat mode: " << mainWindowInstance->getRepeatMode();
		file.close();
	}
}