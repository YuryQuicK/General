// 2019 ReVoL Primer Template
// lexan.h
// лексический анализатор

#include "sttot.h"

class lexan {
    // входной поток
    FILE * input_stream;
    // поток сообщений
    FILE * error_stream;
    // текущий символ входа
    char cc;
    // возвращает очередной символ входа
    void next_char(void) {
        cc = getc(input_stream);
        //_putch(cc);
    }
    // разбирает комментарий Си
    sttype is_comment() {
        enum {A, B, C} state = A;
        while (true) {
            next_char();
            switch (state) {
            case A:
                /*if (cc == '*') {
                    state = B;
                }*/
                switch (cc) {
                case EOF:
                    printf("\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    state = B;
                    break;
                default:
                    return TOK_DIV;
                }
                break;
            case B:
                switch (cc) {
                case EOF:
                    printf("\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    state = C;
                    break;
                }
                break;
            case C:
                switch (cc) {
                case EOF:
                    printf("\nlexan: unexpected end of file in comment\n\n");
                    return TOK_UNKNOWN;
                case '*':
                    break;
                case '/':
                    return TOK_COMMENT;
                default:
                    state = B;
                    break;
                }
                break;
            }
        }
        return TOK_UNKNOWN;
    }
    // принимает идентификатор
    int get_id(sttoken & tok) {
        tok.stt = TOK_ID;
        int count = 0;
        while (true) {
            cc = tolower(cc);
            switch (TOT[cc]) {
            case ALPHA:
                break;
            case DIGIT:
                break;
            default:
                return is_keyword(tok);
            }
            tok.append(cc);
            next_char();
        }
        return 1;
    }
    // определяет ключевое слово
    int is_keyword(sttoken & tok) {
        if (!strcmp(tok.str_val, "print")) {
            tok.stt = TOK_PRINT;
            return 1;
        }
        else if (!strcmp(tok.str_val, "if")) {
            tok.stt = TOK_IF;
            return 1;
        }
        /*else if (!strcmp(tok.str_val, "int")) {
            tok.stt = TOK_INT;
            return 1;
        }
        else if (!strcmp(tok.str_val, "char")) {
            tok.stt = TOK_CHAR;
            return 1;
        }*/

        // ПОЛИЗ
        else if (!strcmp(tok.str_val, "dim")) {
            tok.stt = TOK_DIM;
            return 1;
        }
        else if (!strcmp(tok.str_val, "as")) {
            tok.stt = TOK_AS;
            return 1;
        }
        else if (!strcmp(tok.str_val, "long")) {
            tok.stt = TOK_LONG;
            return 1;
        }
        else if (!strcmp(tok.str_val, "then")) {
            tok.stt = TOK_THEN;
            return 1;
        }
        else if (!strcmp(tok.str_val, "else")) {
            tok.stt = TOK_ELSE;
            return 1;
        }
        else if (!strcmp(tok.str_val, "end")) {
            tok.stt = TOK_END;
            return 1;
        }

        /*if (!strcmp(tok.str_val, "else")) {
            tok.stt = TOK_ELSE;
            return 1;
        }*/
        return 1;
    }
    // принимает целое число
    int is_number(sttoken & tok) {
        tok.stt = TOK_I4;
        while (true) {
            switch (TOT[cc]) {
            case DIGIT:
                tok.int_val *= 10;
                tok.int_val += cc;
                tok.int_val -= '0';
                break;
            case CHDOT:
                return is_float(tok, 0);
            default:
                return 1;
            }
            next_char();
        }
        return 1;
    }
    // разбирает вещественную часть числа
    int is_float(sttoken & tok, int must) {
        tok.stt = TOK_R8;
        double number = 0.0;
        int div = 0;
        while (true) {
            next_char();
            switch (TOT[cc]) {
            case DIGIT:
                must = 0;
                number *= 10;
                number += cc;
                number -= '0';
                div++;
                break;
            case CHDOT:
                printf("\nlexan: extradot in float\n\n");
                return 0;
            default:
                if (must) {
                    printf("\nlexan: single dot in float\n\n");
                    return 1;
                }
                tok.dbl_val = tok.int_val + number / pow(10, div);
                return 1;
            }
        }
        return 1;
    }
    // разбирает строковый литерал
    int is_quote(sttoken & tok) {
        tok.stt = TOK_QUOTE;
        while (true) {
            next_char();
            if (TOT[cc] == QUOTE) {
                next_char();

                return 1;
            }
            if (cc == EOF) {
                printf("\nlexan: unexpected end of file in qoute\n\n");
                return 0;
            }
            if (cc < 32) {
                printf("\nlexan: extra character in qoute\n\n");
                return 0;
            }
            tok.append(cc);
        }
    }
    // разбирает символ
    int is_symbol(sttoken & tok) {
        tok.stt = TOK_SYMBOL;
        while (true) {
            next_char();
            if (TOT[cc] == SYMBOL) {
                next_char();
                return 1;
            }
            if (cc == EOF) {
                printf("\nlexan: unexpected end of file in symbol\n\n");
                return 0;
            }
            if (cc < 32) {
                printf("\nlexan: extra character in symbol\n\n");
                return 0;
            }
            tok.append(cc);
        }
    }
    // принимает операцию
    int is_opera(sttoken & tok) {
        switch (cc) {
        case '=':
            next_char();
            if (cc == '=') {
                next_char();
                tok.stt = TOK_ASS;
                return 1;
            }
            tok.stt = TOK_EQ;
            return 1;
        case '!':
            next_char();
            tok.stt = TOK_LNOT;
            return 1;
            /*if (cc == '=') {
                next_char();
                tok.stt = TOK_LNOT;
                return 1;
            }*/
        case '<':
            next_char();
            /*if (cc == '=') {
                next_char();
                tok.stt = TOK_LE;
                return 1;
            }*/

            // ПОЛИЗ
            if (cc == '>') {
                next_char();
                tok.stt = TOK_NE;
                return 1;
            }

            tok.stt = TOK_LT;
            return 1;
        case '>':
            next_char();
            /*if (cc == '=') {
                next_char();
                tok.stt = TOK_GE;
                return 1;
            }*/
            tok.stt = TOK_GT;
            return 1;
        case '(':
            next_char();
            tok.stt = TOK_LP;
            return 1;
        case ')':
            next_char();
            tok.stt = TOK_RP;
            return 1;
        case '{':
            next_char();
            tok.stt = TOK_LS;
            return 1;
        case '}':
            next_char();
            tok.stt = TOK_RS;
            return 1;
        case '+':
            next_char();
            tok.stt = TOK_ADD;
            return 1;
        case '-':
            next_char();
            tok.stt = TOK_SUB;
            return 1;
        case '*':
            next_char();
            tok.stt = TOK_MUL;
            return 1;
        case '/':
            next_char();
            tok.stt = TOK_DIV;
            return 1;
        case ';':
            tok.stt = TOK_SEMI;
            next_char();
            return 1;
        case ',':
            tok.stt = TOK_COMMA;
            next_char();
            return 1;
        case '[':
            tok.stt = TOK_LB;
            next_char();
            return 1;
        case ']':
            tok.stt = TOK_RB;
            next_char();
            return 1;
        case '&':
            next_char();
            if (cc == '&') {
                tok.stt = TOK_LAND;
                next_char();
                return 1;
            }
            tok.stt = TOK_UNKNOWN;
            return 0;
        case '|':
            next_char();
            if (cc == '|') {
                tok.stt = TOK_LOR;
                next_char();
                return 1;
            }
            tok.stt = TOK_UNKNOWN;
            return 0;
        }
        return 1;
    }
public:
    // возвращает очередной токен потока
    int next_token(sttoken & tok) {
        // ищем первый символ лексемы
        while (1) {
            if (cc == EOF) {
                // конец текста
                tok.stt = TOK_EOT;
                return 1;
            }
            else if (cc == '/') {
                // слэш неоднозначен в Си
                sttype result = is_comment();
                if (result == TOK_DIV) {
                    // это операция деления, а не comment
                    tok.stt = TOK_DIV;
                    return 1;
                } else if (result == TOK_UNKNOWN) {
                    // ошибка в комментарии
                    return 0;
                }
                // comment пропускаем
            }
            else if (cc < 33) {
                // управляющие символы и пробел пропускаем, кроме LF
                if (cc == 10) {
                    next_char();
                    tok.stt = TOK_LF;
                    return 1;
                }
            }
            else {
                // другой символ разбираем дальше
                break;
            }
            // следующий символ
            next_char();
        }
        // подготавливаем токен
        tok.reset();
        // разбираем первый символ лексемы
        switch (TOT[cc]) {
        case ALPHA:
            return get_id(tok);
        case DIGIT:
            return is_number(tok);
        case CHDOT:
            return is_float(tok, 1);
        case QUOTE:
            return is_quote(tok);
        case SYMBOL:
            return is_symbol(tok);
        default:
            return is_opera(tok);
        }
        //return 0;
    }
    // конструктор
    lexan(FILE * input_stream, FILE * error_stream) {
        this->input_stream = input_stream;
        this->error_stream = error_stream;
        // первый символ потока
        next_char();
    }
};
