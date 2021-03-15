#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QPrinter>

#include "checkboxheader.h"
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();

    void on_actionLoad_triggered();

    void on_actionClose_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionPLUS_triggered();

    void on_actionMINUS_triggered();

    void on_action_11_triggered();

    void on_actionprint_triggered();

    void on_action_13_triggered();

    void on_action_6_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_action_triggered();

    void on_action_5_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_actionPage_Setup_triggered();

    void printPreview(QPrinter *printer);

//    void UpdateRecentFileActions();

//    void OpenRecentFile();

//    QString StrippedName(const QString &fullFileName);

    void on_action_7_triggered();

private:
    Ui::MainWindow *ui;
    QLabel* label;
    QLabel* label2;
    QSqlDatabase sdb;
    QSqlTableModel *model;
    CheckBoxHeader* headerr;
    QAction *separatorAct;
    enum { MaxRecentFiles = 5 };
    QAction *RecentProjects[MaxRecentFiles];

    void printTable(QPrinter *printer, bool isPreview);

};
#endif // MAINWINDOW_H
