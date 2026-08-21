#include "error.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static CompilerError error_list[MAX_ERRORS];
static int error_count = 0;

void errors_init(void)
{
    error_count = 0;
}

void compiler_error(
    int line,
    int column,
    const char *format,
    ...
)
{
    if (error_count >= MAX_ERRORS)
        return;

    CompilerError *error =
        &error_list[error_count];

    error->line = line;
    error->column = column;

    va_list args;

    va_start(args, format);

    vsnprintf(
        error->message,
        MAX_ERROR_LENGTH,
        format,
        args
    );

    va_end(args);

    error_count++;
}

int errors_count(void)
{
    return error_count;
}

CompilerError *errors_get(int index)
{
    if (index < 0 || index >= error_count)
        return NULL;

    return &error_list[index];
}