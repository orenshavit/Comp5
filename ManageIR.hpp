#pragma once
#include <string>
#include <vector>
#include <map>
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
    map<string, int> str_map;
    CodeBuffer& cbr = CodeBuffer::instance();
    bool last_bpatch = true;
public:
    Reg new_temp();
    void def_func(const string& id, const string& ret_type, vector<string>& arg_types);
    void end_func(const string& ret_type, Node* s);
    void assign_reg(const string& type, long value, Node* pNode);
    void store_local_var(int offset, const string& ltype, Node* left_pNode, const string& rtype);
    void load_local_var(int offset, const string &type, Node *pNode);
    void push_string_to_emitGlobal(const string &id, const string &type);
    void getelement_string_from_stack(const string &id,  const string &reg_name);
    void emit_print_functions();
    int call_func(const string& id, const string& ret_type, stack<Node*> &args, Node* exp_list = nullptr);
    string to_llvm_type(const string& type);
    string str2name(const string& str1);
    void binop(const string &op, Node* exp1, Node* exp2,
               Node* p_res_node);
    void zext_if_needed(Node* exp1, Node* exp2, const string &op_type);
    Reg getelement_from_stack(int offset);
    void bpatch_if_else_statement(Node* s,
                                  Node* n,
                                  BiNode* p_binode,
                                  const string &true_label,
                                  const string &false_label,
                                  Node* s1,
                                  Node* s2);
    void bpatch_if_statement(Node* s,
                             BiNode* p_binode,
                             const string &true_label,
                             Node* s1);
    void bpatch_while(Node* s,
                      const string &m1_label,
                      BiNode* b,
                      const string &m2_label,
                      Node* s1,
                      vector<pair<int,BranchLabelIndex>>& brk_list,
                      vector<pair<int,BranchLabelIndex>>& cont_list,
                      Node* n);
    void relop(BiNode* p_binode,
               const string& op,
               Node* exp1,
               Node* exp2);
    void gen_label_and_goto_it(Node* s);
    void return_exp(Node* exp, const string& ty);
    void icmp_bool_var(BiNode* p_binode, Node* exp);
    int get_bool_into_reg(BiNode* p_binode, Node* exp_list = nullptr);
    void emit_switch(Node* s, Node* exp, Node* n, Node* given_cl, Node* given_m,
                     vector<pair<int,BranchLabelIndex>>& brk_list);
    void goto_next_of_s(Node* s);
    void dbg_list(Node* n);
    void goto_specific_list(vector<pair<int, BranchLabelIndex>>& next_list);
    void cl_c_cl_rule(CL* , Node* , CL*);
    void cl_c_rule(CL* , Node*);
    int get_called_bool_exp(Node* exp, Node* exp_list = nullptr);
    void explist_exp(Node* exp, stack<Node*>& called_exps,
                     stack<string>& called_arg_types, Node* exp_list);
    void explist_exp_explist(Node* first_exp_list, Node* exp, Node* n, const string& m_label, Node* exp_list,
                             stack<Node *> &called_exps,
                             stack<string> &called_arg_types);
};