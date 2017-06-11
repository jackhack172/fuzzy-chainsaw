#ifndef WORLD
#define WORLD

#include <vector>
#include "color.h"
#include "geometricObject.h"
#include "hitInfo.h"
#include "ray.h"

class World {

private:
	vector<GeometricObject*> objects;
	Color background;

public:
    World(Color background){
        this->background = background;
    }

    void add(GeometricObject* object){
        objects.push_back(object);
    }

    HitInfo* traceRay(Ray* ray)
    {
        HitInfo* result = new HitInfo();
        double minimalDistance = ray->getHuge(); // najbli¿sze trafienie
        double hitDistance = 0; // zmienna pomocnicza, ostatnia odleg³oœæ

        for(int i = 0; i < objects.size(); i++ ){
            GeometricObject* obj = objects[i];
            if (obj->hitTest(ray, hitDistance) &&
                hitDistance < minimalDistance)
            {
                minimalDistance = hitDistance; // nowa najmniejsza odleg³oœæ
                result->setHitObject(true); // trafiono obiekt
                result->setColor(obj->getColor()); // zapisz kolor trafionego obiektu
            }
        }
        return result;
    }

    Color getBackgroundColor(){
        return background;
    }
};

#endif
