//! Copyright [2019] <Caetano Colin Torres>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>  // C++ exceptions
#include "linked_stack.h"
#include "linked_list.h"
#include "linked_queue.h"
using namespace std;

class imagem {
 public:    
    int altura;
    int largura;
    char** data;
    //! deleta o que foi alocado para imagem
    void limpa() {
        for (int i = 0;i < altura; ++i) {
            delete []data[i];             
        }
        delete []data;
    }
};

class coordenada {
 public:
    int x;
    int y;
};

int determina_numero_de_componentes(imagem img) {
    char** matriz_entrada = img.data;
    structures3::LinkedQueue<coordenada> fila;
    int num_componentes_conexos = 0;
    int rotulo = 1;

    // Criando matriz R
    char** mat = new char*[img.altura];
 
    for(int i = 0;i < img.altura; ++i) {
        mat[i] = new char[img.largura];
    }    
    //iniciando ela com zero
    for(int i = 0;i < img.altura; ++i) {
        for(int j = 0;j < img.largura; ++j) {
            mat[i][j] = '0';
        }
    }            
    // Algoritmo de rotulacao
    for (int i = 0; i < img.altura ; i++) {    
        for (int j = 0 ; j < img.largura ; j++) {            
            if(matriz_entrada[i][j] == '1' && mat[i][j] == '0') {                
                // insere i,j(x,y) na fila na cordenada (x,y)
                coordenada xy_i;
                xy_i.x = i;
                xy_i.y = j;
                fila.enqueue(xy_i);                
                mat[i][j] = 'x';                
                while (!fila.empty()) {
                    coordenada xy = fila.dequeue();
                    coordenada* vizinhos = new coordenada[4];
                    vizinhos[0].x = xy.x -1;
                    vizinhos[0].y = xy.y;
                    vizinhos[1].x = xy.x + 1;
                    vizinhos[1].y = xy.y;                    
                    vizinhos[2].x = xy.x;
                    vizinhos[2].y = xy.y - 1;                    
                    vizinhos[3].x = xy.x;
                    vizinhos[3].y = xy.y + 1;
                    for (int i = 0 ; i < 4 ; i++) {
                        if (vizinhos[i].x >= 0 && vizinhos[i].y >= 0 && vizinhos[i].x < img.altura && vizinhos[i].y < img.largura) {                            
                            if (matriz_entrada[vizinhos[i].x][vizinhos[i].y] == '1' && mat[vizinhos[i].x][vizinhos[i].y] == '0') {                                
                                mat[vizinhos[i].x][vizinhos[i].y] = '#';
                                fila.enqueue(vizinhos[i]);                            
                            }
                        }
                    }
                    delete vizinhos;
                }                
                rotulo++;
            }
        }
    }        
    //liberar memória
    for(int i = 0;i < img.altura; ++i)
        delete []mat[i];
 
    delete []mat;
    return rotulo - 1;
}
string removeClosingMark(string s) {
    string ret;
    std::string::size_type tamanho_string_original = s.size();
    ret = "<";
    ret += s.substr(2);
    return ret;
}

int getHeight_in_line(string str) {
    string height_string = "";
    int height;
    size_t init_open_pos = str.find("<height>");
    size_t init_closing_pos = str.find("</height>");
    if (init_closing_pos == string::npos) {
        cout << "linha nao contem marca de fechamento";
        return 0;
    }
    if (init_open_pos == string::npos) {
        cout << "linha nao contem marca de abertura";
        return 0;
    }

    for (int i = init_open_pos + 8; i < init_closing_pos ; i++) {
        height_string += str[i];
    }
    height = stoi(height_string);
    return height;
}

int getWidth_in_line(string str) {
    string width_string = "";
    int width;
    size_t init_open_pos = str.find("<width>");
    size_t init_closing_pos = str.find("</width>");
    if (init_closing_pos == string::npos) {
        cout << "linha nao contem marca de fechamento";
        return 0;
    }
    if (init_open_pos == string::npos) {
        cout << "linha nao contem marca de abertura";
        return 0;
    }

    for (int i = init_open_pos + 7; i < init_closing_pos ; i++) {
        width_string += str[i];
    }
    width = stoi(width_string);
    return width;
}
string getName_in_line(string str) {
    string name_string = "";
    size_t init_open_pos = str.find("<name>");
    size_t init_closing_pos = str.find("</name>");
    if (init_closing_pos == string::npos) {
        cout << "linha nao contem marca de fechamento";
        return 0;
    }
    if (init_open_pos == string::npos) {
        cout << "linha nao contem marca de abertura";
        return 0;
    }
    for (int i = init_open_pos + 6; i < init_closing_pos ; i++) {
        name_string += str[i];
    }
    return name_string;
}
bool valida (string xmlfilename) {
    //! validacao do arquivo xml usando pilha
    structures::LinkedStack<string> stack;
    string line;
    ifstream myfile (xmlfilename);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            string str = line;            
            for(std::string::size_type i = 0; i < str.size(); ++i)   {
                if (str[i] == '<') {
                    int strlength = 1;
                    int index_inicial = i;
                    for (std::string::size_type j = i + 1; j < str.size(); ++j) {
                        strlength++;
                        if (str[j] == '>') {
                            string string_entre_marcadores = str.substr(index_inicial,strlength); // a string inclui os marcadores<>
                            if (string_entre_marcadores[1] == '/') {
                                if (stack.size() == 0) {
                                    return false;
                                } else {
                                    string desempilhado = stack.pop();
                                    string sem_barra = removeClosingMark(string_entre_marcadores);
                                    if (sem_barra != desempilhado) {                                        
                                        stack.push(desempilhado);
                                        return false;
                                    }
                                }                           
                            }
                            if (string_entre_marcadores[1] != '/') {
                                stack.push(string_entre_marcadores);
                            }
                            strlength = 0;
                            break;
                        }
                    }
                }
            }
            //cout << line << '\n'; 
        }
        if (stack.size() != 0) {
            return false;
        } else {
            return true;
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    return false;
}
int main() {

    char xmlfilename[100];
    structures2::LinkedList<string> linhas_do_arquivo{};
    std::cin >> xmlfilename;  // entrada
    bool valido = valida(xmlfilename);
    if (!valido) {
        cout << "error\n";
        return 0;
    }    
    string line;
    ifstream myfile (xmlfilename);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {           
            linhas_do_arquivo.push_back(line);                      
        }       
        myfile.close();
    }
    else cout << "Unable to open file";         
    // etapa 2:
            
    int numero_imagens = 0;
    int nome_contador = 0;
    for (int i = 0 ; i < linhas_do_arquivo.size(); i++) {
        string str = linhas_do_arquivo.at(i);
        size_t found = str.find("<img>");
        if (found != string::npos) {
            numero_imagens++;
        }

    }    
    int* altura = new int[numero_imagens];
    int* largura = new int[numero_imagens];
    // string tem tamanho variavel, entao usamos lista(ponteiro que devolveria no delete muda)
    structures2::LinkedList<string> nomes_imagens{};
    imagem* imagens = new imagem[numero_imagens];
    int a = 0;
    int b = 0;
    int c = 0;
    //! Laço que preenche os arrays de altura/largura com os valores respectivos de cada imagem i
    for (int i = 0; i < linhas_do_arquivo.size(); i++) {
        string str = linhas_do_arquivo.at(i);
        if (str.find("<height>") != string::npos) {
            altura[a++] = getHeight_in_line(str);
        }
        if (str.find("<width>") != string::npos) {
            largura[b++] = getWidth_in_line(str);
        }
        if (str.find("<name>") != string::npos) {
            nomes_imagens.push_back(getName_in_line(str));
        } 
    }

    //! Laço que inicializa as matrizes de cada imagem com suas respectivas alturas/larguras
    for (int i = 0 ; i < numero_imagens ; i++) {                
        imagens[i].data = new char*[altura[i]];
        for(int k = 0; k < altura[i]; ++k) {
            imagens[i].data[k] = new char[largura[i]];
        }
    }

    //! Laço que armazena as strings 0/1's nas matrizes data de cada imagem
    int contador = 0;
    for (int i = 0; i < linhas_do_arquivo.size(); i++) {
        string str = linhas_do_arquivo.at(i);
        if (str.find("<data>") != string::npos) {
            int varia = i+1;
            int linha = 0;
            while (linhas_do_arquivo.at(varia+1).find("</data>") == string::npos) {                
                string string_atual = linhas_do_arquivo.at(varia); 
                for (int j = 0 ; j < string_atual.size(); j++) {                                       
                    imagens[contador].data[linha][j] = string_atual[j];                    
                }                
                linha++;                                        
                varia++;                                
            }
            // armazena ultima linha
            string string_atual = linhas_do_arquivo.at(varia); 
            for (int j = 0 ; j < string_atual.size(); j++) {                                       
                imagens[contador].data[linha][j] = string_atual[j];                
            }                        
            contador++;                        
        }
    }    
    //! Laço que acha o número de componentes conexos de cada imagem
    for (int i = 0 ; i < numero_imagens ; i++) {        
        imagem img_atual = imagens[i];
        img_atual.altura = altura[i];
        img_atual.largura = largura[i];                
        int num_componentes_conexos = determina_numero_de_componentes(img_atual);
        cout << nomes_imagens.at(i) << " " << num_componentes_conexos << "\n";
        img_atual.limpa();
    }    
    delete altura;    
    delete largura;    
    delete imagens;    
    nomes_imagens.clear();
    return 0;
}
    