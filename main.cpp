/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a testing site for the table ADT

   Last updated: May 11, 2021
 */
#include <iostream>
#include <cstring>
#include "table.h"
#define SIZE 5
#define LINK_LEN 180
using namespace std;


void print_error_messages(int success, const char function_name[]);

int main(){
  int success = 0;
  hash_table* table = new hash_table(SIZE);
  char input[20];
  char term[40];
  char link[LINK_LEN];
  char description[250];
  int amount = 0;
  char file[250];
  
  cout << " " << endl;
  cout << "Welcome to Term Search." << endl;
  while(strcmp(input, "q") != 0){
    cout << "---------------------------------" << endl;
    cout << "Valid commands (for submission 3) are: " << endl;
    cout << "add - add a new term, its description, and its links" << endl;
    cout << "search - display the information for a term" << endl;
    cout << "load - load the information from an external data file" << endl;
    cout << "addweb - add a new website link to an existing term" << endl;
    cout << "rmk - remove by keyword" << endl;
    cout << "retrieve - retrieve info about a specific term" << endl;
    cout << "rml - remove all terms containing a specific link" << endl;
    cout << "q - quit" << endl;
    cout << " " << endl;
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    cout << "---------------------------------" << endl;

    for(int i = 0; i < (int) strlen(input); i++){
      input[i] = (int) tolower(input[i]);
    }
    
    //add calls the add function in the table class
    if(strcmp(input, "add") == 0){
      cout << "Enter the term. " << endl;
      cout << "> ";
      cin.get(term, 40);
      cin.get();
      cout << "Enter the description. " << endl;
      cout << "> ";
      cin.get(description, 250);
      cout << "How many links are you adding to this term? " << endl;
      cout << "> ";
      cin >> amount;
      cin.get();

      //make array of size amount
      char* links[amount];
      for(int i = 0; i < amount; i++){ //populate links array
	cout << "Enter your link: " << endl;
	cout << "> ";
	cin.get(link, 180);
	cin.get();
	links[i] = new char[180];
	strcpy(links[i], link);
      }
      success = table->add(term, description, amount, links);
      print_error_messages(success, "add");
    }
    
    //search calls the display function in the table class
    if(strcmp(input, "search") == 0){
      cout << "Enter the term you would like to search for. " << endl;
      cout << "> ";
      cin.get(term, 40);
      cin.get();
      for(int i = 0; i < (int) strlen(term); i++){
	term[i] = (int) tolower(term[i]);
      }
      success = table->display(term);
      print_error_messages(success, "search");
    }

    //load from external data file
    if(strcmp(input, "load") == 0){
      cout << "Enter the name of the external data file." << endl;
      cout << "> ";
      cin.get(file, 250);
      cin.get();
      success = table->load(file);
      print_error_messages(success, "load");
    }
    
    //add a new website to existing term
    if(strcmp(input, "addweb") == 0){
      cout << "What term would you like to add to?" << endl;
      cout << "> ";
      cin.get(term, 40);
      cin.get();
      cout << "Enter your link." << endl;
      cout << "> ";
      cin.get(link, LINK_LEN);
      cin.get();
      success = table->add_website(term, link);
      print_error_messages(success, "addweb");

    }
    //remove by keyword
    if(strcmp(input, "rmk") == 0){
      cout << "Enter the term you would like to remove." << endl;
      cout << "> ";
      cin.get(term, 40);
      cin.get();
      success = table->remove_by_key(term);
      print_error_messages(success, "rmkey");
    }

    //remove all containing a certain link
    if(strcmp(input, "rml") == 0){
      cout << "Enter the link you would like to remove from all terms." << endl;
      cout << "> ";
      cin.get(link, LINK_LEN);
      cin.get();
      success = table->remove_by_link(link);
      print_error_messages(success, "rmlink");  
    }

    //show all information about a term
    if(strcmp(input, "retrieve") == 0){
      char* to_return = new char[250];
      cout << "Enter the term you would like to search for." << endl;
      cout << "> ";
      cin.get(term, 40);
      cin.get();
      success = table->retrieve(term, to_return);
      print_error_messages(success, "retrieve");
    }

    //function (not required) that I made for debugging. prints out the whole table
    if(strcmp(input, "print") == 0){
      table->print();
    }
  }
  cout << "Goodbye!" << endl;
  return 0;
}

void print_error_messages(int success, const char function_name[]){
  if(success == 1){
    if(strcmp(function_name, "add") == 0){
      cout << "Term added successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "load") == 0){
      cout << "Terms loaded successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "addweb") == 0){
      cout << "Website added successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "rmkey") == 0){
      cout << "Term removed successfully." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "rmlink") == 0){
      cout << "All terms containing that link were removed successfully." << endl;
      cout << " " << endl;
    }
  } else {
    if(strcmp(function_name, "search") == 0){
      cout << "Nothing to display for that term." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "load") == 0){
      cout << "Could not find the file you were looking for." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "rmkey") == 0){
      cout << "Could not find the term you were looking for." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "rmlink") == 0){
      cout << "Could not find the link you were looking for." << endl;
      cout << " " << endl;
    }
    if(strcmp(function_name, "retrieve") == 0){
      cout << "Nothing could be found for that term." << endl;
    }
  }
}

