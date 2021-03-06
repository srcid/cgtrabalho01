#ifndef OBJETO_H
#define OBJETO_H

#include <gui.h>

class Objeto
{
public:
    Vetor3D t = Vetor3D(0,0,0);
    Vetor3D a = Vetor3D(0,0,0);
    Vetor3D s = Vetor3D(1,1,1);
    bool isOriginVisible = false;
    bool selecionado = false;
    bool isShadowVisible = true;
    string tipo;

    Objeto();
    virtual ~Objeto();
    virtual void desenha();
    void mostrarOrigem();
    void mostrarSombra();
    string toString();
};

#endif // OBJETO_H
