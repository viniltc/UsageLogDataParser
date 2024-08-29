#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // test git
    ui->dataTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->dataTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Text Files (*.txt);;All Files (*)"));

    std::optional<WalkingData> parsedData = parser.parse(fileName);

    if (parsedData) {
        walkingData = *parsedData;  // Extract the value from std::optional
        displayParsedData();        // Now it's safe to use walkingData
    } else {
        // Handle the error case, e.g., show a message box
        QMessageBox::warning(this, "Error", "Failed to parse walking data.");
    }
}

void MainWindow::displayParsedData()
{

       qDebug() << "Start Date:" << walkingData.startDate.toString();
       qDebug() << "End Date:" << walkingData.endDate.toString();
       qDebug() << "Total Days:" << walkingData.totalDays;


       QString displayText = QString("Start Date: %1\nEnd Date: %2\nTotal Days: %3\nCH1 Total Steps: %4\n")
                               .arg(walkingData.startDate.toString())
                               .arg(walkingData.endDate.toString())
                               .arg(walkingData.totalDays)
                               .arg(walkingData.ch1TotalSteps);


       ui->dataDisplayTextEdit->setPlainText(displayText);


       ui->dataTableWidget->clear();


       ui->dataTableWidget->setRowCount(4);  // Adjust the number of rows based on your data
       ui->dataTableWidget->setColumnCount(2);  // Two columns: one for labels and one for values


       QStringList headers;
       headers << "Property" << "Value";
       ui->dataTableWidget->setHorizontalHeaderLabels(headers);


       ui->dataTableWidget->setItem(0, 0, new QTableWidgetItem("Start Date"));
       ui->dataTableWidget->setItem(0, 1, new QTableWidgetItem(walkingData.startDate.toString()));

       ui->dataTableWidget->setItem(1, 0, new QTableWidgetItem("End Date"));
       ui->dataTableWidget->setItem(1, 1, new QTableWidgetItem(walkingData.endDate.toString()));

       ui->dataTableWidget->setItem(2, 0, new QTableWidgetItem("Total Days"));
       ui->dataTableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(walkingData.totalDays)));

       ui->dataTableWidget->setItem(3, 0, new QTableWidgetItem("CH1 Total Steps"));
       ui->dataTableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(walkingData.ch1TotalSteps)));


    //   ui->dataTableWidget->resizeColumnsToContents();
}

