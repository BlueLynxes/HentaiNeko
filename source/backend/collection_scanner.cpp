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
	imagesPaths.clear();
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
			imagesPaths.push_back(file.path());
		}
	}
}

void hn::backend::CollectionScanner::threadedScan(Glib::Dispatcher& dispatcherSuccess, Glib::Dispatcher& dispatcherFailure)
{
	try
	{
		scan();
	}
	catch (const std::exception& e)
	{
		imagesPaths.clear();
		dispatcherFailure.emit();
	}
	dispatcherSuccess.emit();
}