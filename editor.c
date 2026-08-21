#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#include "editor.h"


void editor_init(Editor *editor)
{
    memset(editor, 0, sizeof(Editor));

    editor->line_count = 1;
    editor->cursor_x = 0;
    editor->cursor_y = 0;
}


int editor_load(Editor *editor, const char *filename)
{
    FILE *file;
    char buffer[MAX_LINE_LENGTH];

    editor_init(editor);

    file = fopen(filename, "r");

    if (file == NULL)
    {
        return -1;
    }

    editor->line_count = 0;

    while (
        editor->line_count < MAX_LINES &&
        fgets(buffer, sizeof(buffer), file) != NULL
    )
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        strncpy(
            editor->lines[editor->line_count],
            buffer,
            MAX_LINE_LENGTH - 1
        );

        editor->lines[editor->line_count]
                     [MAX_LINE_LENGTH - 1] = '\0';

        editor->line_count++;
    }

    fclose(file);

    if (editor->line_count == 0)
    {
        editor->line_count = 1;
    }

    return 0;
}


int editor_save(Editor *editor, const char *filename)
{
    FILE *file;

    file = fopen(filename, "w");

    if (file == NULL)
    {
        return -1;
    }

    for (
        int i = 0;
        i < editor->line_count;
        i++
    )
    {
        fprintf(
            file,
            "%s\n",
            editor->lines[i]
        );
    }

    fclose(file);

    return 0;
}


/* Insert a character */

static void insert_character(Editor *editor, int ch)
{
    char *line =
        editor->lines[editor->cursor_y];

    int length = strlen(line);

    if (length >= MAX_LINE_LENGTH - 1)
    {
        return;
    }

    memmove(
        &line[editor->cursor_x + 1],
        &line[editor->cursor_x],
        length - editor->cursor_x + 1
    );

    line[editor->cursor_x] = (char)ch;

    editor->cursor_x++;
}


/* Create a new line */

static void insert_newline(Editor *editor)
{
    if (editor->line_count >= MAX_LINES)
    {
        return;
    }

    for (
        int i = editor->line_count;
        i > editor->cursor_y + 1;
        i--
    )
    {
        strcpy(
            editor->lines[i],
            editor->lines[i - 1]
        );
    }

    char *line =
        editor->lines[editor->cursor_y];

    char remaining[MAX_LINE_LENGTH];

    strcpy(
        remaining,
        &line[editor->cursor_x]
    );

    line[editor->cursor_x] = '\0';

    strcpy(
        editor->lines[editor->cursor_y + 1],
        remaining
    );

    editor->line_count++;

    editor->cursor_y++;
    editor->cursor_x = 0;
}


/* Backspace */

static void backspace(Editor *editor)
{
    if (editor->cursor_x > 0)
    {
        char *line =
            editor->lines[editor->cursor_y];

        memmove(
            &line[editor->cursor_x - 1],
            &line[editor->cursor_x],
            strlen(&line[editor->cursor_x]) + 1
        );

        editor->cursor_x--;

        return;
    }

    /*
     * At the start of a line:
     * merge with the previous line.
     */

    if (editor->cursor_y > 0)
    {
        int previous_length =
            strlen(
                editor->lines[
                    editor->cursor_y - 1
                ]
            );

        int current_length =
            strlen(
                editor->lines[
                    editor->cursor_y
                ]
            );

        if (
            previous_length +
            current_length >=
            MAX_LINE_LENGTH
        )
        {
            return;
        }

        strcat(
            editor->lines[
                editor->cursor_y - 1
            ],
            editor->lines[
                editor->cursor_y
            ]
        );

        for (
            int i = editor->cursor_y;
            i < editor->line_count - 1;
            i++
        )
        {
            strcpy(
                editor->lines[i],
                editor->lines[i + 1]
            );
        }

        editor->line_count--;

        editor->cursor_y--;

        editor->cursor_x =
            previous_length;
    }
}


void editor_handle_key(
    Editor *editor,
    int ch
)
{
    switch (ch)
    {
        case KEY_UP:

            if (editor->cursor_y > 0)
            {
                editor->cursor_y--;

                int length =
                    strlen(
                        editor->lines[
                            editor->cursor_y
                        ]
                    );

                if (editor->cursor_x > length)
                {
                    editor->cursor_x = length;
                }
            }

            break;


        case KEY_DOWN:

            if (
                editor->cursor_y <
                editor->line_count - 1
            )
            {
                editor->cursor_y++;

                int length =
                    strlen(
                        editor->lines[
                            editor->cursor_y
                        ]
                    );

                if (editor->cursor_x > length)
                {
                    editor->cursor_x = length;
                }
            }

            break;


        case KEY_LEFT:

            if (editor->cursor_x > 0)
            {
                editor->cursor_x--;
            }

            break;


        case KEY_RIGHT:
        {
            int length =
                strlen(
                    editor->lines[
                        editor->cursor_y
                    ]
                );

            if (editor->cursor_x < length)
            {
                editor->cursor_x++;
            }

            break;
        }


        case '\n':
        case KEY_ENTER:

            insert_newline(editor);

            break;


        case KEY_BACKSPACE:
        case 127:
        case 8:

            backspace(editor);

            break;


        default:

            if (
                ch >= 32 &&
                ch <= 126
            )
            {
                insert_character(
                    editor,
                    ch
                );
            }

            break;
    }
}


void editor_draw(
    Editor *editor,
    int start_row,
    int height
)
{
    for (
        int i = 0;
        i < height;
        i++
    )
    {
        int line_number = i;

        int screen_row =
            start_row + i;

        move(screen_row, 0);
        clrtoeol();

        if (
            line_number <
            editor->line_count
        )
        {
            mvprintw(
                screen_row,
                1,
                "%3d | %s",
                line_number + 1,
                editor->lines[line_number]
            );
        }
        else
        {
            mvprintw(
                screen_row,
                1,
                "%3d |",
                line_number + 1
            );
        }
    }

    int cursor_screen_y =
        start_row + editor->cursor_y;

    int cursor_screen_x =
        6 + editor->cursor_x;

    /*
     * Make sure the cursor is inside
     * the editor area.
     */
    if (
        cursor_screen_y >= start_row &&
        cursor_screen_y < start_row + height
    )
    {
        move(
            cursor_screen_y,
            cursor_screen_x
        );

        curs_set(2);
    }
}