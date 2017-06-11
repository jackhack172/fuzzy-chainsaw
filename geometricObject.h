#ifndef GEOMETRIC_OBJECT
#define GEOMETRIC_OBJECT

#include "color.h"
#include "ray.h"

class GeometricObject {

private:
	Color color;

public:
    virtual ~GeometricObject(){};

	virtual bool hitTest(Ray* ray, double &minDistance) = 0;

	Color getColor() {
		return color;
	}

	void setColor(Color color) {
		this->color = color;
	}
};

#endif
