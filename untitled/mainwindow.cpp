#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>
//#include <QAbstractItemModel>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QPaintEngine>
#include <QtGlobal>
#include <QCloseEvent>
#include <QMessageBox>

QString fileName;
int MAXRECENTFILE=5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createActions();
    createMenus();
    (void)statusBar();
    label=new QLabel(this);
    label2=new QLabel(this);
    ui->toolBar->addWidget(label);
    ui->toolBar->addWidget(label2);
    label->setPixmap(QPixmap(":/img/IM_24_red.png"));
    label2->setText("  Связи нет");
    ui->label_2->setText("Загрузите файл конфигурации прибора");
    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionprint->setEnabled(false);
    ui->actionPage_Setup->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->actionSave_2->setEnabled(false);
    ui->actionPLUS->setEnabled(false);
    ui->actionMINUS->setEnabled(false);
    modifyMenu->setEnabled(false);
    priborMenu->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    //fileMenu->addAction(newAct);
    fileMenu->addAction(ui->actionNew);
    fileMenu->addAction(ui->actionLoad);
    fileMenu->addAction(ui->actionSave);
    fileMenu->addAction(ui->actionSaveAs);
    fileMenu->addAction(ui->actionClose);
    separatorAct = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
    fileMenu->addAction(recentFileActs[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionPage_Setup);
    fileMenu->addAction(ui->actionprint);
    fileMenu->addSeparator();
    fileMenu->addAction(ui->actionExit);
    updateRecentFileActions();

    menuBar()->addSeparator();

    modifyMenu = menuBar()->addMenu(tr("&Редактирование"));
    modifyMenu->addAction(ui->actionPLUS);
    modifyMenu->addAction(ui->actionMINUS);

    menuBar()->addSeparator();

    priborMenu = menuBar()->addMenu(tr("&Программирование прибора"));
    priborMenu->addAction(ui->actionRead);
    priborMenu->addAction(ui->actionSave_2);

    menuBar()->addSeparator();

    ingenerMenu = menuBar()->addMenu(tr("&Инструменты"));
    ingenerMenu->addAction(ui->actionNastr);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Справка"));
    helpMenu->addAction(ui->actionHelp);
    helpMenu->addAction(ui->actionAbout);
}

void MainWindow::createActions()
{
    //newAct = new QAction(tr("&Создать новый файл конфигурации прибора"), this);
    //newAct->setShortcuts(QKeySequence::New);
    //newAct->setStatusTip(tr("Создать новый файл конфигурации прибора"));
    //newAct->setIcon(QIcon(":/img/document-new"));
    //newAct->setIconVisibleInMenu(true);
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);

//    openAct = new QAction(tr("&Открыть файл конфигурации прибора"), this);
//    openAct->setShortcuts(QKeySequence::Open);
//    openAct->setStatusTip(tr("Открыть файл конфигурации прибора"));
//    openAct->setIcon(QIcon(":/img/document-open"));
//    openAct->setIconVisibleInMenu(true);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::open);

//    saveAct = new QAction(tr("&Сохранить файл конфигурации прибора"), this);
//    saveAct->setShortcuts(QKeySequence::Save);
//    saveAct->setStatusTip(tr("Сохранить файл конфигурации прибора"));
//    saveAct->setIcon(QIcon(":/img/document-save"));
//    saveAct->setIconVisibleInMenu(true);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::Save);

//    saveAsAct = new QAction(tr("&Сохранить файл конфигурации прибора как"), this);
//    saveAsAct->setShortcuts(QKeySequence::SaveAs);
//    saveAsAct->setStatusTip(tr("Сохранить файл конфигурации прибора как"));
//    saveAsAct->setIcon(QIcon(":/img/document-save-as"));
//    saveAsAct->setIconVisibleInMenu(true);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::SaveAs);

//    closeAct = new QAction(tr("&Закрыть файл конфигурации прибора"), this);
//    closeAct->setShortcuts(QKeySequence::Cancel);
//    closeAct->setStatusTip(tr("Закрыть файл конфигурации прибора"));
//    closeAct->setIcon(QIcon(":/img/document-close"));
//    closeAct->setIconVisibleInMenu(true);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeAllBase);

    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], &QAction::triggered, this, &MainWindow::openRecentFile);
    }

//    printSetupsAct = new QAction(tr("&Просмотр предварительной печати"), this);
//    printSetupsAct->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_P);
//    printSetupsAct->setStatusTip(tr("Просмотр предварительной печати"));
//    printSetupsAct->setIcon(QIcon(":/img/document-preview-archive"));
//    printSetupsAct->setIconVisibleInMenu(true);
    connect(ui->actionPage_Setup, &QAction::triggered, this, &MainWindow::pageSetup);

//    printAct = new QAction(tr("&Печать конфигурации прибора"), this);
//    printAct->setShortcuts(QKeySequence::Print);
//    printAct->setStatusTip(tr("Печать конфигурации прибора"));
//    printAct->setIcon(QIcon(":/img/document-print"));
//    printAct->setIconVisibleInMenu(true);
    connect(ui->actionprint, &QAction::triggered, this, &MainWindow::on_actionprint_triggered);

//    exitAct = new QAction(tr("&Выход"), this);
//    exitAct->setShortcuts(QKeySequence::Quit);
//    exitAct->setStatusTip(tr("Выход"));
//    printAct->setIcon(QIcon(":/img/document-print"));
//    printAct->setIconVisibleInMenu(true);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::closeApp);

//    addAct = new QAction(tr("&Добавить строку"), this);
//    addAct->setShortcut(Qt::SHIFT + Qt::Key_K);
//    addAct->setStatusTip(tr("Добавить строку"));
//    addAct->setIcon(QIcon(":/img/archive-insert"));
//    addAct->setIconVisibleInMenu(true);
    connect(ui->actionPLUS, &QAction::triggered, this, &MainWindow::addPage);

//    removeAct = new QAction(tr("&Удалить строку"), this);
//    removeAct->setShortcut(Qt::SHIFT + Qt::Key_L);
//    removeAct->setStatusTip(tr("Удалить строку"));
//    removeAct->setIcon(QIcon(":/img/archive-remove"));
//    removeAct->setIconVisibleInMenu(true);
    connect(ui->actionMINUS, &QAction::triggered, this, &MainWindow::removePage);

//    readAct = new QAction(tr("&Прочитать данные прибора"), this);
//    readAct->setShortcut(Qt::SHIFT + Qt::Key_R);
//    readAct->setStatusTip(tr("Прочитать данные прибора"));
//    readAct->setIcon(QIcon(":/img/document-import"));
//    readAct->setIconVisibleInMenu(true);
    connect(ui->actionRead, &QAction::triggered, this, &MainWindow::readPribor);

//    writhteAct = new QAction(tr("&Записать данные в прибор"), this);
//    writhteAct->setShortcut(Qt::SHIFT + Qt::Key_W);
//    writhteAct->setIcon(QIcon(":/img/document-export"));
//    writhteAct->setIconVisibleInMenu(true);
//    writhteAct->setStatusTip(tr("Записать данные в прибор"));
    connect(ui->actionSave_2, &QAction::triggered, this, &MainWindow::writhtePribor);

//    settingsAct = new QAction(tr("&Настройки"), this);
//    settingsAct->setShortcut(Qt::ALT + Qt::Key_F12);
//    settingsAct->setStatusTip(tr("Настройки"));
//    settingsAct->setIcon(QIcon(":/img/configure"));
//    settingsAct->setIconVisibleInMenu(true);
    connect(ui->actionNastr, &QAction::triggered, this, &MainWindow::settingsPage);

//    helpAct = new QAction(tr("&Руководство пользователя"), this);
//    helpAct->setShortcuts(QKeySequence::HelpContents);
//    helpAct->setStatusTip(tr("Руководство пользователя"));
//    helpAct->setIcon(QIcon(":/img/system-help"));
//    helpAct->setIconVisibleInMenu(true);
    connect(ui->actionNastr, &QAction::triggered, this, &MainWindow::helpKonf);

//    konfiguretorAct = new QAction(tr("&О программе"), this);
//    konfiguretorAct->setStatusTip(tr("О программе"));
//    konfiguretorAct->setIcon(QIcon(":/img/IM_24_blue"));
//    konfiguretorAct->setIconVisibleInMenu(true);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::aboutKonf);
}

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
   if (action)
   loadFile(action->data().toString());
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings("BRU", "konfiguretor");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings("BRU", "konfiguretor");
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::onCheckBoxHeaderClick1()
{
    if(headerr->isChecked1())
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,1), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

void MainWindow::onCheckBoxHeaderClick2()
{
    if(headerr->isChecked2())
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Checked, Qt::CheckStateRole);
        }
    }
    else
    {
        for (int i=0; i<64; i++ )
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(i,2), Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}


void MainWindow::loadFile(const QString &fileName)
{
    //QString filter = "Файл конфигурации прибора (*.db);;All files (*.*)";
    //fileName = QFileDialog::getOpenFileName(this, "Выбрать файл конфигурации прибора", QDir::homePath(), filter);

     setWindowTitle(fileName + QString(" - IM View"));
    //инициализация базы данных sqlite3
     sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
     sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных
     model = new Model; //создание модели QSqlTableModel
     model->setTable("Net settings"); //Установка для таблицы базы данных, с которой работает модель, tableName
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //Все изменения будут кэшироваться в модели до тех пор, пока не будет вызван сигнал submitAll()

     //подключение заголовка таблицы
     //headerr = new CheckBoxHeader(Qt::Horizontal,ui->tableView);  //создание заголовка tableview
     //ui->tableView->setHorizontalHeader(headerr); //установка заголовка tableview и checkbox в первый столбец
     //connect(headerr, &CheckBoxHeader::checkBoxClicked1, this, &MainWindow::onCheckBoxHeaderClick1); //подключение головного чекбокса к чекбоксам в первом столбце
     //connect(headerr, &CheckBoxHeader::checkBoxClicked2, this, &MainWindow::onCheckBoxHeaderClick2); //подключение головного чекбокса к чекбоксам в первом столбце

     //загрузка данных в таблицу tableview
     model->select(); //Заполняет модель данными из таблицы, которая была установлена ​​с помощью setTable(), используя указанный фильтр и условие сортировки
     ui->tableView->setModel(model); //Устанавливает модель для представления
     ui->tableView->hideColumn(1); //скрытие столбца id

     //настройки таблицы tableview
     ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked); //Редактирование начинается при двойном щелчке по элементу
     ui->tableView->setSelectionMode(QAbstractItemView :: SingleSelection); //нет выделения ячеек
  //  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
     ui->tableView->resizeColumnsToContents(); //Изменяет размер всех столбцов на основе подсказок размера делегата, используемого для визуализации каждого элемента в столбцах

     QString currentTabText = ui->tabWidget->tabText(0);
     QFileInfo fi2(fileName);
     QString base2 = fi2.baseName();
     setWindowTitle(currentTabText + "@" + QString(base2) + QString(" - Konfiguretor"));

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);

     QFileInfo fi4(fileName);
     QString base4 = fi4.baseName();
     ui->label_2->setText(base4);
     ui->actionSave->setEnabled(true);
     ui->actionSaveAs->setEnabled(true);
     ui->actionClose->setEnabled(true);
     ui->actionprint->setEnabled(true);
     ui->actionPage_Setup->setEnabled(true);
     ui->actionRead->setEnabled(true);
     ui->actionSave_2->setEnabled(true);
     ui->actionPLUS->setEnabled(true);
     ui->actionMINUS->setEnabled(true);
     modifyMenu->setEnabled(true);
     priborMenu->setEnabled(true);
     currentTabText = ui->tabWidget->tabText(0);
     QFileInfo fi3(fileName);
     QString base3 = fi3.baseName();
     setWindowTitle(currentTabText + "@" + QString(base3) + QString(" - Konfiguretor"));
     connect(ui->tableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

void MainWindow::closeAllBase()
{
    sdb.close();
    QSqlDatabase::removeDatabase(fileName);
    model->clear();

    ui->label_2->setText("Загрузите файл конфигурации прибора");
    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));

    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionprint->setEnabled(false);
    ui->actionPage_Setup->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->actionSave_2->setEnabled(false);
    ui->actionPLUS->setEnabled(false);
    ui->actionMINUS->setEnabled(false);
    modifyMenu->setEnabled(false);
    priborMenu->setEnabled(false);
}

void MainWindow::newFile()
{
    QString first="netdb_base.db";
    QString filter = "Файл конфигурации прибора (*.db);;Все файлы (*.*)";
    fileName = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", QDir::homePath(), filter);
    QFile::copy(first,fileName);

    int index = ui->tabWidget->currentIndex();
    QString currentTabText = ui->tabWidget->tabText(index);
    QFileInfo fi(fileName);
    QString base = fi.baseName();
    setWindowTitle(currentTabText + "@" + base + QString(" - IM View"));

    //инициализация базы данных sqlite3
     sdb = QSqlDatabase::addDatabase("QSQLITE"); //объявление базы данных sqlite3
     sdb.setDatabaseName(QFileInfo(fileName).absoluteFilePath()); //подключение к базе данных
     model = new Model; //создание модели QSqlTableModel
     model->setTable("Net settings"); //Установка для таблицы базы данных, с которой работает модель, tableName
     model->setEditStrategy(QSqlTableModel::OnManualSubmit); //Все изменения будут кэшироваться в модели до тех пор, пока не будет вызван сигнал submitAll()

     //подключение заголовка таблицы
//     headerr = new CheckBoxHeader(Qt::Horizontal,ui->tableView);  //создание заголовка tableview
//     ui->tableView->setHorizontalHeader(headerr); //установка заголовка tableview и checkbox в первый столбец
//     //connect(headerr, &CheckBoxHeader::checkBoxClicked1, this, &MainWindow::onCheckBoxHeaderClick1); //подключение головного чекбокса к чекбоксам в первом столбце
//     //connect(headerr, &CheckBoxHeader::checkBoxClicked2, this, &MainWindow::onCheckBoxHeaderClick2); //подключение головного чекбокса к чекбоксам в первом столбце

     //загрузка данных в таблицу tableview
     model->select(); //Заполняет модель данными из таблицы, которая была установлена ​​с помощью setTable(), используя указанный фильтр и условие сортировки
     ui->tableView->setModel(model); //Устанавливает модель для представления
     ui->tableView->hideColumn(1); //скрытие столбца id
     QFileInfo fi3(fileName);
     QString base3 = fi3.baseName();
     ui->label_2->setText(base3);

     ui->actionSave->setEnabled(true);
     ui->actionSaveAs->setEnabled(true);
     ui->actionClose->setEnabled(true);
     ui->actionprint->setEnabled(true);
     ui->actionPage_Setup->setEnabled(true);
     ui->actionRead->setEnabled(true);
     ui->actionSave_2->setEnabled(true);
     ui->actionPLUS->setEnabled(true);
     ui->actionMINUS->setEnabled(true);
     modifyMenu->setEnabled(true);
     priborMenu->setEnabled(true);
     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::Save()
{
    model->database().transaction();
    if(model->submitAll())
    model->database().commit();
    else
    {
        model->database().rollback();
    }
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));

    isChanged = false;
}

void MainWindow::SaveAs()
{

}

void MainWindow::addPage()
{
    model->insertRow(model->rowCount());
}

void MainWindow::removePage()
{
    int selectRow = ui->tableView->currentIndex().row();
    if (selectRow >=0)
    {
        model->removeRow(selectRow);
    }
}

void MainWindow::on_action_11_triggered()
{
    close();
}

void MainWindow::on_actionprint_triggered()
{
    QPrinter printer;
    printTable(&printer, false);
}

void MainWindow::on_action_13_triggered()
{
    addPage();
}

void MainWindow::on_action_6_triggered()
{

}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
    if(sdb.isOpen())
    {
        QFileInfo fi5(fileName);
        QString base5 = fi5.baseName();
        ui->label_2->setText(base5);
   //     ui->label_2->setStyleSheet(" QLabel {font-family: 'Open Sans', sans-serif;"
   //                                " font: 12px;"
   //                                " color: black;"
   //                                " font-weight: 600;}");
        QString currentTabText = ui->tabWidget->tabText(index);
        setWindowTitle(currentTabText + "@" + QString(base5) + QString(" - Konfiguretor"));
    }
}

void MainWindow::on_action_triggered()
{
    newFile();
}

void MainWindow::on_action_5_triggered()
{

}

void MainWindow::on_action_9_triggered()
{

}

void MainWindow::on_action_10_triggered()
{

}

void MainWindow::pageSetup()
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QPrintPreviewDialog *printPreview = new QPrintPreviewDialog(printer);
    connect(printPreview, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printPreview(QPrinter*)));
    printPreview->setWindowTitle("Preview Dialog");
    Qt::WindowFlags flags(Qt::WindowTitleHint);
    printPreview->setWindowFlags(flags);
    printPreview->showMaximized();
    printPreview->exec();
}

void MainWindow::printPreview(QPrinter *printer)
{
    printTable(printer, true);
}

void MainWindow::on_action_7_triggered()
{
    removePage();
}

void MainWindow::printTable(QPrinter *printer, bool isPreview)
{
    printer->setPageSize(QPageSize(QPageSize::A4));
    printer->setPageOrientation(QPageLayout::Landscape);
    printer->setFullPage(true);

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg(fileName)
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"
            "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());

    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView->isColumnHidden(column))
                {
                    QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
    out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

    QTextDocument document;
    document.setHtml(strStream);

    if (isPreview)
    {
        document.print(printer);
    }
    else
    {
        QPrintDialog dialog(printer, NULL);
        if (dialog.exec() == QDialog::Accepted) {
            document.print(printer);
        }
    }
}

void MainWindow::readPribor()
{

}

void MainWindow::writhtePribor()
{

}

void MainWindow::settingsPage()
{

}

void MainWindow::helpKonf()
{

}

void MainWindow::aboutKonf()
{

}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionLoad_triggered()
{

}

void MainWindow::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
{
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor") + QString("*"));
    isChanged = true;
}

void MainWindow::closeApp()
{

}

void MainWindow::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    if(isChanged)
    {
        switch (QMessageBox::question(this, "Close Confirmation", "Сохранить?", QMessageBox::Yes | QMessageBox::No |  QMessageBox::Cancel))
        {
        case QMessageBox::Yes:
            Save();
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        case QMessageBox::No:
            event->accept();
        }
    }
    else
    {
        event->accept();
    }
}
