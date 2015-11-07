#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genome.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    genome(new Genome()),
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
    ui->treeWidget->addTopLevelItem(genome->generateInitialSet(programId));
    programId++;
}

void MainWindow::on_dial_valueChanged(int value)
{
    genome->setMaxInitialDepth(value);
    ui->depthLabel->setText(QString::number(value));
}
