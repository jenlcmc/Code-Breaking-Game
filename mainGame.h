#pragma once
#include "mastermindDrive.h"

void setup(MastermindLayout*&, MastermindLayout*&);
void load(MastermindLayout*&, MastermindLayout*&);
void save(MastermindLayout*&, MastermindLayout*&);
void play(MastermindLayout*&, MastermindLayout*&);
string UpperString(string);
void asciiArt();
bool yesOrNo(string msg);
string ConvertString(string);
void ScoreTracking(bool);