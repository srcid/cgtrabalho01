#include "carro.h"

Carro::Carro()
{
    this->tipo = "carro";
    this->z = 0;
    this->animacao = 0;
    model = new Model3DS("../3ds/cartest.3DS");
}

void Carro::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        GUI::setColor(0.5,0.5,0.5);

        if (selecionado) {
            //glEnable(GL_CULL_FACE);
            GUI::setColor(0.5,0.5,0.5);
            GUI::drawBox(-1,-1,-1, 1,1,1, true);

            GUI::setColor(1.0,1.0,1.0);
        }
        glRotatef(this->animacao,0,1,0);
        glTranslatef(0,0,this->z);
        //correspondente ao T'^-1 da Q1 da lista 1
        glRotatef(this->animacao,0,1,0);
        glScalef(1,1,1); //ajuste final da escala, podendo ser não-uniforme, independente para cada eixo
        glRotatef(-90,1,0,0); //alinhar o objeto 3ds com os eixos, deixando ele para cima de acordo com o eixo Y
        glTranslatef(0,0,0); //trazer objeto 3ds para origem
        //
        glScalef(0.001,0.001,0.001); //apenas para conseguir enxergar o modelo 3ds
        model->draw(!selecionado); //se estiver selecionado, tem que desenhar o modelo 3ds
                                   //não colorido internamente para que a cor de destaque
                                   //da seleção tenha efeito
    glPopMatrix();

    this->z += 0.01 * ((this->z > 10 || this->z < 0) ? -1 : 1);
    this->proxima_animacao();
}

void Carro::proxima_animacao() {
    if (this->animacao > 359) this->animacao = 0;
    this->animacao += 0.1;
}
