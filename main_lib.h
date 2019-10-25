#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dir.h>
#include <math.h>

#include "..\File_Reader.h"

#include "Head in ASSembler.h"
#include "Stack.h"

#ifdef Debug
#define PRINTF printf
#define GO( code ) code
#else
#define PRINTF if (0) printf
#define GO( code ) if (0) printf
#endif // My_Debug
