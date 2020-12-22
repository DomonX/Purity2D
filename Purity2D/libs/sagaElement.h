#pragma once

class SagaElement {
public:
	/*! \brief Lifecycle hook that is activated to inform about game started */
	void virtual onStart() {}
	/*! \brief Lifecycle hook that is activated to inform about new frame rendered */
	void virtual onUpdate() {}
	/*! \brief Lifecycle hook that is activated to inform about rendering alpha map */
	void virtual onUpdateAlpha() {}
	/*! \brief Lifecycle hook that is activated to inform about deleting Component */
	void virtual onDelete() {}
};