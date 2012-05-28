//---------------------------------------------------------
//NOM : config.h

//UTILITE : Fichier de l'ui de la configuration généré par QT Creator
//PROJET : Projet de fin de bts iris Examesure

//Date : 2012
//AUTEUR : LARDIES Ludovic
//-------------------------------------------------------
#ifndef CONFIG_H
#define CONFIG_H
#include <QFileDialog>

#include <QWidget>

namespace Ui {
class Config;
}

class Config : public QWidget
{
    Q_OBJECT
    
public:
    explicit Config(QWidget *parent = 0);
    ~Config();
    
private slots:
    void on_toolButton_clicked();

private:
    Ui::Config *ui;
};

#endif // CONFIG_H