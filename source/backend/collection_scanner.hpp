#pragma once

#include <vector>
#include <string>
#include <filesystem>

namespace hn
{
	namespace backend
	{
		class CollectionScanner
		{
		public:
			CollectionScanner() = delete;
			CollectionScanner(const std::string& entryPoint);

			void changeEntryPoint(const std::string& entryPoint);
			void scan();

			std::filesystem::path entryPointPath;
			std::vector<std::string> imagesPaths;
		};
	}
}