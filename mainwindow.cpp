#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <math.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->W_ss->installEventFilter(this);

}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if(object == ui->W_ss) {
        if(event->type() == QEvent::MouseButtonPress) {
            this->ui->W_ss->setText("");
        }
    }
    return false;
};

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    QDateTime dateTimeOne = ui->dateTimeEdit->dateTime();
    QDateTime dateTimeTwo = ui->dateTimeEdit_2->dateTime();
    qint64 secs = dateTimeOne.secsTo(dateTimeTwo);
    qint64 mins = secs/60;
    secs = secs%60;
    qint64 hours = mins/60;
    mins = mins%60;
    qint64 days = hours/24;
    hours = hours%24;
    ui->secs->setText(QString::number(secs));
    ui->mins->setText(QString::number(mins));
    ui->hours->setText(QString::number(hours));
    ui->days->setText(QString::number(days));

//    QPropertyAnimation *animation = new QPropertyAnimation(ui->pushButton_2, "geometry");
//    animation->setDuration(500);
//    animation->setStartValue(QRect(0, 0, 100, 30));
//    animation->setEndValue(QRect(250, 250, 100, 30));

//    animation->start();
}

void MainWindow::on_pushButton_clicked()
{
    if (((ui->L_mm->text().toDouble()<=60) && (ui->L_ss->text().toDouble() <= 60) && ((ui->L_dd->text().toDouble() <=180) && (ui->L_dd->text().toDouble() >= -180))) &&
       ((ui->W_mm->text().toDouble()<=60) && (ui->W_ss->text().toDouble() <= 60) && ((ui->W_dd->text().toDouble() <=90) && (ui->L_dd->text().toDouble() >= -90)))) {
        double longitude = (ui->L_dd->text().toDouble()) + ((ui->L_mm->text()).toDouble()/60) + (ui->L_ss->text().toDouble()/3600);
        double width = (ui->W_dd->text().toDouble()) + ((ui->W_mm->text()).toDouble()/60) + (ui->W_ss->text().toDouble()/3600);
        ui->L_output->setText(QString::number(longitude));
        ui->W_output->setText(QString::number(width));
    }else {
        ui->errorLabel->setText("Введены некорректные значения");
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    ui->W_dd->setText(QString::number(floor(ui->W_output->text().toDouble())));
    ui->W_mm->setText(QString::number((floor(((ui->W_output->text().toDouble()) - (ui->W_dd->text().toDouble()))*60))));
    ui->W_ss->setText(QString::number((((ui->W_output->text().toDouble()) - (ui->W_dd->text().toDouble()))*60 - ui->W_mm->text().toDouble())*60));

    ui->L_dd->setText(QString::number(floor(ui->L_output->text().toDouble())));
    ui->L_mm->setText(QString::number((floor(((ui->L_output->text().toDouble()) - (ui->L_dd->text().toDouble()))*60))));
    ui->L_ss->setText(QString::number((((ui->L_output->text().toDouble()) - (ui->L_dd->text().toDouble()))*60 - ui->L_mm->text().toDouble())*60));

}

void MainWindow::on_pushButton_4_clicked()
{
    double a = ui->aplhaRad->text().toDouble()/2;
    double b = ui->betaRad->text().toDouble()/2;
    double g = ui->gammaRad->text().toDouble()/2;

    QString order = ui->order->currentText();
    double qX,qY,qZ,qW;

    if (order == "ZYXr") {
        qX =  cos(b)*sin(g)*cos(a) - sin(b)*cos(g)*sin(a);
        qY =  cos(b)*sin(g)*sin(a) + sin(b)*cos(g)*cos(a);
        qZ =  cos(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
    }else if (order == "XYXr") {
        qX =  cos(b)*cos(g)*sin(a) + cos(b)*sin(g)*cos(a);
        qY =  sin(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
        qZ =  sin(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) - cos(b)*sin(g)*sin(a);
    }else if (order == "YZXr") {
        qX =  cos(-b)*sin(g)*cos(a) - sin(-b)*cos(g)*sin(a);
        qZ = -cos(-b)*sin(g)*sin(a) - sin(-b)*cos(g)*cos(a);
        qY =  cos(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) + sin(-b)*sin(g)*sin(a);
    }else if (order == "XZXr") {
        qX =  cos(-b)*cos(g)*sin(a) + cos(-b)*sin(g)*cos(a);
        qZ = -sin(-b)*cos(g)*cos(a) - sin(-b)*sin(g)*sin(a);
        qY =  sin(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) - cos(-b)*sin(g)*sin(a);
    }else if (order == "XZYr") {
        qY =  cos(b)*sin(g)*cos(a) - sin(b)*cos(g)*sin(a);
        qZ =  cos(b)*sin(g)*sin(a) + sin(b)*cos(g)*cos(a);
        qX =  cos(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
    }else if (order == "YZYr") {
        qY =  cos(b)*cos(g)*sin(a) + cos(b)*sin(g)*cos(a);
        qZ =  sin(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
        qX =  sin(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) - cos(b)*sin(g)*sin(a);
    }else if (order == "ZXYr") {
        qY =  cos(-b)*sin(g)*cos(a) - sin(-b)*cos(g)*sin(a);
        qX = -cos(-b)*sin(g)*sin(a) - sin(-b)*cos(g)*cos(a);
        qZ =  cos(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) + sin(-b)*sin(g)*sin(a);
    }else if (order == "YXYr") {
        qY =  cos(-b)*cos(g)*sin(a) + cos(-b)*sin(g)*cos(a);
        qX = -sin(-b)*cos(g)*cos(a) - sin(-b)*sin(g)*sin(a);
        qZ =  sin(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) - cos(-b)*sin(g)*sin(a);
    }else if (order == "YXZr") {
        qZ =  cos(b)*sin(g)*cos(a) - sin(b)*cos(g)*sin(a);
        qX =  cos(b)*sin(g)*sin(a) + sin(b)*cos(g)*cos(a);
        qY =  cos(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
    }else if (order == "ZXZr") {
        qZ =  cos(b)*cos(g)*sin(a) + cos(b)*sin(g)*cos(a);
        qX =  sin(b)*cos(g)*cos(a) + sin(b)*sin(g)*sin(a);
        qY =  sin(b)*cos(g)*sin(a) - sin(b)*sin(g)*cos(a);
        qW =  cos(b)*cos(g)*cos(a) - cos(b)*sin(g)*sin(a);
    }else if (order == "XYZr") {
        qZ =  cos(-b)*sin(g)*cos(a) - sin(-b)*cos(g)*sin(a);
        qY = -cos(-b)*sin(g)*sin(a) - sin(-b)*cos(g)*cos(a);
        qX =  cos(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) + sin(-b)*sin(g)*sin(a);
    }else if (order == "ZYZr") {
        qZ =  cos(-b)*cos(g)*sin(a) + cos(-b)*sin(g)*cos(a);
        qY = -sin(-b)*cos(g)*cos(a) - sin(-b)*sin(g)*sin(a);
        qX =  sin(-b)*cos(g)*sin(a) - sin(-b)*sin(g)*cos(a);
        qW =  cos(-b)*cos(g)*cos(a) - cos(-b)*sin(g)*sin(a);
    }else if (order == "ZYXs") {
        qZ =  cos(-b)*sin(a)*cos(g) - sin(-b)*cos(a)*sin(g);
        qY = -cos(-b)*sin(a)*sin(g) - sin(-b)*cos(a)*cos(g);
        qX =  cos(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) + sin(-b)*sin(a)*sin(g);
    }else if (order == "XYXs") {
        qX =  cos(b)*cos(a)*sin(g) + cos(b)*sin(a)*cos(g);
        qY =  sin(b)*cos(a)*cos(g) + sin(b)*sin(a)*sin(g);
        qZ =  sin(b)*cos(a)*sin(g) - sin(b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) - cos(b)*sin(a)*sin(g);
    }else if (order == "YZXs") {
        qY =  cos(b)*sin(a)*cos(g) - sin(b)*cos(a)*sin(g);
        qZ =  cos(b)*sin(a)*sin(g) + sin(b)*cos(a)*cos(g);
        qX =  cos(b)*cos(a)*sin(g) - sin(b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) + sin(b)*sin(a)*sin(g);
    }else if (order == "XZXs") {
        qX =  cos(-b)*cos(a)*sin(g) + cos(-b)*sin(a)*cos(g);
        qZ = -sin(-b)*cos(a)*cos(g) - sin(-b)*sin(a)*sin(g);
        qY =  sin(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) - cos(-b)*sin(a)*sin(g);
    }else if (order == "XZYs") {
        qX =  cos(-b)*sin(a)*cos(g) - sin(-b)*cos(a)*sin(g);
        qZ = -cos(-b)*sin(a)*sin(g) - sin(-b)*cos(a)*cos(g);
        qY =  cos(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) + sin(-b)*sin(a)*sin(g);
    }else if (order == "YZYs") {
        qY =  cos(b)*cos(a)*sin(g) + cos( b)*sin(a)*cos(g);
        qZ =  sin(b)*cos(a)*cos(g) + sin( b)*sin(a)*sin(g);
        qX =  sin(b)*cos(a)*sin(g) - sin( b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) - cos( b)*sin(a)*sin(g);
    }else if (order == "ZXYs") {
        qZ =  cos(b)*sin(a)*cos(g) - sin(b)*cos(a)*sin(g);
        qX =  cos(b)*sin(a)*sin(g) + sin(b)*cos(a)*cos(g);
        qY =  cos(b)*cos(a)*sin(g) - sin(b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) + sin(b)*sin(a)*sin(g);
    }else if (order == "YXYs") {
        qY =  cos(-b)*cos(a)*sin(g) + cos(-b)*sin(a)*cos(g);
        qX = -sin(-b)*cos(a)*cos(g) - sin(-b)*sin(a)*sin(g);
        qZ =  sin(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) - cos(-b)*sin(a)*sin(g);
    }else if (order == "YXZs") {
        qY =  cos(-b)*sin(a)*cos(g) - sin(-b)*cos(a)*sin(g);
        qX = -cos(-b)*sin(a)*sin(g) - sin(-b)*cos(a)*cos(g);
        qZ =  cos(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) + sin(-b)*sin(a)*sin(g);
    }else if (order == "ZXZs") {
        qZ =  cos(b)*cos(a)*sin(g) + cos(b)*sin(a)*cos(g);
        qX =  sin(b)*cos(a)*cos(g) + sin(b)*sin(a)*sin(g);
        qY =  sin(b)*cos(a)*sin(g) - sin(b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) - cos(b)*sin(a)*sin(g);
    }else if (order == "XYZs") {
        qX =  cos(b)*sin(a)*cos(g) - sin(b)*cos(a)*sin(g);
        qY =  cos(b)*sin(a)*sin(g) + sin(b)*cos(a)*cos(g);
        qZ =  cos(b)*cos(a)*sin(g) - sin(b)*sin(a)*cos(g);
        qW =  cos(b)*cos(a)*cos(g) + sin(b)*sin(a)*sin(g);
    }else if (order == "ZYZs") {
        qZ =  cos(-b)*cos(a)*sin(g) + cos(-b)*sin(a)*cos(g);
        qY = -sin(-b)*cos(a)*cos(g) - sin(-b)*sin(a)*sin(g);
        qX =  sin(-b)*cos(a)*sin(g) - sin(-b)*sin(a)*cos(g);
        qW =  cos(-b)*cos(a)*cos(g) - cos(-b)*sin(a)*sin(g);
    }

    ui->outputW->setText(QString::number(qW,'d',7));
    ui->outputX->setText(QString::number(qX,'d',7));
    ui->outputY->setText(QString::number(qY,'d',7));
    ui->outputZ->setText(QString::number(qZ,'d',7));
}

void MainWindow::on_pushButton_5_clicked()
{
    double W = ui->qW->text().toDouble();
    double X = ui->qX->text().toDouble();
    double Y = ui->qY->text().toDouble();
    double Z = ui->qZ->text().toDouble();

    double Nq = X*X+Y*Y+Z*Z+W*W;
    double s;
    double xs,ys,zs,
           wx,wy,wz,
           xx,xy,xz,
           yy,yz,zz;

    if (Nq > 0) {
        s = 2/Nq;
    }else {
        s = 0;
    }

    xs = X*s;  ys = Y*s;  zs = Z*s;
    wx = W*xs; wy = W*ys; wz = W*zs;
    xx = X*xs; xy = X*ys; xz = X*zs;
    yy = Y*ys; yz = Y*zs; zz = Z*zs;

    double Matrix[4][4];
    Matrix[0][0] = 1.0 - (yy + zz);  Matrix[0][1] = xy - wz;          Matrix[0][2] = xz + wy;           Matrix[0][3]=0;
    Matrix[1][0] = xy + wz;          Matrix[1][1] = 1.0 - (xx + zz);  Matrix[1][2] = yz - wx;           Matrix[1][3]=0;
    Matrix[2][0] = xz - wy;          Matrix[2][1] = yz + wx;          Matrix[2][2] = 1 - (xx + yy);     Matrix[2][3]=0;
    Matrix[3][0] = 0;                Matrix[3][1] = 0;                Matrix[3][2] = 0;                 Matrix[3][3]=1;

    double FLT_EPSILON = 0.000002;
    double cy,sy;
    double alphaRad,betaRad,gammaRad;
    QString order = ui->comboBox->currentText();

    if (order == "ZYXr") {
        cy = sqrt(Matrix[0][0]*Matrix[0][0] + Matrix[1][0]*Matrix[1][0]);
        if (cy > 16*FLT_EPSILON) {
            gammaRad = atan2(Matrix[2][1], Matrix[2][2]);
            betaRad = atan2(-Matrix[2][0], cy);
            alphaRad = atan2(Matrix[1][0], Matrix[0][0]);
        }else {
            gammaRad = atan2(-Matrix[1][2], Matrix[1][1]);
            betaRad  = atan2(-Matrix[2][0], cy);
            alphaRad = 0;
        }
        qDebug() << alphaRad << endl << betaRad << endl << gammaRad;
    }else if (order == "XYXr"){
        sy = sqrt(Matrix[0][1]*Matrix[0][1] + Matrix[0][2]*Matrix[0][2]);
        if (sy > 16*FLT_EPSILON) {
            gammaRad = atan2(Matrix[0][1], Matrix[0][2]);
            betaRad  = atan2(sy, Matrix[0][0]);
            alphaRad = atan2(Matrix[1][0], -Matrix[2][0]);
        }else {
            gammaRad = atan2(-Matrix[1][2], Matrix[1][1]);
            betaRad  = atan2(sy, Matrix[0][0]);
            alphaRad = 0;
        }
    }else if (order == "YZXr") {
        cy = sqrt(Matrix[0][0]*Matrix[0][0] + Matrix[2][0]*Matrix[2][0]);
        if (cy > 16*FLT_EPSILON) {
            gammaRad = -atan2(Matrix[1][2], Matrix[1][1]);
            betaRad  = -atan2(-Matrix[1][0], cy);
            alphaRad = -atan2(Matrix[2][0], Matrix[0][0]);
        }else {
            gammaRad = -atan2(-Matrix[2][1], Matrix[2][2]);
            betaRad  = -atan2(-Matrix[1][0], cy);
            alphaRad = 0;
        }
    }


    ui->outputAlpha->setText(QString::number(alphaRad,'d',7));
    ui->outputBeta->setText(QString::number(betaRad,'d',7));
    ui->outputGamma->setText(QString::number(gammaRad,'d',7));
}
