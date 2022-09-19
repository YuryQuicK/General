// 2019 ReVoL Primer Template
// simplet.cpp
// �������� �������

#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
// �������� ���� � �������
#include "types.h"
// ����������� ����������
#include "lexan.h"
// �������������� ����������
//#include "sa1null.h"
//#include "sa2RD.h"
//#include "sa3LL.h"
//#include "sa4LR.h"
#include "sa5LLT.h"

int simplet(FILE * input) {
    // ����������� ����������
    try {
        // �������������� ������
        return (new syntaxan(new lexan(input, stdout), stdout, stdout))->parse();
    } catch(const char * e) {
        printf("\nException raised %s.\n\n", e);
    } catch(...) {
        printf("\nUnexpected exception raised.\n\n");
    }
    return 0; // �������
}

int main(int argc, char * argv[]) {
    // ��������� ������� �����
    FILE * input = fopen("..\\2.st", "rt");
    if (!input) {
        // �������� � ������� ������
        printf("simplet: error while open input file\n\n");
        return 1; // �������
    }
    // ���������� ����������
    __try {
        return (simplet(input)) == 0 ? 1 : 0;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        unsigned int code = GetExceptionCode();
        if (code == EXCEPTION_ACCESS_VIOLATION) {
            printf("\nAccess violation raised.\n\n");
        } else if (code == EXCEPTION_STACK_OVERFLOW) {
            printf("\nStack overflow raised.\n\n");
        } else {
            printf("\nHardware exception raised.\n\n");
        }
    }
    return 1; // �������
}
