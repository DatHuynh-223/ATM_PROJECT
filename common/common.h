#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h> // Cần cho hàm kiểm tra số isdigit()

// 2. Các hằng số cấu hình hệ thống (Dễ dàng thay đổi sau này)
#define MAX_ACC_LEN 21           //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_PIN_LEN 11          //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_DAILY_TRANSACTION 10 //tùy vào ý của thầy cô
#define MAX_TRANSACTION_LEN 51    // giới hạn độ dài tin nhắn mỗi giao dịch (dư 1 kí \0)
#define INFORM_LEN 201           //Thõa được số lượng từ trong message
#define GIAODICHPHIEN 100        // Tổng giao dịch trong một phiên làm việc của ATM


extern char TransactionList[GIAODICHPHIEN][INFORM_LEN];
extern int admin_index;

#endif