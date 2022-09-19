// 2019 ReVoL Primer Template
// syntallo.h
// �������������� ������� LL � ������������� ���������

/* Generated by 2016 ReVoL SYNAX */
/* 17-09-2022 22:18:47 */

#define ST_MAX_RULE_LEN 16 /* Max rule length */

/* Rules */
sttype RULE[27][ST_MAX_RULE_LEN] = {
    /* 0*/{ TOK_EOT },
    /* 1 SYM_M  */{ SYM_S, SYM_M, TOK_EOT },
    /* 2 SYM_M  */{ TOK_EOT },
    /* 3 SYM_S  */{ TOK_LF, TOK_EOT },
    /* 4 SYM_S  */{ TOK_DIM, TOK_ID, OUT_ID, TOK_AS, TOK_LONG, OUT_LONG, OUT_DIM, TOK_LF, TOK_EOT },
    /* 5 SYM_S  */{ TOK_ID, OUT_ID, TOK_EQ, SYM_E, OUT_ASS, TOK_LF, TOK_EOT },
    /* 6 SYM_S  */{ TOK_IF, SYM_E, TOK_THEN, TOK_LF, OUT_PUSH, OUT_BZ, SYM_M, SYM_A, TOK_EOT },
    /* 7 SYM_A  */{ TOK_ELSE, TOK_LF, OUT_PUSH, OUT_BR, OUT_SWAP, OUT_DEFL, SYM_M, OUT_POPL, OUT_DEFL,
                        TOK_END, TOK_IF, TOK_LF, TOK_EOT },
    /* 8 SYM_A  */{ OUT_POPL, OUT_DEFL, TOK_END, TOK_IF, TOK_LF, TOK_EOT },
    /* 9 SYM_S  */{ TOK_PRINT, SYM_E, OUT_PRINT, TOK_LF, TOK_EOT },
    /*10 SYM_E  */{ SYM_R, SYM_R_, TOK_EOT },
    /*11 SYM_R_ */{ TOK_EQ, SYM_R, SYM_R_, OUT_EQ, TOK_EOT },
    /*12 SYM_R_ */{ TOK_NE, SYM_R, SYM_R_, OUT_NE, TOK_EOT },
    /*13 SYM_R_ */{ TOK_LT, SYM_R, SYM_R_, OUT_LT, TOK_EOT },
    /*14 SYM_R_ */{ TOK_GT, SYM_R, SYM_R_, OUT_GT, TOK_EOT },
    /*15 SYM_R_ */{ TOK_EOT },
    /*16 SYM_R  */{ SYM_T, SYM_T_, TOK_EOT },
    /*17 SYM_T_ */{ TOK_ADD, SYM_T, SYM_T_, OUT_ADD, TOK_EOT },
    /*18 SYM_T_ */{ TOK_SUB, SYM_T, SYM_T_, OUT_SUB, TOK_EOT },
    /*19 SYM_T_ */{ TOK_EOT },
    /*20 SYM_T  */{ SYM_P, SYM_P_, TOK_EOT },
    /*21 SYM_P_ */{ TOK_MUL, SYM_P, SYM_P_, OUT_MUL, TOK_EOT },
    /*22 SYM_P_ */{ TOK_DIV, SYM_P, SYM_P_, OUT_DIV, TOK_EOT },
    /*23 SYM_P_ */{ TOK_EOT },
    /*24 SYM_P  */{ TOK_ID, OUT_ID, TOK_EOT },
    /*25 SYM_P  */{ TOK_I4, OUT_I4, TOK_EOT },
    /*26 SYM_P  */{ TOK_LP, SYM_E, TOK_RP, TOK_EOT }
};

#define MAX_RULE 26 /* Max rule index */

/* Rule Length */
int RLEN[] = { 0,2,0,1,5,4,6,6,3,3,2,3,3,3,3,0,2,3,3,0,2,3,3,0,1,1,3 };

/* Evaluates actual rule's length */
void get_rule_len() {
    int rule, count;
    for (rule = 1; rule <= MAX_RULE; rule++) {
        for (count = 0; count < ST_MAX_RULE_LEN; count++) {
            if ((int)RULE[rule][count] == 0) break;
        }
        RLEN[rule] = count;
    }
}

#define ACC 255 /* ACCEPT CODE */
#define POP 254 /* POP CODE */
#define START SYM_M /* START SYMBOL */

/* Syntax Table SYNTA (LL-analysis) */
stack_t SYNTA[32][22] = {
    /*            EOT  [LF] [dim]  [id]  [as] [long   [=]  [if] [then [else [end] [prin  [<>]   [<]   [>]   [+]   [-]   [*]   [/]  [I4]   [(]   [)] */
    /*       */{  ACC,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [LF]*/{    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*  [dim]*/{    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [id]*/{    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [as]*/{    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /* [long]*/{    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [=]*/{    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [if]*/{    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /* [then]*/{    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /* [else]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*  [end]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*[print]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [<>]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [<]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [>]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0 },
    /*    [+]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0 },
    /*    [-]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0 },
    /*    [*]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0 },
    /*    [/]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0 },
    /*   [I4]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0 },
    /*    [(]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0 },
    /*    [)]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP },
    /*            EOT  [LF] [dim]  [id]  [as] [long   [=]  [if] [then [else [end] [prin  [<>]   [<]   [>]   [+]   [-]   [*]   [/]  [I4]   [(]   [)] */
    /*    <M>*/{    2,    1,    1,    1,    0,    0,    0,    1,    0,    2,    2,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <S>*/{    0,    3,    4,    5,    0,    0,    0,    6,    0,    0,    0,    9,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <E>*/{    0,    0,    0,   10,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   10,   10,    0 },
    /*    <A>*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,    8,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <R>*/{    0,    0,    0,   16,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   16,   16,    0 },
    /*   <R.>*/{    0,   15,    0,    0,    0,    0,   11,    0,   15,    0,    0,    0,   12,   13,   14,    0,    0,    0,    0,    0,    0,   15 },
    /*    <T>*/{    0,    0,    0,   20,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   20,   20,    0 },
    /*   <T.>*/{    0,   19,    0,    0,    0,    0,   19,    0,   19,    0,    0,    0,   19,   19,   19,   17,   18,    0,    0,    0,    0,   19 },
    /*    <P>*/{    0,    0,    0,   24,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   25,   26,    0 },
    /*   <P.>*/{    0,   23,    0,    0,    0,    0,   23,    0,   23,    0,    0,    0,   23,   23,   23,   23,   23,   21,   22,    0,    0,   23 }
};
