#ifndef PROTO1_H
#define PROTO1_H
#define Q_WARNING
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QCloseEvent>
#include "widget.h"

namespace Ui {
class proto1;
}

class proto1 : public QDialog {
  Q_OBJECT

 public:
  explicit proto1(QWidget *parent = nullptr);
  ~proto1();

 public slots:
  void functionSlot(QString a);

 private slots:
  void on_scaleSlider_valueChanged(int value);
  void on_xRotationSlider_valueChanged(int value);
  void on_yRotationSlider_valueChanged(int value);
  void on_zRotationSlider_valueChanged(int value);
  void on_distanceXSlider_valueChanged(int value);
  void on_openFileButton_clicked();
  void on_xRotationSpinBox_valueChanged(double arg1);
  void on_yRotationSpinBox_valueChanged(double arg1);
  void on_zRotationSpinBox_valueChanged(double arg1);
  void on_scaleSpinBox_valueChanged(double arg1);
  void on_distanceXSpinBox_valueChanged(double arg1);
  void on_distanceYSpinBox_valueChanged(double arg1);
  void on_distanceZSpinBox_valueChanged(double arg1);
  void on_distanceYSlider_valueChanged(int value);
  void on_distanceZSlider_valueChanged(int value);
  void on_shotButton_clicked();
  void on_gifButton_clicked();
  void on_clearButton_clicked();
  void on_comboBoxBackColor_textActivated(const QString &arg1);
  void on_comboBoxLineColor_textActivated(const QString &arg1);
  void on_comboBoxLineThick_textActivated(const QString &arg1);
  void on_comboBoxLineShape_textActivated(const QString &arg1);
  void on_comboBoxPointColor_textActivated(const QString &arg1);
  void on_comboBoxpointShape_textActivated(const QString &arg1);
  void on_comboBoxPointThick_textActivated(const QString &arg1);
  void on_comboBox_textActivated(const QString &arg1);
  void on_xRotationSlider_sliderReleased();
  void on_yRotationSlider_sliderReleased();
  void on_zRotationSlider_sliderReleased();
  void on_distanceXSlider_sliderReleased();
  void on_distanceYSlider_sliderReleased();
  void on_distanceZSlider_sliderReleased();
  void on_scaleSlider_sliderReleased();
  void on_comboBox_2_textActivated(const QString &arg1);
  void on_pushButton_clicked();
  void on_saveButton_clicked();
  void setAllSlidersToDeafult();
  QString getApplicationFolderMacOS();
  void setUpSettings();

 private:
  Ui::proto1 *ui;
  void closeEvent(QCloseEvent *event);
};

#endif  // PROTO1_H
