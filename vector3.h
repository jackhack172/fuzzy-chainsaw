#ifndef VECTOR3
#define VECTOR3

#include <iostream>

using namespace std;

class Vector3 {

private:
	double x;
	double y;
	double z;

public:
	Vector3() {
	    x=y=z=0;
	}

	Vector3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3* add(Vector3 vector);
	Vector3* subtract(Vector3 vector);
	Vector3* multiply(double value);
	Vector3* divide(double value);
	Vector3* getNormalizedVector();
	Vector3* vectorProduct(Vector3 vectorA, Vector3 vectorB);

	double dotProduct(Vector3 vector);
	double getLenght() ;
	double getSquareLenght();

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	double getZ() const {
		return z;
	}

	void setZ(double z) {
		this->z = z;
	}

	friend ostream & operator<< (ostream &output, const Vector3 &v) {
        return output << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" <<endl;
    }

    friend ostream & operator<< (ostream &output, const Vector3 *v) {
        return output << "(" << v->getX() << ", " << v->getY() << ", " << v->getZ() << ")" <<endl;
    }

    Vector3 operator+ ( Vector3 v){
        return Vector3(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
    }
};

#endif
