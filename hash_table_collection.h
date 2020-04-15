
//----------------------------------------------------------------------
// Author: ...
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hash_table_collection.h
// ...
//----------------------------------------------------------------------

 
#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"


template<typename K, typename V>
class HashTableCollection : public Collection<K,V>
{
public:

  // create an empty hash table with default number of buckets
  HashTableCollection();

  // hash table copy constructor
  HashTableCollection (const HashTableCollection <K,V>& rhs);

  // hash table assignment operator
  HashTableCollection <K,V>& operator=(const HashTableCollection <K ,V >& rhs);

  // delete a linked list
  ~HashTableCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

private:

  // helper to empty entire hash table
  void make_empty();
  
  // helper to resize and rehash the hash table
  void resize_and_rehash();
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  
  // number of k-v pairs in the collection
  int collection_size;

  // number of hash table buckets (default is 16)
  int table_capacity;

  // hash table array load factor (set at 75% for resizing)
  double load_factor_threshold;

  // hash table array
  Node** hash_table;
   
};


// TODO: implement the above functions here ...


#endif
