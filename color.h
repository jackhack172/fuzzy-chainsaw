#ifndef COLOR
#define COLOR

class Color {

private:
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;

public:
	double getR() {
		return r;
	}

	void setR(double r) {
		this->r = r;
	}

	double getG() {
		return g;
	}

	void setG(double g) {
		this->g = g;
	}

	double getB() {
		return b;
	}

	void setB(double b) {
		this->b = b;
	}
};

#endif
