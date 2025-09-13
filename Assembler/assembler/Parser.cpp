#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Parser::Parser(const string &filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error opening file " << filename << endl;
    return;
  }

  string line;
  while (getline(file, line))
  {
    size_t pos = line.find("//");
    if (pos != string::npos)
      line = line.substr(0, pos);
    line = trim(line);
    if (!line.empty())
      lines.push_back(line);
  }

  currentLineIndex = 0;
}

string Parser::getCurrentInstruction()
{
  return currentInstruction;
}

string Parser::trim(const string &str)
{
  size_t start = str.find_first_not_of(" \t\r\n");
  if (start == string::npos)
    return "";
  size_t end = str.find_last_not_of(" \t\r\n");
  return str.substr(start, end - start + 1);
}

void Parser::advance()
{
  if (hasMoreCommands())
  {
    currentInstruction = lines[currentLineIndex++];
  }
}

bool Parser::hasMoreCommands()
{
  return currentLineIndex < lines.size();
}

CommandType Parser::commandType()
{
  if (currentInstruction[0] == '@')
  {
    return A_COMMAND;
  }
  else if (currentInstruction.front() == '(' && currentInstruction.back() == ')')
  {
    return L_COMMAND;
  }
  else
  {
    return C_COMMAND;
  }
}

string Parser::symbol()
{
  if (commandType() == A_COMMAND)
  {
    return currentInstruction.substr(1);
  }
  else if (commandType() == L_COMMAND)
  {
    return currentInstruction.substr(1, currentInstruction.size() - 2); // remove '(' and ')'
  }
  return "";
}

string Parser::dest()
{
  size_t eqPos = currentInstruction.find('=');
  if (eqPos != string::npos)
  {

    return currentInstruction.substr(0, eqPos);
  }
  return "";
}

string Parser::jump()
{
  size_t colonPos = currentInstruction.find(';');
  if (colonPos != string::npos)
  {

    return currentInstruction.substr(colonPos + 1);
  }
  return "";
}

string Parser::comp()
{
  size_t eqPos = currentInstruction.find('=');
  size_t semicolonPos = currentInstruction.find(';');

  // Start after '=' otherwise from the beginning
  size_t compStart = (eqPos != string::npos) ? eqPos + 1 : 0;

  // End at ';'  otherwise end of string
  size_t compEnd = (semicolonPos != string::npos) ? semicolonPos : currentInstruction.size();

  return currentInstruction.substr(compStart, compEnd - compStart);
}
