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

using namespace std;

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

    GUI::displayEnd();
}

bool incluirObjeto = false;

void teclado(unsigned char key, int x, int y) {
    if (!incluirObjeto) {
        GUI::keyInit(key,x,y);
    }
    switch (key) {
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
    GUI gui = GUI(2000,1000,desenha,teclado);
}
