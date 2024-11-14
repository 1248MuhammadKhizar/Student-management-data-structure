#include <iostream>
#include <queue>
using namespace std;


struct Student {
    int rollNumber;
    string firstName;
    string lastName;
    int batch;
    string department;
    float cgpa;
    Student() : rollNumber(0), firstName(""), lastName(""), batch(0), department(""), cgpa(0.0f) {}
    Student(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
        : rollNumber(rollNumber), firstName(firstName), lastName(lastName),
        batch(batch), department(department), cgpa(cgpa) {}

    void print() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Batch: " << batch << endl;
        cout << "Department: " << department << endl;
        cout << "CGPA: " << cgpa << endl;
    }
   
    void update_student(int RollNumber, string FirstName, string LastName, int Batch, string Department, float Cgpa)
    {
        rollNumber = RollNumber;
        firstName = FirstName;
        lastName = LastName;
        batch = Batch;
        department = Department;
        cgpa = Cgpa;

    }
    

    
};


template <typename K, typename V>
class SpecialBST {
private:
    struct Treenode {
        K key;
        V value;
        Treenode* left;
        Treenode* right;

        Treenode(K key1, V val) {
            key = key1;
            value = val;
            left = right = nullptr;
        }
    };
    Treenode* lastnode;
    Treenode* root;

    void rightRotate(Treenode*& node) {
        Treenode* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }

    void leftRotate(Treenode*& node) {
        Treenode* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }

    // Splay operation to bring the accessed node to the root
    void splay(Treenode*& node, K key) {
        if (node == nullptr || node->key == key)
            return;

        // Key lies in the left subtree
        if (key < node->key) {
            if (node->left == nullptr) return;

            if (key < node->left->key) {
                splay(node->left->left, key);
                rightRotate(node);
            }
            else if (key > node->left->key) {
                splay(node->left->right, key);
                if (node->left->right != nullptr)
                    leftRotate(node->left);
            }

            if (node->left == nullptr) return;
            rightRotate(node);
        }
        // Key lies in the right subtree
        else {
            if (node->right == nullptr) return;

            if (key > node->right->key) {
                splay(node->right->right, key);
                leftRotate(node);
            }
            else if (key < node->right->key) {
                splay(node->right->left, key);
                if (node->right->left != nullptr)
                    rightRotate(node->right);
            }

            if (node->right == nullptr) return;
            leftRotate(node);
        }
    }

public:
    SpecialBST() : root(nullptr), lastnode(nullptr) {}
    ~SpecialBST() {
        destroyTree(root);
    }

    void destroyTree(Treenode* node) {
        if (node == nullptr) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);

        delete node;
    }

    void insertNode(Treenode*& node, K key, V value) {
        if (node == nullptr) {
            node = new Treenode(key, value);
            lastnode = node;
            return;
        }

        if (key < node->key) {
            insertNode(node->left, key, value);
        }
        else if (key > node->key) {
            insertNode(node->right, key, value);
        }
        else {
            return;
        }

        splay(root, key);
    }

    Treenode* find_parent(K value) {
        Treenode* cur = nullptr;
        Treenode* temp = root;
        while (temp != nullptr) {
            if (value == temp->key) {
                break;
            }
            else if (value < temp->key) {
                cur = temp;
                temp = temp->left;
            }
            else {
                cur = temp;
                temp = temp->right;
            }
        }
        return cur;
    }

    void get_values_inorder(Treenode* node) {
        if (node != nullptr) {
            get_values_inorder(node->left);
             node->value.print();
             cout << endl;
            get_values_inorder(node->right);
        }
    }

    bool search_key(K key, Treenode* temp) {
        if (!temp) {
            return false;
        }
        if (key == temp->key) {
            lastnode = temp;
            return true;
        }
        else if (key > temp->key) {
            return search_key(key, temp->right);
        }
        else {
            return search_key(key, temp->left);
        }
    }

    bool search(K key) {
        if (!root) {
            return false;
        }
        bool found = search_key(key, root);
        if (found) {
            splay(root, key);
        }
        return found;
    }

    int numOfChild(Treenode* curr) {
        if (curr == nullptr) return -1;
        else return int(curr->left != nullptr) + int(curr->right != nullptr);
    }

    bool remove_node(K key, Treenode*& curr) {
        if (curr == nullptr) return false;

        if (key < curr->key) {
            return remove_node(key, curr->left);
        }
        else if (key > curr->key) {
            return remove_node(key, curr->right);
        }
        else {
            lastnode = find_parent(key);

            if (numOfChild(curr) == 0) {
                delete curr;
                curr = nullptr;
            }
            else if (numOfChild(curr) == 1) {
                Treenode* temp = curr;
                if (curr->left != nullptr) {
                    curr = curr->left;
                }
                else {
                    curr = curr->right;
                }
                delete temp;
            }
            else {
                Treenode* successor = curr->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }

                curr->key = successor->key;
                curr->value = successor->value;

                remove_node(successor->key, curr->right);
            }

            return true;
        }
    }

    bool remove(K key) {
        if (!root) {
            return false;
        }
        bool removed = remove_node(key, root);
        if (removed) {
            splay(root, key);
        }
        return removed;
    }

    bool insert(K key, V value) {
        insertNode(root, key, value);
        splay(root, key);
        return true;
    }

    int getRoot() {
        return root->key;
    }

    Treenode* getr() {
        return root;
    }

    Treenode* getl() {
        return lastnode;
    }

    K getlastnode() {
        return lastnode->key;
    }

    void inorder() {
        get_values_inorder(root);
    }

    void get_values_levelOrder() {
        if (root == nullptr) {
            return;
        }

        queue<Treenode*> q;
        q.push(root);

        while (!q.empty()) {
            Treenode* currentNode = q.front();
            q.pop();

            cout << currentNode->key << " ";

            if (currentNode->left != nullptr) {
                q.push(currentNode->left);
            }

            if (currentNode->right != nullptr) {
                q.push(currentNode->right);
            }
        }
    }
};


//------------------------------    part b ---------------------------------------------

    class list
    {
    private:
        SpecialBST<int, Student> bst;

    public:
        list()
        {

        }

        bool insert(int rollNumber, string firstName, string lastName, int batch, string department, float cgpa)
        {
            Student s1(rollNumber, firstName, lastName, batch, department, cgpa);
           return bst.insert(rollNumber, s1);
        }
        bool deleteStudent(int rollNumber) {
            return bst.remove(rollNumber);
        }

        void displayStudentslevel() {
            bst.get_values_levelOrder();
        }
        void displayStudentsinorder()
        {
            bst.get_values_inorder(bst.getr());
        }
        bool searchStudent(int rollNumber) {
            bool a = bst.search(rollNumber);
            if (a) {
                cout << "Student found with roll number " << rollNumber << endl;
                bst.getl()->value.print();
                return true;
            }
            else
            {
                cout << "Unique roll number !" << endl;
                return false;
            }
       
           
        }
        bool update( int newRollNumber, string
            newFirstName, string newLastName, int newBatch, string
            newDepartment, float newCgpa)
        {
            bool a = bst.search(newRollNumber);
            if (a)
            {
                cout << "The new roll number you have entered already exists " << endl;
                return false;
            }
            else
            {
                Student s1(newRollNumber,newFirstName,newLastName,newBatch,newDepartment,newCgpa);
                bst.insert(newRollNumber, s1);
            }

            return true;
        }

    };


int main() {
  

   


    list students;

     cout << "DO YOU WANT TO INSERT A NEW STUDENT " << endl;
     cout << "Press I for insertion D for deletion S for selecting a Student by a roll number  U for updating a student data  M for displaying roll numbers according to sorted order  E for exit " << endl;
     char choice;
     cin >> choice;
     do {
         if (choice == 'i' || choice == 'I')
         {
             cout << "Enter roll number" << endl;
             int b;
             cin >> b;
             bool a = students.searchStudent(b);
             if (a)
             {
                 cout << "The roll number you have tried already exists " << endl;
                 return 0;
             }
             if (b < 0)
             {
                 cout << "Entered Invalid Roll Number " << endl;
                 return 0;
             }
             cout << endl;
             cout << "Enter first name " << endl;
             string c;
             cin >> c;
             cout << "Enter last name " << endl;
             string d;
             cin >> d;

             cout << " enter year of admission " << endl;
             int e;
             cin >> e;

             cout << "Enter CGPA " << endl;
             float z;
             cin >> z;
             if (z < 0 || z > 4.0)
             {
                 
                 cout << "Enter correct GPA " << endl;
                 while (z < 0 || z > 4.0)
                 {
                     cin >> z;
                 }
             }
             students.insert(b, c, d, e, "Computer Scence", z);
         }
         else if (choice == 'd' || choice =='D')
         {
             cout << "Enter roll number to delete " << endl;
             int b;
             cin >> b;
             if (students.deleteStudent(b))
             {
                 cout << "Student deleted " << endl;
            }
             else
             {
                 cout << "Student not found" << endl;
             }
         }
         else if (choice == 'S' || choice =='s')
         {
            
             cout << "Enter old roll number of a student " << endl;
             int b;
             cin >> b;
             if (b < 0)
             {
                 cout << "Entered wrong number " << endl;
                 return 0;
             }
             students.searchStudent(b);
         }
         else if (choice == 'U' || choice == 'u')
         {
             system("cls");
             cout << "Enter old roll number" << endl;
             int b;
             cin >> b;
             bool a = students.searchStudent(b);
             if (a)
             {
                 students.deleteStudent(b);
            }
             else
             {
                 cout << "The roll number you are trying to pdate does not exists" << endl;
                 return 0;
             }
             if (b < 0)
             {
                 cout << "Entered Invalid Roll Number " << endl;
                 return 0;
             }

             int x;
             cout << "Enter new roll number ";
             cin >> x;
             cout << endl;
             cout << "Enter new first name " << endl;
             string c;
             cin >> c;
             cout << "Enter new last name " << endl;
             string d;
             cin >> d;

             cout << " new enter year of admission " << endl;
             int e;
             cin >> e;

             cout << "new Enter CGPA " << endl;
             float z;
             cin >> z;
             if (z < 0 || z > 4.0)
             {

                 cout << "Enter correct GPA " << endl;
                 while (z < 0 || z > 4.0)
                 {
                     cin >> z;
                 }
             }
             students.update( x, c, d, e,"Computer Science", z);

         }
         else if (choice == 'M' || choice == 'm')
         {
             system("cls");
             students.displayStudentsinorder();
             }
         if (choice == 'I' || choice =='i') {
             system("cls");
         }
         cout << "Press I for insertion D for deletion S for selecting a Student by a roll number U for updating data of a student  m for displaying sorted list " << endl;
         cout << "Enter choice again " << endl;
         cin >> choice;
     } while (choice != 'e');
 


}