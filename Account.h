#include <iostream>
#include<string>
using namespace std;

/*Header file starts from here contains the declaration of account class*/
/*This is the bass class account which simply ask either player or admin to login in their account */
class Account
{
private:
	string	name;
	string password;
public:
	Account();                //default constructor
	Account(string, string);  //parameterized constructor
	bool login(string, string);
	//accessor 
	string getName();   
	string getPassword();
	//mutator
	void setName(string);
	void setPassword(string);
};


/*---------------------------------------------------------*/
/*Implementation of the base class account */

Account::Account()
{
	name = ""; password = "";
}

Account::Account(string n, string p)
{
	name = n; password = p;
}

bool Account::login(string n, string p)
{
	if (name == n)
		if (password == p)
			return true;
	return false;

}

string Account::getName()
{
	return name;
}

string Account::getPassword()
{
	return password;
}

void Account::setName(string n) {
	name = n;
}
void Account::setPassword(string p)
{
	password = p;
}