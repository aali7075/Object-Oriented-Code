/**
Aaron Li
PE 1
This program is creates points and performs different
operations such as distance and translation
No arguments needed just run ./main
*/

#include "Point.h"
#include <iostream>



int main (){
  Point p1= Point(3);
  std::vector<int> dim{10,20,30,40}; // Create a vector
  Point p2= Point(dim);
  Point p3=Point(std::vector<int> {10,20,30});

  std::cout << "The dimensions of p1 are " << "( ";  //Output the points
  p1.PrintPoint();
  std::cout << ")" << '\n';


  std::cout << "The dimensions of p2 are " << "( ";  //Output the points
  p2.PrintPoint();
  std::cout << ")" << '\n';

  std::cout << "The dimensions of p3 are " << "( ";  //Output the points
  p3.PrintPoint();
  std::cout << ")" << '\n';

  /**
  Note the line below will throw an  invalid_argument error if it is uncommented since the points are not the same.
  std::cout<<"The distance between p1 and p2 is "<<p1.Distance(p2)<<std::endl;
  */

  std::cout<<"The distance between p1 and p3 is "<<p1.Distance(p3)<<std::endl;

	std::cout<<"p3 will be translated by 3!"<<std::endl; // Output translation
	p3.Translate(3);

  
  std::cout << "The new dimensions of p3 are " << "( ";  //Output the points
  p3.PrintPoint();
  std::cout << ")" << '\n';
	std::cout<<"The distance between p1 and p3 is "<<p1.Distance(p3)<<std::endl;

}
