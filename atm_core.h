#ifndef ATM_CORE_H
#define ATM_CORE_H

// 1. Nạp các thư viện chuẩn
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

// 2. Các hằng số (#define)
#define MAX_ACC_LEN 21
#define MAX_PIN_LEN 11
#define MAX_DAILY_TRANSACTION 10
#define MAX_TRASACTION_LEN 51
#define INFORM_LEN 175
#define GIAODICHPHIEN 100

// 3. Xử lý Biến toàn cục (Rất quan trọng)
// Phải dùng chữ 'extern' để báo cho compiler biết biến này sẽ được định nghĩa ở file .c
extern char TransactionList[GIAODICHPHIEN][INFORM_LEN];
extern int admin_index;

// 4. Các cấu trúc dữ liệu (struct)
typedef struct Account {
    char AccountNumber[MAX_ACC_LEN];
    char Pin[MAX_PIN_LEN];
    unsigned long long Balance;
    int TransactionCount;
    char TransactionHistory[MAX_TRASACTION_LEN][INFORM_LEN];
} *Account;

typedef struct TreeNode {
    struct Account *Data;
    struct TreeNode *left;
    struct TreeNode *right;
} *node;    

// 5. Khai báo nguyên mẫu hàm (Chỉ lấy dòng tên hàm và thêm dấu chấm phẩy)
int clear_buffer();
Account append_account(char *AN, char *PI, unsigned long long BL);
node CreateNode (Account d);
node CreateTree (node root, node a);
node input(node root);
node findNode(node root, char *target);
long long chonsotiengui(node target, node myAccount);
void guitien(node root, node myAccount);
long long chonsotienchuyen();
void chuyentien(node root, node myAccount);
long long chonsotienrut();
void ruttien(node root, node myAccount);
void xemtaikhoan(node myAccount);
void menu(node root, node myAccount);
void GuestLogin(node root);
void AdministratorLogin(char *shutdown);
void khoidong(node root);

#endif
