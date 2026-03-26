#include "utils.h"

//Hàm xóa bộ nhớ đệm khi người dùng nhập dư kí tự
int clear_buffer()
{
    //c là int vì EOF là -1
    int c;
    int temp = 0;

    while ((c = getchar()) != '\n' && c != EOF )
    {
        temp = 1;
    }
    return temp;
}

// Hàm kiểm tra xem chuỗi có bị lẫn chữ cái/kí tự đặc biệt không
int la_chuoi_so_hop_le(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; // Trả về 0 (False) nếu phát hiện bất kì thứ gì không phải số từ 0-9
        }
    }
    return 1; // Hợp lệ
}