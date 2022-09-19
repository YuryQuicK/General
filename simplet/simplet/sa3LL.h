// 2019 ReVoL Primer Template
// sa3LL.h
// синтаксический анализатор

#include "syntall.h"
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
    // LL(1)
    int parse(void) {
        if (!next_token()) return 0;
        
        // итератор и длина правила
        int i = 0, n = 0;
        // вспомогательные символы для анализа неправильной работы
        stack_t at = TOK_EOT, bt = TOK_EOT;
        // символ на стеке
        stack_t s = TOK_EOT;
        // значение, считанное из управляющей таблицы
        stack_t t = TOK_EOT;

        get_rule_len();
        // обозначаем дно стека
        sta.push(TOK_EOT);
        // START - аксиома грамматики
        sta.push(START);

        while (true) {

            s = sta.top();
            t = SYNTA[s][tok.stt];
            printf("\nSYNTA[%d][%d] = %d\n", s, tok.stt, t);

            if (t <= 0) {
                // ошибка
                fprintf(parse_stream, "\nsyntaxan: failure synta = %d\n\n", t);
                return 0;
            } 
            else if (t == ACC) {
                // допуск
                break;
            }
            else if (t == POP) {
                // выброс
                at = sta.pop();
                if (!next_token()) {
                    printf("\nstack isn't empty!\n\n");
                    return 0;
                }
            }
            else if (t <= MAX_RULE) {
                // правило
                at = sta.pop();
                n = RLEN[t];

                // проталкиваем правило t в стек задом наперед
                for (int i = n - 1; i >= 0; i--) {
                    sta.push(bt = RULE[t][i]);
                    fprintf(parse_stream, "push %d\n", bt);
                }
                printf("\n");
            }
            else {
                // ошибка управляющей таблицы
                throw "syntaxan: invalid SYNTA";
            }
        }

        fprintf(parse_stream, "\nsyntaxan: success.\n\n");
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
