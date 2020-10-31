#pragma once

#include <vector>

class Component {
public:
	void virtual onAddOtherComponent(Component* component) {}
	void virtual onAddThisComponent(Component* component) {}
	void virtual onStart() {}
	void virtual onUpdate() {}
	void virtual onDelete() {}
};