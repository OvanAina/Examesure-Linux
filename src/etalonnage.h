//---------------------------------------------------------
//NOM : etalonnage.h

//UTILITE : La classe Etalonnage permet de définir les consignes et de vérifier la stailité
//PROJET : Projet de fin de bts iris Examesure

//Date : 2012
//AUTEUR : LARDIES Ludovic
//-------------------------------------------------------
#ifndef ETALONNAGE_H
#define ETALONNAGE_H

#include <iostream>
using namespace std;
#include "mainwindow.h"
#include <vector>
#include "four.h"
#include <QtGui>
#include <QSemaphore>
#include <fstream>
#include <sstream>
#include <string>

class Etalonnage : public QThread
{
    Q_OBJECT
private :
    float tempMini;
    float tempMax;
    float intervalle;
    vector<float>tabTemp;
    vector<float>tabTempRecup;
    Four *fr;
    Sonde *sdRef;
    Sonde *sdInt;
signals:
    virtual void emSigCons(QString);

public :
    Etalonnage();

    bool testStabilite(vector<float>);

    float get_tempMini();
    void set_tempMini(float);

    void  run();

    float get_tempMax();
    void set_tempMax(float);

    float get_intervalle();
    void set_intervalle(float);

    vector<float> get_tabTemp();
    void set_tabTemp(vector<float>);

    void remplir_tabTemp();

};



#endif // ETALONNAGE_H