#include "Point.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

/**
  Pushes n values of 0 into the vector
	n specifies the amount of dimensions
  Modifies the private vector varibale dim_
*/
Point::Point(int n) {
  for(int i=0; i<n; i++){
    dim_.push_back(0);
  }
}

/**
  Pushes the values of another vector into dim_
  dim represents the vector being copied into dim_
*/
Point::Point(std::vector<int> dim) {
  for (unsigned int i=0; i<dim.size(); i++){
    dim_.push_back(dim[i]);
  }
}

/**
  Prints the values inside of the vector dim_
*/
void Point::PrintPoint() {
   for(unsigned int i=0; i < dim_.size(); i++){
      std::cout << dim_[i] << ' ';
    }
}

/**
    Returns a double and calculates the euclidean distance formula
	  Uses self as the 1st point
	  p2 is another point

    Throws error if dimensions size is not the same between 2 points
*/
double Point::Distance(Point p2) {
  if(dim_.size()!=p2.get_dim().size()) {
    throw std::invalid_argument("Please ensure both points are same dimension");
  }
  double val=0.0;
  for (unsigned int i=0; i<dim_.size(); i++){
      val+=pow((dim_[i]-p2.get_dim()[i]),2);
  }

    return sqrt(val);  // Also can use this -> to refer

}

/**
    Changes the private varibles dim_ for a Point class instance
	  val is the integer that we are changing each dim_ element by
*/
void Point::Translate(int val){
  for (unsigned int i=0; i<dim_.size(); i++){
      dim_[i]+=val;
  }
}
