#include "vaca.h"

Vaca::Vaca()
{
    this->tipo = "vaca";
    this->animacao = 0.0;
}

void Vaca::proxima_animacao() {
    static double factor = 1;
    if (this->animacao > 60 || this->animacao < 0) {
        factor *= -1;
    }
    this->animacao = this->animacao + factor * 0.1;
}

void Vaca::desenha() {
    glPushMatrix();
        Objeto::desenha(); // T.Rz.Ry.Rx.S. p

        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(1.0, 90.0/255.0, 172.0/255.0);
        }
        glScalef(0.1,0.1,0.1);
        vaca();

    glPopMatrix();
}

void Vaca::desenha_pes() {
    /* pes */
    glPushMatrix();
    if (!this->selecionado) GUI::setColor(0,0,0);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 5);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 0, 0);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 0, 5);
    this->desenha_caixa();
    glPopMatrix();
    /* fim pes */
}

void Vaca::desenha_pernas() {
    /* pernas */
    glPushMatrix();
    if (!this->selecionado) GUI::setColor(1,1,1);
    glTranslatef(0,1,0);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 1, 5);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 1, 0);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 1, 5);
    this->desenha_caixa();
    glPopMatrix();
    /* fim pernas */
}

void Vaca::desenha_corpo() {
    // corpo
    glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(4,3,6);
    this->desenha_caixa();
    glPopMatrix();
}

void Vaca::desenha_cabeca() {
    glTranslatef(0,0.5,1);
    glScalef(1,0.5,1);
    this->desenha_caixa();
    glPopMatrix();
}

void Vaca::desenha_pescoco() {
    // pescoço
    glPushMatrix();
    glTranslatef(2,4.5,5);
    glRotatef(this->animacao, 1,0,0);
    glScalef(2,4,2);
    glTranslatef(-0.5,-0.5,-0.5);
    this->desenha_caixa();
    this->desenha_cabeca();
}

void Vaca::vaca() {
    this->desenha_pes();
    this->desenha_pernas();
    this->desenha_corpo();
    this->desenha_pescoco();

    proxima_animacao();
}

void Vaca::desenha_caixa() {
    //face frente
    glBegin(GL_QUADS);
        glNormal3f(0,1,10);
        glVertex3f(0,0,1);
        glVertex3f(1,0,1);
        glVertex3f(1,1,1);
        glVertex3f(0,1,1);
    glEnd();
    //face trás
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,0,0);
    glEnd();
    //face direita
    glBegin(GL_QUADS);
        glNormal3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(1,0,0);
        glVertex3f(1,1,0);
        glVertex3f(1,1,1);
    glEnd();
    //face esquerda
    glBegin(GL_QUADS);
        glNormal3f(-1,0,0);
        glVertex3f(0,0,1);
        glVertex3f(0,1,1);
        glVertex3f(0,1,0);
        glVertex3f(0,0,0);
    glEnd();
    //face superior
    glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        glVertex3f(0,1,0);
        glVertex3f(0,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,0);
    glEnd();
    //face inferior
    glBegin(GL_QUADS);
        glNormal3f(0,-1,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(0,0,1);
    glEnd();
}
