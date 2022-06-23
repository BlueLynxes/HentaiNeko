#include "image_properties.hpp"
#include <json/json.h>

#include <iostream>

namespace hn
{
	namespace backend
	{
		ImageProperties::ImageProperties(const std::string& json)
		{
			Json::Value root;
			// Parse JSON
			Json::CharReaderBuilder builder;
			JSONCPP_STRING err;
			const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
			if (!reader->parse(json.c_str(), json.c_str() + json.length(), &root, &err)) {
				std::cout << "error" << std::endl;
				std::cout << json << std::endl;
				throw std::exception();
			}

			// Populate Object
			// Since none of the JSON values are mandatory
			// there is no actual validation whatever
			// is present gets read
			// WARNING: Is the element is present, but the type is incorrect
			// this thing will crash (Jsoncpp will thow an exception)

			if (root["sceneType"].isArray())
			{
				Json::Value sceneType = root["sceneType"];
				for (Json::Value::ArrayIndex index = 0; index != sceneType.size(); index++) {
					this->sceneType.push_back(sceneType[index].asString());
				}
			}

			if (root["genres"].isArray())
			{
				Json::Value sceneType = root["genres"];
				for (Json::Value::ArrayIndex index = 0; index != sceneType.size(); index++) {
					this->genres.push_back(sceneType[index].asString());
				}
			}

			if (root["tags"].isArray())
			{
				Json::Value sceneType = root["tags"];
				for (Json::Value::ArrayIndex index = 0; index != sceneType.size(); index++) {
					this->tags.push_back(sceneType[index].asString());
				}
			}

			if (root["setting"].isObject())
			{
				ImageProperties::Setting imageSetting;
				if (root["setting"]["locationProperties"].isArray())
				{
					Json::Value locationProperties = root["setting"]["locationProperties"];
					for (Json::Value::ArrayIndex index = 0; index != locationProperties.size(); index++) {
						imageSetting.locationProperties.push_back(locationProperties[index].asString());
					}
				}
				if (root["setting"]["locationItems"].isArray())
				{
					Json::Value locationItems = root["setting"]["locationItems"];
					for (Json::Value::ArrayIndex index = 0; index != locationItems.size(); index++) {
						imageSetting.locationItems.push_back(locationItems[index].asString());
					}
				}
				if (root["setting"]["time"].isString())
				{
					imageSetting.time = root["setting"]["time"].asString();
				}
				if (root["setting"]["season"].isString())
				{
					imageSetting.season = root["setting"]["season"].asString();
				}
				if (root["setting"]["light"].isString())
				{
					imageSetting.light = root["setting"]["light"].asString();
				}
				this->setting = imageSetting;
			}
			
			if (root["characters"].isArray())
			{
				Json::Value charactersArray = root["characters"];
				for (Json::Value::ArrayIndex index = 0; index != charactersArray.size(); index++)
				{
					if (charactersArray[index].isObject())
					{
						ImageProperties::Character character;
						if (charactersArray[index]["generalInfo"].isObject())
						{
							ImageProperties::Character::GeneralInfo generalInfo;
							if (charactersArray[index]["generalInfo"]["brand"].isString())
							{
								generalInfo.brand = charactersArray[index]["generalInfo"]["brand"].asString();
							}
							if (charactersArray[index]["generalInfo"]["characterName"].isString())
							{
								generalInfo.characterName = charactersArray[index]["generalInfo"]["characterName"].asString();
							}
							if (charactersArray[index]["generalInfo"]["gender"].isString())
							{
								generalInfo.gender = charactersArray[index]["generalInfo"]["gender"].asString();
							}
							if (charactersArray[index]["generalInfo"]["type"].isString())
							{
								generalInfo.type = charactersArray[index]["generalInfo"]["type"].asString();
							}
							character.generalInfo = generalInfo;
						}
						if (charactersArray[index]["bodyDescription"].isObject())
						{
							ImageProperties::Character::BodyDescription bodyDescription;
							if (charactersArray[index]["bodyDescription"]["skinTone"].isString())
							{
								bodyDescription.skinTone = charactersArray[index]["bodyDescription"]["skinTone"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["weight"].isString())
							{
								bodyDescription.weight = charactersArray[index]["bodyDescription"]["weight"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["hairColor"].isString())
							{
								bodyDescription.hairColor = charactersArray[index]["bodyDescription"]["hairColor"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["hairStyle"].isString())
							{
								bodyDescription.hairStyle = charactersArray[index]["bodyDescription"]["hairStyle"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["eyeColor"].isString())
							{
								bodyDescription.eyeColor = charactersArray[index]["bodyDescription"]["eyeColor"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["eyeProperties"].isString())
							{
								bodyDescription.eyeProperties = charactersArray[index]["bodyDescription"]["eyeProperties"].asString();
							}
							if (charactersArray[index]["bodyDescription"]["bodyModifications"].isArray())
							{
								Json::Value bodyModificationsArray = charactersArray[index]["bodyDescription"]["bodyModifications"];
								for (Json::Value::ArrayIndex index = 0; index != bodyModificationsArray.size(); index++)
								{
									if (bodyModificationsArray[index].isString())
									{
										bodyDescription.bodyModifications.push_back(bodyModificationsArray[index].asString());
									}
								}
							}
							if (charactersArray[index]["bodyDescription"]["bodyProportions"].isObject())
							{
								for (auto const& bodyPartName : charactersArray[index]["bodyDescription"]["bodyProportions"].getMemberNames()) {
									if (charactersArray[index]["bodyDescription"]["bodyProportions"][bodyPartName].isString())
									{
										bodyDescription.bodyProportions.insert(std::pair<std::string, std::string>(bodyPartName,
											charactersArray[index]["bodyDescription"]["bodyProportions"][bodyPartName].asString()));
									}
								}
							}
							character.bodyDescription = bodyDescription;
						}
						if (charactersArray[index]["clothingDescription"].isObject())
						{
							ImageProperties::Character::ClothingDescription clothingDescription;
							if (charactersArray[index]["clothingDescription"]["outfitType"].isString())
							{
								clothingDescription.outfitType = charactersArray[index]["clothingDescription"]["outfitType"].asString();
							}
							if (charactersArray[index]["clothingDescription"]["accessories"].isArray())
							{
								Json::Value accessoriesArray = charactersArray[index]["clothingDescription"]["accessories"];
								for (Json::Value::ArrayIndex index = 0; index != accessoriesArray.size(); index++)
								{
									if (accessoriesArray[index].isString())
									{
										clothingDescription.accessories.push_back(accessoriesArray[index].asString());
									}
								}
							}
							if (charactersArray[index]["clothingDescription"]["clothingItems"].isArray())
							{
								Json::Value clothingItemsArray = charactersArray[index]["clothingDescription"]["clothingItems"];
								for (Json::Value::ArrayIndex index = 0; index != clothingItemsArray.size(); index++)
								{
									if (clothingItemsArray[index].isString())
									{
										clothingDescription.clothingItems.push_back(clothingItemsArray[index].asString());
									}
								}
							}
							if (charactersArray[index]["clothingDescription"]["bodyPartsExposure"].isObject())
							{
								for (auto const& bodyPartName : charactersArray[index]["clothingDescription"]["bodyPartsExposure"].getMemberNames()) {
									if (charactersArray[index]["clothingDescription"]["bodyPartsExposure"][bodyPartName].isString())
									{
										clothingDescription.bodyPartsExposure.insert(std::pair<std::string, std::string>(bodyPartName,
											charactersArray[index]["clothingDescription"]["bodyPartsExposure"][bodyPartName].asString()));
									}
								}
							}
							if (charactersArray[index]["clothingDescription"]["bodyExposureRate"].isInt())
							{
								clothingDescription.bodyExposureRate = charactersArray[index]["clothingDescription"]["bodyExposureRate"].asInt();
							}
							character.clothingDescription = clothingDescription;
						}
						if (charactersArray[index]["accessories"].isArray())
						{
							Json::Value accessoriesArray = charactersArray[index]["accessories"];
							for (Json::Value::ArrayIndex index = 0; index != accessoriesArray.size(); index++)
							{
								if (accessoriesArray[index].isString())
								{
									character.accesories.push_back(accessoriesArray[index].asString());
								}
							}
						}
						if (charactersArray[index]["bodyPosition"].isArray())
						{
							Json::Value bodyPositionArray = charactersArray[index]["bodyPosition"];
							for (Json::Value::ArrayIndex index = 0; index != bodyPositionArray.size(); index++)
							{
								if (bodyPositionArray[index].isString())
								{
									character.bodyPosition.push_back(bodyPositionArray[index].asString());
								}
							}
						}
						if (charactersArray[index]["facialExpressions"].isArray())
						{
							Json::Value facialExpressionsArray = charactersArray[index]["facialExpressions"];
							for (Json::Value::ArrayIndex index = 0; index != facialExpressionsArray.size(); index++)
							{
								if (facialExpressionsArray[index].isString())
								{
									character.facialExpressions.push_back(facialExpressionsArray[index].asString());
								}
							}
						}
						if (charactersArray[index]["actions"].isArray())
						{
							Json::Value actionsArray = charactersArray[index]["actions"];
							for (Json::Value::ArrayIndex index = 0; index != actionsArray.size(); index++)
							{
								if (actionsArray[index].isString())
								{
									character.actions.push_back(actionsArray[index].asString());
								}
							}
						}
						this->characters.push_back(character);
					}
				}
			}
		}

		std::string ImageProperties::ExportJson()
		{
			Json::Value root;

			Json::Value tags(Json::arrayValue);
			for (std::string& tag : this->tags)
			{
				tags.append(Json::Value(tag));
			}
			root["tags"] = tags;

			Json::Value genres(Json::arrayValue);
			for (std::string& genre : this->genres)
			{
				genres.append(Json::Value(genre));
			}
			root["genres"] = genres;

			Json::Value sceneType(Json::arrayValue);
			for (std::string& type : this->sceneType)
			{
				sceneType.append(Json::Value(type));
			}
			root["sceneType"] = sceneType;

			Json::Value setting = Json::Value(Json::objectValue);
			Json::Value settingLocationProperties = Json::Value(Json::arrayValue);
			for (std::string& property : this->setting.locationProperties)
			{
				settingLocationProperties.append(Json::Value(property));
			}
			setting["locationProperties"] = settingLocationProperties;

			Json::Value locationItems = Json::Value(Json::arrayValue);
			for (std::string& item : this->setting.locationItems)
			{
				locationItems.append(Json::Value(item));
			}
			setting["locationItems"] = locationItems;

			setting["time"] = this->setting.time;
			setting["season"] = this->setting.season;
			setting["light"] = this->setting.light;
			root["setting"] = setting;

			Json::Value characters = Json::Value(Json::arrayValue);
			for (auto character : this->characters)
			{
				Json::Value characterValue = Json::Value(Json::objectValue);

				Json::Value characterGeneralInfo = Json::Value(Json::objectValue);
				characterGeneralInfo["brand"] = character.generalInfo.brand;
				characterGeneralInfo["characterName"] = character.generalInfo.characterName;
				characterGeneralInfo["gender"] = character.generalInfo.gender;
				characterGeneralInfo["type"] = character.generalInfo.type;
				characterValue["generalInfo"] = characterGeneralInfo;

				Json::Value characterBodyDescription = Json::Value(Json::objectValue);
				characterBodyDescription["skinTone"] = character.bodyDescription.skinTone;
				characterBodyDescription["weight"] = character.bodyDescription.weight;
				characterBodyDescription["hairColor"] = character.bodyDescription.hairColor;
				characterBodyDescription["hairStyle"] = character.bodyDescription.hairStyle;
				characterBodyDescription["eyeColor"] = character.bodyDescription.eyeColor;
				characterBodyDescription["eyeProperties"] = character.bodyDescription.eyeProperties;

				Json::Value bodyModifications = Json::Value(Json::arrayValue);
				for (auto modification : character.bodyDescription.bodyModifications)
				{
					bodyModifications.append(Json::Value(modification));
				}
				characterBodyDescription["bodyModifications"] = bodyModifications;

				Json::Value bodyProportions = Json::Value(Json::objectValue);
				for (auto modification : character.bodyDescription.bodyProportions)
				{
					bodyProportions[modification.first] = modification.second;
				}
				characterBodyDescription["bodyProportions"] = bodyProportions;
				characterValue["bodyDescription"] = characterBodyDescription;

				Json::Value clothingDescription = Json::Value(Json::objectValue);
				clothingDescription["outfitType"] = character.clothingDescription.outfitType;

				Json::Value clothingDescriptionAccessories = Json::Value(Json::arrayValue);
				for (auto accessory : character.clothingDescription.accessories)
				{
					clothingDescriptionAccessories.append(Json::Value(accessory));
				}
				clothingDescription["accessories"] = clothingDescriptionAccessories;

				Json::Value clothingItems = Json::Value(Json::arrayValue);
				for (auto item : character.clothingDescription.clothingItems)
				{
					clothingItems.append(Json::Value(item));
				}
				clothingDescription["clothingItems"] = clothingItems;

				Json::Value bodyPartsExposure = Json::Value(Json::objectValue);
				for (auto bodyPart : character.clothingDescription.bodyPartsExposure)
				{
					bodyPartsExposure[bodyPart.first] = bodyPart.second;
				}
				clothingDescription["bodyPartsExposure"] = bodyPartsExposure;

				clothingDescription["bodyExposureRate"] = character.clothingDescription.bodyExposureRate;
				characterValue["clothingDescription"] = clothingDescription;

				Json::Value accessories = Json::Value(Json::arrayValue);
				for (auto accessory : character.accesories)
				{
					accessories.append(Json::Value(accessory));
				}
				characterValue["accessories"] = accessories;

				Json::Value bodyPosition = Json::Value(Json::arrayValue);
				for (auto position : character.bodyPosition)
				{
					bodyPosition.append(Json::Value(position));
				}
				characterValue["bodyPosition"] = bodyPosition;

				Json::Value facialExpressions = Json::Value(Json::arrayValue);
				for (auto expression : character.facialExpressions)
				{
					facialExpressions.append(Json::Value(expression));
				}
				characterValue["facialExpressions"] = facialExpressions;

				Json::Value actions = Json::Value(Json::arrayValue);
				for (auto action : character.actions)
				{
					actions.append(Json::Value(action));
				}
				characterValue["actions"] = actions;

				characters.append(characterValue);
			}
			root["characters"] = characters;

			Json::StreamWriterBuilder builder;
			const std::string imagePropertiesJsonString = Json::writeString(builder, root);
			return imagePropertiesJsonString;
		}
	}
}