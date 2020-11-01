#pragma once

#include "../component/component.hpp"
#include "../transform/transform.hpp"
#include "../engine/engine.hpp"
#include <allegro5/allegro_primitives.h>

class Renderer : public Component {
protected:
	Transform * transform;
public:
	void onUpdate() {
		Component::onUpdate();
		if (transform == nullptr) {
			return;
		}
		render();
	}

	void onAddOtherComponent(Component * component) {
		Component::onAddOtherComponent(component);
		if (Transform * t = dynamic_cast<Transform *>(component)) {
			transform = t;
		}
	}

	void onAddThisComponent(Component * component) {
		Component::onAddThisComponent(component);
		if (Transform* t = dynamic_cast<Transform*>(component)) {
			transform = t;
		}
	}

	void render() {
		Vector2D lu = transform->getLeftUp();
		Vector2D ld = transform->getLeftDown();
		Vector2D ru = transform->getRightUp();
		Vector2D rd = transform->getRightDown();
		Vector2D pos = transform->getPosition();
		(*transform) = (*transform) + Rotation(1);
		al_draw_line(pos.getX(), pos.getY(), rd.getX(), rd.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(pos.getX(), pos.getY(), ru.getX(), ru.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(pos.getX(), pos.getY(), lu.getX(), lu.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(pos.getX(), pos.getY(), ld.getX(), ld.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(ld.getX(), ld.getY(), rd.getX(), rd.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(ru.getX(), ru.getY(), rd.getX(), rd.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(ru.getX(), ru.getY(), lu.getX(), lu.getY(), al_map_rgb(255, 0, 0), 1);
		al_draw_line(ld.getX(), ld.getY(), lu.getX(), lu.getY(), al_map_rgb(255, 0, 0), 1);
		
	}
};