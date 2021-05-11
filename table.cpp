/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   table.cpp contains all the member functions used
   to create a hash table ADT

   Last updated: May 7
 */
#include <iostream>
#include <cstring>
#include <cmath>
#include "table.h"
#include <fstream>
#define LINK_LEN 180

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
  
  for(int i = 0; i < table_size; i++){
    if(table[i] != NULL){ //if there is something there
      current = table[i];

      //if you find a match with the first term, print it out
      if(strcmp(current->name, key) == 0){
	std::cout << "term: " << current->name << std::endl;
	std::cout << "description: " << current->description << std::endl;
	std::cout << "links: " << std::endl;
	for(int j = 0; j < current->amount; j++){
	  std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
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
	  for(int j = 0; j < current->amount; j++){
	    std::cout << "   Link #" << j+1 << ": " << current->links[j] << std::endl;
	  }
	  return 1;
	}
      }
    }
  }
  return 0; //did not find any matches
}

/* a function to load information from an external data file.
   It takes in the name of the file, searches for it in the
   directory. If it found the correct file, it tokenizes the text,
   creating new nodes for each term in the file.
   Returns 0 if it could not find the file.
 */
int hash_table::load(char* file_name){
  std::ifstream file;
  file.open(file_name);
  char* char_ptr = NULL;
  
  //if it does not exist return 0
  if(!file){
    return 0;
  }

  //tokenize text into parts
  //  for(int i = 0; i < 
  //char_ptr = strtok(
  
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
    std::cout << "not the first one" << std::endl;
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
    std::cout << "is the first one" << std::endl;
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

/* retrieve information about a matching term */
int hash_table::retrieve(char* term){

  return 0;
}

/* remove all terms that contain a specific link */
int hash_table::remove_by_link(char* link){

  return 0;
}
