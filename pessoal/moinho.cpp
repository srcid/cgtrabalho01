#include <moinho.h>

Moinho::Moinho() {
    this->tipo = "moinho";
    this->animacao = 0.0;
}

void Moinho::proxima_animacao() {
    if (animacao > 359) animacao = 0;
    animacao += 0.25;
}

void Moinho::desenha_caixa() {
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

void Moinho::desenha_helices() {

    glPushMatrix();
    glTranslatef(0.25,3.5,0.75);
    glRotatef(this->animacao, 0,0,1);
    glTranslatef(-0.5,-0.5,0);
    glScalef(0.5,3,0.01);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,3.5,0.75);
    glRotatef(this->animacao + 90, 0,0,1);
    glTranslatef(-0.5,-0.5,0);
    glScalef(0.5,3,0.01);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,3.5,0.75);
    glRotatef(this->animacao + 180, 0,0,1);
    glTranslatef(-0.5,-0.5,0);
    glScalef(0.5,3,0.01);
    this->desenha_caixa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25,3.5,0.75);
    glRotatef(this->animacao + 270, 0,0,1);
    glTranslatef(-0.5,-0.5,0);
    glScalef(0.5,3,0.01);
    this->desenha_caixa();
    glPopMatrix();
}

void Moinho::desenha_bico() {
    // bico
    glPushMatrix();
    glTranslatef(0.25,3.5,0.75);
    glScalef(0.5,0.5,0.5);
    glRotatef(this->animacao, 0,0,1);
    glTranslatef(-0.5,-0.5,0);
    this->desenha_caixa();
    glPopMatrix();
}

void Moinho::desenha_base() {
    // tronco
    glPushMatrix();
    glScalef(0.5,3,0.5);
    this->desenha_caixa();
    glPopMatrix();

    // cabeça
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    this->desenha_caixa();
    glPopMatrix();

    desenha_bico();
    desenha_helices();

    this->proxima_animacao();
}

void Moinho::desenha() {
    glPushMatrix();
        Objeto::desenha(); // T.Rz.Ry.Rx.S. p

        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(237/255.0, 237/255.0, 235/255.0);
        }
        moinho();

    glPopMatrix();
}

void Moinho::moinho() {
    desenha_base();
}
