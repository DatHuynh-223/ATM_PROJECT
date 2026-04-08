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

//them ki tu vao vi tri pos
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