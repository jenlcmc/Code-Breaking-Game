#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "mastermindDrive.h"
#include "mainGame.h"
#include <cstdlib>
using namespace std;

void ASCIIart(){
    cout << " ___ ___    ____   _____   ______     ___   ____    ___ ___   ____   ____    ___ \n" <<      
            " |   |   |  /    | / ___/  |      |   /  _] |    |  |   |   | |    | |    |  |   | \n" <<   
            " | _   _ | |  o  (    |_   |      |  /  [_  |  D  ) | _   _ |  |  |  |  _  | |    | \n" <<    
            " |  |_/  | |     | |__  |  |_|  |_| |    _] |    /  |  |_/  |  |  |  |  |  | |  D  | \n" <<   
            " |   |   | |  _  | /  | |    |  |   |   [_  |    |  |   |   |  |  |  |  |  | |     | \n" <<   
            " |   |   | |  |  | |    |    |  |   |     | |  .  | |   |   |  |  |  |  |  | |     | \n" <<   
            " |___|___| |__|__|  |___|    |__|   |_____| |__||_| |___|___| |____| |__|__| |_____| \n" << endl;
}

int main(){
    MastermindLayout* Curr = NULL;
    MastermindLayout* SavedGame = NULL;
    bool end = false;
    char UserChoice;

    do{
        ASCIIart();
        cout << "P/p - play game\n";
        cout << "C/c - continue current game\n";
        cout << "L/l - load current game\n";
        cout << "E/e - exit\n";

        cin >> UserChoice;
        cin.ignore();
        switch(toupper(UserChoice)){
            case 'P':
                setup(Curr, SavedGame);
                play(Curr, SavedGame);
                break;

            case 'C':
                play(Curr, SavedGame);
                break;

            case 'L':
                load(Curr, SavedGame);
                play(Curr, SavedGame);
                break;

            case 'E':
                end = true;
                break;
        
            default:
                cout << "Wrong choice, please enter the choice again '\n";
                break;
        }
    }while(end == false);

    if(Curr != NULL){
        delete Curr;
    }
    if(SavedGame != NULL){
        delete SavedGame;
    }

    cout << endl;
    cout << "Thank you for trying the game. Hope that you enjoy the game \n";

    return 0;
}

void setup(MastermindLayout*& current, MastermindLayout*& saved){
    /*string line, color;
    vector<string> userChoice;
    char YesNo;

    cout << endl;
    cout << "Enter the peg color with 0 at the end \n";
    while(cin >> line){
        while(line.length() <= 1 && userChoice.size() == 0){
            cout << "Sorry! The game need at least 1 pegs color to play. Please enter again \n";
            cin >> line;
        }
        if(line == "0" && userChoice.size() > 0){
            break;
        }
        userChoice.push_back(UpperString(line));
    }*/

    string Color[10] = {"yellow", "green", "blue", "red", "black", "white", "orange", "grey", "brown", "pink"};
    char YesNo;
    vector<string> ColorVec;
    vector<string> userChoice;
    srand(time(NULL));
    int randNum = rand() % 10;

    for(unsigned int i = 0; i < randNum; i++){
        ColorVec.push_back(Color[i]);
    }
    random_shuffle(ColorVec.begin(), ColorVec.end());
    
    userChoice = ColorVec;
    for(int i = 0; i < userChoice.size(); i++){
        cout << userChoice[i] << endl;
    }

    if(current == NULL){
        current = new MastermindLayout(userChoice);
        return;
    }
    if(current != NULL){
        cout << endl;
        cout << "You have a game right now \n";
        cout << "So do you like to save the current game \n"; 
        cout << "Y/y to save and N/n to not save \n";

        cin >> YesNo;
        
        while(toupper(YesNo) != 'Y' || toupper(YesNo) != 'N'){
            if(toupper(YesNo) == 'Y'){
                save(current, saved);
                cout << "Saving current game right now... \n";
            }
            if(toupper(YesNo) == 'N'){
                delete current;
                current = new MastermindLayout(userChoice);
                return;
            }
        }

        if(current != NULL){
            return;
        }else{
            delete current;
            current = new MastermindLayout(userChoice);
        }
    }
}

void save(MastermindLayout*& current, MastermindLayout*& saved){
    if(saved == NULL){
        saved = current;
        current = NULL;
        return;
    }
    if(saved != NULL){
        cout << endl;cout << "Saving current game" << endl;
        cout << "There is a saved game" << endl;
        cout << "This action will destroy/overwrite previously saved game. Is this ok?" << endl;
        
        cout << "Y/y or N/n" << endl;
        char YesNo;
        cin >> YesNo;
        
        while(toupper(YesNo) != 'Y' || toupper(YesNo) != 'N'){
            if(tolower(YesNo) == 'y'){
                delete saved;
                saved = current;
                current = NULL;
            }
            if(tolower(YesNo) == 'n'){
                return;
            }
        }
    }
}

void load(MastermindLayout*& current, MastermindLayout*& saved){
    if(saved == NULL){
        cout << endl;
        cout << "No game to load. \n" << endl;
        return;
    }

    else if(saved != NULL){
        if(current == NULL){
            current = saved;
            saved = NULL;;
            return;
        }
        else{
            cout << endl;
			cout << "This  will destroy current game and cant be undone." << endl;
			cout << "Do you  wish to  continue?" << endl;
            char YesNo;
            cin >> YesNo;

            while(toupper(YesNo) != 'Y' || toupper(YesNo) != 'N'){
                if(tolower(YesNo) == 'y'){
                    cout << "Loading game" << endl;
                    delete current;
                    current = saved;
                    saved = NULL;
                }
                if(tolower(YesNo) == 'n'){
                    return;
                }
            }
        }
    }
}

void play(MastermindLayout*& current, MastermindLayout*& saved){
    vector<string> UserChoice;
    string guess;
    string newGuess;
    int gold = 0;
    int silver = 0;
    int UserMove = 0;
    bool stop = false;
    
    while(UserMove == 0){
        if(current == NULL){
            cout << endl;
            cout << "No current game" << endl;
            return;
        }
        else{
            cout << endl;
            cout << "turn " << current->GetIndexOfMove()
                << ": Enter " << current->GetColumns()
                << " Color or (S)top:" << endl;

            for(int i = 0; i < current->GetColumns(); i++){
                cin >> guess;

                if(guess == "S" || guess == "s"){
                    stop = true;
                    break;
                }else{
                    for(unsigned int i = 0; i < guess.length(); i++){
                        newGuess += toupper(guess[i]);
                    }
                    UserChoice.push_back(newGuess);
                }
            }
            cin.ignore(100, '\n');

            if(stop){
                char YesNo;
                cout << "Do you want to save the game?" << endl;
                cout << "Y/y or N/n" << endl;
                cin >> YesNo;


                while(toupper(YesNo) != 'Y' || toupper(YesNo) != 'N'){
                    if(tolower(YesNo) == 'y'){
                        cout << "Saving game" << endl;
                        save(current, saved);
                        return;
                    }
                    if(tolower(YesNo) == 'n'){
                        cout << "You can return to the game later" << endl;
                        return;
                    }
                }
            }else{
                if(static_cast<int> (UserChoice.size()) == current->GetColumns()){
                    UserMove = current->MovePegs(UserChoice, gold, silver);
                    cout << "Current gold pegs: " << gold << endl;
                    cout << "Current silver pegs: " << silver << endl;
                    UserChoice.clear();
                }
            }
        }
    }

    if(UserMove == 1 || UserMove == -1){
        if(UserMove == 1){
            cout << "Congratulations, you won" << endl;
            cout << "delete the current game" << endl;
            cout << "Game solution: " << endl;
            current->getSolution();
            delete current;
            current = NULL;;
            return;
        }else{
            cout << "Sorry, you lose" << endl;
            cout << "Delete the game" << endl;
            cout << "Game solution: " << endl;
            current->getSolution();
            delete current;
            current = NULL;
            return;
        }
    }
    else if(UserMove == 2){
        return;
    }
}