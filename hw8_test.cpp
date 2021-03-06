//----------------------------------------------------------------------
// Author: Kevin Lunden
// Course: CPSC 223, Spring 2020
// Assign: 8
// File:   hw8_test.cpp
//
// TODO: Tests functions of hash table collection.
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "hash_table_collection.h"

using namespace std;

// Test 1
TEST(BasicListTest, CorrectSize) {
  HashTableCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());
}

// Test 2
// Tests multiple adds with negative and large numbers
// Also tests adding same keys
TEST(BasicListTest, DiffCorrectSize) {
  HashTableCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  c.add("d", 1000.0);
  c.add("d", -10.0);
  ASSERT_EQ(5, c.size());
}


// Test 3
TEST(BasicListTest, SimpleFind) {
  HashTableCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 4
TEST(BasicListTest, SimpleRemoveElems) {
  HashTableCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 5
TEST(BasicListTest, SimpleRange) {
  HashTableCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 6
// Tests if entire range works
TEST(BasicListTest, DiffRange) {
  HashTableCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(10, 60, vs);
  ASSERT_EQ(6, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "e"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "f"));
}

// Test 7
TEST(BasicListTest, SimpleSort) {
  HashTableCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

// Test 8
// Test with negative and large numbers
TEST(BasicListTest, DiffSort) {
  HashTableCollection<string,int> c;
  c.add("a", -10);
  c.add("e", 5000);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}

// Test 9
// Test with multi-letter strings
TEST(BasicCollectionTest, SimpleEqual){
  HashTableCollection <string, double> c;
  c.add("de", 40.0); //make sure remove works on 2 char strings
  c.add("t", 67.0);
  double v;
  c.remove("de");
  ASSERT_EQ(c.find("de", v), false);
  c.remove("i"); //make sure removing a string that doesnt exist works
  ASSERT_EQ(c.find("t", v), true);
  c.remove("t");
  c.remove("f");
  ASSERT_EQ(c.size(), 0); //make sure remove works when empty
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

