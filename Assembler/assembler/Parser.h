#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <vector>

enum CommandType
{
  A_COMMAND,
  C_COMMAND,
  L_COMMAND
};

class Parser
{
private:
  vector<string> lines;
  size_t currentLineIndex = 0;
  ifstream inputFile;
  string currentInstruction;
  string trim(const string &str);

public:
  Parser(const string &filename);

    bool hasMoreCommands();

  void advance();

  string getCurrentInstruction();

  CommandType commandType();

  string symbol();
  string dest();
  string comp();
  string jump();
};
