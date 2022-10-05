#ifndef WIDGET_H
#define WIDGET_H
#include <QDir>
#include <QCoreApplication>
#include <QFile>
#include <QKeyEvent>  // для перехвата нажатий клавиш
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>


#include "giflib/gifimage/qgifimage.h"
extern "C" {
#include "affineTransformations.h"
#include "readObjFile.h"
#include "s21_matrix.h"
}
class MyWidget : public QOpenGLWidget {
  Q_OBJECT
  QTimer *paintTimer;  // таймер
  GLuint model;
  GLfloat angle = 0;  // угол вращения
  void initLight();   // включить свет

 public:
  MyWidget(QWidget *parent = nullptr);
  ~MyWidget();
  void draw(float **array);
  void chengeColorBack(QString backColor);
  void chengeColor(QString color);
  void chengeColorPonts(QString color);
  void chengeLineWidth(float width);
  void chengePointSize(float size);
  void chengePointShape(QString shape);
  void setPointShape(QString shape);
  void setLineDash(int dash);
  void chengeLineDash(int dash);
  void loadSetting(int *countStart);
  void setFileObjName(QString name);
  void loadArrayPoint();
  void cleanMemArraiPoint();
  void rotate(int count, int cordinate);
  void move(int count, int cordinate);
  void scale(float count);
  int getCountLoadArray();
  void setFlagArray();
  void chengePoligonType(QString type);
  void overwritePointCoord();
  void chengeProjection(QString type);
  void setProjection(QString type);
  int getN();
  int getW();
  void recGif(QString pathGif);
  void timerStart();
  void setgifSaveFileName(QString fileName);
  QString getStatusString();
  void setStatusString(QString str);
  QString getApplicationFolderMacOS();

 public slots:
  void slotTimerAlarm();

 signals:
  void signal(QString);

 protected:
  void initializeGL();
  void resizeGL(int nWidth, int nHeight);
  void paintGL();

 private:
  int countStart = 0;  //  переменная отвечающая за загрузку настроек из файла
                       //  при старте. Если 0 то программа толька началась и
                       //  необходимо загрузить настройки из файла.
  int r = 0, g = 0, b = 0;             // цвет заднего фона
  float rl = 1.0, gl = 0.0, bl = 1.0;  // цвет линий
  float rp = 1.0, gp = 0.0, bp = 0.0;  // цвет точек
  float lineWidth = 3.0, pointSize = 10.0;  // толщина линий и точек
  int lineDash = 0;  // если 0 то линии сплошные, если больше нуля то какой-то
                     // из вариантов пунктиров
  QString fileObjName;  // имя obj файла
  GLuint num = 0;  // переменная для загрузки модели из массива точек
  float **pointСoordinates;  // массив точек n x 3
  float **array2;
  int countLoadArray = 0;  // если 0 то память для массива не выделена и данные
                           // не загружены, если 1 то массив точек загружен
  int n = 0;               // колличесто точек в массиве
  int w = 0;  // затычка для бэка, отражает сколько точек в  поверхности
  int flagArray = 0;  // флаг, отражвющий какой из массивов точек нужно
                      // загружать в функцию draw()
  unsigned int poligonType = 0x0001;  //   тип отрисовки модели
  int pointOn = 1;                    // включение точек
  QString pointShape = "square";  // форма точек по умолчанию сфера
  QString projection = "Central";  // тип проекции, по умолчанию центральная
  QTimer *timer;     // объект таймер
  QGifImage gif;     // гифка
  int timerGif = 0;  //  управление таймером и записью гифки, когда > 0
                     //  запускается таймер и каждый тик уменьшаем переменную,
                     //  по таймеру записываем кадры в гифке
  QString gifSaveFileName;  //  имя гиф файла. куда сохраняем
  QString statusString;  // строка состояния в proto1
  QString openFilePath;  // имя файла конфига
};
#endif  // WIDGET_H
