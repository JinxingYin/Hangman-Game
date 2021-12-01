
/* This is the header file for the administrator class (typo for the header file name) */
#include <iostream>
#include <string>
#include <list>
#include <fstream>   
#include <iterator>   //use for iterator implementation
#include "User.h"     // inherits from the user class 
using namespace std; 

class premimum :public User {

public:
	void sorting(list <string>& wordlist, ofstream& file);                         // three required task designs 
	void add(list<string>& wordlist, string word, ofstream& file);
	void remove(list <string>& wordlist, string word, ofstream& file);
};


/*---------------------------------------------------------*/
void premimum::sorting(list <string>& wordlist,ofstream& file) {                   //sorting the list by built in function sort 

	wordlist.sort();
	list<string>::iterator itr;
	for (itr = wordlist.begin(); itr != wordlist.end(); ++itr) 
		file << *itr << endl;
	
	return;
}
void premimum::add(list <string>& wordlist, string word,ofstream& file) {           //checking does the word exist on the wordlist file ,if so 
	                                                                                // do nothing,else add it and output to update the wordlist 
	wordlist.push_back(word);                                                       //file
	wordlist.sort();
	list<string>::iterator itr1;
	for (itr1 = wordlist.begin(); itr1 != wordlist.end(); ++itr1)
		file << *itr1 << endl;
	return;
}
void premimum::remove(list<string>& wordlist, string word,ofstream& file) {          // checking does the desired deltete word exist in the word 
	                                                                                // file or not if so, delete, else print error message.
	wordlist.remove(word);
	wordlist.sort();
	list<string> ::iterator itr2;
	for (itr2 = wordlist.begin(); itr2 != wordlist.end(); ++itr2)
		file << *itr2 << endl;
	return;
}

