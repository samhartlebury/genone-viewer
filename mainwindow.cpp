#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genome.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    programId(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateInitialSetButton_clicked()
{
    ui->treeWidget->addTopLevelItem(Genome().generateInitialSet(programId));
    programId++;
}
