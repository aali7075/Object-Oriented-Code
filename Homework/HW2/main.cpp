#include <iostream>
#include "Counter.hpp"


int main() {
std::vector<int> v{1,1,2,3,3,5,5,5,5};

std::vector<int> v1{};

Counter <int> * pls= new Counter(v);

Counter <int> * pls2= new Counter(v1);

std::cout << (*pls) << '\n';


std::cout << "The count is ";
std::cout << pls->Count() << '\n';
std::cout << "The count for between 1-5 is ";
std::cout << pls->Count(1,5) << '\n';

pls->Remove(2);
std::cout << "The count after removing 2 is ";
std::cout << pls->Count() << '\n';

pls->Increment(3);
std::cout << pls->Count() << '\n';




std::cout << "Incrementing by 10" << '\n';
pls->Increment(1,10);
std::cout << pls->Count() << '\n';

std::cout << "Decrementing" << '\n';
pls->Decrement(3);
std::cout << pls->Count() << '\n';

std::cout << "Decrementing by 10" << '\n';
pls->Decrement(1, 10);
std::cout << pls->Count() << '\n';

std::cout << "Most common value is: " << '\n';
std::cout << pls->MostCommon() << '\n';



std::cout << "Most common value is of range n: " << '\n';
std::vector<int> test=pls->MostCommon(3);
for(int i=0; i<test.size(); i++){
  std::cout << test[i] <<", ";
}
std::cout << "" << '\n';

std::cout << "The Least common value is: " << '\n';
std::cout << pls->LeastCommon() << '\n';

std::cout << "Least common value is of range n: " << '\n';
std::vector<int> owo=pls->LeastCommon(3);
for(int i=0; i<owo.size(); i++){
  std::cout << owo[i] <<", ";
}
std::cout << "" << '\n';


std::map<int,double> uwu= pls->Normalized();

std::cout << "Normalized is" << '\n';
std::cout<<uwu.find(5)->second<<'\n';

std::set<int> sir= pls->Keys();

std::cout << "Keys are" << '\n';
for(std::set<int>::iterator it = sir.begin(); it != sir.end(); ++it){
  std::cout << (*it) <<", ";
}
std::cout << "" << '\n';

std::cout << "Values are " << '\n';
std::vector<int> tired= pls->Values();
for(int i=0; i<tired.size(); i++){
  std::cout << tired[i] <<", ";
}


// Check if domain error works

pls2->MostCommon();





}
