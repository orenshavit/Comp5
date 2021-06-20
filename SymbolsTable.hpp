#pragma once

#include <stack>
#include <string>
#include <list>
#include <vector>
#include <memory>
using namespace std;

class FuncTypes {
    public:
    string ret_type;
    vector<string> arg_types;
    FuncTypes() = default;
    FuncTypes(string ret_type, vector<string> arg_types);
};

class FunctionDecl {
public:
    string id;
    string ret_type;
    vector<string> arg_types;
    vector<string> arg_names;
    FunctionDecl() : id(""), ret_type(""), arg_types(vector<string>()), arg_names(vector<string>()) {}
};

class TableEntry {
public:
    string id;
    int offset;
    string type;
    TableEntry(string id, int offset, string type);
};

class SymbolsTable
{
    SymbolsTable* parent;
public:
    list<TableEntry*> entries;
    SymbolsTable(SymbolsTable* parent);
    TableEntry* insert(string id, int offset, string type);
    void print_ids();
};














