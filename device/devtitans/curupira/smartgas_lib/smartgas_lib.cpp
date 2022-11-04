#include "smartgas_lib.h"

using namespace std;                                   // Permite usar string, ifstream diretamente ao invés de std::string
using namespace android::base;                         // Permite usar GetBoolProperty ao invés de android::base::GetBoolProperty

namespace devtitans::smartgas {                       // Entra no pacote devtitans::smartgas

int Smartgas::connect() {
    char dirPath[] = "/sys/kernel/smartgas";
    struct stat dirStat;
    if (stat(dirPath, &dirStat) == 0)
        if (S_ISDIR(dirStat.st_mode))
            return 1;                                  // Se o diretório existir, retorna 1

    // Diretório não existe, vamos verificar a propriedade
    bool allowSimulated = GetBoolProperty("devtitans.smartgas.allow_simulated", true);
    if (!allowSimulated)
        return 0;                                      // Dispositivo não encontrado
    else
        return 2;                                      // Usando valores simulados
}

int Smartgas::readFileValue(string file) {
    int connected = this->connect();

    if (connected == 2) {                               // Usando valores simulados
        if (file == "threshold")
            return this->simThresholdValue;
        else {
            // "mq2" (sensor de gás): Gera um número aleatório entre 300 e 10000
            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<mt19937::result_type> dist100(300,10000);
            return (int) dist100(rng);
        }
    }

    else if (connected == 1) {                          // Conectado. Vamos solicitar o valor ao dispositivo
        int value;
        string filename = string("/sys/kernel/smartgas/") + file;
        ifstream file(filename);                        // Abre o arquivo do módulo do kernel

        if (file.is_open()) {                           // Verifica se o arquivo foi aberto com sucesso
            file >> value;                              // Lê um inteiro do arquivo
            file.close();
            return value;
        }
    }

    // Se chegou aqui, não foi possível conectar ou se comunicar com o dispositivo
    return -1;
}

bool Smartgas::writeFileValue(string file, int value) {
    int connected = this->connect();

    if (connected == 2) {                                // Usando valores simulados
        if (file == "threshold") {
            this->simThresholdValue = value;
            return true;
        }
    }

    else if (connected == 1) {                          // Conectado. Vamos solicitar o valor ao dispositivo
        string filename = string("/sys/kernel/smartgas/") + file;
        ofstream file(filename, ios::trunc);            // Abre o arquivo limpando o seu conteúdo

        if (file.is_open()) {                           // Verifica se o arquivo foi aberto com sucesso
            file << value;                              // Escreve o ledValue no arquivo
            file.close();
            return true;
        }
    }

    // Se chegou aqui, não foi possível conectar ou se comunicar com o dispositivo
    return false;
}

int Smartgas::getConcentration() {
    return this->readFileValue("mq2");
}

int Smartgas::getThreshold() {
    return this->readFileValue("threshold");
}

bool Smartgas::setThreshold(int thresholdValue) {
    return this->writeFileValue("threshold", thresholdValue);
}

} // namespace