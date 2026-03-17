#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> //thu vi?n h? tr? ti?ng vi?t cho terminal

#define MAX_ACC_LEN 21 //có th? thay d?i n?u c?n thi?t (du 1 kí \0)
#define MAX_PIN_LEN 11 //có th? thay d?i n?u c?n thi?t (du 1 kí \0)
#define MAX_DAILY_TRANSACTION 10 //tùy vào ý c?a th?y cô
#define MAX_TRASACTION_LEN 51 // gi?i h?n d? dài tin nh?n m?i giao d?ch (du 1 kí \0)
#define INFORM_LEN 175 //Thõa du?c s? lu?ng t? trong message
#define GIAODICHPHIEN 100
//Danh sách giao d?ch c?a admin
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

//Hàm xóa b? nh? d?m khi ngu?i dùng nh?p du kí t?
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

//Hàm thêm ch? s? vào Account
Account append_account(char *AN, char *PI, unsigned long long BL)
{
    Account temp = (Account)malloc(sizeof(struct Account));

    //dùng strcpy d? copy xâu 2 qua xâu 1
    strcpy(temp -> AccountNumber,AN);
    strcpy(temp -> Pin, PI);
    temp -> Balance = BL;
    temp ->TransactionCount = 0;
    return temp;
}

//Hàm thêm nhánh vào Tree
node CreateNode (Account d)
{
    // hàm malloc d? c?p phát b? nh? heap, (node) d? ép k?u, sizeof(struct TreeNode) kích thu?c xin c?p
    node temp = (node)malloc(sizeof(struct TreeNode));
    temp -> Data = d;
    temp -> left = NULL;
    temp -> right = NULL; 
    return temp;
}

//Hàm t?o Tree t? nhánh
node CreateTree (node root, node a)
{
    //Ði?m d?ng c?a quá trình d? quy
    if (root ==  NULL) 
    {
        return a;
    }

    //dùng hàm strcmp d? so sánh 2 xâu account number, str1 > str2 thì compare =1
    int compare = strcmp(a-> Data->AccountNumber, root -> Data -> AccountNumber);


    if (compare ==1) root -> right = CreateTree((*root).right, a);
    
    else if (compare == -1) root -> left = CreateTree(root -> left,a);
    
    else printf("L?i trùng l?p s? tài kho?n %s\n", a-> Data ->AccountNumber);

    //tr? v? root ban d?u
    return root;
}

//Hàm d?c file
node input(node root)
{
    FILE *f = fopen("input.txt", "r");

    if (f == NULL)
    {
        printf("Không th? d?c file");
        return root;
    }

    //t?o tmp1 luu account number
    char tmp1[MAX_ACC_LEN];

    //t?o tmp2 luu pin
    char tmp2[MAX_PIN_LEN];

    //t?o tmp3 luu balance
    unsigned long long tmp3;


    // Khi fscanf không nh?n du?c giá tr? nào thõa nên tr? v? -1
    // N?u d?c thành công s? tr? v? 1 nhung có 3 ph?n t? s? tr? v? 3
    while (fscanf(f, "%20s %10s %llu", tmp1, tmp2, &tmp3) == 3) 
    {
        Account temp = append_account(tmp1, tmp2, tmp3);
        root = CreateTree(root,CreateNode(temp));
    }
    return root;
}

//Hàm tìm ki?m Node trong Tree
node findNode(node root, char *target)
{
    //N?u root = NULL thì nghia là dã tìm h?t Tree nhung không tìm th?y
    if (root == NULL)
    {
        return NULL;
    }
    int compare = strcmp(target, root->Data->AccountNumber);
    if (compare == 0) return root;
    else if (compare == 1) return findNode(root -> right, target);
    else return findNode(root -> left, target);
}

//Hàm ch?n s? ti?n g?i di
long long  chonsotiengui(node target, node myAccount)
{
    //Ch?n h?n m?c t?i da
    long long hanmuctoida;
    if (target == myAccount) hanmuctoida = 200000000;
    else hanmuctoida = 100000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    printf("CH? NH?N M?NH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");
    
    //In menu s? ti?n du?c ch?n
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay v? menu        ", i);
        else if (i == 7) printf("%d. S? khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Ch?n s? ti?n b?n mu?n g?i: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("H?n m?c t?i da là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ L?N NH?P ***\n\n");
                return 0;
            }

            printf("Vui lòng nh?p b?i s? c?a 50.000 VND (B?n có %d l?n nh?p): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
    else return arr[i];
}

//Ch?c nang g?i ti?n
void guitien(node root, node myAccount)
{
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
        printf("Nh?p s? tài kho?n b?n mu?n g?i ti?n (B?n còn %d l?n nh?p): ", AccountEntryCount);
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
                char message[81]; //Tr? hao 50 kí t? ghi +VND
                int message_Entry_Count = 3;
                int clear = 0;


                //Nh?p l?i nh?n n?p ti?n
                do
                {
                    if (clear == 1) printf("*** QUÁ 80 KÍ T? ***\n\n");

                    printf("Nh?p l?i nh?n v?i 80 kí t? (B?n còn %d l?n nh?p): ", message_Entry_Count);
                    message_Entry_Count -= 1;

                    //Vì scanf s? d?ng n?u g?p d?u cách khi?n buffer hi?u l?m r?ng du kí t? --> cho phép \n
                    scanf(" %80[^\n]", message); //Tr? hao 50 kí t? ghi +VND
                    clear = clear_buffer();
                } while (clear == 1 && message_Entry_Count > 0);

        
                if (clear == 1)
                {
                    printf("*** QUÁ S? L?N NH?P L?I NH?N ***\n\n");
                    return;
                }

                //Ki?m tra s? l?n giao d?ch phiên
                if (admin_index >= GIAODICHPHIEN)
                {
                    printf("*** QUÁ S? L?N GIAO D?CH PHIÊN ***\n\n");
                    return;
                }

                //Ki?m tra s? l?n giao d?ch trong ngày
                if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                {
                    printf("*** QUÁ S? L?N GIAO D?CH TRONG NGÀY ***\n\n");
                    return;
                }
                
                if (myAccount == targetAccount)
                {
                    //Ki?m tra s? lu?ng giao d?ch d?i v?i l?ch s? giao d?ch
                    if (myAccount ->Data ->TransactionCount < MAX_TRASACTION_LEN)
                    {
                        int current_index = myAccount -> Data -> TransactionCount;

                        //C?ng ti?n vào tài kho?n
                        myAccount-> Data-> Balance += sotiengui;

                        //Thêm l?i nh?n vào thông báo
                        sprintf(myAccount ->Data ->TransactionHistory[current_index], "%s|SD: %llu|+%lld VND|ND: %s", myAccount->Data ->AccountNumber ,myAccount ->Data ->Balance,sotiengui, message);

                        //Thêm vào danh sách admin
                        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[current_index]);
                        admin_index +=1;

                        //C?ng s? l?n giao d?ch
                        myAccount-> Data-> TransactionCount += 1;

                        printf("\n\n>>> GIAO D?CH THÀNH CÔNG\n\n");
                        return;
                    }
                    else
                    {
                        printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH\n\n");
                        return;
                    }
                }
                else
                {
                    //Ki?m tra s? l?n giao d?ch d?i v?i l?ch s? My Account
                    if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH Ð?I V?I TÀI KHO?N C?A B?N\n\n");
                        return;
                    }

                    //Ki?m tra s? l?n giao d?ch d?i v?i l?ch s? TargetAccount
                    if (targetAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH Ð?I V?I TÀI KHO?N G?I Ð?N\n\n");
                        return;
                    }

                    int targetAccount_current_index = targetAccount -> Data -> TransactionCount;
                    int myAccount_current_index = myAccount -> Data -> TransactionCount;

                    //C?ng ti?n vào tài kho?n
                    targetAccount-> Data-> Balance += sotiengui;

                    //Thêm l?i nh?n vào thông báo
                    sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|ND: G?i %lld VND d?n tài kho?n %s", myAccount ->Data ->AccountNumber,myAccount ->Data ->Balance, sotiengui, targetAccount->Data->AccountNumber); //141 kí t?
                    sprintf(targetAccount ->Data ->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s",targetAccount->Data->Balance ,targetAccount ->Data ->Balance,sotiengui, message); //124 kí t?

                    //Thêm vào danh sách giao d?ch admin
                    strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;

                    //C?ng s? l?n giao d?ch
                    myAccount-> Data-> TransactionCount += 1;
                    targetAccount-> Data-> TransactionCount += 1;

                    printf("\n\n>>> GIAO D?CH THÀNH CÔNG\n\n");
                    return;
                }
            }
        }
        else
        {
            printf("\n\n*** Không tìm th?y S? tài kho?n ***\n\n");
            printf("B?n mu?n nh?p l?i S? tài kho?n không? [Y/N]: ");
            scanf(" %c", &yesno);
            int clear = clear_buffer();
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("*** QUÁ S? L?N NH?P TÀI KHO?N ***\n\n");
}

//Hàm ch?n s? ti?n chuy?n di
long long  chonsotienchuyen()
{
    //H?n m?c t?i da
    long long hanmuctoida = 100000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    
    //In menu s? ti?n du?c ch?n
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay v? menu        ", i);
        else if (i == 7) printf("%d. S? khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Ch?n s? ti?n b?n mu?n chuy?n: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("H?n m?c t?i da là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ L?N NH?P ***\n\n");
                return 0;
            }

            printf("Vui lòng nh?p b?i s? c?a 50.000 VND (B?n có %d l?n nh?p): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
    else return arr[i];
}

//Ch?c nang chuy?n ti?n
void chuyentien(node root, node myAccount)
{
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
        printf("Nh?p s? tài kho?n b?n mu?n g?i ti?n (B?n còn %d l?n nh?p): ", AccountEntryCount);
        scanf(" %20s", account);
        int clear = clear_buffer();
        AccountEntryCount -= 1;

        //Ki?m tra trùng l?p tài kho?n ngu?n
        if (strcmp(account, myAccount ->Data ->AccountNumber) == 0)
        {
            printf("*** TRÙNG L?P TÀI KHOÀN NGU?N ***\n\n");
            printf("B?n mu?n nh?p l?i S? tài kho?n không? [Y/N]: ");
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
                    char message[81]; //Tr? hao 50 kí t? ghi +VND
                    int message_Entry_Count = 3;
                    int clear = 0;


                    //Nh?p l?i nh?n n?p ti?n
                    do
                    {
                        if (clear == 1) printf("*** QUÁ 80 KÍ T? ***\n\n");

                        printf("Nh?p l?i nh?n v?i 80 kí t? (B?n còn %d l?n nh?p): ", message_Entry_Count);
                        message_Entry_Count -= 1;

                        //Vì scanf s? d?ng n?u g?p d?u cách khi?n buffer hi?u l?m r?ng du kí t? --> cho phép \n
                        scanf(" %80[^\n]", message); //Tr? hao 50 kí t? ghi +VND
                        clear = clear_buffer();
                    } while (clear == 1 && message_Entry_Count > 0);


                    //Khi thoát ra kh?i vòng l?p mà clear == 1 thì nghia là message_Entry_Count == 0
                    if (clear == 1)
                    {
                        printf("*** QUÁ S? L?N NH?P L?I NH?N ***\n\n");
                        return;
                    }

                    //Ki?m tra s? ti?n tài kho?n ngu?n
                    if (myAccount ->Data ->Balance < sotienchuyen)
                    {
                        printf("*** S? DU TÀI KHO?N KHÔNG Ð? Ð? TH?C HI?N GIAO D?CH ***\n\n");
                        return;
                    }

                    //Ki?m tra s? l?n giao d?ch phiên
                    if (admin_index >= GIAODICHPHIEN)
                    {
                        printf("*** QUÁ S? L?N GIAO D?CH PHIÊN ***\n\n");
                        return;
                    }

                    //Ki?m tra s? l?n giao d?ch trong ngày
                    if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                    {
                        printf("*** QUÁ S? L?N GIAO D?CH TRONG NGÀY ***\n\n");
                        return;
                    }
                    

                    //Ki?m tra s? l?n giao d?ch d?i v?i l?ch s? My Account
                    if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH Ð?I V?I TÀI KHO?N C?A B?N\n\n");
                        return;
                    }

                    //Ki?m tra s? l?n giao d?ch d?i v?i l?ch s? TargetAccount
                    if (targetAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
                    {
                        printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH Ð?I V?I TÀI KHO?N G?I Ð?N\n\n");
                        return;
                    }


                    int targetAccount_current_index = targetAccount -> Data -> TransactionCount;
                    int myAccount_current_index = myAccount -> Data -> TransactionCount;

                    //Tr? ti?n vào myAccount
                    myAccount ->Data -> Balance -= sotienchuyen;

                    //C?ng ti?n vào targetAccount
                    targetAccount-> Data-> Balance += sotienchuyen;

                    //Thêm l?i nh?n vào thông báo
                    sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%lld VND|ND: %s", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance ,sotienchuyen, message);
                    sprintf(targetAccount ->Data ->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%lld VND|ND: %s", targetAccount ->Data ->AccountNumber ,targetAccount ->Data ->Balance,sotienchuyen, message); //T?i da là 130 kí t?

                    //Thêm vào danh sách giao d?ch admin
                    strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
                    admin_index +=1;

                    //C?ng s? l?n giao d?ch
                    myAccount-> Data-> TransactionCount += 1;
                    targetAccount-> Data-> TransactionCount += 1;

                    printf("\n\n>>> GIAO D?CH THÀNH CÔNG\n\n");
                    return;
                }
            }
            else
        {
            printf("\n\n*** Không tìm th?y S? tài kho?n ***\n\n");
            printf("B?n mu?n nh?p l?i S? tài kho?n không? [Y/N]: ");
            scanf(" %c", &yesno);
            int clear = clear_buffer();
        }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("*** QUÁ S? L?N NH?P TÀI KHO?N ***\n\n");
}

//Hàm ch?n s? ti?n rút
long long  chonsotienrut()
{
    //Ch?n h?n m?c t?i da
    long long hanmuctoida = 10000000;
    
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    
    //In menu s? ti?n du?c ch?n
    int i = 0;
    for (i = 0; i < 8; i++)
    {
        if (i == 0) printf("%d. Quay v? menu        ", i);
        else if (i == 7) printf("%d. S? khác\n\n", i);
        else
        {
            printf("%d. %lld VND       ",i,arr[i]);
            if (i == 2 || i == 5) printf("\n\n");
        }
    }

    printf("Ch?n s? ti?n b?n mu?n rút: ");
    scanf("%d", &i);
    int clear = clear_buffer();
    if (i == 0) return 0;
    else if (i == 7)
    {
        printf("H?n m?c t?i da là : %lld VND\n\n", hanmuctoida);

        int tempEntry = 3;
        long long temp;
        do
        {
            if (tempEntry == 0)
            {
                printf("*** QUÁ SÔ L?N NH?P ***\n\n");
                return 0;
            }

            printf("Vui lòng nh?p b?i s? c?a 50.000 VND (B?n có %d l?n nh?p): ", tempEntry);
            scanf(" %lld", &temp);
            int clear = clear_buffer();
            tempEntry -= 1;
        } while (temp % 50000 != 0 || temp > hanmuctoida || temp <= 0);
        return temp;
    }
    else if (i < 0 || i > 7) return 0;
    else return arr[i];
}

//Ch?c nang rút ti?n
void ruttien(node root, node myAccount)
{
    long long sotienrut = chonsotienrut();

    if (sotienrut == 0) return;


    else if  (sotienrut != 0)
    {
        char message[81]; //Tr? hao 50 kí t? ghi +VND
        int message_Entry_Count = 3;
        int clear = 0;

        //Ki?m tra s? ti?n tài kho?n ngu?n
        if (myAccount ->Data ->Balance < sotienrut)
        {
            printf("*** S? DU TÀI KHO?N KHÔNG Ð? Ð? TH?C HI?N GIAO D?CH ***\n\n");
            return;
        }

        //Ki?m tra s? l?n giao d?ch phiên
        if (admin_index >= GIAODICHPHIEN)
        {
            printf("*** QUÁ S? L?N GIAO D?CH PHIÊN ***\n\n");
            return;
        }

        //Ki?m tra s? l?n giao d?ch trong ngày
        if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
        {
            printf("*** QUÁ S? L?N GIAO D?CH TRONG NGÀY ***\n\n");
            return;
        }
        

        //Ki?m tra s? l?n giao d?ch d?i v?i l?ch s? My Account
        if (myAccount ->Data ->TransactionCount >= MAX_TRASACTION_LEN)
        {
            printf(">>>\n\nGIAO D?CH TH?T B?I: VU?T QUÁ S? L?N GIAO D?CH T?I ÐA TRONG L?CH S? GIAO D?CH Ð?I V?I TÀI KHO?N C?A B?N\n\n");
            return;
        }

        int myAccount_current_index = myAccount -> Data -> TransactionCount;

        //Tr? ti?n vào myAccount
        myAccount ->Data -> Balance -= sotienrut;


        //Thêm l?i nh?n vào thông báo
        sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%lld| ND: Rút ti?n t?i ATM", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotienrut); //132

        //Thêm vào danh sách giao d?ch admin
        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
        admin_index +=1;

        //C?ng s? l?n giao d?ch
        myAccount-> Data-> TransactionCount += 1;

        printf("\n\n>>> GIAO D?CH THÀNH CÔNG\n\n");
        return;
    }
}

//Ch?c nang xem tài kho?n
void xemtaikhoan(node myAccount)
{
    char *option[] = {"0. H?y giao d?ch","1. Xem s? du", "2. Xem l?ch s? giao d?ch"};
    int optionCount = sizeof(option) / sizeof(option[0]);

    int i;
    for (i = 0; i< optionCount; i+=1)
    {
        printf("%s  ",option[i]);
    }

    int choice;
    printf("\n\nVui lòng nh?p l?a ch?n c?a b?n: ");
    scanf(" %d", &choice);
    clear_buffer();

    if (choice == 1)
    {
        printf("S? du hi?n t?i: %llu\n\n", myAccount ->Data ->Balance);
        return;
    }
    
    if (choice == 2)
    {
        int index;
        int max_transaction_history = myAccount ->Data ->TransactionCount;
        if (max_transaction_history == 0) printf("B?n chua giao d?ch tru?c dây");
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
    //M?ng con tr?, Nhu?c di?m: Không s?a du?c, Uu di?m: C?p phát dúng b? nh? c?n thi?t
    char *option[] = {"0. H?y giao d?ch","1. G?i ti?n", "2. Chuy?n ti?n", "3. Rút ti?n", "4. Xem tài kho?n"};

    int optionCount = sizeof(option)/ sizeof(option[0]);

    int i;
    for (i = 0; i< optionCount; i+=1)
    {
        printf("%s\n\n",option[i]);
    }

    int choice;
    printf("Nh?p s? l?a ch?n c?a b?n: ");
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

//Hàm dang nh?p v?i vai trò khách
void GuestLogin(node root)
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 3;

    do 
    {
        //nh?p account
        printf("Vui lòng nh?p S? tài kho?n c?a b?n (B?n còn %d l?n nh?p tài kho?n): ", loginCount);
        loginCount -= 1;
        scanf(" %20s", target);
        int clear = clear_buffer();
        
        
        node temp = findNode(root, target);

        //ki?m tra có tìm ra tài kho?n hay không
        if (temp != NULL)
        {
            //Nh?p pin
            char mapin[MAX_PIN_LEN];
            int pinEntryCount = 3;
            do
            {
                printf("Vui lòng nh?p mã Pin (B?n còn %d l?n nh?p)): ", pinEntryCount);
                scanf(" %10s",mapin);
                pinEntryCount-=1;
            } while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0);


            //Ki?m tra mã pin
            if (strcmp(temp ->Data -> Pin, mapin) ==0) 
            {

                //Vào menu
                printf("Vào menu\n\n");
                menu(root, temp);
                return;
            }

            //Ki?m tra s? l?n nh?p
            if (pinEntryCount == 0) 
            {
                printf("\n\n*** H?T S? L?N NH?P MÃ PIN ***\n\n");
                return;
            }
        }
        else
        {
            //Nh?p l?i s? tài kho?n
            printf("\n\n*** Không tìm th?y S? tài kho?n ***\n\n");
            printf("B?n mu?n nh?p l?i S? tài kho?n không? [Y/N]: ");
            scanf(" %c", &yesno);
            clear = clear_buffer();
        } 
    } while (yesno == 'Y' && loginCount > 0);

    if (loginCount == 0) printf("** QUÁ S? L?N NH?P TÀI KHO?N **\n\n");
}

//Hàm dang nh?p v?i vai trò L?p trình viên
void AdministratorLogin(char *shutdown)
{

    char admin_pin[7] = "000000";
    char Pin_Entry[7];
    int Pin_Entry_Count = 3;
    int clear;

    //Nh?p mã b?o m?t
    do 
    {
        printf("Vui lòng nh?p mã b?o m?t c?a Admin (B?n còn %d l?n nh?p): ", Pin_Entry_Count);
        scanf(" %6s", Pin_Entry);
        clear = clear_buffer();
        Pin_Entry_Count -= 1;
    } while ((strcmp(Pin_Entry, admin_pin) != 0 || clear != 0) && Pin_Entry_Count > 0); //Tránh tru?ng h?p ngu?i dùng nh?p du kí t? khi?n buffer hi?u l?m r?ng còn l?n nh?p nhung th?c t? dã h?t l?n nh?p

    //Ki?m tra mã b?o m?t
    if (strcmp(Pin_Entry, admin_pin) == 0 && clear == 0)
    {
        FILE *f =  fopen("output.txt", "w");
        int i = 0;

        for (i = 0; i < admin_index; i+=1)
        {
            fprintf(f ,"%d. S? tài kho?n: %s\n", i+1, TransactionList[i]);
        }

        fclose(f);

        //Chuy?n thành shutdown
        (*shutdown) = 'Y';
    }
    else
    {
        printf("*** QUÁ S? L?N NH?P MÃ B?O M?T ***\n\n");
    }
    return;
}

//Hàm b?t máy ATM
void khoidong(node root)
{
    char ROLE;
    char shutdown = 'N';

    do
    {
    printf("======================================================\n\n");
    printf("* CHÀO M?NG QUÝ KHÁCH Ð?N V?I NGÂN HÀNG Ð?T KHÔNG CHÍN*\n\n");
    printf("======================================================\n\n");

    //ch?n vai trò
    printf("Vai trò c?a b?n là gì [A/G]: ");
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
        else                                 printf("L?i: Vui lòng ch? nh?p A ho?c G!\n");
    }
    else {
        printf("L?i: Vui lòng ch? nh?p A ho?c G!\n");
     }

    } while (shutdown != 'Y');

    printf("K?t thúc chuong trình");
}
int main()
{
    //Cho phép in ti?ng vi?t trong terminal
    SetConsoleOutputCP(CP_UTF8);

    node root = NULL;
    root = input(root);
    khoidong(root);
}
