#include <iostream>
#include <ctime>
using namespace std;

enum Estate
{
	OFF_STATE,
	ON_STATE,
	MAKING_PHOTO_STATE,
	READING_COORDINATES_STATE,
	CALCULATING_STATE,
};

enum class event
{
	press_on,
	press_off,
	make_photo,
	read_coordinates,
	calculate,
};

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
		Photo new_photo;
		return new_photo;
	}
};

class Coordinates {
private:
	int x;
	int y;
public:
	Coordinates() {
		x = 0;
		y = 0;

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

class RealDetector : public Detector {
	Coordinates Detect(bool i, Photo& ph) override {
		if (i) {
			Coordinates cloudCoordinates;			//Даем реальные значения для облака с помощью openCV
			return cloudCoordinates;
		}
		else {
			Coordinates sunCoordinates;			//Даем реальные значения для солнца с помощью openCV
			return sunCoordinates;
		}
	}
	// вычисляются реальные значения координат
};
class mainPC {
private:
	int time;
	Photo photo1;
	Photo photo2;
	Generator gen1;
	Camera cam;
public:


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
		cout << "Press 1, if you want real analyze. Press 0, if you want random" << endl;
		char choose_char;
		cin >> choose_char;
		bool choose;
		if (choose_char == '0')
			choose = false;
		else if (choose_char == '1')
			choose = true;
		else {
			cout << "Wrong input" << endl;
			exit(0);
		}
		if (choose) {
			Detector* det = new RealDetector();
			// ищет реальные объекты с помощью openCV
			Coordinates sunCoordinates1 = det->Detect(false, ph1);
			cout << sunCoordinates1.getXCoordinates() << endl;
			Coordinates sunCoordinates2 = det->Detect(false, ph2);
			Coordinates cloudCoordinates1 = det->Detect(true, ph1);
			Coordinates cloudCoordinates2 = det->Detect(true, ph2);
		}
		else {
			Detector* det = new VirtualDetector();
			Coordinates sunCoordinates1 = det->Detect(false, ph1);
			Coordinates sunCoordinates2 = det->Detect(false, ph2);
			Coordinates cloudCoordinates1 = det->Detect(true, ph1);
			Coordinates cloudCoordinates2 = det->Detect(true, ph2);
		}
	}

	void start() {
		photo1 = getPhoto();
		photo2 = getPhoto();


		predictWeather(photo1, photo2);
	}
};

int main() {
	mainPC Computer;
	Computer.start();

	return 0;
}

