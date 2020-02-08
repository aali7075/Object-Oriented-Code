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
  bool wall_prob;
  bool treasure_prob;
  bool good_treasure_prob;
  bool best_treasure_prob;
  srand(time(NULL)); // en
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){ // The board is always square
      wall_prob=(rand()%100)<20;
      treasure_prob=(rand()%100)<10;
      if(!wall_prob && treasure_prob){ // If wall is false and treasure is true place on treasure
        good_treasure_prob=rand()%100<50; //Generator functions from good and best treaures
        best_treasure_prob=rand()%100<10;
        if(good_treasure_prob){
          arr_[i][j]=SquareType::Good_Treasure;
        }
        else if(best_treasure_prob){
          arr_[i][j]=SquareType::Best_Treasure;
        }
        else{
        arr_[i][j]=SquareType::Treasure;
        }
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
  arr_[3][3]=SquareType::Exit;

}
/**
SquareTypeStringify will take a SquareType and give it the corresponding emoji
Input parameters:
sq is the square that will be converted to corresponding emoji
*/
std::string SquareTypeStringify(SquareType sq){
  std::string wall= "\U0001F6AB"; //Unicode for emoji
  std::string exit = "\U0001F697";
  std::string empty= "\U00002B1C";
  std::string human= "\U0001F628";
  std::string treasure= "\U0001F4B5";
  std::string good_treasure= "\U0001F4B8";
  std::string best_treasure= "\U0001F4B0";
  std::string enemy= "\U0001F479";

  switch(sq){ //Use a switch case for simplicity
    case SquareType::Wall : return wall;
    case SquareType::Exit : return exit;
    case SquareType::Empty : return empty;
    case SquareType::Human : return human;
    case SquareType::Treasure : return treasure;
    case SquareType::Good_Treasure : return good_treasure;
    case SquareType::Best_Treasure : return best_treasure;
    case SquareType::Enemy : return enemy;
    default : return "Not an SquareType value";
  }
}

/**
Override the cout operator for board and print the "UI" for the Board
Call SquareTypeStringify and after after each row create a new line
*/
std::ostream& operator<<(std::ostream& os, const Board &b){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      std::cout<<SquareTypeStringify(b.arr_[i][j])<<" ";
    }
    std::cout << '\n';
  }
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
    if(directions[i]==SquareType::Wall){
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
  std::vector<Position> moves= GetMoves(p);
  Position player_old_pos=p->get_position(); // Store players position before they move
  int moves_size=moves.size(); // Intailize size outside of for loop for effciecny
  SquareType new_pos_type; //Used to check treaures
  for(int i=0; i<moves_size; i++){
    if (moves[i]==pos){ // If chosen position is one of the positions from GetMoves
      p->SetPosition(pos);
      new_pos_type=get_square_value(pos);
      switch(new_pos_type){ // FOR PART 2 OF CREATING 2 NEW TREASURES
        case SquareType::Treasure:
          p->ChangePoints(100);
          std::cout << p->get_name()+ " got 100 Points!" << '\n';
        case SquareType::Good_Treasure:
          p->ChangePoints(200);
          std::cout << p->get_name()+ " got 200 Points!" << '\n';
        case SquareType::Best_Treasure:
          p->ChangePoints(500);
          std::cout << p->get_name()+ " got 500 Points!" << '\n';
      }
      if(p->is_human()){
        SetSquareValue(pos, SquareType::Human);
      }
      else{
        SetSquareValue(pos, SquareType::Enemy);
      }
      SetSquareValue(player_old_pos, SquareType::Empty);
      if(player_old_pos==Position{3,3} && !(p->is_human())){ // If enemy is on exit change square type back to exit
        SetSquareValue(Position{3,3}, SquareType::Exit);
      }
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
