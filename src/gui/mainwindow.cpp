#include "mainwindow.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new QStandardItemModel(this)),
      worker(new DataCollection(this)),
      updateTimer(new QTimer(this)) {

    auto *tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    model->setHorizontalHeaderLabels({"PID", "Name"});

    auto *widget = new QWidget;
    auto *layout = new QVBoxLayout(widget);
    layout->addWidget(tableView);
    setCentralWidget(widget);

    connect(updateTimer, &QTimer::timeout, worker, &DataCollection::update);
    connect(worker, &DataCollection::processListUpdated, this, &MainWindow::onProcessListUpdated);

    updateTimer->start(2000); 
    worker->update();      
}

MainWindow::~MainWindow() {}

void MainWindow::onProcessListUpdated(QVector<ProcessInfo> list) {
    model->removeRows(0, model->rowCount());

    for (const auto &proc : list) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(QString::number(proc.pid)));
        row.append(new QStandardItem(proc.name));
        model->appendRow(row);
    }
}