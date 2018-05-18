#include "bstree.h"
using namespace BSTree;
Tree:: Tree ()
        :root {nullptr}
{}
Node:: Node (int val): data {val}, right {nullptr}, left {nullptr} {
}

bool Tree:: Empty() const  {
    return (root==nullptr? true : false);
}

Tree:: Tree (std::initializer_list<int> list) {
    root=nullptr;
    for (auto value:list) {
        Insert(value);
    }
}

Tree:: Tree (const Tree& tree) {
    this->root=nullptr;
    Copy(tree.root);
}

void Tree:: Copy(Node *curr)  {
    Insert(curr->data);
    if (curr->left!=nullptr) Copy(curr->left);
    if (curr->right!=nullptr) Copy(curr->right);
}

bool Tree:: Insert(int value) {
    if (root == nullptr) {
        root = new Node {value};
        return true;
    }
    Node * parent= root;
    Node * curr= root;
    while ( curr != nullptr) {
        if (curr->data==value) return false;
        if (curr->data < value) curr= curr->right;
        else curr= curr->left;
        if (curr!=nullptr) parent= curr;
    }
    if (parent->data< value) parent->right = new Node {value};
    else parent->left = new Node {value};
    return true;
}

void Tree:: Print(Node *curr, int space) const {
    if (curr!=nullptr) {
        if (curr->right!=nullptr) Print(curr->right, space + 1);
        for (int i=0; i< space; i++) {
            std::cout<< "   ";
        }
        if ((curr->data)!=(root->data))
            std::cout<< "--";
        std::cout<< curr->data << std::endl;
        if (curr->left!=nullptr) Print(curr->left, space + 1);
    }
    else std::cout<<"Дерево не содержит элементов!"<< std::endl;
}

void Tree:: Print() const  {
    Print(root, 0);
}

void Tree:: Delete(Node *&curr) {
    if (curr==nullptr) return;
    if (curr->right!=nullptr)
        Delete(curr->right);
    if (curr-> left!= nullptr) Delete(curr->left);
    delete curr;
    curr = nullptr;
}

void Tree:: Straight(Node *curr) const {
    std::cout<< curr->data<< " ";
    if (curr->left!=nullptr) Straight(curr->left);
    if (curr->right!=nullptr) Straight(curr->right);
}

void Tree:: Reverse(Node *curr) const {
    if (curr->left!=nullptr) Reverse(curr->left);
    if (curr->right!=nullptr) Reverse(curr->right);
    std::cout<< curr->data<<" ";
}

void Tree:: Transverse(Node *curr) const {
    if (curr->left!=nullptr) Transverse(curr->left);
    std::cout<< curr->data<<" ";
    if (curr->right!=nullptr) Transverse(curr->right);
}

void Tree:: Print(traversal_order order) const {

    switch (order) {
        case traversal_order::pre :
            Straight(root);
            break;
        case traversal_order::in :
            Transverse(root);
            break;
        case traversal_order::post:
            Reverse(root);
            break;
    }
}

Tree:: ~Tree() {
    Delete(root);
}

void Tree:: Add(int value) {
    if (!(this->Insert(value)))
    {
        std::cerr << "Дерево уже существует!" << std::endl;
    }
}

bool Tree:: Remove(int value) {
    if ((root->right==nullptr)&& (root->left==nullptr) && (root->data==value)) {
        delete root;
        root= nullptr;
        return true;
    }
    Node * Parent= root;
    Node * curr= root;
    Node * ParentDel =root;
    int ValueNew;
    while (curr!=nullptr) {
        if (curr->data==value) break;
        ParentDel= curr;
        if (curr->data> value) curr= curr->left;
        else {
            if (curr->data< value) curr= curr->right;
        }
    } // нашли удаляемый узел и его родителя
    if (curr==nullptr)
        return false; //узел не существует в дереве
    if (curr->left!=nullptr) {
        Parent = curr;
        curr= curr->left;
        while (1) {
            if (curr->right != nullptr) {
                Parent= curr;
                curr = curr->right;
            }
            if (curr->right==nullptr)  break;
        }
        ValueNew= curr->data;
        if ((Parent->left!=nullptr) && (Parent->left->data==ValueNew)) {
            delete Parent->left;
            Parent->left=nullptr;
        }
        else {
            delete Parent->right;
            Parent->right= nullptr;
        }
    }
    else {
        if (curr->right!=nullptr) {
            Parent = curr;
            curr= curr->right;
            while (1) {
                if (curr->left != nullptr) {
                    Parent= curr;
                    curr = curr->left;
                }
                if (curr->left==nullptr)  break;
            }
            ValueNew= curr->data;
            if ((Parent->right!=nullptr) && (Parent->right->data==ValueNew)) {
                delete Parent->right;
                Parent->right=nullptr;
            }
            else {
                delete Parent->left;
                Parent->left= nullptr;
            }
        }
        else {
            if (ParentDel->data> value) {
                delete ParentDel->left;
                ParentDel->left=nullptr;
                return true;
            }
            delete ParentDel->right;
            ParentDel->right=nullptr;
            return true;
        }       
    }
    if (ParentDel->data> value)
        ParentDel->left->data = ValueNew;
    if (ParentDel->data < value)
        ParentDel->right->data = ValueNew;
    if (ParentDel->data==value)
        root->data= ValueNew;
    return true;
}

void Tree:: SaveRecursion(Node *curr, int space, std::ostream &File) {
    if (curr!=nullptr) {
        if (curr->right!=nullptr) SaveRecursion(curr->right, space + 1, File);
        for (int i=0; i< space; i++) {
            File<< "   ";
        }
        if ((curr->data)!=(root->data))
            File<< "--";
        File<< curr->data << std::endl;
        if (curr->left!=nullptr) SaveRecursion(curr->left, space + 1, File);
    }
}

void Tree:: SaveStraight(Node *curr, std::ostream &File) {
    File<< curr->data<< " ";
    if (curr->left!=nullptr) SaveStraight(curr->left, File);
    if (curr->right!=nullptr) SaveStraight(curr->right, File);
}

bool Tree:: Save(const std::string &path) {
    std::ifstream File1(path) ;
    long file_size;
    File1.seekg(0, std::ios::end);
    file_size = File1.tellg();
    File1.close();
    std::ofstream File(path);
    std::string decision ="yes";
    if ((file_size!=-1) && (file_size!=0))  {
        std::cout << "Вы хотите перезаписать файл? (yes/no)" << std::endl;
        std::cin >> decision;
    }
    File.close();
    File.open (path);
    if ((decision == "y") || (decision == "yes") || (decision == "Y") ||
        (decision == "Yes") || (decision == "YES"))
    {
        SaveStraight(root, File);
        File<< std::endl;
        SaveRecursion(root, 0, File);
    }
    File.close();
    return true;
}

bool Tree:: Load(const std::string &path) {
    std::ifstream File(path);
    if (!File.is_open()) return false;
    std::string tree_string;
    getline (File,tree_string);
    int elements_count=0;
    for (int i=0; i< tree_string.length(); i++) {
        if (tree_string[i]==' ') elements_count++;
    }
    File.close();
    File.open(path);
    for (int i=0; i<elements_count; i++) {
        File >> tree_string;
        this->Insert(atoi(tree_string.c_str()));
    }
    File.close();
    return true;
}

bool Tree:: Exists(int value) const {
    Node * curr = root;
    while (curr!=nullptr) {
        if (curr->data==value) return true;
        if (curr->data > value) curr=curr->left;
        else curr=curr->right;
    }
    return false;
}

void Tree::ForOperaor(std::ostream &stream, Node *curr) {
    stream<< curr->data<< " ";
    if (curr->left!=nullptr) ForOperaor(stream, curr->left);
    if (curr->right!=nullptr) ForOperaor(stream, curr->right);
}

auto Tree::operator=(const Tree& tree) -> Tree& {
    Delete(this->root);
    Copy(tree.root);
    return *this;
}
