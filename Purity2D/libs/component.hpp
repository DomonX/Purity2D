#pragma once

#include <vector>

class Component {
public:
	void virtual onGetOtherComponent(Component* component) {}
	void virtual onGetParentComponent(Component* component) {}
	void virtual onRemoveParentComponent(Component* component) {}
	void virtual onStart() {}
	void virtual onUpdate() {}
	void virtual onDelete() {}
protected:
	template<class T> void storeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = t;
		}
	}

	template<class T> void removeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = nullptr;
		}
	}
};