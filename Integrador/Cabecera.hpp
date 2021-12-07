#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <filesystem> // Libreria que contiene funciones para la manipulacion de ficheros, carpetas, etc
#include <chrono>     // Tiempo de ejecucion
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <random>
#include <time.h>
// Librerías de OpenCV
#include <opencv2/core/core.hpp>           // Contiene los elementos base de OpenCV (matrices, arreglos, etc.)
#include <opencv2/highgui/highgui.hpp>     // Contiene estructuras para crear la interfaz gráfica
#include <opencv2/imgproc/imgproc.hpp>     // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer determinados formatos de imágenes
#include <opencv2/video/video.hpp>         // Procesamiento y escritura
#include <opencv2/videoio/videoio.hpp>     // de video
#include <opencv2/photo/photo.hpp>

#include <filesystem>
namespace fs = std::filesystem;
using namespace std;
using namespace cv;

class Cuadro{
    private:
        string fondo;
        string video;
        string camaraweb;
        vector<Point> puntos1;
        vector<Point> puntos2;
        vector<Point2f> fPuntos1;
        vector<Point2f> fPuntos2;
    public:
        Cuadro(string ="vacio",string="vacio",string="vacio");
        Mat visualizarFondo(string background);
        void agregarVectorPuntos(int x, int y);
        static void eventoRaton(int evento, int x, int y, int flags, void *data);
        Mat crearMascara(vector<Point> puntos, Mat fondo);
        Mat operadorNegacion(Mat mask);
        Mat operadorAND(Mat fondo, Mat mask);
        void capturar(Mat fondo,Mat resultado);
        void setFondo(string fondo);
        string getFondo();
        void setVideo(string video);
        string getVideo();
        void setCamara(string camara);
        string getCamara();
        vector<Point> getPuntos1();
        vector<Point> getPuntos2();
        vector<Point2f> puntosImagen(Mat imagen);
        void dividirPuntos();

};

