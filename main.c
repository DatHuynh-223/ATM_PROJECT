#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> //thư viện hỗ trợ tiếng việt cho terminal

#define MAX_ACC_LEN 21 //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_PIN_LEN 11 //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_DAILY_TRANSACTION 10 //tùy vào ý của thầy cô
#define MAX_TRASACTION_LEN 51 // giới hạn độ dài tin nhắn mỗi giao dịch (dư 1 kí \0)



typedef struct Account
{
    char AccountNumber[MAX_ACC_LEN];
    char Pin[MAX_PIN_LEN];
    unsigned long long Balance;
    int TransactionCount;
    char TransactionHistory[MAX_TRASACTION_LEN];
} *Account;


typedef struct TreeNode
{
    struct Account *Data;
    struct TreeNode *left;
    struct TreeNode *right;
} *node;



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

node CreateNode (Account d)
{
    // hàm malloc để cấp phát bộ nhớ heap, (node) để ép kểu, sizeof(struct TreeNode) kích thước xin cấp
    node temp = (node)malloc(sizeof(struct TreeNode));
    temp -> Data = d;
    temp -> left = NULL;
    temp -> right = NULL; 
    return temp;
}

node CreateTree (node root, node a)
{
    //Điểm dừng của quá trình đệ quy
    if (root ==  NULL) 
    {
        return a;
    }

    //dùng hàm strcmp để so sánh 2 xâu account number, str1 > str2 thì compare =1
    int compare = strcmp(a-> Data->AccountNumber, root -> Data -> AccountNumber);


    if (compare ==1) root -> right = CreateTree((*root).right, a);
    
    else if (compare == -1) root -> left = CreateTree(root -> left,a);
    
    else printf("Lỗi trùng lặp số tài khoản %s\n", a-> Data ->AccountNumber);

    //trả về root ban đầu
    return root;
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

long long  chonsotiengui(node target, node myAccount)
{
    //Chọn hạn mức tối đa
    long long hanmuctoida;
    if (target == myAccount) hanmuctoida = 200000000;
    else hanmuctoida = 100000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    printf("Chọn số tiền bạn muốn gửi: \n");
    printf("CHỈ NHẬN MỆNH GIÁ 50.000 đồng, 100.000 đồng, 200.000 đồng, 500.000 đồng\n\n");
    
    //In menu số tiền được chọn
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay về menu        ", i);
        else if (i == 7) printf("%d. Số khác\n\n", i);
        else
        {
            printf("%d. %lld đồng       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }
    
    
    
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld đồng\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp = 0;
        while (temp % 50000 != 0 || temp > hanmuctoida)
        {
            if (tempEntry == 0)
            {
                "*** QUÁ SÔ LẦN NHẬP ***\n\n";
                return 0;
            }

            printf("Vui lòng nhập bội số của 50.000 đồng (Bạn có %d lần nhập): ", tempEntry);
            scanf(" %lld", &temp);
            tempEntry -= 1;
        }
    }
}

void guitien(node root, node myAccount)
{
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    while (yesno == 'Y' && AccountEntryCount > 0)
    {
        printf("Nhập số tài khoản bạn muốn gửi tiền (Bạn có %d lần nhập): ", AccountEntryCount);
        scanf(" %s", account);
        AccountEntryCount -= 1;


        node temp = findNode(root, account);
        if (temp != NULL)
        {
            chonsotiengui(temp, myAccount);
        }
        else
        {
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
        }
    }
    printf("*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN ***\n\n");
}

void menu(node root, node myAccount)
{
    int option = 0;
    printf("1. Gửi tiền\n\n");
    scanf(" %d" , &option);
    if (option == 1) 
    {
        printf("Gửi tiền");
        guitien(root, myAccount);
    }
}

void dangnhap(node root)
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 2;

    while (yesno == 'Y' && loginCount > 0)
    {
        //nhập account
        printf("Vui lòng nhập Số tài khoản của bạn (Bạn còn %d lần nhập tài khoản): ", loginCount);
        loginCount -= 1;
        scanf(" %s", target);
        
        
        node temp = findNode(root, target);

        //kiểm tra có tìm ra tài khoản hay không
        if (temp != NULL)
        {
            //Nhập pin
            char mapin[MAX_PIN_LEN] "";
            int pinEntryCount = 3;
            while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0) 
            {
                printf("Vui lòng nhập lại mã Pin (Bạn còn %d lần nhập)): ", pinEntryCount);
                scanf(" %s",mapin);
                pinEntryCount-=1;
            }


            //Kiểm tra mã pin
            if (strcmp(temp ->Data -> Pin, mapin) ==0) 
            {
                //Kiểm tra số lần giao dịch trong ngày
                if (temp-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                {
                    printf("*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                    return;
                }
                printf("Vào menu\n\n");
                menu(root, temp);
                return;
            }

            //Kiểm tra số lần nhập
            if (pinEntryCount == 0) 
            {
                printf("HẾT SỐ LẦN NHẬP MÃ PIN\n\n");
                return;
            }
            
        }
        else
        {
            //Nhập lại số tài khoản
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
        }
    }
    if (loginCount == 0) printf("** QUÁ SỐ LẦN NHẬP TÀI KHOẢN **\n\n");
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    node root = NULL;
    root = input(root);
    printf("======================================================\n\n");
    printf("* CHÀO MỪNG QUÝ KHÁCH ĐẾN VỚI NGÂN HÀNG ĐẠT KHÔNG CHÍN*\n\n");
    printf("======================================================\n\n");
    dangnhap(root);
    printf("Kết thúc chương trình");
}