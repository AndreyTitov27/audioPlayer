#include "fileFuctions.hpp"

void loadSettings(MainWindow* mainWindowInstance) {
	std::ifstream file("resources/settings.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.ends_with(".mp3") || line.ends_with(".wav")) {
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
			}
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
		if (!mainWindowInstance->getPlaylist()->isEmpty()) {
			for (int i = 0; i < mainWindowInstance->getPlaylist()->size(); i++) {
				file << mainWindowInstance->getPlaylist()->at(i)->getTrackPath().toUtf8().constData() << std::endl;
			}
		}
		file << "volume: " << mainWindowInstance->getVolume() << std::endl;
		file << "repeat mode: " << mainWindowInstance->getRepeatMode();
		file.close();
	}
}