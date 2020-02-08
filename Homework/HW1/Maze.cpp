#include "Maze.h"

/**
Create the maze constructor
Will create a new board
*/
Maze::Maze(){
  board_ = new Board();
}



/**
Create a new game. Intailize enemies in a random empty place
fill the players_ vector with Players and amount of enemies
Input parameters:
*human is a pass by reference of a human created in main
enemies is the amount of enemies you want on the board. Currently set to 1 enemies are named Demon

Enemies will be placed randomly from empty spaces
*/
void Maze::NewGame(Player *human, const int enemies){
  turn_count_=0;
  player_count_=enemies+1;
  human->SetPosition(Position{0,0});
  players_.push_back(human);
  for(int i=1; i<enemies+1; i++){
    Player *demon = new Player("Demon"+std::to_string(i), false);
    players_.push_back(demon);
  }
  int enemy_count=0;
  while(enemy_count!=enemies){ // Continue looping board until all enemies are on board
    for(int i=0; i<4; i++){
      for(int j=0; j<4; j++){
        if(enemy_count==enemies){ // If statement needed to break so while loop stops as soon as enemies are populated
          break;
        }
        if(board_->get_square_value(Position{i,j})==SquareType::Empty && rand()%2){
          board_->SetSquareValue(Position{i,j}, SquareType::Enemy);
          players_[enemy_count+1]->SetPosition(Position{i,j});
          enemy_count++;
          continue;
        }
      }
    }
  }
}

/**
GetNextPlayer() Will give you the next player in vector.
Uses the turn_count_ and player_count_ to find the next player.
For example: if the players are 1 human and 1 enemy then player_count_=2
if turn_count_=0; 0%2=0 and player will go since human is stored in the 0th position
*/
Player * Maze::GetNextPlayer(){
  return players_[turn_count_%player_count_];
}

/**
Returns true if either player gets into enemy position or player gets to exit
*/
bool Maze::IsGameOver(){
  if(players_[0]->get_position()==Position{3,3}){ // If human reaches exit. End the game
    return true;
  }
  int players_size= players_.size();
  for(int i=1; i<players_size; i++){ // Check to see whether the enemy position and human position overlap. If they do end game
    if(players_[0]->get_position()==players_[i]->get_position()){
      return true;
    }
  }
  return false;
}

/**
GenerateReport will generate key values of the match
Will show Game has ended, Turns played, and how many points each player had
*/
std::string Maze::GenerateReport(){
  int players_size=players_.size();
  std::cout << '\n' << '\n'<<'\n';
  std::cout << "Game Over!" << '\n';
  std::cout << "Turns played: " <<turn_count_<<'\n';
  for(int i=0; i< players_size; i++){
    std::cout << players_[i]->get_name() <<" Points: "<<players_[i]->get_points() <<'\n';
  }
}

/**
Last Function to implement, It will run the game.
Input parameters:
p is a one of the players from the players vector. Human starts first and then enemies go.

Create while loop using IsGameOver and continue playing
Call move player, to move some player
Decide on which player to move by calling the GetNextPlayer function
Use the ToRelativePosition to get the directions to move

*/
void Maze::TakeTurn(Player *p){

  std::cout << '\n' << '\n'<<'\n';
  std::cout<<(*board_)<<'\n';
  std::cout << '\n' << '\n'<<'\n';
  std::cout << p->get_name()+" it's your move!" << '\n';
  std::string answer; // Will hold users input
  std::vector<std::string> all_answers;
  bool correct_answer=false; //Check is users answer is one of the positions from the GetMoves function

  if(!(IsGameOver())){ // Check if Game is over. i.e one of the conditions from IsGameOver is met
    std::vector <Position> pos_positions=board_->GetMoves(p); //Get all posible positions of current player
    int pos_size=pos_positions.size();
    std::cout << "You can go: ";
    for(int i=0; i<pos_size; i++){
      all_answers.push_back(p->ToRelativePosition(pos_positions[i]));
      std::cout<<all_answers[i]<<" ";
    }
    while(!correct_answer){
      std::cout <<'\n'<<"Answer: ";
      std::cin>>answer;
      for (int i=0; i<answer.size(); i++){ //Make user input into all upper case to make comparing easier
        answer.at(i) = toupper(answer.at(i));
      }

      for(int i=0; i<pos_size; i++){
        if(answer==all_answers[i]){ // If Player chose an answer that was part of the possible positions move player and set correct_answer=true
          correct_answer=board_->MovePlayer(p,pos_positions[i]);
        }
      }
      if(!correct_answer){
        std::cout << "Invalid answer. Maybe you typed it in wrong..." << '\n';
        std::cout << "Again, you can go: ";
        for(int i=0; i<pos_size; i++){
          all_answers.push_back(p->ToRelativePosition(pos_positions[i])); // Redisplay the possible directions
          std::cout<<all_answers[i]<<" ";
        }
      }
    }

    turn_count_++; // Increase turn_count_ by 1
    TakeTurn(GetNextPlayer()); // Get the next player to play and take turn
  }




}
