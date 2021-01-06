#pragma once

#include <vector>
#include <algorithm>

#include "component.hpp"
#include "gameObject.hpp"
#include "transform.hpp"
#include "meshHolder.hpp"
#include "controllerObserver.hpp"
#include "meshController.hpp"
#include "meshScene.hpp"

using namespace std;

class PathData {
public:
	vector < Vector2D > path;
	bool foundPlayer;

	PathData() {
		this->path = {};
		this->foundPlayer = false;
	}

	PathData(vector<Vector2D> path, bool foundPlayer) {
		this->path = path;
		this->foundPlayer = foundPlayer;
	}
};

class MeshAi : public Component, public ControllerObserver {
private:
	MeshScene* scene;
	MeshHolder* playerPosition;
	GameObject** player;
	MeshHolder* mesh = nullptr;
	Vector2D lastPlayerPosition = Vector2D::ZERO;
	PathData currentPath;
	MeshController* ctrl = nullptr;
	int vision;

	vector<Vector2D> visitedTiles;
public:
	MeshAi(MeshScene* scene, int vision) {
		this->scene = scene;
		this->vision = vision;
	}

	void onGetOtherComponent(Component* component) {
		this->storeIfIsInstance(&mesh, component);
		if (ctrl == nullptr) {
			this->storeIfIsInstance(&ctrl, component);
		}
		if (ctrl == component) {
			ctrl->subscribe(this);
		}
	}

	void onUpdate() {
		/*if (!currentPath.foundPlayer) {
			recalculatePath();
			startMovement();
		}*/
	}

	void onDelete() {
		ctrl->unsubscribe(this);
	}

	void onMoveEnd() {
		/*currentPath.path.erase(currentPath.path.begin());
		if (getPlayerPosition() != lastPlayerPosition) {
			recalculatePath();
		}
		startMovement();*/
	}

	void onCollide() {
		/*recalculatePath();
		startMovement();*/
	}

private:
	void recalculatePath() {
		/*lastPlayerPosition = getPlayerPosition();
		visitedTiles.clear();
		currentPath = runToAdjacentTiles(mesh->getPosition(), 0);

		vector<Vector2D> layerOfTiles;
		vector<Vector2D> visitiedTiles;
		layerOfTiles.push_back(mesh->getPosition());

		for (int i = 0; i < vision; i++) {
			visitedTiles
			layerOfTiles
		}*/
	}

	Vector2D getPlayerPosition() {
		if (player == nullptr) {
			player = scene->getPlayer();
		}

		if (playerPosition == nullptr) {
			playerPosition = (*player)->getComponent<MeshHolder>();
		}

		return playerPosition->getPosition();
	}

	PathData findPathInPlace(Vector2D prevTile, Vector2D tile, int len) {
		if (len > vision) {
			return PathData({}, false);
		}
		if (lastPlayerPosition == tile) {
			return PathData({}, true);
		}
		for (Vector2D t : visitedTiles) {
			if (tile == t) {
				return PathData({}, false);
			}
		}
		visitedTiles.push_back(tile);
		bool collides = !ctrl->canMove(prevTile, tile);
		if (collides) {
			return PathData({}, false);
		}

		return runToAdjacentTiles(tile, len);
	}

	PathData runToAdjacentTiles(Vector2D tile, int len) {
		vector<PathData> paths;
		paths.push_back(findPathInPlace(tile, tile + Vector2D::LEFT, len + 1));
		paths.push_back(findPathInPlace(tile, tile + Vector2D::RIGHT, len + 1));
		paths.push_back(findPathInPlace(tile, tile + Vector2D::UP, len + 1));
		paths.push_back(findPathInPlace(tile, tile + Vector2D::DOWN, len + 1));

		std::remove_if(paths.begin(), paths.end(), [](PathData d) {
			return d.foundPlayer; 
		});

		if (paths.size() == 0) {
			return PathData({}, false);
		}

		int shortestPathLenght = -1;
		int indexOfShortestPath = -1;
		int currentIndex = 0;
		for (PathData data : paths) {
			if (shortestPathLenght == -1 || data.path.size() < shortestPathLenght) {
				shortestPathLenght = data.path.size();
				indexOfShortestPath = currentIndex;
			}
			currentIndex++;
		}

		paths.at(indexOfShortestPath).path.push_back(tile);

		return paths.at(indexOfShortestPath);
	}

	void startMovement() {
		Direction dir = findDirection();

		if (dir == Direction::NONE) {
			currentPath.foundPlayer = false;
			return;
		}

		ctrl->move(dir);
	}

	Direction findDirection() {
		Vector2D destination = currentPath.path.at(0);
		Vector2D currentPosition = mesh->getPosition();

		if (destination.getX() - currentPosition.getX() == 1) {
			return Direction::RIGHT;
		}

		if (destination.getX() - currentPosition.getX() == -1) {
			return Direction::LEFT;
		}

		if (destination.getY() - currentPosition.getY() == 1) {
			return Direction::DOWN;
		}

		if (destination.getX() - currentPosition.getX() == 1) {
			return Direction::UP;
		}

		return Direction::NONE;
	}
};