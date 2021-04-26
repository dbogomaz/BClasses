/* Предназначен для редактирования полей с датой в QTableWiev с использованием QTableModel.
 * Для использования в QTableModel необходимо создать делегат где переопределить createEditor в котором
 * должен быть return nullptr. Иначе, после закрытия вызывается делегат для редактриования.
 * Класс возвращает индекс и значение потому в программе нужен метод или слот который примет эти параметры.
 * Например:
 * void MainWindow::setData(const QModelIndex &index, const QVariant &value)
 * {
 *     m_tableModel->setData(index, value);
 * }
 * Вызывать по двойному щелчку в ячейке:
 * void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
 * {
 *     BCalendarDelegate *dd = new BCalendarDelegate(index);
 *     connect(dd, &BCalendarDelegate::activated, this, &MainWindow::setData);
 *     dd->exec();
 * }
 */
#ifndef BCalendarDelegate_H
#define BCalendarDelegate_H

#include <QWidget>
#include <QDialog>
#include <QCalendarWidget>
#include <QHBoxLayout>
#include <QModelIndex>

#include <QDebug>

class BCalendarDelegate : public QDialog
{
    Q_OBJECT
public:
    BCalendarDelegate(const QModelIndex &index, QWidget *parent = nullptr);

signals:
    void activated(const QModelIndex &index, const QDate &date);

private slots:
    void accept() override;

private:
    QModelIndex m_index;
    QCalendarWidget *m_cw;

};

#endif // BCalendarDelegate_H
