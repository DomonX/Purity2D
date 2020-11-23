#pragma once

#include <vector>

class Component {
public:
	/*! \brief Lifecycle hook that is activated to inform about other Component in same GameObject */
	void virtual onGetOtherComponent(Component* component) {}
	/*! \brief Lifecycle hook that is activated to inform about other Component in parent GameObject */
	void virtual onGetParentComponent(Component* component) {}
	/*! \brief Lifecycle hook that is activated to inform about other Component is removed in parent GameObject */
	void virtual onRemoveParentComponent(Component* component) {}
	/*! \brief Lifecycle hook that is activated to inform about game started or component created */
	void virtual onStart() {}
	/*! \brief Lifecycle hook that is activated to inform about new frame rendered */
	void virtual onUpdate() {}
	/*! \brief Lifecycle hook that is activated to inform about deleting Component */
	void virtual onDelete() {}
	/*! \brief Method for cloning component */
	virtual Component* clone() { return nullptr; }
protected:
	/*! 
		\brief Saves component in place when share type with destination component
		\param target Pointer to place where component will be stored
		\param component Component which will be stored
	*/
	template<class T> void storeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = t;
		}
	}

	/*!
		\brief Removes component in place when share type with destination component
		\param target Pointer to place where component will be removed
		\param component Component which is desired to be removed
	*/
	template<class T> void removeIfIsInstance(T** target, Component* component) {
		T* t = dynamic_cast<T*>(component);
		if (t) {
			(*target) = nullptr;
		}
	}
};