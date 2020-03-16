#ifndef ELECTORALMAP_H
#define ELECTORALMAP_H

#include "District.h"

//ElectoralMap is a singleton

class ElectoralMap {
public:

	static ElectoralMap& GetInstance() {
		// gets instantiated the first time
		static ElectoralMap instance; // guaranteed to be destroyed

		return instance;
	}

    District * get_district(int id) { return &District_[id]; };

		std::map<int, District> get_all_districts(){return District_;};
		void set_all_districts(std::map<int, District> old_districts){District_=old_districts;};


	// Delete the methods we don't want
	ElectoralMap(ElectoralMap const&) = delete; // copy constructor
	void operator=(ElectoralMap const&) = delete; // assignment operator

  static const int NUM_DISTRICTS;

	// Either override operator<< for Player or implement the following function
	friend std::ostream& operator<<(std::ostream& ouput, const ElectoralMap& map);

 private:
 	ElectoralMap();  // private constructor
 	std::map<int, District> District_; // Couldn't make static
};  // class Earth



#endif  // ELECTORALMAP_H
