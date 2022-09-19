// 2019 ReVoL Primer Template
// sa3LL.h
// �������������� ����������

#include "syntall.h"
// ������ ����� ��-��������
#define MAX_STACK 64

class syntaxan {
public:
    // �����������
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LL(1)
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

            s = sta.top();
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
    // ���� ��-��������
    ststack<stack_t, MAX_STACK> sta;
    // ���������� ��������� �����
    int next_token() {
        return lex->next_token(tok);
    }
};
