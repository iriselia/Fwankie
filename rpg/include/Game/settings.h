#pragma once
#include "Core.h"
#include "hge.h"
#include <string>

class Settings {
public:
	static bool load(const std::tstring& file_name);
	static bool save(const std::tstring& file_name);

};