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

private:
    QStringList m_operators;
    int m_maxInitialDepth;
    int addRandomChild(QTreeWidgetItem * const parent, int excludeRC = -1);
    QTreeWidgetItem *addRandomNumberAsChild(QTreeWidgetItem * const parent);
    QTreeWidgetItem *addImageAsChild(QTreeWidgetItem * const parent);
    QTreeWidgetItem *addRandomOperatorAsChild(QTreeWidgetItem * const parent);
    int itemDepth(QTreeWidgetItem * const parent);
};

#endif // GENOME_H
