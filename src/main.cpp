#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "AVL.h"


using namespace std;

bool isUFIDValid(const string& ufid) {
    return regex_match(ufid, regex("\\d{8}")); // must be 8 digits
}

bool isNameValid(const string& name) {
    return regex_match(name, regex("[a-zA-Z ]+")); // only conaints letters and spaces
}
int commandToNumber(const string& command) {
    if (command == "insert") return 1;
    if (command == "remove") return 2;
    if (command == "search") return 3;
    if (command == "printInorder") return 4;
    if (command == "printPreorder") return 5;
    if (command == "printPostorder") return 6;
    if (command == "printLevelCount") return 7;
    if (command == "removeInorder") return 8;
    return 0; // for unsuccessful or invalid commands
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

        int cmd = commandToNumber(command);
        switch (cmd) {
            case 1: { // insert
                string name, ufid;
                char quote;
                in >> quote;
                getline(in, name, '"');
                in >> ufid;

                if (quote == '"' && isNameValid(name) && isUFIDValid(ufid)) {
                    tree.insert(name, ufid);
                }
                break;
            }
            case 2: { // remove
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
                break;
            }
            case 3: { // search
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
                break;
            }
            case 4: // printInorder
                tree.printInorder();
                break;

            case 5: // printPreorder
                tree.printPreorder();
                break;

            case 6: // printPostorder
                tree.printPostorder();
                break;

            case 7: // printLevelCount
                cout << tree.getLevelCount() << endl;
                break;

            case 8: { // removeInorder
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
                break;
            }
            default:
                cout << "unsuccessful" << endl;
                break;
        }
    }

    return 0;
}