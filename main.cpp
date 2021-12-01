#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <list>
#include "premimum.h"
#include "Premimumuser.h"
using namespace std;

//print the dash line for the boundary
void printBoarder()
{
	cout << "+---------------------------------+" << endl;
}

//print prompt word and left right boundary
void printData(string data)
{
	cout << "|";
	bool backFoward = true;
	for (int i = data.length(); i < 33; i++)
	{
		if(backFoward)
			data = " " + data;
		else
			data = data + " ";
		backFoward = !backFoward;
	}
	cout << data << "|" << endl;
}


//draw hangman image
void DrawHangman(int guessCount)
{
	printData("|");
	if (guessCount == 0)
	{
		printData(" ");
		printData(" ");
		printData(" ");
	}
	else if (guessCount == 1)
	{
		printData("O");
		printData(" ");
		printData(" ");
	}
	

	else if (guessCount == 2)
	{
		printData("O");
		printData("|");
		printData(" ");
	}

	else if (guessCount == 3)
	{
		printData("O");
		printData("/| ");
		printData(" ");
	}

	else if (guessCount == 4)
	{
		printData("O");
		printData("/|\\");
		printData(" ");
	}

	else if (guessCount == 5)
	{
		printData("O");
		printData("/|\\");
		printData("/  ");
	}

	else if (guessCount == 6)
	{
		printData("O");
		printData("/|\\");
		printData("/ \\");
	}
	

}


//update guessing word and image for hangman
bool PrintWordAndCheckWin(string word, string guessed)
{
	bool won = true;
	string s;
	for (int i = 0; i < word.length(); i++)
	{
		if (guessed.find(word[i]) == string::npos)
		{
			won = false;
			s += "_ ";
		}
		else
		{
			s += word[i];
			s += " ";
		}
	}
	printBoarder();
	printData(s);
	printBoarder();
	return won;
}

//generate a random word for usr to guess in the hangman game
string LoadRandomWord(string path)
{
	srand(time(0));
	int lineCount = 0;
	string word;
	vector<string> v;
	ifstream reader(path);
	if (reader.is_open())
	{
		while (!reader.eof()) {
			reader >> word;
			v.push_back(word);
		}

		int randomLine = rand() % v.size();
		word = v.at(randomLine);
		reader.close();
	}
	for (int i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);
	return word;
}

//cout how many tries user still have before game over
int TriesLeft(string word, string guessed)
{
	int error = 0;
	for (int i = 0; i < guessed.length(); i++)
	{
		if (word.find(guessed[i]) == string::npos && guessed.length() > 0)
			error++;
	}
	return error;
}

// print incorrect guessing word and correct guessing word
void printMissesGusses(string guesses, string misses)
{
	cout << "Gusses: ";
	for (int i = 0; i < guesses.length(); i++)
		cout << guesses[i] << " ";
	cout << endl;
	cout << "Misses: ";
	for (int i = 0; i < misses.length(); i++)
		cout << misses[i] << " ";
	cout << endl;
}


bool hangManGame(string wordToGuess)
{
	char x=0;
	string guesses, misses,total_guesses;
	int tries = 0;
	bool win = false;

	do
	{
		system("cls");
		printBoarder();
		printData("HANGMAN");
		printBoarder();
		DrawHangman(tries);
		win = PrintWordAndCheckWin(wordToGuess, total_guesses);
		printMissesGusses(guesses, misses);

		if (win)
			break;

		cout << "Guess a letter: "; cin >> x;
		x = toupper(x);
		
		if (total_guesses.find(x) == string::npos)
			total_guesses += x;
		tries = TriesLeft(wordToGuess, total_guesses);

		if (wordToGuess.find(x) == string::npos)
		{
			if (misses.find(x) == string::npos)
			{
				misses += x;
			}
		}
		else
		{
			if (guesses.find(x) == string::npos)
				guesses += x;
		}

	} while (tries < 6);

	if (win)
	{
		printBoarder();
		printData("YOU WON!");
		printBoarder();
	}
	else {
		system("cls");
		printBoarder();
		printData("HANGMAN");
		printBoarder();
		DrawHangman(tries);
		win = PrintWordAndCheckWin(wordToGuess, total_guesses);
		printMissesGusses(guesses, misses);
		printBoarder();
		printData("GAME OVER");
		printBoarder();
		printData("Answer: " + wordToGuess);
		printBoarder();
	}
	return win;
}

// read userhistory as n input file, store it into a user type list then return 
list<User> readFile(string fileName)
{
	ifstream input(fileName);
	list<User> lt;
	string name, password, winStreak, LastPlay, percent,premimum;
	double winPct;
	int wins, losses;
	string n, p, w, l, wp, ws, lp, pm;
	bool formatting = true;

	if (input.fail())
	{
		cout << "ERROR: UserAccountHistory.txt can not open\n";
		exit(0);

	}

	while (input >> name)	// read file
	{
		if (input.eof())
			break;

		if (formatting) {
			input >> p >> pm >> w >> l >> wp >> ws >> lp;	//format
			formatting = false;
			continue;
		}
		input >> password >> premimum >> wins >> losses >> winPct >> percent >> winStreak >> LastPlay;
		User user(name, password, premimum, wins, losses, winPct, winStreak, LastPlay);
		lt.push_back(user);
	}

	formatting = true;
	input.close();	//close input file

	return lt;
	
}	// end readFile()

// after a user plays a game it requires an update for the useraccount history file, this function does this task.
void updateFile(string fileName, list<User> lt)
{
	ofstream output(fileName);
	list<User>::iterator it;

	output << setw(15) << "Name" << setw(15) << "Password" << setw(15) << "Premimum" << setw(15) << "Wins" << setw(15) << "Losses" << setw(15);
	output << "WinPct" << setw(15) << "WinStreak" << setw(20) << "LastPlay" << endl;

	for (it = lt.begin(); it != lt.end(); it++)
		(*it).writeHistoryToFile(output);
	output.close();	//close file
}


void registerNewAcc(list<User> &lt)                                 // bonus feature   *** register a new user account to play the game 
{
	string userName, userPassword;
	bool userNameDone = false;
	list<User>::iterator it;

	while (!userNameDone) {
		cout << "Please enter your new user name:";
		cin >> userName;
		userNameDone = true;

		for (it = lt.begin(); it != lt.end(); it++)		// check if duplicated user name exist
		{
			if ((*it).getName() == userName)
			{
				cout << "Error: user name (" << userName << ") has already taken by someone else"<< endl;
				cout << "Please create another user name\n";
				userNameDone = false;
				break;
			}
		}
	}

	cout << "Please enter your user password:";
	cin >> userPassword;

	cout << "CONGRADULATION! YOU HAVE FINISHED REGISTERING AN ACCOUNT\n";

	User user(userName, userPassword);
	lt.push_back(user);
}


//after an account logined in, this will be the function display the page and features for a user and return 
// which command the user want to implement 
char userModePage(list<User>::iterator it)
{
	if ((*it).getPremimum() == "YES") {
		printBoarder();
		printData("Hello " + (*it).getName());
		printData("PREMIMUM USER!");
		printBoarder();
		printData("1. Play a game");
		printData("2. Check your history");
		printData("3. To clear or check rank");
		printBoarder();
		cout << "Please select a number to continue, enter 'q' to quit: ";
	}
	else if ((*it).getPremimum() == "NO") {
		printBoarder();
		printData("1. Play a game");
		printData("2. Check your history");
		printData("3. Upgrade to Premimum");
		printBoarder();
		cout << "Please select a number to continue, enter 'q' to quit: ";
	}
	char selection;
	cin >> selection;
	return selection;
}

// this function will implement and display the page and features for an administrator logined in also 
// returns the command the administrator want to perform.
char adminModePage() {
	printBoarder();
		printData("Manage Your Word List");
	printBoarder();
	printData("1. Sort the list aphabetically");
	printData("2 Add a word to the list");
	printData("3. Delete a word from the list");
	printBoarder();
	cout << "Please select a number to continue, enter 'q' to quit: ";
	char selection;
	cin >> selection;
	return selection;
		
}

// this function will implement and display the page and features for all user login in and ask the user
// whether login in as user or administrator or play a new game or register a new account, and return the user choice
char mainPage()
{	
	printBoarder();
	printData("Hangman Game");
	printBoarder();
	printData("ESE224 FALL 2019");
	printBoarder();
	printData("Group Member:");
	printData("WEIWEN LIN");
	printData("JINXING YIN");
	printBoarder();
	printData("1. start a new game");
	printData("2. sign in as user");
	printData("3. register a new account");
	printData("4. sign in as admin");
	printBoarder();
	cout << "Please select a number to continue, enter 'q' to quit: ";
	char selection;
	cin >> selection;
	return selection;
}

//this function show the feature and layout of the condition if an account is an administrator.
void admLogin() {
	int count = 0;
	int count2 = 0;
	ifstream wordfile;
	ofstream n_wordfile;
	list <string> wordlist;
	list<string>::iterator str;
	list<string>::iterator dtr;
	premimum p1;
	string password;
	string word;
	string new_word;
	string delete_word;
	char selection;
	bool login_sucess = false;
	cout << "Please enter the password" << endl;
	cin >> password;
	if (password == "admin12345")
		login_sucess = true;
	else {
		cout << "Invalid Password...";
		return;
	}
	if (login_sucess) {
		system("cls");
		selection = adminModePage();
		wordfile.open("WordList.txt");
		wordfile >> word;
		while (!wordfile.eof()) {
			wordlist.push_back(word);
			wordfile >> word;
		}
		wordfile.close();
		switch (selection) {
		case'1':
			n_wordfile.open("WordList.txt");
			p1.sorting(wordlist, n_wordfile);
			cout << "The list is sorted" << endl;
			n_wordfile.close();
			break;
		case'2':
			n_wordfile.open("WordList.txt");
			cout << "Please input the word you want to add" << endl;
			cin >> new_word;
			for (str = wordlist.begin(); str != wordlist.end(); ++str) {
				if ((*str) == new_word)
					count++;
			}
			if (count == 1) {
				cout << "The word is already existed" << endl;
				n_wordfile.close();
				break;
			}
			else if (count == 0) {
				p1.add(wordlist, new_word, n_wordfile);
				cout << "The word " << new_word << "  is added" << endl;
				n_wordfile.close();
				break;
			}
		case'3':
			n_wordfile.open("WordList.txt");
			cout << "Please input the word you want to delete" << endl;
			cin >> delete_word;
			for (dtr = wordlist.begin(); dtr != wordlist.end(); ++dtr) {
				if ((*dtr) == delete_word)
					count2++;
			}
			if (count2 == 0) {
				cout << "The word does not exist" << endl;
				n_wordfile.close();
				break;
			}
			else if (count2 == 1) {
				p1.remove(wordlist, delete_word, n_wordfile);
				cout << "The word " << delete_word << "  is deleteed" << endl;
				n_wordfile.close();
				break;
			}
		default:
			cout << "Wrong input" << endl;
		}
	}
	return;
	}

// the function show the feature and layout of the condition if an account is an user.
void userLogin()
{
	string fileName = "UserAccountHistory.txt";
	list<User> lt = readFile(fileName);	// read file and store in list
	list<User>::iterator it;
	premimumuser p;
	string userName, userPassword;
	cout << "Please enter the user name:";
	cin >> userName;
	cout << "Please enter the user password:";
	cin >> userPassword;
	bool loginSuccess = true;
	for (it = lt.begin(); it != lt.end(); it++)	// check for name and password
	{
		if ((*it).login(userName, userPassword))	// login successfully                      {??should this be pointer ->}
		{
			loginSuccess = true;
			break;
		}
		loginSuccess = false;
	}

	if (loginSuccess == false)		// fail to login
	{
		cout << "Login fail: User name and password do not match\n";
		return;
	}
	bool not_quit = true;
	char selection;
	string wordToGuess;
	bool win;
	int choose;

	while (not_quit) {
		system("cls");

		selection = userModePage(it);
		switch (selection)
		{
		case '1':
			wordToGuess = LoadRandomWord("WordList.txt");
			win = hangManGame(wordToGuess);
			(*it).updateHistory(win, wordToGuess);
			updateFile(fileName, lt);
			system("pause");
			break;
		case '2':
			(*it).printHistory();
			system("pause");
			break;
		case '3':
			if ((*it).getPremimum() == "NO")
			{
				(*it).upgrade_to_premimum();
				updateFile(fileName, lt);
				cout << "CONGRADULATION! YOU ARE PREMIMUM USER!" << endl;
				cout << "Do you want to clear history pressed 0 or check rank pressed 1" << endl;
				cin >> choose;
				if (choose == 1)
					p.check_rank(lt);
				else if (choose == 0) {
					p.clear_history(userName, lt);
					updateFile(fileName, lt);
				}
				else
					cout << "do nothing as a premimum user" << endl;
			}
			else if ((*it).getPremimum() == "YES")
			{
				cout << "CONGRADULATION! YOU ARE PREMIMUM USER!" << endl;
				cout << "Do you want to clear history pressed 0 or check rank pressed 1" << endl;
				cin >> choose;
				if (choose == 1)
					p.check_rank(lt);
				else if (choose == 0) {
					p.clear_history(userName, lt);
					updateFile(fileName, lt);
				}
				else
					cout << "do nothing as a premimum user" << endl;
			}
			system("PAUSE");
			break;
		default:
			not_quit = false;
		}
	}
	return;
}

// main function call and execute all the above functions 
int main()
{
	bool not_quit = true;
	char selection;
	string fileName = "UserAccountHistory.txt";
	list<User> lt;
	string name;
	Account a;
		
		while (not_quit) {
			system("cls");
			cin.clear();
			selection = mainPage();
		
			switch (selection)
			{
			case '1':                                              //play a game
				hangManGame(LoadRandomWord("WordList.txt"));
				system("pause");
				break;
			case '2':                                              //sign in as a user
				userLogin();
				system("pause");
				break;
			case '3':                                              // register a new account
				lt = readFile(fileName);
				registerNewAcc(lt);
				updateFile(fileName,lt);
				system("pause");
				break;
			case '4':                                               //sign in as an administrator
				admLogin();
				system("pause");
				break;
			default:
				not_quit = false;
				break;
			}
		}
		

		system("pause");
		getchar();
		return 0;

}