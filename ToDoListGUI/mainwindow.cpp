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
    taskModel->setHorizontalHeaderLabels({"Task", "Due Date", "Type", "Status"});
    ui->ListTask->setModel(taskModel);
    
    // Configure table columns
    ui->ListTask->horizontalHeader()->setStretchLastSection(false);
    ui->ListTask->setColumnWidth(0, 300);  // Task name - wider
    ui->ListTask->setColumnWidth(1, 120);  // Due date
    ui->ListTask->setColumnWidth(2, 100);  // Type
    ui->ListTask->setColumnWidth(3, 150);  // Status
    
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

void MainWindow::onAddTaskClicked()
{
    QString taskText = ui->lineEdit->text();
    QDate selectedDate = ui->dateEdit->date();
    QString taskType = ui->comboBox->currentText();
    
    if (taskText.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a task!");
        return;
    }
    
    // Create a new task based on selected type
    baseTask* newTask = nullptr;
    
    if (taskType == "Daily Task") {
        newTask = new dailyTask(
            selectedDate.day(),
            selectedDate.month(),
            selectedDate.year(),
            taskText.toStdString()
        );
    } else {
        newTask = new oneTimeTask(
            selectedDate.day(),
            selectedDate.month(),
            selectedDate.year(),
            taskText.toStdString()
        );
    }
    
    if (newTask->isValid()) {
        platform.addTask(newTask);
        refreshTaskDisplay();
        ui->lineEdit->clear();
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

