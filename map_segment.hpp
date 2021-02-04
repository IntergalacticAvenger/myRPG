#ifndef MAP_SEGMENT_HPP
#define MAP_SEGMENT_HPP

#include <string>
#include <vector>

#include "building.hpp"
#include "item.hpp"


/**
 * This is probably the class that will have the second biggest portion of
 * your code for this assignment. (The biggest would likely be held
 * by the Game class.)
 *
 * Some things I did that you don't have to do:
 * - Define an enum class for portal directions.
 * - Method for connecting two map segments' portals.
 * - Methods for adding buildings or items to a map segment.
 */

class MapSegment
{
public:

    MapSegment(int height, int width);

//    void createModel(std::vector<std::string> &modelVector);



//    void setBuildings(std::vector<std::string> &buildings);
//    void setPortal(std::vector<std::string> &portals);
//    void setItem(std::vector<std::string> &items);
//    std::vector<std::string> const &getMapSegment();
//    void setMapSegment(std::vector<std::string> &mapsegment);
//    std::vector<std::string> getMapSegment();
//    void setPortals(std::vector<std::string> &myportals);
//    std::vector<std::string> getPortals();


    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }
    int getPortalX() const { return mPortalX; }
    int getPortalY() const { return mPortalY; }

    /**
     * Returns representation of this map segment as a vector of strings,
     * including any contained items and buildings.
     */

private:
//    std::vector<std::string> modelVec();
//    std::string currLine, garb, tempMove;
//    std::string playerStartHeight,playerStartWidth, playerOrientation;
//    int pStartHeight,pStartWidth;
//    int mapSegindex;
//
//
//
//    std::vector<std::string> mapSegments;
//    std::vector<std::string> buildings;
//    std::vector<std::string> portals;
//    std::vector<std::string> items;
//    int moves;


    static char VERTICAL_BORDER_CHAR;
    static char HORIZONTAL_BORDER_CHAR;
    static char PORTAL_CHAR;

    /**
     * As always, you don't need to have these member variables if you don't
     * think they would be useful to you.
     */

    int mHeight;
    int mWidth;
    /**
     * For helping position the portals.
     * See how they are initialized in the constructor.
     */
    int mPortalY;
    int mPortalX;
};

#endif // MAP_SEGMENT_HPP
