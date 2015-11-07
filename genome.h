#ifndef GENOME_H
#define GENOME_H

#include <QObject>
#include <QTreeWidget>

class Genome : public QObject
{
    Q_OBJECT
public:
    explicit Genome(QObject *parent = 0);
    QTreeWidgetItem *generateInitialSet();

private:
    int addRandomChild(QTreeWidgetItem * const parent);

    QStringList m_operators;
};

#endif // GENOME_H
