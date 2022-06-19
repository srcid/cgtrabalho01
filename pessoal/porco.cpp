#include <porco.h>

Porco::Porco() {
this->tipo = "porco";
}

void Porco::desenha() {
    glPushMatrix();
        Objeto::desenha(); // T.Rz.Ry.Rx.S. p

        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(1.0, 90.0/255.0, 172.0/255.0);
        }
        glScalef(0.08,0.08,0.08);
        porco();

    glPopMatrix();
}

void Porco::porco() {
    /* pes */
    glPushMatrix();
    glTranslatef(1, 0, 1);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, -1);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 0, 1);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 0, -1);
    this->desenha_caixa();
    glPopMatrix();
    /* fim pes */

    // corpo
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glTranslatef(-2, 0, -2);
    glScalef(5,4,5);
    this->desenha_caixa();
    glPopMatrix();

    // cabeça
    glPushMatrix();
    glTranslatef(-0.5, 2, 3);
    glScalef(2,2,1);
    this->desenha_caixa();
    glPopMatrix();

    // olho esquerdo
    glPushMatrix();
    GUI::setColor(0,0,0);
    glTranslatef(-1, 2.5, 3);
    GUI::drawSphere(1,1,1,0.25);
    glPopMatrix();

    // olho direito
    glPushMatrix();
    GUI::setColor(0,0,0);
    glTranslatef(0, 2.5, 3);
    GUI::drawSphere(1,1,1,0.25);
    glPopMatrix();

    // fucinho
    glPushMatrix();
    GUI::setColor(1.0, 90.0/255.0, 172.0/255.0);
    glTranslatef(-0.25, 2.2, 4);
    glScalef(1.5,0.8,0.1);
    this->desenha_caixa();
    glPopMatrix();
}

void Porco::desenha_caixa() {
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
