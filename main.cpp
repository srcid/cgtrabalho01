#include <iostream>
#include <vector>
#include <fstream>
#include <moinho.h>
#include <porco.h>
#include <vaca.h>
#include <arvore.h>
#include <carroca.h>
#include <homem.h>

using namespace std;

vector<Objeto*> objetos;
int posSelecionado = -1;
size_t pontoSelecionado = 0;
bool selecionadoMostrarSombra = false;
bool pontual = false;

vector<string> strSplit(string s) {
    const string delimiter = ",";
    string token;
    size_t pos;
    vector<string> arr;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    if (s.size() > 0) {
        arr.push_back(s);
    }

    return arr;
}

void loadFromFile(const string fname = "objetos.txt") {
    ifstream file;
    file.open(fname);

    objetos.clear();

    if (file.is_open()) {
        string line;
        string tipo;
        float tx, ty, tz, ax, ay, az, sx, sy, sz;
        bool isOriginVisible, selecionado;
        vector<string> arr;

        while (getline(file, line)) {
            Objeto* obj = nullptr;
            arr = strSplit(line);

            tipo = arr[0];
            tx = stof(arr[1]);
            ty = stof(arr[2]);
            tz = stof(arr[3]);
            ax = stof(arr[4]);
            ay = stof(arr[5]);
            az = stof(arr[6]);
            sx = stof(arr[7]);
            sy = stof(arr[8]);
            sz = stof(arr[9]);
            isOriginVisible = stoi(arr[10]);
            selecionado = stoi(arr[11]);

            if (tipo == "porco") {
                obj = new Porco();
            } else if (tipo == "vaca") {
                obj = new Vaca();
            } else if (tipo == "moinho") {
                obj = new Moinho();
            } else if (tipo == "arvore") {
                obj = new Arvore();
            } else if (tipo == "homem") {
                obj = new Homem();
            } else if (tipo == "carroca") {
                obj = new Carroca();
            } else {
                cout << "tipo inválido" << endl;
                break;
            }

            obj->t.x = tx;
            obj->t.y = ty;
            obj->t.z = tz;
            obj->a.x = ax;
            obj->a.y = ay;
            obj->a.z = az;
            obj->s.x = sx;
            obj->s.y = sy;
            obj->s.z = sz;
            obj->isOriginVisible = isOriginVisible;
            obj->selecionado = selecionado;

            objetos.push_back(obj);
        }

        file.close();
    }
}

void saveToFile() {
    const string fname = "objetos.txt";
    ofstream file;
    file.open(fname);

    if (file.is_open()) {
        for (auto e : objetos) {
            file << (*e).toString();
        }

        file.close();
    } else {
        cout << "erro ao abrir o arquivo." << endl;
    }
}

void mostraSombras( GLfloat plano[4], float lightPos[4] ) {
    if (selecionadoMostrarSombra) {
        bool aux = glutGUI::draw_eixos;
        glutGUI::draw_eixos = false;

        for (size_t i = 0; i < objetos.size(); i++) {
            glDisable(GL_LIGHTING);
            glColor4d(0.0,0.0,0.0, 0.5);

            GLfloat sombra[4][4];

            glPushMatrix();
                GUI::shadowMatrix(sombra,plano,lightPos);
                glMultTransposeMatrixf( (GLfloat*)sombra );

                if ( objetos[i]->isShadowVisible ) {
                    objetos[i]->desenha();
                }

                glEnable(GL_LIGHTING);
            glPopMatrix();
        }
        glutGUI::draw_eixos = aux;
    }
}

void mostrarSombrasNosPlanos() {
    float lightPos[4] = {glutGUI::lx,glutGUI::ly,glutGUI::lz,pontual ? 1.0f : 0.0f};

    GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GLfloat plano1[4] = {0,1,0, -0.001};
    mostraSombras(plano1, lightPos);

    // parede lateral
    GUI::setColor(138.0/255, 89.0/255, 6.0/255);
    glPushMatrix();
        glTranslatef(3,0,0);
        glRotatef(90, 0,0,1);
        glScalef(2,2,2);
        GUI::drawQuad();
    glPopMatrix();
    GLfloat plano2[4] = {-1,0,0, 3.00-0.001};
    mostraSombras(plano2, lightPos);

    // parede frontal
    GUI::setColor(138.0/255, 89.0/255, 6.0/255);
    glPushMatrix();
        glTranslatef(0,0,2);
        glRotatef(-90, 1,0,0);
        glScalef(2,2,2);
        GUI::drawQuad();
    glPopMatrix();
    GLfloat plano3[4] = {0,0,-1, 2.00-0.001};
    mostraSombras(plano3, lightPos);

    // parede inclinada
    GUI::setColor(0.0,0.5,0.0);
    glPushMatrix();
        glTranslatef(1.5,0,0);
        glRotatef(45, 0,0,1);
        glScalef(2,2,2);
        GUI::drawQuad();
    glPopMatrix();
    GLfloat plano4[4] = {-1,1,0, 1.50-0.001};
    mostraSombras(plano4, lightPos);
}

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

double animacao_sol = 0;

void displayInner() {
    if (animacao_sol > 360) animacao_sol = 0;
    else animacao_sol += 0.05;
    glPushMatrix();
    glRotatef(animacao_sol, 1,0,0);
    GUI::setLight(1,1,3,5,true,false);
    glPopMatrix();

    GUI::drawOrigin(1);
    glClearColor(66/255.0, 194/255.0, 245/255.0, 0);
    //GUI::setColor(1,0,0);
    GUI::setColor(84/255.0, 245/255.0, 66/255.0);
    GUI::drawFloor(10,10,0.3,0.3,10,10);

    if (selecionadoMostrarSombra) {
        mostrarSombrasNosPlanos();
    }

    for (size_t i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }
}

void desenhaComViewPorts() {
    Vetor3D olho1, olho2, olho3;
    Vetor3D centro1, centro2, centro3;
    Vetor3D up1, up2, up3;

    GUI::displayInit();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(glutGUI::width/2, 0, glutGUI::width/2, glutGUI::height/2);
    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z,glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z,glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    displayInner();

    glLoadIdentity();
    glViewport(0, glutGUI::height/2, glutGUI::width/2, glutGUI::height/2);
    olho1 = Vetor3D(0, 10, 0);
    centro1 = Vetor3D(0, 0, 0);
    up1 = Vetor3D(0,0,1);
    gluLookAt(olho1.x,olho1.y,olho1.z, centro1.x,centro1.y,centro1.z, up1.x,up1.y,up1.z);
    displayInner();

    glLoadIdentity();
    glViewport(0, 0, glutGUI::width/2, glutGUI::height/2);
    olho2 = Vetor3D(0, 1, 10);
    centro2 = Vetor3D(0, 1, 0);
    up2 = Vetor3D(0,1,0);
    gluLookAt(olho2.x,olho2.y,olho2.z, centro2.x,centro2.y,centro2.z, up2.x,up2.y,up2.z);
    displayInner();

    glLoadIdentity();
    glViewport(glutGUI::width/2, glutGUI::height/2, glutGUI::width/2, glutGUI::height/2);
    olho3 = Vetor3D(10, 1, 0);
    centro3 = Vetor3D(0, 1, 0);
    up3 = Vetor3D(0,1,0);
    gluLookAt(olho3.x,olho3.y,olho3.z, centro3.x,centro3.y,centro3.z, up3.x,up3.y,up3.z);
    displayInner();

    if (posSelecionado >= 0 && posSelecionado < (int)objetos.size()) {
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

    GUI::displayEnd();
}

void desenhaSemViewPorts() {
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

    // picking
    else if (pontoSelecionado != 0 and pontoSelecionado <= objetos.size()) {
        objetos[pontoSelecionado-1]->t.x += glutGUI::dtx;
        objetos[pontoSelecionado-1]->t.y += glutGUI::dty;
        objetos[pontoSelecionado-1]->t.z += glutGUI::dtz;

        objetos[pontoSelecionado-1]->a.x += glutGUI::dax;
        objetos[pontoSelecionado-1]->a.y += glutGUI::day;
        objetos[pontoSelecionado-1]->a.z += glutGUI::daz;

        objetos[pontoSelecionado-1]->s.x += glutGUI::dsx;
        objetos[pontoSelecionado-1]->s.y += glutGUI::dsy;
        objetos[pontoSelecionado-1]->s.z += glutGUI::dsz;
    }
    // picking

    GUI::displayEnd();
}

bool mostrarViewPorts = false;

void desenha() {
    if (mostrarViewPorts) {
        desenhaComViewPorts();
    } else {
        desenhaSemViewPorts();
    }
}

bool incluirObjeto = false;

void desenhaPontosDeControle()
{
    for (size_t i=0; i < objetos.size(); i++) {
        if (i == pontoSelecionado - 1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,0,1,1,true);
        }

        glPushName(i+1);
            objetos[i]->desenha();
        glPopName();
    }

    //teste triangulo
    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1); //definir a normal permite ver as cores mais vivas ao posicionar a iluminacao adequadamente
        GUI::setColor(1,1,1);
        glVertex3f(0,0,1);
        GUI::setColor(0,0,1,0.0);
        glVertex3f(2,0,1);
        GUI::setColor(0,1,0,0.0);
        glVertex3f(0,2,1);
    glEnd();
    //teste triangulo usando glColor (sem iluminacao)
    glDisable(GL_LIGHTING);
    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1);
        glColor4f(0,1,0,1);
        glVertex3f(-1,2,1);
        glColor4f(0,0,1,1);
        glVertex3f(-3,0,1);
        glColor4f(1,1,1,0);
        glVertex3f(-1,0,1);
    glEnd();
    glEnable(GL_LIGHTING);
}

int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];
    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);
    GUI::displayInit();
    desenhaPontosDeControle();
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

void teclado(unsigned char key, int x, int y) {
    if (!incluirObjeto) {
        GUI::keyInit(key,x,y);
    }
    switch (key) {
    case 'w': /* troca de perspectiva para ortográfica */
        glutGUI::perspective = !glutGUI::perspective;
        break;
    case 'e': /* remove sombra dos objetos */
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->mostrarSombra();
        }
        break;
    case 'y': /* Habilita view ports*/
        mostrarViewPorts = !mostrarViewPorts;
        break;
    case 's':
        selecionadoMostrarSombra = !selecionadoMostrarSombra;
        break;
    case 'p':
        pontual = !pontual;
        break;
    case '0':                            // olho, camera, up
        glutGUI::cam = new CameraDistante(0.01,25,0.01, 0,0,0, 0,1,0);
        break;
    case '9':
        glutGUI::cam = new CameraDistante(-9,9,9, 0,0,0, 0,1,0);
        break;
    case '8':
        glutGUI::cam = new CameraDistante(9,9,9, 0,0,0, 0,1,0);
        break;
    case '6':
        glutGUI::cam = new CameraDistante(9,9,-9, 0,0,0, 0,1,0);
        break;
    case '5':
        glutGUI::cam = new CameraDistante(-9,9,-9, 0,0,0, 0,1,0);
        break;
    case '4':
        glutGUI::cam = new CameraDistante(5,5,5, 0,0,0, 0,1,0);
        break;
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
    case 'u':
        if (posSelecionado >= 0 and posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->selecionado = false;
            posSelecionado = -1;
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
        if (posSelecionado >= 0 && posSelecionado < (int)objetos.size()) {
            objetos[posSelecionado]->mostrarOrigem();
        }
        break;
    case 'r':
        if (objetos.size() > 0) {
            cout << "removou o último" << endl;
            delete objetos.back();
            objetos.pop_back();
        }
        break;
    case 'd':
        if (posSelecionado >= 0 && posSelecionado < (int)objetos.size() && !objetos.empty()) {
            cout << "removeu " + posSelecionado << endl;
            delete objetos[posSelecionado];
            objetos.erase(objetos.begin()+posSelecionado);
            posSelecionado = -1;
        }
        break;
    case 'O':
        cout << (incluirObjeto ? "modo inserção desligado" : "modo inserção iniciado") << endl;
        incluirObjeto = !incluirObjeto;
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
    case 'A':
        if (incluirObjeto) {
            objetos.push_back(new Arvore());
        }
        break;
    case 'H':
        if (incluirObjeto) {
            objetos.push_back(new Homem());
        }
        break;
    case 'C':
        if (incluirObjeto) {
            objetos.push_back(new Carroca());
        }
        break;
    case '#':
        loadFromFile();
        break;
    case '@':
        saveToFile();
        break;
    case '!':
        loadFromFile("objetos_final.txt");
        break;
    default:
        break;
    }
}

int main()
{
    GUI gui = GUI(2000,1000,desenha,teclado, mouse, "COLHEITA FELIZ V3.27 PRO");
}
