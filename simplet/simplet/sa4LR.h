// 2019 ReVoL Primer Template
// sa4LR.h
// синтаксический анализатор

#include "syntalr.h"
// размер стека МП-автомата
#define MAX_STACK 64

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LR(1)
    int parse(void) {
        if (!next_token()) return 0;

        // состояние ДКА
        short m = 0;
        //символ на стеке
        stack_t s = TOK_EOT;
        // значение в таблице
        stack_t t = TOK_EOT;

        sta.push(TOK_EOT);
        //sta.push(START);
        while (true) {

            // получаем номер множества базовых пунктов
            s = sta.top();
            t = SYNTA[s][tok.stt];
            fprintf(parse_stream, "\nSYNTA[%d][%d] = %d\n", s, tok.stt, t);

            if (t == ACC) {
                // допуск
                break;
            }
            else if (t < 0) {
                // свёртка
                for (int number = RLEN[-t], i = 0; i < number; i++) {
                    // снимаем RLEN[-t] символов со стека
                    sta.pop();
                }

                // получаем нетерминал в который сворачивается продукция
                m = RSYM[-t];
                // возвращаемся к предыдущему множеству базовых нетерминалов
                s = sta.top();
                // получаем новое множество базовых нетерминалов
                t = SYNTA[s][m];
                sta.push(t);
                fprintf(parse_stream, "push: %d\nrule: %d\n\n", t, m);
            }
            else if (t > 0 && t < MAX_DFA_STATE) {
                // перенос
                sta.push(t);
                fprintf(parse_stream, "push: %d\n\n", t);
                next_token();
            }
            else if (t > 0) {
                // ошибка синтаксической таблицы
                throw "syntaxan: invalid SYNTA";
            }
            else {
                // синтаксическая ошибка
                fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
                return 0;
            }

        }

        fprintf(parse_stream, "\nsyntaxan: success\n\n");
        return 1;
    }
private:
    // ссылка на лексический анализатор
    lexan * lex;
    // поток результата
    FILE * parse_stream;
    // поток сообщений
    FILE * error_stream;
    // текущий токен
    sttoken tok;
    // стек МП-автомата
    ststack<stack_t, MAX_STACK> sta;
    // возвращает очередной токен
    int next_token() {
        return lex->next_token(tok);
    }
};
