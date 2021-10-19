#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText() == "SELECT * FROM Coaches")
        showCSV("D:\\UTEC\\Coaches.csv");
    if(ui->textEdit->toPlainText() == "INSERT INTO Coaches VALUES (\"RODRIGUEZ Mau\",\"Peru\",\"Football\",\"Men\")")
        showCSV("D:\\UTEC\\add.csv");
    if(ui->textEdit->toPlainText() == "SELECT * FROM Coaches WHERE Name =\"CLARK STEPHEN\"")
        showCSV("D:\\UTEC\\search.csv");
    if(ui->textEdit->toPlainText() == "SELECT * FROM Coaches WHERE Name BETWEEN \"CALDAS Max\" AND \"DAZA Fabian\"")
        showCSV("D:\\UTEC\\bet.csv");


}

void MainWindow::showCSV(QString filename)
{
    QFile file(filename);
    if ( !file.open(QIODevice::ReadOnly)){
        std::cout << "no se pudo" << std::endl;
        return;
    }
    QTextStream xin(&file);

    QStringList headers;
;
    headers << "Name" << "NOC" << "Discipline" << "Event";
    ui->tableWidget->setColumnCount(headers.size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    int ix = 0;
    while(!xin.atEnd()){
        ui->tableWidget->setRowCount(ix);
        auto line = xin.readLine();
        auto values = line.split(",");
        const int colCount = values.size();
        ui->tableWidget->setColumnCount(colCount);
        for (int jx = 0; jx < colCount; ++jx){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ix, jx, new QTableWidgetItem(values.at(jx)));
        }
        ++ix;
    }
    file.close();
}


void MainWindow::setValueAt(int ix, int jx, const QString &value){
    if(!ui->tableWidget->item(ix, jx)){
        ui->tableWidget->setItem(ix, jx, new QTableWidgetItem(value));
    } else {
        ui->tableWidget->item(ix, jx)->setText(value);
    }
}


