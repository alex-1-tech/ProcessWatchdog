#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QIcon>
#include "core/processmanager.h"
#include "processdetailsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new ProcessViewModel(this)),
      controller(new ProcessController(this)),
      tableView(new QTableView(this)),
      searchEdit(new QLineEdit(this))
{

        tableView->setModel(model);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        auto *widget = new QWidget;
        auto *layout = new QVBoxLayout(widget);

        searchEdit->setPlaceholderText("Поиск по имени или PID процесса...");
        layout->addWidget(searchEdit);
        layout->addWidget(tableView);

        setCentralWidget(widget);

        connect(searchEdit, &QLineEdit::textChanged,
                model, &ProcessViewModel::setSearchFilter);

        connect(controller, &ProcessController::processListReady,
                model, &ProcessViewModel::updateProcessList);

        connect(model, &ProcessViewModel::processAction,
                controller, &ProcessController::handleProcessAction);

        connect(controller, &ProcessController::actionResult,
                this, &MainWindow::onActionResult);

        connect(model, &ProcessViewModel::requestActionWidget,
                this, &MainWindow::onRequestActionWidget);

        connect(tableView, &QTableView::doubleClicked, this, [this](const QModelIndex &index)
                {
                int row = index.row();
                int pid = model->item(row, 0)->text().toInt();
                auto *dialog = new ProcessDetailsDialog(pid, this);
                dialog->exec(); });

        controller->refreshProcesses();

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, controller, &ProcessController::refreshProcesses);
        timer->start(2000);
}

MainWindow::~MainWindow() {}

void MainWindow::onProcessListUpdated(QVector<ProcessInfo> list)
{
        model->updateProcessList(list);
}

void MainWindow::onActionResult(int pid, const QString &action, bool success)
{
        if (success)
        {
                qDebug() << "Action" << action << "for PID" << pid << "was successful!";
        }
        else
        {
                qDebug() << "Action" << action << "for PID" << pid << "failed!";
        }
}

void MainWindow::onRequestActionWidget(const QModelIndex &index, int pid)
{
        QWidget *buttonWidget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
        layout->setContentsMargins(0, 0, 0, 0);

        QPushButton *btnStop = new QPushButton("Stop");
        QPushButton *btnCont = new QPushButton("Continue");
        QPushButton *btnKill = new QPushButton("Kill");

        btnStop->setStyleSheet("font-size: 10px; padding: 2px 5px;");
        btnCont->setStyleSheet("font-size: 10px; padding: 2px 5px;");
        btnKill->setStyleSheet("font-size: 10px; padding: 2px 5px;");

        btnStop->setIcon(QIcon::fromTheme("media-playback-stop"));
        btnCont->setIcon(QIcon::fromTheme("media-playback-start"));
        btnKill->setIcon(QIcon::fromTheme("process-stop"));

        btnStop->setIconSize(QSize(16, 16));
        btnCont->setIconSize(QSize(16, 16));
        btnKill->setIconSize(QSize(16, 16));

        layout->addWidget(btnStop);
        layout->addWidget(btnCont);
        layout->addWidget(btnKill);

        connect(btnStop, &QPushButton::clicked, this, [this, pid]()
                { emit model->processAction(pid, "stop"); });
        connect(btnCont, &QPushButton::clicked, this, [this, pid]()
                { emit model->processAction(pid, "continue"); });
        connect(btnKill, &QPushButton::clicked, this, [this, pid]()
                { emit model->processAction(pid, "kill"); });

        tableView->setIndexWidget(index, buttonWidget);
}
