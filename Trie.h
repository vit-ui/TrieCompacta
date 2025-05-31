#pragma once
#include<string>

const int N = 27;

struct No{
    std::string chave;
    bool noExterno;
    No *alfabeto[N];
};

class Arvore{
public:
	Arvore(){
        Trie = nullptr;
    }
    void Inserir(std::string);

    void Remove(std::string, No * aux = nullptr);

    bool Pesquisa(std::string);

    void PalavrasPrefixo(std::string);

    ~Arvore(){}

private:
    No *Trie;

    void TodasChaves(No *);
    void NullTodosPointers(No *);
};

