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
    Vector3* a = new Vector3(1.0, 2.3, 4.6);
    cout << "Hello world!" << endl;
    cout << "Vector a = " << a << endl;
    cout << *a+(*a)<< endl;

    Color background;
    background.setB(0.4);
    background.setR(0.5);

    World* world = new World(background);

    Color color;
    color.setB(0.7);

    //(Vector3* center, double radius, Color color) {
    Sphere* sphere = new Sphere(new Vector3(0,0,0),2,color);

    world->add(sphere);

    Orthogonal* ortho = new Orthogonal(new Vector3(0,0,-5), 0, new Vector2(5, 5));

    Raytracer* raytracer = new Raytracer();

//    raytracer->raytrace(world, ortho);
    raytracer->raytrace2(world, ortho);

    getchar();
    return 0;
}
