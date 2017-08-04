#include "Viiva.h"

class pensseli{
public:
    const int MAX_KOKO = 130;
    
    bool viivaJatkuu = false;
    
    float koko = 10;
    float blur = 0.1;
    float spacing = 0.4; // suhteena pensselin koosta. huom: vaikuttaa sumennukseen olennaisesti!
    const ofColor clearColor = ofColor(127, 127, 127, 0);
    ofColor vari = ofColor::lightPink;
    
    ofPoint sijainti;
    
    ofFbo brushFbo; //tähän piirretään yksi pensselin piste
    
    void setup(); // luo fbo:n

    void drawBrush(); // päivittää brushFbo:n
    void strokeTo(ofPoint kohde);
    void lopetaViiva();
};


class Monitori : public pensseli {
public:
    ofColor taustaVari = ofColor::grey;
    ofFbo viivaFbo;
    bool show = false;
    
    void setup();
    void draw();
    
    void piirraViiva(const Viiva&);
    void piirraVari(ofColor vari_);
    void tyhjenna();
};