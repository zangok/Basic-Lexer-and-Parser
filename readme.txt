lexer.cpp is is the lexer
lexer has a function "lex(string input)" where input is the program name to be put through the lexer
filename is lexer output, do not delete.
to test, the lexer int main has a function call to lex, change to any program name.
test3 and test4 are the tests that I've edited to fit the syntax of my lexer.
I removed some information that would be outputted that I believe would be redundant for the compiler to shorten the output file.
For instance, before I had
<input>
<ID>
x
but an ID was always after every input, so I instead, I have
<input>
x

Project Part 2:
In parser.cpp,
string file = "test4.prog";
under int main determines what file is being used. 
test3.prog has been edited to not work, while test4.prog does.
if you modify a file, make sure you modify the file in string file / change the file listed.

parser.cpp is the parser and has an include for lexer.h, lexer.cpp is the parser and has an include for lexer.h
VS code was acting up for me, so personally, I used 
https://www.onlinegdb.com/online_c++_compiler#
Uploaded all the files except parser.cpp, and replaced the main file they provided with parser.cpp
