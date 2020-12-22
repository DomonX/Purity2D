#pragma once

#include "component.hpp"


class Visibility : public Component {
public:
	virtual bool isVisible() {
		return true;
	};
	Component* clone() {
		return new Visibility();
	}
};