#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "genome.h"

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
    void on_generateInitialSetButton_clicked();
    void on_dial_valueChanged(int value);

    void on_breedButton_clicked();

private:
    Ui::MainWindow *ui;
    Genome *genome;
    int programId;
};

#endif // MAINWINDOW_H
