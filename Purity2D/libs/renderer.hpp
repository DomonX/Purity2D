#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "engine.hpp"

class Renderer : public Component {
protected:
	Transform* transform = nullptr;
	Transform calculateNewTransform() {
		Vector2D newPosition = transform->getPosition() * GameState::get()->getViewScale() - GameState::get()->getViewPosition();
		Vector2D newScale = transform->getScale() * GameState::get()->getViewScale();
		return Transform(newScale, newPosition, transform->getRotation());
	}
public:
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
		Transform current = calculateNewTransform();
		vector<Line> lines = current.getLines();
		for (Line x : lines) {
			al_draw_line(x.begin().getX(), x.begin().getY(), x.end().getX(), x.end().getY(), al_map_rgb(255, 0, 0), 1);
		}
		(*transform) = (*transform) + Rotation(1);		
	}

	bool virtual renderConditions() {
		return transform != nullptr;
	}
};