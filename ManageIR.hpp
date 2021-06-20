#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "SymbolsTable.hpp"
#include "bp.hpp"
#include "output.hpp"

using namespace std;

struct Reg {
    int num;
    string name;
    Reg(int num, string name);
};

class ManageIR {
    vector<Reg> regs;
    CodeBuffer& cbr = CodeBuffer::instance();
    public:
    Reg new_temp();
    void def_func(const string& id, const string& ret_type, vector<string>& arg_types);
    void end_func(const string& ret_type);
    void assign_reg(const string& type, long value, Node* pNode);
    void store_local_var(int offset, const string& type, Node* pNode);
    void load_local_var(int offset, const string &type, Node *pNode);
    void emit_print_functions();
    void call_func(const string& id, const string& ret_type, stack<pair<string, int>> &args);
    string to_llvm_type(const string& type);
    void binop(const string &op, int* r1, int* r2,
               const string &ty1, const string &ty2,
               Node* p_res_node);
    void zext_if_needed(int* r1, int* r2, const string &ty1, const string &ty2,
                                  const string &op_type);
    Reg getelement_from_stack(int offset);
    void if_statement(const string& true_label, const string& false_label);
    void equality(int* r1, int* r2, const string& op, const string& ty1, const string& ty2);




};