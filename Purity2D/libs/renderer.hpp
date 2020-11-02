#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "engine.hpp"

class Renderer : public Component {
protected:
	Transform* transform = nullptr;
public:
	void onUpdate() {
		Component::onUpdate();
		if (transform == nullptr) {
			return;
		}
		render();
	}

	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}

	void render() {
		vector<Line> lines = transform->getLines();
		for (Line i : lines) {
			Line x = i;
			//Line x = ( i + Vector2D(0, -300) ) * scale;
			al_draw_line(x.begin().getX(), x.begin().getY(), x.end().getX(), x.end().getY(), al_map_rgb(255, 0, 0), 1);
		}
		//(*transform) = (*transform) + Rotation(1);		
	}
};