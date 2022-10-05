
#include "proto1.h"
#include "ui_proto1.h"


proto1::proto1(QWidget *parent) : QDialog(parent), ui(new Ui::proto1) {
  ui->setupUi(this);
  connect(ui->myOpenGL, &MyWidget::signal, this, &proto1::functionSlot);
  setUpSettings();
}

proto1::~proto1() { delete ui; }
void proto1::closeEvent(QCloseEvent *event)
{
    ui->myOpenGL->~MyWidget();
    event->accept();
}

void proto1::functionSlot(QString a) { ui->labelStstusProg->setText(a); }

void proto1::on_scaleSlider_valueChanged(int value) {
  ui->scaleSpinBox->setValue(value);
  float z = 1.0;
  if (value == 0.0) {
    z = 1.0;
  } else if (value < 0) {
    z = 1 - (float)value / -10.0f;
  } else
    z = 1 + ((float)value / 10);
  ui->myOpenGL->scale(z);
}

void proto1::on_xRotationSlider_valueChanged(int value) {
  ui->xRotationSpinBox->setValue(value);
  ui->myOpenGL->rotate(value, 1);
}

void proto1::on_yRotationSlider_valueChanged(int value) {
  ui->yRotationSpinBox->setValue(value);
  ui->myOpenGL->rotate(value, 2);
}

void proto1::on_zRotationSlider_valueChanged(int value) {
  ui->zRotationSpinBox->setValue(value);
  ui->myOpenGL->rotate(value, 3);
}

void proto1::on_distanceXSlider_valueChanged(int value) {
  ui->distanceXSpinBox->setValue(value);
  ui->myOpenGL->move(value, 1);
}

void proto1::on_openFileButton_clicked() {
  int load = ui->myOpenGL->getCountLoadArray();
  if (load == 1) {
    ui->myOpenGL->cleanMemArraiPoint();
    ui->lineEditPath->setText("");
    ui->openFileNameLabel->setText("");
    ui->myOpenGL->setFileObjName("");
    ui->labelPointsCount->setText("0");
    ui->labelEdgesCount->setText("0");
    ui->myOpenGL->update();
  }
  QFileDialog *openfileDialog = new QFileDialog();
  openfileDialog->setDirectory(getApplicationFolderMacOS());
  QString filepath = openfileDialog->getOpenFileName();
  if (filepath.endsWith(".obj", Qt::CaseInsensitive)) {
      ui->lineEditPath->setText(filepath);
      ui->openFileNameLabel->setText(filepath.mid(filepath.lastIndexOf("/") + 1));
      ui->myOpenGL->setFileObjName(filepath);
      ui->myOpenGL->loadArrayPoint();
      ui->myOpenGL->update();
      ui->labelPointsCount->setText(QString::number(ui->myOpenGL->getN()));
      ui->labelEdgesCount->setText(QString::number(ui->myOpenGL->getN() / ui->myOpenGL->getW()));
      ui->labelStstusProg->setText("New filе .obj uploaded");
  } else {
      ui->labelStstusProg->setText("Incorrect filе name, none .obj");
  }

  openfileDialog->close();
}

void proto1::on_xRotationSpinBox_valueChanged(double arg1) {
  ui->xRotationSlider->setValue(arg1);
}

void proto1::on_yRotationSpinBox_valueChanged(double arg1) {
  ui->yRotationSlider->setValue(arg1);
}

void proto1::on_zRotationSpinBox_valueChanged(double arg1) {
  ui->zRotationSlider->setValue(arg1);
}

void proto1::on_scaleSpinBox_valueChanged(double arg1) {
  ui->scaleSlider->setValue(arg1);
}

void proto1::on_distanceXSpinBox_valueChanged(double arg1) {
  ui->distanceXSlider->setValue(arg1);
}

void proto1::on_distanceYSpinBox_valueChanged(double arg1) {
  ui->distanceYSlider->setValue(arg1);
}

void proto1::on_distanceZSpinBox_valueChanged(double arg1) {
  ui->distanceZSlider->setValue(arg1);
}

void proto1::on_distanceYSlider_valueChanged(int value) {
  ui->distanceYSpinBox->setValue(value);
  ui->myOpenGL->move(value, 2);
}

void proto1::on_distanceZSlider_valueChanged(int value) {
  ui->distanceZSpinBox->setValue(value);
  ui->myOpenGL->move(value, 3);
}

void proto1::on_shotButton_clicked() {
  QImage pixmap = this->ui->myOpenGL->grabFramebuffer();
  QFileDialog *filesavedialog = new QFileDialog();
  filesavedialog->show();
  QString savepath = filesavedialog->getSaveFileName();
  if (savepath.endsWith(".bmp")) {
    pixmap.save(savepath, "bmp");
    ui->labelStstusProg->setText("New filе .bmp saved");
  } else if (savepath.endsWith(".jpg")) {
    pixmap.save(savepath, "jpg");
    ui->labelStstusProg->setText("New filе .jpg saved");
  } else {
    ui->labelStstusProg->setText("Screenshot file saved error");
  }
  filesavedialog->close();
}

void proto1::on_gifButton_clicked() {
  QFileDialog *filesavedialog = new QFileDialog();
  filesavedialog->show();
  QString savepath = filesavedialog->getSaveFileName();
  ui->labelGifName->setText(savepath);
  ui->myOpenGL->setgifSaveFileName(savepath);
  filesavedialog->close();
  ui->myOpenGL->timerStart();
  ui->labelStstusProg->setText(ui->myOpenGL->getStatusString());
}

void proto1::on_clearButton_clicked() {
  int load = ui->myOpenGL->getCountLoadArray();
  if (load == 1) {
    ui->myOpenGL->cleanMemArraiPoint();
    ui->lineEditPath->setText("");
    ui->openFileNameLabel->setText("");
    ui->myOpenGL->setFileObjName("");
    ui->myOpenGL->update();
    ui->labelStstusProg->setText("Model deleted");
  }
  setAllSlidersToDeafult();
}

void proto1::on_comboBoxBackColor_textActivated(const QString &arg1) {
  ui->myOpenGL->chengeColorBack(arg1);
}

void proto1::on_comboBoxLineColor_textActivated(const QString &arg1) {
  ui->myOpenGL->chengeColor(arg1);
}

void proto1::on_comboBoxLineThick_textActivated(const QString &arg1) {
  float index = arg1.toFloat();
  ui->myOpenGL->chengeLineWidth(index);
}

void proto1::on_comboBoxLineShape_textActivated(const QString &arg1) {
  int index = arg1.toInt();
  ui->myOpenGL->chengeLineDash(index);
}

void proto1::on_comboBoxPointColor_textActivated(const QString &arg1) {
  ui->myOpenGL->chengeColorPonts(arg1);
}

void proto1::on_comboBoxpointShape_textActivated(const QString &arg1) {
  ui->myOpenGL->setPointShape(arg1);
}

void proto1::on_comboBoxPointThick_textActivated(const QString &arg1) {
  float index = arg1.toFloat();
  ui->myOpenGL->chengePointSize(index);
}

void proto1::on_comboBox_textActivated(const QString &arg1) {
  ui->myOpenGL->setProjection(arg1);
  ui->myOpenGL->update();
}

void proto1::on_xRotationSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_yRotationSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_zRotationSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_distanceXSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_distanceYSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_distanceZSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_scaleSlider_sliderReleased() {
  ui->myOpenGL->overwritePointCoord();
  ui->myOpenGL->setFlagArray();
}

void proto1::on_comboBox_2_textActivated(const QString &arg1) {
  ui->myOpenGL->chengePoligonType(arg1);
}

void proto1::on_pushButton_clicked() {
  int load = ui->myOpenGL->getCountLoadArray();
  if (load == 1) {
    ui->myOpenGL->cleanMemArraiPoint();
    ui->myOpenGL->loadArrayPoint();
    ui->myOpenGL->update();
    setAllSlidersToDeafult();
    ui->labelStstusProg->setText("Reverting a model to its original state");
  }
}

void proto1::on_saveButton_clicked() {
  QString path = getApplicationFolderMacOS();
  QString configPath = path + "/default_setting.txt";
  QFile file(configPath);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream stream(&file);
    stream << ui->comboBoxLineColor->currentText() << "\n";  // цвет линий
    stream << ui->comboBoxPointColor->currentText() << "\n";  // цвет вершин
    stream << ui->comboBoxBackColor->currentText() << "\n";  // цвет фона
    stream << ui->comboBoxLineThick->currentText() << "\n";  // тощина линий
    stream << ui->comboBoxLineShape->currentText() << "\n";  // тип штриховки линий
    stream << ui->comboBoxPointThick->currentText() << "\n";  // размер вершин
    stream << ui->comboBoxpointShape->currentText() << "\n";  // форма точек
    stream << ui->comboBox->currentText() << "\n";  // тип проекци
  }
  file.close();
}

void proto1::setAllSlidersToDeafult() {
  ui->xRotationSlider->setValue(0);
  ui->yRotationSlider->setValue(0);
  ui->zRotationSlider->setValue(0);
  ui->distanceXSlider->setValue(0);
  ui->distanceYSlider->setValue(0);
  ui->distanceZSlider->setValue(0);
  ui->scaleSlider->setValue(0);
}

QString proto1::getApplicationFolderMacOS() {
  QString relativePath = QCoreApplication::applicationDirPath();
  return relativePath;
}

void proto1::setUpSettings() {
  QString path = getApplicationFolderMacOS();
  QString configPath = path + "/default_setting.txt";

  QFile file(configPath);
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream stream(&file);
    int count = 0;
    while (!stream.atEnd()) {
      QString line = stream.readLine();
      if (count == 0) {
        ui->comboBoxLineColor->setCurrentText(line);  // цвет линий
      } else if (count == 1) {
        ui->comboBoxPointColor->setCurrentText(line);  // цвет вершин
      } else if (count == 2) {
        ui->comboBoxBackColor->setCurrentText(line);
      } else if (count == 3) {
        ui->comboBoxLineThick->setCurrentText(line);
      } else if (count == 4) {
        ui->comboBoxLineShape->setCurrentText(line);
      } else if (count == 5) {
        ui->comboBoxPointThick->setCurrentText(line);
      } else if (count == 6) {
        ui->comboBoxpointShape->setCurrentText(line);
      } else if (count == 7) {
        ui->comboBox->setCurrentText(line);
      }

      count++;
    }
    file.close();
  }
}
