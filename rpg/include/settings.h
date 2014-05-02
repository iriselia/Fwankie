#include "hge.h"
#include <string>

class Settings {
public:
	static bool load(const std::string& file_name);
	static bool save(const std::string& file_name);

};