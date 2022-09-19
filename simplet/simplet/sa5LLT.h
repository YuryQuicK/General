// 2019 ReVoL Primer Template
// sa5LLT.h
// �������������� ����������

#include "syntallo.h"
#include "stsyms.h"
#include "ststrip.h"
// ������ ����� ��-��������
#define MAX_STACK 64
// ������ ��������������� �����
#define MAX_EXEST 64
// ������ ������� ��������
#define MAX_SYMS 16
// ������ ����� �����
#define MAX_LABEL 16
// ������ �����
#define MAX_STRIP 64
// ������ ����� ��������
#define MAX_IT 999

class syntaxan {
public:
    // �����������
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LL(1) ���������� � �����
    int parse(void) {
        if (!next_token()) return 0;

        // �������� � ����� �������
        int i = 0, n = 0;
        // ��������������� ������� ��� ������� ������������ ������
        stack_t at = TOK_EOT, bt = TOK_EOT;
        // ������ �� �����
        stack_t s = TOK_EOT;
        // ��������, ��������� �� ����������� �������
        stack_t t = TOK_EOT;

        get_rule_len();
        // ���������� ��� �����
        sta.push(TOK_EOT);
        // START - ������� ����������
        sta.push(START);

        while (true) {
            // ��������� �� �����
            //s = sta.top();
            s = clear_stack();
            t = SYNTA[s][tok.stt];
            printf("\nSYNTA[%d][%d] = %d\n", s, tok.stt, t);

            if (t <= 0) {
                // ������
                fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
                return 0;
            }
            else if (t == ACC) {
                // ������
                break;
            }
            else if (t == POP) {
                // ������
                at = sta.pop();
                // ����������� ������������ �������
                clear_stack();
                if (!next_token()) {
                    printf("\nstack isn't empty!\n\n");
                    return 0;
                }
            }
            else if (t <= MAX_RULE) {
                // �������
                at = sta.pop();
                n = RLEN[t];

                // ������������ ������� t � ���� ����� �������
                for (int i = n - 1; i >= 0; i--) {
                    sta.push(bt = RULE[t][i]);
                    fprintf(parse_stream, "push %d\n", bt);
                }
                printf("\n");
            }
            else {
                // ������ ����������� �������
                throw "syntaxan: invalid SYNTA";
            }
        }

        // ���������� ����� ����� �����
        out(OUT_END);
        // ������� ���������� ����� �����
        strip.print(parse_stream);
        execute();

        fprintf(parse_stream, "\nsyntaxan: success.\n\n");
        return 1;
    }
private:
    // ������ �� ����������� ����������
    lexan * lex;
    // ����� ����������
    FILE * parse_stream;
    // ����� ���������
    FILE * error_stream;
    // ������� �����
    sttoken tok;
    // ������� ��������
    stsyms<MAX_SYMS> syms;
    // ����������� ����
    exstack<MAX_EXEST> exe;
    // ����� �����
    ststrip<MAX_STRIP> strip;
    // ���� �����
    ststack<int, MAX_LABEL> stl;
    // ���� ��-��������
    ststack<stack_t, MAX_STACK> sta;
    // ���������� ��������� �����
    int next_token() {
        return lex->next_token(tok);
    }
    // ������ �������� �� ����� �����
    void out(sttype tt) {
        int i = 0, j = 0;
        sttoken t = tok;
        t.stt = tt;
        switch (tt) {
        case OUT_PUSH:
            j = strip.new_label();
            stl.push(j);
            t.int_val = j;
            t.stt = OUT_LABEL;
            break;
        case OUT_POPL:
            j = stl.pop();
            t.int_val = j;
            t.stt = OUT_LABEL;
            break;
        case OUT_SWAP:
            i = stl.pop();
            j = stl.pop();
            stl.push(i);
            t.int_val = j;
            t.stt = OUT_LABEL;
            break;
        }
        strip.add(t);
    }
    // ������� ������������ ������� �� �����
    stack_t clear_stack() {
        stack_t s;
        while ((s = sta.top()) > SYM_LAST) {
            s = sta.pop();
            out((sttype)s);
        }
        return s;
    }
    // ��������� �� ����� ��������
    void exe_pop(exstel &e) {
        exe.pop(e);
        if (e.stt == OUT_I4) {

        }
        else if (e.stt == OUT_ID) {
            int j = syms.find(e);
            if (j == ST_NOTFOUND) {
                // ������ �� ������
                throw "exe_pop identifier not found";
            }
            // ��������� �������� �� ������� ��������
            e.int_val = syms[j].int_val;
            // ������ ��� �������� �� �����������
            e.stt = OUT_I4;
        }
        else {
            // ������������ ����� �����
            throw "exe_pop internal error";
        }
    }
    // ����������� ������ �����
    void execute() {
        // ������� �������� �����
        int it_counter = 1;
        // ��������� ����� �����
        int strip_pointer = 1;
        // ������� ������� �����
        sttype stt;
        // ���������� ��� ����������
        exstel X, Y;
        // ���������������
        int j = 0;

        // ������� ���� ���������� ����� �����
        while (1) {
            // ������� ����������
            X.reset();
            Y.reset();
            // ��������� ��� �������� �����
            stt = strip[strip_pointer].stt;
            switch (stt) {

            case OUT_END:
                fprintf(error_stream, "EXE DONE\n\n");
                return;

            case OUT_ID: case OUT_I4: case OUT_LONG:
                // ������������ � ����
                exe.push(strip[strip_pointer]);
                // ��������� ������� �����
                strip_pointer++;
                break;

            case OUT_DIM:
                exe.pop(Y);
                exe.pop(X);

                j = syms.insert(X);
                if (j == ST_EXISTS) {
                    throw "exe duplicate declaration";
                }
                strip_pointer++;
                break;

            case OUT_ASS:
                exe_pop(Y);
                exe.pop(X);

                j = syms.find(X);
                if (j == ST_NOTFOUND) {
                    throw "exe identifier not found";
                }
                syms[j].int_val = Y.int_val;
                strip_pointer++;
                break;

            case OUT_ADD: case OUT_SUB: case OUT_MUL: case OUT_DIV:
            case OUT_EQ: case OUT_NE: case OUT_LT: case OUT_GT:
                exe_pop(Y);
                exe_pop(X);

                switch (stt) {
                case OUT_ADD:
                    X.int_val += Y.int_val;
                    break;
                case OUT_SUB:
                    X.int_val -= Y.int_val;
                    break;
                case OUT_MUL:
                    X.int_val *= Y.int_val;
                    break;
                case OUT_DIV:
                    if (!Y.int_val) throw "exe division by zero";
                    X.int_val /= Y.int_val;
                    break;
                case OUT_EQ:
                    if (X.int_val == Y.int_val) X.int_val = 1; else X.int_val = 0;
                    break;
                case OUT_NE:
                    if (X.int_val != Y.int_val) X.int_val = 1; else X.int_val = 0;
                    break;
                case OUT_LT:
                    if (X.int_val < Y.int_val) X.int_val = 1; else X.int_val = 0;
                    break;
                case OUT_GT:
                    if (X.int_val > Y.int_val) X.int_val = 1; else X.int_val = 0;
                    break;
                }

                exe.push(X);
                strip_pointer++;
                break;
            
            case OUT_LABEL:
                // �� ���� �������� �������� �����
                X.int_val = strip[strip_pointer].int_val;
                // ��� �������� - ���������
                X.stt = OUT_I4;
                exe.push(X);
                strip_pointer++;
                break;

            case OUT_DEFL:
                exe.pop(X);
                strip_pointer++;
                break;

            case OUT_BZ:
                exe_pop(Y);
                exe_pop(X);

                if (!X.int_val) {
                    j = strip.find_DEF(Y.int_val);
                    if (j == -1) throw "exe label not found";
                    strip_pointer = j;
                }
                else {
                    strip_pointer++;
                }
                break;

            case OUT_BR:
                exe_pop(Y);
                j = strip.find_DEF(Y.int_val);
                if (j == -1) throw "exe label not found";
                strip_pointer = j;
                break;

            case OUT_PRINT:
                exe_pop(Y);
                fprintf(parse_stream, "exe print %d\n", Y.int_val);
                strip_pointer++;
                break;
            }
            if (++it_counter > MAX_IT) {
                throw "exe deadlock";
            }
        }
    }
};
