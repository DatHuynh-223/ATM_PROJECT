#include "common/common.h"
#include "modules/accounts/account_manager.h"
#include "modules/ui/atm_ui.h"
/* 
------RUN CODE------
gcc main.c modules/accounts/account_manager.c modules/transactions/transactions.c utils/utils.c -o atm.exe
./atm.exe

------CHỨC NĂNG CÁC MODULE------
common           :Chứa các hằng số (#define), thư viện hệ thống và khai báo biến dùng chung cho toàn dự án.
utils            :Chứa các hàm tiện ích như xóa bộ nhớ đệm và kiểm tra tính hợp lệ của chuỗi số.
account_manager  : Chứa các hàm quản lý tài khoản như tạo tài khoản, xây dựng cây nhị phân và đọc dữ liệu từ file.
transactions     : Chứa các hàm thực thi giao dịch như gửi tiền, chuyển tiền, rút tiền và xem tài khoản.
atm_ui           : Chứa các hàm giao diện người dùng như menu chính, xử lý đăng nhập và khởi động hệ thống.

*/

// Khởi tạo biến toàn cục
char TransactionList[GIAODICHPHIEN][INFORM_LEN];
int admin_index = 0;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    node root=NULL;
    root=input(root);
    if (root != NULL)
    {
        khoidong(root);
    }
    else{
        printf("\n[CẢNH CÁO ] Hệ thống không có dữ liệu tài khoản để hoạt động.\n");
        printf("Vui lòng kiểm tra file 'input.txt'!\n");
    }
    return 0;

}