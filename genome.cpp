#include "genome.h"
#include <QDateTime>
#include <QDebug>
#include <QThread>

Genome::Genome(QObject *parent) : QObject(parent)
{
    m_operators << "add"
                << "sub"
                << "div"
                << "mul";
}

QTreeWidgetItem *Genome::generateInitialSet()
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "id:1");

    addRandomChild(item);

    return item;
}

int Genome::addRandomChild(QTreeWidgetItem *const parent)
{
    QThread::msleep(2.9); // required to set random seed
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    bool setAsOperator = double(qrand() % 2);
    bool setAsImage = double (qrand() % 2);
    int operatorChoice = double(qrand() % m_operators.size());
    double randomNumber = double(qrand() % 2000) / 1000; // limit random number (2 = max, 3 decimal places)

    QTreeWidgetItem *item = new QTreeWidgetItem();
    QString nodeObject;
    int rc = -1;

    if (setAsOperator) {
        nodeObject = m_operators[operatorChoice];
        addRandomChild(item);
        addRandomChild(item);
        rc = 0;
    } else if (setAsImage) {
        nodeObject = "image";
        rc = 1;
    } else {
        nodeObject = QString::number(randomNumber);
        rc = 2;
    }

    item->setText(0, nodeObject);
    parent->addChild(item);

    return rc;
}
