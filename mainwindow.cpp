#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genome.h"

#include <QDebug>

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
    QTreeWidgetItem *program = genome->generateInitialSet(programId);
    ui->treeWidget->addTopLevelItem(program);
    QString executableGenome;
    genome->convertToString(program->child(0), executableGenome);
    qDebug() << executableGenome;
    programId++;
}

void MainWindow::on_dial_valueChanged(int value)
{
    genome->setMaxInitialDepth(value);
    ui->depthLabel->setText(QString::number(value));
}

void MainWindow::on_breedButton_clicked()
{
    if (ui->treeWidget->topLevelItemCount() < 2)
        return;

    QTreeWidgetItem *baby = genome->crossoverBreedGenomes(ui->treeWidget->topLevelItem(0), ui->treeWidget->topLevelItem(1));
    ui->treeWidget->addTopLevelItem(baby);
}
