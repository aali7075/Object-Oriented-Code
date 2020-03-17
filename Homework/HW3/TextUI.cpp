#include "TextUI.h"


/**
TextUI Constructor
Add the menu options. Store inside private variable main_menu_
*/
TextUI::TextUI() {
  // set up the main menu
}





/**
RouteChoice() Does approriate action given menu options. In this case there is only two choices
representative and direct

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
    represen_elect->Results();
    }
  else{
    Election * elect=new Election(); //aviod segfaults
    //test->ConvertMajority(pls.get_district(1));
    elect->Register();
    std::cout << pls << '\n';
    elect->DistrictCampaign();
    elect->ConstituentCount();
    //std::cout << pls << '\n';
    elect->Results();
  }

}
