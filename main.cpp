#include "main_lib.h"


int main()
{
    char* file_n = Insert_File_Name ();

    int res = Translate (file_n);

    return 0;
}
