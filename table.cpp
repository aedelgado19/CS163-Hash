/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   table.cpp contains all the member functions used
   to create a hash table ADT

   Last updated: May 11
 */
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include "table.h"
#include <fstream>
#define LINK_LEN 180
#define MAX 500
#define TABLE_SIZE 5

/* The constructor initializes the table size 
   and initializes every index in the table to null. 
   It is called whenever the user creates a 
   new table using the 'new' keyword.*/
hash_table::hash_table(int size){
  table = new node*[size];
  table_size = size;
  //set all indices to null
  for(int i = 0; i < table_size; i++){
    table[i] = NULL;
  }
}

/* The destructor deallocates all dynamic memory.
   To do so, it walks through the array. At each index, 
   it finds the pointer to the chain (if it exists), then
   traverses the chain to delete all nodes. It then sets
   the table back to null.
   */
hash_table::~hash_table(){
  node* current = NULL;
  
  for(int i = 0; i < table_size; i++){ //walk through array
    current = table[i];
    while(current != NULL){ //walk through chain
      node* hold = table[i]->next;
      delete current;
      current = hold;
    }
    delete table[i]; //delete the a_node at that index
    table[i] = NULL; 
  }
}

/* the first hash function. It takes in a key
   and returns an index. This specific hash function
   multiplies all letters of the key together by their
   ascii value, then divides by the number of letters that
   there are. Finally it is modded by the size of the table to
   keep the produced index within the range of the table. */
int hash_table::hash_one(char* key){
  int to_return = 1;
  int count = 0;

  //multiply together all the letters in the key
  for(int i = 0; i < (int) strlen(key); i++){
    to_return *= (int) key[i];
    count++;
  }

  //divide the number produced above by how many letters there are
  to_return /= count;
  to_return = to_return % table_size; //mod it by table size
  return to_return;
}

/* the second hash function. It takes in a key
   and returns an index. This specific hash function squares
   each letter of the key and adds all the results together.
   Finally, it is modded by the size of the table to keep the
   produced index within the range of the table.*/
int hash_table::hash_two(char* key){
  int to_return = 0;

  //square each letter and add results together
  for(int i = 0; i < (int) strlen(key); i++){
    to_return += pow(key[i], 2);
  }

  //mod it by size
  to_return = to_return % table_size;
  return to_return;
}

/* a function to add a term with a list of website links.
   here, the function is provided four arguments from main:
   the term, its description, amount of links, and the array of links. 
   This function will create a new node to store these items
   (with the passed in arguments as part of the 'term' structure 
   of a node), and run its term through the hash function to retrieve
   an index. The node is inserted at that index, and chained onto the list
   if there is a collision.*/
int hash_table::add(char* term, char* description, int amount, char** links){
  int index = hash_two(term);
  
  //make the new term node
  node* new_node = new node;
  new_node->name = new char[strlen(description) + 1];
  strcpy(new_node->name, term);
  new_node->description = new char[strlen(description) + 1];
  strcpy(new_node->description, description);
  new_node->amount = amount;
  
  //copy over link array
  new_node->links = new char*[amount * LINK_LEN];
  for(int i = 0; i < amount; i++){
    new_node->links[i] = new char[strlen(links[i])];
    strcpy(new_node->links[i], links[i]);
  }
  
  //if the index is null, insert the new node there
  if(!table[index]){
    table[index] = new_node;
    new_node->next = NULL;
    return 1;
  }
  
  //if the index is not null, chain it on
  node* traverse = table[index];
  while(traverse->next != NULL){
    traverse = traverse->next;
  }
  traverse->next = new_node;
  new_node->next = NULL;
  return 1;
}

/* a function to display the information for a matching key.
   this function traverses each chain in the array to find the key.
   Once it is found, it displays the description and the links associated. */
int hash_table::display(char* key){
  if(!table) return 0;
  node* current = NULL;
  int i = hash_two(key);
  if(!table[i]) return 0; //nothing was found at that index

  //because the line above returns, the following code only fires if table[i] != NULL
  current = table[i];
  //if you find a match with the first term, print it out
  if(strcmp(current->name, key) == 0){
    std::cout << "term: " << current->name << std::endl;
    std::cout << "description: " << current->description << std::endl;
    std::cout << "links: " << std::endl;
    if(current->links[0] == NULL){
      std::cout << "   you deleted all the links." << std::endl;
    }
    for(int j = 0; j < current->amount; j++){
      if(current->links[j]){
	std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
      }
    }
    return 1;
  }

  //otherwise traverse the chain
  while(current->next != NULL){
    current = current->next;
    if(strcmp(current->name, key) == 0){ //if you find a match
      std::cout << "term: " << current->name << std::endl;
      std::cout << "description: " << current->description << std::endl;
      std::cout << "links: " << std::endl;
      if(current->links[0] == NULL){
	std::cout << "   you deleted all the links." << std::endl;
      }
      for(int j = 0; j < current->amount; j++){
	if(current->links[j]){
	  std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
	}
      }
      return 1;
    }
  }
  return 0; //did not find any matches
}

/* a function to load information from an external data file.
   a text file for this program must be structured as follows:
      term name
      description
      amount of website links
      website links separated by a newline

   Returns 0 if it could not find the file.
 */
int hash_table::load(char* file_name){
  std::ifstream file;
  file.open(file_name);
  char line[LINK_LEN];
  
  //if it does not exist return 0
  if(!file){
    return 0;
  }

  //loop through whole file and read it in
  while(!file.eof()){
    //allocate memory
    node* new_node = new node;
    new_node->name = new char[40];
    new_node->description = new char[250];
    file.getline(line, MAX); //term
    strcpy(new_node->name, line);
    file.getline(line, MAX); //desc
    strcpy(new_node->description, line);
    file.getline(line, MAX); //amount
    new_node->amount = atoi(line);
    char** new_array = new char*[new_node->amount];
    for(int j = 0; j < new_node->amount; j++){
      new_array[j] = new char[LINK_LEN];
      file.getline(line, MAX);
      strcpy(new_array[j], line);
    }
    int index = hash_two(new_node->name);
    table[index] = new_node;
    return 1;
  }
  return 0; 
}

/* a function to add a new website link to an existing term.
   It takes in the term you would like to add to, and the links
   to add. Returns 0 if it could not find the existing node.
   Returns 1 if successful. */
int hash_table::add_website(char* term, char* link){
  int index = hash_two(term);
  if(!table[index]) return 0;
  node* current = table[index];
  char** new_array = new char*[current->amount + 1];
  
  //locate the correct node
  if(strcmp(current->name, term) != 0){ //first node is NOT a match
    while(current->next != NULL){
      current = current->next;
      if(strcmp(current->name, term) == 0){
	//copy over contents of the original array
	for(int i = 0; i < current->amount; i++){
	  new_array[i] = new char[strlen(current->links[i])];
	  strcpy(new_array[i], current->links[i]);
	  delete [] current->links[i];
	}
  
	//copy over new website link
	new_array[current->amount + 1] = new char[strlen(link) + 1];
	strcpy(new_array[current->amount + 1], link);
	current->amount++;
	delete [] current->links;
	current->links = new_array;
	return 1;
      }
    }  
  } else { //first node IS a match
    //copy over contents of the original array
    for(int i = 0; i < current->amount; i++){
      new_array[i] = new char[strlen(current->links[i])];
      strcpy(new_array[i], current->links[i]);
      delete [] current->links[i];
    }
  
    //copy over new website link
    new_array[current->amount + 1] = new char[strlen(link) + 1];
    strcpy(new_array[current->amount + 1], link);
    current->amount++;
    delete [] current->links;
    current->links = new_array;
    return 1;
  }
  return 0; //couldn't find term
}

/* a function to remove by keyword.
   It is supplied the term from main, plugs it into the hash
   function, then searches for the term at that array index.
   A 0 is returned if the function could not find that term, 
   and a 1 is returned if it was successful in removing it.*/
int hash_table::remove_by_key(char* term){
  if(!table) return 0;
  int i = hash_two(term);
  node* current = NULL;
  node* prev = NULL;

  if(!table[i]) return 0; //nothing matches that term's key
  current = table[i];

  //CASE 1: found a match with the head pointer
  if(strcmp(current->name, term) == 0){
    table[i] = current->next;
    delete [] current->links;
    current->links = NULL;
    delete current;
    table[i] = NULL;
    return 1;
  }
  
  //CASE 2: it's not the head, so search chain for a match.
  while(current->next != NULL){
    prev = current;
    current = current->next;
    if(strcmp(current->name, term) == 0){
      prev->next = current->next;
      node* hold = current;
      current = current->next;
      delete [] hold->links;
      hold->links = NULL;
      delete hold;
      return 1;
    }
  }
  return 0; //did not find any matches
}

/* retrieves information about a matching term. It supplies
   the matching info back to main through the argument list. 
   To find the info to retrieve, it looks at the hashed index
   of the provided term. If it cannot find anything, it returns 0.*/
int hash_table::retrieve(char* term, char*& to_return){
  if(!table) return 0;
  int i = hash_two(term);
  if(!table[i]) return 0; //nothing was found at that index
  node* current = table[i];
  
  //check the first term
  if(strcmp(term, current->name) == 0){
    
    return 1;
  }
  
  //check its chain
  while(current->next != NULL){
    current = current->next;
    if(strcmp(term, current->name) == 0){

      return 1;
    }
  }
  
  return 0;
}

/* a function to remove all terms that contain a specific link.
   This function must traverse the whole table (since you cannot
   use the hash on it if no term is provided. Returns 0 if the link
   could not be found, and 1 if successful.*/
int hash_table::remove_by_link(char* link){
  if(!table) return 0;
  node* current = NULL;
  bool flag = false;

  //loop through the whole table
  for(int i = 0; i < TABLE_SIZE; i++){
    current = table[i];
    if(current){ //if there's something there in that index
      //check the head node's links
      for(int j = 0; j < current->amount; j++){
	if(current->links[j]){
	  if(strcmp(current->links[j], link) == 0){ //if you find a matching link
	    flag = true;
	    delete current->links[j];
	    for(int k = j; k < current->amount; k++){
	    current->links[k] = current->links[k+1]; // shift them all down one
	    }
	  }
	}
      }
      //now traverse the chain to find any more links
      while(current->next != NULL){
	//check all the links
	for(int j = 0; j < current->amount; j++){
	  if(current->links[j]){
	    if(strcmp(current->links[j], link) == 0){
	      flag = true;
	      delete current->links[j];
	      for(int k = j; k < current->amount; k++){
		current->links[k] = current->links[k+1]; // shift them all down one
	      }
	    }
	  }
	}	
      }
    }
  }
  if(flag == false){
    return 0; //couldn't find a match
  }
  return 1;
}

/* this is a function I wrote (not required) that prints out the entire
   table. I use it for debugging, but it is not essential for the
   functionality of the ADT */
int hash_table::print(){
  if(!table) return 0;
  node* current = NULL;
  
  for(int i = 0; i < TABLE_SIZE; i++){
    current = table[i];
    if(current){ //if there's something there  
      //print out the first term:
      std::cout << " " << std::endl;
      std::cout << "index: " << i << std::endl;
      std::cout << "term: " << current->name << std::endl;
      std::cout << "description: " << current->description << std::endl;
      std::cout << "links: " << std::endl;
      if(current->links[0] == NULL){
	std::cout << "   you deleted all the links." << std::endl;
      }
      for(int j = 0; j < current->amount; j++){
	if(current->links[j]){
	  std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
	}

      }

      //check chain
      while(current->next != NULL){
	current = current->next;
	std::cout << " " << std::endl;
	std::cout << "index: " << i << std::endl;
	std::cout << "term: " << current->name << std::endl;
	std::cout << "description: " << current->description << std::endl;
	std::cout << "links: " << std::endl;
	if(current->links[0] == NULL){
	  std::cout << "   you deleted all the links." << std::endl;
	}
	for(int j = 0; j < current->amount; j++){
	  if(current->links[j]){
	    std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
	  }
	}
      }
    }
  }
  return 1;
}
