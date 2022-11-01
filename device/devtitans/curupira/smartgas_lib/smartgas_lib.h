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
         * o dispositivo SmartLamp está conectado via USB. Caso contrário,
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
         * Acessa e seta a intensidade do led.
         *
         * Valor retornado/setado:
         *      0: led desligado
         *      1 a 99: led ligado com intensidade ledValue
         */
        int getLed();
        bool setLed(int ledValue);
        /**
         * Acessa o nível gas
         * pelo sensor de Gas-- MQ2.
         *
         * Retorna:
         *      0: completamente escuro
         *      1 a 99: nível de luminosidade
         *      100: completamente claro
         */
        int getGas();
        /**
         * Threshold - Limiar de luminosidade para ligar/desligar o led.
         * Ao executar esse método, o dispositivo SmartLamp entra no modo
         * automático, em que o led será ligado se a luminosidade for
         * menor que o limiar. Caso contrário, o led é desligado.
         *
         * Valor retornado/setado:
         *      0: completamente escuro
         *      1 a 99: nível de luminosidade
         *      100: completamente claro
         */
        int getThreshold();
        bool setThreshold(int thresholdValue);

    private:
        /**
         * Métodos para ler e escrever valores nos arquivos "led",
         * "gas" ou "threshold" do diretório /sys/kernel/smartgas.
         */
        int readFileValue(string file);
        bool writeFileValue(string file, int value);
        /**
         * Armazena valores simulados para o caso do dispositivo não estar
         * conectado, mas a propriedade devtitans.smartgas.allow_simulated
         * for true.
         */
         int simLedValue = 88;
         int simThresholdValue = 42;
};}
