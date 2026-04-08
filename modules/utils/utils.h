#ifndef UTILS_H
#define UTILS_H
#include "../../common/common.h"

//Xóa bộ nhớ đệm
int clear_buffer();

//Kiểm tra xem chuỗi có phải là chuỗi số hợp lệ hay không
int la_chuoi_so_hop_le(char*str);

// them mot ki tu vao vi tri pos

void insert(char *s,char ch ,int pos,int n);

//them dau cham trong tien 

char* insert_cham(long long n);

#endif