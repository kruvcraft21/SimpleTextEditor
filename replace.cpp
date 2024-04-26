#include "replace.h"
#include "ui_replace.h"

Replace::Replace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Replace)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Replace::accept);
}

Replace::~Replace()
{
    delete ui;
}

void Replace::accept() {
    QString exp = ui->findLine->text();
    QString rep = ui->replaceLine->text();
    if (exp.size() > 0) {
        emit accepted(exp, rep);
    }
}

void Replace::showReplace() {
    show();
}
