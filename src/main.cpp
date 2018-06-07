#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Life.h"

using namespace std;

/**
 * \brief Assinatura de todos os métodos utilizados.
 */
void validarEntrada(int argc, char *argv[]);
void validarArquivo(string nome);
void processarDados(string nomeArquivo, Life &life);
void printHeader();
void setup(string nomeArquivo, Life &life);
void alocarGrid(Life &life);
void configurarGrid(ifstream &arquivo, Life &life);
void loopGame(Life &life, int argc, char *argv[]);

/**
 * \param argc recebe a quantidade de argumentos que foi passada na execução do programa.
 * \param argv recebe todos os argumentos passados para o programa.
 * \return
 */
int main(int argc, char *argv[]) {
    validarEntrada(argc, argv);
    Life life;
    setup(argv[1], life);
    loopGame(life, argc, argv);
    return 0;
}

/**
 * \brief iteração de todo o jogo que será controloda pelo o usuário.
 * \param life recebe um objeto da classe Life como referência.
 * \param argc quantidade de argumentos passados para o main
 * \param argv argumentos passados para o main
 * \return void
 */
void loopGame(Life &life, int argc, char *argv[]) {
    ofstream saida;
    if(argc > 2) {
        saida.open(argv[2]);
    }
    int generation = 1;
    char opcao = 'y';
    vector<bool **> geracoes;
    geracoes.push_back(life.copyGrid());
    do {
        ostringstream ss;
        ss << "Showing generation " << generation << ":" << endl;
        ss << life;
        ss << "Continue viewing new generations?" << endl;
        ss << "(y, n)?" << endl;
        ss << endl;
        if(life.extinct()) {
            ss << "A geração foi extinta" << endl;
            cout << ss.str();
            if(saida.is_open()) {
                saida << ss.str();
            }
            break;
        }
        if(life.stable(geracoes)) {
            ss << "A geração é estável" << endl;
            cout << ss.str();
            if(saida.is_open()) {
                saida << ss.str();
            }
            break;
        }
        cout << ss.str();
        if(saida.is_open()) {
            saida << ss.str();
        }
        cin >> opcao;
        life.update();
        geracoes.push_back(life.copyGrid());
        generation++;
    } while(opcao == 'y');
    if(saida.is_open()) {
        saida.close();
    }
}

/**
 * \brief verifica se a sintaxe foi digitada corretamente e se o arquivo é válido.
 * \param argc quantidade de argumentos passados para o main
 * \param argv argumentos passados para o main
 */
void validarEntrada(int argc, char *argv[]) {
    if(argc < 2) {
        cerr << "Wrong syntaxe!" << endl;
        cerr << "Use: life <input_cfg_file> [<output_cfg_evolution_file>]" << endl;
        exit(0);
    }
    validarArquivo(argv[1]);
}

/**
 * \brief verifica se um arquivo é válido.
 * \param nome, nome do arquivo que será verificado.
 */
void validarArquivo(string nome) {
    cout << endl << ">>> Trying to open input file [" << nome << "]... ";
    ifstream arquivo(nome);
    if(arquivo.is_open()) {
        cout << "done!" << endl << endl;
        arquivo.close();
        return;
    }
    cout << "fail!" << endl << endl;
    exit(0);
}

/**
 * \brief carrega todas as configurações inicias como por exemplo o grid.
 * \param nomeArquivo, recebe o nome do arquivo onde os dados serão buscados.
 * \param life, variável passada como referência onde será carregada as configurações.
 */
void processarDados(string nomeArquivo, Life &life) {
    ifstream arquivo(nomeArquivo);
    string line;
    //Recupera o tamanho da configuração
    getline(arquivo, line);
    stringstream linha(line);
    int linhas;
    int colunas;
    linha >> linhas;
    linha >> colunas;
    life.setnLin(linhas);
    life.setnCol(colunas);

    getline(arquivo, line);
    life.setCaracter(line[0]);
    alocarGrid(life);
    configurarGrid(arquivo, life);
    arquivo.close();
}

/**
 * \brief função responsável por fazer a alocação do grid de forma dinamica
 * \param life, onde será armazenado o grid.
 */
void alocarGrid(Life &life) {
    bool **grid = new bool*[life.getnLin()];
    for(int i = 0; i < life.getnLin(); i++) {
        grid[i] = new bool[life.getnCol()];
    }
    life.setGrid(grid);
}

/**
 * \brief configura o grid baseado nas configurações que estão disponíveis no arquivo
 * \param arquivo, arquivo contendo as configurações do grid.
 * \param life, onde será salva a configuração do grid.
 */
void configurarGrid(ifstream &arquivo, Life &life) {
    for(int i = 0; i < life.getnLin(); i++) {
        for(int j = 0; j < life.getnCol(); j++) {
            char caracter = arquivo.get();
            if(caracter == '\n') {
                caracter = arquivo.get();
            }
            life.getGrid()[i][j] = caracter == life.getCaracter();
        }
    }
}

/**
 * \brief imprime as informações iniciais do jogo.
 * \param life, objeto contendo as configurações.
 */
void printHeader(Life &life) {
    cout << ">>> Processing data, please wait..." << endl;
    cout << ">>> Grid size read form input file: " << life.getnLin() << " rows by " << life.getnCol() << " cols." << endl;
    cout << ">>> Character that represents a living cell read from input file: '" << life.getCaracter() << "'" << endl << endl;
    cout << "****************************************************************" << endl;
    cout << "  Welcome to Conway's game of Life." << endl;
    cout << "  By default this game uses a grid of size 20 by 60 in which" << endl;
    cout << "  each cell can either be occupied by an organism or not." << endl;
    cout << "  The occupied cells change from generation to generation" << endl;
    cout << "  according to the number of neighboring cells which are alive." << endl;
    cout << "****************************************************************" << endl << endl;
}

/**
 * \brief cetraliza todas as configurações necessárias em apenas uma função
 * \param nomeArquivo, nome do arquivo com as configurações
 * \param life, objeto onde será salva as configurações
 */
void setup(string nomeArquivo, Life &life) {
    processarDados(nomeArquivo, life);
    printHeader(life);
}