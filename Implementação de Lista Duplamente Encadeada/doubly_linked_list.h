//! Copyright [2019] <Caetano Colin Torres>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

//! ...
template<typename T>
class DoublyLinkedList {
 public:
    //! ...
    DoublyLinkedList();
    //! ...
    ~DoublyLinkedList();
    //! ...
    void clear();
    //! ...
    void push_back(const T& data);  // insere no fim
    //! ...
    void push_front(const T& data);  // insere no início
    //! ...
    void insert(const T& data, std::size_t index);  // insere na posição
    //! ...
    void insert_sorted(const T& data);  // insere em ordem
    //! ...
    T pop(std::size_t index);  // retira da posição
    //! ...
    T pop_back();  // retira do fim
    //! ...
    T pop_front();  // retira do início
    //! ...
    void remove(const T& data);  // retira específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    //! ...
    const T& at(std::size_t index) const;  // getter constante a um elemento
    //! ...
    std::size_t find(const T& data) const;  // posição de um dado
    //! ...
    std::size_t size() const;  // tamanho

 private:
    class Node {  // elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {  // getter: prev
            return prev_;
        }

        const Node* prev() const {  // getter const: prev
            return prev_;
        }

        void prev(Node* node) {  // setter: prev
            prev_ = node;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };  // end class node

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
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
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}  // insere no fim

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* elemento = new Node(data);
    if (elemento == nullptr) {
        throw std::out_of_range("não tem mais espaço");
    } else {
        elemento->next(head);
        elemento->prev(nullptr);
        // head->prev(elemento);
        head = elemento;
        if (elemento->next() != nullptr) {
            elemento->next()->prev(elemento);
        } else {
            tail = elemento;
        }
        size_++;
    }
}  // insere no início

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
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
                if (novo->next() != nullptr) {
                    novo->next()->prev(novo);
                } else {
                    tail = novo;
                }
                novo->data() = data;
                anterior->next(novo);
                size_++;
            }
        }
    }
}  // insere na posição

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node* atual;
    int posicao;
    atual = head;
    posicao = 0;
    while (atual != nullptr && atual->data() < data) {
        atual = atual->next();
        posicao++;
    }
    insert(data, posicao);
}  // insere em ordem

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
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
            if (eliminar->next() != nullptr) {
                eliminar->next()->prev(anterior);
            } else {
                tail = anterior;
            }
            size_--;
            delete eliminar;
            return volta;
        }
    }
    return size_;
}  // retira da posição

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}  // retira do fim

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("empty");
    } else {
        Node* saiu;
        saiu = head;
        T volta;
        volta = saiu->data();
        head = saiu->next();
        if (head != nullptr) {
            head->prev(nullptr);
        } else {
            tail = nullptr;
        }
        size_--;
        delete saiu;
        return volta;
    }
}  // retira do início

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    int index = find(data);
    pop(index);
}  // retira específico

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}  // lista vazia

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
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
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
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
}  // acesso a um elemento (checando limites)

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
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
}  // getter constante a um elemento

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node* aux = head;
    for (int i = 0 ; i < size_ ; i++) {
        if (aux->data() == data)
            return i;
        aux = aux->next();
    }
    return size_;
}  // posição de um dado

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}  // tamanho
