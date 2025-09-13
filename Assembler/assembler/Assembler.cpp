#include <iostream>
#include <fstream>
#include <bitset>
#include "Parser.h"
#include "codeModule.h"
#include "symbolTable.h"
using namespace std;

string toBinary16(int value)
{

  return bitset<16>(value).to_string();
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: Assembler <inputfile.asm>" << endl;
    return 1;
  }

  string inputFile = argv[1];

  // Derive output file name
  size_t dotPos = inputFile.find_last_of(".");
  string outputFile = (dotPos == string::npos) ? inputFile + ".hack" : inputFile.substr(0, dotPos) + ".hack";

  // file setup and intialization
  Parser parser(inputFile);
  ofstream out(outputFile);
  // file opening error
  if (!out.is_open())
  {
    cerr << "Error opening output file " << outputFile << endl;
    return 1;
  }

  // pass 1: find symbols
  SymbolTable symbols;
  int romAddress = 0;

  while (parser.hasMoreCommands())
  {
    parser.advance();
    if (parser.commandType() == L_COMMAND)
    {
      symbols.addEntry(parser.symbol(), romAddress);
    }
    else
    {
      romAddress++;
    }
  }

  int nextVariableAddress = 16;

  Parser parser2(inputFile);

  while (parser2.hasMoreCommands())
  {
    parser2.advance();

    if (parser2.commandType() == A_COMMAND)
    {
      string sym = parser2.symbol();
      int address;
      if (isdigit(sym[0]))
      {
        address = stoi(sym);
      }
      else
      {
        if (!symbols.contains(sym))
        {
          symbols.addEntry(sym, nextVariableAddress++);
        }
        address = symbols.getAddress(sym);
      }
      out << toBinary16(address) << "\n";
    }
    else if (parser2.commandType() == C_COMMAND)
    {
      string destBits = Code::dest(parser2.dest());
      string compBits = Code::comp(parser2.comp());
      string jumpBits = Code::jump(parser2.jump());

      string instruction = "111" + compBits + destBits + jumpBits;
      out << instruction << "\n";
    }
  }

  out.close();
  cout << "Assembly complete. Output written to " << outputFile << endl;
  return 0;
}