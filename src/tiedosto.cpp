#include "tiedosto.h"
#include <iterator>
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>

Viiva tiedosto::lataaViiva(std::string tiedostonNimi) {
    std::ifstream is(tiedostonNimi, ios::binary | ios::ate | ios::in);
    Viiva viiva;
    
    if (is.is_open()) {
        
        char* memory;
        streampos size = is.tellg();
        size_t pisteSize = size/sizeof(ViivanPiste);
        is.seekg(0, ios::beg);
        memory = new char[size];
        
        is.read(memory, size);
        
        for(int i = 0; i < pisteSize;i++) {
            ViivanPiste* vp;
            vp = (ViivanPiste*)(memory + (i*sizeof(ViivanPiste))); 
            viiva.pisteet.push_back((*vp));
        }
        
        is.close();

        delete[] memory;
    }
    return viiva;
}

void tiedosto::tallennaViiva(Viiva viiva) {

    ofstream os;
    os.open("arkisto/" + aika() + ".ov");

    os << viiva.toString();
    os.close();

}

std::string tiedosto::aika() {
    std::chrono::time_point<std::chrono::system_clock> now;
    now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_t);

}

void tiedosto::tallennaViivaCopy(Viiva viiva) {
    std::string file = "arkisto/" + aika() + ".ov";
    std::ofstream os(file, ios::binary);
    for (ViivanPiste& piste : viiva.pisteet) {

        char* buffer;
        buffer = (char*) &piste;
        os.write((char*) buffer, sizeof (ViivanPiste));
    }
    cout << "tallennetaan " << viiva.pisteet.size() << " pistetta\n";
    os.close();
    lataaViiva(file);
}

