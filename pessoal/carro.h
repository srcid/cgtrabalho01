#ifndef CARRO_H
#define CARRO_H

#include <objeto.h>

class Carro : public Objeto
{
public:
    Model3DS* model;
    double z;
    double animacao;
public:
    Carro();
    void desenha();
    void proxima_animacao();
};

#endif // CARRO_H
