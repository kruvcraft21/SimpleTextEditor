#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , searchButton(new Search(this))
    , replaceButton(new Replace(this))
{
    ui->setupUi(this);

    connect(ui->action_New, &QAction::triggered, this, &MainWindow::slotNew, Qt::UniqueConnection);
    connect(ui->action_Open, &QAction::triggered, this, &MainWindow::slotOpen, Qt::UniqueConnection);
    connect(ui->action_Save, &QAction::triggered, this, &MainWindow::slotSave, Qt::UniqueConnection);
    connect(ui->action_About_program, &QAction::triggered, this, &MainWindow::slotAboutProgram, Qt::UniqueConnection);
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt, Qt::UniqueConnection);
    connect(ui->actionSearch, &QAction::triggered, searchButton, &Search::showSearch, Qt::UniqueConnection);
    connect(ui->actionReplace, &QAction::triggered, replaceButton, &Replace::showReplace, Qt::UniqueConnection);
    connect(searchButton, &Search::accepted, this, &MainWindow::slotSearch);
    connect(replaceButton, &Replace::accepted, this, &MainWindow::slotReplace);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::slotIsSaved);
    setWindowModified(false);
    slotNew();
}

void MainWindow::closeEvent(QCloseEvent* ev) {
    if (!askForFileSaveAndClose()) {
        ev->ignore();
    }
}

void MainWindow::slotIsSaved() {
    setWindowModified(true);
}

void MainWindow::slotReplace(const QString& exp, const QString& rep) {
    if (ui->plainTextEdit->find(exp)) {
        auto cursor = ui->plainTextEdit->textCursor();
        if (cursor.hasSelection()) {
            cursor.removeSelectedText();
            cursor.insertText(rep);
        }
    }
}

void MainWindow::slotSearch(const QString& exp) {
    ui->plainTextEdit->find(exp);
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, "About", "TextEditor for simple edits");
}

void MainWindow::updateTitle()
{
    setWindowTitle(QString("TextEditor - %1[*]").arg(mFileName));
}

void MainWindow::slotNew()
{
    if (!askForFileSaveAndClose()) {
        return;
    }
    mFileName = "";
    ui->plainTextEdit->clear();
    setWindowModified(false);
    updateTitle();
}

void MainWindow::slotOpen()
{
    if (!askForFileSaveAndClose())
    {
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open file ...", QDir::homePath(),
                                                    "Text files (*.txt);;All files(*.*)");
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        mFileName = fileName;
        ui->plainTextEdit->setPlainText(file.readAll());
        file.close();
        setWindowModified(false);
        updateTitle();
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for reading").arg(file.fileName()),
                             QMessageBox::Ok);
    }
}

void MainWindow::slotSave()
{
    QString fileName = mFileName[0] != '\0' ? mFileName : QFileDialog::getSaveFileName(this, "Open file ...", QDir::homePath(),
                                                    "Text files (*.txt);;All files(*.*)");
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        mFileName = fileName;
        QByteArray data;
        data.append(ui->plainTextEdit->toPlainText());
        file.write(data);
        file.close();
        setWindowModified(false);
        updateTitle();
    }
    else
    {
        QMessageBox::warning(this, "Error",
                             QString("Could not open file %1 for writing").arg(file.fileName()),
                             QMessageBox::Ok);
    }
}

bool MainWindow::askForFileSaveAndClose()
{
    if (isWindowModified())
    {
        int result = QMessageBox::question(this, "Save changes",
                                           QString(
                                               "File %1 is modified. Do you want to save your changes ?")
                                           .arg(mFileName),
                                           QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
        if (result == QMessageBox::Yes)
        {
            slotSave();
        }
        else if (result == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

