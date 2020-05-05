#include "Container.hpp"
#include "Forward_list.hpp"
#include <stdexcept>
#include <iterator>
#include "Const_iterator.hpp"

template <typename T>
Forward_list<T>::const_Iterator::const_Iterator() {}
template <typename T>
Forward_list<T>::const_Iterator::const_Iterator(Node* _node): node(_node) {}
template <typename T>
Forward_list<T>::const_Iterator::~const_Iterator() { }

template <typename T>
typename Forward_list<T>::const_Iterator::reference Forward_list<T>::const_Iterator::operator*() const{
    if(!node)
        throw std::runtime_error("dereferencing a null pointer");
    return node -> value_;
}

template <typename T>
bool Forward_list<T>::const_Iterator::operator==(const const_Iterator& it) const{
    return (node == it.node);
}
template <typename T>
bool Forward_list<T>::const_Iterator::operator!=(const const_Iterator& it) const{
    return !(*this == it);
}
template <typename T>
typename Forward_list<T>::const_Iterator& Forward_list<T>::const_Iterator::operator++(){
    if(node)
        node = node -> next;
    else{
        throw std::runtime_error("end of list");
    }
    return *this;
}
template <typename T>
typename Forward_list<T>::const_Iterator Forward_list<T>::const_Iterator::operator++(value_type){
        Node *n;
        if(node){
            n = node;
            node = node -> next;
        }
        else{
            throw std::runtime_error("end of list");
        }
        return n;
}

