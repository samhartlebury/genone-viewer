#include "genome.h"

#include <QColor>
#include <QDateTime>
#include <QDebug>
#include <QThread>

Genome::Genome(QObject *parent) :
    QObject(parent),
    m_maxInitialDepth(4)
{
    qsrand(QDateTime::currentDateTime().toMSecsSinceEpoch()); // set random seed
    m_operators << "add"
                << "sub"
                << "div"
                << "mul";
}

void Genome::setMaxInitialDepth(int depth)
{
    m_maxInitialDepth = depth;
}

QTreeWidgetItem *Genome::generateInitialSet(int id)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    addRandomChild(item, 3); // excludeRC 3 = exclude image or number (only operator allowed as top node)
    item->setBackgroundColor(0, QColor::fromHsv((id * 10) % 255, 200, 255));
    item->setText(0, "program " + QString::number(id));

    return item;
}

int Genome::itemDepth(QTreeWidgetItem *const parent)
{
    QTreeWidgetItem *item = parent;
    int depth = 0;
    while(item != 0) {
        item = item->parent();
        ++depth;
    }

    return depth;
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
    bool setAsOperator = double(qrand() % 2);
    bool setAsImage = double (qrand() % 2);

    switch (excludeRC) { // exclusion rules
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
    case 3:
        setAsOperator = true;
        break;
    }

    if (itemDepth(parent) >= m_maxInitialDepth) { // depth case
        setAsOperator = false;
        if (excludeRC == 2)
            setAsImage = true;
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
