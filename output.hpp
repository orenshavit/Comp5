#ifndef _236360_3_
#define _236360_3_

#include <vector>
#include <string>
#include "bp.hpp"

using namespace std;


class Node {
    public:
    string id;
    string type;
    long value;
    int reg_num;
    virtual ~Node() = default;
};

class BiNode : public Node {
public:
    vector<pair<int,BranchLabelIndex>> true_list;
    vector<pair<int,BranchLabelIndex>> false_list;
};

class M : public Node {
public:
    const string& label; // like quad
//    pair<int,BranchLabelIndex> label;
    explicit M(const string& label) : Node(), label(label) {}
    ~M() override = default;
};

class N : public Node {
public:
    vector<pair<int,BranchLabelIndex>> next_list;
    explicit N() : Node() {}
    ~N() override = default;
};


class Id : public Node {
public:
    string id;
    Id(string id) : Node(), id(id) {}
    ~Id() {}
};






#define YYSTYPE Node*

namespace output{
    void endScope();
    void printID(const string& id, int offset, const string& type);

    /* Do not save the string returned from this function in a data structure
        as it is not dynamically allocated and will be destroyed(!) at the end of the calling scope.
    */
    string makeFunctionType(const string& retType, vector<string>& argTypes);

    void errorLex(int lineno);
    void errorSyn(int lineno);
    void errorUndef(int lineno, const string& id);
    void errorDef(int lineno, const string& id);
    void errorUndefFunc(int lineno, const string& id);
    void errorMismatch(int lineno);
    void errorPrototypeMismatch(int lineno, const string& id, vector<string>& argTypes);
    void errorUnexpectedBreak(int lineno);
    void errorUnexpectedContinue(int lineno);
    void errorMainMissing();
    void errorByteTooLarge(int lineno, const string& value);
}

#endif
