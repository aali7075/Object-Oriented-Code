#include "TextUI.h"


/**
TextUI Constructor
Add the menu options. Store inside private variable main_menu_
*/
TextUI::TextUI() {
  // set up the main menu
}





/**
RouteChoice() Does approriate action given menu options. In this case there is only
two options Choose corpus and Lave

The choice choose corpus and run engine will:
1. Let user enter a corpus/Textfile
2. Create the search engine by calling AutoComplete on the corpus
3. User inputs the query and gets back search results anc can continue to enter search results
4. Can quit search engine and then either leave or create a new search engine from another corpus

*/

void TextUI::RouteChoice(std::string choice) {
  ElectoralMap &pls = ElectoralMap::GetInstance();
  if (choice == "representative") {
    RepresentativeElection * represen_elect=new RepresentativeElection(); //aviod segfaults
    //test->ConvertMajority(pls.get_district(1));
    represen_elect->Register();
    std::cout << pls << '\n';

    represen_elect->DistrictCampaign();
    represen_elect->ConstituentCount();
    //std::cout << pls << '\n';
    represen_elect->Results();
    }
  else{
    Election * elect=new Election(); //aviod segfaults
    //test->ConvertMajority(pls.get_district(1));
    elect->Register();
    //
    elect->DistrictCampaign();
    elect->ConstituentCount();
    //std::cout << pls << '\n';
    elect->Results();
  }

}
