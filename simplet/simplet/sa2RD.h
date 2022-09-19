// 2019 ReVoL Primer Template
// sa2RD.h
// �������������� ����������

class syntaxan {
public:
    // �����������
    syntaxan(lexan * lex, FILE * parse_stream, FILE * error_stream) {
        this->lex = lex;
        this->parse_stream = parse_stream;
        this->error_stream = error_stream;
    }

    char is_plus() { if (tok.stt == TOK_ADD) return 1; return 0; }
    char is_mult() { if (tok.stt == TOK_MUL) return 1; return 0; }
    char is_sub() { if (tok.stt == TOK_SUB) return 1; return 0; }
    char is_div() { if (tok.stt == TOK_DIV) return 1; return 0; }

    int P(double & value) {
        if (tok.stt == TOK_ADD || tok.stt == TOK_MUL || tok.stt == TOK_SUB || tok.stt == TOK_DIV) return 0;
        if (tok.stt == TOK_LP) {
            next_token();
            if (!E(value)) return 0;
            if (tok.stt != TOK_RP) return 0;
        }
        else {
            if (tok.stt == TOK_I4) value = tok.int_val;
            else if (tok.stt = TOK_R8) value = tok.dbl_val;
        }
        next_token();
        return 1;
    }
    int T(double & value) {
        double mul = 0.0;
        char flag = 0;
        if (!P(value)) return 0;
        while (is_mult() || is_div()) {
            if (is_mult()) flag = 1; else flag = 0;
            next_token();
            if (!P(mul)) return 0;
            if (flag) value *= mul; else value /= mul;
        }
        return 1;
    }
    int E(double & value) {
        double num = 0.0;
        char flag = 0;
        if (!T(value)) return 0;
        while (is_plus() || is_sub()) {
            if (is_plus()) flag = 1; else flag = 0;
            next_token();
            if (!T(num)) return 0;
            if (flag) value += num; else value -= num;
        }
        return 1;
    }

    // ����������� �����
    int parse(void) {
        if (!next_token()) return 0;
        double result = 0.0;
        //next_token();
        if (E(result)) printf("%.3lf\n", result);
        else printf("Failure\n");
        //fprintf(parse_stream, "\nsyntaxan: success.\n\n");
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
    // ���������� ��������� �����
    int next_token() {
        return lex->next_token(tok);
    }
};