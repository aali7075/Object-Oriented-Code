/**
Aaron Li
HW 1
This program will run a rudimentary maze game.
One User will be a human the other will be an enemy.
Collect treasures as you try to escape the maze!
Watch out though, there are randomly generated walls to prevent your both
If the enemy catches you lose, if human escapes then you win!
*/

#include "Maze.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

/**
For Step 2 of the game I made Two extra Treasures
The regular treasure is denoted by a standard bill and is 100 points 10% spawn rate
The good treasure is a flying money bill which is 200 points 5% spawn rate
The best treasure is a money sack which is 500 points! 0.5% spawn rate
*/

int main(){
  Player aaron=Player("Aaron",true);

  Maze *game= new Maze();
  game->NewGame(&aaron,1);
  game->TakeTurn(&aaron);
  game->GenerateReport();


}
