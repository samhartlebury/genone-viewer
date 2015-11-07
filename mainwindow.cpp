#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genome.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Genome genome;
    ui->treeWidget->addTopLevelItem(genome.generateInitialSet());
    ui->treeWidget->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}
