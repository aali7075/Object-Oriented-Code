#ifndef ELECTION_H
#define ELECTION_H

#include "ElectoralMap.h"
#include <string>
#include <cmath>

struct Candidate{
  std::string name;
  Parties party;
  int id;
  int votes;
};

class Election {
  public:
    Election(); //constructor

    void Register();

    void DistrictCampaign();

    virtual void ConstituentCount();

    void ConvertMajority(District * district);

    std::vector<int> FindCandidates(Parties party);

    void Results();

  protected:
    std::map<int,Candidate> candidates_;




};

// Define your animals here.
class RepresentativeElection : public Election{
public:
	RepresentativeElection():
		Election()
		{}

		void ConstituentCount();
};


#endif  // ELECTION_H
