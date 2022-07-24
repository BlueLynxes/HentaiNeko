#include "tags_config.hpp"
#include <fstream>
#include <sstream>

namespace hn::backend
{
	TagsConfig::TagsConfig(const std::string& jsonPath)
	{
		std::fstream jsonFile(jsonPath, std::ios::in);
		std::stringstream jsonContent;
		jsonContent << jsonFile.rdbuf();
		parseJson(jsonContent.str());
	}
}