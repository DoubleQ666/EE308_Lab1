#include <bits/stdc++.h>
using namespace std;

string keyword[] = {"asm", "do","if","return","typedef","auto","double","inline","short","typeid","bool","dynamic_cast","int","signed","typename","break","else","long","sizeof","union","case","enum","mutable","static","unsigned","catch","explicit","namespace","static_cast","using","char","export","new","struct","virtual","class","extern","operator","switch","void","const","false","private","template","volatile","const_cast","float","protected","this","wchar_t","continue","for","public","throw","while","default","friend","register","true", "delete","goto","reinterpret_cast","try"};
string input;
vector<int> sw;
int cnt_else_if = 0, cnt_else = 0;

void get_switch(int& st, int id) {
    sw.emplace_back(0);
    int cnt = 0;
    for (int i = st; i < input.length(); i++) {
        if (input[i] == '{') {
            cnt++;
        } else if (input[i] == '}') {
            cnt--;
            if (!cnt) {
                st = i;
                return;
            }
        }

        if (input.substr(i, 4) == "case") {
            sw[id]++;
        }
    }
}

void get_if(int& st) {
    bool is_else_if = 0;
    bool flag = 0;
    int cnt = 0;
    for (int i = st + 2; i < input.length(); i++) {
        if (flag == 1) {
            if (input[i] == '{') {
                cnt++;
            }
            if (input[i] == '}') {
                cnt--;
                if (!cnt) {
                    st = i + 1;
                    return;
                }
            }
        }

        if (input.substr(i, 2) == "if") {
            get_if(i);
        }
        if (input.substr(i, 7) == "else if") {
            if (!is_else_if) {
                is_else_if = 1;
                cnt_else_if++;
            }
            i += 7;
        } else if (input.substr(i, 4) == "else") {
            if (!is_else_if) {
                cnt_else++;
            }
            flag = 1;
            i += 4;
        }
    }
}

int main() {
    string path;
    cout << "Please input the file's path: ";
    cin >> path;
    cout << "Please input completion level: ";
    int level;
    cin >> level;

    double st = clock();
    ifstream ifs;
    ifs.open(path, ios::in);
    if (!ifs.is_open()) {
        cout << "fail to open the specified file" << endl;
        exit(0);
    }

    string buf;
    while (getline(ifs, buf)) {
        input += buf;
        input += "\n";
    }

    int cnt = 0;
    for (int i = 0; i < 63; i++) {
        int len = keyword[i].length();
        for (int j = 0; j < input.length(); j++) {
            if (input.substr(j, len) == keyword[i]) {
                cnt++;
                if (input.substr(j, len) == "do") {
                    if (input.substr(j, 6) == "double") {
                        cnt--;
                    }
                }

            }
        }
    }


//    int sw_num = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input.substr(i, 6) == "switch") {
            get_switch(i, sw_num++);
        }
    }
    for (int i = 0; i < input.length(); i++) {
        if (input.substr(i, 2) == "if") {
            get_if(i);
        }
    }



    if (level >= 1) {
        cout << "total num: " << cnt << endl;
    }
    if (level >= 2) {
        cout << "switch num: " << sw_num << endl;
        cout << "case num: ";
        for (int i = 0; i < sw.size(); i++) {
            cout << sw[i] << " ";
        }
        cout << endl;
    }
    if (level >= 3) {
        cout << "if-else num: " << cnt_else << endl;
    }
    if (level >= 4) {
        cout << "if-elseif-else num: " << cnt_else_if << endl;
    }
    double end = clock();
    cout << "time cost: " << end - st << endl;
    return 0;
}