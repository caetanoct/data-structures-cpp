//! Copyright [2018] <caetano colin torres>


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! documentacao
template<typename T>
class ArrayList {
 public:
    //! construtor sem param
    ArrayList();
    //! ...
    explicit ArrayList(std::size_t max_size);
    //! ...
    ~ArrayList();

    //! ...
    void clear();
    //! ...
    void push_back(const T& data);
    //! ...
    void push_front(const T& data);
    //! ...
    void insert(const T& data, std::size_t index);
    //! ...
    void insert_sorted(const T& data);
    //! ...
    T pop(std::size_t index);
    //! ...
    T pop_back();
    //! ...
    T pop_front();
    //! ...
    void remove(const T& data);
    //! ...
    bool full() const;
    //! ...
    bool empty() const;
    //! ...
    bool contains(const T& data) const;
    //! ...
    std::size_t find(const T& data) const;
    //! ...
    std::size_t size() const;
    //! ...
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();

    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    size_ = 0;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    size_ = 0;
    max_size_ = max_size;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
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
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
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
void structures::ArrayList<T>::insert_sorted(const T& data) {
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
    T structures::ArrayList<T>::pop(std::size_t index) {
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
    T structures::ArrayList<T>::pop_front() {
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
    T structures::ArrayList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("empty");
        } else {
            size_--;
            return contents[size_];
        }
    }
    template<typename T>
    void structures::ArrayList<T>::remove(const T& data) {
        if (!empty()) {
            std::size_t indice = find(data);
            pop(indice);
        } else {
            throw std::out_of_range("empty");
        }
    }
    template<typename T>
    bool structures::ArrayList<T>::full() const {
        if (size_ == max_size_) {
            return true;
        } else {
            return false;
        }
    }
    template<typename T>
    bool structures::ArrayList<T>::empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }
    template<typename T>
    bool structures::ArrayList<T>::contains(const T& data) const {
        for (int i = 0 ; i < size_ ; i++) {
            if (data == contents[i]) {
                return true;
            }
        }
        return false;
    }
    template<typename T>
    std::size_t structures::ArrayList<T>::find(const T& data) const {
            for (int i = 0 ; i < size_ ; i++) {
                if (data == contents[i]) {
                    return i;
                }
            }
            return max_size_;
    }
    template<typename T>
    std::size_t structures::ArrayList<T>::size() const {
        return size_;
    }
    template<typename T>
    std::size_t structures::ArrayList<T>::max_size() const {
        return max_size_;
    }
    template<typename T>
    T& structures::ArrayList<T>::at(std::size_t index) {
        if (index >= 0 && index < size()) {
         return *(contents+index);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    template<typename T>
    T& structures::ArrayList<T>::operator[](std::size_t index) {
        return *(contents+index);
    }
    template<typename T>
    const T& structures::ArrayList<T>::at(std::size_t index) const {
        if (index >= 0 && index < size()) {
         return *(contents+index);
        } else {
            throw std::out_of_range("out of range");
        }
    }
    template<typename T>
    const T& structures::ArrayList<T>::operator[](std::size_t index) const {
        return *(contents+index);
    }

structures::ArrayListString::~ArrayListString() {
    clear();
}

void structures::ArrayListString::clear() {
    for (std::size_t i = 0 ; i < ArrayList::size() ; i++) {
        delete[] ArrayList::at(i);
    }
    ArrayList::clear();
}

void structures::ArrayListString::push_back(const char *data) {
    char* datanew = new char[strlen(data)+1];
    snprintf(datanew, strlen(data)+1, "%s", data);
    ArrayList::push_back(datanew);
}

void structures::ArrayListString::push_front(const char *data) {
    char* datanew = new char[strlen(data)+1];
    snprintf(datanew, strlen(data)+1, "%s", data);
    ArrayList::push_front(datanew);
}

void structures::ArrayListString::insert(const char *data, std::size_t index) {
    char* datanew = new char[strlen(data)+1];
    snprintf(datanew, strlen(data)+1, "%s", data);
    ArrayList::insert(datanew, index);
}

void structures::ArrayListString::insert_sorted(const char *data) {
    if (!ArrayList::full()) {
        for (std::size_t i = 0 ; i < ArrayList::size() ; i++) {
            int result = strcmp(data, ArrayList::at(i));
            if (result <= 0) {
                insert(data, i);
                return;
            }
        }
        push_back(data);
    } else {
        throw std::out_of_range("full");
    }
}

char *structures::ArrayListString::pop(std::size_t index) {
    char* retrn = new char[strlen(ArrayList::at(index)+1)];
    snprintf(retrn, strlen(ArrayList::at(index))+1, "%s", ArrayList::at(index));
    // delete [] ArrayList::at(index);
    ArrayList::pop(index);
    return retrn;
}

char *structures::ArrayListString::pop_back() {
    std::size_t i = ArrayList::size() - 1;
    return pop(i);
}

char *structures::ArrayListString::pop_front() {
    return pop(0);
}

void structures::ArrayListString::remove(const char *data) {
    if (ArrayList::empty()) {
        throw std::out_of_range("empty");
    } else {
        std::size_t index = find(data);
        pop(index);
    }
}

bool structures::ArrayListString::contains(const char *data) {
    if (find(data) == ArrayList::max_size()) {
        return false;
    } else {
        return true;
    }
}

std::size_t structures::ArrayListString::find(const char *data) {
    char* datanew = new char[strlen(data)+1];
    snprintf(datanew, strlen(data)+1, "%s", data);
    for (std::size_t i = 0 ; i < ArrayList::size() ; i++) {
        if (strcmp(datanew, ArrayList::at(i)) == 0) {
            return i;
        }
    }
    delete[] datanew;
    return ArrayList::max_size();
}
