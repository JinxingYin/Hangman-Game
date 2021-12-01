#include <iostream>
#include <string>
#include <iomanip>
#include "User.h"
/*This is the Bonus part two which requires the designer to give a premimum user class inherits from the use class */
using namespace std;

class premimumuser:public User{
public:                                                                 // premimumuse class right clear own history or check rank for the game 
	void clear_history(string,list<User>& lt);
	void check_rank(list<User> accountlist);

};

void premimumuser::clear_history(string name,list<User>& lt) {             // clear history implementation is just set the game history to be zero and 
	list<User>::iterator itr;                                              //set lastplay to empty word;
	for(itr=lt.begin(); itr!=lt.end(); ++itr)
	if ((*itr).getName() == name) {
		(*itr).setWins(0);
		(*itr).setLosses(0);
		(*itr).setWinPct(0);
		(*itr).setWinStreak("0");
		(*itr).setLastPlay("emptyWord");
	}

	return;

}
void premimumuser::check_rank(list<User>  accountlist) {                        // check rank by the user winrate
	vector<double> wr;                                                          // and then associated name with the winrate. 
	vector<string> user;
	list<User>::iterator ltr;
	int i, j;
	double temp;
	string stemp;

	for (ltr = accountlist.begin(); ltr != accountlist.end(); ++ltr) {            // push the name string into a string vector 
		user.push_back((*ltr).getName());                                         // push the win rate string to a double vector
		wr.push_back((*ltr).getwinPct());
	}
	for (j = 0; j < wr.size(); j++) {                                             //sorting the winrate by descending order
		for (i = j + 1; i < (wr.size() - 1); i++) {
			if (wr[j] < wr[i])
			{
				temp = wr[i];
				wr[i] = wr[j];
				wr[j] = temp;

				stemp = user[i];
				user[i] = user[j];
				user[j] = stemp;
			}
		}
	}
	//cout << "The Rank for each player in descending order " << endl;
	for (i = 0; i < user.size(); i++)
		cout << user[i] << " ";
	cout << endl;
	//cout << "With their win percent" << endl;
	cout << setprecision(2)<< fixed;
	for (j = 0; j < wr.size(); j++)
		cout << wr[j] << " ";

}
