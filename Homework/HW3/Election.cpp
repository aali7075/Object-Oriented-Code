#include "Election.h"

Election::Election(){
};

void Election::Register(){
  //std::cout << "Working?" << '\n';
  std::string choice="y";
  std::string candidate_name;
  Candidate * person= new Candidate; //avoid seg faults
  int candidate_id=1;
  std::vector<Parties> party= enum_to_vec();
  for(int i=0; i<party.size()-1; i++){

    while(choice!="n"){
    std::cout << "Do you want to register a candidate for party " << enum_to_string(party[i]) <<"(y or n)?" << '\n';
    std::cin >> choice;
    if(choice=="y"){
      std::cout << "What is their name? ";
      std::cin >> candidate_name;
      (*person) = {candidate_name, party[i], candidate_id,0};
      candidates_.insert(std::pair<int,Candidate>(candidate_id,(*person)));
      candidate_id++;
      }
    }
    choice="y";
  }
}


void Election::DistrictCampaign(){

  int canidate_choice=-1;
  int district_choice=-1;
  Candidate person;
  ElectoralMap &map = ElectoralMap::GetInstance();
  while(canidate_choice!=0){
    std::cout<< '\n';
    std::cout << "----------------------------" << '\n';
    for (int i = 0; i < candidates_.size(); i++) {
      std::cout << i+1 << ": " << candidates_[i+1].name <<" [Party: " <<enum_to_string(candidates_[i+1].party)<<"]"<<'\n'<<'\n';
    }
    std::cout << "Which candidate is campaigning (id) (0 to stop) ? ";
    std::cin >> canidate_choice;
    if(canidate_choice==0){ // if statement so second while loop is chosen when choice is 0
      break;
    }
    person=candidates_[canidate_choice];
    // PRINT OUT THE DISTRICTS
    std::cout << map << '\n';
    while(district_choice!=0){
    std::cout << "Where is this candidate campaigning (id) (0 to stop)? ";
    std::cin >> district_choice;
    if(district_choice==0){
      break;
    }
    std::cout <<person.name <<" is campaigning in district " <<district_choice<<'\n';
    map.get_district(district_choice)->Campaign(person.party);
    std::cout << map << '\n';
    }
    district_choice=-1;
  }
}


void Election::ConvertMajority(District* district){
  std::vector<Parties> majority; // Could have multiple parties with majority
  int max_group=-1;
  int party_number;
  Parties chosen_party;
  std::map<Parties,int> constituents =district->get_constituents();
  for(std::map<Parties, int>::iterator it = constituents.begin(); it != constituents.end(); ++it){
    if(it->first==Parties::No_Party){
      continue;
    }
    if(it->second>max_group){
      max_group=it->second;
    }
  }

  for(std::map<Parties, int>::iterator it = constituents.begin(); it != constituents.end(); ++it){
    if(it->second==max_group && it->first != Parties:: No_Party){
      majority.push_back(it->first);
    }
  }
  party_number=rand() % majority.size();
  chosen_party=majority[party_number];

  district->ChangeNoParty(chosen_party);

}

std::vector<int> Election::FindCandidates(Parties party){
    std::vector<int> candidate_ids;
    for(std::map<int,Candidate>::iterator it = candidates_.begin(); it != candidates_.end(); ++it){
      if(it->second.party==party){
        candidate_ids.push_back(it->first);
      }
    }

    return candidate_ids;
}


void Election::ConstituentCount(){
  ElectoralMap &map = ElectoralMap::GetInstance();
  std::map<int, District> old_districts = map.get_all_districts();
  std::map<int, District> districts = map.get_all_districts();
  std::map<Parties,int> constituents;
  std::vector<Parties> enum_vec=enum_to_vec();
  std::vector<int> candidate_ids;
  int choose_canidate;

  //For each district grab the constituents and thier parties
  for(int i=1; i<districts.size()+1; i++){// Distric id starts at 1
    this->ConvertMajority(map.get_district(i));
  }
  districts=map.get_all_districts(); //Regrab values of districts
  for(int i=0; i<enum_vec.size(); i++){
    if(enum_vec[i]==Parties::No_Party){
      continue;
    }
    candidate_ids=FindCandidates(enum_vec[i]);
    for(std::map<int, District>::iterator dist = districts.begin(); dist != districts.end(); ++dist){
      constituents=dist->second.get_constituents();
      if(candidate_ids.empty()){
        choose_canidate=rand()%candidates_.size()+1;
        std::cout << "choose_canidate is " <<choose_canidate<<'\n';
        // if constituents don't have a candiate of same party they all randomly choose one
        candidates_[choose_canidate].votes+= constituents[enum_vec[i]];
      }
      else{
        for(int j=0; j<constituents[enum_vec[i]]; j++){
          choose_canidate=rand()%candidate_ids.size();
          candidates_[candidate_ids[choose_canidate]].votes+=1;
        }
      }
    }

  }
  map.set_all_districts(old_districts);
  return;
}


void RepresentativeElection::ConstituentCount(){
  ElectoralMap &map = ElectoralMap::GetInstance();
  std::map<int, District> old_districts = map.get_all_districts();
  std::map<int, District> districts = map.get_all_districts();
  std::map<Parties,int> constituents;
  int total_constituents=0;
  int total_dist_votes=5*districts.size();
  int total_dist_const=0;
  float dist_votes;
  std::vector<Parties> enum_vec=enum_to_vec();
  std::vector<std::pair<int,int>> candidate_votes;
  std::pair<int,int> largest_vote(0,0);
  std::vector<int> candidate_ids;

  int choose_canidate;

  //For each district grab the constituents and thier parties
  for(int i=1; i<districts.size()+1; i++){// Distric id starts at 1
    this->ConvertMajority(map.get_district(i));
  }

  for(std::map<int, District>::iterator dist = districts.begin(); dist != districts.end(); ++dist){
    constituents=dist->second.get_constituents();
    for(int i=0; i<enum_vec.size(); i++){
      total_constituents+=constituents[enum_vec[i]];
    }

  }

  districts=map.get_all_districts(); //Regrab values of districts
  for(std::map<int, District>::iterator dist = districts.begin(); dist != districts.end(); ++dist){
    constituents=dist->second.get_constituents();
    for(int i=0; i<enum_vec.size(); i++){
      if(enum_vec[i]==Parties::No_Party){
        continue;
      }
      candidate_ids=this->FindCandidates(enum_vec[i]);
      if(candidate_ids.empty()){
        choose_canidate=rand()%candidates_.size()+1; //Plus 1 becuase candiate starts at 1
        // if constituents don't have a candiate of same party they all randomly choose one

        candidates_[choose_canidate].votes+= constituents[enum_vec[i]];
      }
      else{
        for(int j=0; j<constituents[enum_vec[i]]; j++){
          choose_canidate=rand()%candidate_ids.size();

          candidates_[candidate_ids[choose_canidate]].votes+=1;
        }
      }
      total_dist_const+=constituents[enum_vec[i]];

    }

    dist_votes=floor((total_dist_const/float(total_constituents))*total_dist_votes);
    total_dist_const=0; //Reintialize back to zero

    for(std::map<int,Candidate>::iterator it = candidates_.begin(); it != candidates_.end(); ++it){
      if(largest_vote.second<it->second.votes){
        largest_vote=std::make_pair(it->first, it->second.votes);  //Candidate id then votes
      }
      it->second.votes=0;
    }
    candidate_votes.push_back(std::pair(largest_vote.first, dist_votes));

    std::cout << "District: " << dist->first<<'\n';
    std::cout <<candidates_[largest_vote.first].name <<": " << dist_votes<<'\n';

    largest_vote=std::make_pair(0, 0);

  }
  for(int i=0; i<candidate_votes.size(); i++){
    candidates_[candidate_votes[i].first].votes+=candidate_votes[i].second;

  }

  map.set_all_districts(old_districts);
  return;
};


void Election::Results(){
  std::cout<< '\n';
  std::vector< std::pair<int, std::string>> sorted_map_vec;

  for (typename std::map<int, Candidate>::iterator it = candidates_.begin(); it != candidates_.end(); ++it) {
      sorted_map_vec.push_back(std::pair(it->second.votes,it->second.name));
  }
  std::sort(sorted_map_vec.begin(), sorted_map_vec.end(), std::greater <>() ); // sort by default uses first element in pair to sort. greater for descending

  std::cout << "Full results: " << '\n';
  for(int i=0; i<sorted_map_vec.size(); i++){
    std::cout << sorted_map_vec[i].second <<": " <<sorted_map_vec[i].first <<'\n';
  }

  std::cout << "Congratulations, "<< sorted_map_vec[0].second <<", you've won!" << '\n';
}
