#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <cstring>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // cấu hình bảng hiển thị
    ui->tblMonHoc->setColumnCount(4);
    QStringList headers = {"Mã MH", "Tên MH", "STCLT", "STCTH"};
    ui->tblMonHoc->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnThemMH_clicked() {
    MonHoc mh;

    QString mamh = ui->edtMaMH->text();
    QString tenmh = ui->edtTenMH->text();

    if (mamh.isEmpty() || tenmh.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập đầy đủ thông tin.");
        return;
    }

    std::strncpy(mh.MAMH, mamh.toStdString().c_str(), 10);
    mh.MAMH[10] = '\0';
    std::strncpy(mh.TENMH, tenmh.toStdString().c_str(), 50);
    mh.TENMH[50] = '\0';
    mh.STCLT = ui->spnSTCLT->value();
    mh.STCTH = ui->spnSTCTH->value();
    mh.height = 1;

    dsMonHoc.insert(mh);
    loadTableMonHoc();
    QMessageBox::information(this, "Thành công", "Đã thêm môn học!");
}

void MainWindow::loadTableMonHoc() {
    auto list = dsMonHoc.getAllSortedByName();
    ui->tblMonHoc->setRowCount(list.size());

    for (int i = 0; i < list.size(); ++i) {
        const MonHoc &mh = list[i];
        ui->tblMonHoc->setItem(i, 0, new QTableWidgetItem(mh.MAMH));
        ui->tblMonHoc->setItem(i, 1, new QTableWidgetItem(mh.TENMH));
        ui->tblMonHoc->setItem(i, 2, new QTableWidgetItem(QString::number(mh.STCLT)));
        ui->tblMonHoc->setItem(i, 3, new QTableWidgetItem(QString::number(mh.STCTH)));
    }
}

void MainWindow::on_btnXoaMH_clicked() {
    QString mamh = ui->edtMaMH->text();
    if (mamh.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã môn học cần xóa.");
        return;
    }

    dsMonHoc.remove(mamh.toStdString().c_str());
    loadTableMonHoc();
    QMessageBox::information(this, "Thành công", "Đã xóa môn học!");
}
