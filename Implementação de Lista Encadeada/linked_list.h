//! Copyright [2019] <Caetano Colin Torres>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty();  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}


template<typename T>
void structures::LinkedList<T>::clear() {
    Node* aux = head;
    Node* tmp = aux;
    for (int i = 1 ; i < size_ ; i++) {
        tmp = aux;
        aux = aux->next();
        delete tmp;
    }
    delete aux;
    head = nullptr;
    size_ = 0;
}
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    if (size_ == 0) {
        Node* element = new Node(data);
        element->next(nullptr);
        head = element;
        size_++;
    } else {
        Node* element = new Node(data);
        Node* aux = head;
        for (int i = 1 ; i < size() ; i++) {
            aux = aux->next();
        }
        element->next(nullptr);
        aux->next(element);
        size_++;
    }
}  // inserir no fim

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* elemento;
    elemento = new Node(data);
    if (elemento == NULL) {
        throw std::out_of_range("erro lista cheia");
    } else {
        elemento->next(head);
        head = elemento;
        size_++;
    }
}  // inserir no início

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* novo;
    Node* anterior;
    if (index > size_) {
        throw std::out_of_range("index out of range");
    } else {
        if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("erro lista cheia");
            } else {
                anterior = head;
                for (int i = 1 ; i < index ; i++) {
                    anterior = anterior->next();
                }
                novo->next(anterior->next());
                novo->data() = data;
                anterior->next(novo);
                size_++;
            }
        }
    }
}  // inserir na posição

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* atual;
    int posicao;
    atual = head;
    posicao = 0;
    while (atual != nullptr && atual->data() < data) {
        atual = atual->next();
        posicao++;
    }
    insert(data, posicao);
}  // inserir em ordem

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index out of bounds");
    } else {
        if (index == 0) {
            return head->data();
        }
        Node* aux = head;
        for (int i = 0 ; i < index ; i++) {
            aux = aux->next();
        }
        return aux->data();
    }
}  // acessar um elemento na posição index

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("index out of range");
    } else {
        Node* anterior;
        Node* eliminar;
        T volta;
        if (index == 0) {
            return pop_front();
        } else {
            anterior = head;
            for (int i = 1 ; i < index ; i++) {
                anterior = anterior->next();
            }
            eliminar = anterior->next();
            volta = eliminar->data();
            anterior->next(eliminar->next());
            size_--;
            delete eliminar;
            return volta;
        }
    }
    return size_;
}  // retirar da posição

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}  // retirar do fim

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("empty");
    } else {
        Node* aux;
        aux = head;
        T volta;
        volta = head->data();
        head = head->next();
        size_--;
        delete aux;
        return volta;
    }
}  // retirar do início

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    int index = find(data);
    pop(index);
}  // remover específico

template<typename T>
bool structures::LinkedList<T>::empty() {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}  // lista vazia

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* aux = head;
    for (int i = 0 ; i < size_ ; i++) {
        if (data == aux->data()) {
            return true;
        }
        aux = aux->next();
    }
    return false;
}  // contém

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* aux = head;
    for (int i = 0 ; i < size_ ; i++) {
        if (aux->data() == data)
            return i;
        aux = aux->next();
    }
    return size_;
}  // posição do dado

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}  // tamanho da lista

