#include <moinho.h>

Moinho::Moinho() {
    this->animacao = 0;
}

void Moinho::proxima_animacao() {
    if (animacao > 360) animacao = 0;
    animacao += 1.0;
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
    //hélice de cima
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    glTranslatef(0.25,0.25,1);
    glTranslatef(0,0,0.25);
    glScalef(0.5,1.5,0.01);
    desenha_caixa();
    glPopMatrix();

    // hélice da esquerda
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    glTranslatef(0.25,0.25,1);
    glTranslatef(0,0,0.25);
    glTranslatef(0.5,0,0);
    glRotatef(90, 0, 0, 1);
    glScalef(0.5,1.5,0.01);
    desenha_caixa();
    glPopMatrix();

    // hélice da direita
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    glTranslatef(0.25,0.25,1);
    glTranslatef(0,0,0.25);
    glTranslatef(0,0.5,0);
    glRotatef(-90, 0, 0, 1);
    glScalef(0.5,1.5,0.01);
    desenha_caixa();
    glPopMatrix();

    // hélice de baixo
    glPushMatrix();
    glTranslatef(-0.25,3.5,-0.25);
    glTranslatef(0.25,0.25,1);
    glTranslatef(0,0,0.25);
    glTranslatef(0.5,0,0);
    glRotatef(180,0,0,1);
    glScalef(0.5,1.5,0.01);
    desenha_caixa();
    glPopMatrix();
}

void Moinho::desenha_bico() {
    // bico
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    glTranslatef(0.25,0.25,1);
    glScalef(0.5,0.5,0.5);
    desenha_caixa();
    glPopMatrix();
}

void Moinho::desenha_base() {

    // tronco
    glPushMatrix();
    glScalef(0.5,3,0.5);
    desenha_caixa();
    glPopMatrix();

    // cabeça
    glPushMatrix();
    glTranslatef(-0.25,3,-0.25);
    desenha_caixa();
    glPopMatrix();

    desenha_bico();
    desenha_helices();

}

void Moinho::desenha() {
    glPushMatrix();
        Objeto::desenha(); // T.Rz.Ry.Rx.S. p

        if (selecionado) {
            GUI::setColor(1,0,0);
        } else {
            GUI::setColor(1,1,0);
        }
        moinho();

    glPopMatrix();
}

void Moinho::moinho() {
    desenha_base();
}
