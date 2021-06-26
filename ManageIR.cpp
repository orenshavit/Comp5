#include "ManageIR.hpp"

#include <utility>
#define P(s) cout << s << endl

string num2name(int num) {
    return "%t"+ to_string(num);
}
Reg ManageIR::new_temp() {
    int size = regs.size();
    regs.push_back(Reg(size, num2name(size)));
    return regs.back();
}

static string to_lower(const string& s) {
    string res;
    for (const char& c : s){
        res += tolower(c);
    }
    return res;
}

string ManageIR::to_llvm_type(const string& type) {
    if (type == "INT")
        return "i32";
    else if (type == "BYTE")
        return "i8";
    else if (type == "BOOL")
        return "i1";
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
    auto list = cbr.makelist(pair<int,BranchLabelIndex>(loc, FIRST));
    if (last_bpatch) {
        list = cbr.merge(list, s->next_list);
    }
    string label = cbr.genLabel();
    cbr.bpatch(list, label);
}

void ManageIR::end_func(const string &ret_type, Node* s) {

    if (ret_type == "VOID") {
        gen_label_and_goto_it(s);
        cbr.emit("\tret void");
    }
    cbr.emit("}");
    cbr.emit("");
}

void ManageIR::assign_reg(const string& type, long value, Node* pNode) {
    auto reg = new_temp();
    string reg_name = reg.name;
    pNode->reg_num = reg.num;
    cbr.emit("\t" + reg_name + " = add " + type + " " + to_string(value) + ", 0");
    last_bpatch = false;
}

Reg ManageIR::getelement_from_stack(int offset) {
    auto ptr = new_temp();
    cbr.emit("\t" + ptr.name + " = getelementptr i32, i32* %st_ptr, i32 " + to_string(offset));
    return ptr;
}

void ManageIR::emit_print_functions() {
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

int ManageIR::call_func(const string &id,
                         const string &ret_type,
                         stack<pair<string, int>> &args) {
    string cmd = "\t";
    Reg ret_reg = new_temp();
    if (ret_type != "VOID") {
        cmd += ret_reg.name + " = ";
    }
    cmd += "call " + to_llvm_type(ret_type) + " @" + id + "(";
    while (!args.empty()) {
       auto arg = args.top();
       cmd += to_llvm_type(arg.first) + num2name(arg.second);
       args.pop();
    }
    cmd += ")";
    cbr.emit(cmd);
    return ret_reg.num;
}

void ManageIR::zext_if_needed(int* r1, int* r2, const string &ty1, const string &ty2,
                           const string &op_type) {
    if (op_type == "INT") {
        if (ty1 == "BYTE") {
            Reg reg = new_temp();
            cbr.emit("\t" + reg.name + " = zext i8 " + num2name(*r1) + " to i32");
            *r1 = reg.num;
        }
        if (ty2 == "BYTE") {
            Reg reg = new_temp();
            cbr.emit("\t" + reg.name + " = zext i8 " + num2name(*r2) + " to i32");
            *r2 = reg.num;
        }
    }
}

void ManageIR::binop(const string &op, int* r1, int* r2,
                     const string &ty1, const string &ty2,
                     Node* p_res_node) {
    const string &op_type = p_res_node->type;
    zext_if_needed(r1, r2, ty1, ty2, op_type);
    auto reg = new_temp();
    p_res_node->reg_num = reg.num;
    string cmd = "\t" + reg.name + " = ";
    if (op == "DIV") cmd += "sdiv";
    else cmd += to_lower(op);
    cmd += " " + to_llvm_type(op_type) + " " + num2name(*r1) + ", " + num2name(*r2);
    cbr.emit(cmd);

}

void ManageIR::load_local_var(int offset, const string &type, Node *pNode) {
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

void ManageIR::store_local_var(int offset, const string& ltype, Node* left_pNode, const string& rtype) {
    auto ptr = getelement_from_stack(offset);
    auto reg = regs.at(regs.size() - 2);
    if (ltype != "INT") {
        auto reg2 = new_temp();
        cbr.emit("\t" + reg2.name + " = zext " + to_llvm_type(ltype) + " " + reg.name + " to i32");
        reg = reg2;
    }
    if (ltype == "INT" and rtype == "BYTE") {
        auto reg3 = new_temp();
        cbr.emit("\t" + reg3.name + " = zext i8 " + reg.name + " to i32");
        reg = reg3;
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

string op2llvm(const string& op) {
    if (op == "==") return "eq ";
    if (op == "!=") return "ne ";
    if (op == "<") return "slt ";
    if (op == ">") return "sgt ";
    if (op == "<=") return "sle ";
    return "sge ";
}

void ManageIR::relop(BiNode* p_binode,
                     int* r1, int* r2,
                     const string& op,
                     const string& ty1,
                     const string& ty2) {
    Reg reg = new_temp();
    string cmd = "\t" + reg.name + " = icmp ";
    cmd += op2llvm(op);
    const string& op_type = larger_type(ty1, ty2);
    cmd += to_llvm_type(op_type);
    zext_if_needed(r1, r2, ty1, ty2, op_type);
    cmd += " " + num2name(*r1) + ", " + num2name(*r2);
    cbr.emit(cmd);

    int loc = cbr.emit("\tbr i1 " + reg.name + ", label @, label @");
    p_binode->true_list = cbr.merge(p_binode->true_list, cbr.makelist({loc, FIRST}));
    p_binode->false_list = cbr.merge(p_binode->false_list, cbr.makelist({loc, SECOND}));
}

void ManageIR::return_exp(int reg_num, const string& ty) {
    cbr.emit("\tret " + to_llvm_type(ty) + " " + num2name(reg_num));
}

void ManageIR::icmp_bool_var(BiNode* p_binode, int reg_num) {
    Reg reg = new_temp();
    cbr.emit("\t" + reg.name + " = icmp eq i1 " + num2name(reg_num) + ", 1");
    int loc = cbr.emit("\tbr i1 " + reg.name + ", label @, label @");
    p_binode->true_list = cbr.merge(p_binode->true_list, cbr.makelist({loc, FIRST}));
    p_binode->false_list = cbr.merge(p_binode->false_list, cbr.makelist({loc, SECOND}));

}

//void ManageIR::temp_bool_reg(const string& one_or_zero) {
//    Reg reg = new_temp();
//    cbr.emit("\t" + reg.name + " = add i1 " + one_or_zero + ", 0");
//
//}

int ManageIR::get_bool(BiNode* p_binode) {
    cbr.emit("");
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

void ManageIR::bpatch_if_else_statement(Node* s,
                                        Node* n,
                                        BiNode* p_binode,
                                        const string &true_label,
                                        const string &false_label,
                                        Node* n2) {
    cbr.bpatch(p_binode->true_list, true_label);
    cbr.bpatch(p_binode->false_list, false_label);
    s->next_list = cbr.merge(n->next_list, n2->next_list);
    last_bpatch = true;
}

void ManageIR::bpatch_if_statement(Node* s,
                                   BiNode* p_binode,
                                   const string &true_label,
                                   Node* n) {
    cbr.bpatch(p_binode->true_list, true_label);
    s->next_list = cbr.merge(p_binode->false_list, n->next_list);
    last_bpatch = true;
}

void ManageIR::bpatch_while(Node *s, const string &m1_label, BiNode *b, const string &m2_label, Node *n) {
    cbr.bpatch(n->next_list, m1_label);
    cbr.bpatch(b->true_list, m2_label);
    s->next_list = b->false_list;
    cbr.emit("\tbr label %" + m1_label);
    last_bpatch = true;
}

void ManageIR::emit_switch(Node* s, Node* exp, Node* n, Node* given_cl, Node* given_m) {
    auto m = dynamic_cast<M*>(given_m);
    cbr.bpatch(n->next_list, m->label);
    auto cl = dynamic_cast<CL*>(given_cl);
    string ty = exp->type;
    int exp_reg_num = exp->reg_num;

    string llvm_ty = to_llvm_type(ty);
    string cmd = "\tswitch " +
            llvm_ty + " " +
            num2name(exp_reg_num) +
            ", label "+
            cl->default_label +" [\n";

    int value;
    string label;
    while(!cl->value_list.empty()) {
        value = cl->value_list.top();
        cl->value_list.pop();

        label = cl->quad_list.top();
        cl->quad_list.pop();

        cmd += "\t\t" + llvm_ty + " " + to_string(value) + ", label " + label + "\n]";
    }
    cbr.emit(cmd);
    s->next_list = cl->next_list;

}


Reg::Reg(int num, string name) : num(num), name(std::move(name)) {}
