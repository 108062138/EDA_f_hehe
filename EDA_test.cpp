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
                    caslib.insert(pr.first);
                }else {
                    if (uprec.size() > 1) {
                        upcontis.push_back(uprec);
                    }
                    uprec.clear();
                    uprec.push_back(pr);
                }
            }

            /*if (downrec.empty()) downrec.push_back(pr);
            else {
                if (downrec.back().second - 1 == rhsval && downrec.back().first + 1 == i){
                    downrec.push_back(pr);
                    caslib.insert(ps.first);
                }else {
                    if (downrec.size() > 1) {
                        downcontis.push_back(downrec);
                    }
                    downrec.clear();
                    downrec.push_back(pr);
                }
            }*/
        }
    }

    if (uprec.size() > 1)
        upcontis.push_back(uprec);
    //if (downrec.size() > 1)
    //    downcontis.push_back(downrec);

    set<int> rec;
    cout << "for the upcontis: " << endl;
    for (auto x : upcontis) {
        for (auto y : x) {
        //    cout << "lhs: " << y.first << " rhs: " << y.second << endl;
            rec.insert(y.first);
        }
        int len = x.size();
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
        //cout << "assign out[" << x[len - 1].first << ":" << x[0].first << "] = in[" << x[len - 1].second << ":" << x[0].second << "]" << endl;
        cout << endl;
    }

    /*cout << "for the downcontis: " << endl;
    for (auto x : downcontis) {
        bool meetbutmore = false;
        if (rec.find(x[0].first) != rec.end()) {
            if (x.size() > 2)
                meetbutmore = true;
            else {
                caslib.erase(x[1].first);
                continue;
            }
        }
        int len = x.size();
        if (meetbutmore == false) {
            //for (int i = 0; i < len; i++)
            //    cout << "lhs: " << x[i].first << " rhs: " << x[i].second << endl;
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
            //cout << "assign out[" << x[len - 1].first << ":" << x[0].first << "] = in[" << x[len - 1].second << ":" << x[0].second << "]" << endl;
            cout << endl;
        }
        else {
            //for (int i = 1; i < len; i++)
            //    cout << "lhs: " << x[i].first << " rhs: " << x[i].second << endl;
            string tmp = "assign out[";
            tmp += to_string(x[len - 1].first);
            tmp += ":";
            tmp += to_string(x[1].first);
            tmp += "] = in[";
            tmp += to_string(x[len - 1].second);
            tmp += ":";
            tmp += to_string(x[1].second);
            tmp += "];\n";
            cout << tmp;
            rescontis.push(tmp);
            //cout << "assign out[" << x[len - 1].first << ":" << x[1].first << "] = in[" << x[len - 1].second << ":" << x[1].second << "]" << endl;
            cout << endl;
        }
        cout << endl;
    }*/


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
    cut_unused_tmp();
    optimized_computing_chen();
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
    //show the required input and output length
    /*cout << outlen << " " << inlen << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    //show the temp var
    cout << "show temp. var" << endl;
    for (auto x = temporaryvar.begin(); x != temporaryvar.end(); ++x) {
        cout << *x << endl;
    }
    cout << "show used temp" << endl;
    for (auto x = usedtemparyvar.begin(); x != usedtemparyvar.end(); ++x)cout << *x << endl;
    //show the lhseq:
    cout << "show equatino " << endl;
    for (auto x = lhseq.begin(); x != lhseq.end(); ++x) {
        cout << "lhs: " << x->first << " rhs: ";
        if (x->second != nullptr && x->second->left==nullptr && x->second->right == nullptr) {
            cout << x->second->str;
            cout << endl;
            continue;
        }
        if (x->second->left != nullptr) {
            cout << x->second->left->str << " ";
        }
        cout << x->second->str << " ";
        if (x->second->right != nullptr) {
            cout << x->second->right->str << endl;
        }
        cout << endl;
    }*/
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
