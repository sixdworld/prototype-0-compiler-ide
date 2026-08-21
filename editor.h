#ifndef EDITOR_H
#define EDITOR_H

#define MAX_LINES 500
#define MAX_LINE_LENGTH 256

typedef struct
{
    char lines[MAX_LINES][MAX_LINE_LENGTH];

    int line_count;

    int cursor_x;
    int cursor_y;

} Editor;

void editor_init(Editor *editor);

int editor_load(
    Editor *editor,
    const char *filename
);

int editor_save(
    Editor *editor,
    const char *filename
);

void editor_handle_key(
    Editor *editor,
    int ch
);

void editor_draw(
    Editor *editor,
    int start_row,
    int height
);

#endif