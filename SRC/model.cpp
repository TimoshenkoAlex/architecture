#include <iostream>
#include <ctime>
using namespace std;

class Generator {
private:
	bool condition;
public:
	void switchCondition() {
		condition = !condition;
	}
	bool getCondition() {
		return condition;
	}
};

class Photo {
private:
	int width;
	int height;
	int brightness;

public:
	Photo() {
		width = 500;
		height = 500;
		brightness = 20;
	}
	Photo(int widthValue, int heightValue, int brightnessValue) {
		width = widthValue;
		height = heightValue;
		brightness = brightnessValue;
	}
	int getWidth() {
		return width;
	}
	
	void setWidth(int value){
		width = value;
		}

	int getHeight() {
		return height;
	}

	void setHeight(int value){
		height = value;
	}

	int getBrightness() {
		return brightness;
	}

	void setBrightness(int value){
		brightness = value;
	}
};

class Camera {
private:
	int condition;				// 0 - выключена, 1 - готова к работе, 2 - ожидание;
public:
	Photo makePhoto() {

	}
};

class Coordinates {
private:
	int x;
	int y;
public:
	Coordinates() {

	}
	Coordinates(int xValue, int yValue) {
		x = xValue;
		y = yValue;
	}
	int getXCoordinates() {
		return x;
	}
	int getYCoordinates() {
		return x;
	}
	void setCoordinates(int x_value, int y_value) {
		x = x_value;
		y = y_value;
	}
};


class Detector {
public:
	virtual Coordinates Detect(bool i, Photo& ph) {
		Coordinates h(0, 0);
		return h;
	}
};

class VirtualDetector : public Detector {
public:
	Coordinates Detect(bool i, Photo& ph) override {
		srand(time(NULL));
		if (i){
			Coordinates cloudCoordinates = Coordinates(rand() % (ph.getWidth() + 1), rand() % (ph.getHeight() + 1));			//Даем рандомные значения для облака
			return cloudCoordinates;
		}
		else {
			Coordinates sunCoordinates = Coordinates(rand() % (ph.getWidth() + 1), rand() % (ph.getHeight() + 1));			//Даем рандомные значения для солнца
			return sunCoordinates;
		}
	}

};
class mainPC {
private:
	int time;
	Photo photo1;
	Photo photo2;
	Generator gen1;
	Camera cam;
public:
	mainPC() {

	}

	void setTime(int t) {
		time = t;
	}

	int getTime() {
		return time;
	} 

	void switchGenerator() {
		gen1.switchCondition();
	}

	Photo getPhoto() {
		Photo ph;
		ph =  cam.makePhoto();
		return ph;
	}

	void predictWeather(Photo &ph1, Photo &ph2) {
		Detector* det = new VirtualDetector();
		Coordinates sunCoordinates1 = det->Detect(true, ph1);
		cout << sunCoordinates1.getXCoordinates() << endl;
		Coordinates sunCoordinates2 = det->Detect(true, ph2);
		Coordinates cloudCoordinates1 = det->Detect(false, ph1);
		Coordinates cloudCoordinates2 = det->Detect(false, ph2);
	}

	void start() {
		predictWeather(photo1, photo2);
	}
};

int main() {
	mainPC Computer;
	Computer.start();

	return 0;
}

