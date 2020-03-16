#include "District.h"




std::vector<Parties> enum_to_vec(){
  std::vector<Parties> enum_vec;
  enum_vec.push_back(Parties::Pancakes);
  enum_vec.push_back(Parties::Waffles);
  enum_vec.push_back(Parties::Crepe);
  enum_vec.push_back(Parties::No_Party);

  return enum_vec;
}


std::string enum_to_string(Parties type) {
   switch(type) {
      case Parties::Pancakes:
         return "Pancakes";
      case Parties::Waffles:
         return "Waffles";
      case Parties::Crepe:
         return "Crepe";
      default:
         return "No Party";
   }
}



District::District(){
      square_miles_=rand()%25+5;
      std::vector<Parties> enum_vec=enum_to_vec();

      int vec_size=enum_vec.size();
      for(int i=0; i<vec_size; i++){
      constituents_.insert(std::pair<Parties,int>(enum_vec[i],rand()%10));
    }
}


void District::Campaign(Parties party){
    int party_constituents= constituents_[party];
    int other_constituents=0; // All constituents_ exlcuding chosen party and none party
    bool conversion;
    float prob;
    for(std::map<Parties,int>::iterator it = constituents_.begin(); it != constituents_.end(); ++it){
      if(it->first==party || it->first==Parties::No_Party){
        continue;
      }
      other_constituents+=it->second;
    }

    prob=( ((party_constituents+1)*2.0)/(other_constituents) * ((party_constituents+1)*2.0)/(square_miles_) );
    prob= std::min(float(1.0),prob);
    std::cout << "Chances to convert: " <<prob*100<<'\n';
    std::cout << "Chances to convert from another party: " <<prob*10<<'\n';

    for(std::map<Parties,int>::iterator it = constituents_.begin(); it != constituents_.end(); ++it){
      if(it->first==party){
        continue;
      }
      else if(it->first==Parties::No_Party){
        conversion=(it->second * prob*100 >rand()%100);

      }
      else{
      conversion=(it->second * prob*10>rand()%100);
    }
      if(conversion){
        std::cout << "Congrats, you have converted someone from " << enum_to_string(it->first);
        std::cout << " to " << enum_to_string(party) <<"!" <<'\n';
        it->second-=1;
        constituents_[party]+=1;
      }
    }
}

void District::ChangeNoParty(Parties party){
  constituents_[party]+= constituents_[Parties::No_Party];
  constituents_[Parties::No_Party]=0;
}

/**
Override the cout operator for District and Show the square miles and party
*/
std::ostream& operator<<(std::ostream& os, const District &district){
  os<< "square miles: "<< district.square_miles_<<'\n';
  for (std::pair<Parties,int> it: district.constituents_) { // For each loop

    os <<"[Party: "<<enum_to_string(it.first) <<"]"<<" : "<<it.second<<" ";
  }
  return os;
}
