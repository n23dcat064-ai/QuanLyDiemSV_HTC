#ifndef MONHOC_H
#define MONHOC_H

struct MonHoc {
    char MAMH[11]; // Mã môn học
    char TENMH[51]; //Tên môn học
    int STCLT; // Số tín chỉ lý thuyết
    int STCTH; // Số tín chỉ thực hành
    int height; // chiều cao (dùng cho AVL)

};

struct nodeMH {
    MonHoc mh;
    nodeMH *left;
    nodeMH *right;
};

typedef nodeMH* TreeMH;


#endif // MONHOC_H
