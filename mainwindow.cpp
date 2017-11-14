#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include "reversepolish.h"
#include "qcustomplot.h"
#include "bet.h"
#include <queue>
#include <exception>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Odwrotna Notacja Polska"));
    z.resize(1001);
    y.resize(1001);


    equation = ui->equation;
    eqOutput = ui->eqOutput;
    from = ui->from;
    to=ui->to;
    graph=ui->graph;
    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupPlot()
{
    graph->xAxis->setLabel("y");
    graph->yAxis->setLabel("z");
    graph->addGraph();
    graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_confirm_clicked()
{
    try
    {
    reversePolish rp;
    QString c = equation->toPlainText();
    string b = c.toStdString();
    eq_to_bet = b;
    string d = rp.postfix_string(rp.infix_to_postfix(b));
    c = c.fromStdString("Odwrotna Notacja Polska:   " + d);
    eqOutput->setText(c);
    }

    catch(const exception & ex)
    {cerr << ex.what() << endl;
       QString g;
       g = g.fromStdString("Odwrotna Notacja Polska:   Proszę sprawdzić równanie");
       eqOutput->setText(g);
    }

}

void MainWindow::on_draw_clicked()
{
    try{
    QString c = from->toPlainText();
    QString d = to->toPlainText();
    double from_dbl = std::stod(c.toStdString());
    double to_dbl = std::stod(d.toStdString());
    double i2;
    double range = to_dbl - from_dbl;
    reversePolish rp;
    string infix = eq_to_bet;

    queue<string> postfix = rp.infix_to_postfix(infix);
    if (!infix.empty() && postfix.back()!="Cos poszlo nie tak"){
        BET binary_expression_tree(postfix);
    if(range > 0){
        for (int i = 0; i < 1001; i++){
            i2 = double(i);
            y[i] = from_dbl + i2*range/1000;
            z[i] = binary_expression_tree.getValue_publc(y[i]);
        }
    }
    graph->graph(0)->setData(y, z);
    graph->graph(0)->rescaleAxes();
    graph->replot();
    }
    }

    catch(const exception & ex)
    {  cerr << ex.what() << endl;
       QString g;
       g = g.fromStdString("Odwrotna Notacja Polska:   Proszę sprawdzić równanie");
       eqOutput->setText(g);
    }

}

