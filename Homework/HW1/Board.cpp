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
    }
  }
  arr_[0][0]=SquareType::Human; // Humans and exit must happen so assigned values at the end
  arr_[board_len-1][board_len-1]=SquareType::Exit;

}
/**
ASK ABOUT THIS
*/
std::ostream& operator<<(std::ostream& os, const Board &b){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      int enum_val= static_cast<int>(b.arr_[i][j]);
      std::cout <<"Board at " +std::to_string(i) +" "+ std::to_string(j) +" is "<<b.Square_name_[enum_val] <<'\n';
    }
  }
  std::cout << "";
}

/**
Returns the square type for the given square on the board
Input parameters:
pos is a Position struct that gives the location on the board for our square
*/

SquareType Board::get_square_value(Position pos) const{
  return arr_[pos.row][pos.col];
}

void Board::SetSquareValue(Position pos, SquareType value){
  arr_[pos.row][pos.col] =value;
}

/**
Returns all the possible Places player can move
Input parameters:
p as A a Player class instance
Take the board and copy the 4 by 4 array and pad it into a 6 by 6 array where
All along the edges are walls.
This will prevent segfaults from occuring and make code more consistent
*/
std::vector<Position> Board::GetMoves(Player *p){
  Position pos= p->get_position();
  int row= pos.row;
  int col= pos.col;
  SquareType arr_copy[6][6];
  std::vector<Position> moves{Position{row-1,col},Position{row+1,col},Position{row,col+1},Position{row,col-1}}; // index corresponds to up down right left
  for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
      if(i==0 || j==0 || i==5 ||j==5){ // Pad the outside squre with wall
        arr_copy[i][j]=SquareType::Wall;
        continue;
      }
      arr_copy[i][j]=arr_[i-1][j-1];
    }
  }

  SquareType up=arr_copy[row][col+1]; // Since arr_copy is padded then the real array is start at 1 row and 1 col position
  SquareType down=arr_copy[row+2][col+1];
  SquareType right=arr_copy[row+1][col+2];
  SquareType left=arr_copy[row+1][col];
  std::vector<SquareType> directions{up,down,right,left};
  for(int i=3; i>-1; i--){ // Since we are deleting positions we need  to start from end otherwise well get a seg fault
    if(directions[i]==SquareType::Wall || directions[i]==SquareType::Enemy){
      moves.erase(moves.begin()+i); // Erase any position that has a wall or enemy
    }
  }

return moves;

}

/**
MovePlayer will move try to move a player to a pos
Input parameters
p is the player
pos is the place we want to go to

Call the GetMoves function on player and then check if position is inside the possible moves
If it is  move the player and return true, otherwise return false
*/
bool Board::MovePlayer(Player *p, Position pos){
  std::vector<Position> moves= GetMoves(p); // Why do I not need to pass in a mememory adress?
  Position player_old_pos=p->get_position(); // When do I use dot and when do I use ->
  int moves_size=moves.size();
  Position moves_pos;
  for(int i=0; i<moves_size; i++){
    moves_pos= moves[i];
    std::cout << moves_pos.row <<" " <<moves_pos.col<<'\n';
    if (moves_pos.row==pos.row && moves_pos.col==pos.col){
      SetSquareValue(player_old_pos, SquareType::Empty);
      SetSquareValue(pos, SquareType::Human);
      p->SetPosition(pos);
      return true;
    }
  }
  return false;
}

/**
GetExitOccupant will check if the human is at the exit

Call the get_square_value method on the exit square which is always 3,3
*/
SquareType Board::GetExitOccupant(){
  return get_square_value(Position{3,3});
}
