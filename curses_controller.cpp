#include "curses_controller.hpp"

#include <curses.h>

CursesController::~CursesController()
{
}

Command CursesController::getInput()
{
//    std::cout << "Enter input: ";
//    std::cin >> ch;

    int choice = getch();

    //    printw("chice is %d", choice);
//    std::string str = std::to_string(choice);
    if(choice == '\033' ){
        getch();
        int actualCommand = getch();
        if(actualCommand == 'A'){
            return Command::Forward; //up key / 'w' key
        }else if(actualCommand == 'D') {
            return Command::Left; //arrow left aka our 'a' key
        }else if(actualCommand == 'C'){
            return Command::Right; //arrow right aka our 'd' key LOl why is this inversed
        }else if(actualCommand == 'B'){
            return Command::Invalid; //invalid aka 's' or down key
        }
    }
//    else if(choice == 'a'){
//        return Command::Left;
//    }
//    else if(choice == 'd'){
//        return Command::Right;
//    }else if(choice == 'q'){
//        return Command::Quit;
//    }else if(choice == 's'){
//        return Command::Invalid;
//    }



    if(choice == 'w'){
        return Command::Forward;
    }else if(choice == 'a'){
        return Command::Left;
    }else if(choice == 'd'){
        return Command::Right;
    }else if(choice == 'q'){
        return Command::Quit;
    }else if(choice == 's'){
        return Command::Invalid;
    }
//    else if(str.length() > 1){
//        return Command::Invalid;
//    }





//     To prevent a compiler error in the starter files...
    return Command::Invalid;
}
