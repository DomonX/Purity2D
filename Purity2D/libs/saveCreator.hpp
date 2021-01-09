#pragma once

#include "gameState.hpp"
#include "filesystemHandler.hpp"

class SaveCreator {
public:
	void save(string fileName) {
		Json j = GameState::get()->save();
		string gameName = j["name"];
		string path = "saves/" + gameName + '/' + fileName + ".json";
		FileSystemHandler().saveToFile(path, j.dump(4));
	}
};