#include "ManageIR.hpp"

#include <utility>
#define P(s) cout << s << endl

/*
 * Static Methods
 */
static string larger_type(const string& ty1, const string& ty2);
static string op2llvm(const string& op);
static string num2name(int num, bool is_arg = false) {
    string name = "%";
    if (!is_arg) name += "t";
    return name + to_string(num);
}
static string to_lower(const string& s) {
    string res;
    for (const char& c : s){
        res += tolower(c);
    }
    return res;
}
string ManageIR::str2name(const string& str1) {
    if (str_map.find(str1) == str_map.end()){
        int size = str_map.size();
        str_map.insert(pair<string, int>(str1, size +1));
    }
    return "str" + to_string(str_map[str1]);
}


Reg ManageIR::new_temp() {
    int size = regs.size();
    regs.push_back(Reg(size, num2name(size)));
    return regs.back();
}



string ManageIR::to_llvm_type(const string& type) {
    if (type == "INT")
        return "i32";
    else if (type == "BYTE")
        return "i8";
    else if (type == "BOOL")
        return "i1";
    else if (type == "STRING")
        return "i8*";
    return "void";
}

void ManageIR::def_func(const string& id,
                        const string& ret_type,
                        vector<string>& arg_types) {
    if (id == "print" or id == "printi") return;
    string def = "define " + to_llvm_type(ret_type) + " @" + id + "(";
    if (!arg_types.empty()) {
        for (uint i = 0; i < arg_types.size() - 1; i++) {
            def += to_llvm_type(arg_types.at(i)) + ", ";
        }
        def += to_llvm_type(arg_types.at(arg_types.size() - 1));
    }
    def += ") {";
    cbr.emit(def);
    cbr.emit("\t%st_ptr = alloca i32, i32 50");
}

void ManageIR::gen_label_and_goto_it(Node* s) {
    int loc = cbr.emit("\tbr label @");
    auto list = cbr.merge(s->next_list, cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST)));
    if (last_bpatch) {
        list = cbr.merge(list, s->next_list);
    }
    string label = cbr.genLabel();
    cbr.bpatch(list, label);
}

void ManageIR::end_func(const string &ret_type, Node* s) {
    gen_label_and_goto_it(s);
    if (ret_type == "VOID") {
        cbr.emit("\tret void");
    }
    else {
        cbr.emit("\tret " + to_llvm_type(ret_type) + " 0");
    }
    cbr.emit("}");
    cbr.emit("");
}

void ManageIR::assign_reg(const string& type, long value, Node* pNode) {
    auto reg = new_temp();
    string reg_name = reg.name;
    pNode->reg_num = reg.num;
    if (pNode->type == "STRING"){
        getelement_string(pNode->id, reg_name);
    }
    else {
        cbr.emit("\t" + reg_name + " = add " + type + " " + to_string(value) + ", 0");
    }
    last_bpatch = false;
}

Reg ManageIR::getelement_from_stack(int offset) {
    auto ptr = new_temp();
    cbr.emit("\t" + ptr.name + " = getelementptr i32, i32* %st_ptr, i32 " + to_string(offset));
    return ptr;
}

void ManageIR::getelement_string(const string &id, const string &reg_name) {
    auto size = id.size();
    auto string_val = id.substr(1,id.size() -2);
    auto name = str2name(string_val);
    cbr.emit("\t" + reg_name + " = getelementptr [" +  to_string(size-1) + " x i8], [" +
        to_string(size-1) + " x i8]* @." + name +", i32 0, i32 0");
}

void ManageIR::push_string_to_emitGlobal(const string &id){
    auto size = id.size();
    auto string_val = id.substr(1,id.size() -2);
    if (str_map.find(id) == str_map.end()) {
        auto name = str2name(string_val);
        auto str = "@." + name + " = internal constant [" + to_string(size-1) +
                   " x i8] c\"" + string_val + "\\00\"";
        cbr.emitGlobal(str);
    }
}

void ManageIR::emit_print_functions() {
    cbr.printGlobalBuffer();
    cbr.emit("declare i32 @printf(i8*, ...)");
    cbr.emit("declare void @exit(i32)");
    cbr.emit("@.int_specifier = constant [4 x i8] c\"%d\\0A\\00\"");
    cbr.emit("@.str_specifier = constant [4 x i8] c\"%s\\0A\\00\"");
    cbr.emit("");
    cbr.emit("define void @printi(i32) {");
        cbr.emit("\t%spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0");
        cbr.emit("\tcall i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)");
        cbr.emit("\tret void");
    cbr.emit("}");
    cbr.emit("");
    cbr.emit("define void @print(i8*) {");
        cbr.emit("\t%spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0");
        cbr.emit("\tcall i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)");
        cbr.emit("\tret void");
    cbr.emit("}");
    cbr.emit("");
}

void ManageIR::zext_if_needed(Node* exp1, Node* exp2, const string &op_type) {
    int* r1 = &(exp1->reg_num);
    int* r2 = &(exp2->reg_num);
    const string& ty1 = exp1->type;
    const string& ty2 = exp2->type;
    if (op_type == "INT") {
        if (ty1 == "BYTE") {
            Reg reg = new_temp();
            cbr.emit("\t" + reg.name + " = zext i8 " + num2name(*r1, exp1->is_arg) + " to i32");
            *r1 = reg.num;
            exp1->is_arg = false;
        }
        if (ty2 == "BYTE") {
            Reg reg = new_temp();
            cbr.emit("\t" + reg.name + " = zext i8 " + num2name(*r2, exp2->is_arg) + " to i32");
            *r2 = reg.num;
            exp1->is_arg = false;
        }
    }
}

void ManageIR::relop(BiNode* p_binode, const string& op, Node* exp1, Node* exp2) {
    int* r1 = &(exp1->reg_num);
    int* r2 = &(exp2->reg_num);
    const string& ty1 = exp1->type;
    const string& ty2 = exp2->type;

    Reg reg = new_temp();
    string cmd = "\t" + reg.name + " = icmp ";
    cmd += op2llvm(op);
    const string& op_type = larger_type(ty1, ty2);
    cmd += to_llvm_type(op_type);
    zext_if_needed(exp1, exp2, op_type);
    cmd += " " + num2name(*r1, exp1->is_arg) + ", " + num2name(*r2, exp2->is_arg);
    cbr.emit(cmd);

    int loc = cbr.emit("\tbr i1 " + reg.name + ", label @, label @");
    p_binode->true_list = cbr.merge(p_binode->true_list, cbr.makelist({loc, FIRST}));
    p_binode->false_list = cbr.merge(p_binode->false_list, cbr.makelist({loc, SECOND}));

}

void ManageIR::check_zero_div(Node* exp2) {
    Reg reg = new_temp();
    cbr.emit("\t" + reg.name + " = icmp eq " + to_llvm_type(exp2->type) + " " +
             num2name(exp2->reg_num, exp2->is_arg) + ", 0");
    int loc = cbr.emit("\tbr i1 " + reg.name + ", label @, label @");
    auto true_list = cbr.makelist({loc, FIRST});
    auto false_list = cbr.makelist({loc, SECOND});
    string true_label = cbr.genLabel();
    auto str_ptr = new_temp();
    getelement_string("\"Error division by zero\"", str_ptr.name);
    cbr.emit("\tcall void @print(i8*" + str_ptr.name + ")");
    auto temp_int = new_temp();
    cbr.emit("\t" + temp_int.name + " = add i32 0, 0");
    cbr.emit("\tcall void @exit(i32" + temp_int.name + ")");
    int false_loc = cbr.emit("\tbr label @");
    false_list = cbr.merge(false_list, cbr.makelist({false_loc, FIRST}));
    string false_label = cbr.genLabel();
    cbr.bpatch(true_list, true_label);
    cbr.bpatch(false_list, false_label);
}

void ManageIR::binop(const string &op, Node* exp1, Node* exp2, Node* p_res_node) {
    int* r1 = &(exp1->reg_num);
    int* r2 = &(exp2->reg_num);
    const string &op_type = p_res_node->type;
    zext_if_needed(exp1, exp2, op_type);
    auto reg = new_temp();

    p_res_node->reg_num = reg.num;

    string cmd = "\t" + reg.name + " = ";
    if (op == "DIV") {
        check_zero_div(exp2);
        if (op_type == "BYTE")
            cmd += "udiv";
        else
            cmd += "sdiv";
    }
    else cmd += to_lower(op);
    cmd += " " + to_llvm_type(op_type) + " " + num2name(*r1, exp1->is_arg) + ", " + num2name(*r2, exp2->is_arg);
    cbr.emit(cmd);

}

void ManageIR::load_local_var(int offset, const string &type, Node *pNode) {
    if (offset < 0) { // function argument
        pNode->reg_num = -(offset + 1);
        pNode->is_arg = true;
        return;
    }
    Reg right_ptr = getelement_from_stack(offset);
    Reg reg = new_temp();
    cbr.emit("\t" + reg.name + " = load i32, i32* " + right_ptr.name);
    if (type != "INT") {
        Reg new_reg = new_temp();
        cbr.emit("\t" + new_reg.name+ " = trunc i32 " + reg.name + " to " + to_llvm_type(type));
        pNode->reg_num = new_reg.num;
    } else
        pNode->reg_num = reg.num;
}

void ManageIR::store_local_var(int offset, const string& ltype, Node* left_pNode, const string& rtype, Node* exp) {
    auto ptr = getelement_from_stack(offset);
    Reg reg = Reg(0, "");
    if (exp) {
        reg.num = exp->reg_num;
        reg.name = num2name(exp->reg_num, exp->is_arg);
    }
    else
        reg = regs.at(regs.size() - 2);

    if (ltype != "INT") {
        auto reg2 = new_temp();
        cbr.emit("\t" + reg2.name + " = zext " + to_llvm_type(ltype) + " " + reg.name + " to i32");
        reg = reg2;
        left_pNode->is_arg = false;
    }
    if (ltype == "INT" and rtype == "BYTE") {
        auto reg3 = new_temp();
        cbr.emit("\t" + reg3.name + " = zext i8 " + reg.name + " to i32");
        reg = reg3;
        left_pNode->is_arg = false;
    }
    left_pNode->reg_num = reg.num;
    cbr.emit("\tstore i32 " + reg.name + ", i32* " + ptr.name);
}

static string larger_type(const string& ty1, const string& ty2) {
    if (ty1 == "INT" or ty2 == "INT") {
        return "INT";
    }
    return "BYTE";
}

static string op2llvm(const string& op) {
    if (op == "==") return "eq ";
    if (op == "!=") return "ne ";
    if (op == "<") return "slt ";
    if (op == ">") return "sgt ";
    if (op == "<=") return "sle ";
    return "sge ";
}

void ManageIR::return_exp(Node* exp, const string& ty) {
    cbr.emit("\tret " + to_llvm_type(ty) + " " + num2name(exp->reg_num, exp->is_arg));
}

void ManageIR::icmp_bool_var(BiNode* p_binode, Node* exp) {
    Reg reg = new_temp();
    cbr.emit("\t" + reg.name + " = icmp eq i1 " + num2name(exp->reg_num, exp->is_arg) + ", 1");
    int loc = cbr.emit("\tbr i1 " + reg.name + ", label @, label @");
    p_binode->true_list = cbr.merge(p_binode->true_list, cbr.makelist({loc, FIRST}));
    p_binode->false_list = cbr.merge(p_binode->false_list, cbr.makelist({loc, SECOND}));

}

void ManageIR::bpatch_if_else_statement(Node* s,
                                        Node* n,
                                        BiNode* p_binode,
                                        const string &true_label,
                                        const string &false_label,
                                        Node* s1,
                                        Node* s2
                                        ) {
    cbr.bpatch(p_binode->true_list, true_label);
    cbr.bpatch(p_binode->false_list, false_label);
    auto temp = cbr.merge(s1->next_list, n->next_list);
    s->next_list = cbr.merge(temp, s2->next_list);
    last_bpatch = true;
}

void ManageIR::bpatch_if_statement(Node* s,
                                   BiNode* p_binode,
                                   const string &true_label,
                                   Node* s1) {
    cbr.bpatch(p_binode->true_list, true_label);
    s->next_list = cbr.merge(p_binode->false_list, s1->next_list);
    last_bpatch = true;
}

void ManageIR::bpatch_while(Node *s, const string &m1_label, BiNode *b, const string &m2_label, Node *s1,
                            vector<pair<int,BranchLabelIndex>>& brk_list,
                            vector<pair<int,BranchLabelIndex>>& cont_list,
                            Node* n) {
    cbr.bpatch(cont_list, m1_label);
    cont_list = {};
    cbr.bpatch(n->next_list, m1_label);

    cbr.bpatch(s1->next_list, m1_label);
    cbr.bpatch(b->true_list, m2_label);
    s->next_list = b->false_list;
    cbr.emit("\tbr label %" + m1_label);
    s->next_list = cbr.merge(s->next_list, brk_list);
    brk_list = {};
    last_bpatch = true;
}

void ManageIR::emit_switch(Node* s, Node* exp, Node* n, Node* given_cl, Node* given_m,
                           vector<pair<int,BranchLabelIndex>>& brk_list) {
    auto m = dynamic_cast<M*>(given_m);
    cbr.bpatch(n->next_list, m->label); // like goto init
    auto cl = dynamic_cast<CL*>(given_cl);
    string ty = exp->type;
    int exp_reg_num = exp->reg_num;

    string llvm_ty = to_llvm_type(ty);
    string cmd = "\tswitch " +
            llvm_ty + " " +
            num2name(exp_reg_num, exp->is_arg) +
            ", label ";

    bool default_defined = false;
    if (cl->default_label != "") {
        default_defined = true;
        cmd += "%" + cl->default_label;
    }
    else
        cmd += "@";
    cmd += " [\n";

    int loc = cbr.emit(cmd);
    cmd = "";
    if (!default_defined) {
        s->next_list = cbr.makelist({loc, FIRST});
    }
    s->next_list = cbr.merge(s->next_list, brk_list);
    s->next_list = cbr.merge(s->next_list, cl->next_list);
    brk_list = {};

    int value;
    string label;
    while(!cl->value_list.empty()) {
        value = cl->value_list.top();
        cl->value_list.pop();

        label = cl->quad_list.top();
        cl->quad_list.pop();

        cmd += "\t\t" + llvm_ty + " " + to_string(value) + ", label %" + label + "\n";
    }
    cbr.emit(cmd + "\t]");

}

void ManageIR::goto_next_of_s(Node* s) {
    int loc = cbr.emit("\tbr label @");
    s->next_list = cbr.merge(s->next_list, cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST)));
}

void ManageIR::dbg_list(Node *n) {

}

void ManageIR::goto_specific_list(vector<pair<int, BranchLabelIndex>>& next_list) {
    int loc = cbr.emit("\tbr label @");
    next_list = cbr.merge(next_list, cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST)));
}

void ManageIR::cl_c_cl_rule(CL *given_cl, Node *given_c, CL *cl1) {
    string last_quad = cl1->quad_list.top();
    auto c = dynamic_cast<C*>(given_c);
    auto cl = dynamic_cast<CL*>(given_cl);
    cl->quad_list = cl1->quad_list;
    cl->quad_list.push(c->quad);
    cl->value_list = cl1->value_list;
    cl->value_list.push(c->value);
    cbr.bpatch(c->next_list, last_quad);
    cl->next_list = cl1->next_list;
    cl->default_label = cl1->default_label;
}

void ManageIR::cl_c_rule(CL *cl, Node *given_c) {
    //cl = new CL();
    auto c = dynamic_cast<C*>(given_c);
    cl->quad_list.push(c->quad);
   // cl->default_label
    cl->value_list.push(c->value);
    cl->next_list = c->next_list;
}

vector<Node*> ManageIR::cast_bytes_to_ints(const string &id, stack<Node*> &args,
                       vector<string>& exp_func_args) {
    vector<Node*>args_vec;
    while (!args.empty()) {
        args_vec.push_back(args.top());
        args.pop();
    }

    for (uint i = 0; i < exp_func_args.size(); i++) {
        Node* called_exp = args_vec.at(i);
        string exp_type = exp_func_args.at(i);
        string called_type = called_exp->type;
        if (exp_type != called_type) {
            if (exp_type == "INT" && called_type == "BYTE") {
                Reg reg = new_temp();
                cbr.emit("\t" + reg.name + " = zext i8 " + num2name(called_exp->reg_num, called_exp->is_arg) + " to i32");
                called_exp->reg_num = reg.num;
                called_exp->is_arg = false;
            }
        }
    }
    return args_vec;
}

int ManageIR::call_func(const string &id,
                        const string &ret_type,
                        stack<Node*> &args,
                        unordered_map<string, FuncTypes>& hash_funcs,
                        Node* exp_list) {
    if (exp_list != nullptr && !exp_list->next_list.empty())
        cbr.bpatch(exp_list->next_list, cbr.genLabel());

    vector<string> exp_func_args = hash_funcs[id].arg_types;
    vector<Node*> args_vec = cast_bytes_to_ints(id, args, exp_func_args);

    string cmd = "\t";
    Reg ret_reg = new_temp();
    if (ret_type != "VOID") {
        cmd += ret_reg.name + " = ";
    }
    cmd += "call " + to_llvm_type(ret_type) + " @" + id + "(";
    for (uint i = 0 ; i < args_vec.size(); i ++) {
        Node* arg = args_vec.at(i);
        string type = arg->type;
        if (type == "BYTE" and exp_func_args.at(i) == "INT")
            type = "INT";
        cmd += to_llvm_type(type);
        cmd += num2name(arg->reg_num, arg->is_arg);
        if (i != args_vec.size() - 1) cmd += ", ";
    }
    cmd += ")";
    cbr.emit(cmd);
    args = {};




    return ret_reg.num;
}

int ManageIR::get_bool_into_reg(BiNode* p_binode, Node* exp_list) {
    cbr.emit("\t; Getting Bool Using Phi");
    const string &true_label = cbr.genLabel();
    int next_loc_1 = cbr.emit("\tbr label @");

    const string &false_label = cbr.genLabel();
    int next_loc_2 = cbr.emit("\tbr label @");

    const string &next_label = cbr.genLabel();
    auto list = cbr.merge(cbr.makelist({next_loc_1, FIRST}), cbr.makelist({next_loc_2, FIRST}));
    cbr.bpatch(list, next_label);
    Reg phi_reg = new_temp();
    cbr.emit("\t" + phi_reg.name + " = phi i1 [1, %" + true_label + "], [0, %" + false_label + "]");

    cbr.bpatch(p_binode->true_list, true_label);
    cbr.bpatch(p_binode->false_list, false_label);

    return phi_reg.num;
}


int ManageIR::get_called_bool_exp(Node* exp, Node* exp_list) {
    int reg_num = exp->reg_num;
    if (exp->type == "BOOL") {
        BiNode* bi_exp = dynamic_cast<BiNode*>(exp);
        reg_num = get_bool_into_reg(bi_exp, exp_list);
    }
    return reg_num;
}

void ManageIR::explist_exp(Node *exp, stack<Node *> &called_exps,
                           stack<string> &called_arg_types, Node* exp_list) {
    cbr.emit("; ExpList : Exp");
    called_arg_types.push(exp->type);
    exp->reg_num = get_called_bool_exp(exp, exp_list);
    if (exp_list != nullptr){
        int loc = cbr.emit("\tbr label @");
        exp_list->next_list = cbr.makelist({loc, FIRST});
    }
    called_exps.push(exp);

}

void ManageIR::explist_exp_explist(Node* first_exp_list, Node *exp, Node *n, const string& m_label, Node *second_exp_list,
                                   stack<Node *> &called_exps,
                                   stack<string> &called_arg_types) {
    cbr.emit("; ExpList : Exp COMMA N M ExpList and M label is " + m_label);
    cbr.bpatch(n->next_list, m_label);
    called_arg_types.push(exp->type);
    exp->reg_num = get_called_bool_exp(exp, second_exp_list);
    called_exps.push(exp);
    first_exp_list->next_list = second_exp_list->next_list;
    cbr.emit("\tbr label %" + m_label);
}


Reg::Reg(int num, string name) : num(num), name(std::move(name)) {}
