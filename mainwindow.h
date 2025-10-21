#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "danhsachmonhoc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_btnThemMH_clicked();
    void on_btnXoaMH_clicked();
    void on_btnSuaMH_clicked();
    void loadTableMonHoc();

private:
    Ui::MainWindow *ui;
    DanhSachMonHoc dsMonHoc; // Cấu trúc dữ liệu lưu cây môn học
};
#endif // MAINWINDOW_H
