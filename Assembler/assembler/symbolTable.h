#include <unordered_map>
#include <string>
using namespace std;

class SymbolTable
{
private:
  unordered_map<string, int> table;

public:
  SymbolTable()
  {
    // Predefined symbols
    for (int i = 0; i <= 15; i++)
      table["R" + to_string(i)] = i;
    table["SP"] = 0;
    table["LCL"] = 1;
    table["ARG"] = 2;
    table["THIS"] = 3;
    table["THAT"] = 4;
    table["SCREEN"] = 16384;
    table["KBD"] = 24576;
  }

  void addEntry(const string &symbol, int address)
  {
    table[symbol] = address;
  }

  bool contains(const string &symbol)
  {
    return table.find(symbol) != table.end();
  }

  int getAddress(const string &symbol)
  {
    return table[symbol];
  }
};