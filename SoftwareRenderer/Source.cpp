#include <iostream>
#include <fstream>
#include <vector>


void PrintPPM(){}

int main() {
	// Image

	int image_width = 512;
	int image_height = 512;


	// Render
	std::ofstream myfile;
	myfile.open("PPM_Example.ppm");
	// P3 defines the type of PPM file: colors are in ASCII, then a line each for the image width and height
	myfile << "P3" << std::endl;
	myfile << image_width << std::endl;
	myfile << image_height << std::endl;
	// 255 defined as max color intensity
	myfile << "255" << std::endl;

	std::vector<std::vector<int>> imageContainer(image_height, std::vector<int>(image_width, 0));
	
	int x0, y0;
	int x1, y1;
	
	x0 = 10;
	y0 = 10;
	
	x1 = 200;
	y1 = 100;

	int x;
	int y = y0;

	float deltaX, deltaY;
	float m, c;

	deltaX = x1 - x0;
	deltaY = y1 - y0;

	m = deltaY / deltaX;
	c = y0 / (m * x0);
	
	float targetY;

	for (x = x0; x < x1; x++) {
		imageContainer[x][y] = 255;

		targetY = (m * x) + c;
		while (y < targetY) {
			y = y + 1;
			imageContainer[x][y] = 255;
		}
	}
	
	
	for (int j = 0; j < image_height; j++) {
		std::cerr << "\rScanlines remaining: " << image_height - j - 1 << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {

			int ir = 0;
			int ig = 0;
			int ib = 0;

			if (imageContainer[i][j] > 0) {
				ir = 255;
				ig = 255;
				ib = 255;
			}
			myfile << ir << ' ' << ig << ' ' << ib << std::endl;
		}
	}

	std::cerr << "\nDone.\n";

	system("pause");
	myfile.close();
	return 0;
}