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
aaron.SetPosition(Position{4,5});

std::cout << aaron.get_name() << " "<< aaron.get_points()<<'\n';
std::cout << aaron.ToRelativePosition(Position{-8,-9}) << '\n';
}
