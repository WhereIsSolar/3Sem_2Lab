#include "Stack.h"
#include <iostream>
#include <string>
#include <sstream>

const string DATA_FILE = "stack.txt";

static Stack stackInstance;

void printStack(Stack &s) {
    for (int i = 0; i < s.size; ++i) {
        cout << s.data[i];
        if (i + 1 < s.size) cout << " ";
    }
    cout << endl;
}

int Solver(const string line, Stack& stck) {
  for (const char symbol: line) {
    if (isdigit(symbol)) {
      Push(stck, symbol);
    } else if (symbol == '*' or symbol == '+' or symbol == '-' or symbol == '/') {
      // cout << "\n";
      // printStack(stck);
      // cout << "\n";
      
      string op1;
      string result_str1 = Pop(stck, op1);
      char result_char1 = result_str1[0];

      string op2;
      string result_str2 = Pop(stck, op2);
      char result_char2 = result_str2[0];
      // cout << "DEBUG" << op1 << op2 << endl;
      
      int operand1 = stoi(op1);
      int operand2 = stoi(op2);
      if (symbol == '+'){
        Push(stck, to_string(operand2 + operand1));
      } else if (symbol == '*') {
        Push(stck, to_string(operand2 * operand1));
      }   else if (symbol == '-') {
        Push(stck, to_string(operand2 - operand1));
      }  else if (symbol == '/') {
        Push(stck, to_string(operand2 / operand1));
      }
      
   }
  };
    return -1;
}

int main() {
    cout << "RPN solver.\n Input your linear equalention\n >>>" << endl;
    string line;
    initStack(stackInstance);
    while (cin >> line) {
      if (line == "EXIT")
        break;
      else if (isdigit(line[0])) {
	Solver(line, stackInstance);
        cout << "Result:" << endl;
	string val;
	Pop(stackInstance, val);
      }
        // if (!line.empty()) Solver(line);
    }
    clearStack(stackInstance);
    return 0;
}
