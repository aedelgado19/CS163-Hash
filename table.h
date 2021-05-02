/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   table.cpp contains all function prototypes
   to create a hash table ADT

   Last updated May 2                                 
 */
#include <iostream>

struct node {
  char* term;
  char* description;
  char** links;
};

//all int return types return 1 for success and 0 for failure
class table {
public:
  //task 1: Constructor (takes in argument for size)  
  table(int size);

  //task 2: Destructor                                
  ~table();

  //task 4: add a term with a list of website links 
  int add(char* term, char* description, char** links);

  //task 5: display the information for a matching key   
  int display(char* key);

  //task 6: load info from an external data file 
  int load(char* file_name);

  //task 7: add a new website link to an existing term
  int add_website(char* term, char** links);

  //task 8: remove by keyword
  int remove_by_key(char* term);

  //task 9: retrieve info about a matching term       
  int retrieve(char* term);

  //task 10: remove all that contain a specific link  
  int remove_by_link(char* link);

private:
  //task 3: hash functions (each is different)        
  int hash_one(char* key);
  int hash_two(char* key);
};
