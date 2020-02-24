/**
Aaron Li

Bugs in the original:
Rectangle constructor could take any point not just bottom left and top right
Overlap bug doesnt check if the lower left point is touching the upper left point of rectangle

Shrink on y allows for negative space
*/

#include "Rectangle.h"

Rectangle::Rectangle(Point p1, Point p2){
  int tmp;
  if(p1.x>=p2.x){
    tmp = p1.x;
    p1.x = p2.x;
    p2.x = tmp;
  }
  if(p1.y>=p2.y){
    tmp = p1.y;
    p1.y= p2.y;
    p2.y=tmp;
  }
  p1_=p1;
  p2_=p2;

}

int Rectangle::GetWidth(){
  return p2_.x-p1_.x;
}

int Rectangle::GetHeight(){
  return p2_.y-p1_.y;
}

bool Rectangle::Overlaps(Rectangle& other){
  int r1_p1_x= p1_.x;
  int r1_p2_x=p2_.x;
  int r1_p1_y= p1_.y;
  int r1_p2_y=p2_.y;

  int r2_p1_x= other.get_p1().x;
  int r2_p2_x=other.get_p2().x;
  int r2_p1_y= other.get_p1().y;
  int r2_p2_y=other.get_p2().y;

  // Check if either x val from other rectangle and check if it is not in the x-interval of the current rectangle
  if((r2_p2_x<r1_p1_x) || (r2_p1_x>r1_p2_x)){
    return false;
  }
  else{
    if ((r2_p2_y<r1_p1_y) || (r2_p1_y>r1_p2_y)){ // Check if top side of other rect is etiher lower or higher than other rectangle
      return false;
    }
  }
  return true;

}


int Rectangle::CalculateArea(){
  return (this-> GetWidth()*this-> GetHeight());
}

void Rectangle::Expand(){
  p1_.x--;
  p1_.y--;
  p2_.x++;
  p2_.y++;

}

void Rectangle::Shrink(){
  int diff_x= p2_.x-p1_.x;
  int diff_y= p2_.y-p1_.y;

  if(diff_x<=1 || diff_y<=1){ // If distance between points is less than 2 then we go into inverse space
    return;
  }
  p1_.x++;
  p1_.y++;
  p2_.x--;
  p2_.y--;

}
