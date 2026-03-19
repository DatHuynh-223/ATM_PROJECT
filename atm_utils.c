// Tiện ích và nhâp xuất
#include "atm_types.h"
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
node input(node root)
{
    FILE *f = fopen("input.txt", "r");

    if (f == NULL)
    {
        printf("Không thể đọc file");
        return root;
    }

    //tạo tmp1 lưu account number
    char tmp1[MAX_ACC_LEN];

    //tạo tmp2 lưu pin
    char tmp2[MAX_PIN_LEN];

    //tạo tmp3 lưu balance
    unsigned long long tmp3;


    // Khi fscanf không nhận được giá trị nào thõa nên trả về -1
    // Nếu đọc thành công sẽ trả về 1 nhưng có 3 phần tử sẽ trả về 3
    while (fscanf(f, "%20s %10s %llu", tmp1, tmp2, &tmp3) == 3) 
    {
        Account temp = append_account(tmp1, tmp2, tmp3);
        root = CreateTree(root,CreateNode(temp));
    }
    return root;
}
