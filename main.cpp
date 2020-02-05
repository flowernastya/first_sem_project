#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <iomanip>

class Treap{
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
    Tree* root;
public:
    Treap(): root(nullptr){}
    Treap(long long value){
        root = new_tree(value);
    }
    void add(long long value){
        add_in_tree(root, value);
    }
    bool check(long long value){
        return check_in_tree(root, value);
    }
    ~Treap(){
        delete_my_tree(root);
    }
};



    void build_treap(Treap &treap, int n){
        for(int i = 0; i < n; i++){
            long long x;
            std::cin >> x;
            treap.add(x);
        }
    }
    long long find(Treap &treap, int m){
        int start_time, end_time;
        long long time(0);
        long long value;
        for(int j = 0; j < m / 2; ++j){
            std::cin >> value;
            start_time = std::clock();
            bool flag = treap.check(value);
            end_time = std::clock();
            time += end_time - start_time;
        }
        return time;
    }
    long long insert(Treap  &treap, int m){
        int start_time, end_time;
        long long value, time(0);
        for(int j = 0; j < m / 2; ++j){
            std::cin >> value;
            start_time = std::clock();
            treap.add(value);
            end_time = std::clock();
            time += end_time - start_time;
        }
        return time;
    }
int main()
{
   freopen("keke.in", "r", stdin);
  //  freopen("sum.out", "w", stdout);
    long long n, m;
    std::cout << std::fixed << std::setprecision(10);
    for(int i = 0; i < 5; ++i){
        Treap treap;
        std::cin >> n;
        std::cout << n << std::endl;
        build_treap(treap, n);
        std::cin >> m;
        long long time =find(treap, m);
        long double number = m / 2;
        long double t = time;
        t /= number * CLOCKS_PER_SEC;
        std::cout << "search time: " << t << std::endl;
        time = insert(treap, m);
        t = time;
        t /=  number * CLOCKS_PER_SEC;
        std::cout << "insert time: " << t << std::endl;
    }

   // std::cout << sum(s, std::min(a, b), std::max(a, b));

    return 0;
}
