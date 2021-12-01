#pragma once   //since we need to include this file in both premimum file(this should be administrator file but I typed the wrong 
			   // name for the header)and premimumuser file  if we do not use this preprocessor #pragma once it will cause a redefinition
               // error, thus I placed this preprocessor here to avoid that problem 

#include<iostream> 
#include <string>
#include<iomanip>     //for std::setprecision(); std::fixed ;
#include<fstream>     //for ofstream
#include<list>        // the list is served as a class template in STL
#include "Account.h"  // include the base class account 

using namespace std;


class User :public Account    //method to show this is the derived class from the bass class account 
{
private:
	
	string	LastPlay, winStreak;  // all attributes for derived class  
	int	wins, losses;
	double winPct;
	string premimum;
	Account acc;
	

public:
	User();     //default constructor 
	User(string n, string p); //new register user
	User(string n, string p, string pm,int wins, int losses, double winPct, string winStreak, string LastPlay); //user played history
	
	//mutator method 
	void setWins(int w);
	void setLosses(int l);
	void setWinPct(double wp);
	void setWinStreak(string ws);
	void setLastPlay(string lp);


	void upgrade_to_premimum(); //bonus requirement ask users to upgrade to premimum user class 

	void updateHistory(bool,string);           // update account history 
	void writeHistoryToFile(ofstream &output);  // write to the input file the updated account history
	void printHistory(); //use if a user request to check his/her account history 

	//accessor
	double getwinPct();
	string getPremimum();
	
};

User::User() :Account()
{
	wins = 0; losses = 0; winPct = 0; winStreak = "0"; LastPlay = "emptyWord";
	premimum = "NO";
}


User::User(string n, string p):Account(n,p)
{
	  wins = 0; losses = 0; winPct = 0; winStreak = "0"; LastPlay = "emptyWord";
	  premimum = "NO";
}


User::User(string n, string p, string pm,int w, int l, double wp, string ws, string lp):Account(n,p)
{
	 wins = w; losses = l; winPct = wp; winStreak = ws; LastPlay = lp;
	 premimum = pm;
}

void User::upgrade_to_premimum() {
	premimum = "YES";
}

void User::setWins(int w) {
	wins = w;
}
void User::setLosses(int l)
{
	losses = l;
}
void User::setWinPct(double wp)
{
	winPct = wp;
}
void User::setWinStreak(string ws)
{
	winStreak = ws;
}
void User::setLastPlay(string lp)
{
	LastPlay = lp;
}

void User::printHistory()
{

	cout << setw(15) << "Name" << setw(15) << "Premimum"<< setw(15) << "Wins" << setw(15) << "Losses" << setw(15);
	cout << "WinPct" << setw(15) << "WinStreak" << setw(20) << "LastPlay" << endl;

	cout << setw(15) << getName() << setw(15) << premimum << setw(15) << wins << setw(15) << losses << setw(13) << setprecision(4);
	cout << winPct << " %" << setw(15) << winStreak << setw(20) << LastPlay << endl;
}

void User::updateHistory(bool w, string lp)
{
	if (w)	// win
	{
		++wins;
		if (winStreak == "-1")
			winStreak = "0";
		else //(winStreak == "0")
			winStreak = "+1";
	}
	else
	{
		// losses
		++losses;
		if (winStreak == "+1")
			winStreak = "0";
		else //(winStreak == "0")
			winStreak = "-1";
	}
	LastPlay = lp;
	winPct = ((double)wins*100 / ((double)wins+losses));
}


void User::writeHistoryToFile(ofstream &output)
{
	
	if (output.fail())
	{
		cout << "ERROR: UserAccountHistory.txt can not open\n";
		return;

	}
	// setting the format for the output file 
		output << setw(15) << getName() << setw(15) << getPassword() << setw(15) << premimum << setw(15) << wins << setw(15)
		 << losses << setw(13) << setprecision(4) << winPct << " %" << setw(15)
		 << winStreak << setw(20) << LastPlay << endl;
	

}

string User::getPremimum()
{
	return premimum;
}

double User::getwinPct() {

	return winPct;
}