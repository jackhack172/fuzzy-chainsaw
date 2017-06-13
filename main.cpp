#include <iostream>
#include "vector3.h"
#include "vector2.h"
#include "ray.h"
#include "world.h"
#include "sphere.h"
#include "orthogonalCamera.h"
#include "raytracer.h"

using namespace std;

int main()
{
    Color background;
    background.setB(0.4);
    background.setR(0.5);

    World* world = new World(background);

    Color color;
    color.setB(0.7);

    Sphere* sphere = new Sphere(new Vector3(0,0,0),2,color);

    world->add(sphere);

    Orthogonal* ortho = new Orthogonal(new Vector3(0,0,-5), 0, new Vector2(5, 5));

    Raytracer* raytracer = new Raytracer();
    raytracer->raytrace(world, ortho);

    getchar();
    return 0;
}
