#ifndef RAY
#define RAY

#include <iostream>
#include <limits>
#include "vector3.h"

using namespace std;

class Ray {

private:
    Vector3* origin;
    Vector3* direction;

public:

    const double epsilon = 0.00001;
    const double huge = std::numeric_limits<double>::max();
    // << "double: " << std::defaultfloat << std::numeric_limits<double>::max()

    Ray(Vector3* origin, Vector3* direction) {
        this->origin = origin;
        this->direction = direction->getNormalizedVector();
    }

    Vector3* getOrigin() const {
		return origin;
	}

	void setOrigin(Vector3* origin) {
		this->origin = origin;
	}

	Vector3* getDirection() const {
		return direction;
	}

	void setDirection(Vector3* direction) {
		this->direction = direction;
	}

	double getHuge(){
        return huge;
	}

};

#endif
