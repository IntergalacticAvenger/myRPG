# myRPG

RPG Game creating using a N by N matrix. Imported from an existing gameFile.

Movement:
  - Can only move forward with 'W' 
  - To move left/right/down, you need to use the 'A','D' key to reposition the player.

Running the game:
For the normal mode that supports 'WASD' keys
g++ -g -std=c++11  main.cpp  item.cpp  map_segment.cpp  curses_controller.cpp  print_controller.cpp  curses_view.cpp  print_view.cpp  game.cpp  view.cpp          building.cpp -o main -lcurses && ./main

For the Ncurses version of the game that uses the 'Left/Up/Right' arrow keys
g++ -g -std=c++11  main.cpp  item.cpp  map_segment.cpp  curses_controller.cpp  print_controller.cpp  curses_view.cpp  print_view.cpp  game.cpp  view.cpp  building.cpp -o main -lcurses && ./main r

Ojective:
  - Collect all items before the number of moves is == 0, if you do so you win!
  - If you collect the last item on the last move, you win!
  - Each level has a different number of items you need to collect. 

Some Screenshots of the game in action:
![Screenshot](https://user-images.githubusercontent.com/53759586/106840062-66f91380-666d-11eb-9d98-36bbff0d107f.png)

![Screenshot](https://user-images.githubusercontent.com/53759586/106840065-6791aa00-666d-11eb-8d9b-a9031f83732a.png)

![Screenshot](https://user-images.githubusercontent.com/53759586/106840066-6791aa00-666d-11eb-96f3-b4cd6de6c516.png)

Now let's say you collect all the items, then you will get this!
![Screenshot](https://user-images.githubusercontent.com/53759586/106840068-6791aa00-666d-11eb-85e1-5fdf61e746e9.png)
