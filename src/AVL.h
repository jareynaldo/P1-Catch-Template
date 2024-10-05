#include <string>
#ifndef P1DEMO_AVL_H
#define P1DEMO_AVL_H
#include <iostream>
#include  <vector>
#include <regex>

struct Node{
    //node attributes
    std::string name;
    std::string ufid;
    Node* left; 
    Node* right;
    int height;

    Node(std::string name, std::string ufid){
        this-> name = name;
        this-> ufid = ufid;
        this->left= nullptr;
        this->right = nullptr;
        this->height = 1;
    }

};


class MyAVLTree {
private:
    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    bool insertHelper(Node*& node, std::string name, std::string ufid);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* minValueNode(Node* node);

    Node *deleteNode(Node *root, std::string ufid);

    Node* removeByUFID(Node* root, std::string UFID);
    Node* balance(Node* node);

    void postorderHelper(Node* node);
    void collectInorderUFIDs(Node* node, std::vector<std::string>& ufidList) const;




public: 

    MyAVLTree();
    ~MyAVLTree();

    bool isUFIDValid(const std::string& ufid);
    bool isNameValid(const std::string& name);

    void deletePostOrder(Node *node);

    bool insert(std::string name, std::string ufid);


    bool remove(std::string ufid);

    void inorderHelper(Node *node, bool &firstPrinted);


    void printInorder();

    void preorderHelper(Node *node, bool &firstPrinted);

    std::string searchByID(const std::string& ufid) const;
    std::string searchByName(const std::string& name) const;





    void printInorder(Node* node, bool& firstPrinted);
    void printPreorder();

    void postorderHelper(Node *node, bool &firstPrinted);

    void printPostorder();
    int getLevelCount();
    void getInorderUFIDs(std::vector<std::string>& ufidList) const;








};

#endif