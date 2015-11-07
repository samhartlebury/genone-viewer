#include "genome.h"

#include <QColor>
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

QTreeWidgetItem *Genome::generateInitialSet(int id = 0)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "programID: " + QString::number(id));
    item->setBackgroundColor(0, QColor::fromHsv((id * 10) % 255, 200, 255));
    addRandomChild(item);

    return item;
}

QTreeWidgetItem *Genome::addRandomOperatorAsChild(QTreeWidgetItem *const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    int operatorChoice = double(qrand() % m_operators.size());
    item->setText(0, m_operators[operatorChoice]);
    parent->addChild(item);

    return item;
}

QTreeWidgetItem *Genome::addImageAsChild(QTreeWidgetItem *const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "image");
    parent->addChild(item);

    return item;
}

QTreeWidgetItem *Genome::addRandomNumberAsChild(QTreeWidgetItem *const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    double randomNumber = double(qrand() % 2000) / 1000; // limit random number (2 = max, 3 decimal places)
    item->setText(0, QString::number(randomNumber));
    parent->addChild(item);

    return item;
}

int Genome::addRandomChild(QTreeWidgetItem *const parent, int excludeRC)
{
    QThread::msleep(2.9); // required to set random seed
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch());
    bool setAsOperator = double(qrand() % 2);
    bool setAsImage = double (qrand() % 2);

    switch (excludeRC) {
    case 0:
        setAsOperator = false;
        break;
    case 1:
        setAsImage = false;
        break;
    case 2:
        if (!setAsImage && !setAsOperator)
            setAsOperator = double(qrand() % 2);
        setAsImage = !setAsOperator;
        break;
    }

    int rc = -1;
    if (setAsOperator) {
        auto item = addRandomOperatorAsChild(parent);
        int result = addRandomChild(item);

        if (result != 0)
            addRandomChild(item, result);
        else
            addRandomChild(item);

        rc = 0;
    } else if (setAsImage) {
        addImageAsChild(parent);
        rc = 1;
    } else {
        addRandomNumberAsChild(parent);
        rc = 2;
    }

    return rc;
}
