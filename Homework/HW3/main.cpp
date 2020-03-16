#include "TextUI.h"



int main() {
  srand(time(NULL)); //Randomly generate new values each time we run the elections

  ElectoralMap &pls = ElectoralMap::GetInstance();
  TextUI * text= new TextUI();


  std::string choice="";

  while (choice!="0") {
    std::cout << "What kind of election should we have (direct or representative, 0 to stop)? ";
    std::cin >> choice;
    if(choice=="0"){
      break;
    }
    text->RouteChoice(choice);


  }


}
