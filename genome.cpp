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

int Genome::itemDepth(QTreeWidgetItem * parent)
{
    QTreeWidgetItem *item = parent;
    int depth = 0;
    while(item != 0) {
        item = item->parent();
        ++depth;
    }

    return depth;
}

void Genome::examineTree(QTreeWidgetItem * const topLevel)
{
    QList<QTreeWidgetItem *> bottomList;
    bottomChildren(topLevel->child(0), bottomList);
}

QTreeWidgetItem *Genome::pickRandomChild(QTreeWidgetItem * const parent)
{
    Q_ASSERT(parent);
    if (parent->childCount() < 2)
        return parent;

    QList<QTreeWidgetItem*> childList;
    allChildrenAsList(parent->child(0), childList);
    allChildrenAsList(parent->child(1), childList);

    Q_ASSERT(childList.size());

    QTreeWidgetItem *randomChild = childList[qrand() % childList.length()];

    return randomChild;
}

void Genome::allChildrenAsList(QTreeWidgetItem * const parent, QList<QTreeWidgetItem*> &childList)
{
    childList.append(parent);

    if (parent->childCount() < 2)
        return;

    allChildrenAsList(parent->child(0), childList);
    allChildrenAsList(parent->child(1), childList);
}

void Genome::filterPairs(QTreeWidgetItem *parent, int itemIndex, QTreeWidgetItem *baby2, QTreeWidgetItem *randomChild2)
{
    bool randomChild1siblingIsInt = false;
    parent->child(1 - itemIndex)->text(0).toInt(&randomChild1siblingIsInt);
    bool randomChild2IsInt = false;
    randomChild2->text(0).toInt(&randomChild2IsInt);

    if (parent->child(1 - itemIndex)->text(0) == randomChild2->text(0))
        randomChild2 = pickRandomChild(baby2->child(0))->clone();
    else if (randomChild1siblingIsInt && randomChild2IsInt)
        randomChild2 = pickRandomChild(baby2->child(0))->clone();
    else
        return;

    filterPairs(parent, itemIndex, baby2, randomChild2);
}

QTreeWidgetItem *Genome::crossoverBreedGenomes(QTreeWidgetItem * const topLevel1, QTreeWidgetItem * const topLevel2)
{
    Q_ASSERT(topLevel1->child(0) && topLevel2->child(0));
    QTreeWidgetItem *baby1 = topLevel1->clone(); //= new QTreeWidgetItem();
    QTreeWidgetItem *baby2 = topLevel2->clone();
    QTreeWidgetItem *randomChild1 = pickRandomChild(baby1->child(0));
    QTreeWidgetItem *randomChild2 = pickRandomChild(baby2->child(0))->clone();
    QTreeWidgetItem *parent = randomChild1->parent();
    int itemIndex = parent->indexOfChild(randomChild1);

    filterPairs(parent, itemIndex, baby2, randomChild2);

    parent->removeChild(randomChild1);
    parent->insertChild(itemIndex, randomChild2);

    baby1->setText(0, "(" + topLevel1->text(0) + "+" + topLevel2->text(0) + ")");
    QString baby1string;
    convertToString(baby1->child(0), baby1string);
    QString randomChild1string;
    convertToString(randomChild1, randomChild1string);
    QString randomChild2string;
    convertToString(randomChild2, randomChild2string);


    qDebug() << endl << "swapped " << randomChild1string
             << endl << "with " << randomChild2string
             << endl << endl << baby1string;

    return baby1;
}

void Genome::convertToString(QTreeWidgetItem * const parent, QString &executableScript)
{
    executableScript.append(parent->text(0));

    if (parent->childCount() < 2)
        return;

    executableScript.append('(');
    convertToString(parent->child(0), executableScript);
    executableScript.append(',');
    convertToString(parent->child(1), executableScript);
    executableScript.append(')');

    return;
}


QTreeWidgetItem *Genome::bottomChildren(QTreeWidgetItem * const parent, QList<QTreeWidgetItem*> &bottomChildList)
{

    if (parent->childCount() < 2)
        return parent;


    QTreeWidgetItem *path1 = parent->child(0);
    QTreeWidgetItem *path2 = parent->child(1);

    auto *path1Child = bottomChildren(path1, bottomChildList);
    auto *path2Child = bottomChildren(path2, bottomChildList);

    if (path1Child == path1) {
        qDebug() << path1->text(0) << itemDepth(path1) - 1;
        bottomChildList.append(path1Child);
    }
    if(path2Child == path2) {
        qDebug() << path2->text(0) << itemDepth(path2) - 1;
        bottomChildList.append(path2Child);
    }

    return path1;
}

QTreeWidgetItem *Genome::addRandomOperatorAsChild(QTreeWidgetItem * const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    int operatorChoice = double(qrand() % m_operators.size());
    item->setText(0, m_operators[operatorChoice]);
    parent->addChild(item);

    return item;
}

QTreeWidgetItem *Genome::addImageAsChild(QTreeWidgetItem * const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "image");
    parent->addChild(item);

    return item;
}

QTreeWidgetItem *Genome::addRandomNumberAsChild(QTreeWidgetItem * const parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    double randomNumber = double(qrand() % 2000) / 1000; // limit random number (2 = max, 3 decimal places)
    item->setText(0, QString::number(randomNumber));
    parent->addChild(item);

    return item;
}

int Genome::addRandomChild(QTreeWidgetItem * const parent, int excludeRC)
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
