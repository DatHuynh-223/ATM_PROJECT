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


    if (compare ==1) root -> right = CreateTree((*root).right, a);
    
    else if (compare == -1) root -> left = CreateTree(root -> left,a);
    
    else printf("Lỗi trùng lặp số tài khoản %s\n", a-> Data ->AccountNumber);

    //trả về root ban đầu
    return root;
}

//Hàm đọc file
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
long long  chonsotiengui(node target, node myAccount)
{
    //Chọn hạn mức tối đa
    long long hanmuctoida;
    if (target == myAccount) hanmuctoida = 200000000;
    else hanmuctoida = 100000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    printf("CHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");
    
    //In menu số tiền được chọn
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay về menu        ", i);
        else if (i == 7) printf("%d. Số khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Chọn số tiền bạn muốn gửi: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ LẦN NHẬP ***\n\n");
                return 0;
            }

            printf("Vui lòng nhập bội số của 50.000 VND (Bạn có %d lần nhập): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
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
        printf("Nhập số tài khoản bạn muốn gửi tiền (Bạn còn %d lần nhập): ", AccountEntryCount);
        scanf(" %20s", account);
        int clear = clear_buffer();
        AccountEntryCount -= 1;


        node targetAccount = findNode(root, account);
        if (targetAccount != NULL)
        {
            long long sotiengui = chonsotiengui(targetAccount, myAccount);

            if (sotiengui == 0) return;


            else if  (sotiengui != 0)
            {
                char message[81]; //Trừ hao 50 kí tự ghi +VND
                int message_Entry_Count = 3;
                int clear = 0;


                //Nhập lời nhắn nạp tiền
                do
                {
                    if (clear == 1) printf("*** QUÁ 80 KÍ TỰ ***\n\n");

                    printf("Nhập lời nhắn với 80 kí tự (Bạn còn %d lần nhập): ", message_Entry_Count);
                    message_Entry_Count -= 1;

                    //Vì scanf sẽ dừng nếu gặp dấu cách khiến buffer hiểu lầm rằng dư kí tự --> cho phép \n
                    scanf(" %80[^\n]", message); //Trừ hao 50 kí tự ghi +VND
                    clear = clear_buffer();
                } while (clear == 1 && message_Entry_Count > 0);

        
                if (clear == 1)
                {
                    printf("*** QUÁ SỐ LẦN NHẬP LỜI NHẮN ***\n\n");
                    return;
                }

                //Kiểm tra số lần giao dịch phiên
                if (admin_index >= GIAODICHPHIEN)
                {
                    printf("*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                    return;
                }

                //Kiểm tra số lần giao dịch trong ngày
                if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                {
                    printf("*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                    return;
                }
                
                if (myAccount == targetAccount)
                {
                    //Kiểm tra số lượng giao dịch đối với lịch sử giao dịch
                    if (myAccount ->Data ->TransactionCount < MAX_TRASACTION_LEN)
                    {
                        int current_index = myAccount -> Data -> TransactionCount;

                        //Cộng tiền vào tài khoản
                        myAccount-> Data-> Balance += sotiengui;

                        //Thêm lời nhắn vào thông báo
                        sprintf(myAccount ->Data ->TransactionHistory[current_index], "%s|SD: %llu|+%lld VND|ND: %s", myAccount->Data ->AccountNumber ,myAccount ->Data ->Balance,sotiengui, message);

                        //Thêm vào danh sách admin
                        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[current_index]);
                        admin_index +=1;

                        //Cộng số lần giao dịch
                        myAccount-> Data-> TransactionCount += 1;

                        printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                        return;
                    }
                    else
                    {
                        printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH\n\n");
                        return;
                    }
                }
                else
                {
                    //Kiểm tra số lần giao dịch đối với lịch sử My Account
                    if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }

                    //Kiểm tra số lần giao dịch đối với lịch sử TargetAccount
                    if (targetAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
                        return;
                    }

                    int targetAccount_current_index = targetAccount -> Data -> TransactionCount;
                    int myAccount_current_index = myAccount -> Data -> TransactionCount;

                    //Cộng tiền vào tài khoản
                    targetAccount-> Data-> Balance += sotiengui;

                    //Thêm lời nhắn vào thông báo
                    sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|ND: Gửi %lld VND đến tài khoản %s", myAccount ->Data ->AccountNumber,myAccount ->Data ->Balance, sotiengui, targetAccount->Data->AccountNumber); //141 kí tự
                    sprintf(targetAccount ->Data ->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s",targetAccount->Data->Balance ,targetAccount ->Data ->Balance,sotiengui, message); //124 kí tự

                    //Thêm vào danh sách giao dịch admin
                    strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;

                    //Cộng số lần giao dịch
                    myAccount-> Data-> TransactionCount += 1;
                    targetAccount-> Data-> TransactionCount += 1;

                    printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                    return;
                }
            }
        }
        else
        {
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
            int clear = clear_buffer();
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN ***\n\n");
}

//Hàm chọn số tiền chuyển đi
long long  chonsotienchuyen()
{
    //Hạn mức tối đa
    long long hanmuctoida = 100000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    
    //In menu số tiền được chọn
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay về menu        ", i);
        else if (i == 7) printf("%d. Số khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Chọn số tiền bạn muốn chuyển: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ LẦN NHẬP ***\n\n");
                return 0;
            }

            printf("Vui lòng nhập bội số của 50.000 VND (Bạn có %d lần nhập): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
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
        printf("Nhập số tài khoản bạn muốn gửi tiền (Bạn còn %d lần nhập): ", AccountEntryCount);
        scanf(" %20s", account);
        int clear = clear_buffer();
        AccountEntryCount -= 1;

        //Kiểm tra trùng lặp tài khoản nguồn
        if (strcmp(account, myAccount ->Data ->AccountNumber) == 0)
        {
            printf("*** TRÙNG LẶP TÀI KHOÀN NGUỒN ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
            clear = clear_buffer();
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
                    char message[81]; //Trừ hao 50 kí tự ghi +VND
                    int message_Entry_Count = 3;
                    int clear = 0;


                    //Nhập lời nhắn nạp tiền
                    do
                    {
                        if (clear == 1) printf("*** QUÁ 80 KÍ TỰ ***\n\n");

                        printf("Nhập lời nhắn với 80 kí tự (Bạn còn %d lần nhập): ", message_Entry_Count);
                        message_Entry_Count -= 1;

                        //Vì scanf sẽ dừng nếu gặp dấu cách khiến buffer hiểu lầm rằng dư kí tự --> cho phép \n
                        scanf(" %80[^\n]", message); //Trừ hao 50 kí tự ghi +VND
                        clear = clear_buffer();
                    } while (clear == 1 && message_Entry_Count > 0);


                    //Khi thoát ra khỏi vòng lặp mà clear == 1 thì nghĩa là message_Entry_Count == 0
                    if (clear == 1)
                    {
                        printf("*** QUÁ SỐ LẦN NHẬP LỜI NHẮN ***\n\n");
                        return;
                    }

                    //Kiểm tra số tiền tài khoản nguồn
                    if (myAccount ->Data ->Balance < sotienchuyen)
                    {
                        printf("*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
                        return;
                    }

                    //Kiểm tra số lần giao dịch phiên
                    if (admin_index >= GIAODICHPHIEN)
                    {
                        printf("*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                        return;
                    }

                    //Kiểm tra số lần giao dịch trong ngày
                    if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                    {
                        printf("*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                        return;
                    }
                    

                    //Kiểm tra số lần giao dịch đối với lịch sử My Account
                    if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }

                    //Kiểm tra số lần giao dịch đối với lịch sử TargetAccount
                    if (targetAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
                        return;
                    }


                    int targetAccount_current_index = targetAccount -> Data -> TransactionCount;
                    int myAccount_current_index = myAccount -> Data -> TransactionCount;

                    //Trừ tiền vào myAccount
                    myAccount ->Data -> Balance -= sotienchuyen;

                    //Cộng tiền vào targetAccount
                    targetAccount-> Data-> Balance += sotienchuyen;

                    //Thêm lời nhắn vào thông báo
                    sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%lld VND|ND: %s", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance ,sotienchuyen, message);
                    sprintf(targetAccount ->Data ->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s", targetAccount ->Data ->AccountNumber ,targetAccount ->Data ->Balance,sotienchuyen, message); //Tối đa là 130 kí tự

                    //Thêm vào danh sách giao dịch admin
                    strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;

                    //Cộng số lần giao dịch
                    myAccount-> Data-> TransactionCount += 1;
                    targetAccount-> Data-> TransactionCount += 1;

                    printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
                    return;
                }
            }
            else
        {
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
            int clear = clear_buffer();
        }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN ***\n\n");
}

//Hàm chọn số tiền rút
long long  chonsotienrut()
{
    //Chọn hạn mức tối đa
    long long hanmuctoida = 10000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    
    //In menu số tiền được chọn
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay về menu        ", i);
        else if (i == 7) printf("%d. Số khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Chọn số tiền bạn muốn rút: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("Hạn mức tối đa là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ LẦN NHẬP ***\n\n");
                return 0;
            }

            printf("Vui lòng nhập bội số của 50.000 VND (Bạn có %d lần nhập): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
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
            printf("*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch phiên
        if (admin_index >= GIAODICHPHIEN)
        {
            printf("*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch trong ngày
        if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
        {
            printf("*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
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

    int i;
    for (i = 0; i< optionCount; i+=1)
    {
        printf("%s  ",option[i]);
    }

    int choice;
    printf("\n\nVui lòng nhập lựa chọn của bạn: ");
    scanf(" %d", &choice);
    clear_buffer();

    if (choice == 1)
    {
        printf("Số dư hiện tại: %llu\n\n", myAccount ->Data ->Balance);
        return;
    }
    
    if (choice == 2)
    {
        int index;
        int max_transaction_history = myAccount ->Data ->TransactionCount;
        if (max_transaction_history == 0) printf("Bạn chưa giao dịch trước đây");
        else
        {
            for (index = 0; index <max_transaction_history; index +=1)
            {
                printf("%d. %s\n\n", index+1, myAccount ->Data ->TransactionHistory[index]);
            }
        }
        printf("\n");
        return;
    }

    return;
}

//Menu
void menu(node root, node myAccount)
{
    //Mảng con trỏ, Nhược điểm: Không sửa được, Ưu điểm: Cấp phát đúng bộ nhớ cần thiết
    char *option[] = {"0. Hủy giao dịch","1. Gửi tiền", "2. Chuyển tiền", "3. Rút tiền", "4. Xem tài khoản"};

    int optionCount = sizeof(option)/ sizeof(option[0]);

    int i;
    for (i = 0; i< optionCount; i+=1)
    {
        printf("%s\n\n",option[i]);
    }

    int choice;
    printf("Nhập sự lựa chọn của bạn: ");
    scanf(" %d" , &choice);
    int clear = clear_buffer();
    if (choice == 1) 
    {
        guitien(root, myAccount);
    }
    else if (choice == 2)
    {
        chuyentien(root, myAccount);
    }
    else if (choice == 3)
    {
        ruttien(root, myAccount);
    }
    else if (choice == 4)
    {
        xemtaikhoan(myAccount);
    }
    else return;
}

//Hàm đăng nhập với vai trò khách
void GuestLogin(node root)
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 3;

    do 
    {
        //nhập account
        printf("Vui lòng nhập Số tài khoản của bạn (Bạn còn %d lần nhập tài khoản): ", loginCount);
        loginCount -= 1;
        scanf(" %20s", target);
        int clear = clear_buffer();
        
        
        node temp = findNode(root, target);

        //kiểm tra có tìm ra tài khoản hay không
        if (temp != NULL)
        {
            //Nhập pin
            char mapin[MAX_PIN_LEN];
            int pinEntryCount = 3;
            do
            {
                printf("Vui lòng nhập mã Pin (Bạn còn %d lần nhập)): ", pinEntryCount);
                scanf(" %10s",mapin);
                pinEntryCount-=1;
            } while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0);


            //Kiểm tra mã pin
            if (strcmp(temp ->Data -> Pin, mapin) ==0) 
            {

                //Vào menu
                printf("Vào menu\n\n");
                menu(root, temp);
                return;
            }

            //Kiểm tra số lần nhập
            if (pinEntryCount == 0) 
            {
                printf("\n\n*** HẾT SỐ LẦN NHẬP MÃ PIN ***\n\n");
                return;
            }
        }
        else
        {
            //Nhập lại số tài khoản
            printf("\n\n*** Không tìm thấy Số tài khoản ***\n\n");
            printf("Bạn muốn nhập lại Số tài khoản không? [Y/N]: ");
            scanf(" %c", &yesno);
            clear = clear_buffer();
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
        printf("Vui lòng nhập mã bảo mật của Admin (Bạn còn %d lần nhập): ", Pin_Entry_Count);
        scanf(" %6s", Pin_Entry);
        clear = clear_buffer();
        Pin_Entry_Count -= 1;
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

    do
    {
    printf("======================================================\n\n");
    printf("* CHÀO MỪNG QUÝ KHÁCH ĐẾN VỚI NGÂN HÀNG ĐẠT KHÔNG CHÍN*\n\n");
    printf("======================================================\n\n");

    //chọn vai trò
    printf("Vai trò của bạn là gì [A/G]: ");
    if (scanf("%c", &ROLE) != 1) {
            continue; 
        }
    if (ROLE=='\n')
    {
    	continue;
	} 
    int clean=clear_buffer(); 
    if (clean == 0)
	{
        if (ROLE == 'G' || ROLE == 'g')      GuestLogin(root);
        else if (ROLE == 'A' || ROLE == 'a') AdministratorLogin(&shutdown);
        else                                 printf("Lỗi: Vui lòng chỉ nhập A hoặc G!\n");
    }
    else {
        printf("Lỗi: Vui lòng chỉ nhập A hoặc G!\n");
     }

    } while (shutdown != 'Y');

    printf("Kết thúc chương trình");
}
int main()
{
    //Cho phép in tiếng việt trong terminal
    SetConsoleOutputCP(CP_UTF8);

    node root = NULL;
    root = input(root);
    khoidong(root);
}
