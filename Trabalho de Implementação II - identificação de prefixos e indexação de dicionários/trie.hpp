    #ifndef TRIE_HPP
    #define TRIE_HPP

    #include <string>
    #include <stdexcept>
    #include <vector>
    #include <iostream>

    using namespace std;

    namespace structures {

    class Trie {
     private:
      struct Node {
        char letter;
        vector<Node *> sons;
        std::size_t pos;
        std::size_t comprimento;
        std::size_t length;
        
        explicit Node(char letter){
          this->letter = letter;
          this->sons = vector<Node*>();
        }

        Node* destroyRec() {
          int size = sons.size();
          if (size == 0) {
            return this;
          }
          for (int i = 0; i < size; ++i) {
            delete sons[i]->destroyRec();
          }
          return this;
        }        
        void insert(Node* node, string key, int d, int this_line_length, int this_char_pos) {
          bool hasChild = false;
          Node* next_node;
          for (int i = 0; i < sons.size(); ++i) {
            if (sons[i]->letter == key[d]) {
              next_node = sons[i];
              hasChild = true;
              break;
            }
          }

          if (!hasChild) {
            next_node = new Node(key[d]);
            //cout << "node com caractere = " << key[d] << " criado\n";        
            sons.push_back(next_node);
          }

          bool last = key.size() == d + 1;
          if (!last) {
            next_node->insert(node, key, d + 1, this_line_length, this_char_pos);
          } else {
            next_node->length = d + 1;
            next_node->comprimento = this_line_length;
            next_node->pos = this_char_pos;
            //cout << "nodo tem comprimento = " << d << " e seu caractere é igual a: " << key[d] << "\n";
          }
        }
    };
     public:
        Trie() {
        root = new Node('\0');
      }

      ~Trie() {
        root->destroyRec();
        delete root;
      }
      
      void insert(string key, int this_line_length, int this_char_pos) {
        root->insert(root, key, 0, this_line_length, this_char_pos);
        //cout << "executando insert() com key = " << key << "\n";
      }
      bool search(string key) {
            Node* current = root;
            for (int i = 0 ; i < key.size(); ++i) {            
                int index = findPosOf(key[i], current->sons);
                if (index == -1) {
                    return false;
                } else {
                    current = current->sons[index];
                }
            }
            if(current->length == key.size()) {            
                return true;
            } else {
                return false;
            }
        }
        void printResult(string key) {        
            if(search(key)) {
                Node* current = root;
                for (int i = 0 ; i < key.size(); ++i) {            
                    int index = findPosOf(key[i], current->sons);
                    if (index == -1) {
                        cout << "ERRO NAO ACHOU CARACTERE NOS FILHOS";
                    } else {
                        current = current->sons[index];
                    }
                }
                cout << current->pos << " " << current->comprimento << "\n";
            } else {
                cout << "is prefix\n";
            }        
        }
        bool isPrefix(string key) {  
            Node* current = root;  
            for (int i = 0 ; i < key.size(); i++) {
                int index = findPosOf(key[i], current->sons);
                if (index == -1) {
                    return false;
                } else {
                    current = current->sons[index];
                }
            }
            return true;     
        }
        int findPosOf(char c, vector<Node *> v) {
            for (int i = 0 ; i < v.size(); i++) {
                if (c == v[i]->letter) {
                    return i;
                }
            }
            return -1;
        }        
        Node* root;        
      };
    } // Namespace structures

    #endif