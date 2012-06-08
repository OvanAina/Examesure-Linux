//---------------------------------------------------------
//NOM : camera.cpp

//UTILITE : Gérer la webcam
//PROJET : Projet de fin de bts iris Examesure

//Date : 2012
//AUTEUR : LARDIES Ludovic
//-------------------------------------------------------
#include "camera.h"

static QImage IplImage2QImage(const IplImage *iplImage)//fonction pour convertir IplImage* en QImage
{
    int height = iplImage->height;
    int width = iplImage->width;
    if (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
        const uchar *qImageBuffer =(const uchar*)iplImage->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
        return img.rgbSwapped();
    }else{
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}



bool Camera::connecter(int id)
{

    QMessageBox box;

    camera = cvCaptureFromCAM(id);

    if (!camera) {
        cvReleaseCapture(&camera);
        box.setText("Verifier votre webcam");
        box.exec();
        cout<<"idcam :"<<idcam<<endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

Camera::Camera()
{

}

Camera::~Camera()
{
    cvReleaseCapture(&camera);
}


void Camera::run()
{

    while(true)
    {
        usleep(50);
        image = cvQueryFrame(camera);//récuperer le flux de la webcam
        img=IplImage2QImage(image);//convertir IplImage en QImage
        emit emSig2(img);
    }

}




