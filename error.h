#ifndef ERROR_H
#define ERROR_H

#define MAX_ERRORS 100
#define MAX_ERROR_LENGTH 256

typedef struct {
    int line;
    int column;
    char message[MAX_ERROR_LENGTH];
} CompilerError;

void errors_init(void);

void compiler_error(
    int line,
    int column,
    const char *format,
    ...
);

int errors_count(void);

CompilerError *errors_get(int index);

#endif