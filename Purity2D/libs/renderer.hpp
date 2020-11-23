#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "engine.hpp"
#include "time.hpp"

class Renderer : public Component, public Renderable {
protected:
	Transform* transform = nullptr;
	Camera** cameraHook = nullptr;
	Transform calculateNewTransform() {
		Vector2D newPosition = (transform->getPosition() - GameState::get()->getViewPosition()) * GameState::get()->getViewScale();
		Vector2D newScale = transform->getScale() * GameState::get()->getViewScale();
		return Transform(newScale, newPosition, transform->getRotation());
	}
	bool isVisible() {
		return (*cameraHook)->isVisible(transform);
	}
public:
	/*! \brief Constructor for Renderer which automatically connects Camera to it */
	Renderer() {
		cameraHook = GameState::get()->getCameraHook();
	}

	/*! @copydoc Component::onUpdate() */
	void onUpdate() {
		Component::onUpdate();
		if (!renderConditions()) {
			return;
		}
		onRender();
		//GameState::get()->queueRender(this->transform->getLayer(), this->transform->getPosition().getY(), this);
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
		//(*transform) = (*transform) + (Rotation(10) * Time::getDeltaTime());		
	}

	/*! \brief Returns if current GameObject can be rendered */
	bool virtual renderConditions() {
		return transform != nullptr && isVisible();
	}

	virtual Component* clone() {
		return new Renderer();
	}
};