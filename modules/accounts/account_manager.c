#include "account_manager.h"

//Hàm thêm chỉ số vào Account
Account append_account(char *AN, char *PI, unsigned long long BL)
{
    Account temp = (Account)malloc(sizeof(struct Account));

    //dùng strcpy để copy xâu 2 qua xâu 1
    strcpy(temp -> AccountNumber,AN);
    strcpy(temp -> Pin, PI);
    temp -> Balance = BL;
    temp ->TransactionCount = 0;
    return temp;
}

//Hàm thêm nhánh vào Tree
node CreateNode (Account d)
{
    // hàm malloc để cấp phát bộ nhớ heap, (node) để ép kểu, sizeof(struct TreeNode) kích thước xin cấp
    node temp = (node)malloc(sizeof(struct TreeNode));
    temp -> Data = d;
    temp -> left = NULL;
    temp -> right = NULL; 
    return temp;
}

//Hàm tạo Tree từ nhánh
node CreateTree (node root, node a)
{
    //Điểm dừng của quá trình đệ quy
    if (root ==  NULL) 
    {
        return a;
    }

    //dùng hàm strcmp để so sánh 2 xâu account number, str1 > str2 thì compare =1
    int compare = strcmp(a-> Data->AccountNumber, root -> Data -> AccountNumber);


    if (compare >0) root -> right = CreateTree((*root).right, a);
    
    else if (compare <0) root -> left = CreateTree(root -> left,a);
    
    else 
    {
        printf("Lỗi trùng lặp số tài khoản %s\n", a-> Data ->AccountNumber);
        free(a->Data);
        free(a);
    }
    //trả về root ban đầu
    return root;
}

//Hàm đọc file
node input(node root)
{
    FILE *f = fopen("data/account.dat", "r");

    if (f == NULL)
    {
        printf("Không thể đọc file");
        return root;
    }

    // Buffer rộng rãi để chứa trọn vẹn 1 dòng từ file (kể cả người dùng gõ siêu dài)
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        char stk[50];
        char pin[20];
        char thong_tin_thua[50];
        unsigned long long balance;

        // Dùng sscanf để bóc tách dữ liệu từ buffer
        // %49s và %19s là khiên chống tràn: Nếu chuỗi dài 1000 kí tự, nó cũng chỉ cắt lấy 49 kí tự
        int so_luong_doc = sscanf(buffer, " %49s %19s %llu %49s", stk, pin, &balance, thong_tin_thua);

        // 1. Kiểm tra xem có đủ 3 thông tin không (Đề phòng dòng bị thiếu)
        if (so_luong_doc < 3 || so_luong_doc > 3) {
            continue; // Bỏ qua, sang dòng tiếp theo
        }


        // 2. Kiểm tra Số tài khoản và PIN có bị lẫn chữ cái không
        if (!la_chuoi_so_hop_le(stk) || !la_chuoi_so_hop_le(pin)) {
            continue; 
        }

        // 3. Kiểm tra độ dài (Ví dụ quy định STK không quá 14 số, PIN bằng 6 số)
        if (strlen(stk) > MAX_ACC_LEN-1 ||strlen(pin) > MAX_PIN_LEN-1) {
            continue;
        }

        // Tiến hành đưa vào Danh sách liên kết hoặc Cây nhị phân ở đây
        Account temp = append_account(stk, pin, balance);
        root = CreateTree(root,CreateNode(temp));
    }
    return root;
}

//Hàm tìm kiếm Node trong Tree
node findNode(node root, char *target)
{
    //Nếu root = NULL thì nghĩa là đã tìm hết Tree nhưng không tìm thấy
    if (root == NULL)
    {
        return NULL;
    }
    int compare = strcmp(target, root->Data->AccountNumber);
    if (compare == 0) return root;
    else if (compare == 1) return findNode(root -> right, target);
    else return findNode(root -> left, target);
}

//ghi du lieu vao file input
void ghiFile(node root ,FILE *f)
{
    if (root != NULL)
    {
        ghiFile(root -> left, f);
        fprintf(f, "%s %s %llu\n", root -> Data -> AccountNumber, root -> Data -> Pin, root -> Data -> Balance);
        ghiFile(root -> right, f);
    }
}

// cap nhat file input vao cuoi ngay
void update_File(node root)
{
    FILE *f = fopen("data/account.dat", "w");
    ghiFile(root, f);
    fclose(f);
    
}