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
    bool last_bpatch = true;
public:
    Reg new_temp();
    void def_func(const string& id, const string& ret_type, vector<string>& arg_types);
    void end_func(const string& ret_type, Node* s);
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
    void bpatch_if_else_statement(Node* s,
                                  Node* n,
                                  BiNode* p_binode,
                                  const string &true_label,
                                  const string &false_label,
                                  Node* n2);
    void equality(BiNode* p_binode,
                  int* r1,
                  int* r2,
                  const string& op,
                  const string& ty1,
                  const string& ty2);
    void gen_label_and_goto_it(Node* s);
    void return_exp(int reg_num, const string& ty);
    void icmp_bool_var(BiNode* p_binode, int reg_num);
    void temp_bool_reg(const string& one_or_zero);
    //void phi();
    int get_bool(BiNode* p_binode);
};