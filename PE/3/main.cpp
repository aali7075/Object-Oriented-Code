#include <iostream>

// Name: Aaron Li
//

// Write any functions you need here!
void intPt(int * val){
  std::cout << "The pass by a pointer function returns" << (*val)<< '\n';
}

void intRef(int  &val){
  std::cout << "The pass by reference function returns " << val<< '\n';
}

void intOut(const int &val, int * val_out){
  *(val_out)=val*2;

}

// Create custome classes
class Point {
  public:
    Point(int x, int y){ // constructor
      x_=x;
      y_=y;
    }
    // Override functions
    bool operator==(const Point & p2){
       return (x_==p2.x_&& y_ ==p2.y_);
    }
    Point operator+(const Point & p2){
      return Point((x_+p2.x_),(y_+p2.y_));


    }

    // getters declared
    int get_x() { return x_; }

    int get_y() { return y_; }

    // setters declared
    void set_x(int num) { x_= num;}

    void set_y(int num) { y_= num;}


  private:
    int x_;
    int y_;


};



int main() {
    // Add as many prints to cout as you need to answer the questions.
    // Leave them in your code when you turn it in.
    // If you have lines of code that cause errors that test the questions,
    // leave this code in your file but comment it out.

    // 1) Declare an int
    int x=1;

    // 2) Declare a pointer to that int
    int* x_pt=&x;

    // 3) Increment the int via the pointer
    (*x_pt)++;
    std::cout << x << '\n';
    // 4) Declare a reference to your int
    int &y=x;
    // 5) Increment the int via the reference
    y++;
    std::cout << x << '\n';

    // 6) When you increment the int via the variable declared in #1, which
    // variables will be modified to see the changes? (the pointer , reference or both?)
    x++;
    std::cout <<*(x_pt)<< '\n';
    std::cout <<y<< '\n';
    // Answer: Both of them can see the increment

    // 7) When you increment the int via the pointer declared in #2, which
    // variables will be modified to see the changes?
    (*x_pt)++;
    std::cout <<x<< '\n';
    std::cout <<y<< '\n';
    // Answer: Both?

    // 8) When you increment the int via the reference declared in #4, which
    // variables will be modified to see the changes?
    y++;
    std::cout <<x<< '\n';
    std::cout <<y<< '\n';
    // Answer: The variable and the reference  both change

    // 9) Write a function that takes an int * parameter. How would you pass the
    // variable from #1 into this function? (write the function header and function call below)

    //std::cout << intPt(x) << '\n'; Not Possible returns mismatch type error


    // 10) Can you pass your reference from #4 to the function from #9 without accessing its address?
    // Answer: No not possible pointers need a memory address

    // 11) Write a function that takes an int & parameter. How would you pass the
    // variable from #1 into this function? (write the function header and call below)
      intRef(x); // pass the varible an the & in the header will deference it

    // 12) Can you pass your pointer from #2 to the function from #11 without dereferencing it?
    // Answer: NO
      //intRef(x_pt);

    // 13) Can you pass your reference from #4 to the function from #11?
    // Answer: Yes
      intRef(y);
    // 14) Write a function that takes one const reference input parameter and one pointer
    // output parameter. The function should fill in the value of the output parameter based
    // on the value of the input parameter. (what it does exactly is up to you).
    // Call your function 3 times below. Be sure to include output as necessary to be sure
    // your function works as described.
    for(int i=0; i<3; i++){ // output 3 times
    intOut(x,x_pt);
    std::cout << "The value of x_pt is now " <<(*x_pt) << '\n';
    }

    // 15) What is/are the difference(s) between output parameters and return values?
    // Answer: Output parameters are pass by reference so we don't need to return anything to see the change occur
    // Return values are

    // 16) Create a custom class with at least one private field/class attribute. Overload the == and + operator for this class
    // such that == can be used to compare the objects of the class and + can be used to add
    // 2 objects of the class together. Implement an appropriate constructor for your class.
    // When you overload these operators, the resulting return value should make sense.
    // Instantiate at least 2 objects of this class and perform the == and + operations on them.
    // hint: for operator+, the function signature when implemented as a member function of the Object class is:
    // Object operator+(const Object &other)
    // Answer:
    Point p1= Point(3,4);
    Point p2= Point(3,4);
    std::cout <<"p1 and p2 x value are " <<p1.get_x() <<" y values are " <<p1.get_y()<<'\n';
    std::cout <<"p1==p2 returns "<<(p1==p2) << '\n';
    Point p3=p1+p2;
    std::cout <<"p3 x value is " <<p3.get_x() <<" y is " <<p3.get_y()<<'\n';
}
