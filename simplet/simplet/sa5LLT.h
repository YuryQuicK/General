// 2019 ReVoL Primer Template
// sa5LLT.h
// синтаксический анализатор

#include "syntallo.h"
#include "stsyms.h"
#include "ststrip.h"
// размер стека МП-автомата
#define MAX_STACK 64
// размер вычислительного стека
#define MAX_EXEST 64
// размер таблицы символов
#define MAX_SYMS 16
// размер стека меток
#define MAX_LABEL 16
// размер ленты
#define MAX_STRIP 64
// предел числа итераций
#define MAX_IT 999

class syntaxan {
public:
    // конструктор
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }
    // LL(1) трансляция в ПОЛИЗ
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
            // состояние на стеке
            //s = sta.top();
            s = clear_stack();
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
                // выталкиваем операционные символы
                clear_stack();
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

        // записываем конец ленты ПОЛИЗ
        out(OUT_END);
        // выводим содержимое ленты ПОЛИЗ
        strip.print(parse_stream);
        execute();

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
    // таблица символов
    stsyms<MAX_SYMS> syms;
    // исполняющий стек
    exstack<MAX_EXEST> exe;
    // лента ПОЛИЗ
    ststrip<MAX_STRIP> strip;
    // стек меток
    ststack<int, MAX_LABEL> stl;
    // стек МП-автомата
    ststack<stack_t, MAX_STACK> sta;
    // возвращает очередной токен
    int next_token() {
        return lex->next_token(tok);
    }
    // запись символна на ленту ПОЛИЗ
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
    // выводит операционные символы со стека
    stack_t clear_stack() {
        stack_t s;
        while ((s = sta.top()) > SYM_LAST) {
            s = sta.pop();
            out((sttype)s);
        }
        return s;
    }
    // извлекает из стека значение
    void exe_pop(exstel &e) {
        exe.pop(e);
        if (e.stt == OUT_I4) {

        }
        else if (e.stt == OUT_ID) {
            int j = syms.find(e);
            if (j == ST_NOTFOUND) {
                // символ не найден
                throw "exe_pop identifier not found";
            }
            // извлекаем значение из таблицы символов
            e.int_val = syms[j].int_val;
            // меняем тип элемента на константный
            e.stt = OUT_I4;
        }
        else {
            // неправильная лента ПОЛИЗ
            throw "exe_pop internal error";
        }
    }
    // исполняющая машина ПОЛИЗ
    void execute() {
        // счетчик операций ПОЛИЗ
        int it_counter = 1;
        // указатель ленты ПОЛИЗ
        int strip_pointer = 1;
        // текущий элемент ПОЛИЗ
        sttype stt;
        // переменные для вычислений
        exstel X, Y;
        // вспомогатеьлные
        int j = 0;

        // рабочий цикл выполнения ленты ПОЛИЗ
        while (1) {
            // очистим переменные
            X.reset();
            Y.reset();
            // считываем тип элемента ленты
            stt = strip[strip_pointer].stt;
            switch (stt) {

            case OUT_END:
                fprintf(error_stream, "EXE DONE\n\n");
                return;

            case OUT_ID: case OUT_I4: case OUT_LONG:
                // проталкиваем в стек
                exe.push(strip[strip_pointer]);
                // следующий элемент ленты
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
                // на стек помещаем значение метки
                X.int_val = strip[strip_pointer].int_val;
                // тип значения - константа
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
