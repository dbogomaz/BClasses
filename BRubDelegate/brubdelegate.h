/* Предназначен для работы с полями с int в QTableWiev с использованием QTableModel,
 * которые содержат значение в копейках и приводит к формату "9 999,99 руб."
 */
#ifndef BRUBDELEGATE_H
#define BRUBDELEGATE_H

#include <QStyledItemDelegate>

#include <QDebug>

class BRubDelegate : public QStyledItemDelegate
{
public:
    BRubDelegate();
    static QString toRub(int value); // преобразует int копейки в финансовый рублевый формат,
                                     // метод статический, что бы можно было использовать извне

// QStyledItemDelegate interface
public:
    virtual QString displayText(const QVariant &value, const QLocale &locale) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    const int MAX_VALUE = 2147483647; // максимальное заначение для int
    static const QString CURRENCY;    // валюта (статическая константа) по сути глобальная
};

#endif // BRUBDELEGATE_H
