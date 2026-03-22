#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> //thư viện hỗ trợ tiếng việt cho terminal

#define MAX_ACC_LEN 21 //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_PIN_LEN 11 //có thể thay đổi nếu cần thiết (dư 1 kí \0)
#define MAX_DAILY_TRANSACTION 10 //tùy vào ý của thầy cô
#define MAX_TRASACTION_LEN 51 // giới hạn độ dài tin nhắn mỗi giao dịch (dư 1 kí \0)
#define INFORM_LEN 175 //Thõa được số lượng từ trong message
#define GIAODICHPHIEN 100
//Danh sách giao dịch của admin
char TransactionList[GIAODICHPHIEN][INFORM_LEN];
int admin_index = 0;

typedef struct Account
{
    char AccountNumber[MAX_ACC_LEN];
    char Pin[MAX_PIN_LEN];
    unsigned long long Balance;
    int TransactionCount;
    char TransactionHistory[MAX_TRASACTION_LEN][INFORM_LEN];
} *Account;


typedef struct TreeNode
{
    struct Account *Data;
    struct TreeNode *left;
    struct TreeNode *right;
} *node;    


//Hàm xóa bộ nhớ đệm khi người dùng nhập dư kí tự
int clear_buffer();

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

//Hàm chọn số tiền gửi đi
long long chonsotiengui(node target, node myAccount);

//Chức năng gửi tiền
void guitien(node root, node myAccount);

//Hàm chọn số tiền chuyển đi
long long chonsotienchuyen();

//Chức năng chuyển tiền
void chuyentien(node root, node myAccount);

//Hàm chọn số tiền rút
long long chonsotienrut();

//Chức năng rút tiền
void ruttien(node root, node myAccount);

//Chức năng xem tài khoản
void xemtaikhoan(node myAccount);

//Menu
void menu(node root, node myAccount);

//Hàm đăng nhập với vai trò khách
void GuestLogin(node root);

//Hàm đăng nhập với vai trò Lập trình viên
void AdministratorLogin(char *shutdown);

//Hàm bật máy ATM
void khoidong(node root);

int main()
{
    //Cho phép in tiếng việt trong terminal
    SetConsoleOutputCP(CP_UTF8);

    node root = NULL;
    root = input(root);
    khoidong(root);
}

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
    FILE *f = fopen("D:\\project\\New folder\\ATM_PROJECT\\input.txt", "r");

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

//Hàm chọn số tiền gửi đi
long long chonsotiengui(node target, node myAccount)
{
    long long hanmuctoida;
    if (target == myAccount) hanmuctoida = 200000000;
    else hanmuctoida = 100000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;
    char choose[100];

    printf("\nCHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");
        
    int j = 0;
    for (j = 0; j < 8; j++)
    {
        if (j == 0) printf("%d. Quay về menu        ", j);
        else if (j == 7) printf("%d. Số khác\n\n", j);
        else
        {
            printf("%d. %lld VND       ",j,arr[j]);
            if (j == 2 || j == 5) printf("\n\n");
        }
    }
    do 
    {

        if (moneyEntryCount == 3)
        {
            printf("Nhập lựa chọn của bạn : ");
        }
        else
        {
            printf("Nhập lại lựa chọn của bạn  (Bạn còn %d lần): ", moneyEntryCount);
        }
        
        
        if (fgets(choose,sizeof(choose),stdin)==NULL) continue;
        
        if (choose[0]=='\n')
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Bạn chưa nhập gì! ***\n");
            continue;
        }
        
        int len = strlen(choose);
        clear = 0;
        
        if (choose[len-1]=='\n') 
        {
            choose[len-1]='\0';
            len--;
        }
        else 
        {
            clear = clear_buffer(); 
        }
    
        if (len > 1 || clear == 1)
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng CHỈ NHẬP 1 SỐ. ***\n");
            continue; 
        }
        
        if (choose[0]>='0' && choose[0] <='7')
        {
            i = choose[0]-'0';
            break; 
        }
        else
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }

        if (i < 0 || i > 7 || clear == 1)
        {
            moneyEntryCount -= 1;
            printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }

    } while (moneyEntryCount > 0);
    if (moneyEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return 0;
            }
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 3)
            {
                printf("Vui lòng nhập bội số của 50.000 VND: ");
            }
            else
            {
                printf("Vui lòng nhập bội số của 50.000 VND (Bạn còn %d lần): ", tempEntry);
            }
            
            scanf(" %lld", &temp);
            clear = clear_buffer();

            if (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1)
            {
                tempEntry -= 1;
                
                if (tempEntry == 0)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                    return 0;
                }
                printf("\n*** Số tiền không hợp lệ! ***\n\n");
            }
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1);
        return temp;
    }
    else if (i<0 || i>7 || clear == 1)
    {
        printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
        return 0;
    }
    else return arr[i];
}

//Chức năng gửi tiền
void guitien(node root, node myAccount)
{
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
        if (AccountEntryCount == 3)
        {
            printf("Nhập số tài khoản bạn muốn gửi tiền: ");
        }
        else
        {
            printf("Nhập số tài khoản bạn muốn gửi tiền (Bạn còn %d lần nhập): ", AccountEntryCount);
        }
        
        AccountEntryCount -= 1;

        if (fgets(account,sizeof(account),stdin)==NULL) continue;
        int len=strlen(account);
        if (account[0]=='\n')
        {
            printf("**** Bạn chưa nhập gì cả! **** \n");
            continue;
        }
        if (account[len-1]=='\n')
        {
        	account[len-1]='\0';
		}
        else
        {
        	clear_buffer();
		}

        node targetAccount = findNode(root, account);
        if (targetAccount != NULL)
        {
            long long sotiengui = chonsotiengui(targetAccount, myAccount);

            if (sotiengui == 0) return;
            else if  (sotiengui != 0)
            {
                char message[81]; 
                int message_Entry_Count = 3;
                int clear_msg = 0;

                do
                {
                    if (clear_msg == 1) printf("\n*** QUÁ 80 KÍ TỰ ***\n\n");

                    if (message_Entry_Count == 3)
                    {
                        printf("Nhập lời nhắn với 80 kí tự: ");
                    }
                    else
                    {
                        printf("Nhập lời nhắn với 80 kí tự (Bạn còn %d lần nhập): ", message_Entry_Count);
                    }
                    
                    message_Entry_Count -= 1;
                    if (fgets(message,sizeof(message),stdin)==NULL) continue;
                    int len=strlen(message);
                    if (message[len-1]=='\n')
                    {
                        message[len-1]='\0';
                        len--;
                    }
                    else
                    {
                        clear_msg = clear_buffer();
                    } 
                    if (len>80)
                    {
                        if (message_Entry_Count>0) printf("Nhập quá 80 kí tự ,vui lòng nhập lại !!!");
                        else
                        {
                            printf("Đã quá số lần nhập -.-");
                        }
                    }
                }
                while (clear_msg == 1 && message_Entry_Count > 0);

                if (clear_msg == 1)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                    return;
                }

                if (admin_index >= GIAODICHPHIEN)
                {
                    printf("\n*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                    return;
                }

                if (myAccount->Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                {
                    printf("\n*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                    return;
                }
                
                if (myAccount == targetAccount)
                {
                    if (myAccount->Data->TransactionCount < MAX_TRASACTION_LEN)
                    {
                        int current_index = myAccount->Data->TransactionCount;
                        myAccount->Data->Balance += sotiengui;

                        sprintf(myAccount->Data->TransactionHistory[current_index], "%s|SD: %llu|+%lld VND|ND: %s", myAccount->Data->AccountNumber ,myAccount->Data->Balance,sotiengui, message);
                        strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[current_index]);
                        admin_index +=1;
                        myAccount->Data->TransactionCount += 1;

                        printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                        return;
                    }
                    else
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỬ GIAO DỊCH\n\n");
                        return;
                    }
                }
                else
                {
                    if (myAccount->Data->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }
                    if (targetAccount->Data->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
                        return;
                    }

                    int targetAccount_current_index = targetAccount->Data->TransactionCount;
                    int myAccount_current_index = myAccount->Data->TransactionCount;

                    targetAccount->Data->Balance += sotiengui;

                    sprintf(myAccount->Data->TransactionHistory[myAccount_current_index], "%s|SD: %llu|ND: Gửi %lld VND đến tài khoản %s", myAccount->Data->AccountNumber,myAccount->Data->Balance, sotiengui, targetAccount->Data->AccountNumber);
                    sprintf(targetAccount->Data->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s", targetAccount->Data->AccountNumber, targetAccount->Data->Balance,sotiengui, message);

                    strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;
                    myAccount->Data->TransactionCount += 1;
                    targetAccount->Data->TransactionCount += 1;

                    printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                    return;
                }
            }
        }
        else
        {
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            
            if (AccountEntryCount == 0) break;

            int clear_yn;
            int ynEntryCount = 3;

            do 
            {
                if (ynEntryCount == 3)
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
                }
                else
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N] (Bạn còn %d lần): ", ynEntryCount);
                }
                if (scanf("%c", &yesno) != 1) 
                {
                    ynEntryCount--;
                    continue; 
                }
                if (yesno=='\n')
                {
                    ynEntryCount--;
                    continue;
                } 
                clear_yn = clear_buffer();

                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1)
                {
                    ynEntryCount -= 1;
                    if (ynEntryCount == 0)
                    {
                        printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                        return;
                    }
                    printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
            if (yesno == 'N') return;
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    
    if (AccountEntryCount == 0) printf("\n*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
}

//Hàm chọn số tiền chuyển đi
long long chonsotienchuyen()
{
    long long hanmuctoida = 100000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;
    char choose[100];

    printf("\nCHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");

        int j = 0;
        for (j = 0; j < 8; j++)
        {
            if (j == 0) printf("%d. Quay về menu        ", j);
            else if (j == 7) printf("%d. Số khác\n\n", j);
            else
            {
                printf("%d. %lld VND       ",j,arr[j]);
                if (j == 2 || j == 5) printf("\n\n");
            }
        }

    do
    {
        if (moneyEntryCount == 3)
        {
            printf("Chọn số tiền bạn muốn chuyển: ");
        }
        else
        {
            printf("Chọn số tiền bạn muốn chuyển (Bạn còn %d lần): ", moneyEntryCount);
        }
        
        
        if (fgets(choose,sizeof(choose),stdin)==NULL) continue;
        
        if (choose[0]=='\n')
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Bạn chưa nhập gì! ***\n");
            continue;
        }
        
        int len = strlen(choose);
        clear = 0;
        
        if (choose[len-1]=='\n') 
        {
            choose[len-1]='\0';
            len--;
        }
        else 
        {
            clear = clear_buffer(); 
        }
    
        if (len > 1 || clear == 1)
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng CHỈ NHẬP 1 SỐ. ***\n");
            continue; 
        }
        
        if (choose[0]>='0' && choose[0] <='7')
        {
            i = choose[0]-'0';
            break; 
        }
        else
        {
            moneyEntryCount -= 1;
            if (moneyEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }
        if (i < 0 || i > 7 || clear == 1)
        {
            moneyEntryCount -= 1;
            
            if (moneyEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return 0;
            }
            printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }

    } while (moneyEntryCount>0);

    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 3)
            {
                printf("Vui lòng nhập bội số của 50.000 VND: ");
            }
            else
            {
                printf("Vui lòng nhập bội số của 50.000 VND (Bạn còn %d lần): ", tempEntry);
            }
            
            scanf(" %lld", &temp);
            clear = clear_buffer();

            if (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1)
            {
                tempEntry -= 1;
                
                if (tempEntry == 0)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                    return 0;
                }
                printf("\n*** Số tiền không hợp lệ! ***\n\n");
            }
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1);
        return temp;
    }
    else return arr[i];
}

//Chức năng chuyển tiền
void chuyentien(node root, node myAccount)
{
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
        if (AccountEntryCount == 3)
        {
            printf("Nhập số tài khoản bạn muốn chuyển tiền: ");
        }
        else
        {
            printf("Nhập số tài khoản bạn muốn chuyển tiền (Bạn còn %d lần nhập): ", AccountEntryCount);
        }
        
        AccountEntryCount -= 1;
        if (fgets(account,sizeof(account),stdin)==NULL) continue;
        int len=strlen(account);
        if (account[0]=='\n')
        {
            printf("**** Bạn chưa nhập gì cả! **** \n");
            continue;
        }
        if (account[len-1]=='\n')
        {
        	account[len-1]='\0';
		}
        else
        {
        	clear_buffer();
		}

        if (strcmp(account, myAccount->Data->AccountNumber) == 0)
        {
            printf("\n*** TRÙNG LẶP TÀI KHOẢN NGUỒN ***\n\n");
            
            if (AccountEntryCount == 0) break;

            int clear_yn;
            int ynEntryCount = 3;

            do 
            {
                if (ynEntryCount == 3)
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
                }
                else
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N] (Bạn còn %d lần): ", ynEntryCount);
                }
                if (scanf("%c", &yesno) != 1) 
                {
                    ynEntryCount--;
                    continue; 
                }
                if (yesno=='\n')
                {
                    ynEntryCount--;
                    continue;
                } 
                clear_yn = clear_buffer();

                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1)
                {
                    ynEntryCount -= 1;
                    if (ynEntryCount == 0)
                    {
                        printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                        return;
                    }
                    printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
            
            if (yesno == 'N') return;
        }
        else
        {
            node targetAccount = findNode(root, account);
            if (targetAccount != NULL)
            {
                long long sotienchuyen = chonsotienchuyen();

                if (sotienchuyen == 0) return;
                else if  (sotienchuyen != 0)
                {
                    char message[81];
                    int message_Entry_Count = 3;
                    int clear_msg = 0;

                    do
                {
                    if (clear_msg == 1) printf("\n*** QUÁ 80 KÍ TỰ ***\n\n");

                    if (message_Entry_Count == 3)
                    {
                        printf("Nhập lời nhắn với 80 kí tự: ");
                    }
                    else
                    {
                        printf("Nhập lời nhắn với 80 kí tự (Bạn còn %d lần nhập): ", message_Entry_Count);
                    }
                    
                    message_Entry_Count -= 1;
                    if (fgets(message,sizeof(message),stdin)==NULL) continue;
                    int len=strlen(message);
                    if (message[len-1]=='\n')
                    {
                        message[len-1]='\0';
                        len--;
                    }
                    else
                    {
                        clear_msg = clear_buffer();
                    } 
                    if (len>80)
                    {
                        if (message_Entry_Count>0) printf("Nhập quá 80 kí tự ,vui lòng nhập lại !!!");
                        else
                        {
                            printf("Đã quá số lần nhập -.-");
                        }
                    }
                }
                while (clear_msg == 1 && message_Entry_Count > 0);

                    if (clear_msg == 1)
                    {
                        printf("\n*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                        return;
                    }

                    if (myAccount->Data->Balance < sotienchuyen)
                    {
                        printf("\n*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
                        return;
                    }

                    if (admin_index >= GIAODICHPHIEN)
                    {
                        printf("\n*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                        return;
                    }

                    if (myAccount->Data->TransactionCount >= MAX_DAILY_TRANSACTION)
                    {
                        printf("\n*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                        return;
                    }

                    if (myAccount->Data->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }

                    if (targetAccount->Data->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
                        return;
                    }

                    int targetAccount_current_index = targetAccount->Data->TransactionCount;
                    int myAccount_current_index = myAccount->Data->TransactionCount;

                    myAccount->Data->Balance -= sotienchuyen;
                    targetAccount->Data->Balance += sotienchuyen;

                    sprintf(myAccount->Data->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%lld VND|ND: %s", myAccount->Data->AccountNumber ,myAccount->Data->Balance ,sotienchuyen, message);
                    sprintf(targetAccount->Data->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s", targetAccount->Data->AccountNumber ,targetAccount->Data->Balance,sotienchuyen, message);

                    strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;

                    myAccount->Data->TransactionCount += 1;
                    targetAccount->Data->TransactionCount += 1;

                    printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                    return;
                }
            }
            else
            {
                printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
                
                if (AccountEntryCount == 0) break;

                int clear_yn;
                int ynEntryCount = 3;

                do 
            {
                if (ynEntryCount == 3)
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
                }
                else
                {
                    printf("Bạn muốn nhập lại Số tài khoản không? [Y/N] (Bạn còn %d lần): ", ynEntryCount);
                }
                if (scanf("%c", &yesno) != 1) 
                {
                    ynEntryCount--;
                    continue; 
                }
                if (yesno=='\n')
                {
                    ynEntryCount--;
                    continue;
                } 
                clear_yn = clear_buffer();

                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1)
                {
                    ynEntryCount -= 1;
                    if (ynEntryCount == 0)
                    {
                        printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                        return;
                    }
                    printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);

                
                if (yesno == 'N') return;
            }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    
    if (AccountEntryCount == 0) printf("\n*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
}

//Hàm chọn số tiền rút
long long chonsotienrut()
{
    long long hanmuctoida = 10000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;

    do
    {
        printf("\n");
        int j = 0;
        for (j = 0; j < 8; j++)
        {
            if (j == 0) printf("%d. Quay về menu        ", j);
            else if (j == 7) printf("%d. Số khác\n\n", j);
            else
            {
                printf("%d. %lld VND       ",j,arr[j]);
                if (j == 2 || j == 5) printf("\n\n");
            }
        }

        if (moneyEntryCount == 3)
        {
            printf("Chọn số tiền bạn muốn rút: ");
        }
        else
        {
            printf("Chọn số tiền bạn muốn rút (Bạn còn %d lần): ", moneyEntryCount);
        }
        
        scanf("%d", &i);
        clear = clear_buffer();

        if (i < 0 || i > 7 || clear == 1)
        {
            moneyEntryCount -= 1;
            
            if (moneyEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return 0;
            }
            printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }

    } while (i < 0 || i > 7 || clear == 1);

    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 3)
            {
                printf("Vui lòng nhập bội số của 50.000 VND: ");
            }
            else
            {
                printf("Vui lòng nhập bội số của 50.000 VND (Bạn còn %d lần): ", tempEntry);
            }
            
            scanf(" %lld", &temp);
            clear = clear_buffer();

            if (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1)
            {
                tempEntry -= 1;
                
                if (tempEntry == 0)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                    return 0;
                }
                printf("\n*** Số tiền không hợp lệ! ***\n\n");
            }
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0 || clear == 1);
        return temp;
    }
    else return arr[i];
}

//Chức năng rút tiền
void ruttien(node root, node myAccount)
{
    long long sotienrut = chonsotienrut();

    if (sotienrut == 0) return;


    else if  (sotienrut != 0)
    {
        char message[81]; //Trừ hao 50 kí tự ghi +VND
        int message_Entry_Count = 3;
        int clear = 0;

        //Kiểm tra số tiền tài khoản nguồn
        if (myAccount ->Data ->Balance < sotienrut)
        {
            printf("* SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch phiên
        if (admin_index >= GIAODICHPHIEN)
        {
            printf("* QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch trong ngày
        if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
        {
            printf("* QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
            return;
        }
        

        //Kiểm tra số lần giao dịch đối với lịch sử My Account
        if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
        {
            printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
            return;
        }

        int myAccount_current_index = myAccount -> Data -> TransactionCount;

        //Trừ tiền vào myAccount
        myAccount ->Data -> Balance -= sotienrut;


        //Thêm lời nhắn vào thông báo
        sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%lld| ND: Rút tiền tại ATM", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotienrut); //132

        //Thêm vào danh sách giao dịch admin
        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
        admin_index +=1;

        //Cộng số lần giao dịch
        myAccount-> Data-> TransactionCount += 1;

        printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
        return;
    }
}

//Chức năng xem tài khoản
void xemtaikhoan(node myAccount)
{
    char *option[] = {"0. Hủy giao dịch","1. Xem số dư", "2. Xem lịch sử giao dịch"};
    int optionCount = sizeof(option) / sizeof(option[0]);
    int choice;
    int clear;
    int accEntryCount = 3;

    do
    {
        printf("\n");
        int i;
        for (i = 0; i< optionCount; i+=1)
        {
            printf("%s  ",option[i]);
        }

        if (accEntryCount == 3)
        {
            printf("\n\nVui lòng nhập lựa chọn của bạn: ");
        }
        else
        {
            printf("\n\nVui lòng nhập lựa chọn của bạn (Bạn còn %d lần): ", accEntryCount);
        }
        
        scanf("%d", &choice);
        clear = clear_buffer();

        if (choice < 0 || choice > 2 || clear == 1)
        {
            accEntryCount -= 1;
            
            if (accEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return;
            }
            printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ chọn số từ 0 đến 2. ***\n\n");
        }

    } while (choice < 0 || choice > 2 || clear == 1);

    if (choice == 1)
    {
        printf("\nSố dư hiện tại: %llu\n\n", myAccount->Data->Balance);
        return;
    }
    else if (choice == 2)
    {
        printf("\n");
        int index;
        int max_transaction_history = myAccount->Data->TransactionCount;
        
        if (max_transaction_history == 0) 
        {
            printf("Bạn chưa giao dịch trước đây\n\n");
        }
        else
        {
            for (index = 0; index < max_transaction_history; index +=1)
            {
                printf("%d. %s\n\n", index+1, myAccount->Data->TransactionHistory[index]);
            }
        }
        return;
    }
    else if (choice == 0)
    {
        return;
    }
}

//Menu
void menu(node root, node myAccount)
{
    char *option[] = {"0. Hủy giao dịch","1. Gửi tiền", "2. Chuyển tiền", "3. Rút tiền", "4. Xem tài khoản"};
    int optionCount = sizeof(option)/ sizeof(option[0]);
    
        int choice=-1;
        int menuEntryCount = 3;
        char input[1000];
        
        printf("\n--- MENU GIAO DỊCH ---\n");
        for (int i = 0; i < optionCount; i++) printf("%s\n", option[i]);
        while (menuEntryCount>0)
        {
            if (menuEntryCount == 3)    printf("Nhập sự lựa chọn của bạn: ");
            else                        printf("Nhập lại (Bạn còn %d lần): ", menuEntryCount);
            if (fgets(input,sizeof(input),stdin)==NULL) continue;
            if (input[0]=='\n')
            {
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Bạn chưa nhập gì. Vui lòng nhập từ 0 đến 4! ***\n");
                continue;
            }
            int len=strlen(input);
            int clear=0;
            if (input[len-1]=='\n')
            {
                input[len-1]='\0';
                len--;
            }
            else
            {
                clear=clear_buffer();
            }
            if (len > 1 || clear == 1)
            {
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng CHỈ NHẬP 1 SỐ. ***\n");
                continue; 
            }
            if (input[0]>='0' && input[0] <='4')
            {
                choice=input[0]-'0';
                break;
            }
            else{
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ chọn từ 0 đến 4. ***\n");
            }
        }
        if ((menuEntryCount == 0) && (choice<0 || choice >4)) {
            printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
            return;
        }
        //xử lý các lựa chọn
        switch (choice)
        {
            case 1: guitien(root, myAccount); break;
            case 2: chuyentien(root, myAccount); break;
            case 3: ruttien(root, myAccount); break;
            case 4: xemtaikhoan(myAccount); break;
            case 0: 
            default:
                printf("\n Đã hủy giao dịch. \n");
                 return;
        }

}

//Hàm đăng nhập với vai trò khách
void GuestLogin(node root)
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 3;

    do 
    {
        printf("Vui lòng nhập Số tài khoản của bạn (Bạn còn %d lần nhập tài khoản): ", loginCount);
        loginCount -= 1;

        if (fgets(target,sizeof(target),stdin)==NULL) continue;
        if (target[0]=='\n')	continue;
        int len = strlen(target);
        if (target[len - 1] == '\n') 
        {
            target[len - 1] = '\0'; 
        } 
        else 
        {
            clear_buffer();
        }

        node temp = findNode(root, target);

        if (temp != NULL)
        {
            char mapin[MAX_PIN_LEN];
            int pinEntryCount = 3;
            do
            {
                printf("Vui lòng nhập mã Pin (Bạn còn %d lần nhập)): ", pinEntryCount);
                pinEntryCount-=1;
                if (fgets(mapin,sizeof(mapin),stdin)==NULL) continue;
                int len=strlen(mapin);
                if (mapin[len-1]=='\n')
                {
                	mapin[len-1]='\0';
				}
				else
				{
					clear_buffer();
				}
            } while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0);

            if (strcmp(temp ->Data -> Pin, mapin) ==0) 
            {
                printf("\nVào menu\n\n");
                menu(root, temp);
                return;
            }

            if (pinEntryCount == 0) 
            {
                printf("\n\n*** HẾT SỐ LẦN NHẬP MÃ PIN ***\n\n");
                return;
            }
        }
        else
        {
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            
            int clear_yn;
            int ynEntryCount = 3; 

            do 
            {
                if (ynEntryCount == 0)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. KHỞI ĐỘNG LẠI CHƯƠNG TRÌNH ***\n\n");
                    return; 
                }

                printf("Bạn muốn nhập lại Số tài khoản không? [Y/N] (Bạn còn %d lần): ", ynEntryCount);
                scanf(" %c", &yesno);
                clear_yn = clear_buffer();
                ynEntryCount -= 1;

                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1)
                {
                    printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while ((yesno != 'Y' && yesno != 'N') || clear_yn == 1);

            if (yesno == 'N') return;
        } 
    } while (yesno == 'Y' && loginCount > 0);

    if (loginCount == 0) printf("** QUÁ SỐ LẦN NHẬP TÀI KHOẢN **\n\n");
}

//Hàm đăng nhập với vai trò Lập trình viên
void AdministratorLogin(char *shutdown)
{

    char admin_pin[7] = "000000";
    char Pin_Entry[7];
    int Pin_Entry_Count = 3;
    int clear;

    //Nhập mã bảo mật
    do 
    {
        if (Pin_Entry_Count <3) printf("***** Nhập sai! *****\n");
        printf("Vui lòng nhập mã bảo mật của Admin (Bạn còn %d lần nhập): ", Pin_Entry_Count);
        Pin_Entry_Count -= 1;
		if (fgets(Pin_Entry,sizeof(Pin_Entry),stdin)==NULL) continue;
        if (Pin_Entry[0]=='\n')	continue;
        Pin_Entry[strcspn(Pin_Entry, "\n")] = 0;
        if (strlen(Pin_Entry)<6) continue;
		clear=clear_buffer();
    } while ((strcmp(Pin_Entry, admin_pin) != 0 || clear != 0) && Pin_Entry_Count > 0); //Tránh trường hợp người dùng nhập dư kí tự khiến buffer hiểu lầm rằng còn lần nhập nhưng thực tế đã hết lần nhập

    //Kiểm tra mã bảo mật
    if (strcmp(Pin_Entry, admin_pin) == 0 && clear == 0)
    {
        FILE *f =  fopen("output.txt", "w");
        int i = 0;

        for (i = 0; i < admin_index; i+=1)
        {
            fprintf(f ,"%d. Số tài khoản: %s\n", i+1, TransactionList[i]);
        }

        fclose(f);

        //Chuyển thành shutdown
        (*shutdown) = 'Y';
    }
    else
    {
        printf("*** QUÁ SỐ LẦN NHẬP MÃ BẢO MẬT ***\n\n");
    }
    return;
}

//Hàm bật máy ATM
void khoidong(node root)
{
    char ROLE;
    char shutdown = 'N';
    int clear;
    int roleEntryCount;

    do
    {
        printf("======================================================\n\n");
        printf("* CHÀO MỪNG QUÝ KHÁCH ĐẾN VỚI NGÂN HÀNG ĐẠT KHÔNG CHÍN*\n\n");
        printf("======================================================\n\n");

        roleEntryCount = 3;

        do 
        {
            if (roleEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG TẮT MÁY ĐỂ BẢO MẬT ***\n\n");
                return; 
            }
            roleEntryCount -= 1;
            printf("Vai trò của bạn là gì [A/G] (Bạn còn %d lần): ", roleEntryCount);
            if (scanf("%c", &ROLE) != 1) {
                continue; 
            }
            if (ROLE=='\n')
            {
            continue;
            } 
            clear = clear_buffer();

            if ((ROLE != 'A' && ROLE != 'G') || clear == 1)
            {
                printf("Lỗi: Vui lòng chỉ nhập A hoặc G!\n\n");
            }
        } while ((ROLE != 'A' && ROLE != 'G') || clear == 1);

        if (ROLE == 'G') GuestLogin(root);
        else if (ROLE == 'A') AdministratorLogin(&shutdown);

    } while (shutdown != 'Y');
    printf("\n*** MÁY ĐANG TẮT... CẢM ƠN QUÝ KHÁCH ĐÃ SỬ DỤNG DỊCH VỤ ***\n\n");
        
}