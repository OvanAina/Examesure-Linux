//--------------------------------------------------------
//NOM : rs232.cpp

//UTILITE : la classe Rs232 permet de gérer la liaison série rs232
//PROJET : Projet de fin de bts iris Examesure

//Date : 2012
//AUTEUR : LARDIES Ludovic
//-------------------------------------------------------
#include "rs232.h"


Rs232* Rs232::rs232 = NULL;
string Rs232::vitesseFour="0";
QString Rs232::idFour="0";

Rs232* Rs232::getInstance ()
{
    if (Rs232::rs232 == NULL)
    {
        Rs232::rs232 = new Rs232;
    }
    return Rs232::rs232;
}

Rs232* Rs232::getInstance (QString id, string baud)
{
    Rs232::vitesseFour=baud;
    Rs232::idFour=id;

    if (Rs232::rs232 == NULL)
    {
        Rs232::rs232 = new Rs232;

    }
    return Rs232::rs232;
}

Rs232::Rs232()
{


    cout<<"Un objet entree"<<endl;

    if (Rs232::vitesseFour=="2400")
    {
        system("stty -F /dev/ttyUSB0 2400");
        system("stty -F /dev/ttyUSB1 2400");
    }

    else if (Rs232::vitesseFour=="4800")
    {
        system("stty -F /dev/ttyUSB0 4800");
        system("stty -F /dev/ttyUSB1 4800");
    }

    else if (Rs232::vitesseFour=="9600")
    {
        system("stty -F /dev/ttyUSB0 9600");
        system("stty -F /dev/ttyUSB1 9600");
    }
    else if (Rs232::vitesseFour=="19200")
    {
        system("stty -F /dev/ttyUSB0 19200");
        system("stty -F /dev/ttyUSB1 19200");
    }



    id_tty=open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NONBLOCK); //
    if (id_tty < 0 )
    {
        perror("open");
        cout<<"On est pas co "<<endl;
    }
    else
    {
        cout<<"On est co "<<endl;
    }

    QString data = "$"+idFour+"WVAR8 3 \r";


    const char* buffer= data.toStdString().c_str();

    mutex.lock();// bloque la liaison RS232
    usleep(50);
    write(id_tty, buffer ,data.size()); //ecrire sur la liaison
    mutex.unlock(); // debloque la liaison RS232

}

void Rs232::ecrire(QString para, int id_tty)
{
    QString data = "$"+Rs232::idFour+"WVAR0 "+para+"\r";
    const char* buffer= data.toStdString().c_str();

    mutex.lock();
    write(id_tty, buffer ,data.size()); //envoi au port serie
    mutex.unlock(); // debloque la liaison RS232

    usleep(50);

}

QString Rs232::recevoir(QString para, int id_tty) // recuperer la temperature externe
{

    mutex.lock();

    QString data = "$"+Rs232::idFour+"RVAR"+para+" \r";
    cout<<data.toStdString()<<endl;
    taille = data.size()+1; // recupere la taille de la donnée

    char * buffer = new char[ taille ]; // pour convertir le string en char*

    strcpy(buffer, data.toStdString().c_str() ); // convertie le string en char*
    write(id_tty, buffer ,data.size()); //envoi au port serie

    delete buffer;

    usleep(50);
    for(int nb=0;nb<15;nb++)
    {
        read(id_tty,buff+nb, 1);//lire sur la liaison caractère par caractère
        if(buff[nb]=='\r')//lire jusqu'au caractère \r
        {
            buff[nb]==0;
            break;//sortir de la boucle
        }
    }

    buffRead= buff;//convertie buff(char*) en QString

    found = buffRead.lastIndexOf(" "); //trouve ou est le caractere  espace
    found2 = buffRead.indexOf(" ");
    trameFormate=buffRead.mid(found2,found);

    cout<<trameFormate.toStdString()<<endl;
    mutex.unlock();// libérer le mutex

    if ((trameFormate.toFloat()>0) && (trameFormate.toFloat()<1000))
    {
        return trameFormate;

    }
    else
    {
        return 0;
    }

}

int  Rs232::get_id_tty()
{
    return id_tty;
}
