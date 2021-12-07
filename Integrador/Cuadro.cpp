#include "Cabecera.hpp"

Cuadro::Cuadro(string fondo,string video, string camaraweb){
    vector<Point> p1;
    vector<Point> p2;
    vector<Point2f> fp1;
    vector<Point2f> fp2;
    this->fondo=fondo;
    this->video=video;
    this->camaraweb=camaraweb;
    this ->puntos1=p1;
    this -> puntos2=p2;
    this ->fPuntos1=fp1;
    this-> fPuntos2=fp2;
}

Mat Cuadro::visualizarFondo(string background){
    Mat f=imread(background);
    return f;

}

void Cuadro::agregarVectorPuntos(int x, int y){
    this ->puntos1.push_back(Point(x,y));
 
}

void Cuadro::eventoRaton(int evento, int x, int y, int flags, void *data){
    //this ->
    //string *p
    if(evento == EVENT_RBUTTONDOWN){
        cout << "Click Izquierdo x= " << x << " y= " << y << endl;
        Cuadro *p = (Cuadro*)data;
        p->agregarVectorPuntos(x,y);
    }

}

void Cuadro::setFondo(string fondo){
     this ->fondo=fondo;
 }

string Cuadro::getFondo(){
     return this->fondo;
 }

  void Cuadro::setVideo(string video){
     this ->video=video;
 }

 string Cuadro::getVideo(){
     return this->video;
 }

void Cuadro::setCamara(string camara){
     this ->camaraweb=camara;
 }

 string Cuadro::getCamara(){
     return this->camaraweb;
 }

 vector<Point> Cuadro::getPuntos1(){
     return this->puntos1;
 }

 vector<Point> Cuadro::getPuntos2(){
     return this->puntos2;
 }

void Cuadro::dividirPuntos(){
    vector<Point> puntos= this->getPuntos1();
    cout << "Dividir:" << puntos.size() << endl;
    vector<Point> p1;
    vector<Point> p2;
    if(puntos.size()>4){
        for(int i=0;i<puntos.size()/2;i++){
            //cout << puntos[i] << endl;
            //cout << puntos[i].x << endl;
            int x=(int) puntos[i].x;
            int y=(int) puntos[i].y;
            p1.push_back(Point(x,y));
            fPuntos1.push_back(Point2f(x, y));
            //cout << "Metodo:"<< puntos2.size() << endl;
        }
        
        for(int i=4;i<puntos.size();i++){
            //cout << puntos[i] << endl;
            //cout << puntos[i].x << endl;
            int x=(int) puntos[i].x;
            int y=(int) puntos[i].y;
            p2.push_back(Point(x,y));
            fPuntos2.push_back(Point2f(x,y));
            //cout << "Metodo:"<< puntos2.size() << endl;
        }
    }
    this ->puntos1=p1;
    this ->puntos2=p2;

}

Mat Cuadro::crearMascara(vector<Point> puntos, Mat fondo){
    Mat mask = Mat(Size(fondo.cols, fondo.rows), CV_8UC1, Scalar(0));
    fillPoly(mask, this->getPuntos1(), Scalar(255, 255, 255));
    fillPoly(mask, this->getPuntos2(), Scalar(255, 255, 255));
    return mask;

}

Mat Cuadro::operadorNegacion(Mat mask){
    bitwise_not(mask,mask);
    return mask;
}

Mat Cuadro::operadorAND(Mat fondo, Mat mask){
    Mat resultado;
    bitwise_and(fondo, fondo, resultado, mask);
    return resultado;
}

vector<Point2f> Cuadro::puntosImagen(Mat imagen)
{
    vector<Point2f> puntos;
    Point2f p1(0, 0);
    Point2f p2(imagen.cols - 1, 0);
    Point2f p3(imagen.cols - 1, imagen.rows - 1);
    Point2f p4(0, imagen.rows - 1);
    puntos.push_back(Point2f(p1));
    puntos.push_back(Point2f(p2));
    puntos.push_back(Point2f(p3));
    puntos.push_back(Point2f(p4));
    return puntos;
}

void Cuadro::capturar(Mat fondo, Mat resultado){
    Mat copia=fondo.clone();

    VideoCapture video(this->getCamara());
    VideoCapture video1(this->getVideo());
    //codigo=VideoWriter_fourcc();
    
    //int numero = CAP_PROP_FOURCC(4);
    int fourcc=VideoWriter::fourcc('M','J','P','G');
    VideoWriter salida("presentacion.avi",fourcc,20,Size(fondo.cols,fondo.rows));
    Mat frame;
    Mat corto;
    Mat r;
    Mat finally;
     if(video.isOpened()){
        namedWindow("Video1", WINDOW_AUTOSIZE);
        while(3==3){
            video >> frame;
            video1 >> corto;

            if(frame.empty()){
                cout << "Video Finalizado" << endl;
                break;
            }

            vector<Point2f> puntos = puntosImagen(frame);
            vector<Point2f> puntos2 = puntosImagen(corto);
            Mat h1 = getPerspectiveTransform(puntos, fPuntos1);
            Mat h2 = getPerspectiveTransform(puntos2, fPuntos2);

            warpPerspective(frame, fondo, h1, fondo.size());
            warpPerspective(corto, copia, h2, copia.size());
            add(fondo,copia,r);
            add(resultado, r, finally);
            imshow("Video1", finally);
            salida.write(finally);

            if(waitKey(23)==27){
                break;
            }
        }
        video.release();
        salida.release();
    }
}