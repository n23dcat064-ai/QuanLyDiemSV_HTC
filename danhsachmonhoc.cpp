#include "danhsachmonhoc.h"
#include <cstring>
#include <algorithm>
#include <iostream>

DanhSachMonHoc::DanhSachMonHoc() : root(nullptr) {}
DanhSachMonHoc::~DanhSachMonHoc() { clear(root); }

void DanhSachMonHoc::clear(TreeMH node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

int DanhSachMonHoc::height(TreeMH node) {
    return node ? node->mh.height : 0;
}

int DanhSachMonHoc::getBalance(TreeMH node) {
    return node ? height(node->left) - height(node->right) : 0;
}

TreeMH DanhSachMonHoc::rotateRight(TreeMH y) {
    TreeMH x = y->left;
    TreeMH T2 = x->right;

    x->right = y;
    y->left = T2;

    y->mh.height = std::max(height(y->left), height(y->right)) + 1;
    x->mh.height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

TreeMH DanhSachMonHoc::rotateLeft(TreeMH x) {
    TreeMH y = x->right;
    TreeMH T2 = y->left;

    y->left = x;
    x->right = T2;

    x->mh.height = std::max(height(x->left), height(x->right)) + 1;
    y->mh.height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

TreeMH DanhSachMonHoc::insertNode(TreeMH node, const MonHoc& mh) {
    if (!node) {
        TreeMH nn = new nodeMH;
        nn->mh = mh;
        nn->left = nn->right = nullptr;
        nn->mh.height = 1;
        return nn;
    }

    if (std::strcmp(mh.MAMH, node->mh.MAMH) < 0)
        node->left = insertNode(node->left, mh);
    else if (std::strcmp(mh.MAMH, node->mh.MAMH) > 0)
        node->right = insertNode(node->right, mh);
    else
        return node; // trùng mã -> bỏ qua

    node->mh.height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && std::strcmp(mh.MAMH, node->left->mh.MAMH) < 0)
        return rotateRight(node);

    if (balance < -1 && std::strcmp(mh.MAMH, node->right->mh.MAMH) > 0)
        return rotateLeft(node);

    if (balance > 1 && std::strcmp(mh.MAMH, node->left->mh.MAMH) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && std::strcmp(mh.MAMH, node->right->mh.MAMH) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void DanhSachMonHoc::insert(const MonHoc& mh) {
    root = insertNode(root, mh);
}

TreeMH DanhSachMonHoc::minValueNode(TreeMH node) {
    TreeMH current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

TreeMH DanhSachMonHoc::deleteNode(TreeMH node, const char maMH[]) {
    if (!node) return node;

    if (std::strcmp(maMH, node->mh.MAMH) < 0)
        node->left = deleteNode(node->left, maMH);
    else if (std::strcmp(maMH, node->mh.MAMH) > 0)
        node->right = deleteNode(node->right, maMH);
    else {
        if (!node->left || !node->right) {
            TreeMH temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            TreeMH temp = minValueNode(node->right);
            node->mh = temp->mh;
            node->right = deleteNode(node->right, temp->mh.MAMH);
        }
    }

    if (!node) return node;

    node->mh.height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
        return rotateRight(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
        return rotateLeft(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void DanhSachMonHoc::remove(const char maMH[]) {
    root = deleteNode(root, maMH);
}

TreeMH DanhSachMonHoc::searchNode(TreeMH node, const char maMH[]) {
    if (!node) return nullptr;
    int cmp = std::strcmp(maMH, node->mh.MAMH);
    if (cmp == 0) return node;
    if (cmp < 0) return searchNode(node->left, maMH);
    return searchNode(node->right, maMH);
}

MonHoc* DanhSachMonHoc::find(const char maMH[]) {
    TreeMH p = searchNode(root, maMH);
    return p ? &p->mh : nullptr;
}

void DanhSachMonHoc::inorderCollect(TreeMH node, std::vector<MonHoc>& out) {
    if (!node) return;
    inorderCollect(node->left, out);
    out.push_back(node->mh);
    inorderCollect(node->right, out);
}

std::vector<MonHoc> DanhSachMonHoc::getAllSortedByName() {
    std::vector<MonHoc> arr;
    inorderCollect(root, arr);
    std::sort(arr.begin(), arr.end(), [](const MonHoc& a, const MonHoc& b) {
        return std::strcmp(a.TENMH, b.TENMH) < 0;
    });
    return arr;
}
