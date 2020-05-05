#include <stdexcept>
#include <iterator>
#include "Container.hpp"
#include "Forward_list.hpp"
#include "Const_iterator.hpp"
#include "Iterator.hpp"
template <typename T>
struct Forward_list<T>::Node{
        T value_;
        Node* next;
        Node(): next(nullptr) {}
        Node(const T& t): value_(t), next(nullptr) {}
        ~Node(){}
};
template<typename T>
typename Forward_list<T>::const_iterator Forward_list<T>::begin() const{
    return const_iterator(first_element);
}
template<typename T>
typename Forward_list<T>::const_iterator Forward_list<T>::end() const{
    return const_iterator(nullptr);
}
template<typename T>
typename Forward_list<T>::iterator Forward_list<T>::begin(){
    return iterator(first_element);
}
template<typename T>
typename Forward_list<T>::iterator Forward_list<T>::end(){
    return iterator(nullptr);
}
template< typename T >
unsigned int Forward_list<T>::size() const{
    size_t s(0);
    for(auto it = begin(); it != end(); ++it)
        ++s;
    return s;
}
template <typename T>
Forward_list<T>::Forward_list(): first_element(nullptr), last_element(nullptr){}
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& l){
    if(!(l.first_element)){
        first_element = nullptr;
        last_element = nullptr;
    }
    else{
        first_element = nullptr;
        last_element = nullptr;
        for(auto it = l.begin(); it != l.end(); ++it){
            (*this).Push_back(*it);
        }

    }
}
template <typename T>
Forward_list<T>& Forward_list<T>::operator=(const Forward_list& l){
    if(this == &l)
        return *this;
    if(first_element)
        delete_list();
    if(!(l.first_element)){
        first_element = nullptr;
        last_element = nullptr;
    }
    else{
        first_element = nullptr;
        last_element = nullptr;
        for(auto it = l.begin(); it != l.end(); ++it){
            (*this).Push_back(*it);
        }

    }
    return *this;
}
template <typename T>
Forward_list<T>::~Forward_list(){
    while(first_element){
        Node* new_first = first_element -> next;
        delete first_element;
        first_element = new_first;
    }
    last_element = nullptr;
}
template <typename T>
void Forward_list<T>::delete_list(){
    while(first_element){
        Node* new_first = first_element -> next;
        delete first_element;
        first_element = new_first;
    }
    last_element = nullptr;
}
template <typename T>
void Forward_list<T>::insert(const T& value){
   Node* node = new Node(value);
   node -> next = first_element;
   if(!first_element)
        last_element = node;
   first_element = node;
}
template <typename T>
void Forward_list<T>::Push_back(const T& value){
    Node* node = new Node(value);
    if(!last_element){
        first_element = node;
        last_element = node;
    }
    else{
        last_element -> next = node;
        last_element = node;
    }

}
template <typename T>
bool Forward_list<T>::exists(const T& value) const{
    Node* node = first_element;
    while(node){
        if(node -> value_ == value)
            return true;
        node = node -> next;
    }
    return false;
}
template <typename T>
void Forward_list<T>::remove(const T& value){
    Node* node = first_element;
    while(node){
        if(first_element && first_element -> value_ == value){
            node = first_element -> next;
            if(!node)
                last_element = nullptr;
            delete first_element;
            first_element = node;

        }
        else{
        if(node -> next && node -> next -> value_ == value){
            Node * newNode = node -> next -> next;
            if(!newNode)
                last_element = node;
             delete node -> next;
             node -> next = newNode;
        }
        else
            node = node -> next;
        }
    }
}
