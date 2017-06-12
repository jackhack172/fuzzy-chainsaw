#ifndef HITINFO
#define HITINFO

#include "color.h"

class HitInfo {

private:
	bool hitObject = false;
	Color color;

public:
    HitInfo() {
	}

	bool isHitObject() {
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
