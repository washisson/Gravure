#include "Saver.hpp"
#include "Filter2d.hpp"
#include "Filter1d.hpp"
#include "ColorMap.hpp"
#include <SFML/Graphics.hpp>
// #include <random>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
// #include <stdint.h>

const double my_pi = 3.14159265358979, blurRadius = 50;
const char nameOfConfigFile[] = "Engrave.config";
bool t_save = false, t_autochange = true, t_fast_change = true;

bool readNameOfImageFile(std::string & nameOfImageFile){
	std::ifstream configFile(nameOfConfigFile);

	if(configFile.is_open()){
		getline(configFile, nameOfImageFile);
		return true;
	}
	return false;
}

int main(){
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	float blurSigma1 = 2, blurSigma2 = 2, blurSigma3 = 2;
	int w_width = 512, w_height = 512;
	bool t_start = true, t_draw = true;
	std::string nameOfImageFile;
	// std::mt19937_64 rnd(time(0));
	// std::uniform_real_distribution<> rnd_rl(0, 1);

	sf::Image WB_image;

	readNameOfImageFile(nameOfImageFile);
	WB_image.loadFromFile(nameOfImageFile);
	// WB_image.loadFromFile("1 - 512.png");
	// WB_image.loadFromFile("source images/1 - 1024.png");
	// WB_image.loadFromFile("IMG_20240614_192205.jpg");
	// WB_image.loadFromFile("3wb.png");
	// WB_image.loadFromFile("2color.png");
	w_width = WB_image.getSize().x, w_height = WB_image.getSize().y;

	sf::RenderWindow window(sf::VideoMode(w_width, w_height), "Printmaking");
	Saver saver;
	sf::Texture background_texture;
	sf::RectangleShape background(sf::Vector2f(w_width, w_height));

	background_texture.create(w_width, w_height);
	background.setTexture(& background_texture);

	background_texture.loadFromImage(WB_image);

	window.clear();

	window.draw(background);
	window.display();

	// sf::Clock timer;
	sf::Image resultImage;
	sf::Image testImage;
	sf::Image blurImage1, blurImage2, blurImage3;
	sf::Image frequencyDecompositionImage1, frequencyDecompositionImage2, frequencyDecompositionImage3;
	ColorMap mainColorMap(WB_image);
	ColorMap testColotMap;
	ColorMap frequencyDecompositionColorMap1, frequencyDecompositionColorMap2, frequencyDecompositionColorMap3;
	ColorMap blurColorMap1, blurColorMap2, blurColorMap3;

	GaussianFilter1d filter1(blurSigma1), filter2(blurSigma2), filter3(blurSigma3);
	// ColorMap cm2(cm1.useFilter1d(GF1d));
	// resultImage = cm1.getWBImage();
	blurColorMap1 = mainColorMap.useFilter1d(filter1);
	blurColorMap2 = blurColorMap1.useFilter1d(filter1);
	blurColorMap3 = blurColorMap2.useFilter1d(filter1);
	blurImage1 = blurColorMap1.getWBImage();
	blurImage2 = blurColorMap2.getWBImage();
	blurImage3 = blurColorMap3.getWBImage();

	frequencyDecompositionColorMap1 = (mainColorMap - blurColorMap1) / 2 + 0.5;
	// frequencyDecompositionColorMap1.separate();
	frequencyDecompositionImage1 = frequencyDecompositionColorMap1.getWBImage();
	frequencyDecompositionColorMap2 = (blurColorMap1 - blurColorMap2) / 2 + 0.5;
	frequencyDecompositionImage2 = frequencyDecompositionColorMap2.getWBImage();
	frequencyDecompositionColorMap3 = (blurColorMap2 - blurColorMap3) / 2 + 0.5;
	frequencyDecompositionImage3 = frequencyDecompositionColorMap3.getWBImage();
	resultImage = WB_image;
	// resultImage = createEngravingEffect(WB_image);

	testColotMap = frequencyDecompositionColorMap1;
	// testColotMap = mainColorMap;
	testColotMap.separate();
	testImage = testColotMap.getWBImage();

	for(int j = 0; j < w_height / 2; ++ j){
		sf::Color temp_color(sf::Color::Red);

		resultImage.setPixel(38 + abs(j % 8 - 4), j + 8, temp_color);

	}
	if(t_save){
		saver.set_image(resultImage);
		saver.save_image();
	}
	background_texture.loadFromImage(resultImage);
	window.clear();

	window.draw(background);
	window.display();


	while (window.isOpen()){
		sf::Event event;
		int numberOfImage = 1, oldNumberOfImage;
		bool tReloadImage = false, tReloadTexture = false, tReloadDrawn = false;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				t_start = true;
			if (event.type == sf::Event::KeyPressed)
				switch(event.key.code){
				case sf::Keyboard::Num0:
					numberOfImage = 0;
					tReloadImage = true;
					break;
				case sf::Keyboard::Num1:
					numberOfImage = 1;
					tReloadImage = true;
					break;
				case sf::Keyboard::Num2:
					numberOfImage = 2;
					tReloadImage = true;
					break;
				case sf::Keyboard::Num3:
					numberOfImage = 3;
					tReloadImage = true;
					break;
				case sf::Keyboard::Q:
					numberOfImage = 10;
					tReloadImage = true;
					break;
				case sf::Keyboard::W:
					numberOfImage = 20;
					tReloadImage = true;
					break;
				case sf::Keyboard::E:
					numberOfImage = 30;
					tReloadImage = true;
					break;
				case sf::Keyboard::A:
					numberOfImage = 15;
					tReloadImage = true;
					break;
				}
		}

		if(tReloadImage && numberOfImage != oldNumberOfImage){
			tReloadImage = false;
			tReloadDrawn = true;
			switch(numberOfImage){
			case 0:
				background_texture.loadFromImage(WB_image);
				break;
			case 1:
				background_texture.loadFromImage(blurImage1);
				break;
			case 2:
				background_texture.loadFromImage(blurImage2);
				break;
			case 3:
				background_texture.loadFromImage(blurImage3);
				break;
			case 10:
				background_texture.loadFromImage(frequencyDecompositionImage1);
				break;
			case 20:
				background_texture.loadFromImage(frequencyDecompositionImage2);
				break;
			case 30:
				background_texture.loadFromImage(frequencyDecompositionImage3);
				break;
			case 15:
				background_texture.loadFromImage(testImage);
				break;
			}

			oldNumberOfImage = numberOfImage;
		}
		else if(tReloadImage)
			tReloadImage = false;

		if(t_start){
			t_start = false;

		}
		if(tReloadDrawn){
			tReloadDrawn = false;

			window.clear();
	
			window.draw(background);
			window.display();
		}
		// timer.restart();

	}

	return 0;
}
