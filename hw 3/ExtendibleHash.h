//Christopher Chan
#ifndef EXTENDIBLE_HASH_H
  #define EXTENDIBLE_HASH_H

#include <vector>
using namespace std;
class ExtendibleLeaf
{
//  int** Directory;
//  int* binaryNode;

public:
  ExtendibleLeaf(int LSize);
  int** Directory;
  int* binaryNode;
  int count; 
  int leafsize;

  void insert2Leaf(int value);
  void removeFromLeaf(int index);
  void inputRemove(int object);
  int search(int input);
};


class ExtendibleHash
{
  ExtendibleLeaf  **Directory;
  int bits;
  int size;
  int LeafSize;
  int bitsize;
  int notfound;

  ExtendibleLeaf *binaryNode;
  vector <int> binaryKey;

public:
  ExtendibleHash(const int & notFound, int s, int LSize = 2);
  void insert(const int &object);
  void remove(const int &object);
  const int find(const int &object);
  void extend(const int &object);
  int GetBits()const {return bits;}

  void setKeys(int bitsize);
  int DSize(int bitsize);
  ExtendibleLeaf* searchIndex(const int &object, int bits);
  bool splitOrExtend (ExtendibleLeaf *ptr,int object);
}; // class ExtendibleHashing

#include "ExtendibleHash.cpp"

#endif

