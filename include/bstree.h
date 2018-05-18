#include <iostream>
#include <initializer_list>
#include <cstddef>
namespace BSTree {
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val);
    };
    enum class traversal_order {pre, in, post};
    class Tree {
        Node* root;
        void Print(Node *curr, int space) const;
        void Delete(Node *&curr);
        void Straight(Node *curr) const;
        void Reverse(Node *curr) const;
        void Transverse(Node *curr) const;
        void SaveRecursion(Node *curr, int space, std::ostream &File);
        void SaveStraight(Node *curr, std::ostream &File);
        void Copy(Node *curr);
        void ForOperaor(std::ostream &stream, Node *curr);

    public:
        Tree();
        Tree(std::initializer_list<int> list);
        Tree(const Tree& tree);
        bool Insert(int value);
        void Print() const;
        bool Empty() const;
        void Add(int value);
        bool Remove(int value);
        bool Save(const std::string &path);
        bool Load(const std::string &path);
        bool Exists(int value) const;
        void Print(traversal_order order) const;
        auto operator=(const Tree&) -> Tree&;
        ~Tree();
        auto friend operator<<(std::ostream& stream, Tree& tree) -> std::ostream&
        {
            tree.ForOperaor(stream, tree.root);
            return stream;
        }
    };
}
