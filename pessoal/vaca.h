#ifndef VACA_H
#define VACA_H

#include <objeto.h>

class Vaca : public Objeto
{
public:
    double animacao;
    Vaca();
    void vaca();
    void desenha_caixa();
    void desenha();
    void proxima_animacao();
};

#endif // VACA_H
