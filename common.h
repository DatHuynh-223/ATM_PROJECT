#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h> // Cần cho hàm kiểm tra số isdigit()

// 2. Các hằng số cấu hình hệ thống (Dễ dàng thay đổi sau này)
#define MAX_ACC_LEN 21           // Độ dài STK tối đa
#define MAX_PIN_LEN 11           // Độ dài mã PIN tối đa
#define MAX_DAILY_TRANSACTION 10 // Số giao dịch tối đa/ngày
#define MAX_TRASACTION_LEN 51    // Giới hạn số lượng giao dịch trong lịch sử
#define INFORM_LEN 175           // Độ dài tối đa của một dòng thông tin giao dịch
#define GIAODICHPHIEN 100        // Tổng giao dịch trong một phiên làm việc của ATM

// 3. Khai báo biến toàn cục (Sử dụng từ khóa extern)
// 'extern' báo cho trình biên dịch biết biến này tồn tại ở đâu đó, 
// giúp các file khác nhau có thể dùng chung một danh sách giao dịch.
extern char TransactionList[GIAODICHPHIEN][INFORM_LEN];
extern int admin_index;

#endif