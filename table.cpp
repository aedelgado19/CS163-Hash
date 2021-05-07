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
#define LINK_LEN 180

/* The constructor initializes the table size 
   and initializes every index in the table to null. 
   It is called whenever the user creates a 
   new table using the 'new' keyword.*/
hash_table::hash_table(int size){
  table_size = size;

  //set all indices to null
  for(int i = 0; i < table_size; i++){
    std::cout << "i: " << i << std::endl;  
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
  t_node* current = NULL;
  
  for(int i = 0; i < table_size; i++){ //walk through array
    current = table[i];
    while(current != NULL){ //walk through chain
      t_node* hold = table[i]->next;
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
  for(int i = 0; i < strlen(key); i++){
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
  for(int i = 0; i < strlen(key); i++){
    to_return += pow(key[i], 2);
  }

  //mod it by size
  to_return = to_return % table_size;
  return 0;
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
  t_node* new_node = new t_node;
  new_node->name = new char[strlen(description) + 1];
  strcpy(new_node->name, term);
  new_node->description = new char[strlen(description) + 1];
  strcpy(new_node->description, description);

  new_node->links = new char*[amount * LINK_LEN];
  for(int i = 0; i < amount; i++){
    strcpy(new_node->links[i], links[i]);
  }

  //if the index is null, insert the new node there
  if(!table[index]){
    table[index] = new_node;
    return 1;
  }

  //if the index is not null, chain it on
  t_node* traverse = table[index];
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
  t_node* current = NULL;
  
  for(int i = 0; i < table_size; i++){
    if(table[i] != NULL){ //if there is something there
      current = table[i];

      //if you find a match with the first term, print it out
      if(strcmp(current->name, key) == 0){
	std::cout << "term: " << current->name << std::endl;
	std::cout << "description: " << current->description << std::endl;
	std::cout << "links: " << std::endl;
	for(int j = 0; j < (sizeof(current->links)/sizeof(current->links[0])); j++){
	  std::cout << current->links[j] << std::endl;
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
	  for(int j = 0; j < (sizeof(current->links)/sizeof(current->links[0])); j++){
	    std::cout << current->links[j] << std::endl;
	  }
	  return 1;
	}
      }
    }
  }
  return 0; //did not find any matches
}

/* load information from an external data file */
int hash_table::load(char* file_name){

  return 0;
}

/* add a new website link to an existing term */
int hash_table::add_website(char* term, char** links){

  return 0;
}

/* remove by keyword */
int hash_table::remove_by_key(char* term){

  return 0;
}

/* retrieve information about a matching term */
int hash_table::retrieve(char* term){

  return 0;
}

/* remove all terms that contain a specific link */
int hash_table::remove_by_link(char* link){

  return 0;
}
