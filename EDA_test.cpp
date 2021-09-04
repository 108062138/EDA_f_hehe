// EDA_problemf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <stack>
#include <map>
#include <queue>
using namespace std;
typedef struct TreeNode {
    string str;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : str(""), left(nullptr), right(nullptr) {}
    TreeNode(string x) : str(x), left(nullptr), right(nullptr) {}
}TreeNode;
map<string, TreeNode*> lhseq;
int inlen = 1; int outlen = 1;
set<string> temporaryvar;
set<string> usedtemparyvar;
stack<string> st;
queue<string> endoutput;
vector<vector<pair<int, int> > > upcontis;
vector<vector<pair<int, int> > > downcontis;
vector<vector< pair <pair<int, int>, pair<string, string> > > > vec;
set<int> caslib;
stack<string> rescontis;

pair<int, int> setval(string& str, int begin) {
    string tmp = "0";
    int nextcur = 0;
    for (int i = begin; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9')
            tmp.push_back(str[i]);
        if (str[i] == ':') {
            nextcur = i++;
            return make_pair(stoi(tmp), nextcur);
        }
    }
    return make_pair(stoi(tmp), -1);
}
void cut_unused_tmp() {
    for (auto x = lhseq.begin(); x != lhseq.end(); ++x) {
        if (x->second->left == nullptr && x->second->right == nullptr) {
            if (temporaryvar.find(x->second->str) != temporaryvar.end()) {
                usedtemparyvar.insert(x->second->str);
            }
            continue;
        }
        if (temporaryvar.find(x->second->left->str) != temporaryvar.end()) {
            usedtemparyvar.insert(x->second->left->str);
        }
        if (temporaryvar.find(x->second->right->str) != temporaryvar.end()) {
            usedtemparyvar.insert(x->second->right->str);
        }
    }
}
void optimized_computing_david() {
    for (auto x = lhseq.begin(); x != lhseq.end(); ++x) {
        if (x->second->str == "~1\'b0") {
            string rmem = x->first;
            for (auto y = lhseq.begin(); y != lhseq.end(); ++y) {
                if (y->second->left == nullptr) {
                    if (y->second->str == rmem) {
                        y->second->str = "1\'b1";
                    }
                }
                else {
                    if (y->second->left->str == rmem) {
                        y->second->left->str = "1\'b1";
                    }
                    if (y->second->right->str == rmem) {
                        y->second->right->str = "1\'b1";
                    }
                }
            }
        }
        if (x->second->str == "~1\'b1") {
            string rmem = x->first;
            for (auto y = lhseq.begin(); y != lhseq.end(); ++y) {
                if (y->second->left == nullptr) {
                    if (y->second->str == rmem) {
                        y->second->str = "1\'b0";
                    }
                }
                else {
                    if (y->second->left->str == rmem) {
                        y->second->left->str = "1\'b0";
                    }
                    if (y->second->right->str == rmem) {
                        y->second->right->str = "1\'b0";
                    }
                }
            }
        }
        if (x->second->str == "1\'b0") {
            string rmem = x->first;
            for (auto y = lhseq.begin(); y != lhseq.end(); ++y) {
                if (y->second->left == nullptr) {
                    if (y->second->str == rmem) {
                        y->second->str = "1\'b0";
                    }
                }
                else {
                    if (y->second->left->str == rmem) {
                        y->second->left->str = "1\'b0";
                    }
                    if (y->second->right->str == rmem) {
                        y->second->right->str = "1\'b0";
                    }
                }
            }
        }
        if (x->second->str == "1\'b1") {
            string rmem = x->first;
            for (auto y = lhseq.begin(); y != lhseq.end(); ++y) {
                if (y->second->left == nullptr) {
                    if (y->second->str == rmem) {
                        y->second->str = "1\'b1";
                    }
                }
                else {
                    if (y->second->left->str == rmem) {
                        y->second->left->str = "1\'b1";
                    }
                    if (y->second->right->str == rmem) {
                        y->second->right->str = "1\'b1";
                    }
                }
            }
        }
    }
}
int computlhsindex(string str) {
    string theval = "";
    bool meetleftbra = false;
    for (auto x : str) {
        if (x == '[') {
            meetleftbra = true;
            continue;
        }
        if (x == ']')break;
        if (meetleftbra == true) {
            theval.push_back(x);
        }
    }
    if (theval == "")return -1;

    return stoi(theval);
}
void optimized_computing_chen() {

    vector<TreeNode*> indexlib(outlen);

    for (auto iter = lhseq.begin(); iter != lhseq.end(); ++iter) {
        string theval = "";
        bool meetleftbra = false;
        cout << "for the item " << iter->first << endl;
        
        int val = computlhsindex(iter->first);
        if (val == -1)continue;
        indexlib[val] = iter->second;
    }
    vector<pair<int, int> > uprec;
    vector<pair<int, int> > downrec;
    for (int i = 0; i < outlen; i++) {
        cout << "out[" << i << "]= ";
        if (indexlib[i]->str.find("in[") != std::string::npos) {//the rhs has "in["
            cout << indexlib[i]->str << endl;
            string tmpval = "";
            for (int st = 3; st < indexlib[i]->str.length(); st++) {
                if (indexlib[i]->str[st] == ']')break;
                tmpval.push_back(indexlib[i]->str[st]);
            }
            int rhsval = stoi(tmpval);
            auto pr = make_pair(i, rhsval);
            //auto ps = make_pair(i, rhsval);
            if (uprec.empty()) uprec.push_back(pr);
            else {
                if (uprec.back().second + 1 == rhsval && uprec.back().first + 1 == i) {
                    uprec.push_back(pr);
                }else {
                    if (uprec.size() > 1) {
                        upcontis.push_back(uprec);
                    }
                    uprec.clear();
                    uprec.push_back(pr);
                }
            }
        }
    }

    if (uprec.size() > 1)
        upcontis.push_back(uprec);
    set<int> rec;
    cout << "for the upcontis: " << endl;
    for (auto x : upcontis) {
        for (auto y : x) {
        //    cout << "lhs: " << y.first << " rhs: " << y.second << endl;
            rec.insert(y.first);
        }
        int len = x.size();
        for (auto item : x) {
            caslib.insert(item.first);
        }
        cout << endl;
        string tmp = "assign out[";
        tmp += to_string(x[len - 1].first);
        tmp += ":";
        tmp += to_string(x[0].first);
        tmp += "] = in[";
        tmp += to_string(x[len - 1].second);
        tmp += ":";
        tmp += to_string(x[0].second);
        tmp += "];\n";
        cout << tmp;
        rescontis.push(tmp);
    }
    //after push item into rescontis
    cout << "for caslib:" << endl;
    for (auto iter = caslib.begin(); iter != caslib.end(); ++iter)
        cout << *iter << endl;
}
void optimized_combining_lee() {
    vector<TreeNode*> indexlib(outlen);
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for (auto iter = lhseq.begin(); iter != lhseq.end(); ++iter) {
        string theval = "";
        bool meetleftbra = false;
        cout << "for the item " << iter->first << " = ";

        int val = computlhsindex(iter->first);
        if (val == -1)continue;
        indexlib[val] = iter->second;
        if (iter->second->left && iter->second->right) {
            cout << iter->second->left->str << " " << iter->second->str << " " << iter->second->right->str;
            cout << endl;
        }
    }
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    vector<pair<int, int> > uprec;
    vector<pair<int, int> > downrec;
    vector< pair <pair<int, int>, pair<string, string> > > p;

    for (int i = 0; i < outlen; i++) {
        cout << "out[" << i << "]= ";
        if (!(indexlib[i]->left && indexlib[i]->right))continue;
        if (indexlib[i]->left->str.find("in[") != std::string::npos) {//the rhs has "in["
            cout << indexlib[i]->str << endl;
            string tmpval = "";

            for (int st = 3; st < indexlib[i]->left->str.length(); st++) {
                if (indexlib[i]->left->str[st] == ']')break;
                tmpval.push_back(indexlib[i]->left->str[st]);
            }
            string mid, right;
            mid = indexlib[i]->str;
            right = indexlib[i]->right->str;

            int rhsval = stoi(tmpval);
            auto pr = make_pair(i, rhsval);
            auto pr_oper_and_var = make_pair(mid, right);
            auto pr_pr_and_oper = make_pair(pr, pr_oper_and_var);
            //p.push_back(pr_pr_and_oper);

            if (p.empty()) p.push_back(pr_pr_and_oper);
            else {
                if (p.back().first.second + 1 == rhsval && p.back().first.first + 1 == i) {
                    if (p.back().second.first == mid && p.back().second.first == right)
                        p.push_back(pr_pr_and_oper);
                }
                else {
                    if (p.size() > 1) {
                        vec.push_back(p);
                    }
                    p.clear();
                    p.push_back(pr_pr_and_oper);
                }
            }
        }
    }
    if (p.size() > 1)
        vec.push_back(p);
    ///////
    set<int> rec;
    cout << "for the upcontis: " << endl;
    for (auto x : vec) {
        for (auto y : x) {
            //    cout << "lhs: " << y.first << " rhs: " << y.second << endl;
            rec.insert(y.first.first);
            caslib.insert(y.first.first);
        }
        int len = rec.size();

        cout << endl;
        string tmp = "assign out[";
        tmp += to_string(x[len - 1].first.first);
        tmp += ":";
        tmp += to_string(x[0].first.first);
        tmp += "] = in[";
        tmp += to_string(x[len - 1].first.second);
        tmp += ":";
        tmp += to_string(x[0].first.second) + "]";
        tmp += x[0].second.first + x[0].second.second;
        tmp += ";\n";
        cout << tmp;
        rescontis.push(tmp);
    }
    //after push item into rescontis
    cout << "for caslib:" << endl;
    for (auto iter = caslib.begin(); iter != caslib.end(); ++iter)
        cout << *iter << endl;
    
}
void optimized_computing_lee() {
    for (auto iter = lhseq.begin(); iter != lhseq.end(); ++iter) {
        //handle bitwise &
        if (iter->second->str == "&") {
            if ((iter->second->left != nullptr && iter->second->left->str == "1\'b0") || (iter->second->right != nullptr && iter->second->right->str == "1\'b0")) {
                delete iter->second->left;
                iter->second->left = nullptr;
                delete iter->second->right;
                iter->second->right = nullptr;
                iter->second->str = "1\'b0";
                continue;
            }
            if (iter->second->left != nullptr && iter->second->left->str == "1\'b1") {
                iter->second->str = iter->second->right->str;
                delete iter->second->right;
                iter->second->right = nullptr;
                delete iter->second->left;
                iter->second->left = nullptr;
                continue;
            }

            if (iter->second->right != nullptr && iter->second->right->str == "1\'b1") {
                iter->second->str = iter->second->left->str;
                delete iter->second->right;
                iter->second->right = nullptr;
                delete iter->second->left;
                iter->second->left = nullptr;
                continue;
            }
        }
        //handle bitwise |
        if (iter->second->str == "|") {
            if ((iter->second->left != nullptr && iter->second->left->str == "1\'b1") || (iter->second->right != nullptr && iter->second->right->str == "1\'b1")) {
                delete iter->second->left;
                iter->second->left = nullptr;
                delete iter->second->right;
                iter->second->right = nullptr;
                iter->second->str = "1\'b1";
                continue;
            }
        }
        if (iter->second->str == "^") {
            if (iter->second->left != nullptr && iter->second->right != nullptr) {
                if ((iter->second->left->str == "1\'b1" && iter->second->left->str == "1\'b0") ||
                    (iter->second->left->str == "1\'b0" && iter->second->left->str == "1\'b1")) {
                    delete iter->second->left;
                    iter->second->left = nullptr;
                    delete iter->second->right;
                    iter->second->right = nullptr;
                    iter->second->str = "1\'b1";
                    continue;
                }
                if ((iter->second->left->str == "1\'b0" && iter->second->left->str == "1\'b0") ||
                    (iter->second->left->str == "1\'b1" && iter->second->left->str == "1\'b1")) {
                    delete iter->second->left;
                    iter->second->left = nullptr;
                    delete iter->second->right;
                    iter->second->right = nullptr;
                    iter->second->str = "1\'b0";
                    continue;
                }

                if (iter->second->left->str == "1\'b0") {
                    iter->second->str = iter->second->right->str;
                    delete iter->second->left;
                    iter->second->left = nullptr;
                    delete iter->second->right;
                    iter->second->right = nullptr;
                    continue;
                }
                if (iter->second->right->str == "1\'b0") {
                    iter->second->str = iter->second->left->str;
                    delete iter->second->left;
                    iter->second->left = nullptr;
                    delete iter->second->right;
                    iter->second->right = nullptr;
                    continue;
                }

            }
        }

        if (iter->second->str == "~1\'b1")
            iter->second->str = "1\'b0";
        if (iter->second->str == "~1\'b0")
            iter->second->str = "1\'b1";
    }
}

int main()
{
    int is_ok = EXIT_FAILURE;
    FILE* fp = std::fopen("./original.v", "r");
    if (!fp) {
        std::perror("File opening failed");
        return is_ok;
    }

    int c; // note: int, not char, required to handle EOF
    string tok = "";
    bool eatall = false;
    vector<string> token_buffer;
    while ((c = std::fgetc(fp)) != EOF) { // standard C I/O file reading loop
        //std::putchar(c);
        char tmp = c;
        if (eatall == true) {
            tok.push_back(tmp);
            continue;
        }
        if (c == ' ' || c == '\n') {
            if (tok == "endmodule") {
                eatall = true;
            }
            if (!tok.empty()) {
                token_buffer.push_back(tok);
                //cout << tok << endl;
            }
            tok = "";
        }
        else {
            tok.push_back(tmp);
        }
    }

    cout << "=============================================================" << endl;

    bool seeendflag = false;
    string rem_out;
    string rem_in;
    for (int i = 4; i < token_buffer.size(); i++) {
        if (seeendflag = true || token_buffer[i] == "endmodule") {
            seeendflag = true;
            endoutput.push(token_buffer[i]);
        }
        if (token_buffer[i].find("	output") != std::string::npos) {
            rem_out = token_buffer[i];
            if (token_buffer[i].length() >= 10) {
                pair<int, int> leftval = setval(token_buffer[i], 8);
                pair<int, int> rightval = setval(token_buffer[i], leftval.second);
                outlen = leftval.first - rightval.first + 1;
            }
        }
        if (token_buffer[i].find("	input") != std::string::npos) {
            rem_in = token_buffer[i];
            if (token_buffer[i].length() > 10) {
                pair<int, int> leftval = setval(token_buffer[i], 7);
                pair<int, int> rightval = setval(token_buffer[i], leftval.second);
                inlen = leftval.first - rightval.first + 1;
            }
        }
        if (!st.empty()) {
            if (st.top() == "wire") {
                cout << "record wire: " << token_buffer[i] << endl;
                st.pop();
                token_buffer[i].pop_back();
                temporaryvar.insert(token_buffer[i]);
            }
            else if (st.top() == "lhs") {
                st.pop();
                st.push(token_buffer[i]);
                st.push("at=");
                lhseq.insert(make_pair(token_buffer[i], nullptr));
            }
            else if (st.top() == "at=") {
                st.pop();
                st.push("after=");
            }
            else if (st.top() == "after=") {
                st.pop();
                string laststr = st.top();
                auto iter = lhseq.find(laststr);
                st.pop();//change to next sentence
                if (token_buffer[i][0] == '~') {//for x=~y;
                    if (iter != lhseq.end()) {
                        TreeNode* tmp = new TreeNode;
                        token_buffer[i].pop_back();
                        string oper1 = token_buffer[i];
                        tmp->str = oper1;
                        iter->second = tmp;
                    }
                }
                else {
                    int len = token_buffer[i].length();
                    if (token_buffer[i][len - 1] == ';') {//for x=y;
                        TreeNode* tmp = new TreeNode;
                        token_buffer[i].pop_back();
                        string oper1 = token_buffer[i];
                        tmp->str = oper1;
                        iter->second = tmp;
                    }
                    else {
                        string oper1 = token_buffer[i];
                        string ndoperator = token_buffer[++i];
                        string oper2 = token_buffer[++i];
                        oper2.pop_back();
                        TreeNode* tmp = new TreeNode;
                        tmp->str = ndoperator;
                        tmp->left = new TreeNode;
                        tmp->left->str = oper1;
                        tmp->right = new TreeNode;
                        tmp->right->str = oper2;
                        iter->second = tmp;
                    }
                }
            }
        }
        if (token_buffer[i] == "	wire") {
            st.push("wire");
        }

        if (token_buffer[i] == "	assign") {
            st.push("lhs");
        }
    }

    if (std::ferror(fp)) {
        std::puts("I/O error when reading");
    }
    else if (std::feof(fp)) {
        std::puts("End of file reached successfully");
        is_ok = EXIT_SUCCESS;
    }


    std::fclose(fp);

    optimized_computing_lee();
    optimized_computing_david();
    optimized_computing_lee();
    cut_unused_tmp();
    optimized_computing_chen();
    optimized_combining_lee();
    ofstream mf("optimized.v");
    mf << "module dut(out,in);" << endl;
    mf << rem_out << " out;" << endl;
    mf << rem_in << " in;" << endl;
    for (auto x = usedtemparyvar.begin(); x != usedtemparyvar.end(); ++x) {
        mf << "wire " << *x << ";" << endl;
    }

    for (auto x = lhseq.begin(); x != lhseq.end(); ++x) {
        int val = computlhsindex(x->first);
        if (caslib.find(val) == caslib.end()) {
            mf << "assign ";
            if (x->second->left == nullptr || x->second->right == nullptr) {
                mf << x->first << " = " << x->second->str << ";" << endl;
            }
            else {
                mf << x->first << " = " << x->second->left->str << " " << x->second->str << " " << x->second->right->str << ";" << endl;
            }
        }
    }
    while (!rescontis.empty())
    {
        mf << rescontis.top();
        rescontis.pop();
    }
    mf << "endmodule" << endl;
    mf << tok << endl;
    mf.close();
    return 0;
}
