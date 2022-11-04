#include "smartgas_client.h"

using namespace std;                  // Permite usar o cout e endl diretamente ao invés de std::cout

namespace devtitans::smartgas {      // Entra no pacote devtitans::smartgas

void SmartgasClient::start(int argc, char **argv) {
    cout << "Cliente Smartgas!" << endl;

    if (argc < 2) {
        cout << "Sintaxe: " << argv[0] << "  " << endl;
        cout << "    Comandos: get-concentration, get-threshold, set-threshold" << endl;
        exit(1);
    }

    Smartgas smartgas;             // Classe da biblioteca Smartgas

   
    // Comando get-concentration
    if (!strcmp(argv[1], "get-concentration")) {
        cout << "Concentração de gás inflamável atual: " << smartgas.getConcentration() << endl;
    }

    // Comandos get-threshold e set-threshold
    else if (!strcmp(argv[1], "get-threshold")) {
        cout << "Valor do Threshold: " << smartgas.getThreshold() << endl;
    }
    else if (!strcmp(argv[1], "set-threshold")) {
        int thresholdValue = atoi(argv[2]);
        if (smartgas.setThreshold(thresholdValue))
            cout << "Valor do Threshold setado para " << thresholdValue << endl;
        else
            cout << "Erro ao setar valor do Threshold para " << thresholdValue << endl;
    }

    else {
        cout << "Comando inválido." << endl;
        exit(1);
    }
}

} // namespace



// MAIN

using namespace devtitans::smartgas; // Permite usar SmartgasClient diretamente ao invés de devtitans::smartgas::SmartgasClient

int main(int argc, char **argv) {
    SmartgasClient client;               // Variável client, da classe SmartgasClient, do pacote devtitans::smartgas
    client.start(argc, argv);             // Executa o método printHello
    return 0;
}
