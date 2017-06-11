#include "Vector3.h"
#include <math.h>

Vector3* Vector3::add(Vector3 vector) {
	return new Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3* Vector3::subtract(Vector3 vector) {
	return new Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3* Vector3::multiply(double value) {
	return new Vector3(x * value, y * value, z * value);
}

Vector3* Vector3::divide(double value) {
	if (value != 0) {
		return new Vector3(x / value, y / value, z / value);
	} else {
		return new Vector3();
	}
}

// Iloczyn skalarny
double Vector3::dotProduct(Vector3 vector) {
	return (x * vector.x + y * vector.y + z * vector.z);
}

// Iloczyn wektorowy
Vector3* Vector3::vectorProduct(Vector3 vectorA, Vector3 vectorB) {
	return new Vector3(vectorA.y * vectorB.z - vectorA.z * vectorB.y,
			vectorA.z * vectorB.x - vectorA.x * vectorB.z,
			vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}

double Vector3::getLenght() {
	return sqrt(x * x + y * y + z * z);
}

double Vector3::getSquareLenght() {
	return (x * x + y * y + z * z);
}

Vector3* Vector3::getNormalizedVector() {
	return divide(getLenght());
}

