#pragma once

#include "visibility.hpp"
#include "camera.hpp"
#include "gameState.hpp"

class CameraVisibility : public Visibility {

	Camera** cameraHook = nullptr;
	Transform* transform = nullptr;

	void onGetOtherComponent(Component* component) {
		Component::onGetOtherComponent(component);
		storeIfIsInstance(&transform, component);
	}

public:
	CameraVisibility(): Visibility() {
		cameraHook = GameState::get()->getCameraHook();
	}

	virtual bool isVisible() {
		return (*cameraHook)->isVisible(transform);
	};
};