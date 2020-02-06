/**
Aaron Li
HW 1
This program will run a maze game
*/

#include "Maze.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

int main(){
  Player aaron=Player("Aaron",true);
  aaron.ChangePoints(3);
  aaron.SetPosition(Position{0,0});

  // std::cout << aaron << '\n';
  // std::cout << aaron.ToRelativePosition(Position{-8,-9}) << '\n';

  Board test=Board();
  std::cout << test << '\n';
  test.get_square_value(Position{0,0});
  std::vector<Position> check_moves=test.GetMoves(&aaron);
  for(int i=0; i< check_moves.size(); i++){
    std::cout <<"Possible Positions " <<check_moves[i].row <<" " <<check_moves[i].col <<'\n';
  }

  // bool yeet=test.MovePlayer(&aaron, Position{1,0});
  // std::cout << yeet << '\n';
  // std::cout << test << '\n';

}
