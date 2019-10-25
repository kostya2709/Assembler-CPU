#include "main_lib.h"

char* error = "Error!";

char screen = 'k';

char* Find_Code (char com_n, command com[MAX_COM], int com_num);

int Print_Reg (int* reg);

int Res_to_File (char* file_n, int val);

int Int_Byte_Read (void* ptr);

char* Insert_File_Name (void);

char* Take_File_Path (int level);

int Just_Code_For_JMP (char** buf_r_ptr, char** buf_r);

int Translate (char* file_name)
{
    assert (file_name);

    const char assm[5] = ".asm";
    const char wr[14] = "_result.txt";

    char* file = (char*)calloc (1, 100);
    strcpy (file, file_name);
    char* file1 = (char*)calloc (1, 100);
    strcpy (file1, file_name);


    char* read = strcat (file, assm);
    char* write = strcat (file1, wr);

    FILE* f = fopen (read, "r");
    if (!f)
    {
        printf ("This file ( %s ) doesn't exist!\n", read);
        abort();
    }

    Stack_t stk1 = {};
    Stack_Constructor (stk1);


    char cur_com = -1;
    char com_l[MAX_COM_NAME] = {};

    char* buf_r = (char*)calloc (1, MAX_COM * MAX_COM_NAME);
    fread (buf_r, MAX_COM * MAX_COM_NAME, 1, f);
    char* buf_r_ptr = buf_r;

    int j = 0;
    int reg[26] = {};
    for (j = 0; j < 26; j++)
        reg[j] = -666;

    char my_int[sizeof(int) + 1] = {};
    int val = 0;
    int leave = 0;

    while (true)
    {
        cur_com = *buf_r_ptr;

        switch (cur_com)
        {
            #define ASM_CMD( name, num, args_num, code)     \
            case num:                                       \
            {                                               \
                code                                        \
                buf_r_ptr++;                                \
                break;                                      \
            }

            #include "..\Commands_Header.h"

            default:
            {
                printf ("Unidentified operator\n");
                abort();
            }
        }
        #undef ASM_CMD

        if (leave == 1)
            break;

    }

    int vall = 0;
    if (stk1.size > 0)
        vall = Stack_Pop (&stk1);

    if ((screen == 'f') || (screen == 'F')) printf ("\nResult of your program is:\n%d\n", vall / FLOAT_P);
    printf ("\nYou can find the result of your program here:\n%s\n\n", write);
    fclose (f);

    Res_to_File (write, vall);

    Stack_Destruct (&stk1);

    return vall;
}

int Int_Byte_Read (void* ptr)
{
    assert (ptr);

    int i = 0;
    int num = 0;
    int* ptr1 = &num;
    for (i = 0; i < 4; i++)
        *((char*)ptr1 + i) = (char)*((char*)ptr + i);
    return num;
}

char* Insert_File_Name (void)
{
    printf ("Press 'F' if you want to display your program result on the screen,\nOr press any other button if you don't.\n\n");
    scanf ("%c", &screen);
    printf ("Press '0' to run a default program \"asm_progs\\program_qq\".\n");
    printf ("Or enter your file (without spaces and extension) to compile from \"asm_progs\" folder.\n\n");

    char* file_n = (char*)calloc (1,511);
    char default_f[511] = "program_qq";
    char scanf_is_my_love[40] = {};
    char adress[511] = "asm_progs\\";
    char* path = (char*)calloc (1,511);
    path = Take_File_Path (2);

    scanf ("%s", &scanf_is_my_love);

    char slash[2] = {};
    slash[0] = '\\';

    if (scanf_is_my_love[0] == '0')
    {
        strcat (adress, default_f);
        strcat (adress, slash);
        strcat (path, adress);
        strcpy (file_n, strcat (path, default_f));
    }
    else
    {
        strcat (adress, scanf_is_my_love);
        strcat (adress, slash);
        strcat(path, adress);
        strcpy(file_n, strcat (path, scanf_is_my_love));
    }

    return file_n;
}

char* Take_File_Path (int level)
{
    char* path = (char*)calloc(1,511);
    strcpy (path, __FILE__);

    int count = level;
    char* ptr = path;
    while (*ptr++);
    while (count)
    {
        if (*ptr == '\\')
            count--;
        if (count) *ptr = '\0';
        ptr--;
    }

    ptr = path;

    return ptr;
}

int Res_to_File (char* file_n, int val)
{
    assert (file_n);

    FILE* f = fopen (file_n, "w");
    fprintf (f, "%d", val);
    fclose (f);

    return 0;
}

int Print_Reg (int* reg)
{
    int i = 0;
    while (*(reg + i) != -666)
    {
        printf ("%cx = %d ", (char)(i + 'a'), *(reg + i) / FLOAT_P);
        i++;
    }
    printf ("\n");
    return 0;
}

int Just_Code_For_JMP (char** buf_r_ptr, char** buf_r)
{

        (*buf_r_ptr)++;
        char* my_int = (char*)calloc (1, sizeof(int));

        int j = 0;

        for (j = 0; j < sizeof (int); j++)
            my_int[j] = *((*buf_r_ptr)++);

        char* ptr = my_int;
        int val = Int_Byte_Read (ptr);

        *buf_r_ptr = *buf_r + val - 1;

}
