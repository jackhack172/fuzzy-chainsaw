#ifndef SPHERE
#define SPHERE

#include "vector3.h"
#include "color.h"
#include "geometricObject.h"
#include <math.h>

class Sphere: public GeometricObject {

private:
	Vector3* center;
	double radius;

public:
	Sphere(Vector3* center, double radius, Color color) {
		this->center = center;
		this->radius = radius;
		setColor(color);
	}

	~Sphere(){
	    delete center;
	}

	virtual bool hitTest(Ray* ray, double &minDistance) {
		double t = 0;
		Vector3* distance = ray->getOrigin()->subtract(*center);

		double a = ray->getDirection()->getSquareLenght();
		double b = distance->multiply(2)->dotProduct(*(ray->getDirection()));
		double c = distance->getSquareLenght() - radius * radius;
		double disc = b * b - 4 * a * c;

		if(disc < 0 ){
            return false;
		}

		double discSq = sqrt(disc);
		double denom = 2 * a;

		t = (-b - discSq) / denom;

		if(t < 0.0000001){
            t = (-b + discSq) / denom;
		}
		if(t < 0.0000001){
            return false;
		}

		minDistance = t;
		return true;
	}

};

#endif
