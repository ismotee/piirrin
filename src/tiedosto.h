#pragma once
#include "Viiva.h"


namespace tiedosto {
  
    Viiva lataaViiva(std::string tiedostonNimi);
    void tallennaViiva(Viiva viiva);
    void tallennaViivaCopy(Viiva viiva);
    std::string aika();
};