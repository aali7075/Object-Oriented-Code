/**
Aaron Li
*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Rectangle.h"


// TEST_CASE ( "Factorials are computed", "[factorial]") {
//   REQUIRE( Factorial(2) == 2 );
//   REQUIRE( Factorial(3) == 6 );
// }

TEST_CASE ( "Rectangle constructor", "[rectangle]") {
  Rectangle r=Rectangle(Point{1,5},Point{-1,-3});
  Rectangle line_x=Rectangle(Point{6,5},Point{1,5});
  Rectangle line_y=Rectangle(Point{1,4},Point{1,2});
  Rectangle point=Rectangle(Point{1,5},Point{1,5});


  REQUIRE( r.get_p1().x<=r.get_p2().x);
  REQUIRE(r.get_p1().y<=r.get_p2().y);

  REQUIRE( line_x.get_p1().x<=line_x.get_p2().x);
  REQUIRE(line_x.get_p1().y<=line_x.get_p2().y);

  REQUIRE( line_y.get_p1().x<=line_y.get_p2().x);
  REQUIRE(line_y.get_p1().y<=line_y.get_p2().y);

  REQUIRE( point.get_p1().x<=point.get_p2().x);
  REQUIRE(point.get_p1().y<=point.get_p2().y);

  SECTION( "Checking the width the rectangle" ){
    REQUIRE(r.GetWidth()==2);
    REQUIRE(line_x.GetWidth()==5);
    REQUIRE(line_y.GetWidth()==0);
    REQUIRE(point.GetWidth()==0);

  }

  SECTION( "Checking the height the rectangle" ){
    REQUIRE(r.GetHeight()==8);
    REQUIRE(line_x.GetHeight()==0);
    REQUIRE(line_y.GetHeight()==2);
    REQUIRE(point.GetHeight()==0);

  }
  SECTION( "Checking for point overlap" ){
    Rectangle r_test=Rectangle(Point{-1,6},Point{1,10});
    r=Rectangle(Point{-1,-3},Point{1,5});
    line_x=Rectangle(Point{0,5},Point{1,5});
    line_y=Rectangle(Point{1,5},Point{1,8});
    point=Rectangle(Point{-4,-6},Point{-1,-3});
    REQUIRE(r.Overlaps(r)==true);
    REQUIRE(r.Overlaps(line_x)==true);
    REQUIRE(r.Overlaps(line_y)==true);
    REQUIRE(r.Overlaps(point)==true);
    REQUIRE(r.Overlaps(r_test)==false);


  }
  SECTION( "Checking the area of each cirle" ){
    REQUIRE(r.CalculateArea()==16);
    REQUIRE(line_x.CalculateArea()==0);
    REQUIRE(line_y.CalculateArea()==0);
    REQUIRE(point.CalculateArea()==0);
  }

  // // moves the bottom left coordinate down one and to the left one
  // // moves the upper right coordinate up one and to the right one
  r=Rectangle(Point{0,7},Point{3,9});
  SECTION( "Checking the expand" ){
    r.Expand();
    REQUIRE(r.get_p1().x==-1);
    REQUIRE(r.get_p1().y==6);
    REQUIRE(r.get_p2().x==4);
    REQUIRE(r.get_p2().y==10);
    REQUIRE(r.GetWidth()*r.GetHeight()==20);


    line_x.Expand();
    REQUIRE(line_x.get_p1().x==0);
    REQUIRE(line_x.get_p1().y==4);
    REQUIRE(line_x.get_p2().x==7);
    REQUIRE(line_x.get_p2().y==6);

    line_y.Expand();
    REQUIRE(line_y.get_p1().x==0);
    REQUIRE(line_y.get_p1().y==1);
    REQUIRE(line_y.get_p2().x==2);
    REQUIRE(line_y.get_p2().y==5);

    point.Expand();
    REQUIRE(point.get_p1().x==0);
    REQUIRE(point.get_p1().y==4);
    REQUIRE(point.get_p2().x==2);
    REQUIRE(point.get_p2().y==6);
  }
  r=Rectangle(Point{-1,-3},Point{1,5});
  line_x=Rectangle(Point{1,5},Point{6,5});
  line_y=Rectangle(Point{1,2},Point{1,4});
  point=Rectangle(Point{1,5},Point{1,5});

  // // moves the bottom left coordinate up one and to the right one
  // // moves the upper right coordinate down one and to the left one
  SECTION( "Checking the shrink" ){
    r=Rectangle(Point{1,5},Point{-1,-3});
    line_x=Rectangle(Point{6,5},Point{1,5});
    line_y=Rectangle(Point{1,4},Point{1,2});
    point=Rectangle(Point{1,5},Point{1,5});
    r.Shrink();
    REQUIRE(r.get_p1().x==0);
    REQUIRE(r.get_p1().y==-2);
    REQUIRE(r.get_p2().x==0);
    REQUIRE(r.get_p2().y==4);

    line_x.Shrink();
    REQUIRE(line_x.get_p1().x==1);
    REQUIRE(line_x.get_p1().y==5);
    REQUIRE(line_x.get_p2().x==6);
    REQUIRE(line_x.get_p2().y==5);

    line_y.Shrink();
    REQUIRE(line_y.get_p1().x==1);
    REQUIRE(line_y.get_p1().y==2);
    REQUIRE(line_y.get_p2().x==1);
    REQUIRE(line_y.get_p2().y==4);

    point.Shrink();
    REQUIRE(point.get_p1().x==1);
    REQUIRE(point.get_p1().y==5);
    REQUIRE(point.get_p2().x==1);
    REQUIRE(point.get_p2().y==5);
  }

}
