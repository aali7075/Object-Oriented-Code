#include "ElectoralMap.h"

const int ElectoralMap::NUM_DISTRICTS = 4;


/**
Create district based on static variable NUM_DISTRICTS
*/
ElectoralMap::ElectoralMap() {
    // Implement your constructor here
    // make sure to initialize your fields!

    for(int i=1; i<NUM_DISTRICTS+1; i++){// start at 1 because district id's starts at 1
      District_.insert(std::pair<int,District>(i,District())); // Only giving same value
    }
}

std::ostream& operator<<(std::ostream& os, const ElectoralMap &map){
  for(std::pair<int, District> it: map.District_){
  os<< "District "<< it.first<<":"<<'\n';
  os<<it.second<<'\n'; //Already overridden at another point
  }
  return os;
}
