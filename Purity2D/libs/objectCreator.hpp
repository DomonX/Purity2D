#pragma once

#include "jsonProperty.hpp"
#include "gameObject.hpp"

class ObjectCreator {
	JsonProperty compile() {
		return JsonProperty();
	}

	GameObject* load() {
		return nullptr;
	}
};