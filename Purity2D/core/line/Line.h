#pragma once
#include "../vector2d/vector2d.hpp"
class Line {
private:	
	Vector2D beginVec;
	Vector2D endVec;
public:
	Line(Vector2D begin, Vector2D end) {
		this->beginVec = begin;
		this->endVec = end;
	}

	Vector2D begin() {
		return beginVec;
	}

	Vector2D end() {
		return endVec;
	}

	bool intersect(Line line);
};

