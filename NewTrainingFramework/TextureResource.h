#pragma once
#include <string>

struct TextureResource {
	std::string path;
	std::string type;
	std::string file;
	std::string minFilter;
	std::string magFilter;
	std::string wrapS;
	std::string wrapT;
};