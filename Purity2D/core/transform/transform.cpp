#include "transform.hpp"

Transform const Transform::base = Transform(Vector2D(0, 0), Vector2D(0, 0), Rotation(0));

bool Transform::collides(Transform transform) {
	vector<Line> lines = getLines();
	for (Line i : lines) {
		if (transform.collides(i)) {
			return true;
		}
	}
	if (isInside(transform)) {
		return true;
	}

	if (transform.isInside(*this)) {
		return true;
	}

	return false;
}

bool Transform::isInside(Transform transform) {
	vector<Line> lines = transform.getLines();
	Line positionLine = Line(Vector2D::ZERO, getPosition());
	int collisionCount = 0;
	for (Line i : lines) {
		if (i.intersect(positionLine)) {
			collisionCount++;
		}
	}
	return collisionCount % 2 == 1;
}
