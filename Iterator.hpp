#ifndef ITERATOR_H
#define ITERATOR_H
#include "Container.hpp"
#include "Forward_list.hpp"
#include <stdexcept>
#include <iterator>

template <typename T>
class Forward_list<T>::Iterator{
    Node *node;
public:
    friend class Forward_list<T>;
    Iterator();
    Iterator(Node* _node);
    ~Iterator();
    typedef size_t difference_type;
    typedef T value_type;
    typedef Node* pointer;
    typedef T& reference;
    typedef std::forward_iterator_tag iterator_category;
    reference operator*();
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;
    Iterator& operator++();
    Iterator operator++(value_type);
};
#include "Iterator_impl.hpp"
#endif // ITERATOR_H
