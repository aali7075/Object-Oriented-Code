#include "Election.h"

Election::Election(){
};


/**
Election Register()
ask user to input candiates until they want to stop
*/
void Election::Register(){
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
    choice="y";// Reset back to y so user can input if needed
  }
}


/**
DistrictCampaign()
Allow user to choose a candiate and let them campaign in a distrct
*/
void Election::DistrictCampaign(){

  int canidate_choice=-1;
  int district_choice=-1;
  Candidate person;
  ElectoralMap &map = ElectoralMap::GetInstance();
  while(canidate_choice!=0){
    std::cout<< '\n';
    std::cout << "----------------------------" << '\n';
    for (int i = 0; i < candidates_.size(); i++) { // List out canidates
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
    map.get_district(district_choice)->Campaign(person.party); //call on specific distrct
    std::cout << map << '\n';
    }
    district_choice=-1;
  }
}


/**
ConvertMajority()
Goes and changes the No party constiuents to the majority pary of that district.
Makes ConstituentCount easier
*/
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
  party_number=rand() % majority.size(); //Choose a random party if multiple with majority
  chosen_party=majority[party_number];

  district->ChangeNoParty(chosen_party);

}

/**
Helper function for ConstituentCount to make it easier to find which candiates
are in which party
*/
std::vector<int> Election::FindCandidates(Parties party){
    std::vector<int> candidate_ids;
    for(std::map<int,Candidate>::iterator it = candidates_.begin(); it != candidates_.end(); ++it){
      if(it->second.party==party){
        candidate_ids.push_back(it->first);
      }
    }

    return candidate_ids;
}


/**
Will count up all the constiuetns in the party and change the vote value of
canidates.
This functions handles the edge cases where there are constituents with no candiate.
In that case it randomly chosen a candiate for the constituent.
*/

void Election::ConstituentCount(){
  ElectoralMap &map = ElectoralMap::GetInstance();
  //keep track of distrct before we call ConvertMajority to change it back in the end
  std::map<int, District> old_districts = map.get_all_districts();
  std::map<int, District> districts = map.get_all_districts();
  std::map<Parties,int> constituents;
  std::vector<Parties> enum_vec=enum_to_vec();
  std::vector<int> candidate_ids;
  int choose_canidate;

  //For each district grab the constituents and thier parties
  for(int i=1; i<districts.size()+1; i++){// Distric id starts at 1
    this->ConvertMajority(map.get_district(i)); // change no party to vote for majority
  }
  districts=map.get_all_districts(); //Regrab values of districts after convert
  for(int i=0; i<enum_vec.size(); i++){
    if(enum_vec[i]==Parties::No_Party){ // No candiate in No_Party
      continue;
    }
    candidate_ids=FindCandidates(enum_vec[i]); // find all candiates in specific party
    for(std::map<int, District>::iterator dist = districts.begin(); dist != districts.end(); ++dist){
      constituents=dist->second.get_constituents();
      if(candidate_ids.empty()){ // If no candiate in party randomly chose a candiate
        choose_canidate=rand()%candidates_.size()+1;
        std::cout << "choose_canidate is " <<choose_canidate<<'\n';
        // if constituents don't have a candiate of same party they all randomly choose one
        candidates_[choose_canidate].votes+= constituents[enum_vec[i]];
      }
      else{
        for(int j=0; j<constituents[enum_vec[i]]; j++){
          choose_canidate=rand()%candidate_ids.size(); // Randomly chose a canidate in party
          candidates_[candidate_ids[choose_canidate]].votes+=1;
        }
      }
    }

  }
  map.set_all_districts(old_districts); //reset map back
  return;
}


/**
Similar to ConstituentCount but this time we have a RepresentativeElection
First we find all possible distrct votes which is 5*NUM_DISTRICTS

We count which candiate has the majority in a district and they get the votes from the distrct
District votes is created by an eqation. This function still handles edge cases
Where constituent don't have candiate.
*/
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
      total_constituents+=constituents[enum_vec[i]];//Find the total_constituents for distrct eqation
    }

  }

  districts=map.get_all_districts(); //Regrab values of districts after ConvertMajority
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
          choose_canidate=rand()%candidate_ids.size(); //Radnomly choose from candiate in party

          candidates_[candidate_ids[choose_canidate]].votes+=1;
        }
      }
      total_dist_const+=constituents[enum_vec[i]]; //Need to count all constiuents in distrct in equation

    }

    dist_votes=floor((total_dist_const/float(total_constituents))*total_dist_votes); //District eqation
    total_dist_const=0; //Reintialize back to zero

    for(std::map<int,Candidate>::iterator it = candidates_.begin(); it != candidates_.end(); ++it){
      if(largest_vote.second<it->second.votes){ //Find candiate with largest amount of votes
        largest_vote=std::make_pair(it->first, it->second.votes);  //Candidate id then votes
      }
      it->second.votes=0; //Reset for next distrct
    }
    //Keep track of canidate id and how many votes they got
    candidate_votes.push_back(std::pair(largest_vote.first, dist_votes));

    std::cout << "District: " << dist->first<<'\n';
    std::cout <<candidates_[largest_vote.first].name <<": " << dist_votes<<'\n';

    largest_vote=std::make_pair(0, 0); //reset largest vote pair for next distrct

  }
  for(int i=0; i<candidate_votes.size(); i++){
    // Put all the votes inside the canidate
    candidates_[candidate_votes[i].first].votes+=candidate_votes[i].second;

  }

  map.set_all_districts(old_districts);
  return;
};


/**
Print all of the resutls of the election by taking the map and creating a vector.
Sort the vector by descending order.
*/
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
