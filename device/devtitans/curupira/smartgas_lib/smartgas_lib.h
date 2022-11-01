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
         * Acessa o nível gas
         * pelo sensor de Gas-- MQ2.
         *
         * Retorna:
         *      0: completamente escuro
         *      1 a 99: nível de luminosidade
         *      100: completamente claro
         */
        int getGas();
    private:
        /**
         * Métodos para ler valor no arquivo "gas",
         * "gas" do diretório /sys/kernel/smartgas.
         */
        int readFileValue(string file);
        /**
         * Armazena valores simulados para o caso do dispositivo não estar
         * conectado, mas a propriedade devtitans.smartgas.allow_simulated
         * for true.
         */
};}
