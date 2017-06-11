#ifndef HITINFO
#define HITINFO

#include "color.h"

class HitInfo {

private:
	bool hitObject;
	Color color;

public:
    HitInfo() {
	}

	double isHitObject() {
		return hitObject;
	}

	void setHitObject(bool hitObject) {
		this->hitObject = hitObject;
	}

	Color getColor() {
		return color;
	}

	void setColor(Color color) {
		this->color = color;
	}
};

#endif
