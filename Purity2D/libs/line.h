#pragma once
#include "vector2d.hpp"
class Line {
private:	
	Vector2D beginVec;
	Vector2D endVec;
public:
	/*!
		\brief Constructor of Line from two vectors from beginning to end
	*/
	Line(Vector2D begin, Vector2D end) {
		this->beginVec = begin;
		this->endVec = end;
	}

	/*!
		\brief Returns Vector2D which points to begin of Line
	*/
	Vector2D begin() {
		return beginVec;
	}

	/*!
		\brief Returns Vector2D which points to end of Line
	*/
	Vector2D end() {
		return endVec;
	}

	/*!
		\brief Moves Line by Vector2D
	*/
	Line operator+(Vector2D vector) {
		return Line(beginVec + vector, endVec + vector);
	}

	/*!
		\brief Moves Line by negated Vector2D
	*/
	Line operator-(Vector2D vector) {
		return Line(beginVec - vector, endVec - vector);
	}

	/*!
		\brief Scales line
	*/
	Line operator*(double scale) {
		return Line(beginVec * scale, endVec * scale);
	}

	Vector2D toVector() {
		return endVec - beginVec;
	}

	/*!
		\brief Checks if Line intersects (cross) with another Line
	*/
	bool intersect(Line line) {
		Vector2D a = line.begin();
		Vector2D b = line.end();
		Vector2D c = begin();
		Vector2D d = end();

		double x0 = a.getX();
		double x1 = b.getX();
		double x2 = c.getX();
		double x3 = d.getX();
		double y0 = a.getY();
		double y1 = b.getY();
		double y2 = c.getY();
		double y3 = d.getY();

		double s1_x = x1 - x0;
		double s2_x = x3 - x2;
		double s1_y = y1 - y0;
		double s2_y = y3 - y2;

		double determin = (s2_x * -1 * s1_y + s1_x * s2_y);

		if (determin == 0) {
			return false;
		}

		double s = (-s1_y * (x0 - x2) + s1_x * (y0 - y2)) / (-s2_x * s1_y + s1_x * s2_y);
		double t = (s2_x * (y0 - y2) - s2_y * (x0 - x2)) / (-s2_x * s1_y + s1_x * s2_y);;

		if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
			return true;
		}
		else {
			return false;
		}
	}
};

