#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <string>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_confirm_clicked();

    void on_draw_clicked();

private:
    Ui::MainWindow *ui;
    QTextEdit *equation;
    QCustomPlot *graph;
    void setupPlot();

    QLabel *eqOutput;
    QString *eq;
    QTextEdit *from;
    QTextEdit *to;
    string eq_to_bet;

    QVector<double> y, z;
};

#endif // MAINWINDOW_H
