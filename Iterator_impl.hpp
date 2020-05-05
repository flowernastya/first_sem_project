#include "Container.hpp"
#include "Forward_list.hpp"
#include <stdexcept>
#include <iterator>
#include "Iterator.hpp"
template <typename T>
Forward_list<T>::Iterator::Iterator() {}
template <typename T>
Forward_list<T>::Iterator::Iterator(Node* _node): node(_node) {}
template <typename T>
Forward_list<T>::Iterator::~Iterator() { }
template <typename T>
typename Forward_list<T>::Iterator::reference Forward_list<T>::Iterator::operator*(){
        if(!node)
            throw std::runtime_error("dereferencing a null pointer");
        return node -> value_;
}
template <typename T>
bool Forward_list<T>::Iterator::operator==(const Iterator& it) const{
        return (node == it.node);
}
template <typename T>
bool Forward_list<T>::Iterator::operator!=(const Iterator& it) const{
    return !(*this == it);
}

template <typename T>
typename Forward_list<T>::Iterator& Forward_list<T>::Iterator::operator++(){
    if(node)
        node = node -> next;
    else{
        throw std::runtime_error("end of list");
    }
    return *this;
}
template <typename T>
typename Forward_list<T>::Iterator Forward_list<T>::Iterator::operator++(value_type){
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


