#include "collection_scanner.hpp"
#include <algorithm>
#include <string>
#include <iostream>

hn::backend::CollectionScanner::CollectionScanner(const std::string& entryPoint)
{
	entryPointPath = entryPoint;
}

void hn::backend::CollectionScanner::changeEntryPoint(const std::string& entryPoint)
{
	entryPointPath = entryPoint;
}

void hn::backend::CollectionScanner::scan()
{
	std::array<std::string, 3> supportedTypes 
	{
		".JPG", ".JPEG",
		".PNG"
	};

	for (const auto& file : std::filesystem::recursive_directory_iterator(entryPointPath))
	{
		std::string extension = file.path().extension();
		std::transform(extension.begin(), extension.end(), extension.begin(), ::toupper);
		if (std::find(supportedTypes.begin(), supportedTypes.end(), extension) != supportedTypes.end())
		{
			std::cout << file.path() << std::endl;
			imagesPaths.push_back(file.path());
		}
	}
}