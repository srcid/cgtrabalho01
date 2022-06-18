#include "objeto.h"

Objeto::Objeto()
{
}

void Objeto::desenha()
{
    // T.Rz.Ry.Rx.S (correspondente ao T'' da Q1 da lista 1)
    glTranslatef(t.x,t.y,t.z); //transformacao (matriz) mais a esquerda (mais global)
    glRotatef(a.z,0,0,1);  // \ .
    glRotatef(a.y,0,1,0);  //  | Rz.Ry.Rx . v
    glRotatef(a.x,1,0,0);  // /
    if (this->isOriginVisible) GUI::drawOrigin(1);
    glScalef(s.x,s.y,s.z); //transformacao (matriz) mais a direita (mais local)
}

void Objeto::mostrarOrigem() {
    this->isOriginVisible = !this->isOriginVisible;
}

string Objeto::toString()  {
    return this->tipo + "," +
            to_string(this->t.x) + "," + to_string(this->t.y) + "," + to_string(this->t.z) + "," +
            to_string(this->a.x) + "," + to_string(this->a.y) + "," + to_string(this->a.z) + "," +
            to_string(this->s.x) + "," + to_string(this->s.y) + "," + to_string(this->s.z) + "," +
            to_string(this->isOriginVisible) + "," +
            to_string(this->selecionado) + "\n";
}
