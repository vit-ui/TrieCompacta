#include "Trie.h"

#include<iostream>

void Arvore::Inserir(std::string palavra){
    // Se arvore estiver vazia:
    if(Trie == nullptr){
        No *novo = new No;
        novo->chave = palavra;
        novo->noExterno = true;
        NullTodosPointers(novo);
        
        Trie = new No;
        Trie->chave = "Trie";
        Trie->noExterno = false;
        NullTodosPointers(Trie);
        Trie->alfabeto[palavra[0] - 'a'] = novo;
        return;
    }

    No* aux = Trie;
	bool nulo = false;
	int i = 0;
    // Caminhando pela arvore até NULL ou nó externo
    while(!nulo && !aux->noExterno){
		if(aux->alfabeto[palavra[i] - 'a'] == nullptr)
			nulo = true;
		else
		{
			aux = aux->alfabeto[palavra[i] - 'a'];
			i++;
		}
    }

    // Se for encontrado NULL(aux == nullptr)
    // cria novo nó externo e armazena
    if(nulo) {
        No* novo = new No;
        novo->chave = palavra;
        novo->noExterno = true;
        NullTodosPointers(novo);
        
        aux->alfabeto[palavra[i] - 'a'] = novo;
    }
    // Se for encontrado um nó externo
    // Se palavra diferente da chave
    else if(palavra != aux->chave) {
        // Cria aux2 para armazenar o nó externo
        No *aux2 = aux;
		std::string key = aux->chave;
        // Compara cada letra e se for igual cria um nó interno
        // Se for diferente cria um nó externo para palavra
        for(; i < palavra.size() && i < key.size(); i++){
			if(palavra[i] == key[i])
			{
				// No interno:
				No *interno = new No;
				interno->chave = "interno";
				interno->noExterno = false;
				NullTodosPointers(interno);
				
				aux = aux2;

				aux->alfabeto[palavra[i] - 'a'] = interno;
				aux->noExterno = false;
				aux->chave = "interno";
				
				aux2 = interno;
			}
			else break;
        }
		int a;
		if(i >= palavra.size())
		{
			a = N - 1;
			i = key[i] - 'a';
		}
		else if(i >= key.size())
		{
			a = palavra[i] - 'a';
			i = N - 1;
		}
		else
		{
			a = palavra[i] - 'a';
			i = key[i] - 'a';
		}

		No *novo = new No;

		novo->chave = palavra;
		novo->noExterno = true;
		NullTodosPointers(novo);

		aux2->alfabeto[a] = novo;
		aux2->alfabeto[i] = new No;
		aux2->alfabeto[i]->chave = key;
		aux2->alfabeto[i]->noExterno = true;
		NullTodosPointers(aux2->alfabeto[i]);
		
		aux->chave = "interno";
		aux->noExterno = false;
    }
    // Se palavra igual a chave, retorne
    else 
        return;
}

void Arvore::Remove(std::string palavra, No* aux){
    if(!aux)
        aux = Trie;

    for(int k = 0; k < N; k++){
        No *aux2 = aux->alfabeto[k];

        if(aux2 && !aux2->noExterno){
            Remove(palavra, aux2);
            int count = 0;
            int loc = 0;
            for(int i = 0; i < N; i++){
                if(aux2->alfabeto[i] && aux2->alfabeto[i]->noExterno)
                {
                    if(++count == 1) loc = i;
                }
            }
            if(count == 1)
				aux->alfabeto[k] = aux2->alfabeto[loc];
        }
        else{
            if(aux2 && aux2->chave == palavra){
                // Delete os ponteiros
                delete aux2;
				aux->alfabeto[k] = nullptr;
                return;
            }
        }
    }
}

bool Arvore::Pesquisa(std::string palavra){
    No *aux = new No;
    aux = Trie;

    int i = 0;
    // Caminhando pela arvore até NULL ou nó externo
    while(aux && !aux->noExterno){
		if(i < palavra.size())
			aux = aux->alfabeto[palavra[i++] - 'a'];
		else
			aux = aux->alfabeto[N - 1];
    }

    // Se aux for NULL ou a chave encontrada for
    // diferente da palavra, retorne false.
    if(!aux || aux->chave != palavra)
        return false;
    return true;
}

void Arvore::PalavrasPrefixo(std::string prefixo){
    No *aux = new No;
    aux = Trie;

    int i = 0;
    // Caminhando pela arvore até NULL ou fim do prefixo
    while(i < prefixo.size() && aux && !aux->noExterno){
        aux = aux->alfabeto[prefixo[i++] - 'a'];
    }

	if(aux && aux->noExterno && prefixo != aux->chave)
		aux = aux->alfabeto[prefixo[i++] - 'a'];

    // Se o prefixo não estiver no caminho da arvore, avise o usuario
    if(!aux)
        std::cout << "Palavras com prefixo " << prefixo << " nao encontradas. Tente outro prefixo." << std::endl;
    else{ // Recursivo: imprime as chaves com o prefixo
        std::cout << "\n\tForam encontradas as seguintes palavras com o prefixo " << prefixo << ":\n";
        TodasChaves(aux);
    }
}

void Arvore::TodasChaves(No *aux){
    for(int i = 0; i < N; i++){
        if(aux->alfabeto[i] != nullptr){
            TodasChaves(aux->alfabeto[i]);
        }
        if(aux->noExterno == true){
            std::cout << "\t" << aux->chave << std::endl;
            return;
        }
    }
}

void Arvore::NullTodosPointers(No *vet)
{
    for(int i = 0; i < N; i++)
        vet->alfabeto[i] = nullptr;
}