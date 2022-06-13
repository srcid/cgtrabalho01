#ifndef MOINHO_H
#define MOINHO_H

#include <objeto.h>

class Moinho : public Objeto
{
public:
    float animacao;
    Moinho();
    void desenha();
    void moinho();
    void desenha_helices();
    void desenha_caixa();
    void desenha_base();
    void desenha_bico();
    float proxima_animacao();
};

#endif // MOINHO_H
