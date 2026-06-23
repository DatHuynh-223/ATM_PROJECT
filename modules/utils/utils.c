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
    return 1; 
}


void insert(char *s,char ch ,int pos,int n)
{
	if (pos >n || pos <0) return ;
	for (int i=n;i>=pos;i--)
	{
		s[i+1]=s[i];
	}
	s[pos]=ch;
}

char* insert_cham(long long n)
{
    static char s[30];
	sprintf(s,"%lld",n);
	int len=strlen(s);
	int x=len-1;
	int dem=0;
	while (x>0)
	{
        dem++;
		if (dem==3)
		{
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

char * today()
{
	time_t rt;
	time(&rt);
	struct tm *info=localtime(&rt);
	static char b[100];
	strftime(b,100,"%A,%d-%m-%Y",info);
	return b;
}
void cr_file(char *filename)
{
	char b[100];
	sprintf(b,"data/Transactions/%s.dat",filename);
	FILE *f=fopen(b,"w+");
	fclose(f);
}
void them_cach(const char* r, char* s) {
    int len=strlen(r);
	int j=0;
	for (int i=0;i<len;i++)
	{
		s[j++]=r[i];
		if ((len-i-1)%3==0 && i != len-1)
		{
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

void nhap_mk(char *pw,int n)
{
	int i=0;
	char ch =0;
	while (1)
	{
		ch=_getch();
		if (ch=='\r')
		{
			pw[i++] = '\n';
            pw[i] = '\0';
			break;
		}
		else if (ch=='O' || ch=='o')
		{
			if (i>0)
			{
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
		}
		else if (ch=='\b')
		{
			if (i>0)
			{
				i--;
                printf("\b \b");
			}
		}
		else if (ch>='0' && ch<='9' && i < 6)
		{
			pw[i++]=ch;
			printf("*"); 
		}
	}
}

	void display_about()
{
	system("cls");
    printf("\n\n");
    printf("\t\t\t╔════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║                 THÔNG TIN HỆ THỐNG ATM                 ║\n");
    printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
	char *lines[] = {
        "Tên dự án : Xây dựng ứng dụng thực hiện giao",
        "            dịch trên máy ATM ",
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
        "Phiên bản : 2.0.0",
        "Ngày HT   : 23 / 6 / 2026"
		};
		int len=sizeof(lines)/sizeof(lines[0]);
		for (int i=0;i<len;i++)
		{
			printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(lines[i]), lines[i]);
		}
	printf("\t\t\t╚════════════════════════════════════════════════════════╝\n");
		

}

void in_tg(int sec)
{
	for (int i=sec;i>0;i--)
	{
		printf("\r\t\t\t*** Vui lòng chờ %d giây ***",i);
		Sleep(1000);
	}
}