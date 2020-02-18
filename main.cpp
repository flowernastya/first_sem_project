#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iomanip>

class Container{
public:
    virtual void insert(long long value) = 0;
    virtual bool exists(long long value) = 0;
    virtual void remove(long long value) = 0;
    virtual void print() = 0;
    virtual ~Container() { };
};

class Treap: public Container {
    long long rand_L(){
      //  std::srand(std::time(nullptr));
        long long rz = rand();
        for(int i = 0; i < 3; i++){
            rz = rz << 16;
            rz += rand();
        }
        return rz;
    }
    struct Tree{
        long long key, priority, sum;
        Tree *left, *right;

    };
    Tree* new_tree(long long value){
        Tree *tree = new Tree;
        tree -> key = value;
        tree -> sum = value;
        tree -> priority = rand_L();
        tree -> left = nullptr;
        tree -> right = nullptr;
        return tree;
    }
    void update(Tree * tree){
        if(!tree)
            return;
        tree -> sum = tree -> key;
        if(tree -> left)
            tree -> sum += tree -> left -> sum;
        if(tree -> right)
            tree -> sum += tree -> right -> sum;
    }
    void split(Tree *tree, long long key, Tree* &left, Tree* &right){
        if(!tree){
            left = right = nullptr;
            return;
        }
        if(tree -> key <= key){
            left = tree;
            split(left -> right, key, left -> right, right);
            update(left);
        }
        else{
            right = tree;
            split(right -> left, key, left, right -> left);
            update(right);
        }
    }
    Tree * merge( Tree* left, Tree* right){
        if(!left)
            return right;
        if(!right)
            return left;
        if(left -> priority > right -> priority){
            left -> right = merge(left -> right, right);
            update(left);
            return left;
        }
        right -> left = merge(left, right -> left);
        update(right);
        return right;
    }
    bool check_in_tree(Tree* &treap, long long key){
        Tree* left = nullptr;
        Tree* right = nullptr;
        Tree* l = nullptr;
        Tree* ans = nullptr;
        bool check(0);
        split(treap, key, l, right);
        split(l, key - 1, l, ans);
        if(ans)
            check = 1;
        left = merge(l, ans);
        treap = merge(left, right);
        return check;
    }
    void add_in_tree(Tree* &treap, long long key){
        Tree* new_element = new_tree(key);
        Tree* left = nullptr;
        Tree* right = nullptr;
        Tree* l = nullptr;
        Tree* ans = nullptr;
        split(treap, key, l, right);
        split(l, key - 1, l, ans);
        if(!ans)
            ans = new_element;
        else
            delete new_element;
        left = merge(l, ans);
        treap = merge(left, right);
    }
    void remove_from_tree(Tree* &treap, long long key){
      //  Tree* left = nullptr;
        Tree* right = nullptr;
        Tree* l = nullptr;
        Tree* ans = nullptr;
        split(treap, key, l, right);
        split(l, key - 1, l, ans);
        delete ans;
        treap = merge(l, right);
    }
    long long sum(Tree* &treap, long long left_key, long long right_key){
        Tree* left = nullptr;
        Tree* l = nullptr;
        Tree* right = nullptr;
        Tree* ans = nullptr;
        split(treap, right_key, left, right);
        split(left, left_key - 1, l, ans);
        long long answer(0);
        if(ans)
            answer = ans -> sum;
        left = merge(l, ans);
        treap = merge(left, right);
        return answer;
    }
    void delete_my_tree(Tree* &treap){
        if(!treap)
            return;
        delete_my_tree(treap -> left);
        delete_my_tree(treap -> right);
        delete treap;
    }
    void print_tree(Tree* &treap){
        if(!treap)
            return;
        print_tree(treap -> left);
        print_tree(treap ->right);
        std::cout << treap -> key << ' ';
    }
    Tree* root;
    bool p;
public:
    Treap(): root(nullptr) {}
    Treap(long long value){
        root = new_tree(value);
    }
    void insert(long long value){
        add_in_tree(root, value);
    }
    bool exists(long long value){
        return check_in_tree(root, value);
    }
    void remove(long long value){
        return remove_from_tree(root, value);
    }
    void print(){
        print_tree(root);
        std::cout << std::endl;
    }
    ~Treap(){
        delete_my_tree(root);
    }
};

int main()
{
  // freopen("keke.in", "r", stdin);
    //freopen("sum.out", "w", stdout);
    Container* c = new Treap;

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    std::cout << "Container after creation:" << std::endl;
    c->print();

    if(c->exists(25))
        std::cout << "Search for value 25: found" << std::endl;

    if(!c->exists(111))
        std::cout << "Search for value 111: not found" << std::endl;

    c->remove(25);
    std::cout << "Container after deletion of the element:" << std::endl;
    c->print();

    delete c;

    //std::cout << sum(s, std::min(a, b), std::max(a, b));

    return 0;
}
