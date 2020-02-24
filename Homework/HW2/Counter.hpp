#include <iostream>
#include <vector>
#include<iterator> // for iterators
#include <algorithm>
#include <map>
#include <set>

template <class T>
class Counter {
public:
  //Intialize an empty Counter <T>
  Counter()=default;

  //initialize a Counter<T> appropriately from a vector or array that contains type T
  Counter(std::vector<T> vals);

  //access the total of all counts so far
  int Count();

  //access the count associated with any object T, even for values of T that have not been counted
  int Count(T key);

  // // access the total of all counts for objects T given a
  // // certain range (an inclusive minimum T and an
  // // exclusive maximum T element)
  // int Count(T min, T max);

  // remove all counts of an object T from the Counter
  void Remove(T key);

  // increment the count of an object T by one
  void Increment(T key);

  // increment the count of an object T by n
  void Increment(T key, int n);

  // decrement the count of an object T by one
  void Decrement(T key);

  // decrement the count of an object T by n
  void Decrement(T key, int n);

  // get the most commonly occurring object of type T
  // (the object with the highest count)
  // If the Counter is empty, this method should throw a
  // domain error
  T MostCommon();

  // get the n most commonly occurring objects of type
  // T. If the Counter is empty, this method should
  // return a vector of size 0.
  std::vector<T> MostCommon(int n);

  // get the least commonly occurring object of type T
  // (the object with the highest count)
  // If the Counter is empty, this method should throw a
  // domain error
  T LeastCommon();

  // get the n least commonly occurring objects of type
  // T. If the Counter is empty, this method should
  // return a vector of size 0.
  std::vector<T> LeastCommon(int n);


  // access normalized weights for all objects of type T
  // seen so far
  std::map<T, double> Normalized();

  // access the set of all keys in the Counter
  std::set<T> Keys();

  // access the collection of all values in the Counter
  std::vector<int> Values();



  // Note the non-T typename designation!
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Counter<U> &b);


private:
 std::map<T, int> map_;
};
// Class Definition -------

template<class T>
Counter<T>::Counter(std::vector<T> vals){
  int vals_size= vals.size();

  for(int i=0; i<vals_size; i++){
    typename std::map<T,int>::iterator it = map_.find(vals[i]);

		// key already present in the map
		if (it != map_.end()) {
			it->second++;	// increment map's value for key 'c'
		}
		// key not found
		else {
			map_.insert(std::pair(vals[i], 1));
		}
  }
}

template<class T>
int Counter<T>::Count(){
  int val_count=0;
  // Need typename so compiler understands what type it is
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    val_count+=it->second;
    //retval.push_back(element.first);
  }
  return val_count;
}

template<class T>
int Counter<T>::Count(T key){
  return map_.find(key)->second;
}

// template<class T>
// int Counter<T>::Count(T min, T max){
//
//   return map_.find(Key)->second;
// }

template<class T>
void Counter<T>::Remove(T key){
  map_.erase(key);
}

template<class T>
void Counter<T>::Increment(T key){
  map_.find(key)->second++;
}

template<class T>
void Counter<T>::Increment(T key, int n){
  map_.find(key)->second+=n;
}

template<class T>
void Counter<T>::Decrement(T key){
  map_.find(key)->second--;
}

template<class T>
void Counter<T>::Decrement(T key, int n){
  map_.find(key)->second-=n;
}


//*********ADD THE DOMAIN ERROR******************
template<class T>
T Counter<T>::MostCommon(){
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

//*********ADD THE DOMAIN ERROR******************
template<class T>
std::vector<T> Counter<T>::MostCommon(int n){
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


//*********ADD THE DOMAIN ERROR******************
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

//*********ADD THE DOMAIN ERROR******************
template<class T>
std::vector<T> Counter<T>::LeastCommon(int n){
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
std::set<T> Counter<T>::Keys(){
  std::set<T> keys;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    keys.insert(it->first);
  }
}


template<class T>
std::vector<int> Counter<T>::Values(){
  std::vector<int> vals;
  for (typename std::map<T,int>::iterator it = map_.begin(); it != map_.end(); ++it) {
    vals.push_back(it->second);
  }
  return vals;
}





// then, when implementing
// template <typename U>
// std::ostream& operator<<(std::ostream& os, const Counter<U> &n) {
//   std::cout << "{" <<;
//   for(typename std::map<U,int>::iterator it = n.map_.begin(); it != n.map_.end(); ++it){
//     std::cout <<it << '\n';
//   }
//   std::cout << "}" << '\n';
// }
