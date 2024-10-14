#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings setting;

    int taxLevel = setting.value("general/taxLeve", 21).toInt();

    if (taxLevel == 21) ui->rb21->setChecked(true);
    else ui->rb15->setChecked(true);

    if (setting.value("general/language", "EN").toString() == "EN"){
        ui->actionCzech->setChecked(false);
        ui->actionEnglish->setChecked(true);
        if (translator.load(":/i18n/SimpleTaxCalc_en.qm"))
            QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);

    }else{
        ui->actionCzech->setChecked(true);
        ui->actionEnglish->setChecked(false);
        if (translator.load(":/i18n/SimpleTaxCalc_cs.qm"))
            QCoreApplication::installTranslator(&translator);
        ui->retranslateUi(this);
    }


    connect(ui->leWithoutTAX, &QLineEdit::textChanged, this, &MainWindow::recalculate );
    connect(ui->rb15, &QRadioButton::clicked, this, &MainWindow::recalculate);
    connect(ui->rb21, &QRadioButton::clicked, this, &MainWindow::recalculate);
    connect(ui->rb15, &QRadioButton::clicked, this, &MainWindow::rbChanged);
    connect(ui->rb21, &QRadioButton::clicked, this, &MainWindow::rbChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbClear_clicked()
{
    ui->leWithTAX->clear();
    ui->leWithoutTAX->clear();
}

void MainWindow::recalculate()
{
    bool success;
    double value = ui->leWithoutTAX->text().toDouble(&success);
    if (success){
        if (ui->rb15->isChecked()) value *= 1.15;
        else value *= 1.21;
        ui->leWithTAX->setText(QString("%1").arg(value));
    } else ui->leWithTAX->setText("N/A");
}

void MainWindow::rbChanged()
{
    QSettings settings;
    int value = 0;
    if (ui->rb15->isChecked()) value = 15;
    else value = 21;
    settings.setValue("general/taxLeve", value);
}



void MainWindow::on_actionEnglish_triggered()
{
    QSettings settings;
    ui->actionCzech->setChecked(false);
    settings.setValue("general/language", "EN");
    QCoreApplication::removeTranslator(&translator);
    if (translator.load(":/i18n/SimpleTaxCalc_en.qm"))
        QCoreApplication::installTranslator(&translator);
    ui->retranslateUi(this);
}

void MainWindow::on_actionCzech_triggered()
{
    QSettings settings;
    ui->actionEnglish->setChecked(false);
    settings.setValue("general/language", "CZ");
    QCoreApplication::removeTranslator(&translator);
    if(translator.load(":/i18n/SimpleTaxCalc_cs.qm"))
        QCoreApplication::installTranslator(&translator);
    ui->retranslateUi(this);
}
