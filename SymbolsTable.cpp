#include "SymbolsTable.hpp"
#include "output.hpp"
// #include <stdlib.h>
#include <iostream>


FuncTypes::FuncTypes(string ret_type, vector<string> arg_types) : ret_type(ret_type), arg_types(arg_types) {}

TableEntry::TableEntry(string id, int offset, string type) : id(id) , offset(offset), type(type) {}


SymbolsTable::SymbolsTable(SymbolsTable* parent) : parent(parent) {}

TableEntry* SymbolsTable::insert(string id, int offset, string type) {
    TableEntry* entry = new TableEntry(id, offset, type);
    entries.push_back(entry);
    return entry;

}

void SymbolsTable::print_ids() {
    for (auto entry : entries) {
        output::printID(entry->id, entry->offset, entry->type);
    }
}