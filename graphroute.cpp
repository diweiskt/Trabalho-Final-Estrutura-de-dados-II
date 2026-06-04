// Diwei V. Nicolay - 193014

#include <iostream>
#include <fstream>

using namespace std;

int menu(){
    int opcao;
    while (true) {
        cout << "======================================================\n"
             << "\x1b[31m1\x1b[0m. Exibir Grafo Completo\n"
             << "\x1b[31m2\x1b[0m. Encontrar Menor Caminho\n"
             << "\x1b[31m3\x1b[0m. Calcular o Diâmetro do Grafo\n"
             << "\x1b[31m4\x1b[0m. Identificar Roteadores Críticos\n"
             << "\x1b[31m0\x1b[0m. Sair\n"
             << "======================================================\n"
             << "Escolha uma opção: ";
        cin >> opcao;
        cout << endl;
        cin.ignore(); 
        if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 0) {
            return opcao;
        }
        cout << "\x1b[31mOpção inválida. Tente novamente.\n";
    }
}


int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "\x1b[31m[Erro] Você não passou um caminho de um arquivo de log de traceroute\x1b[0m\n";
        return 1;
    }

    ifstream arq;
    arq.open(argv[1]);
    if(!arq){
        cout << "\x1b[31m[Erro] Não foi possivel abrir o arquivo \x1b[34m'" << argv[1] << "'\x1b[0m\n";
        return 1;
    }

    int opcao;

    do {
        opcao = menu();

        switch (opcao) {
        case 1:
            //exibirGrafoCompleto();
            break;
        case 2:
            //encontrarMenorCaminho();
            break;
        case 3:
            //calcularDiametroGrafo();
            break;
        case 4:
            //identificarRoteadoresCriticos();
            break;
        case 0:
            cout << "\x1b[34mEncerrando analisador de rotas.\x1b[0m\n";
            break;
        }
    } while (opcao != 0);

    return 0;
}