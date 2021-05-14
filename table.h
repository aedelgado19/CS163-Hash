/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   table.cpp contains all function prototypes
   to create a hash table ADT

   Last updated May 7
*/
#include <iostream>

/* a struct to hold term nodes.
   contains a name, description, and links. 
   the array index points to the head node in a chain */
struct node {
  char* name;
  char* description;
  char** links;
  int amount;
  node* next;
};

//all int return types return 1 for success and 0 for failure
class hash_table {
public:
  //task 1: Constructor (takes in argument for size)
  hash_table(int size = 5);

  //task 2: Destructor
  ~hash_table();

  //task 4: add a term with a list of website links
  int add(char* term, char* description, int amount, char** links);

  //task 5: display the information for a matching key
  int display(char* key);

  //task 6: load info from an external data file
  int load(char* file_name);

  //task 7: add a new website link to an existing term
  int add_website(char* term,  char* link);

  //task 8: remove by keyword
  int remove_by_key(char* term);

  //task 9: retrieve info about a matching term       
  int retrieve(char* term, char* to_return[]);

  //task 10: remove all that contain a specific link
  int remove_by_link(char* link);

  //a function (not required for this project) that I wrote
  //to display the whole table
  int print();
  
private:
  //task 3: hash functions (each is different)
  int hash_one(char* key);
  int hash_two(char* key);
  node** table;
  int table_size;
};
