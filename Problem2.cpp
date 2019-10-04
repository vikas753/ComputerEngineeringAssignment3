///////////////////////////////////////////////////////////
//
//   Name  : VIKAS VEERABATHINI
//   NU ID : 001302155
//   Implement a C++ Program to study how hash table size 
//   affects collisions amongst elements while probing
//
//////////////////////////////////////////////////////////


#include<iostream>
#include<random>
#include<vector>
#include<string.h>

using namespace std;


// getRandomNumber : we are using a normal distribution and  a seed 
// obtained from mersenne_twister_engine to generate a randome number
// as shown in below api . 

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
uniform_int_distribution<> dis(0, 1000);

int getRandomNumber()
{
  return dis(gen);
}

// getRandomBirthDate : random number's remainder when divided by NUM_MONTHS
// will usually provide a number in range of 0-11 , adding 1 will provide a random
// month number . We can apply above caveat to dd and yy too . 

#define NUM_MONTHS 12
#define NUM_DAYS 28
#define NUM_YEARS 5

#define OFS_MM 10000
#define OFS_DD   100
#define OFS_YY     1

int getRandomBirthDate()
{
  int Month = 1+ ( getRandomNumber() % NUM_MONTHS );
  int Day   = 1+ ( getRandomNumber() % NUM_DAYS );
  int Year  =  getRandomNumber() % NUM_YEARS ;
  int BirthDate = Month * OFS_MM + Day * OFS_DD + Year * OFS_YY ; 
  return BirthDate ;  
}

#define PRESET_SENTINEL 0x5a5a5a5a
#define DELETE_SENTINEL 0x5b5b5b5b

// getVectorBySize : Initialize a container with size as given in argument
// with a value of sentinel say 0x5a5a5a5a

vector<int> getVectorBySize(int size)
{
  vector<int> a;
  a.assign(size,PRESET_SENTINEL);
  return a;
}

// Inserting a key into a hashtable
// Note that we are resolving collision by chaining ( indirectly ) , 
// where we would be maintaining the count of elements collisions
// encountered at that slot
//
void HashTableInsert(vector<int>& HashTable , int key)
{
  // Hash table function is below
  int hashTableIndex = key % HashTable.size();
  if(HashTable[hashTableIndex] == PRESET_SENTINEL)
  {
    HashTable[hashTableIndex] = 1; 
  }
  else
  {
    HashTable[hashTableIndex]++;  
  }   
}

// Display Hashtable contents with Hashtable index and value . 

void DisplayHashTable(vector<int>& HashTable)
{
  cout << " Hash table Size " << HashTable.size() << endl;
  for(int i=0;i<HashTable.size();i++)
  {
    cout << i << "  | " << HashTable[i] << endl;
  }
  cout << endl;
}

// Calculate the mean of Hash table values in table slots

#define INVALID_MEAN -1
#define INVALID_VARIANCE INVALID_MEAN

double getMean(vector<int> HashTable)
{
  if(HashTable.size()>0)
  {
    int sum = 0;
    for(int i=0;i<HashTable.size();i++)
    {
      sum = sum + HashTable[i];
    }
    return ( sum / HashTable.size());
  }
  else
  {
    cout << " Hash Tables size is zero ! " << endl ; 
    return INVALID_MEAN;
  }   
}

// Calculate the variance of elements in Hashtable slots

double getVariance(vector<int> HashTable)
{
  double mean = getMean(HashTable) , sumElements = 0;
  if(HashTable.size()>0)
  {
    for(int i=0;i<HashTable.size();i++)
    {
      sumElements = sumElements +((HashTable[i] - mean)*(HashTable[i] - mean));
    } 
    return (sumElements / HashTable.size());
  }
  else
  {
    cout << " Hash Tables size is zero ! " << endl ; 
    return INVALID_VARIANCE;
  }  
}

// Calculate the minimum value in Hash table

int getMinimum(vector<int> HashTable)
{
  int minimum = HashTable[0];
  for(int i=1;i<HashTable.size();i++)
  {
    if(HashTable[i] < minimum)
    {
      minimum = HashTable[i];
    } 
  }
  return minimum ; 
}

// Calculate the maximum value in Hash table

int getMaximum(vector<int> HashTable)
{
  int maximum = HashTable[0];
  for(int i=1;i<HashTable.size();i++)
  {
    if(HashTable[i] > maximum)
    {
      maximum = HashTable[i];
    } 
  }
  return maximum ; 
}


#define NUM_RANDOM_BIRTHDATES 1000
#define NUM_HASH_TABLES 4

int HashTableSizes[NUM_HASH_TABLES] = {64,66,67,61};

int main()
{
  vector<int> RandomNumberStorage = getVectorBySize(1000);

  for(int i=0;i<NUM_RANDOM_BIRTHDATES;i++)
  {
    RandomNumberStorage[i] = getRandomBirthDate();
  }
  
  vector<int> HashTable[NUM_HASH_TABLES];
  
  for(int i=0;i<NUM_HASH_TABLES;i++)
  {
    HashTable[i] = getVectorBySize(HashTableSizes[i]);
  }
  
  for(int j=0;j<NUM_HASH_TABLES;j++)
  {
    for(int i=0;i<NUM_RANDOM_BIRTHDATES;i++)
    {
      HashTableInsert(HashTable[j],RandomNumberStorage[i]);
    }
  }

  for(int j=0;j<NUM_HASH_TABLES;j++)
  {
    DisplayHashTable(HashTable[j]);
    cout << " Mean of Hash Table is     : " << getMean(HashTable[j]) << endl ; 
    cout << " Minimum of Hash Table is  : " << getMinimum(HashTable[j]) << endl ; 
    cout << " Maximum of Hash Table is  : " << getMaximum(HashTable[j]) << endl ; 
    cout << " Variance of Hash Table is : " << getVariance(HashTable[j]) << endl ; 
    
  } 
  
  

  return 0;
}
