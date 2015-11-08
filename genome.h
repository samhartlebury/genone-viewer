// Sam Hartlebury 2015
/*
CLass to handle all aspects of the programs genome:
Used to create an initial set with a chosen maximum depth,
convert genomes to scripts for QScript engine execution,
crossover breed genomes and apply mutation to genomes.
*/

#ifndef GENOME_H
#define GENOME_H

#include <QObject>
#include <QTreeWidget>

class Genome : public QObject
{
    Q_OBJECT
public:
    explicit Genome(QObject *parent = 0);
    QTreeWidgetItem *generateInitialSet(int id = 0);
    void setMaxInitialDepth(int depth);
    void convertToString(QTreeWidgetItem * const parent, QString &executableScript);
    void examineTree(QTreeWidgetItem * const topLevel);
    QTreeWidgetItem *crossoverBreedGenomes(QTreeWidgetItem * const topLevel1, QTreeWidgetItem * const topLevel2);
    QTreeWidgetItem *pickRandomChild(QTreeWidgetItem * const parent);
    void allChildrenAsList(QTreeWidgetItem * const parent, QList<QTreeWidgetItem *> &childList);
private:
    QStringList m_operators;
    int m_maxInitialDepth;
    int addRandomChild(QTreeWidgetItem * const parent, int excludeRC = -1);
    QTreeWidgetItem *addRandomNumberAsChild(QTreeWidgetItem * const parent);
    QTreeWidgetItem *addImageAsChild(QTreeWidgetItem * const parent);
    QTreeWidgetItem *addRandomOperatorAsChild(QTreeWidgetItem * const parent);
    int itemDepth(QTreeWidgetItem * const parent);
    QTreeWidgetItem *bottomChildren(QTreeWidgetItem * const parent, QList<QTreeWidgetItem *> &bottomChildList);
    void filterPairs(QTreeWidgetItem *parent, int itemIndex, QTreeWidgetItem *baby2, QTreeWidgetItem *randomChild2);
};

#endif // GENOME_H
