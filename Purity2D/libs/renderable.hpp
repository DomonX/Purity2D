#pragma once
class Renderable {
public:
	/*!	\brief Lifecycle hook called when Renderable is ready to render */
	void virtual onRender() {}
};