#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include "lexer.h"

using namespace std;
bool isInt(string input) {
    if(regex_match(input, regex("(\\+|-)?[0-9]+" )))
        return true;
    return false;
}

bool isID(string input) {
    if(regex_match(input, regex("[_a-zA-Z][_a-zA-Z0-9]*" )))
        return true;
    return false;
}

bool isString(string input) { //might not work
    if(regex_match(input, regex("\"([^\"]|\")*\"" )))
        return true;
    return false;
}
//void evalExpr(string input, ofstream & output, stringstream & s);
void evalVal(string input, ofstream & output, stringstream & s) { //true means continue, false means done
    string lexeme = input;
    //if(lexeme == "")
    //    s >> lexeme;
    if(lexeme == "(")
    {
        output << "<lb>\n";
        s >> lexeme;
        evalExpr(lexeme, output, s);
        output << "<rb>\n";
    }
    else if(lexeme == "not")
    {
        output << "<not>\n";
        s >> lexeme;
        evalVal(lexeme, output, s);
    }
    else if(lexeme == "-")
    {
        output << "<->\n";
        s >> lexeme;
        evalVal(lexeme, output, s);
    }
    else if(isInt(lexeme)) {
        output << "<int>\n" << lexeme << "\n";
    }
    else if(isID(lexeme)) {
        output << "<id>\n" << lexeme << "\n";
    }
    else if (lexeme != ")") {
        output << "<error>\n" << lexeme<< "\n";
    }
    //output << lexeme;
}

void evalExpr(string input, ofstream & output, stringstream & s) {
    string lexeme = input;
    if(lexeme == "")
        s >> lexeme;
    //output << "<expr>\n";
    evalVal(lexeme, output, s);
    while (s.peek() != EOF) {
        s >> lexeme;
        if(lexeme == ">" || lexeme == ">=" || lexeme == "<" || lexeme == "<=" || lexeme == "==" || lexeme == "!=") {
            output << "<compare>\n" << lexeme << "\n";
            s >> lexeme;
            evalVal(lexeme, output, s);  
        } 
        else if(lexeme == "*") {
            output << "<mult>\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "/") {
            output << "<div>\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "%") {
            output << "<mod>\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "+") {
            output << "<add>\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "-") {
            output << "<min>\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "and") {
            output << "<and>\n" << lexeme << "\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else if(lexeme == "or") {
            output << "<or>\n" << lexeme << "\n";
            s >> lexeme;
            evalVal(lexeme, output, s); 
        }
        else {
            output << "<error>\n" <<lexeme <<"\n";
        }
    } 
    //output << "<exprE>\n";
}
void lex(string input1) {
    ofstream output("filename");
    ifstream input(input1);
    string line;
    int f = 0;
    while(input.peek() != EOF)
    {
        getline(input, line);
        if(line.find_first_not_of(" ") != string::npos)
            line = line.substr(line.find_first_not_of(" "));
        stringstream s(line);
        string lexeme;
        s >> lexeme;
        if(lexeme == "if") {
            output << "<if>\n";
            f += 1001;
            s >> lexeme;
            evalExpr(lexeme, output, s);
            output << "<then>\n";
        } 
        else if(lexeme == "get") {
            s >> lexeme;
            output << "<input>\n" << lexeme <<"\n";
            while( s >> lexeme)
                output << lexeme << "\n";
            output << "<inputE>\n";
        }
        else if(lexeme == "print") {
            output << "<print>\n";
            s >> lexeme;
            if(isString(s.str().substr(s.str().find(" ")+1))) {
                output << "<string>\n";
                char temp;
                s.get(temp);
                while(s.get(temp)) {
                    if(temp == '\\') {
                        s.get(temp);
                        if(temp == '\\')
                            output << "\\";
                        else if(temp == 'n')
                            output << "\n";
                        else if(temp == 't')
                            output << "\t";
                        else if(temp == '\"')
                            output << "\"";
                    }
                    else if(temp == '\"') {
                        output << "\n<stringE>\n";
                    }
                    else {
                        output << temp;
                    }
                }
                output << "<printE>\n";

            }
            else {
                //s >> lexeme;
                evalExpr(lexeme, output, s);
                output << "<printE>\n";
            }
        }
        else if(lexeme == "while") {
            output << "<while>\n";
            f++;
            s >> lexeme;
            evalExpr(lexeme, output, s);
            output << "<do>\n";
        }
        else if(lexeme == "for") {
            output << "<for>\n";
            f++;
            s >> lexeme;
            isInt(lexeme);
        }
        else if(lexeme == "else") {
            f = f-1000;
            output << "<else>\n";
        }
        else if(lexeme == "end") {
            f = f-1;
            output << "<end>\n";
        }
        else if(lexeme == "exit") {
            output << "<exit>\n";
        }
        else if(lexeme == "file") {
            output << "<file>\n";
            if(isString(s.str().substr(s.str().find(" ")+1))){
                char temp;
                s.get(temp);
                while(s.get(temp)) {
                    if(temp == '\\') {
                        s.get(temp);
                        if(temp == '\\')
                            output << "\\";
                        else if(temp == 'n')
                            output << "\n";
                        else if(temp == 't')
                            output << "\t";
                        else if(temp == '\"')
                            output << "\"";
                    }
                    else if(temp == '\"') {
                        
                    }
                    else {
                        output << temp;
                    }
                }
            }
            else
                output << "<error>\n" << lexeme;
            output << "\n";
        }
        else if(isID(lexeme)){
            output << "<assign>\n" << lexeme << "\n";
            s >> lexeme;
            if( lexeme == "=")
            {
                if(s.peek() == EOF) {
                    output << "<error>\n";
                }
                while(s >> lexeme)
                    evalExpr(lexeme,output,s);
            }
            else 
                output << "<error>\n= expected\n";
            output << "<assignE>\n";
        }
        else if (lexeme.find_first_not_of(' ') != string::npos){
            output << "<error>\n" << lexeme;

        }
    }
    if(f!=0)
        output << "<error>\nmissing/excessive end & else above\n";
}