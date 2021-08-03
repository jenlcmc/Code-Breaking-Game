#include "mastermindDrive.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*MastermindLayout - constructor that sets the size of solution vector and assignseach element to contain"red", 
    Algorithm - assign color to default color red and maxmoves to 5, moves to 0
*/

MastermindLayout::MastermindLayout(int size) : GameSolution(size)
{
    string defaultColor = "white";
    MaxMoves = 6;
    GameMove = 0;

    for(auto i : GameSolution){
        GameSolution.push_back(defaultColor);
    }
}

/*MastermindLayout - constructor that sets the solution vector with the content of UserGame vector (insensitive way)
    Algorithm - using nested for loop to to convert the vector of string UserGame to all uppercase and then put them in solution
    vec using push_back(). Also, assign maxMoves to 5 and moves to 0

*/
MastermindLayout::MastermindLayout(vector<string> UserGame)
{
    for(size_t i = 0; i < UserGame.size(); i++){
        string temp = UserGame[i];
        string convert;
        for(size_t j = 0; j < temp.length(); j++){
            convert += toupper(temp[j]);
        }
        GameSolution.push_back(convert);
    }

    MaxMoves = 6;
    GameMove = 0;
}

/*move - this function simulates one move/round of the MastermindLayout game. 
    Algorithm - using nested loop to loop through solution and player vector. Then determine the gold value by compare
    2 vectors and mark it using bool. Then inside the nested loop, determine for silver, increment silver 1st
    and then check if vector of playermove in outerloop same with insideloop or not and 
    then check if it's already have mark or not. If it's the same and have mark, then subtract the silver value and break from the loop
    After nested loop, increment move. Return value based on above conditions
*/
int MastermindLayout::MovePegs(vector<string> playerMove, int& gold, int& silver) 
{
    gold = silver = 0;
    bool havePeg = false;

    for(size_t i = 0; i < GameSolution.size(); i++){
        if(playerMove[i] == GameSolution[i]){
            gold++;
            havePeg = true;
        }
        for(size_t j = 0; j < playerMove.size(); j++){
            if(playerMove[j] == GameSolution[i] && i != j){
                silver++;
                if(playerMove[i] == playerMove[j] && havePeg){
                    silver--;
                    break;
                }
            }
        }
    }
    GameMove++;
    
    if(static_cast<size_t>(gold) == GameSolution.size()){
        return 1;
    }
    else if(GameMove >= MaxMoves){
        return -1;
    }
    else if(GameMove <= MaxMoves){
        return 0;
    }
    return 3;
    if(playerMove.size() != GameSolution.size()){ 
        return 2;
    }
}

/*getSolution - get game solution
    Algorithm - take colors from vector and cout 
*/
void MastermindLayout::getSolution(){
    for(auto i : GameSolution){
        cout << i << " " << endl;
    }
}

/*getMoveIndex - get move index
    Algorithm - return move +1 cause UserGame is 0
*/
int MastermindLayout::GetIndexOfMove() const
{
    return(GameMove + 1);
}

/*getMoveIndex - get solution size/ columns numbers
    Algorithm - return solution size
*/
int MastermindLayout::GetColumns() const
{   
    return(GameSolution.size()); 
}
