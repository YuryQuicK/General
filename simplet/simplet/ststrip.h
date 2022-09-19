// 2019 ReVoL Primer Template
// ststrip.h
// ������ ����� ����������� �������������

// ������� �����
typedef sttoken exstel;

// �����
template <int N>
class ststrip {
    // ������ ���������
    exstel st[N];
    // ������� ���������
    int count;
    // ������� �����
    int label;
    // �������
    int depth;
public:
    // �����������
    ststrip() {
        reset();
        st[0].stt = OUT_START;
    }
    // ����������
    ~ststrip() {
        printf("ststrip: size=%d, depth=%d.\n", N, depth - 1);
    }
    // ������� ������
    void reset(void) {
        count = 1;
        depth = label = 0;
        for (int i = 0; i < N; i++) st[i].reset();
    }
    // ���������� ���������� ���������
    int size(void) {
        return count - 1;
    }
    // ���������� ����� ������������� �����
    int new_label() {
        return ++label;
    }
    // ���������� ��������� �������
    exstel & operator [] (int index) {
        if (index < 1 || index >= count) throw "ststrip::operator[] invalid index";
        return st[index];
    }
    // ��������� �������
    void add(exstel e) {
        if (count >= N) throw "ststrip::add strip overflow";
        st[count++] = e;
        if (depth < count) depth = count;
    }
    // ���� �� ����� ����������� ����� � ��������������� id
    int find_DEF(int id) {
        for (int i = 1; i < count; i++) {
            if (st[i].stt == OUT_END) return -1; // ����� �����
            if (st[i].stt == OUT_LABEL && st[i].int_val == id) {
                if (st[i + 1].stt == OUT_DEFL) {
                    return (i + 2);
                }
            }
        }
        return -1;
    }
    // ����� � ��������� ����
    void print(FILE * f) {
        fprintf(f, "\nstrip\n");
        for (int i = 1; i < count; i++) {
            fprintf(f, "%03d ", i);
            switch (st[i].stt) {
            case OUT_ID:    fprintf(f, "ID %s\n", st[i].str_val); break;
            case OUT_I4:    fprintf(f, "I4 %d\n", st[i].int_val); break;
            case OUT_R8:    fprintf(f, "R8 %g\n", st[i].dbl_val); break;
            case OUT_LABEL: fprintf(f, "LABEL %d\n", st[i].int_val); break;
            case OUT_DEFL:  fprintf(f, "DEFL\n"); break;
            case OUT_PUSH:  fprintf(f, "PUSH\n"); break;
            case OUT_POPL:  fprintf(f, "POPL\n"); break;
            case OUT_SWAP:  fprintf(f, "SWAP\n"); break;
            case OUT_BZ:    fprintf(f, "BZ\n"); break;
            case OUT_BR:    fprintf(f, "BR\n"); break;
            case OUT_EQ:    fprintf(f, "EQ\n"); break;
            case OUT_NE:    fprintf(f, "NE\n"); break;
            case OUT_LT:    fprintf(f, "LT\n"); break;
            case OUT_GT:    fprintf(f, "GT\n"); break;
            case OUT_LE:    fprintf(f, "LE\n"); break;
            case OUT_GE:    fprintf(f, "GE\n"); break;
            case OUT_DIM:   fprintf(f, "DIM\n"); break;
            case OUT_ASS:   fprintf(f, "ASS\n"); break;
            case OUT_ADD:   fprintf(f, "ADD\n"); break;
            case OUT_SUB:   fprintf(f, "SUB\n"); break;
            case OUT_MUL:   fprintf(f, "MUL\n"); break;
            case OUT_DIV:   fprintf(f, "DIV\n"); break;
            case OUT_PRINT: fprintf(f, "PRINT\n"); break;
            case OUT_LONG:  fprintf(f, "LONG\n"); break;
            case OUT_INT:   fprintf(f, "INT\n"); break;
            case OUT_END:   fprintf(f, "END\n"); break;
            default: fprintf(f, "UNKNOWN\n");
            }
        }
        fprintf(f, "\n");
    }
};

// �������������� ���� �����
template <int N>
class exstack {
private:
    // ������ ���������
    exstel st[N];
    // �������
    int count;
    // �������
    int depth;
public:
    // �����������
    exstack() {
        count = 0;
        depth = 0;
    }
    // ����������
    ~exstack() {
        printf("exstack: size=%d, depth=%d.\n", N, depth);
    }
    // ���������� ���������� ���������
    int size(void) {
        return count;
    }
    // ������������ �������
    void push(exstel & e) {
        if (count >= N) throw "exstack::push exe-stack overflow";
        st[count++] = e;
        if (depth < count) {
            depth = count;
        }
    }
    // ����������� �������
    void pop(exstel & e) {
        if (count < 1) throw "exstack::push exe-stack is empty";
        e = st[--count];
        st[count].reset();
    }
};
