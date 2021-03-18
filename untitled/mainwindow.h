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

class QAction;
class QMenu;
class QTextEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void open();
    void Save();
    void SaveAs();
    void closeAllBase();
    void pageSetup();
    void pagePrint();
    void closeApp();
    void addPage();
    void removePage();
    void readPribor();
    void writhtePribor();
    void settingsPage();
    void helpKonf();
    void aboutKonf();

    void openRecentFile();
    void on_tabWidget_currentChanged(int index);
    void printPreview(QPrinter *printer);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    void printTable(QPrinter *printer, bool isPreview);
    void loadFile(const QString &fileName);
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);
private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();
    void closeEvent(QCloseEvent *event); 
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();

    QString curFile;
    QLabel* label;
    QLabel* label2;
    QSqlDatabase sdb;
    QSqlTableModel *model;
    CheckBoxHeader* headerr;
    QAction *separatorAct;
    QMenu *fileMenu;
    QMenu *modifyMenu;
    QMenu *priborMenu;
    QMenu *ingenerMenu;
    QMenu *recentFilesMenu;
    QMenu *helpMenu;
    bool isChanged = false;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

};
#endif // MAINWINDOW_H
