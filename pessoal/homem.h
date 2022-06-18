#ifndef HOMEM_H
#define HOMEM_H

#include <objeto.h>

class Homem : public Objeto
{
public:
    Homem();
    Model3DS* model;
    void desenha();
};

#endif // HOMEM_H
