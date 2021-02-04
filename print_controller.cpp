#include "print_controller.hpp"


#include <iostream>



PrintController::~PrintController()
{
}

void PrintController::setVec(std::vector<std::vector<std::string> > myVec) {
    myScreen = myVec;
//    std::cout << myScreen[0][0] << "\n";
}

//std::vector<std::vector<std::string>>& PrintView::getVec() {
//    return myScreen;
//}


Command PrintController::getInput()
{

    std::cout << "Enter input: ";
    std::cin >> ch;



    if(ch == "w"){
      return Command::Forward;
    }else if(ch == "a"){
        return Command::Left;
    }else if(ch == "d"){
        return Command::Right;
    }else if(ch == "q"){
        return Command::Quit;
    }else if(ch == "s"){
        return Command::Invalid;
    }
//    else if(ch.length() > 1){
//        return Command::Invalid;
//    }





//     To prevent a compiler error in the starter files...
    return Command::Invalid;
}

