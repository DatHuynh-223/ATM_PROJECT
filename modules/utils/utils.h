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

int tinhOffset(const char *s);

void cr_file(char *filename);
char * today();
void them_cach(const char* r, char* s);  

void man_hinh_chao_mung();

void nhap_mk(char *pw,int n);

void display_about();
void in_tg(int sec);
#endif