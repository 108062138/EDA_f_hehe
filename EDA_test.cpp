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
#include <algorithm>
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
vector<vector<pair<int, char> > > fkcontis;
vector<vector< pair <pair<int, string>, pair<int, int> > > > leecontis;
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
        //cout << "for the item " << iter->first << endl;

        int val = computlhsindex(iter->first);
        if (val == -1)continue;
        indexlib[val] = iter->second;
    }
    vector<pair<int, int> > uprec;
    vector<pair<int, char>> fkrec;
    vector<pair<int, int> > downrec;
    for (int i = 0; i < outlen; i++) {
        //cout << "out[" << i << "]= ";
        if (indexlib[i]->left != nullptr || indexlib[i]->right != nullptr)
            continue;
        if (indexlib[i]->str.find("1\'b1") != std::string::npos || indexlib[i]->str.find("1\'b0") != std::string::npos) {
            char tmpval = (indexlib[i]->str.find("1\'b1") != std::string::npos)? '1' : '0';
            auto pr = make_pair(i, tmpval);
            if (fkrec.empty())fkrec.push_back(pr);
            else {
                if (fkrec.back().first + 1 == i) {
                    fkrec.push_back(pr);
                }
                else {
                    if (fkrec.size() > 1) {
                        fkcontis.push_back(fkrec);
                    }
                    fkrec.clear();
                    fkrec.push_back(pr);
                }
            }
        }
        if (indexlib[i]->str.find("in[") != std::string::npos) {//the rhs has "in["
            //cout << indexlib[i]->str << endl;
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
                }
                else {
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
    if (fkrec.size() > 1)
        fkcontis.push_back(fkrec);
    set<int> rec;
    //cout << "for the upcontis: " << endl;
    for (auto x : upcontis) {
        for (auto y : x) {
            //    cout << "lhs: " << y.first << " rhs: " << y.second << endl;
            rec.insert(y.first);
        }
        int len = x.size();
        for (auto item : x) {
            caslib.insert(item.first);
        }
        //cout << endl;
        string tmp = "assign out[";
        tmp += to_string(x[len - 1].first);
        tmp += ":";
        tmp += to_string(x[0].first);
        tmp += "] = in[";
        tmp += to_string(x[len - 1].second);
        tmp += ":";
        tmp += to_string(x[0].second);
        tmp += "];\n";
        //cout << tmp;
        rescontis.push(tmp);
    }

    for (auto x : fkcontis) {
        int len = x.size();
        string rstr="";
        for (auto item : x) {
            rstr.push_back(item.second);
            caslib.insert(item.first);
        }
        reverse(rstr.begin(),rstr.end());
        string tmp = "assign out[";
        tmp += to_string(x[len - 1].first);
        tmp += ":";
        tmp += to_string(x[0].first);
        tmp += "] = ";
        tmp += to_string(len);
        tmp += "\'b";
        tmp += rstr;
        tmp += ";\n";
        rescontis.push(tmp);
    }
    //after push item into rescontis
    //cout << "for caslib:" << endl;
    //for (auto iter = caslib.begin(); iter != caslib.end(); ++iter)
    //    cout << *iter << endl;
}

void optimized_combining_lee() {

    vector<TreeNode*> indexlib(outlen);
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    for (auto iter = lhseq.begin(); iter != lhseq.end(); ++iter) {
        string theval = "";
        bool meetleftbra = false;
        cout << "for the item " << iter->first << " = " << endl;

        int val = computlhsindex(iter->first);
        if (val == -1)continue;
        indexlib[val] = iter->second;
    }
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    vector<pair< pair<int, string>, pair<int,int> > >leerec;
    for (int i = 0; i < outlen; i++) {
        //cout << "out[" << i << "]= ";
        if (!(indexlib[i]->left && indexlib[i]->right))continue;
        if (indexlib[i]->left->str.find("in[") != std::string::npos && indexlib[i]->right->str.find("in[") != std::string::npos) {//the rhs has "in["
            //cout << indexlib[i]->left->str << endl;
            string ltmpval = "";

            for (int st = 3; st < indexlib[i]->left->str.length(); st++) {
                if (indexlib[i]->left->str[st] == ']')break;
                ltmpval.push_back(indexlib[i]->left->str[st]);
            }
            int lrhsval = stoi(ltmpval);

            string rtmpval = "";

            for (int st = 3; st < indexlib[i]->right->str.length(); st++) {
                if (indexlib[i]->right->str[st] == ']')break;
                rtmpval.push_back(indexlib[i]->right->str[st]);
            }
            int rrhsval = stoi(rtmpval);
            auto pr1 = make_pair(i, indexlib[i]->str);
            auto pr2 = make_pair(lrhsval, rrhsval);
            auto pr = make_pair(pr1, pr2);

            if (leerec.empty())leerec.push_back(pr);
            else {
                if (leerec.back().first.first + 1 == i &&
                    leerec.back().second.first  +1 == pr.second.first && 
                    leerec.back().second.second +1 == pr.second.second &&
                    leerec.back().first.second == pr.first.second
                    ) {
                    //cout << "lee:" << leerec.back().second.first + 1 << " prsf" << pr.second.first << endl;
                    //    cout << "lee: " << leerec.back().second.second + 1 << " pr" << pr.second.first << endl;

                    leerec.push_back(pr);
                }
                else {
                    if (leerec.size() > 1) {
                        leecontis.push_back(leerec);
                    }
                    leerec.clear();
                    leerec.push_back(pr);
                }
            }
        }
    }
    if (leerec.size() > 1)
        leecontis.push_back(leerec);
    //cout << "for the upcontis: " << endl;
    for (auto x : leecontis) {
        int len = x.size();
        for (auto item : x) {
            caslib.insert(item.first.first);
        }
        string tmp = "assign out[";
        tmp += to_string(x[len - 1].first.first);
        tmp += ":";
        tmp += to_string(x[0].first.first);
        tmp += "] = ";
        tmp += "in[";
        tmp += to_string(x[len - 1].second.first);
        tmp += ":";
        tmp += to_string(x[0].second.first);
        tmp += "] ";
        tmp += x[0].first.second;
        tmp += " in[";
        tmp += to_string(x[len - 1].second.second);
        tmp += ":";
        tmp += to_string(x[0].second.second);
        tmp += "];\n";
        rescontis.push(tmp);
    }

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
                    (iter->second->left->str == "1\'b1" && iter->second->left->str == "1\'b1") ||
                    (iter->second->left->str == iter->second->right->str)) {
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

    //cout << "=============================================================" << endl;

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
                //cout << "record wire: " << token_buffer[i] << endl;
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