#define DEBUG
#undef DEBUG

#ifdef DEBUG
#define DE_BUG( code ) code;
#else #define DE_BUG( code ) if (0);
#endif // DEBUG

const int MAX_COM = 1000;

#define step 3
const int FLOAT_P = pow (10, step);
#define PR_F "%.3f\n"


const int MAX_COM_NAME = 10;

struct command
{
	char name[MAX_COM_NAME];
	int code;
};

int Code_Read (command* com, int* max);

char* Insert_File_Name (void);

int Translate (char* file_name);

char* Take_File_Path (int level);

/*
end 0
push 1
add 2
min 3
mul 4
div 5
pop 6
*/
