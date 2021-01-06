#pragma once

#include "component.hpp"
#include "sprite.hpp"
#include "meshController.hpp"
#include "controllerObserver.hpp"

class Animator : public Component {
private:
	map<string, vector<Vector2D>> animations;
	Sprite* sprite;
	MeshController* ctrl;
	vector<Vector2D> currentAnimation;
	int currentFrame;
	int animationFrames;
	float currentTime;
	float frameDuration;
	bool isAnimating;
	bool cycle;
public:
	Animator(map < string, vector<Vector2D> > animations) {
		this->animations = animations;
	}

	void onGetOtherComponent(Component* component) {
		storeIfIsInstance(&sprite, component);
	}

	void animate(string animation, float duration, bool cycle) {
		if (isAnimating) {
			return;
		}
		currentAnimation = animations[animation];
		animationFrames = currentAnimation.size() - 1;
		if (animationFrames < 0) {
			return;
		}
		setFrame(currentAnimation.at(0));
		if (animationFrames == 0) {
			return;
		}
		frameDuration = duration / ( animationFrames + 1 );
		currentFrame = 0;
		currentTime = 0;
		this->cycle = cycle;
		isAnimating = true;
	}

	void onUpdate() {
		if (!isAnimating) {
			return;
		}
		currentTime += Time::getDeltaTime();
		if (currentTime >= frameDuration) {
			nextFrame();
		}

		if (currentFrame > animationFrames) {
			processFinishedAnimation();
		}
	}
private:
	void nextFrame() {
		currentFrame++;
		currentTime -= frameDuration;
		if (currentFrame <= animationFrames) {
			setFrame(currentAnimation.at(currentFrame));
		}
	}

	void setFrame(Vector2D data) {
		sprite->change(data.getX(), data.getY());
	}

	void processFinishedAnimation() {
		if (cycle) {
			currentFrame = -1;
			return;
		} else {
			isAnimating = false;
		}
	}
};