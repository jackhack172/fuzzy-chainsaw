#ifndef CAMERA
#define CAMERA

#include "ray.h"
#include "vector2.h"

abstract class Camera {

public:
	virtual Ray getRayTo(Vector2 );
}

#endif
