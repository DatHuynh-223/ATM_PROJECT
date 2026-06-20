#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

// --- CONSTANTS ---
#define MAX_ACC_LEN 21           
#define MAX_PIN_LEN 11          
#define MAX_DAILY_TRANSACTION 10 
#define MAX_TRANSACTION_LEN 51    
#define INFORM_LEN 201           
#define GIAODICHPHIEN 100        

// --- DATA STRUCTURES ---
typedef struct Account
{
    char AccountNumber[MAX_ACC_LEN];
    char Pin[MAX_PIN_LEN];
    unsigned long long Balance;
    int TransactionCount;
    char TransactionHistory[MAX_TRANSACTION_LEN][INFORM_LEN];
} *Account;

typedef struct TreeNode
{
    struct Account *Data;
    struct TreeNode *left;
    struct TreeNode *right;
} *node;   

// --- GLOBAL VARIABLES ---
char TransactionList[GIAODICHPHIEN][INFORM_LEN];
int admin_index = 0;

// --- FUNCTION PROTOTYPES ---

// Utils
int clear_buffer();
int la_chuoi_so_hop_le(char*str);
void insert(char *s,char ch ,int pos,int n);
char* insert_cham(long long n);
int tinhOffset(const char *s);
void cr_file(char *filename);
char * today();
void them_cach(const char* r, char* s);  
void man_hinh_chao_mung();
void nhap_mk(char *pw,int n);
void display_about();
void in_tg(int sec);

// Account Manager
Account append_account(char *AN, char *PI, unsigned long long BL);
node CreateNode (Account d);
node CreateTree (node root, node a);
node input(node root);
node findNode(node root, char *target);
void ghiFile(node root , FILE *f);
void update_File(node root);

// Transactions
long long chonsotienchung(long long hanmuctoida, const char* thongbao, int solanchon_toida, int solannhap_toida);
long long chonsotiengui(node target, node myAccount);
long long chonsotienchuyen();
long long chonsotienrut();
void guitien(node root, node myAccount);
void chuyentien(node root, node myAccount);
void ruttien(node root, node myAccount);
void xemtaikhoan(node myAccount);

// UI
void menu(node root, node myAccount);
void GuestLogin(node root,char *shutdown);
void AdministratorLogin(char *shutdown);
void khoidong(node root);

// --- IMPLEMENTATIONS ---

// --- Utils (from utils.c) ---
int clear_buffer() {
    int c;
    int temp = 0;
    while ((c = getchar()) != '\n' && c != EOF ) {
        temp = 1;
    }
    return temp;
}

int la_chuoi_so_hop_le(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1; 
}

void insert(char *s,char ch ,int pos,int n) {
	if (pos >n || pos <0) return ;
	for (int i=n;i>=pos;i--) {
		s[i+1]=s[i];
	}
	s[pos]=ch;
}

char* insert_cham(long long n) {
    static char s[30];
	sprintf(s,"%lld",n);
	int len=strlen(s);
	int x=len-1;
	int dem=0;
	while (x>0) {
        dem++;
		if (dem==3) {
			insert(s,'.',x,len);
            len++;  
			dem=0;
		}
		x--;
	}
	return s;
}

int tinhOffset(const char *s) {
    int offset = 0;
    while (*s) {
        if ((*s & 0xc0) == 0x80) offset++; 
        s++;
    }
    return offset;
}

char * today() {
	time_t rt;
	time(&rt);
	struct tm *info=localtime(&rt);
	static char b[100];
	strftime(b,100,"%A,%d-%m-%Y",info);
	return b;
}

void cr_file(char *filename) {
	char b[100];
	sprintf(b,"data/Transactions/%s.dat",filename);
	FILE *f=fopen(b,"w+");
	fclose(f);
}

void them_cach(const char* r, char* s) {
    int len=strlen(r);
	int j=0;
	for (int i=0;i<len;i++) {
		s[j++]=r[i];
		if ((len-i-1)%3==0 && i != len-1) {
			s[j++]='.';
		}
	}
	s[j]='\0';
}

void man_hinh_chao_mung() {
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t\t╔════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║                                                            ║\n");
    printf("\t\t\t║                    HỆ THỐNG GIAO DỊCH ATM                  ║\n");
    printf("\t\t\t║                                                            ║\n");
    printf("\t\t\t║  ████████╗██████╗ ██╗     ██████╗ ██████╗ ██████╗ ███████╗ ║\n");
    printf("\t\t\t║  ╚══██╔══╝██╔══██╗██║    ██╔════╝██╔═══██╗██╔══██╗██╔════╝ ║\n");
    printf("\t\t\t║     ██║   ██████╔╝██║    ██║     ██║   ██║██████╔╝█████╗   ║\n");
    printf("\t\t\t║     ██║   ██╔══██╗██║    ██║     ██║   ██║██╔══██╗██╔══╝   ║\n");
    printf("\t\t\t║     ██║   ██║  ██║██║    ╚██████╗╚██████╔╝██║  ██║███████╗ ║\n");
    printf("\t\t\t║     ╚═╝   ╚═╝  ╚═╝╚═╝     ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ║\n");
    printf("\t\t\t║                                                            ║\n");
    printf("\t\t\t║                    TRI-CORE BANKING SYSTEM                 ║\n");
    printf("\t\t\t║                                                            ║\n");
    printf("\t\t\t╚════════════════════════════════════════════════════════════╝\n");
    printf("\n\n\n");
}

void nhap_mk(char *pw,int n) {
	int i=0;
	char ch =0;
	while (1) {
		ch=_getch();
		if (ch=='\r') {
			pw[i++] = '\n';
            pw[i] = '\0';
			break;
		} else if (ch=='O' || ch=='o') {
			if (i>0) {
                for(int j=0; j<i; j++) {
                    printf("\b \b");
                }
				pw[i]='\0';
				printf("%s",pw);
				Sleep(1000); 
				for(int j=0; j<i; j++) {
					printf("\b \b");
				}
                for(int j=0; j<i; j++) {
					printf("*");
				}
			}
		} else if (ch=='\b') {
			if (i>0) {
				i--;
                printf("\b \b");
			}
		} else if (ch>='0' && ch<='9' && i < 6) {
			pw[i++]=ch;
			printf("*"); 
		}
	}
}

void display_about() {
	system("cls");
    printf("\n\n");
    printf("\t\t\t╔════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║                 THÔNG TIN HỆ THỐNG ATM                 ║\n");
    printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
	char *lines[] = {
        "Tên dự án : Xây dựng ứng dụng thực hiện giao",
        "            dịch trên máy ATM sử dụng cấu trúc",
        "            dữ liệu Cây nhị phân tìm kiếm.",
        "",
        "Mã đề tài : 701, 602",
        "Giảng viên: Trần Hồ Thủy Tiên",
        "",
        "Thực hiện : Thái Nhật Hoàng Ân (MSV: 102250053)",
        "            Huỳnh Tiến Đạt     (MSV: 102250058)",
        "            Lê Viết Huy        (MSV: 102250071)",
        "",
        "Mô tả     : Quản lý tài khoản và giao dịch",
        "            bằng cấu trúc Cây nhị phân tìm kiếm (BST).",
        "",
        "Chức năng : - Đăng nhập Khách và Quản trị viên (Admin)",
        "            - Rút tiền, Gửi tiền, Chuyển khoản",
        "            - Tra cứu số dư và Lịch sử giao dịch",
        "            - Cập nhật và lưu trữ dữ liệu file .dat",
        "",
        "Phiên bản : 1.0.0",
        "Ngày HT   : ... / ... / ......"
	};
	int len=sizeof(lines)/sizeof(lines[0]);
	for (int i=0;i<len;i++) {
		printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(lines[i]), lines[i]);
	}
	printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
}

void in_tg(int sec) {
	for (int i=sec;i>0;i--) {
		printf("\r\t\t\t*** Vui lòng chờ %d giây ***",i);
		Sleep(1000);
	}
}

// --- Account Manager (from account_manager.c) ---
Account append_account(char *AN, char *PI, unsigned long long BL) {
    Account temp = (Account)malloc(sizeof(struct Account));
    strcpy(temp -> AccountNumber,AN);
    strcpy(temp -> Pin, PI);
    temp -> Balance = BL;
    temp ->TransactionCount = 0;
    return temp;
}

node CreateNode (Account d) {
    node temp = (node)malloc(sizeof(struct TreeNode));
    temp -> Data = d;
    temp -> left = NULL;
    temp -> right = NULL; 
    return temp;
}

node CreateTree (node root, node a) {
    if (root ==  NULL) {
        return a;
    }
    int compare = strcmp(a-> Data->AccountNumber, root -> Data -> AccountNumber);
    if (compare >0) root -> right = CreateTree((*root).right, a);
    else if (compare <0) root -> left = CreateTree(root -> left,a);
    else {
        printf("Lỗi trùng lặp số tài khoản %s\n", a-> Data ->AccountNumber);
        free(a->Data);
        free(a);
    }
    return root;
}

node input(node root) {
    FILE *f = fopen("data/account.dat", "r");
    if (f == NULL) {
        printf("Không thể đọc file");
        return root;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        char stk[50];
        char pin[20];
        char thong_tin_thua[50];
        unsigned long long balance;
        int so_luong_doc = sscanf(buffer, " %49s %19s %llu %49s", stk, pin, &balance, thong_tin_thua);
        if (so_luong_doc < 3) continue;
        if (so_luong_doc > 3) continue;
        if (!la_chuoi_so_hop_le(stk) || !la_chuoi_so_hop_le(pin)) continue; 
        if (strlen(stk) > MAX_ACC_LEN-1) continue;
        if (strlen(pin) > MAX_PIN_LEN-1) continue;
        Account temp = append_account(stk, pin, balance);
        root = CreateTree(root,CreateNode(temp));
    }
    fclose(f);
    return root;
}

node findNode(node root, char *target) {
    if (root == NULL) return NULL;
    int compare = strcmp(target, root->Data->AccountNumber);
    if (compare == 0) return root;
    else if (compare == 1) return findNode(root -> right, target);
    else return findNode(root -> left, target);
}

void ghiFile(node root ,FILE *f) {
    if (root != NULL) {
        ghiFile(root -> left, f);
        fprintf(f, "%s %s %llu\n", root -> Data -> AccountNumber, root -> Data -> Pin, root -> Data -> Balance);
        ghiFile(root -> right, f);
    }
}

void update_File(node root) {
    FILE *f = fopen("data/account.dat", "w");
    ghiFile(root, f);
    fclose(f);
}

// --- Transactions (from transactions.c) ---
long long chonsotienchung(long long hanmuctoida, const char* thongbao, int solanchon_toida, int solannhap_toida) {
    SetConsoleOutputCP(65001); 
    long long arr[8] = {0, 100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    char luachon[100];
    int i = 0, clear = 0;
    int solanchon_cl = solanchon_toida;

    while (solanchon_cl > 0) {
        system("cls");
        memset(luachon, 0, sizeof(luachon));
        printf("\n\n\t\t  %s\n\n", thongbao);
        printf("\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║ 1. 100.000 VND            ║ 2. 200.000 VND             ║\n");
        printf("\t\t\t║ 3. 500.000 VND            ║ 4. 1.000.000 VND           ║\n");
        printf("\t\t\t║ 5. 2.000.000 VND          ║ 6. 3.000.000 VND           ║\n");
        printf("\t\t\t║ 7. Số khác                ║ 0. Hủy giao dịch           ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");

        char *msg;
        if (solanchon_cl == solanchon_toida) msg = "Vui lòng chọn số từ 0 đến 7";
        else if (solanchon_cl > 1) {
            static char buf[100];
            sprintf(buf, "Lựa chọn sai! Bạn còn %d lần nhập", solanchon_cl);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";

        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  Nhập lựa chọn của bạn: [   ]                          ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[28C"); 

        if (fgets(luachon, sizeof(luachon), stdin) == NULL) continue;
        if (luachon[0] == '\n') { solanchon_cl--; continue; }
        int len = strlen(luachon);
        if (luachon[len - 1] == '\n') { luachon[--len] = '\0'; clear = 0; }
        else clear = clear_buffer();
        if (len > 1 || clear == 1 || luachon[0] < '0' || luachon[0] > '7') {
            solanchon_cl--; continue;
        }
        i = luachon[0] - '0'; break;
    }

    if (solanchon_cl == 0) return 0;
    if (i == 0) { printf("\n\n"); return 0; }
    if (i != 7) { printf("\n\n"); return arr[i]; }

    int solannhap_cl = solannhap_toida;
    while (solannhap_cl > 0) {
        system("cls");
        char hanmuc_full[100];
        sprintf(hanmuc_full, "Hạn mức tối đa: %s VND", insert_cham(hanmuctoida));
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(hanmuc_full), hanmuc_full);
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *info;
        if (solannhap_cl == solannhap_toida) info = "Vui lòng nhập bội số của 50.000 VND";
        else if (solannhap_cl > 1) {
            static char buf2[100];
            sprintf(buf2, "Số tiền không hợp lệ! Còn %d lần", solannhap_cl);
            info = buf2;
        } else info = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(info), info);
        printf("\t\t\t║  Số tiền: [                  ] VND                     ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[14C"); 

        char chuoitien[30] = "";
        char formatted[50] = "";
        int idx = 0;
        while(1) {
            char ch=_getch();
            if (ch == '\r') break;
            else if (ch=='\b') {
                if (idx>0) {
                    idx--;
                    chuoitien[idx]='\0';
                }
            } else if (ch>='0' && ch<='9') {
                if (idx < 15) {
                    chuoitien[idx++] = ch;
                    chuoitien[idx] = '\0';
                }
            } else continue;
            them_cach(chuoitien,formatted);
            printf("\r\t\t\t\033[14C%-18s", formatted);
            printf("\r\t\t\t\033[%dC", 14 + (int)strlen(formatted));
        }
        chuoitien[idx++]='\n';
        chuoitien[idx]='\0';
        if (chuoitien[0] == '\n') { solannhap_cl--; continue; }
        int len = strlen(chuoitien);
        if (chuoitien[len-1] == '\n') { chuoitien[--len] = '\0'; clear = 0; }
        else clear = clear_buffer();
        long long sotien = atoll(chuoitien);
        if (sotien % 50000 != 0 || sotien > hanmuctoida || sotien <= 0 || clear == 1) {
            solannhap_cl--;
        } else {
            printf("\n\n"); 
            return sotien;
        }
    }
    return 0;
}

long long chonsotiengui(node target, node myAccount) {
    long long hanmuctoida = (target == myAccount) ? 200000000 : 100000000;
    return chonsotienchung(hanmuctoida, "CHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND", 3, 3);
}

long long chonsotienchuyen() {
    return chonsotienchung(100000000, "Chọn số tiền bạn muốn chuyển:", 3, 3);
}

long long chonsotienrut() {
    return chonsotienchung(10000000, "Chọn số tiền bạn muốn rút:", 3, 3);
}

void guitien(node root, node myAccount) {
    char filename[50];
    sprintf(filename,"data/Transactions/%s.dat",today());
    FILE *f=fopen(filename,"a");
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;
    do {
        system("cls");
        memset(account, 0, sizeof(account)); 
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                 GỬI TIỀN VÀO TÀI KHOẢN                 ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (AccountEntryCount == 3) msg = "Vui lòng nhập số tài khoản bạn muốn gửi";
        else if (AccountEntryCount > 1) {
            static char buf[100];
            sprintf(buf, "Tài khoản sai! Bạn còn %d lần nhập", AccountEntryCount);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  Số tài khoản: [                  ]                    ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[19C");
        AccountEntryCount -= 1;
        if (fgets(account,sizeof(account),stdin)==NULL) continue;
        int len=strlen(account);
        if (account[0]=='\n') continue;
        if (account[len-1]=='\n') account[len-1]='\0';
        else clear_buffer();

        node targetAccount = findNode(root, account);
        if (targetAccount != NULL) {
            long long sotiengui = chonsotiengui(targetAccount, myAccount);
            if (sotiengui == 0) { fclose(f); return ; }
            else if  (sotiengui != 0) {
                char message[81]; 
                int message_Entry_Count = 3;
                int clear_msg = 0;
                if (myAccount != targetAccount) {
                    do {
                        system("cls");
                        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                        printf("\t\t\t║                     NHẬP LỜI NHẮN                      ║\n");
                        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                        char *msg2;
                        if (clear_msg == 1) msg2 = "QUÁ 80 KÍ TỰ! Vui lòng nhập lại";
                        else if (message_Entry_Count == 3) msg2 = "Nhập lời nhắn (Tối đa 80 kí tự)";
                        else if (message_Entry_Count > 1) {
                            static char buf2[100];
                            sprintf(buf2, "Lỗi! Bạn còn %d lần nhập", message_Entry_Count);
                            msg2 = buf2;
                        } else msg2 = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
                        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg2), msg2);
                        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                        printf("\t\t\t  >> ");
                        message_Entry_Count -= 1;
                        if (fgets(message,sizeof(message),stdin)==NULL) continue;
                        int len=strlen(message);
                        if (message[len-1]=='\n') { message[len-1]='\0'; len--; }
                        else clear_msg = clear_buffer();
                    } while (clear_msg == 1 && message_Entry_Count > 0);
                    if (clear_msg == 1) {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                        fclose(f); return;
                    }
                }
                if (admin_index >= GIAODICHPHIEN) {
                    printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n"); fclose(f); return;
                }
                if (myAccount->Data->TransactionCount  >= MAX_DAILY_TRANSACTION) {
                    printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n"); fclose(f); return;
                }
                if (myAccount == targetAccount) {
                    if (myAccount->Data->TransactionCount < MAX_TRANSACTION_LEN) {
                        int current_index = myAccount->Data->TransactionCount;
                        myAccount->Data->Balance += sotiengui;
                        char sotien[30];
                        strcpy(sotien,insert_cham(sotiengui));
                        sprintf(myAccount->Data->TransactionHistory[current_index], "%s|SD: %llu|+%s VND|ND: Gui tien tai ATM", myAccount->Data->AccountNumber ,myAccount->Data->Balance,sotien);
                        strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[current_index]);
                        char info[100];
                        sprintf(info, "%s|%llu|+%s", myAccount->Data->AccountNumber ,myAccount->Data->Balance,sotien);
                        fprintf(f ,"%s\n", info);
                        fflush(f);  
                        admin_index +=1;
                        myAccount->Data->TransactionCount += 1;
                        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                        printf("\t\t\t║             >>> GIAO DỊCH THÀNH CÔNG <<<               ║\n");
                        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
                        fclose(f); return; 
                    } else {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỬ GIAO DỊCH ***\n\n"); 
                        fclose(f); return;
                    }
                } else {
                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN) {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
                        fclose(f); return;
                    }
                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN) {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN ***\n\n");
                        fclose(f); return;
                    }
                    int targetAccount_current_index = targetAccount->Data->TransactionCount;
                    int myAccount_current_index = myAccount->Data->TransactionCount;
                    targetAccount->Data->Balance += sotiengui;
                    char sotien[30];
                    strcpy(sotien,insert_cham(sotiengui));
                    sprintf(myAccount->Data->TransactionHistory[myAccount_current_index], "%s|SD: %llu|GUI %s VND|DEN %s|ND: %s", myAccount->Data->AccountNumber,myAccount->Data->Balance, sotien, targetAccount->Data->AccountNumber,message);
                    sprintf(targetAccount->Data->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%s VND|TU: %s|ND: %s", targetAccount->Data->AccountNumber, targetAccount->Data->Balance,sotien, myAccount->Data->AccountNumber, message);
                    strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[myAccount_current_index]);
                    fprintf(f ,"%d. Số tài khoản: %s\n", admin_index + 1, TransactionList[admin_index]);
                    fflush(f); 
                    admin_index +=1;
                    myAccount->Data->TransactionCount += 1;
                    targetAccount->Data->TransactionCount += 1;
                    printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                    printf("\t\t\t║             >>> GIAO DỊCH THÀNH CÔNG <<<               ║\n");
                    printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
                    fclose(f); return;
                }
            }
        } else {
            if (AccountEntryCount == 0) break;
            int clear_yn;
            int ynEntryCount = 3;
            do {
                char *msg_yn;
                printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                printf("\t\t\t║            KHÔNG TÌM THẤY TÀI KHOẢN ĐÍCH!              ║\n");
                printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                if (ynEntryCount == 3) msg_yn = "Bạn có muốn nhập lại STK không? (Y/N)";
                else if (ynEntryCount > 1) {
                    static char buf_yn[100];
                    sprintf(buf_yn, "Lỗi! Bạn còn %d lần nhập (Y/N)", ynEntryCount);
                    msg_yn = buf_yn;
                } else msg_yn = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
                printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg_yn), msg_yn);
                printf("\t\t\t║  Lựa chọn: [   ]                                       ║\n");
                printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                printf("\033[2A\r\t\t\t\033[15C");
                if (scanf("%c", &yesno) != 1) { ynEntryCount--; continue; }
                if (yesno=='\n') { ynEntryCount--; continue; } 
                clear_yn = clear_buffer();
                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1) {
                    ynEntryCount -= 1;
                    if (ynEntryCount == 0) {
                        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n"); fclose(f); return;
                    }
                    printf("\n\n\t\t\t*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
            if (yesno == 'N') { fclose(f); return; }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
    fclose(f);
}

void chuyentien(node root, node myAccount) {
    char filename[50];
    sprintf(filename,"data/Transactions/%s.dat",today());
    FILE *f=fopen(filename,"a");
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;
    do {
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                  CHUYỂN KHOẢN                          ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (AccountEntryCount == 3) msg = "Vui lòng nhập số tài khoản nhận tiền";
        else if (AccountEntryCount > 1) {
            static char buf[100];
            sprintf(buf, "Tài khoản sai! Bạn còn %d lần nhập", AccountEntryCount);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  Số tài khoản: [                  ]                    ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[19C");
        AccountEntryCount -= 1;
        if (fgets(account,sizeof(account),stdin)==NULL) continue;
        int len=strlen(account);
        if (account[0]=='\n') continue;
        if (account[len-1]=='\n') account[len-1]='\0';
        else clear_buffer();
        if (strcmp(account, myAccount->Data->AccountNumber) == 0) {
            printf("\n\n\t\t\t*** TRÙNG LẶP TÀI KHOẢN NGUỒN ***\n\n");
            if (AccountEntryCount == 0) break;
            int clear_yn;
            int ynEntryCount = 3;
            do {
                printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                char *msg_yn;
                if (ynEntryCount == 3) msg_yn = "Bạn có muốn nhập lại STK không? (Y/N)";
                else if (ynEntryCount > 1) {
                    static char buf_yn[100];
                    sprintf(buf_yn, "Lỗi! Bạn còn %d lần nhập (Y/N)", ynEntryCount);
                    msg_yn = buf_yn;
                } else msg_yn = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
                printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg_yn), msg_yn);
                printf("\t\t\t║  Lựa chọn: [   ]                                       ║\n");
                printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                printf("\033[2A\r\t\t\t\033[15C");
                if (scanf("%c", &yesno) != 1) { ynEntryCount--; continue; }
                if (yesno=='\n') { ynEntryCount--; continue; } 
                clear_yn = clear_buffer();
                if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1) {
                    ynEntryCount -= 1;
                    if (ynEntryCount == 0) {
                        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n"); fclose(f); return;
                    }
                    printf("\n\n\t\t\t***Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
            if (yesno == 'N') { fclose(f); return; }
        } else {
            node targetAccount = findNode(root, account);
            if (targetAccount != NULL) {
                long long sotienchuyen = chonsotienchuyen();
                if (sotienchuyen == 0) { fclose(f); return; }
                else if  (sotienchuyen != 0) {
                    char message[81];
                    int message_Entry_Count = 3;
                    int clear_msg = 0;
                    do {
                        system("cls");
                        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                        printf("\t\t\t║                     NHẬP LỜI NHẮN                      ║\n");
                        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                        char *msg2;
                        if (clear_msg == 1) msg2 = "QUÁ 80 KÍ TỰ! Vui lòng nhập lại";
                        else if (message_Entry_Count == 3) msg2 = "Nhập lời nhắn (Tối đa 80 kí tự)";
                        else if (message_Entry_Count > 1) {
                            static char buf2[100];
                            sprintf(buf2, "Lỗi! Bạn còn %d lần nhập", message_Entry_Count);
                            msg2 = buf2;
                        } else msg2 = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
                        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg2), msg2);
                        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                        printf("\t\t\t  >> ");
                        message_Entry_Count -= 1;
                        if (fgets(message,sizeof(message),stdin)==NULL) continue;
                        int len=strlen(message);
                        if (message[len-1]=='\n') { message[len-1]='\0'; len--; }
                        else clear_msg = clear_buffer();
                    } while (clear_msg == 1 && message_Entry_Count > 0);
                    if (clear_msg == 1) {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                        fclose(f); return;
                    }
                    if (myAccount->Data->Balance < sotienchuyen) {
                        printf("\n\t\t\t*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
                        fclose(f); return;
                    }
                    if (admin_index >= GIAODICHPHIEN) {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                        fclose(f); return;
                    }
                    if (myAccount->Data->TransactionCount >= MAX_DAILY_TRANSACTION) {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                        fclose(f); return;
                    }
                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN) {
                        printf("\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
                        fclose(f); return;
                    }
                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN) {
                        printf("\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN ***\n\n");
                        fclose(f); return;
                    }
                    int targetAccount_current_index = targetAccount->Data->TransactionCount;
                    int myAccount_current_index = myAccount->Data->TransactionCount;
                    myAccount->Data->Balance -= sotienchuyen;
                    targetAccount->Data->Balance += sotienchuyen;
                    char sotien[30];
                    strcpy(sotien,insert_cham(sotienchuyen));
                    sprintf(myAccount->Data->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%s VND|DEN: %s|ND: %s", myAccount->Data->AccountNumber ,myAccount->Data->Balance ,sotien, targetAccount ->Data ->AccountNumber ,message);
                    sprintf(targetAccount->Data->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%s VND|TU: %s|ND: %s", targetAccount->Data->AccountNumber ,targetAccount->Data->Balance,sotien, myAccount->Data ->AccountNumber ,message);
                    strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[myAccount_current_index]);
                    char info[100];
                    sprintf(info, "%s|%llu|-%s|%s", myAccount->Data->AccountNumber ,myAccount->Data->Balance ,sotien, targetAccount ->Data ->AccountNumber );
                    fprintf(f ,"%s\n", info);
                    fflush(f);
                    admin_index +=1;
                    myAccount->Data->TransactionCount += 1;
                    targetAccount->Data->TransactionCount += 1;
                    printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                    printf("\t\t\t║             >>> GIAO DỊCH THÀNH CÔNG <<<               ║\n");
                    printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
                    fclose(f); return;
                }
            } else {  
                if (AccountEntryCount == 0) break;
                int clear_yn;
                int ynEntryCount = 3;
                do {
                    system("cls");
                    printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                    printf("\t\t\t║            KHÔNG TÌM THẤY TÀI KHOẢN ĐÍCH!              ║\n");
                    printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                    char *msg_yn;
                    if (ynEntryCount == 3) msg_yn = "Bạn có muốn nhập lại STK không? (Y/N)";
                    else msg_yn = "Lựa chọn sai! Nhập lại (Y/N)";
                    printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg_yn), msg_yn);
                    printf("\t\t\t║  Lựa chọn: [   ]                                       ║\n");
                    printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                    printf("\033[2A\r\t\t\t\033[15C");
                    if (scanf("%c", &yesno) != 1) { ynEntryCount--; continue; }
                    if (yesno=='\n') { ynEntryCount--; continue; } 
                    clear_yn = clear_buffer();
                    if ((yesno != 'Y' && yesno != 'N') || clear_yn == 1) {
                        ynEntryCount -= 1;
                        if (ynEntryCount == 0) {
                            printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                            fclose(f); return;
                        }
                    }
                } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
                if (yesno == 'N') { fclose(f); return; }
            }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    if (AccountEntryCount == 0) printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
    fclose(f);
}

void ruttien(node root, node myAccount) {
    char filename[50];
    sprintf(filename,"data/Transactions/%s.dat",today());
    FILE *f=fopen(filename,"a");
    long long sotienrut = chonsotienrut();
    if (sotienrut == 0) { fclose(f); return; }
    else if  (sotienrut != 0) {
        if (myAccount ->Data ->Balance < sotienrut) {
            printf("\n\n\t\t\t*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
            fclose(f); return;
        }
        if (admin_index >= GIAODICHPHIEN) {
            printf("\n\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
            fclose(f); return;
        }
        if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION) {
            printf("\n\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
            fclose(f); return;
        }
        if (myAccount ->Data ->TransactionCount >= MAX_TRANSACTION_LEN) {
            printf("\n\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
            fclose(f); return;
        }
        int myAccount_current_index = myAccount -> Data -> TransactionCount;
        myAccount ->Data -> Balance -= sotienrut;
        char sotien[30];
        strcpy(sotien,insert_cham(sotienrut));
        sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%s VND| ND: Rút tiền tại ATM", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotien); 
        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
        char info[100];
        sprintf(info, "%s|%llu|-%s", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotien); 
        fprintf(f ,"%s\n", info);
        fflush(f);
        admin_index +=1;
        myAccount-> Data-> TransactionCount += 1;
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║             >>> GIAO DỊCH THÀNH CÔNG <<<               ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
        fclose(f); return;
    }
    fclose(f);
}

void xemtaikhoan(node myAccount) {
    int choice;
    int clear;
    int accEntryCount = 3;
    char *choose = (char*)malloc(sizeof(char)*21);
    printf("\n");
    do {
        system("cls");
        memset(choose, 0, sizeof(choose));
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                  THÔNG TIN TÀI KHOẢN                   ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        printf("\t\t\t║ 1. Xem số dư hiện tại                                  ║\n");
        printf("\t\t\t║ 2. Xem lịch sử giao dịch                               ║\n");
        printf("\t\t\t║ 0. Quay lại menu chính                                 ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (accEntryCount == 3) msg = "Vui lòng chọn chức năng từ 0 đến 2";
        else if (accEntryCount > 1) {
            static char buf[100];
            sprintf(buf, "Lựa chọn sai! Bạn còn %d lần nhập", accEntryCount);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  Nhập lựa chọn của bạn: [   ]                          ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[28C"); 
        if (fgets(choose,sizeof(choose),stdin)==NULL) continue;
        if (choose[0]=='\n') { accEntryCount -= 1; continue; }
        int len = strlen(choose);
        clear = 0;
        if (choose[len-1]=='\n') { choose[len-1]='\0'; len--; }
        else { clear = clear_buffer(); }
        if (len > 1 || clear == 1) { accEntryCount -= 1; continue; }
        if (choose[0]>='0' && choose[0] <='2') {
            choice= choose[0]-'0';
            break; 
        } else { accEntryCount -= 1; continue; }
    } while (accEntryCount > 0);
    free(choose);
    if (accEntryCount == 0) {
        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
        return ;
    }
    printf("\n\n");
    if (choice == 1) {
        system("cls");
        char sodu_str[100];
        sprintf(sodu_str, "SỐ DƯ HIỆN TẠI: %s VND", insert_cham(myAccount->Data->Balance));
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(sodu_str), sodu_str);
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
    } else if (choice == 2) {
        system("cls");
        int max_history = myAccount->Data->TransactionCount;
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                   LỊCH SỬ GIAO DỊCH                    ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        if (max_history == 0) {
            printf("\t\t\t║  Bạn chưa có giao dịch nào trước đây                   ║\n");
        } else {
            for (int index = 0; index < max_history; index += 1) {
                printf("\t\t\t  [%d]. %s\n", index+1, myAccount->Data->TransactionHistory[index]);
            }
        }
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
    }
}

// --- UI (from atm_ui.c) ---
void menu(node root, node myAccount) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    char *option[] = {"0. Thoát", "1. Gửi tiền", "2. Chuyển tiền", "3. Rút tiền", "4. Xem tài khoản"};
    int optionCount = sizeof(option)/ sizeof(option[0]);
    while (1) {
        int menuEntryCount = 4;
        int choice = -1;
        char input[100];
        int clear = 0;
        while (menuEntryCount > 0) {
            memset(input, 0, sizeof(input));
            system("cls");
            printf("\n\n");
            printf("\t\t\t╔════════════════════════════════════════════════════════╗\n"); 
            printf("\t\t\t║                     MENU GIAO DỊCH                     ║\n");
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            for (int i = 1; i < optionCount; i++) {
                printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(option[i]), option[i]);
            }
            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(option[0]), option[0]);
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            char *msg;
            if (menuEntryCount == 4) msg = "Vui lòng chọn chức năng từ 0 đến 4";
            else if (menuEntryCount > 1) {
                static char buf[100];
                sprintf(buf, "Lựa chọn sai! Bạn còn %d lần nhập", menuEntryCount);
                msg = buf;
            } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
            printf("\t\t\t║  Nhập lựa chọn của bạn: [   ]                          ║\n");
            printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
            printf("\033[2A\r\t\t\t\033[28C");
            if (fgets(input, sizeof(input), stdin) == NULL) continue;
            if (input[0] == '\n') { menuEntryCount--; continue; }
            int len = strlen(input);
            clear = 0;
            if (input[len - 1] == '\n') { input[len - 1] = '\0'; len--; }
            else { clear = clear_buffer(); }
            if (len > 1 || clear == 1 || input[0] < '0' || input[0] > '4') { menuEntryCount--; continue; }
            choice = input[0] - '0';
            break;
        }
        if (menuEntryCount == 0) {
            printf("\n\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
            return; 
        }
        printf("\n\n");
        switch (choice) {
            case 1: guitien(root, myAccount); break;
            case 2: chuyentien(root, myAccount); break;
            case 3: ruttien(root, myAccount); break;
            case 4: xemtaikhoan(myAccount); break;
            case 0: 
            default:
                printf("\t\tĐã hủy / Kết thúc giao dịch. \n");
                return; 
        }
        char yn_input[100];
        int ynEntryCount = 3;
        int clear_yn;
        char yn = 'X';
        while (ynEntryCount > 0) {
            memset(yn_input, 0, sizeof(yn_input));
            printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
            printf("\t\t\t║              BẠN CÓ MUỐN TIẾP TỤC GIAO DỊCH KHÔNG?     ║\n");
            printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
            char *yn_msg;
            if (ynEntryCount == 3) yn_msg = "Nhập Y (Có) hoặc N (Không)";
            else if (ynEntryCount > 1) {
                static char yn_buf[100];
                sprintf(yn_buf, "Lựa chọn sai! Bạn còn %d lần nhập", ynEntryCount);
                yn_msg = yn_buf;
            } else yn_msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
            printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(yn_msg), yn_msg);
            printf("\t\t\t║  Lựa chọn của bạn: [   ]                               ║\n");
            printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
            printf("\033[2A\r\t\t\t\033[23C"); 
            if (fgets(yn_input, sizeof(yn_input), stdin) == NULL) continue;
            if (yn_input[0] == '\n') { ynEntryCount--; printf("\n\n"); continue; } 
            int len = strlen(yn_input);
            clear_yn = 0;
            if (yn_input[len - 1] == '\n') { yn_input[len - 1] = '\0'; len--; }
            else { clear_yn = clear_buffer(); }
            if (len > 1 || clear_yn == 1) { ynEntryCount--; printf("\n\n"); continue; }
            yn = yn_input[0];
            if (yn == 'Y' || yn == 'y' || yn == 'N' || yn == 'n') { printf("\n\n"); break; }
            ynEntryCount--;
            printf("\n\n");
        }
        if (ynEntryCount == 0) { printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n"); return; }
        if (yn == 'N' || yn == 'n') { printf("\n\t\t\t*** CẢM ƠN QUÝ KHÁCH ĐÃ SỬ DỤNG DỊCH VỤ ***\n\n"); return; }
    }
}

void GuestLogin(node root,char *shutdown ) {
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 4;
    char stk_Admin[MAX_ACC_LEN]="06121234";
    char shutdown1='N';
    int KT=0;
    do {
        if (KT) loginCount = 4;
        memset(target, 0, sizeof(target));
        man_hinh_chao_mung();
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║        VUI LÒNG ĐĂNG NHẬP ĐỂ BẮT ĐẦU GIAO DỊCH             ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (loginCount == 4) msg = "";
        else if (loginCount > 1) {
            static char buf[100];
            sprintf(buf, "Tài khoản sai! Bạn còn %d lần nhập", loginCount);
            msg = buf;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 58 + tinhOffset(msg), msg);
        printf("\t\t\t║  Số tài khoản: [                  ]                        ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[19C"); 
        loginCount -= 1;
        if (fgets(target,sizeof(target),stdin)==NULL) continue;
        if (target[0]=='\n') continue;
        int len = strlen(target);
        if (target[len - 1] == '\n') target[len - 1] = '\0'; 
        else clear_buffer();
        if (strcmp(target,stk_Admin)==0) {
            KT=1;
            AdministratorLogin(&shutdown1);
            (*shutdown)=shutdown1;
            if (*shutdown == 'Y') return; 
        } else {
            node temp = findNode(root, target);
            if (temp != NULL) {
                KT=1;
                char mapin[10];
                int pinEntryCount = 4;
                do {
                    system("cls");
                    memset(mapin, 0, sizeof(mapin));
                    printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                    printf("\t\t\t║                  XÁC THỰC TÀI KHOẢN                    ║\n");
                    printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                    char *pin_msg;
                    if (pinEntryCount == 4) pin_msg = "Vui lòng nhập mã PIN (6 số)";
                    else if (pinEntryCount > 1) {
                        static char p_buf[100];
                        sprintf(p_buf, "Sai mã PIN! Bạn còn %d lần nhập", pinEntryCount);
                        pin_msg = p_buf;
                    } else pin_msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
                    printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(pin_msg), pin_msg);
                    printf("\t\t\t║  (O:hiện) Mã PIN:                                      ║\n");
                    printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
                    printf("\033[2A\r\t\t\t\033[20C");
                    pinEntryCount-=1;
                    nhap_mk(mapin, 10);
                    if (strlen(mapin) == 0) continue;
                    int len=strlen(mapin);
                    if (mapin[len-1]=='\n') mapin[len-1]='\0';
                    else clear_buffer();
                } while (strcmp(temp ->Data -> Pin, mapin ) !=0 && pinEntryCount>0);
                if (strcmp(temp ->Data -> Pin, mapin) ==0) {
                    printf("\n\n");
                    menu(root, temp);
                    return;
                }
                if (pinEntryCount == 0) {
                    printf("\n\n\t\t\t*** HẾT SỐ LẦN NHẬP MÃ PIN! ***\n\n");
                    Sleep(1500);
                    return;
                }
            } else {
                printf("\n\n\t\t\t*** KHÔNG TÌM THẤY SỐ TÀI KHOẢN ***\n\n");
                Sleep(1000);
            } 
        }
    } while ( loginCount > 0);
    if (loginCount == 0) {
        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. KHÓA TẠM THỜI! ***\n\n");
        in_tg(2);
    }
}

void AdministratorLogin(char *shutdown) {
    char admin_pin[7] = "000000";
    char Pin_Entry[10];
    int Pin_Entry_Count = 4;
    int clear=0;
    do {
        clear=0;
        memset(Pin_Entry, 0, sizeof(Pin_Entry)); 
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                 CHÀO MỪNG QUẢN TRỊ VIÊN                ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (Pin_Entry_Count == 4) msg = "Vui lòng nhập mã bảo mật Admin để tắt máy";
        else if (Pin_Entry_Count > 1) {
            static char a[100];
            sprintf(a, "Sai mã bảo mật! Bạn còn %d lần nhập", Pin_Entry_Count);
            msg = a;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(msg), msg);
        printf("\t\t\t║  (O:hiện) Mã bảo mật:                                  ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[25C");
        Pin_Entry_Count -= 1;
		nhap_mk(Pin_Entry, 10); 
        if (strlen(Pin_Entry) == 0) continue;
        if (Pin_Entry[0]=='\n') continue;
        int len = strlen(Pin_Entry);
        if (Pin_Entry[len - 1] == '\n') Pin_Entry[len - 1] = '\0'; 
        else clear = clear_buffer(); 
        if (strcmp(Pin_Entry, admin_pin) != 0) continue;
    } while ((strcmp(Pin_Entry, admin_pin) != 0 || clear != 0) && Pin_Entry_Count >= 0);
    if (strcmp(Pin_Entry, admin_pin) == 0 && clear == 0) (*shutdown) = 'Y';
    else {
        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP MÃ BẢO MẬT. ! ***\n\n");
        in_tg(2);
    }
}

void khoidong(node root) {
    system("cls");
    char shutdown = 'N';
    int clear=0;
    int passEntryCount = 4;
    char pass[10];
    char admin_pass[7]="000000";
    int KT=0;
    do {
        system("cls");
        memset(pass, 0, sizeof(pass)); 
        display_about();
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║                      HỆ THỐNG ATM                      ║\n");
        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
        char *msg;
        if (passEntryCount == 4) msg = "Vui lòng nhập mã bảo mật Admin để bật máy";
        else if (passEntryCount > 1) {
            static char b[100];
            sprintf(b, "Sai mã bảo mật! Còn %d lần nhập", passEntryCount);
            msg = b;
        } else msg = "*** ĐÂY LÀ LẦN NHẬP CUỐI CÙNG !!! ***";
        printf("\t\t\t║  %-*s║\n", 54+tinhOffset(msg) , msg);
        printf("\t\t\t║  (O:hiện) Mã bảo mật:                                  ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
        printf("\033[2A\r\t\t\t\033[25C");
        passEntryCount -= 1;
        nhap_mk(pass, 10);
        if (strlen(pass) == 0) continue;
        if (pass[0]=='\n') continue;
        int len = strlen(pass);
        if (pass[len - 1] == '\n') pass[len - 1] = '\0'; 
        else clear = clear_buffer(); 
        if (strlen(pass)<6 || strcmp(pass, admin_pass) != 0 ) continue;
    } while ((strcmp(pass, admin_pass) != 0 || clear != 0) && passEntryCount > 0);

    if (strcmp(pass, admin_pass) == 0 && clear == 0) {
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║           >>> KHỞI ĐỘNG HỆ THỐNG THÀNH CÔNG <<<        ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
        KT=1;
        Sleep(1500);
    } else {
        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP MÃ BẢO MẬT. SHUTTING DOWN... ***\n\n");
    }
    if (KT) {
        char *today_str = today();
        cr_file(today_str);
        do { GuestLogin(root,&shutdown); } while (shutdown != 'Y');
        system("cls");
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║          MÁY ĐANG TẮT... CẢM ƠN QUÝ KHÁCH!             ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
    }
}

// --- MAIN ---
int main() {
    SetConsoleOutputCP(CP_UTF8); 
    SetConsoleCP(CP_UTF8);
    node root=NULL;
    root=input(root);
    if (root != NULL) {
        khoidong(root);
    } else {
        printf("\n[CẢNH CÁO ] Hệ thống không có dữ liệu tài khoản để hoạt động.\n");
        printf("Vui lòng kiểm tra file 'account.dat'!\n");
    }
    update_File(root);
    return 0;
}
