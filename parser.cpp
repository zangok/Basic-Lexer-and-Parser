#include <regex>
#include <iomanip>
#include <vector>
#include "lexer.h" 
using namespace std;

class Node {
    public:
        string info;
        vector<Node *> child;
        Node * parent;
        Node(string a, Node * par) {
            info = a;
            parent = par;
        }
        void addChild(string a) {
            child.push_back(new Node(a,this));
        }
};

int main() {
    string file = "test4.prog";
    lex(file);
    ifstream input("filename");
    string line;
    Node head("start",nullptr);
    Node * ptr = &head;
    
    while(input.peek() != EOF) {
        getline(input,line);
        ptr -> addChild(line);
        if(line == "<error>") {
                cout << "program is incorrect";
                exit(0);
        }
        if(line == "<while>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input, line);
            if(line == "<error>" || input.peek() == EOF) {
                cout << "program is incorrect";
                exit(0);
            }
            while(line != "<do>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || input.peek() == EOF) {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            while(line != "<end>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || input.peek() == EOF) {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            ptr = (*ptr).parent;
        }
        else if(line =="<if>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input, line);
            if(line == "<error>" || input.peek() == EOF) {
                cout << "program is incorrect";
                exit(0);
            }
            while(line != "<then>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || input.peek() == EOF) {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            while(line != "<end>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || (input.peek() == EOF && line != "<end>")) {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            ptr = (*ptr).parent;
        }
        else if(line == "<input>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input, line);
            if(line == "<error>" || (input.peek() == EOF && line != "<end>")) {
                    cout << "program is incorrect";
                    exit(0);
            }
            while(line != "<inputE>") {
                getline(input,line);
                ptr -> addChild(line);
                if(regex_match(line,regex("<[a-z]+>")) || line.substr(0,1) == "\"") {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            ptr = (*ptr).parent;
        }
        else if(line == "<assign>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input, line);
            if(line == "<error>" || (input.peek() == EOF && line != "<end>")) {
                    cout << "program is incorrect";
                    exit(0);
            }
            while(line != "<assignE>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || (input.peek() == EOF && line != "<end>")) {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
            ptr = (*ptr).parent;
        }
        else if(line == "<file>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input, line);
            ptr -> addChild(line);
            if(regex_match(line,regex("<[a-z]+>"))) {
                cout << "program is incorrect";
                exit(0);
            }
            ptr = (*ptr).parent;
        }
        else if (line == "<print>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input,line);
            if(regex_match(line,regex("<error>"))) {
                cout << "program is incorrect";
                exit(0);
            }
            while(line != "<printE>") {
                //cout << line;
                if(line == "<string>") {
                    ptr -> addChild(line);
                    getline(input, line);
                    if(regex_match(line,regex("<error>"))) {
                        cout << "program is incorrect";
                        exit(0);
                    }
                    while(line != "<stringE>") {
                        ptr -> addChild(line);
                        getline(input, line);
                        if(regex_match(line,regex("<error>"))) {
                            cout << "program is incorrect";
                            exit(0);
                        }
                    }
                    ptr = (*ptr).parent;
                }
                getline(input,line);
                ptr -> addChild(line);
                if(line == "print") {
                    cout << "program is incorrect";
                    exit(0);
                }
            }
        }
        else if (line == "<for>") {
            ptr -> addChild(line);
            ptr = (*ptr).child.back();
            getline(input,line);
            if(line == "<error>" || (input.peek() == EOF)) {
                    cout << "program is incorrect";
                    exit(0);
            }
            while(line != "<end>") {
                ptr -> addChild(line);
                getline(input,line);
                if(line == "<error>" || (input.peek() == EOF && line != "<end>")) {
                    cout << "program is incorrect";
                    exit(0);
                }
                
            }
            ptr = (*ptr).parent;
            
        }
        else {
            cout << "Program is incorrect";
            exit(0);
        }
    }
    cout << "Program is correct";
}