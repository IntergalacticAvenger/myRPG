#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

enum class Command
{
    // Changing how player is facing.
    Left,
    Right,

    // Movement.
    Forward,

    Quit,
    Invalid,


    };

class Controller
{
public:
    Controller() = default;
    virtual ~Controller() = default;
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    virtual Command getInput() = 0;



private:
    int xLoc, yLoc, xMax, yMax;
    char character;

};

#endif // CONTROLLER_HPP
