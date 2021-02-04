#ifndef CURSES_VIEW_HPP
#define CURSES_VIEW_HPP

#include <curses.h>


#include "view.hpp"

/**
 * You shouldn't have to change this header file.
 * Implement the functions defined in the source file.
 */

class CursesView : public View
{
public:  // public methods
    CursesView(int height, int width);
    virtual ~CursesView();
    CursesView(const CursesView&) = delete;
    CursesView& operator=(const CursesView&) = delete;
    virtual void draw(const std::vector<std::string>& lines) override;

    void setHeight(int h);
    void setWidth(int w);
//    WINDOW* setScreen(WINDOW *curScreen);
//    WINDOW* getWindow();
//
    void setMapSegment(int mapIndex);
    int getMapSegment();




private:
    int mapSegmentIndex = -1;

    int iteration = 0;
//    WINDOW *screen;
    std::vector<std::vector<std::string>> myScreen;
    std::vector<std::vector<std::string>> myMapSeg;



    std::vector<std::string> MagSegments;
    std::vector<std::string> Buildings;
    std::vector<std::string> Portals;
    std::vector<std::string> Items;
    int Moves;
    int screenHeight, screenWidth;

    std::string playerOrientation;
};

#endif // CURSES_VIEW_HPP
