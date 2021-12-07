#include "Cabecera.hpp"


int main(int argc, char *argv[]){
    Cuadro cuadroV =Cuadro("frame.jpg","corto.mp4","/dev/video0");
    string background=cuadroV.getFondo();
    Mat fondo=cuadroV.visualizarFondo(background);
    namedWindow("F", WINDOW_AUTOSIZE);
    setMouseCallback("F",cuadroV.eventoRaton,&cuadroV);
    imshow("F",fondo);
    waitKey(0);
    destroyAllWindows();
    cuadroV.dividirPuntos();
    vector<Point> im1= cuadroV.getPuntos1();
    Mat mask=cuadroV.crearMascara(im1,fondo);
    //namedWindow("M", WINDOW_AUTOSIZE);
    //imshow("M",mask);
    mask=cuadroV.operadorNegacion(mask);
    Mat resultado=cuadroV.operadorAND(fondo,mask);
    //namedWindow("R", WINDOW_AUTOSIZE);
    //imshow("R",resultado);
    //waitKey(0);
    cuadroV.capturar(fondo,resultado);


}