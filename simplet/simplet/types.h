// 2019 ReVoL Primer Template
// types.h
// ����

// ������������ ����� ��
#define MAX_ID 7
// ������������ ����� �������
#define MAX_QUOTE 31

// ��� ������ �����
typedef signed short stack_t;

// ���� ������ ��������� ���������
typedef enum stdtyp : stack_t { STDT_NULL = VT_NULL, STDT_I4 = VT_I4, STDT_R8 = VT_R8 } _stdtyp;

// ������� ���������� � �����������
typedef enum sttype : stack_t {
    OUT_START = 997,
    TOK_COMMENT,
    TOK_UNKNOWN,
    // ������
    TOK_EOT = 0,
    TOK_LF,
    TOK_DIM,
    TOK_ID,
    TOK_AS,
    TOK_LONG,
    TOK_EQ,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_END,
    TOK_PRINT,
    TOK_NE,
    TOK_LT,
    TOK_GT,
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_I4,
    TOK_LP,
    TOK_RP,
    TOK_LAST = TOK_RP,
    // �����������
    SYM_M,
    SYM_S,
    SYM_E,
    SYM_A,
    SYM_R,
    SYM_R_,
    SYM_T,
    SYM_T_,
    SYM_P,
    SYM_P_,
    SYM_LAST = SYM_P_,
    // ����� �������� ����������
    // ������� ���������� ����
    OUT_ID,
    OUT_I4,
    OUT_LABEL,
    OUT_DEFL,
    OUT_PUSH,
    OUT_POPL,
    OUT_SWAP,
    OUT_LONG,
    OUT_BZ,
    OUT_BR,
    OUT_DIM,
    OUT_ASS,
    OUT_ADD,
    OUT_SUB,
    OUT_MUL,
    OUT_DIV,
    OUT_EQ,
    OUT_NE,
    OUT_LT,
    OUT_GT,
    OUT_PRINT,
    OUT_END,
    // ��� ������������
    OUT_INT,
    OUT_R8,
    OUT_LE,
    OUT_GE,
    TOK_R8,
    TOK_QUOTE,
    TOK_LS,
    TOK_RS,
    TOK_LB,
    TOK_RB,
    TOK_SYMBOL,
    TOK_LNOT,
    TOK_SEMI,
    TOK_COMMA,
    TOK_LAND,
    TOK_LOR,
    TOK_AND,
    TOK_ASS,
    TOK_OR,
    TOK_NOT,
    TOK_LE,
    TOK_GE
} _sttype;

// �����
struct sttoken {
    // ��� ������
    sttype stt;
    // ������������� ��������
    int int_val;
    // ������������ ��������
    double dbl_val;
    // ��� ������
    stdtyp data_type;
    // ��������� ��������
    char str_val[1 + MAX_QUOTE];
    // �����������
    sttoken() {
        reset();
    }
    // ������� ������
    void reset(void) {
        stt = TOK_EOT;
        int_val = 0;
        dbl_val = 0;
        data_type = STDT_NULL;
        text_reset();
    }
    // ������� ��������� �������������
    void text_reset(void) {
        for (int i = 0; i <= MAX_QUOTE; i++) str_val[i] = 0;
    }
    // ��������� ������
    int append(char c) {
        int len = strlen(str_val);
        if (len < MAX_QUOTE) {
            str_val[len] = c;
            return 1;
        }
        return 0;
    }
};

// ������ �����
template <class T, int N>
class ststack {
    // ������ ���������
    T st[N];
    // �������
    int count;
    // �������
    int depth;
public:
    // �����������
    ststack() {
        reset();
    }
    // ����������
    ~ststack() {
        printf("ststack: size=%d, depth=%d.\n", N, depth);
    }
    // ������� ������
    void reset(void) {
        depth = count = 0;
        for (int i = 0; i < N; i++) st[i] = 0;
    }
    // ���������� ���������� ���������
    int size(void) {
        return count;
    }
    // ������������ �������
    void push(T value) {
        if (count >= N) throw "ststack::push stack overflow";
        st[count++] = value;
        if (depth < count) depth = count;
    }
    // ����������� �������
    T pop(void) {
        if (count < 1) throw "ststack::pop stack is empty";
        T value = st[--count];
        st[count] = 0;
        return value;
    }
    // ����������� number ���������
    T pop(int number) {
        if (count < number) throw "ststack::pop(int) stack isn't so big as number";
        count -= number;
        return st[count];
    }
    // ���������� ������� �� �������
    T top(void) {
        if (count < 1) throw "ststack::top stack is empty";
        return st[count - 1];
    }
};
