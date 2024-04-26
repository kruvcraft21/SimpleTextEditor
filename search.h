#pragma once

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

private slots:
    void accept();

public slots:
    void showSearch();

signals:
    void accepted(const QString& exp);

private:
    Ui::Search *ui;
};

