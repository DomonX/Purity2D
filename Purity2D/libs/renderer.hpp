#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "engine.hpp"
#include "time.hpp"

class Renderer : public Component {
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
	Renderer() {
		cameraHook = GameState::get()->getCameraHook();
	}
	void onUpdate() {
		Component::onUpdate();
		if (!renderConditions()) {
			return;
		}
		render();
	}

	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}

	void virtual render() {
		cout << "Renderuje element " << endl;
		Transform current = calculateNewTransform();
		vector<Line> lines = current.getLines();
		for (Line x : lines) {
			al_draw_line(x.begin().getX(), x.begin().getY(), x.end().getX(), x.end().getY(), al_map_rgb(255, 0, 0), 1);
		}
		(*transform) = (*transform) + (Rotation(10) * Time::getDeltaTime());		
	}

	bool virtual renderConditions() {
		return transform != nullptr && isVisible();
	}
};