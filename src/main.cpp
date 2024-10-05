#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "AVL.h"

using namespace std;

bool isUFIDValid(const string& ufid) {
    return regex_match(ufid, regex("\\d{8}")); // must be 8 digits
}a

bool isNameValid(const string& name) {
    return regex_match(name, regex("[a-zA-Z ]+")); // only conaints letters and spaces
}

int main() {
    MyAVLTree tree;
    string numCommands;

    // how many commands?
    getline(cin, numCommands);
    int n = stoi(numCommands);


    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        istringstream in(line);

        string command;
        in >> command;

        if (command == "insert") {

            string name, ufid;
            char quote;
            in >> quote;
            getline(in, name, '"');
            in >> ufid;


            if (quote == '"' && isNameValid(name) && isUFIDValid(ufid)) {
                tree.insert(name, ufid);
            }

        } else if (command == "remove") {
            string ufid;
            in >> ufid;

            if (isUFIDValid(ufid)) {

                bool success = tree.remove(ufid);

                if (success) {
                    cout << "successful" << endl;
                } else {
                    cout << "unsuccessful" << endl;
                }

            } else {
                cout << "unsuccessful" << endl;
            }

        } else if (command == "search") {
            string searchType;
            in >> searchType;

            if (searchType[0] == '"') {
                string name = searchType.substr(1, searchType.size() - 2);

                if (isNameValid(name)) {
                    string result = tree.searchByName(name);
                    if (result != "unsuccessful") {
                        cout << result;
                    } else {
                        cout << "unsuccessful" << endl;
                    }

                } else {
                    cout << "unsuccessful" << endl;
                }

            } else if (isUFIDValid(searchType)) {
                string name = tree.searchByID(searchType);

                if (!name.empty()) {
                    cout << name << endl;
                } else {
                    cout << "unsuccessful" << endl;
                }

            } else {
                cout << "unsuccessful" << endl;
            }

        } else if (command == "printInorder") {
            tree.printInorder();

        } else if (command == "printPreorder") {
            tree.printPreorder();

        } else if (command == "printPostorder") {
            tree.printPostorder();

        } else if (command == "printLevelCount") {
            cout << tree.getLevelCount() << endl;

        } else if (command == "removeInorder") {
            int N;
            in >> N;

            std::vector<std::string> ufidList;
            tree.getInorderUFIDs(ufidList);

            if (N >= 0 && N < ufidList.size()) {
                const std::string& ufidToRemove = ufidList[N];
                tree.remove(ufidToRemove);
                cout << "successful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }
        }else {
            cout << "unsuccessful" << endl;

        }
    }

    return 0;
}