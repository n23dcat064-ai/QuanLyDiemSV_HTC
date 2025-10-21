#ifndef DANHSACHMONHOC_H
#define DANHSACHMONHOC_H

#include "monhoc.h"
#include <vector>

class DanhSachMonHoc {
private:
    TreeMH root;

    int height(TreeMH node);
    int getBalance(TreeMH node);
    TreeMH rotateLeft(TreeMH x);
    TreeMH rotateRight(TreeMH y);

    TreeMH insertNode(TreeMH node, const MonHoc& mh);
    TreeMH minValueNode(TreeMH node);
    TreeMH deleteNode(TreeMH node, const char maMH[]);
    TreeMH searchNode(TreeMH node, const char maMH[]);

    void inorderCollect(TreeMH node, std::vector<MonHoc>& out);
    void clear(TreeMH node);

public:
    DanhSachMonHoc();
    ~DanhSachMonHoc();

    void insert(const MonHoc& mh);
    void remove(const char maMH[]);
    MonHoc* find(const char maMH[]);
    std::vector<MonHoc> getAllSortedByName();
};

#endif // DANHSACHMONHOC_H
