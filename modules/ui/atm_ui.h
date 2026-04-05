#ifndef ATM_UI_H
#define ATM_UI_H

#include "../../common/common.h"
#include "../accounts/account_manager.h"
#include "../transactions/transactions.h"
#include "../utils/utils.h"

// Menu chính sau khi đăng nhập thành công
void menu(node root, node myAccount);

// Xử lý đăng nhập cho khách hàng (G - Guest)
void GuestLogin(node root,char *shutdown);

// Xử lý đăng nhập cho quản trị viên (A - Admin)
void AdministratorLogin(char *shutdown);

// Hàm khởi động, hiển thị lời chào và chọn vai trò
void khoidong(node root);

#endif