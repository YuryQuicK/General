// 2019 ReVoL Primer Template
// sa4LR.h
// �������������� ����������

#include "syntalr.h"
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
    // LR(1)
    int parse(void) {
        if (!next_token()) return 0;

        // ��������� ���
        short m = 0;
        //������ �� �����
        stack_t s = TOK_EOT;
        // �������� � �������
        stack_t t = TOK_EOT;

        sta.push(TOK_EOT);
        //sta.push(START);
        while (true) {

            // �������� ����� ��������� ������� �������
            s = sta.top();
            t = SYNTA[s][tok.stt];
            fprintf(parse_stream, "\nSYNTA[%d][%d] = %d\n", s, tok.stt, t);

            if (t == ACC) {
                // ������
                break;
            }
            else if (t < 0) {
                // ������
                for (int number = RLEN[-t], i = 0; i < number; i++) {
                    // ������� RLEN[-t] �������� �� �����
                    sta.pop();
                }

                // �������� ���������� � ������� ������������� ���������
                m = RSYM[-t];
                // ������������ � ����������� ��������� ������� ������������
                s = sta.top();
                // �������� ����� ��������� ������� ������������
                t = SYNTA[s][m];
                sta.push(t);
                fprintf(parse_stream, "push: %d\nrule: %d\n\n", t, m);
            }
            else if (t > 0 && t < MAX_DFA_STATE) {
                // �������
                sta.push(t);
                fprintf(parse_stream, "push: %d\n\n", t);
                next_token();
            }
            else if (t > 0) {
                // ������ �������������� �������
                throw "syntaxan: invalid SYNTA";
            }
            else {
                // �������������� ������
                fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
                return 0;
            }

        }

        fprintf(parse_stream, "\nsyntaxan: success\n\n");
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
