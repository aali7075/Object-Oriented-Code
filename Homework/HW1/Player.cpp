#include "Player.h"
#include <iostream>
/**
Player intialize an instance of the Player class
Input parameters:
name is the name of the player
is_human checks whether the player is a person or enemy
*/
Player::Player(const std::string name, const bool is_human){
  name_=name;
  points_=0;
  is_human_=is_human;
}
/**
Changes the point value of a specific player
Input parameters:
x determines how much points_ will be changed
*/
void Player::ChangePoints(const int x){
  points_+=x;
}
/**
Set the Position of the player
Input parameters:
pos is the position of the player
*/
void Player::SetPosition(Position pos){
  pos_=pos;
}
/**
Gives the Relative Position from the Player.
Since the player will only be able to go up, down, left, or right, at one time
Only print one of those directions
Input parameters:
other is a Position and is compared to the players position
*/
std:: string Player:: ToRelativePosition(Position other){
  std::string pos_description;
  int col_direct= other.col-pos_.col;
  int row_direct= other.row-pos_.row ;
  if(row_direct<0){
    pos_description+="UP";
  }
  else if (row_direct> 0){
    pos_description+="DOWN";
  }
  else if (col_direct>0){
    pos_description+="RIGHT";
  }
  else{
    pos_description+="LEFT";
  }
  return pos_description;

}

/**
Overide the cout operator for player
*/
std::ostream& operator<<(std::ostream& ouput, const Player& player){
  std::cout<<player.name_<<" "<<player.points_;
}
