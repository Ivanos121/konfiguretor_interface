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
    void onCheckBoxHeaderClick1();
    void onCheckBoxHeaderClick2();

    void open();

    void closeAllBase();

    void newFile();

    void Save();

    void SaveAs();

    void addPage();

    void removePage();

    void on_action_11_triggered();

    void on_actionprint_triggered();

    void on_action_13_triggered();

    void on_action_6_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_action_triggered();

    void on_action_5_triggered();

    void on_action_9_triggered();

    void on_action_10_triggered();

    void pageSetup();

    void printPreview(QPrinter *printer);

    void openRecentFile();

    void setCurrentFile(const QString &fileName);

    void updateRecentFileActions();

    QString strippedName(const QString &fullFileName);

    void on_action_7_triggered();

    void printTable(QPrinter *printer, bool isPreview);

    void readPribor();

    void writhtePribor();

    void settingsPage();

    void helpKonf();

    void aboutKonf();

    void loadFile(const QString &fileName);

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenus();

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
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printSetupsAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *closeAct;
    QAction *addAct;
    QAction *removeAct;
    QAction *readAct;
    QAction *writhteAct;
    QAction *settingsAct;
    QAction *helpAct;
    QAction *konfiguretorAct;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];

};
#endif // MAINWINDOW_H
