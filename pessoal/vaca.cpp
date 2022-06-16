#include "vaca.h"

Vaca::Vaca()
{
    this->animacao = 0.0;
}

void Vaca::proxima_animacao() {
    static double factor = 1;
    if (this->animacao > 30 || this->animacao < 0) {
        factor *= -1;
    }
    this->animacao = this->animacao + factor * 0.1;
}

void desenha_chifre() {
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(6,0,0);
    glVertex3f(6,0,6);
    glVertex3f(4,0,2);
    glVertex3f(0,0,2);
    glEnd();
}

void Vaca::desenha() {
    glPushMatrix();
        Objeto::desenha(); // T.Rz.Ry.Rx.S. p

        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(1.0, 90.0/255.0, 172.0/255.0);
        }
        glScalef(0.3,0.3,0.3);
        vaca();

    glPopMatrix();
}

void Vaca::vaca() {
    /* pes */
    glPushMatrix();
    GUI::setColor(0,0,0);
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

    /* pernas */
    glPushMatrix();
    GUI::setColor(1,1,1);
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

    // corpo
    glPushMatrix();
    glScalef(4,2,6);
    glTranslatef(0,1,0);
    this->desenha_caixa();
    glPopMatrix();

    // pescoço
    glPushMatrix();
    glTranslatef(1,3,4);
    glScalef(2,4,2);
    this->desenha_caixa();
    glPopMatrix();

    // cabeça
    glPushMatrix();
    glTranslatef(1, 5, 6);
    glScalef(2,2,2);
    this->desenha_caixa();
    glPopMatrix();

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
    //face tras
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
