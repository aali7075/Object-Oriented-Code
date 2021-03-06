#ifndef TEXT_UI_H
#define TEXT_UI_H

/**
  Provided code for CSCI 3010, PE 7, Fall 2019
*/

class TextUI {
  public:
    TextUI();

    std::string MainMenu();

    void RouteChoice(Store s, std::string choice);

    int ItemMenu(Store s, std::map<int, std::string> items);


  private:
    std::vector<std::string> main_menu_;
};


#endif  // TEXT_UI_H
