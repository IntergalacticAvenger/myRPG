#include "game.hpp"
#include "curses_view.hpp"
#include "curses_controller.hpp"
#include "print_view.hpp"
#include "print_controller.hpp"

#include <ncurses.h>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

//#include <libgen.h>
//#include <unistd.h>
//#include <limits.h>
// CSIF to copy and run
// g++ -g -std=c++11  main.cpp  item.cpp  map_segment.cpp  curses_controller.cpp  print_controller.cpp  curses_view.cpp  print_view.cpp  game.cpp  view.cpp  building.cpp -o main -lcurses && ./main


//i left comments about how i went about utilzing the classes in printview.cpp

const int Game::MIN_VIEW_HEIGHT = 15;
const int Game::MIN_VIEW_WIDTH = 15;
const char Game::HERO_ICON_LEFT = '<';
const char Game::HERO_ICON_RIGHT = '>';
const char Game::HERO_ICON_UP = '^';
const char Game::HERO_ICON_DOWN = 'v';



Game::Game(const std::string& filename, InterfaceType interfaceType)
        : mView{nullptr}
        , mController{nullptr}
        , mInterfaceType{interfaceType}
{
//    InterfaceType *myInterface = new InterfaceType(interfaceType);
    mInterface = interfaceType;
    if(interfaceType == InterfaceType::Curses ){
//        std::cout << "curses mode" << "\n";
        goto readFile;


    }else if(interfaceType == InterfaceType::Print){

    readFile:
    //    std::cout << filename << "\n";
    //    std::string newFileName = "/" + filename;
        std::ifstream file(filename); // GAME FILE LOADED HERE
        int iteration = 0;
        std::string currLine;
        std::string temp, tempLvl;

        if(file.is_open()){
            while(std::getline(file,currLine)){ //read line by line of the GAME_INPUT FILE
    //            printf("%s\n",currLine.c_str());
                std::istringstream stream(currLine);
                if(iteration == 0)
                    stream >> height >> width;
                if(iteration == 1)
                    stream >> tempLvl;
                if(iteration >= 2) {
                    stream >> temp;
                    levelFiles.push_back(temp); //storing the relative paths in this vector levelFiles
                }
                iteration++;
            }
        }
        file.close(); //close GAME_INPUT FILE
        file.clear();

        totalLevels = std::stoi(tempLvl);

    //    std::cout << "h  " << height << "w  " << width << "level  " << totalLevels << "\n";
        std::string currentLevelFile = levelFiles[currLVL-1]; //this is the file we are going to load
    //    char buf[PATH_MAX]; /* PATH_MAX incudes the \0 so +1 is not required */


    //    char resolved_path[PATH_MAX];
    //    realpath(filename.c_str(), resolved_path);
    //    printf("\n%s\n",resolved_path);
    //    std::string path = resolved_path;
    //    std::string s(resolved_path);
    //    std::vector<std::string> meme;
    //    meme.push_back(s);
    //    std::cout << meme[0] << "\n";
    //    std::string x = meme[0];
    //    std::cout << "last: /" << s.rfind('/') <<  "length:" << s.length() << "\n";
    //    std::string executableName;

        FILENAME = filename;
        std::string tempFileName = filename; //   game_files/demo_game1.txt
        std::string newFileResult = tempFileName.substr(0,tempFileName.find("/"));
    //    std::cout << "token result:" << result << "\n";

    //    std::cout << currentLevelFile << "\n";
        int doesItHaveASlash = levelFiles[currLVL-1].rfind('/');

        if(doesItHaveASlash == -1){
            currentLevelFile = newFileResult + "/" + levelFiles[currLVL-1]; //might be @ lvl 1, but our index starts at 0
        }else{
            currentLevelFile = "./" +newFileResult + "/" + levelFiles[currLVL-1]; //might be @ lvl 1, but our index starts at 0
        }
    //    std::cout << "after if: " <<  currentLevelFile << "\n";


        file.open(currentLevelFile); // demo_level1.txt
        if(file.is_open()){
    //        std::cout << "printing level file" << "\n";
            while(std::getline(file,currLine)){
    //            std::cout << currLine << "\n";
                drawInfo.push_back(currLine); // current vector file in vector drawInfo
            }
        }else{
            std::cout << "error" << "\n";

        }
        file.close(); //close GAME_LEVEL1 FILE
        file.clear();

    }
}


void Game::NextLevelBaby() {
    std::string currentLevelFile = levelFiles[currLVL-1]; //this is the file we are going to load
    std::string tempFileName = FILENAME; //   game_files/demo_game1.txt
    std::string newFileResult = tempFileName.substr(0,tempFileName.find("/"));
//    std::cout << "token result:" << result << "\n";

//    std::cout << currentLevelFile << "\n";
    int doesItHaveASlash = levelFiles[currLVL-1].rfind('/');
    if(doesItHaveASlash == -1){
        currentLevelFile = newFileResult + "/" + levelFiles[currLVL-1]; //might be @ lvl 1, but our index starts at 0
    }else{
        currentLevelFile = "./" +newFileResult + "/" + levelFiles[currLVL-1]; //might be @ lvl 1, but our index starts at 0
    }


    std::ifstream file; // NEXT GAME LEVEL LOADED HERE
    file.open(currentLevelFile); // demo_level1.txt
    Items.clear();
    currentLevelItems.clear();
    drawInfo.clear(); //clean our vector and reload it with the next level info
    if(file.is_open()){
//        std::cout << "printing level file" << "\n";
        while(std::getline(file,currLine)){
//            std::cout << currLine << "\n";
            drawInfo.push_back(currLine); // current vector file in vector drawInfo
        }
    }
    file.close();
    file.clear();
}


Game::~Game()
{
    // TODO: Usually, deallocate anything that was dynamically
    // allocated in the ctor (constructor).
}
void Game::newStartingPositions() {
//    for(int i = 0; i < currMapPortalOrientation.size(); i++){
//        std::cout << "currentOrientation:" << currMapPortalOrientation[i] << "\n";
//    }
//
//    if(currMapPortalOrientation.back() == "left"){
//        //give left orientation
//        std::cout << "left running" << "\n";
//        portalStartH = height;
//        portalStartW = 1;
//    }else if(currMapPortalOrientation.back() == "right"){
//        //give left orientation
//        std::cout << "right running" << "\n";
//        portalStartH = height;
//        portalStartW = OGMapWidth-2;
//    }else if(currMapPortalOrientation.back() == "up"){
//        std::cout << "up running" << "\n";
//        portalStartH = 1;
//        portalStartW = 1+(OGMapWidth-1)/2;
//    }else if (currMapPortalOrientation.back() == "down"){
//        std::cout << "down running" << "\n";
//        portalStartH = OGMapHeight-2;
//        portalStartW = (OGMapWidth-1)/2;
//    }

}


int Game::preparePortals() {
    bool portalexist = false;
    std::stringstream  ss;
    for(unsigned i = 0; i < Portals.size(); i++) {
        ss.str("");
        ss.clear();
        ss.str(Portals[i]);
        currentPortalIndex = std::to_string(currentMapIndex);
        ss >> garbage >> firstMapIndex >> firstMapWall >> secondMapIndex >> secondMapWall;

        if (currentPortalIndex == firstMapIndex){ //normal portal
            if(firstMapWall == currentWall){
                int mapOne = std::stoi(firstMapIndex);
                int mapTwo = std::stoi(secondMapIndex);
                currentMapPortal.push_back(mapOne);
                currentMapPortal.push_back(mapTwo);
                currMapPortalOrientation.push_back(firstMapWall);
                currMapPortalOrientation.push_back(secondMapWall);
                portalexist = 1;
//                std::cout << "INSIDE A IF" << "\n";
                isTherePortalSet(1);
//                std::cout << "taking the portal"  << firstMapIndex  << firstMapWall <<  " " << " to" << secondMapIndex << " " << secondMapWall << "\n";
//                break;
            }
        }else if (currentPortalIndex == secondMapIndex){ //reverse portal
            if(secondMapWall == currentWall) {
                int mapOne = std::stoi(secondMapIndex);
                int mapTwo = std::stoi(firstMapIndex);
                currentMapPortal.push_back(mapOne);
                currentMapPortal.push_back(mapTwo);
                currMapPortalOrientation.push_back(secondMapWall);
                currMapPortalOrientation.push_back(firstMapWall);
                portalexist = 1;
//                std::cout << "INSIDE A IF" << "\n";
                isTherePortalSet(1);
//                std::cout << "taking the portal" << secondMapIndex << " " << secondMapWall <<  " " << " to" << firstMapIndex  << firstMapWall << "\n";
//                break;
//                break;
            }
        }
        ss.str("");
        ss.clear();
    }

if(portalexist == 1){

}else{
    isTherePortalSet(-1);
}
return 0;

}

void Game::setNextOrientation() { //CALCULATE NEW ORIENTATION
//    std::cout << "setOrientation input" << orientationVec.back() << "\n";


    if((orientationVec.back() == "<") && (LEFT == 1)) { // < (left)
        orientationVec.push_back("v");
    }else if((orientationVec.back() == "v") && (LEFT == 1)) { // < (left)
        orientationVec.push_back(">");
    }else if((orientationVec.back() == ">") && (LEFT == 1)) { // < (left)
        orientationVec.push_back("^");
    }else if((orientationVec.back() == "^") && (LEFT == 1)) { // < (left)
        orientationVec.push_back("<");
    }

    if((orientationVec.back() == "<") && (RIGHT == 1)) { // < (left)
        orientationVec.push_back("^");
    }else if((orientationVec.back() == "^") && (RIGHT == 1)) { // < (left)
        orientationVec.push_back(">");
    }else if((orientationVec.back() == ">") && (RIGHT == 1)) { // < (left)
        orientationVec.push_back("v");
    }else if((orientationVec.back() == "v") && (RIGHT == 1)) { // < (left)
        orientationVec.push_back("<");
    }

//    std::cout << orientationVec.back() << "THE NEW ORIENTATION" << "\n";
}
//void Game::itemHandler() {
//    std::string someIndex, h, w;
//
//    for(int i = 0; i < Items.size(); i++){
//        if(itemindex == i){
//            currentMapItems.push_back(Items[i]);
//            std::cout << "current segment has the following items:" << Items[i] << "\n";
//        }
//    }
//}
int Game::areWeHittingBuilding(int height, int width) {
    std::stringstream ss;
    std::string h,w,someIndex,buildingIndex;
    buildingIndex = std::to_string(currentMapIndex); //buildingIndex == our current mapsegment

    for(unsigned i = 0; i < Buildings.size(); i++) {
        ss.str(Buildings[i]);
        ss >> garbage >> someIndex >> h >> w; // the index, y axis, x axis
        if (someIndex == buildingIndex) { // if the current map  has the same index as the building from Building vector
            buildingYStart = std::stoi(h);
            buildingXStart = std::stoi(w); //attempt to compare the BUILDING COORDS vs PLAYER COORDS
            if((height == buildingYStart) && (width == buildingXStart)) {  //WE DEF WANT THIS
                return 1; // 1 = BUILDING AT CURRENT LOCATION
            }else if((height == buildingYStart+1) && (width == buildingXStart)){ //height + 1,2,3 is for the building being height=4
                return 1;
            }else if((height == buildingYStart+2) && (width == buildingXStart)){ //left edge
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart)){
//                std::cout << "hitting a fucking building " << "\n";
                return 1;
            }

            if((height == buildingYStart) && (width == buildingXStart+5)) {  //right edge //0,5
                return 1; // 1 = BUILDING AT CURRENT LOCATION
            }else if((height == buildingYStart+1) && (width == buildingXStart+5)){ //1,5
                return 1;
            }else if((height == buildingYStart+2) && (width == buildingXStart+5)){ //2,5
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart+5)){ //3,5
                return 1;
            }


            // now do top edge
            else if((height == buildingYStart) && (width == buildingXStart)) {  //start at 0,0
                return 1; // 1 = BUILDING AT CURRENT LOCATION
            }else if((height == buildingYStart) && (width == buildingXStart+1)){ //0,1
                return 1;
            }else if((height == buildingYStart) && (width == buildingXStart+2)){ //0,2
                return 1;
            }else if((height == buildingYStart) && (width == buildingXStart+3)){ // 0,3
                return 1;
            }else if((height == buildingYStart) && (width == buildingXStart+4)){ // 0,4
                return 1;
            }else if((height == buildingYStart) && (width == buildingXStart+5)){ // 0,5
                return 1;
            }

            //now do bottom edge
            else if((height == buildingYStart+3) && (width == buildingXStart)) {  //start at 0,0
                return 1; // 1 = BUILDING AT CURRENT LOCATION
            }else if((height == buildingYStart+3) && (width == buildingXStart+1)){ //0,1
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart+2)){ //0,2
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart+3)){ // 0,3
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart+4)){ // 0,4
                return 1;
            }else if((height == buildingYStart+3) && (width == buildingXStart+5)){ // 0,5
                return 1;
            }



        }
        ss.str("");
        ss.clear();
    }
    return -1;
}

int Game::areWeHittingItem(int height,int width) {
    //if I hit an ITEM in this function -> use a vector called itemHitInfo and we will parse / remove it from map
    std::string itemindex, someIndex, h, w;
    std::stringstream ss;
    itemindex = std::to_string(currentMapIndex);
    for(unsigned i = 0; i < Items.size(); i++){
        ss.str(Items[i]);
        ss >> garbage >> someIndex >> h >> w;
        if(someIndex == itemindex){ //we may want this item
            yItem = std::stoi(h);
            xItem = std::stoi(w);
            if((height == yItem) && (width == xItem)) { //WE DEF WANT THIS
                itemToRemove = Items[i]; // what we will remove
                ss.str("");
                ss.clear(); //rese
                return 1;
            }
        }
        ss.str("");
        ss.clear(); //reset stream
    }
    return -1;
}

void Game::isTherePortalSet(int isThereP) {
    isTherePortal = isThereP; //is there a portal 1 if yes, -1 if no
}


//Determine from getInput() what our next level will look like
void Game::update(std::vector<std::string> currentBoard) {
    std::stringstream ss;
    std::string playerStartHeight, playerStartWidth;
//    int pStartHeight, pStartWidth;
    //reparse our new board to prepare for collisions
//    std::cout << "current level" << currLVL << "\n";
    Items.clear();
    Portals.clear();
    Buildings.clear();
    for(unsigned i = 0; i < currentBoard.size(); i++) {
        currLine = currentBoard[i];
//        std::cout << currLine << "\n";


        if ((currLine[0] == 'M') && (i == ((unsigned) currentMapIndex + 3))) { //IF ITS CURRENT MAP I WANT ITS HEIGHT
            ss.str(currLine);
            ss >> garbage >> mapHeight >> mapWidth; //for collision/portals
            OGMapHeight = stoi(mapHeight);
            OGMapWidth = stoi(mapWidth); //these are final until we get a new map
//            std::cout << "IS THIS WORKING";
            ss.str("");
            ss.clear();
        }
        if (currLine[0] == 'B') // buildings
            Buildings.push_back(currLine);
        if (currLine[0] == 'P') // portals
            Portals.push_back(currLine);
        if (currLine[0] == 'I') // items
            Items.push_back(currLine);
        if(currLine[0] == 'N'){
            if(totalMoves == -1){
                ss.str(currLine);
                ss >> garb >> tempMove;
                totalMoves = std::stoi(tempMove);
                ss.str("");
                ss.clear();
            }
        }

    }


    currentLevelItems = Items; //how we store the # of items per level
    totalItems = currentLevelItems.size();
    if(currentLevelItems.empty()){
        currentLevelItems = Items; //how we store the # of items per level
        totalItems = currentLevelItems.size();
    }
//    std::cout << "Total Items" << totalItems << "\n";
//    for(int i = 0; i < currentLevelItems.size(); i++){
//        std::cout << "curr lvl  Items" << currentLevelItems[i] << "\n";
//    }
//    std::cout << "Total Items" << totalItems << "\n";
//    for(int i = 0; i < Items.size(); i++){
//        std::cout << " Items" << Items[i] << "\n";
//    }



    //FIND BUILDINGS LOCATIONS @ other current mapSegmentIndex
//    std::string h,w,someIndex,buildingIndex;
//    buildingIndex = std::to_string(currentMapIndex); //buildingIndex == our current mapsegment
//
//    int buildingYStart,buildingXStart;
//    for(unsigned i = 0; i < Buildings.size(); i++) {
//        ss.str(Buildings[i]);
//        ss >> garbage >> someIndex >> h >> w; // the index, y axis, x axis
//        if (someIndex == buildingIndex) { // if the current map  has the same index as the building from Building vector
//            buildingYStart = std::stoi(h);
//            buildingXStart = std::stoi(w); //attempt to compare the BUILDING COORDS vs PLAYER COORDS
//            if ((height == buildingYStart) && (width == buildingXStart)) {  //WE DEF WANT THIS
//
//                ss.str("");
//                ss.clear();
//            }
//        }
//        ss.str("");
//        ss.clear();
//    }

//    itemHandler();





    //handling movement for portal / collisions
    for(unsigned i = 0; i < currentBoard.size(); i++) {
        currLine = currentBoard[i];
//        std::cout << "LEFT == " << LEFT << "RIGHT == " << RIGHT << "\n";
        if(i == 2 && LEFT == 1){ // HANDLE "A"
            if (currLine == "left") {
                pOrientation = "<";
            }else if (currLine == "right") {
                pOrientation = ">";
            }else if (currLine == "down") {
                pOrientation = "v";
            }else if (currLine == "up") {
                pOrientation = "^";
            }
//            orientationVec.clear();
            orientationVec.push_back(pOrientation); //PUSHING BACK LAST POSITION
            setNextOrientation(); //determine next position LEFT move
            if (orientationVec.back() == "v")
                pOrientation = "down";
            else if (orientationVec.back() == "<")
                pOrientation = "left";
            else if (orientationVec.back() == ">")
                pOrientation = "right";
            else if (orientationVec.back() == "^")
                pOrientation = "up";
            currLine = pOrientation;
            currentBoard[i] = currLine;
            LEFT = 0;
        }
        if((i == 2) && (RIGHT == 1)){  //HANDLE "D"
//            std::cout << "curr" << currLine << "\n";
            if (currLine == "left") {
                pOrientation = "<";
            }if (currLine == "right") {
                pOrientation = ">";
            }if (currLine == "down") {
                pOrientation = "v";
            }if (currLine == "up") {
                pOrientation = "^";
            }
//            orientationVec.clear();
            orientationVec.push_back(pOrientation); //PUSHING BACK LAST POSITION
            setNextOrientation(); //determine next position LEFT move
            if (orientationVec.back() == "v")
                pOrientation = "down";
            if (orientationVec.back() == "<")
                pOrientation = "left";
            if (orientationVec.back() == ">")
                pOrientation = "right";
            if (orientationVec.back() == "^")
                pOrientation = "up";

            currLine = pOrientation;
            currentBoard[i] = currLine;
            RIGHT = 0;


        }
        if((i == currentBoard.size()-1) && (moveFORWARD == 1)){ //HANDLE THE MOVESSSS
//            std::cout << "before:" << currLine << "\n";

            currLine = currentBoard[1];
            ss.str(currLine);
            ss >> pHeight >> pWidth;
            height = stoi(pHeight);
            width = stoi(pWidth);
            //depending on the way its facing, i move accordingly 1. get the currline direction
            currDirection =  currentBoard[2]; //current direction in which way we move
            //if direction is up
//            std::cout << "dir" << currDirection << "\n";

            if(currDirection == "up"){
                int newHeight = height - 1;
//                 std::cout << "next height will be: "  << newHeight << "\n";



//                std::cout << "before if" << "\n";
//                std::cout << "newH" << newHeight << "Yitem" << yItem << "Xitem" << xItem << "\n";
//                std::cout << "newW" << width << "Yitem" << "\n";

                //global variable -> decrements # of moves
                if(areWeHittingItem(newHeight, width) == 1){ //IF WE RUN INTO AN ITEM
                    //we know we have an item to remove @ itemToRemove
//                    std::cout << "item to remove: " << itemToRemove << "\n";
                    for(unsigned i = 0; i < currentBoard.size(); i++){
                        if(currentBoard[i] == itemToRemove){ //ITEM WE WANT TO REMOVE COMPARED WITH OG VECTOR
                            //this is the index of what we will remove
                        }else{
                            removedItemBoard.push_back(currentBoard[i]);
                        }
//                        std::cout << currentBoard[i] << "\n";
                    }

                    currentBoard.clear();
                    currentBoard = removedItemBoard;

                    totalItems--; //reduce #of items
                    totalMoves--;
                    height--; //keep moving
                    itemToRemove = "";
                    removedItemBoard.clear();
                }
                else if((newHeight == 0) && (width == ((OGMapWidth-1)/2))){
                    currentWall = "up"; //completely checked
                    currMapPortalOrientation.clear();
                    preparePortals();
                    if(isTherePortal == 1) {
                        int newMap = currentMapPortal[1];
                        std::string newM = std::to_string(newMap);
                        currentBoard[0] = newM; //set MAP INDEX = THE NEW MAP PORTAL TAKES US TO

                        int newMapIndexDueToPortal = currentMapPortal[1] + 3; //<- our new segment index
                        ss.clear();
                        ss.str(currentBoard[newMapIndexDueToPortal]);
                        std::string newH, newW;
                        ss >> garbage >> newH >> newW; //for collision/portals
                        OGMapHeight = std::stoi(newH);
                        OGMapWidth = std::stoi(newW); //these are final until we get a new map
                        ss.str("");
                        ss.clear();
                        if(currMapPortalOrientation.back() == "up"){
//                            std::cout << "up running" << "\n";
                            portalStartH = 1;
                            portalStartW = (OGMapWidth-1)/2;
                            currentBoard[2] = "down"; // v
                        }
                        else if (currMapPortalOrientation.back() == "down"){ //position because we are going to end up @ down
                            portalStartH = OGMapHeight-2;
                            portalStartW = (OGMapWidth-1)/2;

                        }
                        else if(currMapPortalOrientation.back() == "left"){
                            //give left orientation
//                            std::cout << "up to left portal running" << "\n";
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = 1;
                            currentBoard[2] = "right"; // v


                        }else if(currMapPortalOrientation.back() == "right"){
                            //give left orientation
//                            std::cout << "right running" << "\n";
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = OGMapWidth-2;
                            currentBoard[2] = "left";

                        }

                        pHeight = std::to_string(portalStartH); //covnert backwards to store in the OG vector
                        pWidth = std::to_string(portalStartW);
                        currLine = pHeight + " " + pWidth;
                        currentBoard[1] = currLine;
                        portalTaken = true;

                    }

                    else if(isTherePortal == -1){
                        //NO portal no move
                    }


                }else if(newHeight==0){ //handling the portal for move UP
                    //hit top border -> do nothing
                }
                else if(areWeHittingBuilding(newHeight,width) == 1){
//                    std::cout << "hitting a fucking building up" << "\n";
                }
                else{
                    height--;
                    totalMoves--;
                }


            }
            else if(currDirection == "down"){ //PLAYER MOVE DOWN
                int newPlayerHeight = height;
                int tempHeight = height + 1;

                if(areWeHittingItem(tempHeight, width) == 1){ //IF WE RUN INTO AN ITEM
                    //we know we have an item to remove @ itemToRemove
//                    std::cout << "item to remove: " << itemToRemove << "\n";
                    for(unsigned i = 0; i < currentBoard.size(); i++){
                        if(currentBoard[i] == itemToRemove){ //ITEM WE WANT TO REMOVE COMPARED WITH OG VECTOR
                            //this is the index of what we will remove
                        }else{
                            removedItemBoard.push_back(currentBoard[i]);
                        }
//                        std::cout << currentBoard[i] << "\n";
                    }

                    currentBoard.clear();
                    currentBoard = removedItemBoard;

                    totalItems--; //reduce #of items
                    totalMoves--;
                    height++; //keep moving

                    itemToRemove = "";
                    removedItemBoard.clear();
                }
                else if((newPlayerHeight == (OGMapHeight-2)) && (width == ((OGMapWidth-1)/2)))
                {
                    currentWall = "down";
                    currMapPortalOrientation.clear();
                    preparePortals();
                    if(isTherePortal == 1) {
//                        std::cout << "portal present" << "\n";

                        int temp = currentMapPortal.back();
                        int newMap = temp;
                        std::string newM = std::to_string(newMap);
                        currentBoard[0] = newM; //set MAP INDEX = THE NEW MAP PORTAL TAKES US TO

                        int newMapIndexDueToPortal = currentMapPortal[1] + 3; //<- our new segment index
                        ss.clear();
                        std::stringstream ss;
                        ss.str(currentBoard[newMapIndexDueToPortal]);
                        std::string newH, newW;
                        ss >> garbage >> newH >> newW; //for collision/portals
                        OGMapHeight = std::stoi(newH);
                        OGMapWidth = std::stoi(newW); //these are final until we get a new map
                        ss.str("");
                        ss.clear();
                        if(currMapPortalOrientation.back() == "up"){
                            portalStartH = 1;
                            portalStartW = (OGMapWidth-1)/2;
                        }
                        else if (currMapPortalOrientation.back() == "down"){ //position because we are going to end up @ down
                            portalStartH = OGMapHeight-2;
                            portalStartW = (OGMapWidth-1)/2;
                            currentBoard[2] = "up";
                        }
                        else if(currMapPortalOrientation.back() == "left"){
                            //give left orientation
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = 1;
                            currentBoard[2] = "right";

                        }else if(currMapPortalOrientation.back() == "right"){
                            //give left orientation
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = OGMapWidth-2;
                            currentBoard[2] = "left";

                        }

                        pHeight = std::to_string(portalStartH); //covnert backwards to store in the OG vector
                        pWidth = std::to_string(portalStartW);
                        currLine = pHeight + " " + pWidth;

                        currentBoard[1] = currLine;
                        portalTaken = true;


                    }
                    else if(isTherePortal == -1){
//                        std::cout << "WALL BRO" << "\n";
                        //do nothing
                    }

                }else if(newPlayerHeight == (OGMapHeight-2)){ //index @ 0 so have to minus 1

                }
                else if(areWeHittingBuilding(tempHeight,width) == 1){
                    //do nothing hitting building
                }
//                else if((width == buildingXStart) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }else if(((width) == buildingXStart+1) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }else if(((width) == buildingXStart+2) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }else if(((width) == buildingXStart+3) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }else if(((width) == buildingXStart+4) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }else if(((width) == buildingXStart+5) && ((newPlayerHeight+1) == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                }
                else{
                    height++;
                    totalMoves--;
                }





            }else if(currDirection == "left"){ //handle MOVE LEFT COLLISIONS / PORTAL HERE
                int newWidth = width - 1; // 12 17
//                 std::cout << "MOVING LEFT" << "\n";
//
//                preparePortals();



                //if theres a portal
                if((newWidth == 0) && (height == (OGMapHeight-1)/2)){
                    currentWall = "left";
                    currMapPortalOrientation.clear();
                    preparePortals(); //sets everything up for this part of the func
//                    std::cout << isTherePortal << "\n";
                    if(isTherePortal == 1){
//                        std::cout << "portal present" << "\n";

                        int newMap = currentMapPortal[1];
                        std::string newM = std::to_string(newMap);
                        currentBoard[0] = newM; //set MAP INDEX = THE NEW MAP PORTAL TAKES US TO



                        int newMapIndexDueToPortal = currentMapPortal[1] + 3; //<- our new segment index
                        ss.clear();
                        ss.str(currentBoard[newMapIndexDueToPortal]);
                        std::string newH, newW;
                        ss >> garbage >> newH >> newW; //for collision/portals
//                     std::cout << newH << " " <<  newW; //THERES A PORTAL HERE
                        OGMapHeight = std::stoi(newH);
                        OGMapWidth =  std::stoi(newW); //these are final until we get a new map
                        ss.str("");
                        ss.clear();
                        if(currMapPortalOrientation.back() == "up"){
//                         std::cout << "up running" << "\n";
                            portalStartH = 1;
                            portalStartW = (OGMapWidth-1)/2;
                            currentBoard[2] = "down";
                        }
                        else if (currMapPortalOrientation.back() == "down"){ //position because we are going to end up @ down
//                         std::cout << "down running" << "\n";
                            portalStartH = OGMapHeight-2;
                            portalStartW = (OGMapWidth-1)/2;
                            currentBoard[2] = "up";
                        }else if(currMapPortalOrientation.back() == "left"){
                            //give left orientation
//                         std::cout << "left running" << "\n";
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = 1;
                            currentBoard[2] = "right";
                        }else if(currMapPortalOrientation.back() == "right"){
                            //give left orientation
//                         std::cout << "right running" << "\n";
                            portalStartH = (OGMapHeight-1)/2;
                            portalStartW = OGMapWidth-2;
                        }



                        pHeight = std::to_string(portalStartH); //covnert backwards to store in the OG vector
                        pWidth = std::to_string(portalStartW);
                        currLine = pHeight + " " + pWidth;

                        currentBoard[1] = currLine;
                        portalTaken = true;


                    }else if(isTherePortal == -1){
//                        std::cout << "WALL BRO" << "\n";
                        //do nothing

                    }
                }
                else if(newWidth == 0){
                    //you're hitting a wall!
                }
                //are we hitting an item -> WORKS
                else if(areWeHittingItem(height, newWidth) == 1){ //IF WE RUN INTO AN ITEM
                    //we know we have an item to remove @ itemToRemove
//                    std::cout << "item to remove: " << itemToRemove << "\n";
                    for(unsigned i = 0; i < currentBoard.size(); i++){
                        if(currentBoard[i] == itemToRemove){ //ITEM WE WANT TO REMOVE COMPARED WITH OG VECTOR
                            //this is the index of what we will remove
                        }else{
                            removedItemBoard.push_back(currentBoard[i]);
                        }
//                        std::cout << currentBoard[i] << "\n";
                    }

                    currentBoard.clear();
                    currentBoard = removedItemBoard;

                    totalItems--; //reduce #of items
                    totalMoves--;
                    width--; //keep moving
                    itemToRemove = "";
                    removedItemBoard.clear();
                }
                    //HANDLE PORTAL FOR LEFT MOVE ->FIX IT
                else if(areWeHittingBuilding(height,newWidth) == 1){
                    //do nothing hitting building
                }

//                    else if((newWidth == (buildingXStart+5)) && (height == buildingYStart)){
//                    //trying to go into  building -> do nothing
//                }else if((newWidth == (buildingXStart+5)) && (height == (buildingYStart+1))){
//                    //trying to go into  building -> do nothing
//                }else if((newWidth == (buildingXStart+5)) && (height == (buildingYStart+2))){
//                    //trying to go into  building -> do nothing
//                }else if((newWidth == (buildingXStart+5)) && ((height) == (buildingYStart+3))){
//                    //trying to go into  building -> do nothing
//                }
                else{
                    width--;
                    totalMoves--;
                }


            }
            else if(currDirection == "right") { //MOVE RIGHT
                int newWidth = width; //current: 9, 13
                newWidth++; //new max now  9,14




                    //COLLECTING ITEMS
                 if(areWeHittingItem(height, newWidth) == 1){ //IF WE RUN INTO AN ITEM
//                    std::cout << "removing item" << "\n";
//                    std::cout << currentBoard.size() << "\n";
                    //we know we have an item to remove @ itemToRemove
//                    std::cout << "item to remove: " << itemToRemove << "\n";
                    for(unsigned i = 0; i < currentBoard.size(); i++){
                        if(currentBoard[i] == itemToRemove){ //ITEM WE WANT TO REMOVE COMPARED WITH OG VECTOR
                            //this is the index of what we will remove
                        }else{
                            removedItemBoard.push_back(currentBoard[i]);
                        }
//                        std::cout << currentBoard[i] << "\n";
                    }

                    currentBoard.clear();
                    currentBoard = removedItemBoard;
//                    for(int i = 0; i < currentBoard.size(); i++){
//                        std::cout << currentBoard[i] << "\n";
//                    }
                    totalItems--; //reduce #of items
                    totalMoves--;
                    width++; //keep moving
                    itemToRemove = "";
                    removedItemBoard.clear();
                }

                    //HANDLE PORTAL FOR RIGHT MOVE
                else if((height == ((OGMapHeight-1)/2)) && (newWidth == (OGMapWidth - 1))) {
                    currentWall = "right";
                    currMapPortalOrientation.clear();
                    preparePortals();
//                     std::cout << "PORTAL HERE TRANSPORT! \n"; //THERES A PORTAL HERE
                     if(isTherePortal == 1) {
//                         std::cout << "portal present" << "\n";
                         //transport urself
                         int newMap = currentMapPortal[1];
                         std::string newM = std::to_string(newMap);
                         currentBoard[0] = newM; //set MAP INDEX = THE NEW MAP PORTAL TAKES US TO



                         int newMapIndexDueToPortal = currentMapPortal[1] + 3; //<- our new segment index
                         ss.clear();
                         ss.str(currentBoard[newMapIndexDueToPortal]);
                         std::string newH, newW;
                         ss >> garbage >> newH >> newW; //for collision/portals

                         OGMapHeight = std::stoi(newH);
                         OGMapWidth =  std::stoi(newW); //these are final until we get a new map
                         ss.str("");
                         ss.clear();
                         if(currMapPortalOrientation.back() == "up"){ // send me up
//                         std::cout << "up running" << "\n";
                             portalStartH = 1;
                             portalStartW = (OGMapWidth-1)/2;
                             currentBoard[2] = "down";
                         }
                         else if (currMapPortalOrientation.back() == "down"){ //position because we are going to end up @ down
//                         std::cout << "down running" << "\n";
                             portalStartH = OGMapHeight-2;
                             portalStartW = (OGMapWidth-1)/2;
                             currentBoard[2] = "up";

                         }else if(currMapPortalOrientation.back() == "left"){
                             //give left orientation
//                         std::cout << "left running" << "\n";
                             portalStartH = (OGMapHeight-1)/2;
                             portalStartW = 1;
                         }else if(currMapPortalOrientation.back() == "right"){
                             //give left orientation
//                         std::cout << "right running" << "\n";
                             portalStartH = (OGMapHeight-1)/2;
                             portalStartW = OGMapWidth-2;
                             currentBoard[2] = "left";

                         }


                         pHeight = std::to_string(portalStartH); //REDONE HEIGHT FOR THIS PORTAL
                         pWidth = std::to_string(portalStartW);
                         currLine = pHeight + " " + pWidth;
                         currentBoard[1] = currLine;
                         portalTaken = true;


                     }else if(isTherePortal == -1){
                         //wall here
                     }

                }
                else if (newWidth == (OGMapWidth - 1)) {   //if this is the  max width stop
                    //do nothing

                }
//                else if ((newWidth == buildingXStart) && (height == buildingYStart)) {
//                    //trying to go into  building -> do nothing
//                } else if ((newWidth == buildingXStart) && (height == (buildingYStart + 1))) {
//                    //trying to go into  building -> do nothing
//                } else if ((newWidth == buildingXStart) && ((height) == (buildingYStart + 2))) {
//                    //trying to go into  building -> do nothing
//                } else if ((newWidth == buildingXStart) && ((height) == (buildingYStart + 3))) {
//                    //trying to go into  building -> do nothing
//                }
                else if(areWeHittingBuilding(height,newWidth) == 1){
                }
                else {
                     width++;
                     totalMoves--;
                 }




            }
//            if(totalItems == 0){
//                std::cout << "Game over!" << "\n\n";
//            }

            if(portalTaken == true) { //if you took portal then we just contineu without updated -> we updated in the function where we moved
                ss.str("");
                ss.clear();
                totalMoves--; //decrease # of moves
                moveFORWARD = 0;
                portalTaken = false; //reset for the next mapw
                currMapPortalOrientation.clear();
                currentMapPortal.clear(); //reset for the next map
            }else{ //portalTaken = false;
//                std::cout << "MOVE REGISTERED: " << currLine << "\n";
                pHeight = std::to_string(height); //covnert backwards to store in the OG vector
                pWidth = std::to_string(width);
                currLine = pHeight + " " + pWidth;
//                totalMoves--;

//                std::cout << "after:" << currLine << "\n";
                currentBoard[1] = currLine;
                moveFORWARD = 0;

                ss.str("");
                ss.clear();
            }

        } //end of MOVE FORWARD LOOP

    }//end of large FOR LOOP




    std::string newMoves = "N ";
    newMoves += std::to_string(totalMoves);
    currentBoard.back() = newMoves; //set the New # of moves to our board


    drawInfo = currentBoard;



}//end of function Update




void Game::run() {
    if (mInterface == InterfaceType::Curses) { //curses mode
//        std::cout << "curses mode" << "\n";
        CursesView *cursesView = new CursesView(height, width);
        CursesController *cursesControl = new CursesController();
        initscr();
        noecho();


//        WINDOW *screen = newwin(height, width, 0, 0);
//        cursesView->setScreen(screen);
        cursesView->draw(drawInfo);




        currentMapIndex = cursesView->getMapSegment(); //current Map Segment Index
        bool theyWon = 0;
        //keep track
        // W -> move forward
        // A-> change orientation  ^ -> <
        // D -> v -> >
        // keep track of the moves
        // keep track of the

        redoCurses:;

        //    for(int i = 0; i <= levelFiles.size()-1; i++) { //currlvl starts @ 1, levlefiles is 2.
        do {
            auto cursesPrompt = cursesControl->getInput(); //prompt for input FOR NEXT INSTRUCTION


            //       std::cout << "Total Moves in RUn:" << totalMoves << "\n";
            if (cursesPrompt == Command::Quit) {  // q entered
//                std::cout << "\n";
//                printw("hi",3,3);
                std::cout << "You quit the game." << "\n";

                delete (cursesView);
                delete (cursesControl);
                break;
            } else if (cursesPrompt == Command::Invalid) {
                INVALID = true;
                update(drawInfo);
                cursesView->draw(drawInfo);
//                std::cout << "invalid" << "\n";

            }
            else if (cursesPrompt == Command::Left) {
                LEFT = true;
                moveFORWARD = 0;
                update(drawInfo);

                if (totalMoves == 0) {
//                    std::cout << "You lost the game." << "\n";
                      printw("You lost the game", height+5,0);
                    break;
                } else {
//                    std::cout << "Level: " << currLVL << "\n";
                    cursesView->draw(drawInfo);
                }
            }
            else if (cursesPrompt == Command::Right) {
                RIGHT = true;
                moveFORWARD = 0;
                update(drawInfo);
                if (totalMoves == 0) {
                    std::cout << "You lost the game." << "\n";
                    break;
                } else {
//                    std::cout << "Level: " << currLVL << "\n";
                    cursesView->draw(drawInfo);
                }

            } else if (cursesPrompt == Command::Forward) {
                moveFORWARD = true;
                currentMapIndex = cursesView->getMapSegment(); //current Map Segment Index
                LEFT = 0;
                RIGHT = 0;
                //                std::cout << "hi" << "\n"
                //            std::cout << "total items: " << totalItems << "\n";
                update(drawInfo);
                //            std::cout << "total items: " << totalItems << "\n";
                if (totalItems == 0) {
                    if (currLVL == totalLevels) { //GAME IS DONE THEY WIN!
                        theyWon = 1;
                        update(drawInfo); //update board
//                        std::cout << "Level: " << currLVL << "\n";
                        cursesView->draw(drawInfo); //print updated board where u win

                        break;
                    }
                    currLVL++; //need to go to next level
                    NextLevelBaby();
                    totalMoves = -1;
                    update(drawInfo);
//                    std::cout << "Level: " << currLVL << "\n";
                    cursesView->draw(drawInfo);
                    //                    moveFORWARD = false;
                    goto redoCurses;
                }
                if (totalMoves == 0) {
                    std::cout << "You lost the game." << "\n";
                    delete (cursesView);
                    delete (cursesControl);
                    break;
                } else {
//                    std::cout << "Level: " << currLVL << "\n";
                    cursesView->draw(drawInfo);

                }
            }


        } while (1);

        if (theyWon == 1) {
//            printw("hello",height+10,0);
            std::cout << "You won the game." << "\n";
            delete (cursesView);
            delete (cursesControl);
        }





    } else if (mInterface == InterfaceType::Print) { //print mode

        PrintView *printView = new PrintView(height, width);
        PrintController *printControl = new PrintController();
        std::cout << "Level: " << currLVL << "\n";
        printView->draw(drawInfo); //STARTING POSITION
        currentMapIndex = printView->getMapSegment(); //current Map Segment Index
        bool theyWon = 0;
        //keep track
        // W -> move forward
        // A-> change orientation  ^ -> <
        // D -> v -> >
        // keep track of the moves
        // keep track of the

        reset:;

        //    for(int i = 0; i <= levelFiles.size()-1; i++) { //currlvl starts @ 1, levlefiles is 2.
        do {
            auto promptResult = printControl->getInput(); //prompt for input FOR NEXT INSTRUCTION


            //       std::cout << "Total Moves in RUn:" << totalMoves << "\n";
            if (promptResult == Command::Quit) {  // q entered
                std::cout << "You quit the game." << "\n";

                //            std::cout << "testing 1" << "\n";
                delete (printView);
                delete (printControl);
                break;
            } else if (promptResult == Command::Invalid) {
                INVALID = true;
                update(drawInfo);
                printView->draw(drawInfo);
//                std::cout << "invalid" << "\n";

            } else if (promptResult == Command::Left) {
                LEFT = true;
                moveFORWARD = 0;
                update(drawInfo);

                if (totalMoves == 0) {
                    std::cout << "You lost the game." << "\n";
                    break;
                } else {
                    std::cout << "Level: " << currLVL << "\n";
                    printView->draw(drawInfo);
                }
            } else if (promptResult == Command::Right) {
                RIGHT = true;
                moveFORWARD = 0;
                update(drawInfo);
                if (totalMoves == 0) {
                    std::cout << "You lost the game." << "\n";
                    break;
                } else {
                    std::cout << "Level: " << currLVL << "\n";
                    printView->draw(drawInfo);
                }

            } else if (promptResult == Command::Forward) {
                moveFORWARD = true;
                currentMapIndex = printView->getMapSegment(); //current Map Segment Index
                LEFT = 0;
                RIGHT = 0;
                //                std::cout << "hi" << "\n"
                //            std::cout << "total items: " << totalItems << "\n";
                update(drawInfo);
                //            std::cout << "total items: " << totalItems << "\n";
                if (totalItems == 0) {
                    if (currLVL == totalLevels) { //GAME IS DONE THEY WIN!
                        theyWon = 1;
                        update(drawInfo); //update board
                        std::cout << "Level: " << currLVL << "\n";
                        printView->draw(drawInfo); //print updated board where u win

                        break;
                    }
                    currLVL++; //need to go to next level
                    NextLevelBaby();
                    totalMoves = -1;
                    update(drawInfo);
                    std::cout << "Level: " << currLVL << "\n";
                    printView->draw(drawInfo);
                    //                    moveFORWARD = false;
                    goto reset;
                }
                if (totalMoves == 0) {
                    std::cout << "You lost the game." << "\n";
                    delete (printView);
                    delete (printControl);
                    break;
                } else {
                    std::cout << "Level: " << currLVL << "\n";
                    printView->draw(drawInfo);

                }
            }


        } while (1);

        //    endGame:



        if (theyWon == 1) {
            std::cout << "You won the game." << "\n";
            delete (printView);
            delete (printControl);
        }

//        exit(5); lol idk why this is here
    }

}









