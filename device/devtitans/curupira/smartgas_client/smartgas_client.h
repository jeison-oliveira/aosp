#pragma once                      // Inclui esse cabeçalho apenas uma vez

#include <iostream>               // std::cout (char-out) e std::endl (end-line)
#include <string.h>               // Função strcmp
#include <stdlib.h>               // Função atoi

#include "smartgas_lib.h"        // Classe Smartgas

namespace devtitans::smartgas {  // Pacote que a classe abaixo pertence

class SmartgasClient {           // Classe

    public:
        void start(int argc, char **argv);

};

} // namespace
