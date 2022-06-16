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
    void desenha_pes();
    void desenha_pernas();
    void desenha_corpo();
    void desenha_pescoco();
};

#endif // VACA_H
