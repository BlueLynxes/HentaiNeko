#pragma once

#include "image_properties.hpp"

namespace hn
{
	namespace backend
	{
		// Reads and saves user defined and standard tags
		class TagsConfig : public ImageProperties
		{
		public:
			TagsConfig(const std::string& jsonPath);
		};
	}
}