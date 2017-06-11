#ifndef ORTHOGONAL
#define ORTHOGONAL

#include <math.h>
#include "ray.h"
#include "vector2.h"
#include "vector3.h"

class Orthogonal
{
private:
	Vector3* eyePosition;
	double angle;
	Vector2* cameraSize;

public:
    Orthogonal(Vector3* eye, double angle, Vector2* size){
        this->eyePosition = eye;
        this->angle = angle;
        this->cameraSize = size;
    }

    Ray* getRayTo(Vector2* pictureLocation){
        Vector3* direction = new Vector3(sin(angle), 0, cos(angle));
        direction = direction->getNormalizedVector();

        Vector2* offsetFromCenter = new Vector2(
                    pictureLocation->getX() * cameraSize->getX(),
                    pictureLocation->getY() * cameraSize->getY());

        Vector3* position = new Vector3(
                eyePosition->getX() + offsetFromCenter->getX() * cos(angle),
                eyePosition->getY() + offsetFromCenter->getY(),
                eyePosition->getZ() + offsetFromCenter->getX() * sin(angle));

        return new Ray(position, direction);
        //throw new System.NotImplementedException();
    }
};
#endif
