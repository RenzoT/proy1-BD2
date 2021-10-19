#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void showCSV(QString filename);
private slots:


     void on_pushButton_clicked();

private:

    void setValueAt(int ix, int jx, const QString &value);

    Ui::MainWindow *ui;
    QStandardItemModel *mModel;
};
#endif // MAINWINDOW_H
