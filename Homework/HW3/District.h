#ifndef DISTRICT_H
#define DISTRICT_H

#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>



enum class Parties{Pancakes, Waffles, Crepe, No_Party };

std::string enum_to_string(Parties type);

std::vector<Parties> enum_to_vec();

class District {
public:
	// TODO: implement
	District();  // constructor

	int get_miles(){return square_miles_; };

	std::map<Parties,int>  get_constituents(){return constituents_; };

	void Campaign(Parties party);

	void ChangeNoParty(Parties party);

 // Either override operator<< for Player or implement the following function
 friend std::ostream& operator<<(std::ostream& ouput, const District& district);


private:
  int square_miles_;
  std::map<Parties,int> constituents_;

}; // class District


#endif  // DISTRICT_H
