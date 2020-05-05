#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H
#include "Container.hpp"
#include "Forward_list.hpp"
#include <stdexcept>
#include <iterator>

template <typename T>
class Forward_list<T>::const_Iterator{
    Node* node;
public:
    friend class Forward_list<T>;
    const_Iterator();
    const_Iterator(Node* _node);
    ~const_Iterator();
    typedef size_t difference_type;
    typedef T value_type;
    typedef const T& reference;
    typedef const Node* pointer;
    typedef std::forward_iterator_tag iterator_category;
    reference operator*() const;

    bool operator==(const const_Iterator& it) const;
    bool operator!=(const const_Iterator& it) const;
        const_Iterator& operator++();
    const_Iterator operator++(value_type);
};
#include "Const_iterator_impl.hpp"
#endif // CONSTITERATOR_H
