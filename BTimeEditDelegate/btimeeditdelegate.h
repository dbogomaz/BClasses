#ifndef BTIMEEDITDELEGATE_H
#define BTIMEEDITDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QTimeEdit>

#include <QDebug>

class BTimeEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    BTimeEditDelegate();

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    // QStyledItemDelegate interface
public:
    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;
};

#endif // BTIMEEDITDELEGATE_H
