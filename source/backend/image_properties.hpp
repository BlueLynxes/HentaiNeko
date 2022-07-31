#pragma once

#include <vector>
#include <string>
#include <map>

namespace hn
{
	namespace backend
	{
		// Builds image properties and then outputs the JSON to be saved in the picture
		class ImageProperties
		{
		public:
			// Constructors
			ImageProperties() = default;
			ImageProperties(const std::string& json);

			void parseJson(const std::string& json);
			std::string ExportJson();

		public:
			// Nested classes
			struct Setting
			{
				std::vector<std::string> locationProperties;
				std::vector<std::string> locationItems;
				std::string time;
				std::string season;
				std::string light;
			};

			struct Character
			{
			public:
				struct GeneralInfo
				{
					std::string brand;
					std::string characterName;
					std::string gender;
					std::vector<std::string> types;
				};
				struct BodyDescription
				{
					std::string skinTone;
					std::string weight;
					std::string hairColor;
					std::string hairStyle;
					std::string eyeColor;
					std::string eyeProperties;
					std::vector<std::string> bodyModifications;
					std::map<std::string, std::string> bodyProportions;
				};
				struct ClothingDescription
				{
					std::string outfitType;
					std::vector<std::string> accessories;
					std::vector<std::string> clothingItems;
					std::map<std::string, std::string> bodyPartsExposure;
					int bodyExposureRate;
				};

			public:
				GeneralInfo generalInfo;
				BodyDescription bodyDescription;
				ClothingDescription clothingDescription;
				std::vector<std::string> accesories;
				std::vector<std::string> bodyPosition;
				std::vector<std::string> facialExpressions;
				std::vector<std::string> actions;
			};

		public:
			// Properties
			// If the object is initialized from a JSON file only properties found in the
			// JSON get initialized, therefore always check for if variables are set before
			// reading them, or you may fall into SEGFAULTS!!
			std::vector<std::string> tags;
			std::vector<std::string> genres;
			std::vector<std::string> sceneType;
			std::vector<Character> characters;
			Setting setting;
		};
	}
}