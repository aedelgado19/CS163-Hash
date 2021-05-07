/* Author: Allison Delgado
   Class: CS 163 Spring 2021
   main.cpp acts as a testing site for the table ADT

   Last updated: May 7
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
  
  cout << " " << endl;
  cout << "Welcome to Term Search." << endl;
  while(strcmp(input, "q") != 0){
    cout << "---------------------------------" << endl;
    cout << "Valid commands (for submission 2) are: " << endl;
    cout << "add - add a new term, its description, and its links" << endl;
    cout << "search - display the information for a term" << endl;
    cout << " " << endl;
    cout << "> ";
    cin.get(input, 20);
    cin.get();
    cout << "---------------------------------" << endl;

    //change input to lowercase
    for(int i = 0; i < (int) strlen(input); i++){
      input[i] = tolower(input[i]);
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
      char** links = new char*[amount * LINK_LEN];
      for(int i = 0; i < amount; i++){ //populate links array
	cout << "Enter your link: " << endl;
	cout << "> ";
	cin.get(link, 180);
	cin.get();
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
      success = table->display(term);
      print_error_messages(success, "search");
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
  } else {
    if(strcmp(function_name, "search") == 0){
      cout << "Nothing to display for that term." << endl;
      cout << " " << endl;
    }
  }
}
