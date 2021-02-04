#include <iostream>
#include <istream>
#include <sstream>
#include "map_segment.hpp"

char MapSegment::VERTICAL_BORDER_CHAR = '|';
char MapSegment::HORIZONTAL_BORDER_CHAR = '=';
char MapSegment::PORTAL_CHAR = '@';

MapSegment::MapSegment(int height, int width)
    : mHeight(height), mWidth(width)
    , mPortalY{(mHeight - 1) / 2}
    , mPortalX{(mWidth - 1) / 2}
{

//mapSegment -> now the model class

}


//void MapSegment::setMapSegment(std::vector<std::string> &mapsegment) {
//    mapSegments = mapsegment;
//}
//
//std::vector<std::string> MapSegment::getMapSegment() {
//    return mapSegments;
//}
//void MapSegment::setPortals(std::vector<std::string> &myportals) {
//    portals = myportals;
//}
//
//std::vector<std::string> MapSegment::getPortals() {
//    return mapSegments;
//}

//model class basically
//void MapSegment::createModel(std::vector<std::string> &modelVector) {
//    std::stringstream ss;
//    for(unsigned i = 0; i < modelVector.size(); i++) {
//        currLine = modelVector[i];
//
//        //        std::cout << "model made" << "\n";
////        std::cout << modelVector[i] << "\n";
//        if(i == 0) {
//            mapSegindex = std::stoi(currLine);
//        }
//        if(i == 1) {
//            ss.str(currLine);
//            ss >> playerStartHeight >> playerStartWidth;
//            pStartHeight = std::stoi(playerStartHeight);
//            pStartWidth = std::stoi(playerStartWidth);
//            ss.str("");
//            ss.clear();
////            std::cout << "now at H:" << playerStartHeight << " " << playerStartWidth << "\n";
//        }
//        if(i == 2){
//            playerOrientation = currLine;
//            if (playerOrientation == "left")
//                playerOrientation = "<";
//            if (playerOrientation == "right")
//                playerOrientation = ">";
//            if (playerOrientation == "down")
//                playerOrientation = "v";
//            if (playerOrientation == "up")
//                playerOrientation = "^";
//
//        }
//        if(currLine[0] == 'M') { //map segments
//            mapSegments.push_back(currLine);
//        }if(currLine[0] == 'B') { // buildings
//            buildings.push_back(currLine);
//        }if(currLine[0] == 'P') // portals
//            portals.push_back(currLine);
//        if(currLine[0] == 'I') { // items
//            items.push_back(currLine);
////            std::cout << "PRINT VIEW ITEMS:" << currLine << "\n";
//        }if(currLine[0] == 'N'){
//            ss.str(currLine);
//            ss >> garb >> tempMove;
//            moves = std::stoi(tempMove);
//            ss.str("");
//            ss.clear();
//            //            Moves = std::stoi(currLine);
//        }
//
//
//
//        ss.str("");
//        ss.clear();
//
//    }
//    //set these items
//    setMapSegment(mapSegments);
////    setBuildings(buildings);
//    setPortals(portals);
////    setItem(items);
//
//
//
//
//
//
//
//
//
//
//
//}