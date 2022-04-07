// Copyright [2019] <CAETANO COLIN TORRES>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {
template<typename T>
//! CLASSE
class ArrayList {
 public:
    //! Construtor sem param
    ArrayList();
    //! Construtor com param
    explicit ArrayList(std::size_t max_size);
    //! destrutor
    ~ArrayList();
    //! limpa a lista
    void clear();
    //! adiciona no final
    void push_back(const T& data);
    //! adiciona no comeco
    void push_front(const T& data);
    //! insere na posicao
    void insert(const T& data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const T& data);
    //! remove na posicao
    T pop(std::size_t index);
    //! remove do final
    T pop_back();
    //! remove do comeco
    T pop_front();
    //! remove o data do tipo T
    void remove(const T& data);
    //! true se estiver cheio
    bool full() const;
    //! true se estiver vazio
    bool empty() const;
    //! true se conter "data"
    bool contains(const T& data) const;
    //! retorna o indice de onde esta data
    std::size_t find(const T& data) const;
    //! tamanho atual
    std::size_t size() const;
    //! tamanho max
    std::size_t max_size() const;
    //! objeto no Indice
    T& at(std::size_t index);
    //! objeto no []
    T& operator[](std::size_t index);
    //! objeto no index
    const T& at(std::size_t index) const;
    //! objeto no []
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};
template<typename T>
ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    size_ = 0;
    contents = new T[max_size_];
}

template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void ArrayList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void ArrayList<T>::push_front(const T& data) {
    int posicao;
    if (full()) {
        throw std::out_of_range("full");
    } else {
        size_++;
        posicao = size_-1;
        while (posicao > 0) {
            contents[posicao] = contents[posicao-1];
            posicao--;
        }
        contents[0] = data;
    }
}

template<typename T>
void ArrayList<T>::insert(const T& data, std::size_t index) {
    int atual;
    if (full()) {
       throw std::out_of_range("full");
    } else {
        if (index < 0 || index > size_) {
            throw std::out_of_range("erro");
        }
        size_++;
        atual = size_-1;
        while (atual > index) {
            contents[atual] = contents[atual-1];
            atual--;
        }
        contents[index] = data;
    }
}

template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    if (!full()) {
        for (int i = 0 ; i < size_ ; i++) {
            if (data <= contents[i]) {
                insert(data, i);
                return;
            }
        }
        push_back(data);
    } else {
        throw std::out_of_range("full");
    }
}
    template<typename T>
    T ArrayList<T>::pop(std::size_t index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("indice no pop invalido");
        } else {
            if (empty()) {
                throw std::out_of_range("empty");
            } else {
                T valor = contents[index];
                for (int i = index ; i < size_; i++) {
                    contents[i] = contents[i+1];
                }
                size_--;
                return valor;
            }
        }
    }
    template<typename T>
    T ArrayList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("empty");
        } else {
            T valor = contents[0];
                for (int i = 0 ; i < size_; i++) {
                    contents[i] = contents[i+1];
                }
                size_--;
                return valor;
        }
    }
    template<typename T>
    T ArrayList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("empty");
        } else {
            size_--;
            return contents[size_];
        }
    }
    template<typename T>
    void ArrayList<T>::remove(const T& data) {
        if (!empty()) {
            std::size_t indice = find(data);
            pop(indice);
        } else {
            throw std::out_of_range("empty");
        }
    }
    template<typename T>
    bool ArrayList<T>::full() const {
        if (size_ == max_size_) {
            return true;
        } else {
            return false;
        }
    }
    template<typename T>
    bool ArrayList<T>::empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }
    template<typename T>
    bool ArrayList<T>::contains(const T& data) const {
        for (int i = 0 ; i < size_ ; i++) {
            if (data == contents[i]) {
                return true;
            }
        }
        return false;
    }
    template<typename T>
    std::size_t ArrayList<T>::find(const T& data) const {
            for (int i = 0 ; i < size_ ; i++) {
                if (data == contents[i]) {
                    return i;
                }
            }
            return max_size_;
    }
    template<typename T>
    std::size_t ArrayList<T>::size() const {
        return size_;
    }
    template<typename T>
    std::size_t ArrayList<T>::max_size() const {
        return max_size_;
    }
    template<typename T>
    T& ArrayList<T>::at(std::size_t index) {
        if (index >= 0 && index < size()) {
         return *(contents+index);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    template<typename T>
    T& ArrayList<T>::operator[](std::size_t index) {
        return *(contents+index);
    }
    template<typename T>
    const T& ArrayList<T>::at(std::size_t index) const {
        if (index >= 0 && index < size()) {
         return *(contents+index);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    template<typename T>
    const T& ArrayList<T>::operator[](std::size_t index) const {
        return *(contents+index);
    }
}  // namespace structures

#endif
