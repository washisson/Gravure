#ifndef SAVER_LIB
#define SAVER_LIB

#include "FilesystemSolution.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>

class Saver{
private:
	bool t_dir = false;
	int image_number = 0;
	std::string dir_name;
	sf::Image image;

	void gen_dir_name(){
		dir_name = "save_" + std::to_string( (long long) (time(0) - 16e8));
	}

	std::string get_next_image_name(){
		check_dir();
		return dir_name + "/resulte " + std::to_string(++ image_number) + ".png"; 
	}

	void check_dir(){
		if(!t_dir){
			gen_dir_name();
			#ifdef FOR_LINUX
				std::filesystem::create_directory(dir_name);
			#endif
			#ifdef FOR_WINDOWS
				mkdir(dir_name.c_str());
			#endif
			t_dir = true;
		}
	}
public:
	void save_image(){
		image.saveToFile(get_next_image_name());
	}

	void set_image(const sf::Image & image){
		this->image = image;
	}
};

#endif