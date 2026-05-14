#include "transactions.h"
// Các hàm hỗ trợ chọn số tiền


long long chonsotienchung(long long hanmuctoida, const char* thongbao, int solanchon_toida, int solannhap_toida) {
    SetConsoleOutputCP(65001); //
    long long arr[8] = {0, 100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    char luachon[100];
    int i = 0, clear = 0;
    int solanchon_cl = solanchon_toida;

    while (solanchon_cl > 0) {
        system("cls");
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
        
        while(1)
            {
                char ch=_getch();
                if (ch == '\r') break;
                else if (ch=='\b')
                {
                    if (idx>0)
                    {
                        idx--;
                        chuoitien[idx]='\0';
                    }
                }
                else if (ch>='0' && ch<='9')
                {
                    if (idx < 15) 
                    {
                        chuoitien[idx++] = ch;
                        chuoitien[idx] = '\0';
                    }
                }
                else continue;
                them_cach(chuoitien,formatted);
                printf("\r\t\t\t\033[14C%-18s", formatted);
                printf("\r\t\t\t\033[%dC", 14 + (int)strlen(formatted));
            }
        chuoitien[idx++]='\n';
        chuoitien[idx]='\0';
        if (chuoitien[0] == '\n') { solannhap_cl--; continue; }
        
        int len = strlen(chuoitien);
        if (chuoitien[len-1] == '\n') { 
            chuoitien[--len] = '\0'; 
            clear = 0; }
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

long long chonsotiengui(node target, node myAccount)
{
    long long hanmuctoida = (target == myAccount) ? 200000000 : 100000000;
    return chonsotienchung(hanmuctoida, "CHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND", 3, 3);
}

long long chonsotienchuyen()
{
    return chonsotienchung(100000000, "Chọn số tiền bạn muốn chuyển:", 3, 3);
}

long long chonsotienrut()
{
    return chonsotienchung(10000000, "Chọn số tiền bạn muốn rút:", 3, 3);
}

 
// Các hàm thực thi giao dịch chính

void guitien(node root, node myAccount)
{
    char filename[50];
    sprintf(filename,"data/Transactions/%s.txt",today());
    FILE *f=fopen(filename,"a");
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
        system("cls");
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
        if (account[0]=='\n')
        {
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
                if (myAccount != targetAccount)
                {
                    do
                    {
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
                        if (message[len-1]=='\n')
                        {
                            message[len-1]='\0';
                            len--;
                        }
                        else
                        {
                            clear_msg = clear_buffer();
                        } 
                    }
                    while (clear_msg == 1 && message_Entry_Count > 0);

                    if (clear_msg == 1)
                    {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                        return;
                    }
                }

                if (admin_index >= GIAODICHPHIEN)
                {
                    printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n"); return;
                    return;
                }

                if (myAccount->Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
                {
                    printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                    return;
                }
                
                if (myAccount == targetAccount)
                {
                    if (myAccount->Data->TransactionCount < MAX_TRANSACTION_LEN)
                    {
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
                        return; 
                    }
                    else
                    {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỬ GIAO DỊCH ***\n\n"); 
                        return;
                    }
                }
                else
                {
                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
                        return;
                    }
                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n\t\t\t***GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN ***\n\n");
                        return;
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
                    return;
                }
            }
        }
        else
        {
            if (AccountEntryCount == 0) break;

            int clear_yn;
            int ynEntryCount = 3;

            do 
            {
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
                        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n"); return;
                        return;
                    }
                    printf("\n\n\t\t\t*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                }
            } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);
            if (yesno == 'N') return;
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    
    if (AccountEntryCount == 0) printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
    fclose(f);
}

void chuyentien(node root, node myAccount)
{
    char filename[50];
    sprintf(filename,"data/Transactions/%s.txt",today());
    FILE *f=fopen(filename,"a");
    char account[MAX_ACC_LEN];
    char yesno = 'Y';
    int AccountEntryCount = 3 ;

    do 
    {
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
        if (account[0]=='\n')
        {
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
            printf("\n\n\t\t\t*** TRÙNG LẶP TÀI KHOẢN NGUỒN ***\n\n");
            
            if (AccountEntryCount == 0) break;

            int clear_yn;
            int ynEntryCount = 3;

            do 
            {
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
                        printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                        return;
                    }
                    printf("\n\n\t\t\t***Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
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
                        system("cls");
                        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
                        printf("\t\t\t║                     NHẬP LỜI NHẮN                      ║\n");
                        printf("\t\t\t╠════════════════════════════════════════════════════════╣\n");
                        
                        char *msg2;
                        if (clear_msg == 1) msg2 = "QUÁ 80 KÍ TỰ! Vui lòng nhập lại";
                        else if (message_Entry_Count == 3) msg2 = "Nhập lời nhắn (Tối đa 80 kí tự, không dấu)";
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
                        if (message[len-1]=='\n')
                        {
                            message[len-1]='\0';
                            len--;
                        }
                        else
                        {
                            clear_msg = clear_buffer();
                        } 
                    }
                while (clear_msg == 1 && message_Entry_Count > 0);

                    if (clear_msg == 1)
                    {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỜI NHẮN. HỦY GIAO DỊCH ***\n\n");
                        return;
                    }

                    if (myAccount->Data->Balance < sotienchuyen)
                    {
                        printf("\n\t\t\t*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
                        return;
                    }

                    if (admin_index >= GIAODICHPHIEN)
                    {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
                        return;
                    }

                    if (myAccount->Data->TransactionCount >= MAX_DAILY_TRANSACTION)
                    {
                        printf("\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
                        return;
                    }

                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
                        return;
                    }

                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN ***\n\n");
                        return;
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
                    return;
                }
            }
            else
            {  
                if (AccountEntryCount == 0) break;
                int clear_yn;
                int ynEntryCount = 3;

                do 
                {
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
                            printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                            return;
                        }
                    }
                } while (((yesno != 'Y' && yesno != 'N') || clear_yn == 1) && ynEntryCount > 0);

                
                if (yesno == 'N') return;
            }
        }
    } while (yesno == 'Y' && AccountEntryCount > 0);
    
    if (AccountEntryCount == 0) printf("\n\t\t\t*** QUÁ SỐ LẦN NHẬP TÀI KHOẢN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
    fclose(f);
}

void ruttien(node root, node myAccount)
{
    char filename[50];
    sprintf(filename,"data/Transactions/%s.txt",today());
    FILE *f=fopen(filename,"a");
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
            printf("\n\n\t\t\t*** SỐ DƯ TÀI KHOẢN KHÔNG ĐỦ ĐỂ THỰC HIỆN GIAO DỊCH ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch phiên
        if (admin_index >= GIAODICHPHIEN)
        {
            printf("\n\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH PHIÊN ***\n\n");
            return;
        }

        //Kiểm tra số lần giao dịch trong ngày
        if (myAccount-> Data->TransactionCount  >= MAX_DAILY_TRANSACTION)
        {
            printf("\n\n\t\t\t*** QUÁ SỐ LẦN GIAO DỊCH TRONG NGÀY ***\n\n");
            return;
        }
        

        //Kiểm tra số lần giao dịch đối với lịch sử My Account
        if (myAccount ->Data ->TransactionCount >= MAX_TRANSACTION_LEN)
        {
            printf("\n\n\t\t\t*** GIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN ***\n\n");
            return;
        }

        int myAccount_current_index = myAccount -> Data -> TransactionCount;

        //Trừ tiền vào myAccount
        myAccount ->Data -> Balance -= sotienrut;
        char sotien[30];
        strcpy(sotien,insert_cham(sotienrut));
        //Thêm lời nhắn vào thông báo
        sprintf(myAccount ->Data ->TransactionHistory[myAccount_current_index], "%s|SD: %llu|-%s VND| ND: Rút tiền tại ATM", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotien); //132

        //Thêm vào danh sách giao dịch admin
        strcpy(TransactionList[admin_index], myAccount ->Data ->TransactionHistory[myAccount_current_index]);
        char info[100];
        sprintf(info, "%s|%llu|-%s", myAccount ->Data ->AccountNumber ,myAccount ->Data ->Balance, sotien); 
        fprintf(f ,"%s\n", info);
        fflush(f);
        admin_index +=1;

        //Cộng số lần giao dịch
        myAccount-> Data-> TransactionCount += 1;

        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║             >>> GIAO DỊCH THÀNH CÔNG <<<               ║\n");
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
        return;
    }
    fclose(f);
}

void xemtaikhoan(node myAccount)
{
    char *option[] = {"0. Hủy giao dịch","1. Xem số dư", "2. Xem lịch sử giao dịch"};
    int optionCount = sizeof(option) / sizeof(option[0]);
    int choice;
    int clear;
    int accEntryCount = 3;
    char *choose = (char*)malloc(sizeof(char)*21);
    printf("\n");
    do 
    {
        system("cls");
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
        
        if (choose[0]=='\n')
        {
            accEntryCount -= 1;
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
            accEntryCount -= 1;
            continue; 
        }
        
        if (choose[0]>='0' && choose[0] <='2')
        {
            choice= choose[0]-'0';
            free(choose);
            break; 
        }
        else
        {
            accEntryCount -= 1;
             continue;
        }

    } while (accEntryCount > 0);
    if (accEntryCount == 0)
            {
                printf("\n\n\t\t\t*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return ;
            }
    printf("\n\n");
    if (choice == 1)
    {
        system("cls");
        char sodu_str[100];
        sprintf(sodu_str, "SỐ DƯ HIỆN TẠI: %s VND", insert_cham(myAccount->Data->Balance));
        printf("\n\n\t\t\t╔════════════════════════════════════════════════════════╗\n");
        printf("\t\t\t║  %-*s║\n", 54 + tinhOffset(sodu_str), sodu_str);
        printf("\t\t\t╚════════════════════════════════════════════════════════╝\n\n");
        return;
    }
    else if (choice == 2)
    {
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
        return;
    }
    else if (choice == 0)
    {
        return;
    }
}