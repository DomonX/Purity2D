#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "time.hpp"
#include "renderable.hpp"
#include "camera.hpp"

class Renderer : public Component, public Renderable {
protected:
	Transform* transform = nullptr;
	Camera** cameraHook = nullptr;
	virtual Transform calculateNewTransform();
	bool isRendered;
	virtual bool isVisible() {
		return (*cameraHook)->isVisible(transform);
	}
public:
	/*! \brief Constructor for Renderer which automatically connects Camera to it */
	Renderer();

	/*! @copydoc Component::onUpdate() */
	void onUpdate() {
		Component::onUpdate();
		isRendered = renderConditions();
		if (!isRendered) {
			return;
		}
		onRender();
		// GameState::get()->queueRender(this->transform->getLayer(), this->transform->getPosition().getY(), this);
	}

	/*! @copydoc Component::onGetOtherComponent() */
	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}

	/*! @copydoc Renderable::onRender() */
	void virtual onRender() {
		Transform current = calculateNewTransform();
		vector<Line> lines = current.getLines();
		for (Line x : lines) {
			al_draw_line(x.begin().getX(), x.begin().getY(), x.end().getX(), x.end().getY(), al_map_rgb(255, 0, 0), 1);
		}
		(*transform) = (*transform) + (Rotation(10) * Time::getDeltaTime());		
	}

	/*! \brief Returns if current GameObject can be rendered */
	bool virtual renderConditions() {
		return transform != nullptr && isVisible();
	}
	/*! @copydoc Component::clone() */
	virtual Component* clone() {
		return new Renderer();
	}
};