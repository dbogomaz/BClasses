/* Предназначен для редактирования полей с датой в QTableWiev с использованием QTableModel.
 */
#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QDateEdit>

#include <QDebug>

class BDateEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BDateEditDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // QStyledItemDelegate interface
public:
    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;

};

#endif // DATEDELEGATE_H
