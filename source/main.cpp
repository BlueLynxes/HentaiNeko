#include <gtkmm.h>
#include "backend/image_properties.hpp"
#include "gui/application.hpp"

#include <iostream>
#include "backend/collection_scanner.hpp"

int main(int argc, char* argv[])
{
    // TESTING STUFF START
    auto object = hn::backend::ImageProperties(R"(
{
    "sceneType": [
        "portrait"
    ],
    "setting": {
        "locationProperties": [
            "indoor"
        ],
        "locationItems": [
            "bed"
        ],
        "time": "",
        "season": "",
        "light": "white/bright"
    },
    "genres": [
    ],
    "tags": [
        "bunny-girl",
        "big-tits",
        "tits-dangling"
    ],
    "characters": [
        {
            "generalInfo": {
                "brand": "",
                "characterName": "",
                "gender": "female",
                "type": "bunny-girl&milf"
            },
            "bodyDescription": {
                "skinTone": "white/light",
                "weight": "thin",
                "hairColor": "blode/light",
                "hairStyle": "long/straight",
                "eyeColor": "blue&blue",
                "bodyModifications": [
                ],
                "bodyProportions": {
                    "breasts": "mid-large"
                }
            },
            "clothingDescription": {
                "outfitType": "bunny-girl",
                "accessories": [
                    "fake-ears/bunny",
                    "fake-tail/bunny"
                ],
                "clothingItems": [
                    "pantyhose"
                ],
                "bodyPartsExposure": {
                    "breast/right": "visible",
                    "breast/left": "visible",
                    "genitalia": "hidden",
                    "legs": "see-through"
                },
                "bodyExposureRate": 60
            },
            "accessories": [
            ],
            "bodyPosition": [
                "bending",
                "sitting"
            ],
            "facialExpressions": [
                "smiling/pervest",
                "licking-lips"
            ],
            "actions": [
            ]
        }
    ]
}
)");

    //std::cout << object.ExportJson(); // Works! :3

    hn::backend::CollectionScanner scanner = hn::backend::CollectionScanner("../resources");
    scanner.scan();

    // TESTING STUFF END
    hn::gui::Application app = hn::gui::Application();
    app.initInsertDataWindow();
    app.showInsertDataWindow();
    app.initAboutWindow();
    app.run();
    return 0;
}