// Diwei V. Nicolay - 193014

#include <iostream>

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


int main(){

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
            cout << "Encerrando analisador de rotas.\n";
            break;
        }
    } while (opcao != 0);

    return 0;
}