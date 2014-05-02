#include "settings.h"
#include <fstream>

bool Settings::load(const std::string& file_name) {
	HGE* hge = hgeCreate(HGE_VERSION);
	std::fstream settingsdata("resources\\" + file_name);
	if (settingsdata.is_open()) {
		char yolo[100];
		char *yololine = yolo;
		settingsdata.getline(yololine, 100);
		float x, y;
		x = strtof(yololine, &yololine);
		y = strtof(yololine, &yololine);
		
		hge->System_SetState(HGE_SCREENWIDTH, (int)x);
		hge->System_SetState(HGE_SCREENHEIGHT, (int)y);
		settingsdata.close();
	}
	return 0;
}
bool Settings::save(const std::string& file_name) { return 0; }