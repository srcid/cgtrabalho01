#include <iostream>
#include <vector>
#include <personagem.h>
#include <casa.h>
#include <carro.h>
#include <novoobjeto.h>
#include <moinho.h>
#include <porco.h>
#include <vaca.h>

using namespace std;

Model3DS model3ds("../3ds/cartest.3DS");

vector<Objeto*> objetos;
int posSelecionado = -1;

Vetor3D transformedPoint(Vetor3D p)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();

        glRotatef(objetos[0]->a.z,0,0,1);  // \ .
        glRotatef(objetos[0]->a.y,0,1,0);  //  | Rz.Ry.Rx . v
        glRotatef(objetos[0]->a.x,1,0,0);

        float matrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();

    float pos[4] = {p.x,p.y,p.z, 1.0};
    float res[4];

    glutGUI::multGLMatrixByVector(res,matrix,pos);

    Vetor3D res3D = Vetor3D(res[0],res[1],res[2]);
    return res3D;
}

void displayInner() {
    GUI::setLight(1,1,3,5,true,false);
    GUI::setLight(2,-1.5,0.5,-1,true,false);
    //GUI::setLight(3,-5,3,5,true,false);

    GUI::drawOrigin(1);

    GUI::setColor(1,0,0);
    GUI::drawFloor();

    for (size_t i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }
}

void desenha() {
    GUI::displayInit();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    //gluLookAt(0,15,0, 0,0,0, 1,0,0);
    displayInner();

    if (!objetos.empty()) {
        glLoadIdentity();
        glViewport(0, 3*glutGUI::height/4, glutGUI::width/4, glutGUI::height/4);
        Vetor3D zlocalemCoordsGlobais = transformedPoint(Vetor3D(0,0,1));
        Vetor3D olho = objetos[0]->t + zlocalemCoordsGlobais*1.2;
        Vetor3D centro = olho + zlocalemCoordsGlobais;

        Vetor3D ylocalemCoordsGlobais = transformedPoint(Vetor3D(0,1,0));
        Vetor3D up = ylocalemCoordsGlobais;

        gluLookAt(olho.x,olho.y,olho.z, centro.x,centro.y,centro.z, up.x,up.y,up.z);
        displayInner();
    }


    if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }
//    glutGUI::dtx = 0.0; glutGUI::dty = 0.0; glutGUI::dtz = 0.0;
//    glutGUI::dax = 0.0; glutGUI::day = 0.0; glutGUI::daz = 0.0;
//    glutGUI::dsx = 0.0; glutGUI::dsy = 0.0; glutGUI::dsz = 0.0;

    //objeto transformado
    //glPushMatrix();
//        glTranslatef(glutGUI::tx,glutGUI::ty,glutGUI::tz);
//        glRotatef(glutGUI::az,0,0,1);
//        glRotatef(glutGUI::ay,0,1,0);
//        glRotatef(glutGUI::ax,1,0,0);
//        GUI::drawOrigin(1);
//        glScalef(glutGUI::sx,glutGUI::sy,glutGUI::sz);
//        GUI::setColor(0,0,1);
//        //GUI::drawBox(0,0,0, 1,1,1);
//        //GUI::drawBox(1,1,0, 2,2,1);
//        //casa();
//        //personagem();
//        //GUI::draw3ds(model3ds);

    //glPopMatrix();

    GUI::displayEnd();
}

bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    if (!incluirObjeto) {
        GUI::keyInit(key,x,y);
    }

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'n':
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado++;
        posSelecionado = posSelecionado%objetos.size();
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case 'b':
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
        }
        posSelecionado--;
        if (posSelecionado < 0) {
            posSelecionado = objetos.size()-1;
        }
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->selecionado = true;
        }
        break;
    case 'm':
        if (posSelecionado >= 0 && posSelecionado < (int)objetos.size() && !objetos.empty()) {
            objetos[posSelecionado]->mostrarOrigem();
        }
        break;
    case 'r':
        if (objetos.size() > 0) {
            cout << "removou o último" << endl;
            objetos.pop_back();
        }
        break;
    case 'd':
        if (posSelecionado >= 0 && posSelecionado < (int)objetos.size() && !objetos.empty()) {
            cout << "removeu " + posSelecionado << endl;
            objetos.erase(objetos.begin()+posSelecionado);
            posSelecionado = -1;
        }
        break;
    case 'O':
        cout << "inserção" << endl;
        incluirObjeto = !incluirObjeto;
        break;
    case 'p':
        if (incluirObjeto) {
            objetos.push_back( new Personagem() );
        }
        break;
    case 'c':
        if (incluirObjeto) {
            objetos.push_back( new Carro() );
        }
        break;
    case 'C':
        if (incluirObjeto) {
            objetos.push_back( new Casa() );
        }
        break;
    case '4':
        if (incluirObjeto) {
            objetos.push_back( new novoObjeto() );
            incluirObjeto = !incluirObjeto;
        }
        break;
    case 'M':
        if (incluirObjeto) {
            objetos.push_back(new Moinho());
        }
        break;
    case 'P':
        if (incluirObjeto) {
            objetos.push_back(new Porco());
        }
        break;
    case 'V':
        if (incluirObjeto) {
            objetos.push_back(new Vaca());
        }
        break;
//    case 'i':
//        //glutGUI::tx = 0.0;
//        //glutGUI::ty = 0.0;
//        //glutGUI::tz = 0.0;
//        //glutGUI::ax = 0.0;
//        //glutGUI::ay = 0.0;
//        //glutGUI::az = 0.0;
//        //glutGUI::sx = 1.0;
//        //glutGUI::sy = 1.0;
//        //glutGUI::sz = 1.0;
//        //glutGUI::lx = 0.0;
//        //glutGUI::ly = 0.0;
//        //glutGUI::lz = 0.0;
//        if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
//            objetos[posSelecionado]->t.x = 0.0;
//            objetos[posSelecionado]->t.y = 0.0;
//            objetos[posSelecionado]->t.z = 0.0;

//            objetos[posSelecionado]->a.x += glutGUI::dax;
//            objetos[posSelecionado]->a.y += glutGUI::day;
//            objetos[posSelecionado]->a.z += glutGUI::daz;

//            objetos[posSelecionado]->s.x += glutGUI::dsx;
//            objetos[posSelecionado]->s.y += glutGUI::dsy;
//            objetos[posSelecionado]->s.z += glutGUI::dsz;
//        }
//        break;

    default:
        break;
    }
}

int main()
{
    GUI gui = GUI(1080,720,desenha,teclado);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}
