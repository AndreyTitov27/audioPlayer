#pragma once
#include "mainWindow.hpp"
#include <fstream>
#include <filesystem>

void loadSettings(MainWindow* mainWindowInstance);
void saveSettings(MainWindow* mainWindowInstance);