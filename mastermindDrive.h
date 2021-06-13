#pragma once
#include <vector>
#include <string>
using namespace std;

class MastermindLayout{
    public:
        MastermindLayout(int);
        MastermindLayout(vector<string>);
        int MovePegs(vector<string>, int&, int&);
        int GetIndexOfMove() const;
        int GetColumns() const;
        void getSolution();
        void ScoreTracking(int&);

    private:
        int MaxMoves;
        vector<string> GameSolution;
        int GameMove;
        int UserScore;
        int MachineScore;
};