#ifndef MOINHO_H
#define MOINHO_H

#include <objeto.h>

class Moinho : public Objeto
{
public:
    double animacao;
    Moinho();
    void desenha();
    void moinho();
    void desenha_helices();
    void desenha_caixa();
    void desenha_base();
    void desenha_bico();
    void proxima_animacao();
};

#endif // MOINHO_H
