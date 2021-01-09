#pragma once

#include <string>

using namespace std;
class SceneElement {
private:
	string sceneName;
public:
	virtual void setScene(string name) { sceneName = name; }
	virtual string getScene() { return sceneName; }
};