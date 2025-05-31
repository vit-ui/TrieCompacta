#include<iostream>
#include "Trie.h"

int main(){
    Arvore arv;
    int opcao;
    std::string palavra, prefixo;

    do {
        std::cout << "\n======= MENU =======\n";
        std::cout << "1. Inserir palavra\n";
        std::cout << "2. Pesquisar palavra\n";
        std::cout << "3. Remover palavra\n";
        std::cout << "4. Listar palavras com prefixo\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;
        std::cin.ignore(); // Limpa o buffer do cin

        switch (opcao) {
            case 1:
                std::cout << "Digite a palavra a ser inserida: ";
                std::cin >> palavra;
                if(palavra.empty()) std::cout << "palavra main";
                arv.Inserir(palavra);
                std::cout << "Palavra inserida com sucesso.\n";
                break;

            case 2:
                std::cout << "Digite a palavra a ser pesquisada: ";
                std::getline(std::cin, palavra);
                if (arv.Pesquisa(palavra))
                    std::cout << "Palavra encontrada.\n";
                else
                    std::cout << "Palavra nao encontrada.\n";
                break;

            case 3:
                std::cout << "Digite a palavra a ser removida: ";
                std::getline(std::cin, palavra);
				if(arv.Pesquisa(palavra))
				{
					arv.Remove(palavra);
					std::cout << "Palavra removida com sucesso.\n";
				}
                else
                    std::cout << "Erro: Palavra nao encontrada ou nao removida.\n";
                break;

            case 4:
                std::cout << "Digite o prefixo: ";
                std::getline(std::cin, prefixo);
                arv.PalavrasPrefixo(prefixo);
                break;

            case 0:
                std::cout << "Encerrando o programa.\n";
                break;

            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
        }

    } while (opcao != 0);
}