#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

bool isInt(string input);
bool isID(string input);
bool isString(string input);
void evalVal(string input, ofstream & output, stringstream & s);
void evalExpr(string input, ofstream & output, stringstream & s);
void lex(string input1);

#endif