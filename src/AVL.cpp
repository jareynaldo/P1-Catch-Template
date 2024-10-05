#include "AVL.h"



bool MyAVLTree::isUFIDValid(const std::string& ufid) {
    return regex_match(ufid, std::regex("\\d{8}")); // must be 8 digits
}

bool MyAVLTree::isNameValid(const std::string& name) {
    return regex_match(name, std::regex("[a-zA-Z ]+")); // only conaints letters and spaces
}

// done
MyAVLTree::MyAVLTree() {
    root = nullptr;
}

// done
MyAVLTree::~MyAVLTree() {
    deletePostOrder(root);
    root = nullptr;
}



//done
void MyAVLTree::deletePostOrder(Node* node) {
    if (node == nullptr)
        return;

    deletePostOrder(node->left);
    deletePostOrder(node->right);

    delete node;
}




bool MyAVLTree::insertHelper(Node*& node, std::string name, std::string ufid) {
    if (node == nullptr) {
        node = new Node(name, ufid);
        node->height = 1;  // since new leaf
        return true;
    }

    // recursive insertion to the left or right
    if (ufid < node->ufid) {
        if (!insertHelper(node->left, name, ufid)) return false;
    } else if (ufid > node->ufid) {
        if (!insertHelper(node->right, name, ufid)) return false;
    } else {
        // UFID already exists, return false
        return false;
    }


    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    node = balance(node);

    return true;
}

//done
bool MyAVLTree::insert(std::string name, std::string ufid) {

    if (!isUFIDValid(ufid)) {
        std::cout << "unsuccessful" << std::endl;
        return false;
    }
    if (!isNameValid(name)) {
        std::cout << "unsuccessful" << std::endl;
        return false;
    }

    if (searchByID(ufid) != "") {
        std::cout << "unsuccessful" << std::endl;
        return false;
    }

    if (insertHelper(root, name, ufid)) {
        std::cout << "successful" << std::endl;
        return true;
    } else {
        std::cout << "unsuccessful" << std::endl;
        return false;
    }
}


// done
int MyAVLTree::getHeight(Node* node) {
    if (node == nullptr) return 0;

    return node->height;
}

// done
int MyAVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;

    return getHeight(node->left) - getHeight(node->right);
}

// Done
Node* MyAVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* MyAVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// done
Node* MyAVLTree::balance(Node* node) {
    if (node == nullptr) return nullptr;

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        // LR case
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        // RL case
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}


// done
Node* MyAVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

//
Node* MyAVLTree::deleteNode(Node* root, std::string ufid) {
    if (root == nullptr) return root;


    if (ufid < root->ufid)
        root->left = deleteNode(root->left, ufid);
    else if (ufid > root->ufid)
        root->right = deleteNode(root->right, ufid);
    else {
        // one child or none
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {

            Node* temp = minValueNode(root->right);

            root->ufid = temp->ufid;
            root->name = temp->name;

            root->right = deleteNode(root->right, temp->ufid);
        }
    }

    if (root == nullptr)
        return root;

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

    return balance(root);
}

// done
std::string MyAVLTree::searchByID(const std::string& UFID) const {
    Node* current = root;

    while (current != nullptr) {
        if (UFID == current->ufid) {
            return current->name;
        } else if (UFID < current->ufid) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    // id not found
    return "";
}

//done
void searchByNameHelper(const Node* node, const std::string& name, std::vector<std::string>& results) {
    if (node == nullptr) return;


    searchByNameHelper(node->left, name, results);

    if (node->name == name) {
        results.push_back(node->ufid);
    }

    searchByNameHelper(node->right, name, results);
}

//done
std::string MyAVLTree::searchByName(const std::string& name) const {
    std::vector<std::string> UFIDResults;

    // search entire tree
    searchByNameHelper(root, name, UFIDResults);


    if (UFIDResults.empty()) {
        return "unsuccessful";
    }

    // join all UFIDs and return
    std::string result;
    for (const std::string& ufid : UFIDResults) {
        result += ufid + "\n";
    }

    return result;
}



// done
bool MyAVLTree::remove(std::string ufid) {
    if (searchByID(ufid) == "") return false;


    root = deleteNode(root, ufid);
    return true;
}

//done
void MyAVLTree::inorderHelper(Node* node, bool &firstPrinted) {
    if (node == nullptr)
        return;

    inorderHelper(node->left, firstPrinted);

    if (!firstPrinted) {
        std::cout << ", ";
    }
    std::cout << node->name;
    firstPrinted = false;  // After the first element is printed, set the flag to false

    inorderHelper(node->right, firstPrinted);
}

void MyAVLTree::printInorder() {
    bool firstPrinted = true;
    inorderHelper(root, firstPrinted);
    std::cout << std::endl;
}

//done
void MyAVLTree::preorderHelper(Node* node, bool& firstPrinted) {
    if (node == nullptr)
        return;

    if (!firstPrinted) {
        std::cout << ", ";
    }
    std::cout << node->name;
    firstPrinted = false;

    preorderHelper(node->left, firstPrinted);
    preorderHelper(node->right, firstPrinted);
}

void MyAVLTree::printPreorder() {
    bool firstPrinted = true;
    preorderHelper(root, firstPrinted);
    std::cout << std::endl;
}

//done
void MyAVLTree::postorderHelper(Node* node, bool& firstPrinted) {
    if (node == nullptr)
        return;

    postorderHelper(node->left, firstPrinted);
    postorderHelper(node->right, firstPrinted);

    if (!firstPrinted) {
        std::cout << ", ";
    }
    std::cout << node->name;
    firstPrinted = false;
}

void MyAVLTree::printPostorder() {
    bool firstPrinted = true;
    postorderHelper(root, firstPrinted);
    std::cout << std::endl;
}


// done
int MyAVLTree::getLevelCount() {
    return getHeight(root);
}

void MyAVLTree::getInorderUFIDs(std::vector<std::string>& ufidList) const {
    collectInorderUFIDs(root, ufidList);
}

void MyAVLTree::collectInorderUFIDs(Node* node, std::vector<std::string>& ufidList) const {
    if (node == nullptr)
        return;

    collectInorderUFIDs(node->left, ufidList);
    ufidList.push_back(node->ufid);
    collectInorderUFIDs(node->right, ufidList);
}