#ifndef PRINT_CONTROLLER_HPP
#define PRINT_CONTROLLER_HPP


#include <string>
#include "controller.hpp"
#include "print_view.hpp"


//PrintView *p = new PrintView(0,0);

class PrintController : public Controller
{
public:
    PrintController() = default;
    virtual ~PrintController() override;
    PrintController(const PrintController&) = delete;
    PrintController& operator=(const PrintController&) = delete;
    virtual Command getInput() override;
//    WINDOW* setWindow(WINDOW *curWin);
//    WINDOW* getWindow();
//
    void setVec(std::vector<std::vector<std::string>> myVec);
//    std::vector<std::vector<std::string>> & getVec();


private:
    WINDOW *curWin;
    std::string ch;
    std::vector<std::vector<std::string>> myScreen;

};





#endif // PRINT_CONTROLLER_HPP
