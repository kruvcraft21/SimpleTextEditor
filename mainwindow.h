#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QSettings>
#include <string>
#include "search.h"
#include "replace.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

constexpr auto SETTINGS_GROUP_VIEW = "testKey";
constexpr auto SETTING_SHOW_TOOLBAR = "isShowToolBar";
constexpr auto SETTING_SHOW_STATUS_BAR = "isShowStatusBar";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotNew();
    void slotOpen();
    void slotSave();
    void slotAboutProgram();
    void slotSearch(const QString& exp);
    void slotReplace(const QString& exp, const QString& rep);
    void slotIsSaved();

private:
    QFile mFile;
    QString mFileName;

private:
    void updateTitle();
    bool askForFileSaveAndClose();
    void closeEvent(QCloseEvent *ev) override;
private:
    Ui::MainWindow *ui;
    Search *searchButton;
    Replace *replaceButton;
};
#endif // MAINWINDOW_H
