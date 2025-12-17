#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "../logic.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTaskClicked();
    void onMarkDoneClicked();
    void onDeleteClicked();
    void onTaskTypeChanged(const QString &taskType);

private:
    Ui::MainWindow *ui;
    Platform platform;
    QStandardItemModel *taskModel;
    
    void loadTasks();
    void saveTasks();
    void refreshTaskDisplay();
    void setupConnections();
};
#endif // MAINWINDOW_H
