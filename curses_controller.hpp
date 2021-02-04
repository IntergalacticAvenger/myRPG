#ifndef CURSES_CONTROLLER_HPP
#define CURSES_CONTROLLER_HPP

#include "controller.hpp"
#include <string>

class CursesController : public Controller
{
public:
    CursesController() = default;
    virtual ~CursesController() override;
    CursesController(const CursesController&) = delete;
    CursesController& operator=(const CursesController&) = delete;
    virtual Command getInput() override;
private:
    std::string ch;

};

#endif // CURSES_CONTROLLER_HPP
