#include <fstream>
#include <sstream>
#include "Assets/TextAsset.h"

string TextAsset::GetFile(string _path) {
	std::ifstream file;
	file.open(_path);
	assert(file.good() && "Unable to open text asset file");

	std::stringstream ss;
	ss << file.rdbuf();
	file.close();

	return ss.str();
}

TextAsset::TextAsset(string _path) : Asset(_path) {

}