#pragma once

#include <allegro5/allegro_primitives.h>

#include "component.hpp"
#include "transform.hpp"
#include "cameraVisiblity.hpp"
#include "time.hpp"
#include "renderable.hpp"

class Renderer : public Component, public Renderable {
protected:
	Transform* transform = nullptr;
	Visibility* visibility = nullptr;
	bool isRendered = false;
	virtual Transform calculateNewTransform();
public:
	void onUpdate() {
		Component::onUpdate();
		isRendered = renderConditions();
		if (!isRendered) {
			return;
		}
		onRender();
	}

	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
		storeIfIsInstance(&visibility, component);
	}

	void virtual onRender() {
		Transform current = calculateNewTransform();
		vector<Line> lines = current.getLines();
		for (Line x : lines) {
			al_draw_line(x.begin().getX(), x.begin().getY(), x.end().getX(), x.end().getY(), al_map_rgb(255, 0, 0), 1);
		}	
	}

	bool virtual renderConditions() {
		return transform != nullptr && visibility && visibility->isVisible();
	}

	virtual Component* clone() {
		return new Renderer();
	}
};