#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Search::accept);
}

Search::~Search()
{
    delete ui;
}

void Search::showSearch() {
    show();
}

void Search::accept() {
    QString exp = ui->lineEdit->text();
    if (exp.size() > 0) {
        emit accepted(exp);
    }

}
