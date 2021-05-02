/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   table.cpp contains all the member functions used
   to create a hash table ADT

   Last updated: May 2
 */
#include <iostream>

/* The constructor initialies the table size */
table::table(int size){

}

/* The destructor deallocates all dynamic memory */
table::~table(){

}

/* the first hash function.
   takes in a key, returns an index */
int table::hash_one(char* key){

  return 0;
}

/* the second hash function.
   takes in a key, returns an index */
int table::hash_two(char* key){

  return 0;
}

/* add a term with a list of website links */
int table::add(char* term, char* description, char** links){

  return 0;
}

/* display the information for a matching key */
int table::display(char* key){

  return 0;
}

/* load information from an external data file */
int table::load(char* file_name){

  return 0;
}

/* add a new website link to an existing term */
int table::add_website(char* term, char** links){

  return 0;
}

/* remove by keyword */
int table::remove_by_key(char* term){

  return 0;
}

/* retrieve information about a matching term */
int table::retrieve(char* term){

  return 0;
}

/* remove all terms that contain a specific link */
int table::remove_by_link(char* link){

  return 0;
}
