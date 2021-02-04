#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"
#include "view.hpp"
#include "interface_type.hpp"
#include "map_segment.hpp"
#include <ncurses.h>
class Game
{
protected:
    InterfaceType mInterface;

public:  // public methods
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    Game(const std::string& filename, InterfaceType interfaceType);

    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    /**
     * DO NOT change the prototype of this function.
     * The autograder WILL call this function.
     */
    void run();

private:  // private methods
    /**
     * You DO NOT need to have any of the private methods below.
     * I just left some commented out declarations in case it
     * helps guide your thinking, but you don't need to use them.
     */

    /**
     * Set up the vector of stringS that is then given to the draw()
     * method of an instance of a subclass of View.
     */
    // void draw();

    /**
     * Loop until the game is over. On each iteration, use the controller
     * to get input from the user.
     */
//     void doGameLoop();

    /**
     * Update matters related to game logic, e.g. collisions, level completion.
     */
     void update(std::vector<std::string> currentBoard);
     void setNextOrientation();
     int preparePortals();
     void newStartingPositions();
     void itemHandler();
     int areWeHittingItem(int height, int width);
     int areWeHittingBuilding(int height, int width);
     void NextLevelBaby();
     void isTherePortalSet(int isThereP);

    /**
     * Load information related to new level into member variables,
     * being careful to not leave traces of information from previous levels. 
     */
//     void loadLevel(std::vector<std::string> drawInfo);

private:
    static const int MIN_VIEW_HEIGHT;
    static const int MIN_VIEW_WIDTH;
    static const char HERO_ICON_LEFT;
    static const char HERO_ICON_RIGHT;
    static const char HERO_ICON_UP;
    static const char HERO_ICON_DOWN;
    bool moveFORWARD;
    bool LEFT;
    bool RIGHT;
    bool DOWN;
    bool INVALID;
    bool EXIT;
    int didUserChangeOrientation;
    static int iterations;


//    int height, width, levels;
    std::vector<std::string> levelFiles;
    std::vector<std::string> drawInfo;
    std::vector<std::vector<std::string>> currentScreen;
    std::vector<std::string> orientationVec;
    std::string currDirection;
    std::vector<std::string> Buildings, Portals;

    int xLoc, yLoc, xMax, yMax;
    char character;
    WINDOW *curwin;
    std::string CURRENT_ICON;
    int currentMapIndex;
    std::string currLine, pHeight, pWidth,pOrientation, garbage, mapHeight, mapWidth;
    int height, width,OGMapHeight, OGMapWidth, levels;
    std::string currentPortalIndex ,firstMapWall, firstMapIndex, secondMapWall,secondMapIndex;
    bool portalTaken = false;
    std::vector<int> currentMapPortal;
    std::vector<std::string> currMapPortalOrientation;
    int portalStartH,portalStartW;
//    int portalHeight = (OGMapHeight - 1) / 2;
//    int portalWidth = (OGMapWidth - 1) / 2; //sus
    std::string currentWall;

    std::string FILENAME;


    int yItem, xItem, itemIndex, totalItems;
    std::vector<std::string> Items;
    std::vector<std::string> currentLevelItems;
    std::vector<std::string> removedItemBoard;
    std::string itemToRemove;

    std::string tempMove, garb;
    int totalMoves = -1;

    int totalLevels;
    int currLVL = 1;
    std::string tempLevel;

//    int portalResult;
    int isTherePortal;
    int buildingYStart,buildingXStart;







    /**
     * Because one of the constructor parameters must be checked in order
     * to determine the subclass types for the below members, they can't
     * be references, because there's no default constructors for them.
     * (Recall that each member in a class must either be initialized by an
     * initializer list in the constructor OR have a default constructor.)
     */
    View* mView;
    Controller* mController;

    InterfaceType mInterfaceType;



};

//Game::Game(WINDOW *win, int y, int x, char c){
//    curwin = win;
//    yLoc = y;
//    xLoc = x;
//    getmaxyx(curwin, yMax, xMax);
//    keypad(curwin, true);
//    character = c;
//}

#endif // GAME_HPP
