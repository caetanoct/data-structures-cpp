//! Copyright [2019] <Caetano Colin Torres>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

//! ...
template<typename T>
class LinkedQueue {
//! ...
 public:
    //! ...
    LinkedQueue();
    //! ...
    ~LinkedQueue();
    //! ...
    void clear();  // limpa fila
    //! ...
    void enqueue(const T& data);  // enfileirar
    //! ...
    T dequeue();  // desenfileirar
    //! ...
    T& front() const;  // dado na 1 pos
    //! ...
    T& back() const;  // dado na ultima pos
    //! ...
    bool empty() const;  // vazia
    //! ...
    std::size_t size() const;  // tamanho

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

    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    Node* aux = head;
    Node* tmp = aux;
    for (int i = 1 ; i < size_ ; i++) {
        tmp = aux;
        aux = aux->next();
        delete tmp;
    }
    delete aux;
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* elemento = new Node(data);
    if (elemento == nullptr) {
        delete elemento;
        throw std::out_of_range("nao ha mais espaco");
    } else {
        if (empty()) {
            elemento->next(nullptr);
            tail = elemento;
            head = elemento;
            size_++;
        } else {
            elemento->next(nullptr);
            tail->next(elemento);
            tail = elemento;
            size_++;
        }
    }
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("empty");
    } else {
        if (size_ == 1) {
            T volta = head->data();
            delete head;
            head = nullptr;
            tail = nullptr;
            size_--;
            return volta;
        } else {
            T volta;
            volta = head->data();
            Node* elimina = head;
            head = head->next();
            size_--;
            delete elimina;
            return volta;
        }
    }
    throw std::out_of_range("empty");
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("empty");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("empty");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
