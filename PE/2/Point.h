#ifndef _POINT_H_ //Header Guard
#define _POINT_H_
#include <vector>

// declare
class Point {
    public:

        Point(int n); // One constructor represents dimension

        Point(std::vector<int> dim); // For n dimensino point

        void PrintPoint(); // Prints out the Point dimensions

        double Distance(Point p2);  // Calculate the Euclidean distance
        void Translate(int val);  // move the point by some val

        // getters declared
        std::vector<int> get_dim() {return dim_;}
        // setters declared
        void set_dim(std::vector<int> nums) {dim_=nums;}


    private:

        std::vector<int> dim_; // Private varibles should end with _
};

#endif  // end _POINT_H_ header guard
