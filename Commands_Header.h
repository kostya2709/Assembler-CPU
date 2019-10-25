
ASM_CMD( end, 0, 0,
{
    leave = 1;
})

ASM_CMD( push, 1, 1,
{
    buf_r_ptr++;

    char args_n = *buf_r_ptr;
    buf_r_ptr++;

    if (args_n == 1)
    {
        for (j = 0; j < sizeof (int); j++)
            my_int[j] = *buf_r_ptr++;

        char* ptr = my_int;
        val = Int_Byte_Read (ptr) * FLOAT_P;
        Stack_Push (&stk1, val);
    }
    else if (args_n == 2)
    {
        char cur_reg = *buf_r_ptr;
        buf_r_ptr += 2;
        Stack_Push (&stk1, reg[cur_reg - 'a']);
    }
    buf_r_ptr--;

})

ASM_CMD( add, 2, 0,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);
    Stack_Push (&stk1, val1 + val2);
})

ASM_CMD( min, 3, 0,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);
    Stack_Push (&stk1, val2 - val1);
})

ASM_CMD( mul, 4, 0,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);
    Stack_Push (&stk1, val1 * val2 / FLOAT_P);
})

ASM_CMD( div, 5, 0,
{
    double val1 = Stack_Pop (&stk1);
    double val2 = Stack_Pop (&stk1);
    if (val1 == 0)
        printf ("Error! Attempt to divide on zero!");
    else Stack_Push (&stk1, (int)(FLOAT_P * val2 / val1));
})

ASM_CMD( pop, 6, 1,
{
    buf_r_ptr += 2;
    char cur_reg = *buf_r_ptr;
    buf_r_ptr++;
    reg[cur_reg - 'a'] = Stack_Pop (&stk1);
})

ASM_CMD( sqrt, 7, 0,
{
    double val1 = Stack_Pop (&stk1) / FLOAT_P;
    if (val1 < 0)
    {
        printf ("ERROR! You can't take a root of a negative number!\n");
        abort();
    }
    int val2 = (int)(FLOAT_P * sqrt (val1));
    Stack_Push (&stk1, val2);
})

ASM_CMD( in, 8, 0,
{
    int val1 = 0;
    scanf ("%d", &val1);
    Stack_Push (&stk1, FLOAT_P * val1);
})

ASM_CMD( out, 9, 0,
{
    float val1 = Stack_Pop (&stk1);
    printf (PR_F, val1 / FLOAT_P);
})

ASM_CMD( dump, 10, 0,
{
    Dump (stk1);
    Print_Reg (reg);
})

ASM_CMD( jmp, 11, 1,
{

    Just_Code_For_JMP (&buf_r_ptr, &buf_r);

})

ASM_CMD( je, 12, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val1 = val2)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr = buf_r_ptr + sizeof (int);


    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( ja, 13, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val2 > val1)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr += sizeof (int);

    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( jl, 14, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val2 < val1)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr += sizeof (int);

    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( jae, 15, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val2 >= val1)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr += sizeof (int);

    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( jle, 16, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val2 <= val1)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr += sizeof (int);

    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( jne, 17, 1,
{
    int val1 = Stack_Pop (&stk1);
    int val2 = Stack_Pop (&stk1);

    if (val1 != val2)
        Just_Code_For_JMP (&buf_r_ptr, &buf_r);
    else buf_r_ptr += sizeof (int);

    Stack_Push (&stk1, val2);
    Stack_Push (&stk1, val1);
})

ASM_CMD( outf, 18, 1,
{
    buf_r_ptr++;

    char args_n = *buf_r_ptr;
    char* cur_line = (char*)calloc (1, args_n + 1);
    char* cur_start = cur_line;
    buf_r_ptr++;

    for (j = 0; j < args_n; j++)
    {
        if (*buf_r_ptr == '\\' && *(buf_r_ptr + 1) == 'n')
        {
            *cur_line = '\0';
            printf ("%s\n", cur_start);
            cur_line += 2;
            buf_r_ptr += 2;
            cur_start = cur_line;
            j += 2;
            continue;
        }
        *cur_line = *buf_r_ptr;
        cur_line++;
        buf_r_ptr++;
    }

    buf_r_ptr--;

    printf ("%s\n", cur_start);

})
