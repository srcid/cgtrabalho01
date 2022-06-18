#ifndef CARROCA_H
#define CARROCA_H

#include <objeto.h>

class Carroca : public Objeto
{
public:
    Carroca();
    Model3DS* model;
    void desenha();
};

#endif // CARROCA_H
