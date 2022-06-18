TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += pessoal

LIBS += -lGL -lGLU -lglut -l3ds -lSDL_image

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/model3ds.cpp \
    bib/Vetor3D.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp \
    pessoal/arvore.cpp \
    pessoal/carroca.cpp \
    pessoal/casa.cpp \
    pessoal/homem.cpp \
    pessoal/moinho.cpp \
    pessoal/personagem.cpp \
    pessoal/objeto.cpp \
    pessoal/carro.cpp \
    pessoal/novoobjeto.cpp \
    pessoal/porco.cpp \
    pessoal/vaca.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/model3ds.h \
    bib/Vetor3D.h \
    gui_glut/extra.h \
    gui_glut/gui.h \
    pessoal/arvore.h \
    pessoal/carroca.h \
    pessoal/casa.h \
    pessoal/homem.h \
    pessoal/moinho.h \
    pessoal/personagem.h \
    pessoal/objeto.h \
    pessoal/carro.h \
    pessoal/novoobjeto.h \
    pessoal/porco.h \
    pessoal/vaca.h
