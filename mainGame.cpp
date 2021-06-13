#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <random>
#include "mastermindDrive.h"
#include "mainGame.h"
using namespace std;


int main(){
	MastermindLayout * CurrentPlay = nullptr;
	MastermindLayout * OldGame = nullptr;
	char UserChoice;
	bool endGame = false;

	do{
		cout << endl;
        asciiArt();
		cout << "p/P - play game \n"
            << "l/L - load game \n"
            << "c/C - continue game \n"
            << "q/Q - quit game \n \n"
			<< "The game will have combination of 5 colors: yellow, blue, green, red, white. \n"
			<< "In addition, there will be random combination that will have duplicate colors \n"
			<< "You will have 6 chances to guess \n" << endl;

		cin >> UserChoice;
		cin.ignore(); //extra to prevent skipping
		switch (toupper(UserChoice))
		{
			case 'P':
				setup(CurrentPlay, OldGame);
				play(CurrentPlay, OldGame);
				break;

			case 'C':
				play(CurrentPlay, OldGame);
				break;

            case 'L': 
				load(CurrentPlay, OldGame);
				play(CurrentPlay, OldGame);
				break;

			case 'Q':
				endGame = true;
				break;

			default:
				cout << "Wrong option. Choose again" << endl;
				break;
		}
	}while(!endGame);

	//deallocate the objects if any are still left after
	//user decides to quit
	if (CurrentPlay != nullptr)
		delete CurrentPlay;

	if (OldGame != nullptr)
		delete OldGame;

	cout << endl;
	cout << "Thank you for trying. Hope you like the game" << endl;

	return 0;
}

/*setup - this function creates a new game

	MastermindLayout*& CurrentPlay - points to a MastermindLayout object of the current game in play
	MastermindLayout*& OldGame - points toaMastermindLayoutobject of a saved game.
	return void

	Algorithm - using while loop to take user input and only break if user input is = and player size > 0.
	If user input is 0 and less size == 0, then output messages and repromp the user until they enter correct format.
	After that, pushback user input into vector. Check to see if CurrentPlay is nullptr or not. 
	If there is a current game in progress, ask the user if they wish to save the game using yes/no function, 
	if they wish to save the game call the save function 
	if the save function did not actually save the game then exit the setup function, 
	otherwise Allocate a new game to CurrentPlay pointer by passing the vector  to the constructor and return
	If there is a current game in progress, and the user does not want to save the game, 
	deallocatethe CurrentPlay and Allocate a new game to CurrentPlay pointer by passing the vector  to the constructor .  
	Allocate a new game to CurrentPlay pointer by passing the vector  to the constructor

*/

void setup(MastermindLayout*& CurrentPlay, MastermindLayout*& OldGame){
    string Color[12] = {"yellow", "green", "blue", "red", "red", "blue", "green", "yellow", "white", "white", "pink", "pink"};
    char YesNo;
    vector<string> ColorVec;
    vector<string> UserChoice;
    srand(time(NULL));
    int randNum = (rand() % 5) + 1;

    for(size_t i = 0; i < randNum; i++){
        ColorVec.push_back(Color[i]);
    }
    auto seed = default_random_engine();
    shuffle(begin(ColorVec), end(ColorVec), seed);
    
    UserChoice = ColorVec;

	if(CurrentPlay == nullptr){
		CurrentPlay = new MastermindLayout(UserChoice); 
		return;
		
	}else{
		cout << endl;
		cout << "One game in progress" << endl;
		cout << "Would you like to save this game?" << endl;

		if (yesOrNo("(Y/N): ")){
			save(CurrentPlay, OldGame); 
			cout << "Saving current game..." << endl;
		}else{
			delete CurrentPlay;
			CurrentPlay = new MastermindLayout(UserChoice);
			return;
		}

		if(CurrentPlay != nullptr){ // to check if the save function actually work or not
			//saved game rn will have address of previous current
			return;
		}else{
			delete CurrentPlay;
			CurrentPlay = new MastermindLayout(UserChoice);
		}
	}
}

/*save - this function saves a current game
	MastermindLayout*& CurrentPlay - points to a MastermindLayout object of the current game in play
	MastermindLayout*& OldGame - points toaMastermindLayoutobject of a saved game.
	return void

	Algorithm - If there is no saved game, set save to CurrentPlay and assign CurrentPlay to nullptr and exit function
	If there is a saved game, ask the user if they still want to save over the OldGame using yes/no function
	if they want to save over, deallocate OldGame and set it to CurrentPlay, then set CurrentPlay to nullptr
	If the user does not want to save the game then do nothing and exit from the function

*/

void save(MastermindLayout*& CurrentPlay, MastermindLayout*& OldGame){
	if(OldGame == nullptr){
		OldGame = CurrentPlay;
		CurrentPlay = nullptr;
		// if nullptr then we will save it and not nullptr, we will override the previous game
		return;
	}else{
		cout << endl;
		cout << "Saving this game..." << endl;
		cout << "There is a saved game in data" << endl;
		cout << "This will destroy/overwrite old game. Do you want to continue?" << endl;

		if (yesOrNo("(Y/N): ")){
			delete OldGame;
			OldGame = CurrentPlay;
			CurrentPlay = nullptr;
		}else{
			return;
		}
	}
}


/*save - this function load a current game and save game
	MastermindLayout*& CurrentPlay - points to a MastermindLayout object of the current game in play
	MastermindLayout*& OldGame - points toaMastermindLayoutobject of a saved game.
	return void

	Algorithm - If there is no saved game, exit out of the function
	If there is a current game, ask the user if they wish to destroy this game with yes/no function
	If they do, destroy the game and Set current game with the game in saved game and set saved game to nullptr
	If they do not wish to destroy the current game, then exit the function

*/
void load(MastermindLayout*& CurrentPlay, MastermindLayout*& OldGame)
{

	if(OldGame == nullptr){
		cout << endl;
		cout << "There is no game to load. Unable to complete the task. \n" << endl;
		return;
	}else{ 
		if(CurrentPlay == nullptr){
			CurrentPlay = OldGame;
			OldGame = nullptr;
			return; 
		}else{
			cout << endl;
			cout << "This will destroy this game." << endl;
			cout << "This can't be undo." << endl;
			cout << "Are you sure you want to continue?" << endl;

			if (yesOrNo("(Y/N): ")){
				cout << "Loading game..." << endl;
				delete CurrentPlay;
				CurrentPlay = OldGame;
				OldGame = nullptr; 
			}else{
				return;
			}
		}
	}
}


/*yesOrNo- all this function does prompt the user by outputting msg and re-prompts if the user does not enter Y/y or N/n, 
	string msg - user input
	returns true if the user entered Y/y and returns false if they entered N/n.

	Algorithm - this function is written by professor

*/
bool yesOrNo(string msg)
{
	char UserChoice;

	cout << endl;

	do
	{
		cout << msg;
		cin >> UserChoice;
		UserChoice = toupper(UserChoice);
	}
	while (UserChoice != 'Y' && UserChoice != 'N');

	return UserChoice == 'Y';
}

/*play- user interact to play the game
	MastermindLayout*& CurrentPlay - points to a MastermindLayout object of the current game in play
	MastermindLayout*& OldGame - points toaMastermindLayoutobject of a saved game.
	return void

	Algorithm- using outer while loop to continue loop if the playermove that take return value from move() == 0
	Inside while loop, check if CurrentPlay is nullptr or not. If nullptr, output error, and return. Otherwise, prompt the user
	using getMOveIndex() and getNumberOfColumn. Then using for loop to loop through solution size and get user input.
	If user input is p/P then flag and break. Otherwise, push input into vector.
	Outside the for loop, if flag then ask user if they want to save the game or not. If yes, save game by save() and return
	If no, return and do nothing to current and saved game. 
	If not flag, check to see if vector is equal solution size or not. If yes, get return value from move() 
	and output goldPegs and siver. Then clear the vector
	-If playermove is 1 = user win, output messange, delete CurrentPlay, set CurrentPlay to nullptr and return
	-If playerMove is -1 = user lose, output messange, delete CurrentPlay, set CurrentPlay to nullptr and return
	-If playerMove is 2 then return;

*/

void play(MastermindLayout*& CurrentPlay, MastermindLayout*& OldGame)
{
	vector <string> UserChoice;
	string UserGuess;
	int goldPegs = 0;
	int silverPegs = 0;
	int UserMoves = 0;
	int Score;
	bool stop = false;

	while(UserMoves == 0){
		if(CurrentPlay == nullptr){
			cout << endl;
			cout << "No current game found" << endl;
			return;
		}
		else if(CurrentPlay != nullptr){
			cout << endl;
			cout << "Turn " << CurrentPlay->GetIndexOfMove()  
				<< ": Enter " << CurrentPlay->GetColumns()
				<< " color or (S)top:" << endl;

			for(int i = 0; i < CurrentPlay->GetColumns(); i++){
				//cin.clear();
				cin >> UserGuess; 
				UserGuess = ConvertString(UserGuess);
				//cin.ignore(80,'\n');

				if(UserGuess == "s" || UserGuess == "S"){
					stop = true;
					break;
				}else{
					UserChoice.push_back(UpperString(UserGuess));
					
				}
			}
			cin.ignore(100,'\n');

			for(auto i : UserChoice){
				cout << "User Guess: " << i << endl;
			}

			if(stop == true){
				cout << "Let take a break and try again" << endl;
				cout << "Do you want to save this game?" << endl;
				if (yesOrNo("(Y/N): ")){
					cout << "Saving this game..." << endl;
					save(CurrentPlay, OldGame);
					return;
				}
				else{
					cout << "Don't worry, you alway can resume and try again when you want" << endl;
					return;
				}
			}
			else{
				if(static_cast <int> (UserChoice.size()) == CurrentPlay->GetColumns()){
					UserMoves = CurrentPlay->MovePegs(UserChoice, goldPegs, silverPegs);
					cout << "goldPegs pegs: " <<  goldPegs << endl;
					cout << "silverPegs pegs: " << silverPegs << endl; 
					UserChoice.clear();
				}
			}
		}
	}
		if(UserMoves == 1 || UserMoves == -1){
			if(UserMoves == 1){
				Score = 1;
				cout << endl << "Congratulation. You won! :)" << endl;
				cout << "Destroying this game \n" << endl;
                cout << "Here is the game solution: " << endl;

                CurrentPlay->getSolution();
				cout << endl;
				CurrentPlay->ScoreTracking(Score);
				
				delete CurrentPlay;
				CurrentPlay = nullptr;
				return;
			}
			else{
				Score = 2;
				cout << endl << "Sorry. You lose! :(" << endl;
				cout << "Destroying game \n" << endl;
                cout << "Here is the game solution: " << endl;

                CurrentPlay->getSolution();
				cout << endl;
				CurrentPlay->ScoreTracking(Score);

				delete CurrentPlay;
				CurrentPlay = nullptr;
				return;
			}
		}
		else if(UserMoves == 2){ 
			return;
		}
}

/*UpperString - format string to uppercase
	string s- user input string
	return upper string value

	Algorithm- using for loop to loop through the string and then user another var to hold uppercase of the string
	After that, return the uppercase value
*/

string UpperString(string input){
	string value;
    for(size_t i = 0; i < input.length(); i++){
        value += toupper(input[i]);
    }
    return value;
    
}

void asciiArt(){
    cout << ".___  ___.      ___           _______.___________. _______ .______      .___  ___.  __  .__   __.  _______ \n "  
         << "|   ||   |     /   |         /       |           ||   ____||   _  |    |   ||   | |  | |  | |  | |       | \n"
         << "|  |  /  |    /  ^  |       |   (----`---|  |----`|  |__   |  |_)  |    |  |  /  | |  | |   ||  | |  .--.  | \n"
         << "|  ||||  |   /  /_|  |       |   |       |  |     |   __|  |      /     |  ||||  | |  | |  . `  | |  |  |  | \n"
         << "|  |  |  |  /  _____  |  .----)   |      |  |     |  |____ |  |  |----.|  |  |  | |  | |  ||   | |  '--'  | \n"
         << "|__|  |__| /__/     |__| |_______/       |__|     |_______|| _| `._____||__|  |__| |__| |__| |__| |_______/ \n" << endl;
}

string ConvertString(string guess){
	if(guess == "r"){
		guess = "red";
	}else if(guess == "b"){
		guess = "blue";
	}else if(guess == "w"){
		guess = "white";
	}else if(guess == "g"){
		guess = "green";
	}else if(guess == "y"){
		guess = "yellow";
	}else if(guess == "p"){
		guess = "pink";
	}
	return guess;
}