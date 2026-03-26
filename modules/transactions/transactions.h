#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "../../common/common.h"
#include "../accounts/account_manager.h"
#include "../utils/utils.h"

// Các hàm hỗ trợ chọn số tiền
long long chonsotiengui(node target, node myAccount);
long long chonsotienchuyen();
long long chonsotienrut();

// Các hàm thực thi giao dịch chính
void guitien(node root, node myAccount);
void chuyentien(node root, node myAccount);
void ruttien(node root, node myAccount);
void xemtaikhoan(node myAccount);

#endif