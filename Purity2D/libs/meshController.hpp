#pragma once

#include "component.hpp"
#include "meshHolder.hpp"
#include "keyboardObserver.hpp"
#include "keyboard.hpp"
#include "time.hpp"
#include "transform.hpp"
#include "meshCollider.hpp"
#include "controllerObserver.hpp"
#include "EDirection.hpp"

#include <algorithm>;

class MeshController: public Component, public KeyboardObserver {
private:
	MeshHolder* mesh = nullptr;
	Transform* tr = nullptr;
	Direction currentKey = Direction::NONE;
	Direction currentMove = Direction::NONE;
	float distance = -1;
	float currentDistance = 0;
	float movementSpeed;
	vector<ControllerObserver*> observers;
public:
	MeshController(float movementSpeed) : Component(), KeyboardObserver() {
		this->movementSpeed = movementSpeed;
	}

	void onGetOtherComponent(Component* component) {
		this->storeIfIsInstance(&mesh, component);
		this->storeIfIsInstance(&tr, component);
	}

	void onUpdate() {
		if (isNotMoving()) {
			return;
		}

		if (moveIsAboutToStart() && !startMovement()) {
			return;
		}

		applyNewPosition();

		if (movementIsFinished()) {
			finishMovement();
		}
	}

	float getMovementTime() {
		return 1 / movementSpeed;
	}

	void move(Direction direction) {
		currentKey = direction;
	}

	bool canMove(Vector2D pos, Vector2D dest) {
		GameObject* curr = mesh->getMesh()->objects[(int)Layer::TILES][pos];
		if (checkCollisionForObjectOut(curr, dest)) {
			informCollide(curr);
			return false;
		}
		vector<GameObject*> destObjects = mesh->getMesh()->getObjectsInPosition(dest);
		for (GameObject* go : destObjects) {
			if (checkCollisionForObjectIn(go, pos)) {
				informCollide(go);
				return false;
			}
		}
		return true;
	}

	void subscribe(ControllerObserver* observer) {
		observers.push_back(observer);
	}

	void unsubscribe(ControllerObserver* observer) {
		remove_if(observers.begin(), observers.end(), [observer](ControllerObserver* ob) { return ob == observer; });
	}

private:
	Vector2D getMoveVector(double move) {
		if (currentMove == Direction::UP) {
			return Vector2D(0, -move);
		}
		if (currentMove == Direction::DOWN) {
			return Vector2D(0, move);
		}
		if (currentMove == Direction::LEFT) {
			return Vector2D(-move, 0);
		}
		if (currentMove == Direction::RIGHT) {
			return Vector2D(move, 0);
		}
		return Vector2D();
	}

	Vector2D getFinishMoveVector() {
		if (currentMove == Direction::UP) {
			return Vector2D::UP;
		}
		if (currentMove == Direction::DOWN) {
			return Vector2D::DOWN;
		}
		if (currentMove == Direction::LEFT) {
			return Vector2D::LEFT;
		}
		if (currentMove == Direction::RIGHT) {
			return Vector2D::RIGHT;
		}
	}

	bool isNotMoving() {
		return currentKey == Direction::NONE && distance == -1;
	}

	bool moveIsAboutToStart() {
		return distance == -1;
	}
	
	bool startMovement() {
		currentMove = currentKey;
		Vector2D currentPosition = mesh->getPosition();
		Vector2D destinationPosition = currentPosition + getFinishMoveVector();
		if (!canMove(currentPosition, destinationPosition)) {
			return false;
		}
		informStart(currentMove);
		distance = mesh->getMesh()->getSize();
		return true;
	}

	void applyNewPosition() {
		float moveSize = movementSpeed * distance * Time::getDeltaTime();
		currentDistance += moveSize;
		(*tr) = (*tr) + getMoveVector(moveSize);
	}

	bool movementIsFinished() {
		return currentDistance >= distance;
	}

	void finishMovement() {
		distance = -1;
		currentDistance = 0;
		currentKey = Direction::NONE;
		mesh->move(mesh->getPosition() + getFinishMoveVector());
		(*tr) = Transform(tr->getScale(), mesh->getMesh()->calculatePosition(mesh->getPosition()), 0);
		for (ControllerObserver* obs : observers) {
			obs->onMoveEnd();
		}
	}

	bool checkCollisionForObjectOut(GameObject* go, Vector2D pos) {
		if (!go) {
			return false;
		}
		MeshCollider* currentCollider = go->getComponent<MeshCollider>();
		return currentCollider && currentCollider->collidesOut(pos);
	}

	bool checkCollisionForObjectIn(GameObject* go, Vector2D pos) {
		if (!go) {
			return false;
		}
		MeshCollider* currentCollider = go->getComponent<MeshCollider>();
		return currentCollider && currentCollider->collidesIn(pos);
	}

	void informEnd() {
		for (ControllerObserver* obs : observers) {
			obs->onMoveEnd();
		}
	}

	void informCollide(GameObject* go) {
		for (ControllerObserver* obs : observers) {
			obs->onCollide(go);
		}
	}

	void informStart(Direction dir) {
		for (ControllerObserver* obs : observers) {
			obs->onMoveStart(dir);
		}
	}

};