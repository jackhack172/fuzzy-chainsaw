#ifndef VECTOR2
#define VECTOR2

class Vector2 {

private:
	double x;
	double y;

public:
	Vector2() {
	    x=y=0;
	}

	Vector2(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double getX() {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}
};

#endif
