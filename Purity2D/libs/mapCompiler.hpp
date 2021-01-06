#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "filesystemHandler.hpp"
#include "jsonProperty.hpp"

using namespace std;

class MapCompiler {
public:
	void compile(string mapName) {
		vector<string> sceneNames = getSceneNames(mapName);
		//vector<Json> scenes = 
	}
private:
	vector<string> getSceneNames(string mapName) {
		vector<string> scenes;		
		FileSystemHandler h = FileSystemHandler();
		scenes = h.listDir("maps/" + mapName);

		remove_if(scenes.begin(), scenes.end(), [](string i) { i.find(".") != string::npos; });
	}

	Json compileScene(string sceneName) {
		Json scene = Json::object();
		scene["name"] = sceneName;
	}
};