#ifndef CODEMODULE_H
#define CODEMODULE_H

#include <string>
#include <unordered_map>
using namespace std;

class Code
{
public:
  static string dest(const string &mnemonic);
  static string comp(const string &mnemonic);
  static string jump(const string &mnemonic);
};

#endif