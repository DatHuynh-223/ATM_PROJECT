#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H
 
#include "common.h"
#include "utils.h"

// Định nghĩa cấu trúc dữ liệu Tài khoản
typedef struct Account
{
    char AccountNumber[MAX_ACC_LEN];
    char Pin[MAX_PIN_LEN];
    unsigned long long Balance;
    int TransactionCount;
    char TransactionHistory[MAX_TRASACTION_LEN][INFORM_LEN];
} *Account;
// Định nghĩa cấu trúc dữ liệu Node của cây nhị phân tìm kiếm
typedef struct TreeNode
{
    struct Account *Data;
    struct TreeNode *left;
    struct TreeNode *right;
} *node;   

//Các hàm quản lí tài khoản

//Hàm thêm chỉ số vào Account
Account append_account(char *AN, char *PI, unsigned long long BL);

//Hàm thêm nhánh vào Tree
node CreateNode (Account d);

//Hàm tạo Tree từ nhánh
node CreateTree (node root, node a);

//Hàm đọc file
node input(node root);

//Hàm tìm kiếm Node trong Tree
node findNode(node root, char *target);

#endif