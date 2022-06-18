#include "carroca.h"

Carroca::Carroca()
{
    this->tipo = "carroca";
    this->model = new Model3DS("../3ds/carroca.3DS");
}

void Carroca::desenha() {
    glPushMatrix();
        Objeto::desenha();
        GUI::setColor(0.5,0.5,0.5);

        if (selecionado) {
            //glEnable(GL_CULL_FACE);
            GUI::setColor(0.5,0.5,0.5);
            GUI::drawBox(-1,-1,-1, 1,1,1, true);
            GUI::setColor(1.0,1.0,1.0);
        }

        glRotatef(-90,1,0,0);
        glScalef(0.005,0.005,0.005);
        model->draw(!selecionado);
    glPopMatrix();
}
