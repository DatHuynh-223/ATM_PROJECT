#include "atm_ui.h"

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
        FILE *f =  fopen("data/output.txt", "w");
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