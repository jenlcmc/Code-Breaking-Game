#include "mastermindDrive.h"
#include <iostream>

MastermindLayout::MastermindLayout(int size) : GameSolution(size){
    string defaultColor = "white";
    MaxMoves = 6;
    GameMove = 0;

    for(double i = 0; i < GameSolution.size(); i++){
        GameSolution.push_back(defaultColor);
    }
}

MastermindLayout::MastermindLayout(vector<string> Color){
    string tempColor;
    string convert;
    for(unsigned int i = 0; i < Color.size(); i++){
        tempColor = Color[i];
        for(unsigned int j = 0; j < tempColor.length(); j++){
            convert += toupper(tempColor[j]);
        }
        GameSolution.push_back((convert));
    }

    MaxMoves = 6;
    GameMove = 0;
}

int MastermindLayout::MovePegs(vector<string> playerMoves, int& goldPegs, int& silverPegs){
    goldPegs = 0;
    silverPegs = 0;
    bool havePegs = false;

    for(unsigned int i = 0; i < GameSolution.size(); i++){
        if(playerMoves[i] == GameSolution[i]){
            ++goldPegs;
            havePegs = true;
        }
        for(unsigned int j = 0; j < playerMoves.size(); j++){
            if(playerMoves[j] == GameSolution[i] && i != j){
                ++silverPegs;
                if(playerMoves[i] == playerMoves[j] && havePegs == true){
                    silverPegs--;
                    break;
                }
            }
        }
    }
    ++GameMove;

    if(playerMoves.size() != GameSolution.size()){ //error case = 0
        return 2;
    }
    if(static_cast<unsigned int>(goldPegs) == GameSolution.size()){ //win case = 1
        return 1;
    }
    else if(GameMove >= MaxMoves){ //lose case
        return -1;
    }
    else if(GameMove <= MaxMoves){ //not over case
        return 0;
    }
    return 3;
}

int MastermindLayout::GetColumns() const{
    return(GameSolution.size());
}

int MastermindLayout::GetIndexOfMove() const{
    return(GameMove + 1);
}

void MastermindLayout::getSolution(){
    for(int i = 0; i < GameSolution.size(); i++){
        cout << GameSolution[i] << endl;
    }
}