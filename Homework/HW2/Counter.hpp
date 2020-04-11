#ifndef COUNTER_H
#define COUNTER_H


#include <iostream>
#include <vector>
#include<iterator> // for iterators
#include <algorithm>
#include <map>
#include <set>
#include <stdexcept>

template <class T>
class Counter {
public:
  //Intialize an empty Counter <T>
  Counter()=default;

  //initialize a Counter<T> appropriately from a vector or array that contains type T
  Counter(std::vector<T> const vals);

  //access the total of all counts so far
  int Count();

  //access the count associated with any object T, even for values of T that have not been counted
  int Count(T key);

  // access the total of all counts for objects T given a
  // certain range (an inclusive minimum T and an
  // exclusive maximum T element)
  int Count(T min, T max);

  // remove all counts of an object T from the Counter
  void Remove(T key);

  // increment the count of an object T by one
  void Increment(T key);

  // increment the count of an object T by n
  void Increment(T key, const int n);

  // decrement the count of an object T by one
  void Decrement(T key);

  // decrement the count of an object T by n
  void Decrement(T key, const int n);

  // get the most commonly occurring object of type T
  // (the object with the highest count)
  // If the Counter is empty, this method should throw a
  // domain error
  T MostCommon();

  // get the n most commonly occurring objects of type
  // T. If the Counter is empty, this method should
  // return a vector of size 0.
  std::vector<T> MostCommon(const int n);

  // get the least commonly occurring object of type T
  // (the object with the highest count)
  // If the Counter is empty, this method should throw a
  // domain error
  T LeastCommon();

  // get the n least commonly occurring objects of type
  // T. If the Counter is empty, this method should
  // return a vector of size 0.
  std::vector<T> LeastCommon(const int n);


  // access normalized weights for all objects of type T
  // seen so far
  std::map<T, double> Normalized();

  // access the set of all keys in the Counter
  const std::set<T> Keys();

  // access the collection of all values in the Counter
  const std::vector<int> Values();



  // Note the non-T typename designation!
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Counter<U> &b);


private:
 std::map<T, int> map_;
};
// Class Definition -------

/**
Counter Constructor
Parameters: Takes in a vector of some type T and inserts it into map_  as a pair
Any values seen multiple times will increment the value.
*/
template<class T>
Counter<T>::Counter(std::vector<T>  const vals){
  int vals_size= vals.size();

  for(int i=0; i<vals_size; i++){
    typename std::map<T,int>::iterator it = map_.find(vals[i]);

		// key already present in the map
		if (it != map_.end()) {
			it->second++;
		}
		// key not found
		else {
			map_.insert(std::pair(vals[i], 1));
		}
  }
}


/**
Count(T key)
Counts the number of occurences of a certain key
*/
template<class T>
int Counter<T>::Count(T key){
  typename std::map<T,int>::iterator it = map_.find(key);
  if(it==map_.end()){ // If key is not in map return 0 since no instance
    return 0;
  }

  return map_.find(key)->second;
}

/**
Count()
Counts the number of occurences for all keys
*/
template<class T>
int Counter<T>::Count(){
  int val_count=0;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    val_count+=it->second;
  }
  return val_count;
}

/**
Count(T min, T max)
Counts the number of occurences for between min and maximum.
Note inclusive min and  exclusive max
*/
template<class T>
int Counter<T>::Count(T min, T max){
  int val_count=0;
  // Need typename so compiler understands what type it is
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    if (it->first >= min && it->first < max){
      val_count+=it->second;
    }
  }
  return val_count;
}

template<class T>
void Counter<T>::Remove(T key){
  map_.erase(key);
}


/**
Increment either increments by 1 or by specified n
The Increment(key) calls on the other definition to
make error fixing easier
*/

template<class T>
void Counter<T>::Increment(T key){
  //map_.find(key)->second++;
  this->Increment(key,1);
}

template<class T>
void Counter<T>::Increment(T key, const int n){
  typename std::map<T,int>::iterator it = map_.find(key);
  if(it==map_.end()){ //If not in map add it to map
    map_.insert(std::pair(key, n));
  }
  else{
  it->second+=n;
  }
}

/**
Decrement either decrements by 1 or by specified n
The Decrement(key) calls on the other definition to
make error fixing easier
*/
template<class T>
void Counter<T>::Decrement(T key){
  // map_.find(key)->second--;
  this->Decrement(key,1);
}

template<class T>
void Counter<T>::Decrement(T key, const int n){
  typename std::map<T,int>::iterator it = map_.find(key);
  if(it==map_.end()){
    return;
  }
  it->second-=n;

  if(it->second<=0){ //If value goes to zero or lower delete from map
    map_.erase(key);
  }
}



/**
MostCommon
Finds the most frequent/common occurences of a element
*/

template<class T>
T Counter<T>::MostCommon(){
  if(map_.empty()){
    throw std::domain_error("Nothing inside map");
  }
  int compare=0;
  T key;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    if(compare< it->second){
      compare = it->second;
      key =  it->first;
    }
  }
  return key;
}

template<class T>
std::vector<T> Counter<T>::MostCommon(const int n){
  std::vector< std::pair<int,T> > sorted_map_vec;
  std::vector<T> most_comm_keys;

  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
      sorted_map_vec.push_back(std::pair(it->second,it->first));
  }
  std::sort(sorted_map_vec.begin(), sorted_map_vec.end(), std::greater <>() ); // sort by default uses first element in pair to sort. greater for descending
  for (int i=0; i<n; i++){
    most_comm_keys.push_back(sorted_map_vec[i].second);
  }
  return most_comm_keys;
}



template<class T>
T Counter<T>::LeastCommon(){
  std::vector< std::pair<int,T> > sorted_map_vec;
  std::vector<T> most_comm_keys;

  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
      sorted_map_vec.push_back(std::pair(it->second,it->first));
  }
  std::sort(sorted_map_vec.begin(), sorted_map_vec.end()); // sort by default uses first element in pair to sort. greater for descending
  return sorted_map_vec[0].second;
}


template<class T>
std::vector<T> Counter<T>::LeastCommon(const int n){
  std::vector< std::pair<int,T> > sorted_map_vec;
  std::vector<T> most_comm_keys;

  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
      sorted_map_vec.push_back(std::pair(it->second,it->first));
  }
  std::sort(sorted_map_vec.begin(), sorted_map_vec.end()); // sort by default uses first element in pair to sort. greater for descending
  for (int i=0; i<n; i++){
    most_comm_keys.push_back(sorted_map_vec[i].second);
  }
  return most_comm_keys;
}

template<class T>
std::map<T, double> Counter<T>::Normalized(){
  std::map<T, double> map_double;
  int count_tot= this->Count();

  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    map_double.insert(std::pair(it->first, double(it->second)/count_tot));
  }
  return map_double;
}


template<class T>
const std::set<T> Counter<T>::Keys(){
  std::set<T> keys;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    keys.insert(it->first);
  }
  return keys;
}


template<class T>
const std::vector<int> Counter<T>::Values(){
  std::vector<int> vals;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    vals.push_back(it->second);
  }
  return vals;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Counter<U> &n){
  int map_size= n.map_.size();
  os << "{";
  for (typename std::pair<U,int> it: n.map_) { // Syntatical sugar For each loop

    os <<it.first <<":"<<it.second<<",";
  }
  os << "}"<<'\n';
  return os;
}

#endif
