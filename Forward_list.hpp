#ifndef FORWARDLIST_H
#define FORWARDLIST_H
#include "Container.hpp"

template <typename T>
class Forward_list: public Container<T>{
private:
    struct Node;
    Node* first_element;
    Node* last_element;
public:
    class Iterator;
    class const_Iterator;
    typedef Iterator iterator;
    typedef const_Iterator const_iterator;
    Forward_list();
    Forward_list(const Forward_list& l);
    ~Forward_list();
    void delete_list();
    void insert(const T& value);
    void Push_back(const T& value);
    void remove(const T& value);
    bool exists(const T& value) const;
    Forward_list& operator=(const Forward_list& l);
    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();
    unsigned int size() const;
};
#include "Forward_list_impl.hpp"
#endif // FORWARDLIST_H
