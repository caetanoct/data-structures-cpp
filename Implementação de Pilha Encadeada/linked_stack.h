//! Copyright [2019] <Caetano Colin Torres>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

//! ...
template<typename T>
class LinkedStack {
//! ...
 public:
    //! ...
    LinkedStack();
    //! ...
    ~LinkedStack();
    //! ...
    void clear();  // limpa pilha
    //! ...
    void push(const T& data);  // empilha
    //! ...
    T pop();  // desempilha
    //! ...
    T& top() const;  // dado no topo
    //! ...
    bool empty() const;  // pilha vazia
    //! ...
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {  // Elemento
     public:
        Node() {
            printf("node criado");
        }
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };  // End class node

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    Node* aux = top_;
    Node* tmp = aux;
    for (int i = 1 ; i < size_ ; i++) {
        tmp = aux;
        aux = aux->next();
        delete tmp;
    }
    delete aux;
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* elemento = new Node(data);
    if (elemento == nullptr) {
        delete elemento;
        throw std::out_of_range("nao ha mais espaco");
    } else {
        if (empty()) {
            elemento->next(top_);
            top_ = elemento;
            size_++;
        } else {
            elemento->next(top_);
            top_ = elemento;
            size_++;
        }
    }
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("empty");
    } else {
        T volta;
        volta = top_->data();
        Node* elimina = top_;
        top_ = top_->next();
        size_--;
        delete elimina;
        return volta;
    }
    throw std::out_of_range("empty");
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (top_ == nullptr) {
        throw std::out_of_range("empty");
    } else {
        return top_->data();
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}
