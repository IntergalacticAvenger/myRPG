#include "curses_view.hpp"
#include <curses.h>
#include <iostream>
#include <istream>
#include <sstream>

/**
 * Side note: This class should probably be what is known as a singleton
 * class, i.e. a class that uses some setup (e.g. a static variable) to
 * prevent more than one instance of it from being created. I did not do this.
 */

CursesView::CursesView(int height, int width) //MAIN SCREEN BORDER
    : View(height, width)
{ //create the screen
    int H = height+2;
    int W = width+2;

    setHeight(H);
    setWidth(W);
    H = 1000;
    W = 1000;
    myScreen.resize(H); //height columns, unkown width
    for(int i = 0; i < H; i++) {
        myScreen[i].resize(W);
    }


}

void CursesView::setMapSegment(int mapIndex){
    mapSegmentIndex = mapIndex;
};
int CursesView::getMapSegment(){
    return mapSegmentIndex;
};

void CursesView::setHeight(int h) {
    screenHeight = h;
}

void CursesView::setWidth(int w) {
    screenWidth = w;
}



CursesView::~CursesView()
{
    // TODO: Implement. Clean up curses.

}

void CursesView::draw(const std::vector<std::string>& lines) //WHERE PLAYER WILL MOVE'S BOX
{

    MagSegments.clear();
    Buildings.clear();
    Portals.clear();
    Items.clear();
    Moves = 0;
//    int yMax, xMax;
//    WINDOW *playwin = newwin(20, 50, (yMax/2)-10, 10);


    std::string currLine, garb, tempMove;
    std::string playerStartHeight,playerStartWidth, playerOrientation;
    int pStartHeight,pStartWidth;
    std::stringstream ss;
    for(unsigned i = 0; i < lines.size(); i++) {
        currLine = lines[i];
        if(i == 0) {
            mapSegmentIndex = std::stoi(currLine);
            setMapSegment(mapSegmentIndex);
        }

        if(i == 1) {
            ss.str(currLine);
            ss >> playerStartHeight >> playerStartWidth;
            pStartHeight = std::stoi(playerStartHeight);
            pStartWidth = std::stoi(playerStartWidth);
            ss.str("");
            ss.clear();
//            std::cout << "now at H:" << playerStartHeight << " " << playerStartWidth << "\n";
        }if(i == 2){
            playerOrientation = currLine;
            if (playerOrientation == "left")
                playerOrientation = "<";
            if (playerOrientation == "right")
                playerOrientation = ">";
            if (playerOrientation == "down")
                playerOrientation = "v";
            if (playerOrientation == "up")
                playerOrientation = "^";

        }
        if(currLine[0] == 'M') { //map segments
            MagSegments.push_back(currLine);
        }if(currLine[0] == 'B') { // buildings
            Buildings.push_back(currLine);
        }if(currLine[0] == 'P') // portals
            Portals.push_back(currLine);
        if(currLine[0] == 'I') { // items
            Items.push_back(currLine);
//            std::cout << "PRINT VIEW ITEMS:" << currLine << "\n";
        }if(currLine[0] == 'N'){
            ss.str(currLine);
            ss >> garb >> tempMove;
            Moves = std::stoi(tempMove);
            ss.str("");
            ss.clear();
            //            Moves = std::stoi(currLine);
        }

    }
    ss.str("");
    ss.clear();








//pure draw portion
    int shift = 100;



    for(int i = 0+shift; i < screenHeight+shift; i++) {
        for (int j = 0+shift; j < screenWidth+shift; j++) {
            myScreen[i][j] = "~";
        }
    }



    for(int i = 0+shift; i < screenHeight+shift; i++) {
        for (int j = 0+shift; j < screenWidth+shift; j++) {
            myScreen[i][j];

        }
    }


//    mapSegmentIndex = 3;
    std::string temp = MagSegments[mapSegmentIndex]; //current mapSegment
    std::string h, w, whichIndex, garbage;
    int height, width, y, x, yItem, xItem;
    ss.str(temp);
    ss >> whichIndex >> h >> w;
    height = std::stoi(h);
    width = std::stoi(w);
    ss.str("");
    ss.clear();

    //20/2 = 10         10 - 10 = 0;
//    int screenH = screenHeight-2;
//    int screenW = screenWidth-2;
    int offsetH = ((screenHeight-3)/2) - pStartHeight;
    //25/2 = 13 - 15 = -2
    int offsetW= ((screenWidth-3)/2) - pStartWidth;
//    std::cout << "offsetH" <<  offsetH << "\n";
//    std::cout << "offsetW" <<  offsetW << "\n";




    //11 , 15

    for(int i = 1+shift; i < 1+height+shift; i++) {
        for (int j = 1+shift; j <= width+shift; j++) {
//            >  @~~~~~~~*
//            < $ |~~~~~~~~*
//            myScreen[newHeight+ i][newWidth+ j] = ' ';
//            myScreen[newHeight+i][newWidth+width] = '|';
//            myScreen[newHeight+height-1][newWidth+j] = '=';

            myScreen[i +offsetH][j+offsetW] = ' ';
            myScreen[i + offsetH][shift+1+offsetW] = '|';
            myScreen[i+offsetH][width+offsetW+shift] = '|';


//            myScreen[newHeight+ i][newWidth+ j] = ' ';
//            myScreen[newHeight+i][newWidth+width] = '|';
//            myScreen[newHeight+height][newWidth+j] = '=';


        }

    }




//
    for(int i = 1+shift; i < 1+height+shift; i++) {
        for (int j = 1+shift; j < width+1+shift; j++) {

            myScreen[shift+offsetH+1][j + offsetW] = '=';
            myScreen[shift + height + offsetH][j + offsetW] = '=';
        }
    }
//    std::cout << playerOrientation << "\n";
    //
    myScreen[shift+((screenHeight-3)/2)+1][shift+(screenWidth-3)/2+1] = playerOrientation;
//
//
//
    std::string buildingIndex = std::to_string(mapSegmentIndex);
    for(unsigned i = 0; i < Buildings.size(); i++) {
        ss.str(Buildings[i]);
        ss >> garbage >> whichIndex >> h >> w; // the index, y axis, x axis
        if (whichIndex == buildingIndex) {
            y = std::stoi(h);
            x = std::stoi(w);



//            //PLACE THIS BUILDING ON OUR MAP SEGMENT
//            myScreen[y][x+1] = "B";

            for (int a = 0+shift; a < 6+shift; a++) {

                myScreen[1+offsetH + y+shift][ x + a + offsetW+1] = ".";
                myScreen[1+offsetH + y + 1+shift][offsetW + x + a+1] = ".";

            }
            for(int a = 0+shift; a < 6+shift; a++){

                if (a == 2+shift || a == 3+shift) {
                    myScreen[1+offsetH + y + 2+shift][offsetW + x + a+1] = "&";
                    myScreen[1+offsetH + y + 3+shift][offsetW + x + a+1] = "&";
                } else {
                    myScreen[1+offsetH + y + 2+shift][offsetW + x + a+1] = ".";
                    myScreen[1+offsetH + y + 3+shift][offsetW + x + a+1] = ".";
                }
            }
        }
        ss.str("");
        ss.clear();
    }

//
    std::string itemIndex = std::to_string(mapSegmentIndex); //this is the index WE WANT
    for(unsigned i = 0; i < Items.size(); i++){
        ss.str(Items[i]);
//        std::cout << Items[i] << "\n";
        ss >> garbage >> whichIndex >> h >> w;
        if(whichIndex == itemIndex){ //curr line's index match the index WE WANT?
            yItem = std::stoi(h);
            xItem = std::stoi(w);
//            std::cout << yItem << " " << xItem << "\n";
            myScreen[offsetH+yItem+shift+1][offsetW+xItem+1+shift] = '$';
        }
        ss.str("");
        ss.clear(); //reset stream
    }



    std::string portalIndex = std::to_string(mapSegmentIndex);
    for(unsigned i = 0; i < Portals.size(); i++){
        ss.str(Portals[i]);
        //P 0 right 1 right
        std::string whichWall, otherIndex, whichOtherWall;
        ss >> garbage >> whichIndex >> whichWall >> otherIndex >> whichOtherWall;
        if(portalIndex == whichIndex){
            if(whichWall == "right") {
                myScreen[1+shift+offsetH + ((height-1)/2)][shift+width+offsetW] = "@";
                //                mvwprintw(mapSeg1, height/2 -2 , width-1, "@"); // print the Item
            }else if(whichWall == "left"){
                myScreen[shift+offsetH+((height-1)/2) +1][shift+1+offsetW] = "@";

//                mvwprintw(mapSeg1, height/2 -1,0,"@"); // print the Item
            }else if(whichWall == "up"){
                myScreen[1+shift+offsetH + 0][1+shift+offsetW+((width-1)/2)] = "@";

//                mvwprintw(mapSeg1,0,width/2,"@"); // print the Item
            }else if(whichWall == "down"){
                myScreen[1+shift+offsetH+height-1][1+shift+offsetW+((width-1)/2)] = "@";

//                mvwprintw(mapSeg1,height-1,width/2,"@"); // print the Item
            }
        }
        if(portalIndex == otherIndex){
            if(whichOtherWall == "right") {
                myScreen[1+shift+offsetH + ((height-1)/2)][shift+width+offsetW] = "@";
//                mvwprintw(mapSeg1, height/2 -2, width-1, "@"); // print the Item
            }else if(whichOtherWall == "left"){
                myScreen[shift+offsetH+((height-1)/2) +1][shift+1+offsetW] = "@";
//                mvwprintw(mapSeg1, height/2 -1,0,"@"); // print the Item
            }else if(whichOtherWall == "up"){
//                myScreen[0][portalWidth] = "@";
                myScreen[1+shift+offsetH + 0][1+shift+offsetW+((width-1)/2)] = "@";


//                mvwprintw(mapSeg1,0,width/2,"@"); // print the Item
            }else if(whichOtherWall == "down"){
                myScreen[1+shift+offsetH+height-1][1+shift+offsetW+((width-1)/2)] = "@";

//                mvwprintw(mapSeg1,height-1,width/2,"@"); // print the Item
            }
        }
        ss.str("");
        ss.clear();
    }
//    WINDOW *screen = newwin(screenHeight, screenWidth, 0, 0);
//    std::cout << x.c_str();
//    wprintw(screen, x.c_str(),i, j);
//    printw("\n");
//            printw("%s\n",x.c_str());





//    std::cout << "Level: " << mapSegmentIndex+1 << "\n";
//    std::cout << "Items remaining: " << Items.size() << "\n";
    int itemSizeCurses = Items.size();
    int mapIndexCurses = mapSegmentIndex+1;
    WINDOW *myWindow = newwin(screenHeight+3, screenWidth, 0, 0);
    curs_set(0); //hide blink cursor

    wprintw(myWindow, "Level: %d\n",mapIndexCurses);
    wprintw(myWindow,"Items remaining: %d\n",itemSizeCurses);
    wprintw(myWindow, "Moves remaining: %d\n",Moves);

//    std::cout << "Moves remaining: " << Moves << "\n";
//    int shiftScreenH = screenHeight + shift;


    for(int i = 0+shift; i < screenHeight+shift; i++) {
        for (int j = 0+shift; j < screenWidth+shift; j++) {
            myScreen[i][0+shift] = '*';
            myScreen[0+shift][j] = '*';
            myScreen[screenHeight-1+shift][j] = '*';
            myScreen[i][screenWidth-1+shift] = '*';
            std::string tempScreenCurses = myScreen[i][j];
            wprintw(myWindow, "%s",tempScreenCurses.c_str());
//            std::cout << myScreen[i][j];
        }
//        wprintw(myWindow, "\n");

    }
    refresh();
    wrefresh(myWindow);
    delwin(myWindow);
//    getch();
//    setWindow(&screen);


}
