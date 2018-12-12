#pragma once


#define Angstrom -1
#define one_bar -2
#define two_bar -3
#define noadv false

void openfont(char* f);

void closefont();

void JGN_StrokeCharacter(char c, bool hadv = true);
void JGN_StrokeString(char* s, int maxchar = 100000);