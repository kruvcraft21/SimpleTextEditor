#pragma once

#include <QDialog>
#include <QDialogButtonBox>

namespace Ui {
class Replace;
}

class Replace : public QDialog
{
    Q_OBJECT

public:
    explicit Replace(QWidget *parent = nullptr);
    ~Replace();

signals:
    void accepted(const QString& exp, const QString& rep);

private slots:
    void accept();

public slots:
    void showReplace();

private:
    Ui::Replace *ui;
};

