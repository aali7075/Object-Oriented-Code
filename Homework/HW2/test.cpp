/**
Aaron Li
*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Counter.hpp"


std::vector<int> ints{1,1,1,2,3,4,5,3};
std::vector<std::string> animals{"cat", "cat", "dog", "bird", "fish"};
std::vector<char> chars{'a','a','a','b','c','d'};
std::vector<double> dub{1.0,1.0,1.0,2.0,3.0,4.0,5.0,3.0};
std::vector<bool> bools{true,true,true,false,false};


TEST_CASE ( "Counter constructor", "[Counter]") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  SECTION("Using ints"){
    REQUIRE(int_map->Count()==8);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count()==5);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count()==6);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count()==8);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->Count()==5);
  }

}

TEST_CASE ( "Count specfic key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);
  SECTION("Using ints"){
    REQUIRE(int_map->Count(1)==3);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count("cat")==2);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count('a')==3);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count(3.0)==2);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->Count(true)==3);
  }

}

TEST_CASE ( "Count through range") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);

  SECTION("Using ints"){
    REQUIRE(int_map->Count(1,5)==7);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count("bird", "dog")==3);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count('a','c')==4);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count(1.0,5.0)==7);
  }

}

TEST_CASE ( "Remove a key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  int_map->Remove(1);
  animals_map->Remove("cat");
  char_map->Remove('a');
  double_map->Remove(1.0);
  bool_map->Remove(true);

  SECTION("Using ints"){
    REQUIRE(int_map->Count()==5);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count()==3);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count()==3);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count()==5);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->Count()==2);
  }

}


TEST_CASE ( "Increment a key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  int_map->Increment(1);
  animals_map->Increment("zebra",3);
  char_map->Increment('a');
  double_map->Increment(1.0,2);
  bool_map->Increment(true,5);

  SECTION("Using ints"){
    REQUIRE(int_map->Count()==9);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count()==8);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count()==7);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count()==10);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->Count()==10);
  }
}


TEST_CASE ( "Decrement a key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  int_map->Decrement(1);
  animals_map->Decrement("bird");
  char_map->Decrement('a');
  double_map->Decrement(1.0,2);
  bool_map->Decrement(true,5);

  SECTION("Using ints"){
    REQUIRE(int_map->Count()==7);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->Count("bird")==0);
  }
  SECTION("Using char"){
    REQUIRE(char_map->Count()==5);
  }
  SECTION("Using double"){
    REQUIRE(double_map->Count()==6);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->Count()==2);
  }
}

TEST_CASE ( "Find most common key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  std::vector<int> v{1,3};

  SECTION("Using ints"){
    REQUIRE(int_map->MostCommon(2)==v);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->MostCommon()=="cat");
  }
  SECTION("Using char"){
    REQUIRE(char_map->MostCommon()=='a');
  }
  SECTION("Using double"){
    REQUIRE(double_map->MostCommon()==1.0);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->MostCommon()==true);
  }
}


TEST_CASE ( "Find least common key") {
  Counter <int> * int_map= new Counter(ints);
  Counter <std::string> * animals_map= new Counter(animals);
  Counter <char> * char_map= new Counter(chars);
  Counter <double> * double_map= new Counter(dub);
  Counter <bool> * bool_map= new Counter(bools);

  std::vector<bool> v{false};

  SECTION("Using ints"){
    REQUIRE(int_map->LeastCommon()==2);
  }
  SECTION("Using strings"){
    REQUIRE(animals_map->LeastCommon()=="bird");
  }
  SECTION("Using char"){
    REQUIRE(char_map->LeastCommon()=='b');
  }
  SECTION("Using double"){
    REQUIRE(double_map->LeastCommon()==2.0);
  }
  SECTION("Using bool"){
    REQUIRE(bool_map->LeastCommon(1)==v);
  }
}

TEST_CASE ( "Normalized") {
  Counter <bool> * bool_map= new Counter(bools);

  std::vector<bool> v{false};
  std::map<bool, double> bool_dub_map;
  bool_dub_map[true]=0.6;
  bool_dub_map[false]=0.4;

  SECTION("Using bool"){
    REQUIRE(bool_map->Normalized()==bool_dub_map);
  }
}


TEST_CASE ( "Keys") {
  Counter <bool> * bool_map= new Counter(bools);
  Counter <int> * int_map= new Counter(ints);

  std::set<bool> bool_set {true,false};
  std::set<int> int_set {1,2,3,4,5};

  SECTION("Using int"){
    REQUIRE(int_map->Keys()==int_set);
  }

  SECTION("Using bool"){
    REQUIRE(bool_map->Keys()==bool_set);
  }
}

TEST_CASE ( "Values") {
  Counter <bool> * bool_map= new Counter(bools);
  Counter <int> * int_map= new Counter(ints);

  std::vector<int> bool_vec {2,3};
  std::vector<int> int_vec {3,1,2,1,1};

  SECTION("Using int"){
    REQUIRE(int_map->Values()==int_vec);
  }

  SECTION("Using bool"){
    REQUIRE(bool_map->Values()==bool_vec);
  }
}
