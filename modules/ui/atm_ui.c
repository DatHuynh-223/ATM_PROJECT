#include "atm_ui.h"

//Menu
void menu(node root, node myAccount)
{
    system("cls");
    char *option[] = {"0. Thoát","1. Gửi tiền", "2. Chuyển tiền", "3. Rút tiền", "4. Xem tài khoản"};
    int optionCount = sizeof(option)/ sizeof(option[0]);
    
    while (1)
    {
        printf("\n--- MENU GIAO DỊCH ---\n");
        for (int i = 1; i < optionCount; i++) printf("%s\n", option[i]);
        printf("%s\n", option[0]);
        int menuEntryCount = 3;
        int choice = -1;
        char input[1000];
        
        while (menuEntryCount > 0)
        {
            if (menuEntryCount == 4)    
                        printf("Nhập sự lựa chọn của bạn: ");
            else if (menuEntryCount<4 && menuEntryCount>1)       
                        printf("Nhập lại (Bạn còn %d lần): ", menuEntryCount);
            else
                        printf("\n*** Đây là lần nhập cuối cùng !!! ***\n\n");
                        printf("Nhập sự lựa chọn của bạn: ");
            if (fgets(input,sizeof(input),stdin)==NULL) continue;
            
            if (input[0]=='\n')
            {
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Bạn chưa nhập gì. Vui lòng nhập từ 0 đến 4! ***\n");
                continue;
            }
            
            int len = strlen(input);
            int clear = 0;
            
            if (input[len-1] == '\n')
            {
                input[len-1] = '\0';
                len--;
            }
            else
            {
                clear = clear_buffer(); 
            }
            
            if (len > 1 || clear == 1)
            {
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng CHỈ NHẬP 1 SỐ. ***\n");
                continue; 
            }
            
            if (input[0] >= '0' && input[0] <= '4')
            {
                choice = input[0] - '0';
                break;
            }
            else
            {
                menuEntryCount--;
                if (menuEntryCount > 0) printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ chọn từ 0 đến 4. ***\n");
            }
        }
        
        if ((menuEntryCount == 0) && (choice < 0 || choice > 4)) {
            printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
            return; 
        }
    
        switch (choice)
        {
            case 1: 
                guitien(root, myAccount); 
                break;
            case 2: 
                chuyentien(root, myAccount); 
                break;
            case 3: 
                ruttien(root, myAccount); 
                break;
            case 4: 
                xemtaikhoan(myAccount); 
                break;
            case 0: 
            default:
                printf("\n Đã hủy / Kết thúc giao dịch. \n");
                system("cls");
                return; 
        }
        char yn;
        int ynEntryCount = 3;
        int clear_yn;
        do 
        {
            if (ynEntryCount == 3)
            {
                printf("Bạn có muốn thực hiện giao dịch khác không? [Y/N]: ");
            }
            else
            {
                printf("Bạn có muốn thực hiện giao dịch khác không? [Y/N] (Bạn còn %d lần): ", ynEntryCount);
            }
            if (scanf("%c", &yn) != 1) 
            {
                printf("\n *** Nhập không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                ynEntryCount--;
                continue; 
            }
            if (yn=='\n')
            {
                printf("\n *** Bạn chưa nhập gì! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
                ynEntryCount--;
                continue;
            } 
            clear_yn = clear_buffer();

            if ((yn != 'Y' && yn != 'N') || clear_yn == 1)
            {
                ynEntryCount -= 1;
                if (ynEntryCount == 0)
                {
                    printf("\n*** QUÁ SỐ LẦN NHẬP LỰA CHỌN. TỰ ĐỘNG HỦY GIAO DỊCH ***\n\n");
                    return;
                }
                printf("\n*** Lựa chọn không hợp lệ! Vui lòng chỉ nhập Y hoặc N. ***\n\n");
            }
        } while (((yn != 'Y' && yn != 'N') || clear_yn == 1) && ynEntryCount > 0);
        if (yn == 'N') 
        {

            printf("\n*** CẢM ƠN QUÝ KHÁCH ĐÃ SỬ DỤNG DỊCH VỤ ***\n\n");
            return;
        }
        system("cls");
    }
}

//Hàm đăng nhập với vai trò khách
void GuestLogin(node root,char *shutdown )
{
    char target[MAX_ACC_LEN], yesno ='Y';
    int loginCount = 3;
    char stk_Admin[MAX_ACC_LEN]="06121234";
    char shutdown1='N';
    int KT=0;
    do 
    {
        if (KT) loginCount=3;
        printf("Vui lòng nhập Số tài khoản của bạn (Bạn còn %d lần nhập tài khoản): ", loginCount);
        loginCount -= 1;

        if (fgets(target,sizeof(target),stdin)==NULL) 
        {
            printf("\n*** Bạn chưa nhập gì. Vui lòng nhập Số tài khoản! ***\n");
            continue;
        }
        if (target[0]=='\n')	
        {
            printf("\n*** Bạn chưa nhập gì. Vui lòng nhập Số tài khoản! ***\n");
            continue;
        }
        int len = strlen(target);
        if (target[len - 1] == '\n') 
        {
            target[len - 1] = '\0'; 
        } 
        else 
        {
            clear_buffer();
        }
        if (strcmp(target,stk_Admin)==0)
        {
            KT=1;
            AdministratorLogin(&shutdown1);
            (*shutdown)=shutdown1;
            if (*shutdown == 'Y') {
                return; 
            }
        }
        else
        {
        node temp = findNode(root, target);

        if (temp != NULL)
        {
            KT=1;
            char mapin[MAX_PIN_LEN];
            int pinEntryCount = 4;
            do
            {
                if (pinEntryCount==4)
                {
                    printf("Vui lòng nhập mã Pin của bạn: ");
                }
                else if (pinEntryCount < 4 && pinEntryCount > 1)
                {
                    printf("Vui lòng nhập lại mã Pin của bạn (Bạn còn %d lần nhập): ", pinEntryCount);
                }
                else 
                {
                    printf("\n*** Đây là lần nhập cuối cùng !!! ***\n\n");
                    printf("Vui lòng nhập lại mã Pin của bạn : ", pinEntryCount);
                }
                pinEntryCount-=1;
                if (fgets(mapin,sizeof(mapin),stdin)==NULL) 
                {
                    printf("\n*** Bạn chưa nhập gì. Vui lòng nhập Số tài khoản! ***\n");
                    continue;
                }
                int len=strlen(mapin);
                if (mapin[len-1]=='\n')
                {
                	mapin[len-1]='\0';
				}
				else
				{
					clear_buffer();
				}
                if (strcmp(temp ->Data -> Pin, mapin ) !=0)
                {
                    printf("\n*** Mã Pin không chính xác! ***\n");
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
        } 
        }
    } while ( loginCount > 0);

    if (loginCount == 0) printf("** QUÁ SỐ LẦN NHẬP TÀI KHOẢN **\n\n");
}

//Hàm đăng nhập với vai trò Lập trình viên
void AdministratorLogin(char *shutdown)
{
    printf(" \n\n=====================================================================CHÀO MỪNG ADMIN=====================================================================\n\n");
    char admin_pin[7] = "000000";
    char Pin_Entry[7];
    int Pin_Entry_Count = 4;
    int clear;

    do 
    {
        if (Pin_Entry_Count ==1)
        {
            printf("\n *** Đây lần cuối để nhập mã bảo mật! ***\n");
            printf("Vui lòng nhập mã bảo mật của Admin : ");
        }
        else if (Pin_Entry_Count ==4)
        {
            printf("Vui lòng nhập mã bảo mật của Admin : ");
        }
        else
        {
            printf("Vui lòng nhập mã bảo mật của Admin (Bạn còn %d lần nhập): ",Pin_Entry_Count);
        }
        Pin_Entry_Count -= 1;
		if (fgets(Pin_Entry,sizeof(Pin_Entry),stdin)==NULL) continue;
        if (Pin_Entry[0]=='\n')	
        {
            printf("\n*** Bạn chưa nhập gì. ***\n");
            continue;
        }
        int len = strlen(Pin_Entry);
        if (Pin_Entry[len - 1] == '\n') 
        {
            Pin_Entry[len - 1] = '\0'; 
        } 
        else 
        {
            clear = clear_buffer(); 
        }
        if (strcmp(Pin_Entry, admin_pin) != 0)
        {
            printf("\n*** Mã bảo mật không chính xác! ***\n");
        }
    } while ((strcmp(Pin_Entry, admin_pin) != 0 || clear != 0) && Pin_Entry_Count >= 0); //Tránh trường hợp người dùng nhập dư kí tự khiến buffer hiểu lầm rằng còn lần nhập nhưng thực tế đã hết lần nhập

    //Kiểm tra mã bảo mật
    if (strcmp(Pin_Entry, admin_pin) == 0 && clear == 0)
    {
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
    // xóa sạch output khi bắt đàau chạy 
    FILE *f = fopen("data/today's trade.txt", "w");
    if (f != NULL) {
        fclose(f);
    }
    char shutdown = 'N';
    int clear=0;
    int passEntryCount = 3;
    char pass[7];
    char admin_pass[7]="000000";
    int KT=0;
    printf("\n\n[=========================================================NHẬP MÃ BẢO MẬT CỦA ADMIN ĐỂ KHỞI ĐỘNG ATM========================================================= ]\n\n");
    do 
    {
        if (passEntryCount==3)
            printf("Vui lòng nhập mã bảo mật của Admin : ");
        else if (passEntryCount <3 && passEntryCount >0) 
        {
            printf("*****  Vui lòng nhập lại mã bảo mật! *****\n");
            printf("Vui lòng nhập mã bảo mật của Admin (Bạn còn %d lần nhập): ", passEntryCount);
        }
        else 
        {
            printf("\n *** Đây lần cuối để nhập mã bảo mật! ***\n");
            printf("Vui lòng nhập mã bảo mật của Admin : ");
        }
        passEntryCount -= 1;
		if (fgets(pass,sizeof(pass),stdin)==NULL) 
        {
            printf("\n*** Bạn chưa nhập gì. ***\n");
            continue;
        }
        if (pass[0]=='\n')	
        {
            printf("\n*** Bạn chưa nhập gì. ***\n");
            continue;
        }
        int len = strlen(pass);
        if (pass[len - 1] == '\n') 
        {
            pass[len - 1] = '\0'; 
        } 
        else 
        {
            clear = clear_buffer(); 
        }
        if (strlen(pass)<6 || strcmp(pass, admin_pass) != 0 ) 
        {
            printf("\n*** Mã bảo mật không chính xác . ***\n");
            continue;
        }
        
    } while ((strcmp(pass, admin_pass) != 0 || clear != 0) && passEntryCount > 0);
    if (strcmp(pass, admin_pass) == 0 && clear == 0)
    {
        system("cls");
        printf("\n\n[===========================================================KHỞI ĐỘNG THÀNH CÔNG HỆ THỐNG ===========================================================]\n\n");
        KT=1;
    }
    else
    {
        printf("*** \n\nQUÁ SỐ LẦN NHẬP MÃ BẢO MẬT ***~\n\n");
    }
    if (KT)
    {
        do
        {
            system("cls");
            printf("==========================================================================================================================================================\n\n");
            printf("* %50sCHÀO MỪNG QUÝ KHÁCH ĐẾN VỚI NGÂN HÀNG 3 THÀNH VIÊN%50s*\n\n"," "," ");
            printf("==========================================================================================================================================================\n\n");
            FILE *day=fopen("data/day.txt","r");
            int day_trade=1;
            fscanf(day,"%d",&day_trade);
            fclose(day);
            printf("\n\n NGÀY %d GIAO DỊCH \n\n",day_trade);
            GuestLogin(root,&shutdown);
    
        } while (shutdown != 'Y');
        system("cls");
        printf("\n*** MÁY ĐANG TẮT... CẢM ƠN QUÝ KHÁCH ĐÃ SỬ DỤNG DỊCH VỤ ***\n\n");
    }
    else{
        printf("\n*** TỰ ĐỘNG TẮT MÁY ĐỂ BẢO MẬT ***\n\n");
    }
}