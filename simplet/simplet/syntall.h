// 2019 ReVoL Primer Template
// syntall.h
// синтаксическая таблица LL

/* Generated by 2016 ReVoL SYNAX */
/* 15-09-2022 13:59:18 */

#define ST_MAX_RULE_LEN 16 /* Max rule length */

/* Rules */
sttype RULE[52][ST_MAX_RULE_LEN] = {
    /* 0*/{ TOK_EOT },
    /* 1 SYM_M     */{ SYM_DS, SYM_SS, TOK_EOT },
    /* 2 SYM_DS    */{ SYM_D, SYM_D_, TOK_EOT },
    /* 3 SYM_DS    */{ TOK_EOT },
    /* 4 SYM_D_    */{ SYM_D, SYM_D_, TOK_EOT },
    /* 5 SYM_D_    */{ TOK_EOT },
    /* 6 SYM_D     */{ TOK_INT, TOK_ID, SYM_L_, TOK_SEMI, TOK_EOT },
    /* 7 SYM_L_    */{ TOK_COMMA, TOK_ID, SYM_L_, TOK_EOT },
    /* 8 SYM_L_    */{ TOK_EOT },
    /* 9 SYM_B     */{ TOK_LB, SYM_E, TOK_RB, TOK_EOT },
    /*10 SYM_D     */{ TOK_CHAR, TOK_ID, SYM_B, SYM_C_, TOK_SEMI, TOK_EOT },
    /*11 SYM_C_    */{ TOK_COMMA, TOK_ID, SYM_B, SYM_C_, TOK_EOT },
    /*12 SYM_C_    */{ TOK_EOT },
    /*13 SYM_SS    */{ SYM_S, SYM_S_, TOK_EOT },
    /*14 SYM_S_    */{ SYM_S, SYM_S_, TOK_EOT },
    /*15 SYM_S_    */{ TOK_EOT },
    /*16 SYM_S     */{ TOK_SEMI, TOK_EOT },
    /*17 SYM_S     */{ TOK_ID, SYM_SI, TOK_EOT },
    /*18 SYM_SI    */{ SYM_B, TOK_EQ, SYM_E, TOK_SEMI, TOK_EOT },
    /*19 SYM_SI    */{ TOK_EQ, SYM_E, TOK_SEMI, TOK_EOT },
    /*20 SYM_S     */{ TOK_PRINT, SYM_A, TOK_SEMI, TOK_EOT },
    /*21 SYM_S     */{ TOK_IF, SYM_A, SYM_S, TOK_EOT },
    /*22 SYM_S     */{ TOK_LS, SYM_SS, TOK_RS, TOK_EOT },
    /*23 SYM_E     */{ SYM_LOR, SYM_LOR_, TOK_EOT },
    /*24 SYM_LOR_  */{ TOK_LOR, SYM_LOR, SYM_LOR_, TOK_EOT },
    /*25 SYM_LOR_  */{ TOK_EOT },
    /*26 SYM_LOR   */{ SYM_LAND, SYM_LAND_, TOK_EOT },
    /*27 SYM_LAND_ */{ TOK_LAND, SYM_LAND, SYM_LAND_, TOK_EOT },
    /*28 SYM_LAND_ */{ TOK_EOT },
    /*29 SYM_LAND  */{ SYM_R, SYM_R_, TOK_EOT },
    /*30 SYM_R_    */{ TOK_ASS, SYM_R, SYM_R_, TOK_EOT },
    /*31 SYM_R_    */{ TOK_LT, SYM_R, SYM_R_, TOK_EOT },
    /*32 SYM_R_    */{ TOK_GT, SYM_R, SYM_R_, TOK_EOT },
    /*33 SYM_R_    */{ TOK_EOT },
    /*34 SYM_R     */{ SYM_T, SYM_T_, TOK_EOT },
    /*35 SYM_T_    */{ TOK_ADD, SYM_T, SYM_T_, TOK_EOT },
    /*36 SYM_T_    */{ TOK_SUB, SYM_T, SYM_T_, TOK_EOT },
    /*37 SYM_T_    */{ TOK_EOT },
    /*38 SYM_T     */{ SYM_U, SYM_U_, TOK_EOT },
    /*39 SYM_U_    */{ TOK_MUL, SYM_U, SYM_U_, TOK_EOT },
    /*40 SYM_U_    */{ TOK_DIV, SYM_U, SYM_U_, TOK_EOT },
    /*41 SYM_U_    */{ TOK_EOT },
    /*42 SYM_U     */{ SYM_P, TOK_EOT },
    /*43 SYM_U     */{ TOK_SUB, SYM_P, TOK_EOT },
    /*44 SYM_U     */{ SYM_LNOT, TOK_EOT },
    /*45 SYM_LNOT  */{ TOK_LNOT, SYM_P, TOK_EOT },
    /*46 SYM_P     */{ TOK_I4, TOK_EOT },
    /*47 SYM_P     */{ TOK_QUOTE, TOK_EOT },
    /*48 SYM_P     */{ TOK_ID, TOK_EOT },
    /*49 SYM_P     */{ TOK_SYMBOL, TOK_EOT },
    /*50 SYM_P     */{ SYM_A, TOK_EOT },
    /*51 SYM_A     */{ TOK_LP, SYM_E, TOK_RP, TOK_EOT }
};

#define MAX_RULE 51 /* Max rule index */

/* Rule Length */
int RLEN[] = { 0,2,2,0,2,0,4,3,0,3,5,4,0,2,2,0,1,2,4,3,3,3,3,2,3,0,2,3,0,2,3,3,3,0,2,3,3,0,2,3,3,0,1,2,1,2,1,1,1,1,1,3 };

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
stack_t SYNTA[53][28] = {
    /*             EOT [int]  [id]   [;]   [,]   [[]   []] [char   [=] [prin  [if]   [{]   [}]  [||]  [&&]  [==]   [<]   [>]   [+]   [-]   [*]   [/]   [!]  [I4] [QUOT [SYMB   [(]   [)] */
    /*        */{  ACC,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*   [int]*/{    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [id]*/{    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [;]*/{    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [,]*/{    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [[]*/{    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     []]*/{    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*  [char]*/{    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [=]*/{    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /* [print]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [if]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [{]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [}]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [||]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [&&]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    [==]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [<]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [>]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [+]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [-]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     [*]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0,    0 },
    /*     [/]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0,    0 },
    /*     [!]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0,    0 },
    /*    [I4]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0,    0 },
    /* [QUOTE]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0,    0 },
    /*[SYMBOL]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0,    0 },
    /*     [(]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP,    0 },
    /*     [)]*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  POP },
    /*             EOT [int]  [id]   [;]   [,]   [[]   []] [char   [=] [prin  [if]   [{]   [}]  [||]  [&&]  [==]   [<]   [>]   [+]   [-]   [*]   [/]   [!]  [I4] [QUOT [SYMB   [(]   [)] */
    /*     <M>*/{    0,    1,    1,    1,    0,    0,    0,    1,    0,    1,    1,    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <DS>*/{    0,    2,    3,    3,    0,    0,    0,    2,    0,    3,    3,    3,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <SS>*/{    0,    0,   13,   13,    0,    0,    0,    0,    0,   13,   13,   13,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     <D>*/{    0,    6,    0,    0,    0,    0,    0,   10,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <D.>*/{    0,    4,    5,    5,    0,    0,    0,    4,    0,    5,    5,    5,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <L.>*/{    0,    0,    0,    8,    7,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     <B>*/{    0,    0,    0,    0,    0,    9,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     <E>*/{    0,    0,   23,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   23,    0,    0,   23,   23,   23,   23,   23,    0 },
    /*    <C.>*/{    0,    0,    0,   12,   11,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     <S>*/{    0,    0,   17,   16,    0,    0,    0,    0,    0,   20,   21,   22,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <S.>*/{   15,    0,   14,   14,    0,    0,    0,    0,    0,   14,   14,   14,   15,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*    <SI>*/{    0,    0,    0,    0,    0,   18,    0,    0,   19,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    /*     <A>*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   51,    0 },
    /*   <LOR>*/{    0,    0,   26,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   26,    0,    0,   26,   26,   26,   26,   26,    0 },
    /*  <LOR.>*/{    0,    0,    0,   25,    0,    0,   25,    0,    0,    0,    0,    0,    0,   24,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   25 },
    /*  <LAND>*/{    0,    0,   29,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   29,    0,    0,   29,   29,   29,   29,   29,    0 },
    /* <LAND.>*/{    0,    0,    0,   28,    0,    0,   28,    0,    0,    0,    0,    0,    0,   28,   27,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   28 },
    /*     <R>*/{    0,    0,   34,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   34,    0,    0,   34,   34,   34,   34,   34,    0 },
    /*    <R.>*/{    0,    0,    0,   33,    0,    0,   33,    0,    0,    0,    0,    0,    0,   33,   33,   30,   31,   32,    0,    0,    0,    0,    0,    0,    0,    0,    0,   33 },
    /*     <T>*/{    0,    0,   38,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   38,    0,    0,   38,   38,   38,   38,   38,    0 },
    /*    <T.>*/{    0,    0,    0,   37,    0,    0,   37,    0,    0,    0,    0,    0,    0,   37,   37,   37,   37,   37,   35,   36,    0,    0,    0,    0,    0,    0,    0,   37 },
    /*     <U>*/{    0,    0,   42,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   43,    0,    0,   44,   42,   42,   42,   42,    0 },
    /*    <U.>*/{    0,    0,    0,   41,    0,    0,   41,    0,    0,    0,    0,    0,    0,   41,   41,   41,   41,   41,   41,   41,   39,   40,    0,    0,    0,    0,    0,   41 },
    /*     <P>*/{    0,    0,   48,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   46,   47,   49,   50,    0 },
    /*  <LNOT>*/{    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   45,    0,    0,    0,    0,    0 }
};
