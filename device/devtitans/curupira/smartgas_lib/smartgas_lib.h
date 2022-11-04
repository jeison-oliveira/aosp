#pragma once                           // Inclui esse cabeçalho apenas uma vez

#include <fstream>                     // Classe ifstream
#include <android-base/properties.h>   // Função GetBoolProperty
#include <sys/stat.h>                  // Função e struct stat
#include <random>                      // Geração de números aleatórios (valores simulados)

using namespace std;                   // Permite usar string diretamente ao invés de std::string

namespace devtitans::smartgas {       // Pacote Smartgas

class Smartgas {
    public:
        /**
         * Verifica se o diretório /sys/kernel/smartgas existe. Se existir
         * o dispositivo SmartGas está conectado via USB. Caso contrário,
         * verifica a propriedade devtitans.smartgas.allow_simulated
         * para ver se valores simulados podem ser usados.
         *
         * Retorna:
         *      0: dispositivo não encontrado
         *      1: sucesso
         *      2: simulado (disp. não encontrado, mas usando valores simulados)
         */
        int connect();
        
        /**
         * Acessa a concentração de gases inflamáveis do ambiente conforme reportado 
         * pelo sensor de gás (MQ-2).
         *
         * Retorna:
         *      300-10.000ppm
         */
        int getConcentration();

        /**
         * Threshold - Limiar definido que, caso ultrapassado pela leitura obtida pelo sensor MQ-2, deve ser emitida alguma notificação para o usuário automaticamente. .
         * Ao executar esse método, o dispositivo SmartGas entra no modo
         * automático, em que o led será ligado se a luminosidade for
         * menor que o limiar. Caso contrário, o led é desligado.
         *
         * Valor retornado/setado:
         *      300-10.000ppm
         */
        int getThreshold();
        bool setThreshold(int thresholdValue);

    private:
        /**
         * Métodos para ler e escrever valores nos arquivos
         * "mq2" ou "threshold" do diretório /sys/kernel/smartgas.
         */
        int readFileValue(string file);
        bool writeFileValue(string file, int value);

        /**
         * Armazena valores simulados para o caso do dispositivo não estar
         * conectado, mas a propriedade devtitans.smartgas.allow_simulated
         * for true.
         */
         int simThresholdValue = 1000;
};

} // namespace