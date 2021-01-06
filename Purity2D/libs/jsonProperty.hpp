#pragma once

#include <nlohmann/json.hpp>

using namespace std;
using Json = nlohmann::json;

class JsonProperty {
public:
	string name;
	Json value;
	bool created;

	JsonProperty() {
		created = false;
	}

	JsonProperty(string name) {
		this->name = name;
		value = Json::object();
		created = true;
	}
};