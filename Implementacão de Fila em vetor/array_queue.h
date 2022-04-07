// Copyright [2018] <COLOQUE SEU NOME AQUI...>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_SIZE = 10u;
    int next_enqueue;
    int next_dequeue;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    next_enqueue = 0;
    next_dequeue = 0;
    size_ = 0;
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    next_enqueue = 0;
    next_dequeue = 0;
    size_ = 0;
    max_size_ = max;
    contents = new T[max];
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    }
    contents[next_enqueue] = data;
    next_enqueue++;
    size_++;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    size_--;
    next_dequeue++;
    return contents[next_dequeue-1];
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    }
    return contents[size_ - 1];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
    next_dequeue = 0;
    next_enqueue = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == max_size_) {
        return true;
    } else {
        return false;
    }
}
