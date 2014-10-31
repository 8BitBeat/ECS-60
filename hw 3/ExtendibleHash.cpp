//Christopher Chan
#include "ExtendibleHash.h"

ExtendibleLeaf::ExtendibleLeaf(int LSize)
{
  binaryNode = new int[LSize];
  count = 0;
  leafsize = LSize;
}

int ExtendibleHash::DSize(int bits)
{
  int directorysize = 2;

  for(int i= 1; i< bits; i++)
  {
    directorysize = directorysize * 2;
  }  

  return directorysize;
}

int Ehash(int value, int bits)
{

  return value >> (18 - bits) ;
} // Ehash()

ExtendibleLeaf* ExtendibleHash::searchIndex(const int &object, int bits)
{
  int compare = Ehash(object, bits);

  for(int indexIter = 0; indexIter < DSize(bits); indexIter++)
  {
    if(compare == binaryKey[indexIter])
      return Directory[indexIter];
  } 
  
}//returns a directory pointer to the array you are searching for

ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) :
  bits(b), LeafSize(LSize)
{
  notfound = notFound;
  setKeys(b); 
  bits = b;
  Directory = new ExtendibleLeaf*[DSize(bits)];
  ExtendibleLeaf *leafPtr = new ExtendibleLeaf(LSize);
  for(int i=0; i< DSize(b); i++)
    Directory[i] = leafPtr;//makes the initial directory poinmt to an empty leaf

/* TO TEST WHETHER OR NOT ALL DIRECTORIES INITIALLY POINT AT ONE LEAF
 
  for(int i=0; i<LSize; i++)
    leafPtr->binaryNode[i]=i;

  for(int j = 0; j< DSize(b); j++)
  {
A
A
    for(int i=0; i< LSize; i++)
B
    {
      cout<< Directory[j]->binaryNode[i]<< " ";
    }
    cout<< endl;
  }
*/
} // ExtendibleHash()


void ExtendibleHash::insert(const int &object)
{
  ExtendibleLeaf *ptr = searchIndex(object,bits);
  if (ptr->count < ptr->leafsize && ptr->search(object) == -1)
  {        
    ptr->binaryNode[ptr->count] = object;
    ptr->count = ptr->count + 1;  
  }//if leaf isnt full, insert
/*
  for(int iter = 0; iter< ptr->count; iter++)
  {
    cout<< ptr->binaryNode[iter]<< endl;
  }
  cout<<ptr->count<<endl<<endl; *///TO TEST IF INSERTING CORRECTLY 

  else if (ptr->count == ptr->leafsize)
  {
    if(splitOrExtend(ptr,object) == false)
    {
      extend(object);
      insert(object);
    }
       
  }//else if leaf is full, split or index extends  
} // insert()


void ExtendibleHash::remove(const int &object)
{
  int index = Ehash(object,bits);
  Directory[index]->inputRemove(object);
}  // remove()

void ExtendibleLeaf::inputRemove(int object)
{
  for(int iter = 0; iter < count; iter++)
  {
    if(binaryNode[iter] == object)
    {
      removeFromLeaf(iter);
      iter = count + 1;
    }
  } 
}

const int ExtendibleHash::find(const int &object)
{
  int input = Ehash (object,bits);
  int check = Directory[input]->search(object); 
  if(check == -1)
    return notfound;
  else
    return check;
}
  
int ExtendibleLeaf::search(int input)
{
  for(int iter = 0; iter < count; iter++)
  {
    if(binaryNode[iter] == input)
      return input;
  }

  return -1; //input isnt found
}



void ExtendibleHash::extend(const int &object)
{
  int directorySize = DSize(bits);
  int newDirectorySize = DSize(bits+1); 
  bits++; 
  ExtendibleLeaf** newDirectory = new ExtendibleLeaf*[newDirectorySize];
  for(int iter=0; iter<directorySize; iter++)
  {
    newDirectory[1 + 2*iter] = Directory[iter];
    newDirectory[2*iter] = Directory[iter];
  }
  ExtendibleLeaf** temp = Directory;
  Directory = newDirectory;
  delete temp;
  setKeys(bits);
}  // extednd()

void ExtendibleHash::setKeys(int bits)
{
  binaryKey.clear();
  for(int i = 0; i< DSize(bits); i++)
    binaryKey.push_back(i); 
}
 

bool ExtendibleHash::splitOrExtend (ExtendibleLeaf* ptr, int object)
{

  int marker = Ehash(ptr->binaryNode[0],bits);//amount of bits used to differentiate the 2nd different pattern

  for(int iter = 1; iter < ptr->count; iter++)
  {
    if(marker != Ehash(ptr->binaryNode[iter], bits))
    {
      int newMarker = Ehash(ptr->binaryNode[iter], bits);
      Directory[newMarker] = new ExtendibleLeaf(ptr->leafsize);
      ExtendibleLeaf *ptr2 = Directory[newMarker];
      Directory[newMarker]->insert2Leaf(ptr->binaryNode[iter]);
      ptr->removeFromLeaf(iter);  
        for(int jter = iter; jter<ptr->count; jter++)
        {
          if(Ehash(ptr->binaryNode[jter],bits) == newMarker)
          {
            ptr2->insert2Leaf(ptr->binaryNode[jter]);
            ptr->removeFromLeaf(jter);
            jter--;
          }
        }
      ptr->insert2Leaf(object);
      return true;//can split now insert  
    }  
  }
  
  return false;//cannot split, must extend index first
}

void ExtendibleLeaf::insert2Leaf(int value)
{
  binaryNode[count] = value;
  count++;
}  

void ExtendibleLeaf::removeFromLeaf(int index)
{
  binaryNode[index] = binaryNode[count-1];
  binaryNode[count-1] = 0;
  count--;
}
