#include "Board.h"

/**
Constructor for the board class.
Each board is a 4 by 4 array from a SquareType enum
The player always starts at the 0,0 (top left position)
The exit is always on the 4,4 (bottom right position)
The walls have a 20% chance of being spawned from square not on player or exit
Treasure has a 10% chance of being spawned on a location that is not a walls
*/
Board::Board(){
  int board_len=sizeof(arr_)/sizeof(arr_[0]);
  bool wall_prob;
  bool treasure_prob;
  srand(time(NULL)); // en
  for(int i=0; i<board_len; i++){
    for(int j=0; j<board_len; j++){ // The board is always square
      wall_prob=(rand()%100)<20;
      treasure_prob=(rand()%100)<10;
      if(!wall_prob && treasure_prob){ // If wall is false and treasure is true place on treasure
        arr_[i][j]=SquareType::Treasure;
      }
      else if(wall_prob){
        arr_[i][j]=SquareType::Wall;
      }
      else{
        arr_[i][j]=SquareType::Empty;
      }
      std::cout << static_cast<int>(arr_[i][j]) << '\n';
    }
  }
  arr_[0][0]=SquareType::Human; // Humans and exit must happen so assigned values at the end
  arr_[board_len-1][board_len-1]=SquareType::Exit;

}
