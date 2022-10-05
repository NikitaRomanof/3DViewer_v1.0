#define GL_SILENCE_DEPRECATION
#include <glu.h>
#include "widget.h"
using namespace std;
MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent) {
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}

MyWidget::~MyWidget()
{
    cleanMemArraiPoint();
 }

void MyWidget::slotTimerAlarm() {
  if (timerGif > 0) {
    recGif(gifSaveFileName);
    --timerGif;
  } else {
    timer->stop();
    timerGif = 0;
  }
}

void MyWidget::initLight() {
  GLfloat light_ambient[] = {0, 0, 0, 0.0};
  GLfloat light_diffuse[] = {0.0, 0.0, 0.0, 0.0};
  GLfloat light_position[] = {0.0, 0.0, 0.0, 0.0};
  /* устанавливаем параметры источника света */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  /* включаем освещение и источник света */
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);
}

void MyWidget::initializeGL() {
  glClearDepth(1.0);  // Разрешить очистку буфера глубины
  glEnable(GL_DEPTH_TEST);  // Разрешить тест глубины
  initLight();              // включаем свет
}

void MyWidget::resizeGL(int nWidth, int nHeight) {
  glViewport(0, 0, nWidth, nHeight);
}

void MyWidget::paintGL()  // рисование
{
  if (countLoadArray == 1) {
    if (flagArray == 0) {
      draw(pointСoordinates);
    } else if (flagArray > 0) {
      draw(array2);
    }
  }
  chengeProjection(projection);
  // инициализация матрицы вида модели
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // сброс матрицы вида модели
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // очистка экрана и буфера глубины
  glTranslatef(0, 0, -2.5);
  glCallList(num);  // выводит заранее загруженную модель
}

void MyWidget::loadArrayPoint() {
  if (countLoadArray == 0) {
    QByteArray bu = fileObjName.toLocal8Bit();
    char *fileName = bu.data();
    int error = getStringsQantity(fileName, &n, &w);
    if (error == 0) {
      int m = 3;
      pointСoordinates = new float *[n];
      for (int i = 0; i < n; i++) {
        pointСoordinates[i] = new float[m];
      }
      readFile(fileName, pointСoordinates, n, w);
      countLoadArray = 1;  // индикатор того что массив координат загружен
      array2 = new float *[n];
      for (int i = 0; i < n; i++) {
        array2[i] = new float[3];
      }
    }
  }
}

void MyWidget::cleanMemArraiPoint() {
  if (countLoadArray == 1) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 3; j++) {
        pointСoordinates[i][j] = 0.0;
      }
    }
    for (int i = 0; i < n; i++) {
      delete[] pointСoordinates[i];
    }
    delete[] pointСoordinates;
    for (int i = 0; i < n; i++) {
      delete[] array2[i];
    }
    delete[] array2;
    array2 = NULL;
    n = 0;
    w = 0;
    countLoadArray = 0;
    flagArray = 0;
    pointСoordinates = NULL;
    num = 0;
  }
}

void MyWidget::rotate(int rotateX, int cordinate) {
  if (countLoadArray == 1) {
    flagArray = 1;
    turnObject(pointСoordinates, n, rotateX, cordinate, array2);
    update();
  }
}

void MyWidget::move(int move, int cordinate) {
  if (countLoadArray == 1) {
    flagArray = 2;
    moveObject(pointСoordinates, n, move, cordinate, array2);
    update();
  }
}

void MyWidget::scale(float scale) {
  if (countLoadArray == 1) {
    flagArray = 3;
    scaleObject(pointСoordinates, n, scale, array2);
    update();
  }
}

int MyWidget::getCountLoadArray() { return countLoadArray; }

void MyWidget::setFlagArray() { flagArray = 0; }

void MyWidget::chengePoligonType(QString type) {
  flagArray = 0;
  if (QString::compare(type, "LINES", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0001;
  } else if (QString::compare(type, "LOOPLINE", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0002;
  } else if (QString::compare(type, "STRIPLINE", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0003;
  } else if (QString::compare(type, "TRIANGLES", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0004;
  } else if (QString::compare(type, "TRIANGLSTRIP", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0005;
  } else if (QString::compare(type, "FANTRIANGLE", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0006;
  } else if (QString::compare(type, "QUADS", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0007;
  } else if (QString::compare(type, "QUADSTRIP", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0008;
  } else if (QString::compare(type, "POLYGON", Qt::CaseInsensitive) == 0) {
    poligonType = 0x0009;
  }
  update();
}

void MyWidget::overwritePointCoord() {
  for (int i = 0; i < n; i++) {
    pointСoordinates[i][0] = array2[i][0];
    pointСoordinates[i][1] = array2[i][1];
    pointСoordinates[i][2] = array2[i][2];
  }
}

void MyWidget::setProjection(QString type) { projection = type; }

int MyWidget::getN() { return n; }

int MyWidget::getW() { return w; }

void MyWidget::recGif(QString pathGif) {
  gif.setDefaultDelay(10);
  QImage screen = grabFramebuffer();
  gif.addFrame(screen);
  if (timerGif == 1 && pathGif.endsWith(".gif")) {
    bool ok = gif.save(pathGif);
    if (ok) {
      statusString = "File .gif saved";

    } else {
      statusString = "Error saving file .gif";
    }
    emit signal(statusString);
  } else if (!pathGif.endsWith(".gif")) {
    statusString = "Incorrect file name, none .gif";
    emit signal(statusString);
  }
}

void MyWidget::timerStart() {
  timer->start(100);
  timerGif = 50;
  statusString = "File .gif save timer started";
}

void MyWidget::setgifSaveFileName(QString fileName) {
  gifSaveFileName = fileName;
}

QString MyWidget::getStatusString() { return statusString; }

void MyWidget::setStatusString(QString str) { statusString = str; }

void MyWidget::chengeProjection(QString type) {
  if (QString::compare(type, "Central", Qt::CaseInsensitive) == 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // сброс матрицы проекции
    gluPerspective(100, qreal(640) / qreal(480), 0.1, 100.0);
  } else if (QString::compare(type, "Parallel", Qt::CaseInsensitive) == 0) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 10, -6, 5, -100, 100);
  }
}

void MyWidget::draw(float **array) {
  loadSetting(&countStart);
  glClearColor(r, g, b, 0);
  num = glGenLists(1);
  glNewList(num, GL_COMPILE);
  glLineWidth(lineWidth);
  setLineDash(lineDash);
  glBegin(poligonType);
  glColor3f(rl, gl, bl);
  for (int i = 0; i < n; i++) {
    glVertex3f(array[i][0], array[i][1], array[i][2]);
  }
  glEnd();
  if (pointOn == 1) {
    chengePointShape(pointShape);
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    glColor3f(rp, gp, bp);
    for (int i = 0; i < n; i++) {
      glVertex3f(array[i][0], array[i][1], array[i][2]);
    }
    glEnd();
  }
  glEndList();
}

void MyWidget::chengeColorBack(QString backColor) {
  if (QString::compare(backColor, "Red", Qt::CaseInsensitive) == 0) {
    r = 1;
    g = 0;
    b = 0;
  } else if (QString::compare(backColor, "Green", Qt::CaseInsensitive) == 0) {
    r = 0;
    g = 1;
    b = 0;
  } else if (QString::compare(backColor, "Blue", Qt::CaseInsensitive) == 0) {
    r = 0;
    g = 0;
    b = 1;
  } else if (QString::compare(backColor, "Yellow", Qt::CaseInsensitive) == 0) {
    r = 1;
    g = 1;
    b = 0;
  } else if (QString::compare(backColor, "Turquoise", Qt::CaseInsensitive) ==
             0) {
    r = 0;
    g = 1;
    b = 1;
  } else if (QString::compare(backColor, "Purple", Qt::CaseInsensitive) == 0) {
    r = 1;
    g = 0;
    b = 1;
  } else if (QString::compare(backColor, "White", Qt::CaseInsensitive) == 0) {
    r = 1;
    g = 1;
    b = 1;
  } else if (QString::compare(backColor, "Black", Qt::CaseInsensitive) == 0) {
    r = 0;
    g = 0;
    b = 0;
  }
  update();
}

void MyWidget::chengeColor(QString color) {
  if (QString::compare(color, "Red", Qt::CaseInsensitive) == 0) {
    rl = 1.0f;
    gl = 0.0f;
    bl = 0.0f;
  } else if (QString::compare(color, "Green", Qt::CaseInsensitive) == 0) {
    rl = 0.0f;
    gl = 1.0f;
    bl = 0.0f;
  } else if (QString::compare(color, "Blue", Qt::CaseInsensitive) == 0) {
    rl = 0.0f;
    gl = 0.0f;
    bl = 1.0f;
  } else if (QString::compare(color, "Yellow", Qt::CaseInsensitive) == 0) {
    rl = 1.0f;
    gl = 1.0f;
    bl = 0.0f;
  } else if (QString::compare(color, "Turquoise", Qt::CaseInsensitive) == 0) {
    rl = 0.0f;
    gl = 1.0f;
    bl = 1.0f;
  } else if (QString::compare(color, "Purple", Qt::CaseInsensitive) == 0) {
    rl = 1.0f;
    gl = 0.0f;
    bl = 1.0f;
  } else if (QString::compare(color, "White", Qt::CaseInsensitive) == 0) {
    rl = 1.0f;
    gl = 1.0f;
    bl = 1.0f;
  } else if (QString::compare(color, "Black", Qt::CaseInsensitive) == 0) {
    rl = 0.0f;
    gl = 0.0f;
    bl = 0.0f;
  }
  update();
}

void MyWidget::chengeColorPonts(QString color) {
  if (QString::compare(color, "Red", Qt::CaseInsensitive) == 0) {
    rp = 1.0f;
    gp = 0.0f;
    bp = 0.0f;
  } else if (QString::compare(color, "Green", Qt::CaseInsensitive) == 0) {
    rp = 0.0f;
    gp = 1.0f;
    bp = 0.0f;
  } else if (QString::compare(color, "Blue", Qt::CaseInsensitive) == 0) {
    rp = 0.0f;
    gp = 0.0f;
    bp = 1.0f;
  } else if (QString::compare(color, "Yellow", Qt::CaseInsensitive) == 0) {
    rp = 1.0f;
    gp = 1.0f;
    bp = 0.0f;
  } else if (QString::compare(color, "Turquoise", Qt::CaseInsensitive) == 0) {
    rp = 0.0f;
    gp = 1.0f;
    bp = 1.0f;
  } else if (QString::compare(color, "Purple", Qt::CaseInsensitive) == 0) {
    rp = 1.0f;
    gp = 0.0f;
    bp = 1.0f;
  } else if (QString::compare(color, "White", Qt::CaseInsensitive) == 0) {
    rp = 1.0f;
    gp = 1.0f;
    bp = 1.0f;
  } else if (QString::compare(color, "Black", Qt::CaseInsensitive) == 0) {
    rp = 0.0f;
    gp = 0.0f;
    bp = 0.0f;
  }
  update();
}

void MyWidget::chengeLineWidth(float width) {
  lineWidth = 0;
  lineWidth = width;
  update();
}

void MyWidget::chengePointSize(float size) {
  if (size == 0.0) {
    pointOn = 0;
  } else {
    pointOn = 1;
    pointSize = size;
  }
  update();
}

void MyWidget::chengePointShape(QString shape) {
  if (QString::compare(shape, "circle", Qt::CaseInsensitive) == 0) {
    glDisable(GL_POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);
  } else if (QString::compare(shape, "square", Qt::CaseInsensitive) == 0) {
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POINT_SIZE);
  }
}

void MyWidget::setPointShape(QString shape) {
  pointShape = shape;
  update();
}

void MyWidget::setLineDash(int dash) {
  if (dash == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x3333);
  } else if (dash == 2) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xFFF8);
  } else if (dash == 3) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x3F3F);
  } else if (dash == 4) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x8FF1);
  } else if (dash == 0) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyWidget::chengeLineDash(int dash) {
  lineDash = dash;
  update();
}

void MyWidget::loadSetting(int *countStart) {
  if (*countStart == 0) {
    int count = 0;
    QString path = QCoreApplication::applicationDirPath();
    openFilePath = path + "/default_setting.txt";
    QFile file(openFilePath);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream in(&file);
      while (!in.atEnd()) {
        QString line = in.readLine();
        if (count == 0) {
          chengeColor(line);
        } else if (count == 1) {
          chengeColorPonts(line);
        } else if (count == 2) {
          chengeColorBack(line);
        } else if (count == 3) {
          QByteArray bu = line.toLocal8Bit();
          char *buf = bu.data();
          sscanf(buf, "%f", &lineWidth);
        } else if (count == 4) {
          QByteArray bu = line.toLocal8Bit();
          char *buf = bu.data();
          sscanf(buf, "%d", &lineDash);
        } else if (count == 5) {
          QByteArray bu = line.toLocal8Bit();
          char *buf = bu.data();
          sscanf(buf, "%f", &pointSize);
        } else if (count == 6) {
          setPointShape(line);
        } else if (count == 7) {
          setProjection(line);
        }
        count++;
      }
      file.close();
    }
    *countStart = 1;  // индикатор того что данный настроикй применятся  один
                      // раз при загрузке
  }
}

void MyWidget::setFileObjName(QString name) { fileObjName = name; }

QString MyWidget::getApplicationFolderMacOS() {
  QString relativePath;
  QDir directory;
  relativePath = QDir::currentPath();
  directory.setPath(relativePath);
//  directory.cdUp();
//  directory.cdUp();
//  directory.cdUp();
  relativePath = directory.path();
  qDebug() << relativePath;
  return relativePath;
}
