#include "transactions.h"
// Các hàm hỗ trợ chọn số tiền

//Hàm chọn số tiền gửi đi
long long chonsotiengui(node target, node myAccount)
{
    long long hanmuctoida;
    if (target == myAccount) hanmuctoida = 200000000;
    else hanmuctoida = 100000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    char in[8][100]={"00","100.000","200.000","500.000","1.000.000","2.000.000","3.000.000","00"};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;
    char choose[100];

    printf("\nCHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");
        
    int j = 0;
    for (j = 0; j < 8; j++)
    {
        if (j == 0) printf("%d. Hủy giao dịch hiện tại        ", j);
        else if (j == 7) printf("%d. Số khác\n\n", j);
        else
        {
            printf("%d. %s VND       ",j,in[j]);
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
        printf("Hạn mức tối đa là : %s VND\n\n", insert_cham(hanmuctoida));

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

//Hàm chọn số tiền chuyển đi
long long chonsotienchuyen()
{
    long long hanmuctoida = 100000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    char in[8][100]={"00","100.000","200.000","500.000","1.000.000","2.000.000","3.000.000","00"};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;
    char choose[2];

    printf("\nCHỈ NHẬN MỆNH GIÁ 50.000 VND, 100.000 VND, 200.000 VND, 500.000 VND\n\n");

        int j = 0;
        for (j = 0; j < 8; j++)
        {
            if (j == 0) printf("%d. Hủy giao dịch hiện tại        ", j);
            else if (j == 7) printf("%d. Số khác\n\n", j);
            else
            {
                printf("%d. %s VND       ",j,in[j]);
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
        printf("Hạn mức tối đa là : %s VND\n\n", "10.000.000");

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

//Hàm chọn số tiền rút
long long chonsotienrut()
{
    long long hanmuctoida = 10000000;
    
    long long arr[8] = {0 ,100000, 200000, 500000, 1000000, 2000000, 3000000, 0};
    char in[8][100]={"00","100.000","200.000","500.000","1.000.000","2.000.000","3.000.000","00"};
    int i = 0;
    int clear = 0;
    int moneyEntryCount = 3;
    char choose[100];
    int j = 0;
    for (j = 0; j < 8; j++)
    {
        if (j == 0) printf("%d. Hủy giao dịch hiện tại        ", j);
        else if (j == 7) printf("%d. Số khác\n\n", j);
        else
        {
            printf("%d. %s VND       ",j,in[j]);
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
        printf("Hạn mức tối đa là : %s VND\n\n", "10.000.000");

        int tempEntry = 3;
        long long temp;
        char *tempstr=(char*)malloc(sizeof(char)*21);
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
            
            if (fgets(tempstr, sizeof(tempstr), stdin) == NULL) 
            {
                tempEntry--;
                continue;
            }
            if (tempstr[0] == '\n') 
            {
                tempEntry--;
                if (tempEntry > 0) printf("\n*** Bạn chưa nhập gì! ***\n");
                continue;
            }
            int len = strlen(tempstr);
            if (tempstr[len-1] == '\n') 
            {
                tempstr[len-1] = '\0';
            }
            else
            {
                clear = clear_buffer();
            }
            temp = atoll(tempstr);
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
 
// Các hàm thực thi giao dịch chính

//Chức năng gửi tiền
void guitien(node root, node myAccount)
{
    FILE *f =  fopen("data/output.txt", "a");
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
                    if (myAccount->Data->TransactionCount < MAX_TRANSACTION_LEN)
                    {
                        int current_index = myAccount->Data->TransactionCount;
                        myAccount->Data->Balance += sotiengui;

                        char sotien[30];
                        strcpy(sotien,insert_cham(sotiengui));

                        sprintf(myAccount->Data->TransactionHistory[current_index], "%s|SD: %llu|+%s VND|ND: %s", myAccount->Data->AccountNumber ,myAccount->Data->Balance,sotien, message);
                        strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[current_index]);
                        fprintf(f ,"%d. Số tài khoản: %s\n", admin_index + 1, TransactionList[admin_index]);
                        fflush(f);  
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
                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }
                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
                        return;
                    }

                    int targetAccount_current_index = targetAccount->Data->TransactionCount;
                    int myAccount_current_index = myAccount->Data->TransactionCount;

                    targetAccount->Data->Balance += sotiengui;
                    char sotien[30];
                    strcpy(sotien,insert_cham(sotiengui));

                    sprintf(myAccount->Data->TransactionHistory[myAccount_current_index], "%s|SD: %llu|ND: Gửi %s VND đến tài khoản %s", myAccount->Data->AccountNumber,myAccount->Data->Balance, sotien, targetAccount->Data->AccountNumber);
                    sprintf(targetAccount->Data->TransactionHistory[targetAccount_current_index], "%s|SD: %llu|+%s VND|ND: %s", targetAccount->Data->AccountNumber, targetAccount->Data->Balance,sotien, message);

                    strcpy(TransactionList[admin_index], myAccount->Data->TransactionHistory[myAccount_current_index]);
                    fprintf(f ,"%d. Số tài khoản: %s\n", admin_index + 1, TransactionList[admin_index]);

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
    fclose(f);
}

//Chức năng chuyển tiền
void chuyentien(node root, node myAccount)
{
    FILE *f =  fopen("data/output.txt", "a");
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

                    if (myAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
                        return;
                    }

                    if (targetAccount->Data->TransactionCount >= MAX_TRANSACTION_LEN)
                    {
                        printf("\n>>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA ĐỐI VỚI TÀI KHOẢN GỬI ĐẾN\n\n");
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
                    fprintf(f ,"%d. Số tài khoản: %s\n", admin_index + 1, TransactionList[admin_index]);
                    fflush(f);
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
    fclose(f);
}

//Chức năng rút tiền
void ruttien(node root, node myAccount)
{
    FILE *f =  fopen("data/output.txt", "a");
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
        if (myAccount ->Data ->TransactionCount >= MAX_TRANSACTION_LEN)
        {
            printf(">>>\n\nGIAO DỊCH THẤT BẠI: VƯỢT QUÁ SỐ LẦN GIAO DỊCH TỐI ĐA TRONG LỊCH SỰ GIAO DỊCH ĐỐI VỚI TÀI KHOẢN CỦA BẠN\n\n");
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
        fprintf(f ,"%d. Số tài khoản: %s\n", admin_index + 1, TransactionList[admin_index]);
        fflush(f);
        admin_index +=1;

        //Cộng số lần giao dịch
        myAccount-> Data-> TransactionCount += 1;

        printf("\n\n>>> GIAO DỊCH THÀNH CÔNG\n\n");
        return;
    }
    fclose(f);
}

//Chức năng xem tài khoản
void xemtaikhoan(node myAccount)
{
    char *option[] = {"0. Hủy giao dịch","1. Xem số dư", "2. Xem lịch sử giao dịch"};
    int optionCount = sizeof(option) / sizeof(option[0]);
    int choice;
    int clear;
    int accEntryCount = 3;
    char *choose = (char*)malloc(sizeof(char)*21);
    printf("\n");
    int i;
    for (i = 0; i< optionCount; i+=1)
    {
        printf("%s  ",option[i]);
    }
    do 
    {

        if (accEntryCount == 3)
        {
            printf("\nNhập lựa chọn của bạn : ");
        }
        else
        {
            printf("Nhập lại lựa chọn của bạn  (Bạn còn %d lần): ", accEntryCount);
        }
        
        
        if (fgets(choose,sizeof(choose),stdin)==NULL) continue;
        
        if (choose[0]=='\n')
        {
            accEntryCount -= 1;
            if (accEntryCount > 0) printf("\n*** Bạn chưa nhập gì! ***\n");
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
            if (accEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng CHỈ NHẬP 1 SỐ. ***\n");
            continue; 
        }
        
        if (choose[0]>='0' && choose[0] <='2')
        {
            choice= choose[0]-'0';
            break; 
        }
        else
        {
            accEntryCount -= 1;
            if (accEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 2. ***\n\n");
        }

        if (choice < 0 || choice     > 2 || clear == 1)
        {
            accEntryCount -= 1;
            printf("\n*** Lựa chọn không hợp lệ! Vui lòng chọn số từ 0 đến 7. ***\n\n");
        }

    } while (accEntryCount > 0);
    if (accEntryCount == 0)
            {
                printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                return ;
            }

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