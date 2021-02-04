#ifndef PRINT_VIEW_HPP
#define PRINT_VIEW_HPP

#include "view.hpp"
//#include "map_segment.hpp"
#include <ncurses.h>
/**
 * You shouldn't have to change this header file.
 * Implement the functions defined in the source file.
 */


class PrintView : public View
{

public:  // public methods
    PrintView(int height, int width);
    virtual ~PrintView();
    PrintView(const PrintView&) = delete;
    PrintView& operator=(const PrintView&) = delete;
    virtual void draw(const std::vector<std::string>& lines) override;

    //not supposed to use curses in print scratching this
    WINDOW** setWindow(WINDOW **curWin);
    WINDOW* getWindow();
    WINDOW** setBorder(WINDOW **curWin);
    WINDOW* getBorder();

    void setHeight(int h);
    void setWidth(int w);
    void setVec(std::vector<std::vector<std::string>>& myVec);
    std::vector<std::vector<std::string>> & getVec();
    void setMapSegment(int mapIndex);
    int getMapSegment();




//        std::string previousGameIcon();
    //    struct WinInfo{
//        WINDOW *curwin;
//        int myInt;
//    };
//    int TheInt;



private:
    int mapSegmentIndex = -1;

    WINDOW *currentWindow;
    int iteration = 0;

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



#endif // PRINT_VIEW_HPP
