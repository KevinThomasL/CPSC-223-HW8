
//----------------------------------------------------------------------
// Author: Kevin Lunden
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hash_table_collection.h
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

  // remove a key-value pair from the collection
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
// create an empty linked
template <typename K, typename V>
HashTableCollection <K,V>::HashTableCollection() : collection_size(0), table_capacity(16), load_factor_threshold(0.75) 
{
 // dynamically allocate the hash table array
 hash_table = new Node*[table_capacity];

 for (int i = 0; i < table_capacity; ++i)
  hash_table[i] = nullptr;
}

// copy a linked list
template <typename K, typename V>
HashTableCollection<K,V>::HashTableCollection(const HashTableCollection<K,V>& rhs) : hash_table(nullptr)
{
 *this = rhs;
}

// assign a linked list
template <typename K, typename V>
HashTableCollection <K,V>& HashTableCollection <K,V>::operator=(const HashTableCollection<K,V>& rhs)
{
 // check if rhs is current object and return current object
 if (this == &rhs)
  return *this;

 make_empty ();

 // initialize current object
 collection_size = 0;
 load_factor_threshold = 0.75;
  
 hash_table = new Node*[rhs.table_capacity];

 //copy
 Node* ptr;
 for(int i = 0; i < rhs.table_capacity; i++)
 {
  ptr = rhs.hash_table[i];
  while(ptr != nullptr)
  {
   insert(ptr->key, ptr->value);
   ptr = ptr->next;
  }
 }
 return *this;
}

// delete a linked list
template <typename K, typename V>
HashTableCollection <K,V>::~HashTableCollection()
{
  make_empty();
}

// insert a key-value pair into the collection
template <typename K, typename V>
void HashTableCollection<K,V>::add(const K& key, const V& val)
{
 // check current load factor 
 std::hash<K> hash_fun;
 size_t value = hash_fun(key);
 size_t index = value % table_capacity;

 Node* ptr = new Node;
 ptr->key = key;
 ptr->value = val;

 //resize if necessary
 if(double(collection_size / table_capacity) > load_factor_threshold)
 {
  resize_and_rehash();
 }

 if(hash_table[index] == nullptr)
 {
  ptr->next = nullptr;

  //set the bucket pointer to the head of new node
  hash_table[index] = ptr;
 } 
 else if (hash_table[index] != nullptr)
 {
  ptr->next = hash_table[index];

  //bucket now points to head of new node
  hash_table[index] = ptr;
 }

 collection_size++;
}

// remove a key-value pair from the collection
template <typename K, typename V>
void HashTableCollection<K,V>::remove(const K& key)
{
 std::hash<K> hash_fun;
 size_t value = hash_fun(key);
 size_t index = value % table_capacity;
 Node* ptr;
 Node* temp;

 //make sure hash table isn't empty
 if(hash_table != nullptr)
 {
  ptr = hash_table[index];
  if(hash_table[index] != nullptr)
  {
   //if the first node has the key
   if(ptr->key == key)
   { 
    //if there is only one node  
    if(ptr->next == nullptr)
    {
     delete ptr;
     hash_table[index] = nullptr;
     collection_size--;
    } 
    else 
    {
     hash_table[index] = ptr->next;
     ptr->next = nullptr;
     delete ptr;
     collection_size--;
    }
   }
   else
   {
    temp = ptr;
    if(ptr != nullptr)
    {
     ptr = ptr -> next;

     //while not at the last node of the bucket
     while(ptr != nullptr)
     {
      if(ptr->key == key)
      {
       if(ptr->next = nullptr)
       {
        temp->next = nullptr;
        delete ptr;
        collection_size--;
       } 
       else
       {
        temp->next = ptr->next;
        ptr->next = nullptr;
        delete ptr;
        collection_size--;
       }
      }
      temp = ptr;
      ptr = ptr->next;
     }
    }
   }
  }
 }
}

// find the value associated with the key
template <typename K, typename V>
bool HashTableCollection<K,V>::find(const K& key, V& val) const
{
 Node* temp;
 std::hash<K> hash_fun;
 size_t value = hash_fun(key);
 size_t index = value % table_capacity;

 if(hash_table != nullptr)
 {
  if(hash_table[index] == nullptr)
  {
   return false;
  } 
  else 
  {
   temp = hash_table[index];

   while(temp != nullptr)
   {
    if(temp->key == key)
    {
     val = temp -> value;
     return true;
    } 
    else
    {
     temp = temp->next;
    }
   }
  }
 }
 return false;
}

// find and return the values with keys >= to k1 and <= to k2
template <typename K, typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
 Node* ptr;

 for(int i = 0; i < table_capacity; i++)
 {
  ptr = hash_table[i];

  while(ptr != nullptr)
  {
   if(ptr->key >= k1 && ptr->key <= k2)
   {
    vals.push_back(ptr->value);
   }

   ptr = ptr->next;
  }
 }
}

// return all keys in the collection
template <typename K, typename V>
void HashTableCollection<K,V>::keys(std::vector <K>& keys) const
{
 Node* ptr;

 for(int i = 0; i < table_capacity; i++)
 {
  ptr = hash_table[i];

  while(ptr != nullptr)
  {
   keys.push_back(ptr->key);
   ptr = ptr->next;
  }
 }
}

// return collection keys in sorted order
template<typename K,typename V>
void HashTableCollection<K,V>::sort(std::vector<K>& ks) const
{
 keys(ks);
 std::sort(ks.begin(), ks.end());
}

// return the number of keys in collection
template <typename K, typename V>
int HashTableCollection <K,V>::size() const
{
 return collection_size;
}

// helper to empty entire hash table
template <typename K, typename V>
void HashTableCollection <K,V>::make_empty()
{
 Node* ptr;
 Node* next;

 if(hash_table != nullptr)
 {
  for(int i = 0; i < collection_size; i++)
  {
   ptr = hash_table[i];

   //iterate through entire linked list in spot of hash table_capacity
   while(hash_table[i] != nullptr)
   {
    next = ptr->next;
    delete ptr;
    ptr = next;
    hash_table[i] = ptr;
   }
  }
 }

 delete hash_table;
}

template <typename K, typename V>
void HashTableCollection<K,V>::resize_and_rehash()
{
 int new_capacity = table_capacity * 2;

 Node** new_table = new Node*[new_capacity];
 
 // initialize new table
 for(int i = 0; i < new_capacity; i++)
  new_table[i] = nullptr;

 // insert key values
 std::vector <K> ks;
 keys(ks);
 size_t index;
 V inVal;

 for(K key:ks)
 {
  std::hash<K> hash_fun;
  size_t value = hash_fun(key);
  size_t index = value % table_capacity;

  Node* newNode = new Node;
  bool temp = find(key, inVal);
  newNode->key = key;
  newNode->value = inVal;

  if(new_table[index] == nullptr)
  {
   hash_table[index] = newNode;
   newNode->next = nullptr;
  } 
  else 
  {
   newNode->next = new_table[index];
   new_table[index] = newNode;
  }
 }

 make_empty();
 hash_table = new_table;
 table_capacity = new_capacity;
}

#endif
