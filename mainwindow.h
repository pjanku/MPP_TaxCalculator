#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbClear_clicked();
    void recalculate();
    void rbChanged();

    void on_actionEnglish_triggered();

    void on_actionCzech_triggered();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
};
#endif // MAINWINDOW_H
