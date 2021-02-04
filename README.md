# myRPG

RPG Game creating using a N by N matrix. Imported from an existing gameFile.
gameFile follows the structure: (absolute/relative the file will load)
```
  20 25
  2
  demo_level1.txt
  foo/demo_level2.txt
```
Line 1 = Size of the game board
Line 2 = The level you will start on upon loading the game

```
  0
  6 2
  down
  M 12 15
  B 0 4 4
  I 0 8 1
  N 20
```
This is demo_level1.txt: (format is the same for all level files)
Line 1 = Index of the first map you will start in
Line 2 = Position of the player upon loading game (will always be in the center of the user playing the game's map)
Line 3 = The direction the player will be facing upon loading game
Line 4 = Map Segment 0's size (can have more than one Map Segment)
Line 5 = Building's location (can have more than one Building per Map Segment)
Line 6 = Item's location (can have more than one Item per Map Segment)
Line 7 = Number of moves till game is over

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
