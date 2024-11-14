//#include <iostream>
//#include <queue>
//using namespace std;
//template <typename K, typename V>
//class SpecialBST {
//private:
//    struct Treenode {
//        K key;
//        V value;
//        Treenode* left;
//        Treenode* right;
//
//        Treenode(K key1, V val) {
//            key = key1;
//            value = val;
//            left = right = nullptr;
//        }
//    };
//    Treenode* lastnode;
//    Treenode* root;
//
//    void rightRotate(Treenode*& node) {
//        Treenode* temp = node->left;
//        node->left = temp->right;
//        temp->right = node;
//        node = temp;
//    }
//
//    void leftRotate(Treenode*& node) {
//        Treenode* temp = node->right;
//        node->right = temp->left;
//        temp->left = node;
//        node = temp;
//    }
//
//  
//    void splay(Treenode*& node, K key) {
//        if (node == nullptr || node->key == key)
//            return;
//
//        
//        if (key < node->key) {
//            if (node->left == nullptr) return;
//
//            if (key < node->left->key) {
//                splay(node->left->left, key);
//                rightRotate(node);
//            }
//            else if (key > node->left->key) {
//                splay(node->left->right, key);
//                if (node->left->right != nullptr)
//                    leftRotate(node->left);
//            }
//
//            if (node->left == nullptr) return;
//            rightRotate(node);
//        }
//      
//        else {
//            if (node->right == nullptr) return;
//
//            if (key > node->right->key) {
//                splay(node->right->right, key);
//                leftRotate(node);
//            }
//            else if (key < node->right->key) {
//                splay(node->right->left, key);
//                if (node->right->left != nullptr)
//                    rightRotate(node->right);
//            }
//
//            if (node->right == nullptr) return;
//            leftRotate(node);
//        }
//    }
//
//public:
//    SpecialBST() : root(nullptr), lastnode(nullptr) {}
//    ~SpecialBST() {
//        destroyTree(root);
//    }
//
//    void destroyTree(Treenode* node) {
//        if (node == nullptr) {
//            return;
//        }
//
//        destroyTree(node->left);
//        destroyTree(node->right);
//
//        delete node;
//    }
//
//    void insertNode(Treenode*& node, K key, V value) {
//        if (node == nullptr) {
//            node = new Treenode(key, value);
//            lastnode = node;
//            return;
//        }
//
//        if (key < node->key) {
//            insertNode(node->left, key, value);
//        }
//        else if (key > node->key) {
//            insertNode(node->right, key, value);
//        }
//        else {
//            return;
//        }
//
//        splay(root, key);
//    }
//
//    Treenode* find_parent(K value) {
//        Treenode* cur = nullptr;
//        Treenode* temp = root;
//        while (temp != nullptr) {
//            if (value == temp->key) {
//                break;
//            }
//            else if (value < temp->key) {
//                cur = temp;
//                temp = temp->left;
//            }
//            else {
//                cur = temp;
//                temp = temp->right;
//            }
//        }
//        return cur;
//    }
//
//    void get_values_inorder(Treenode* node) {
//        if (node != nullptr) {
//            get_values_inorder(node->left);
//            cout << node->value<<" ";
//          
//            get_values_inorder(node->right);
//        }
//    }
//
//    bool search_key(K key, Treenode* temp) {
//        if (!temp) {
//            return false;
//        }
//        if (key == temp->key) {
//            lastnode = temp;
//            return true;
//        }
//        else if (key > temp->key) {
//            return search_key(key, temp->right);
//        }
//        else {
//            return search_key(key, temp->left);
//        }
//    }
//
//    bool search(K key) {
//        if (!root) {
//            return false;
//        }
//        bool found = search_key(key, root);
//        if (found) {
//            splay(root, key);
//        }
//        return found;
//    }
//
//    int numOfChild(Treenode* curr) {
//        if (curr == nullptr) return -1;
//        else return int(curr->left != nullptr) + int(curr->right != nullptr);
//    }
//
//    bool remove_node(K key, Treenode*& curr) {
//        if (curr == nullptr) return false;
//
//        if (key < curr->key) {
//            return remove_node(key, curr->left);
//        }
//        else if (key > curr->key) {
//            return remove_node(key, curr->right);
//        }
//        else {
//            lastnode = find_parent(key);
//
//            if (numOfChild(curr) == 0) {
//                delete curr;
//                curr = nullptr;
//            }
//            else if (numOfChild(curr) == 1) {
//                Treenode* temp = curr;
//                if (curr->left != nullptr) {
//                    curr = curr->left;
//                }
//                else {
//                    curr = curr->right;
//                }
//                delete temp;
//            }
//            else {
//                Treenode* successor = curr->right;
//                while (successor->left != nullptr) {
//                    successor = successor->left;
//                }
//
//                curr->key = successor->key;
//                curr->value = successor->value;
//
//                remove_node(successor->key, curr->right);
//            }
//
//            return true;
//        }
//    }
//
//    bool remove(K key) {
//        if (!root) {
//            return false;
//        }
//        bool removed = remove_node(key, root);
//        if (removed) {
//            splay(root, key);
//        }
//        return removed;
//    }
//
//    bool insert(K key, V value) {
//        insertNode(root, key, value);
//        splay(root, key);
//        return true;
//    }
//
//    int getRoot() {
//        return root->key;
//    }
//
//    Treenode* getr() {
//        return root;
//    }
//
//    Treenode* getl() {
//        return lastnode;
//    }
//
//    K getlastnode() {
//        return lastnode->key;
//    }
//
//    void inorder() {
//        get_values_inorder(root);
//    }
//
//    void get_values_levelOrder() {
//        if (root == nullptr) {
//            return;
//        }
//
//        queue<Treenode*> q;
//        q.push(root);
//
//        while (!q.empty()) {
//            Treenode* currentNode = q.front();
//            q.pop();
//
//            cout << currentNode->key << " ";
//
//            if (currentNode->left != nullptr) {
//                q.push(currentNode->left);
//            }
//
//            if (currentNode->right != nullptr) {
//                q.push(currentNode->right);
//            }
//        }
//    }
//};
//
//
//
//
//int main() {
//    SpecialBST<int, string> bst;
//
//    bst.insert(3, "3");
//    bst.insert(2, "2");
//    bst.insert(4, "4");
//    bst.insert(2, "2");
//    bst.insert(10, "10");
//    bst.insert(20, "20");
// 
//
//
//    cout << "Level order traversal and inorder of the BST: ";
//    bst.get_values_levelOrder();
//    cout << endl;
//    bst.get_values_inorder(bst.getr());
//    cout << endl;
//    cout << endl;
//    cout << "After insertion of 5 " << endl;
//    bst.insert(5, "5");
//    cout << endl;
//    bst.get_values_levelOrder();
//    cout << endl;
//
//}