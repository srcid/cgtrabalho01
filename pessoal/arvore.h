#ifndef ARVORE_H
#define ARVORE_H

#include <objeto.h>

class Arvore : public Objeto
{
public:
    Arvore();
    Model3DS* model;
    void desenha();
};

#endif // ARVORE_H
