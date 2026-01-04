#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDate>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Initialize the task model for the table view
    taskModel = new QStandardItemModel(this);
    taskModel->setHorizontalHeaderLabels({"Task", "Due Date", "Time", "Type", "Status"});
    ui->ListTask->setModel(taskModel);
    
    // Configure table columns
    ui->ListTask->horizontalHeader()->setStretchLastSection(false);
    ui->ListTask->setColumnWidth(0, 250);  // Task name
    ui->ListTask->setColumnWidth(1, 100);  // Due date
    ui->ListTask->setColumnWidth(2, 80);   // Time
    ui->ListTask->setColumnWidth(3, 80);   // Type
    ui->ListTask->setColumnWidth(4, 150);  // Status
    
    // Enable scrolling
    ui->ListTask->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->ListTask->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->ListTask->setAlternatingRowColors(true);
    ui->ListTask->resizeRowsToContents();
    
    // Setup date picker
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setDisplayFormat("dd/MM/yyyy");
    ui->dateEdit->setCalendarPopup(true);
    
    // Add items to ComboBox
    ui->comboBox->addItem("One-time Task");
    ui->comboBox->addItem("Daily Task");
    
    // Setup button connections
    setupConnections();
    
    // Load existing tasks from file
    QString appPath = QCoreApplication::applicationDirPath();
    QDir dir(appPath);
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    QString tasksFile = dir.path() + "/tasks.txt";
    
    try {
        platform.loadData(tasksFile.toStdString());
        refreshTaskDisplay();
    } catch (...) {
        // File doesn't exist yet, start fresh
    }
}

MainWindow::~MainWindow()
{
    saveTasks();
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->AddTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTaskClicked);
    connect(ui->MarkDoneButton, &QPushButton::clicked, this, &MainWindow::onMarkDoneClicked);
    connect(ui->DeleteButton, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(ui->comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::onTaskTypeChanged);
}

Time MainWindow::getTimeFromUI() const
{
    int hours = ui->hoursSpinBox->value();
    int minutes = ui->minutesSpinBox->value();
    int seconds = ui->secondsSpinBox->value();
    return Time(hours, minutes, seconds);
}

void MainWindow::onAddTaskClicked()
{
    QString taskText = ui->lineEdit->text();
    if(taskText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a task!");
        return;
    }
    QDate selectedDate = ui->dateEdit->date();
    QString taskType = ui->comboBox->currentText();
    Time estimatedTime = getTimeFromUI();
    
    if (taskText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a task!");
        return;
    }
    
    // Create a new task based on selected type
    baseTask* newTask = nullptr;
    
    if (taskType == "Daily Task") {
        newTask = new dailyTask(
            Date(selectedDate.day(), selectedDate.month(), selectedDate.year()),
            estimatedTime,
            taskText.toStdString()
        );
    } else {
        newTask = new oneTimeTask(
            Date(selectedDate.day(), selectedDate.month(), selectedDate.year()),
            estimatedTime,
            taskText.toStdString()
        );
    }
    
    if (newTask->isValid()) {
        platform.addTask(newTask);
        refreshTaskDisplay();
        ui->lineEdit->clear();
        ui->hoursSpinBox->setValue(0);
        ui->minutesSpinBox->setValue(0);
        ui->secondsSpinBox->setValue(0);
        QMessageBox::information(this, "Success", "Task added successfully!");
    } else {
        delete newTask;
        QMessageBox::critical(this, "Error", "Invalid task or date!");
    }
}

void MainWindow::onMarkDoneClicked()
{
    int currentRow = ui->ListTask->currentIndex().row();
    
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a task!");
        return;
    }
    
    const auto& tasks = platform.getTasks();
    if (currentRow >= 0 && currentRow < static_cast<int>(tasks.size())) {
        tasks[currentRow]->setHaveDone();
        refreshTaskDisplay();
        QMessageBox::information(this, "Success", "Task marked as done!");
    }
}

void MainWindow::onDeleteClicked()
{
    int currentRow = ui->ListTask->currentIndex().row();
    
    if (currentRow < 0) {
        QMessageBox::warning(this, "Warning", "Please select a task!");
        return;
    }
    
    platform.deleteTask(currentRow);
    refreshTaskDisplay();
    QMessageBox::information(this, "Success", "Task deleted!");
}

void MainWindow::refreshTaskDisplay()
{
    taskModel->removeRows(0, taskModel->rowCount());
    
    const auto& tasks = platform.getTasks();
    
    for (const auto& task : tasks) {
        QList<QStandardItem*> row;
        
        // Task name
        QStandardItem *taskItem = new QStandardItem(QString::fromStdString(task->getTask()));
        row.append(taskItem);
        
        // Due date
        Date dueDate = task->getDueDate();
        QString dateStr = QString::fromStdString(dueDate.getDate());
        QStandardItem *dateItem = new QStandardItem(dateStr);
        row.append(dateItem);
        
        // Estimated time
        Time est = task->getEstimatedTime();
        QString timeStr = QString("%1:%2:%3")
            .arg(est.getHours(), 2, 10, QLatin1Char('0'))
            .arg(est.getMinutes(), 2, 10, QLatin1Char('0'))
            .arg(est.getSeconds(), 2, 10, QLatin1Char('0'));
        QStandardItem *timeItem = new QStandardItem(timeStr);
        row.append(timeItem);
        
        // Task type
        std::string taskType = (dynamic_cast<dailyTask*>(task) != nullptr) ? "Daily" : "One-Time";
        QStandardItem *typeItem = new QStandardItem(QString::fromStdString(taskType));
        row.append(typeItem);
        
        // Status
        QString status = task->getHaveDone() ? "✅ Done" : "⏳ Pending";
        if (task->getIsDue()) {
            status += " (Overdue)";
        }
        QStandardItem *statusItem = new QStandardItem(status);
        row.append(statusItem);
        
        taskModel->appendRow(row);
    }
    
    // Adjust row heights to fit content
    ui->ListTask->resizeRowsToContents();
}

void MainWindow::loadTasks()
{
    try {
        QString appPath = QCoreApplication::applicationDirPath();
        QDir dir(appPath);
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
        QString tasksFile = dir.path() + "/tasks.txt";
        
        platform.loadData(tasksFile.toStdString());
        refreshTaskDisplay();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Failed to load tasks: %1").arg(e.what()));
    }
}

void MainWindow::onTaskTypeChanged(const QString &taskType)
{
    if (taskType == "Daily Task") {
        ui->dateEdit->setDate(QDate::currentDate());
        ui->dateEdit->setEnabled(false);
    } else {
        ui->dateEdit->setEnabled(true);
    }
}

void MainWindow::saveTasks()
{
    try {
        QString appPath = QCoreApplication::applicationDirPath();
        QDir dir(appPath);
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
        QString tasksFile = dir.path() + "/tasks.txt";
        
        platform.saveData(tasksFile.toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to save tasks: %1").arg(e.what()));
    }
}

