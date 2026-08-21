#include <ncurses.h>
#include <string.h>

#include "ui.h"

#define MAX_MESSAGES 50
#define MESSAGE_LENGTH 256

static char messages[MAX_MESSAGES][MESSAGE_LENGTH];
static int message_count = 0;


void ui_init(void)
{
    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);

    timeout(-1);
    
    mousemask(
        BUTTON1_CLICKED | BUTTON1_PRESSED,
        NULL
    );
    /*
     * The editor needs a visible cursor.
     */
    curs_set(2);

    if (has_colors())
    {
        start_color();

        init_pair(
            1,
            COLOR_WHITE,
            COLOR_BLUE
        );

        init_pair(
            2,
            COLOR_BLACK,
            COLOR_CYAN
        );

        init_pair(
            3,
            COLOR_YELLOW,
            COLOR_BLACK
        );
    }
}


void ui_shutdown(void)
{
    endwin();
}


void ui_clear_messages(void)
{
    message_count = 0;
}


void ui_set_message(const char *message)
{
    if (message_count >= MAX_MESSAGES)
        return;

    strncpy(
        messages[message_count],
        message,
        MESSAGE_LENGTH - 1
    );

    messages[message_count][MESSAGE_LENGTH - 1] = '\0';

    message_count++;
}


void ui_draw(Editor *editor)
{
    erase();


    /* =========================
       TOP MENU
       ========================= */

    attron(COLOR_PAIR(1));

    mvprintw(
        0,
        0,
        " File   Edit   Compile   Run "
    );

    for (int i = 45; i < COLS; i++)
    {
        mvaddch(0, i, ' ');
    }

    attroff(COLOR_PAIR(1));


    /* =========================
       FILE TITLE
       ========================= */

    attron(COLOR_PAIR(2));

    mvprintw(
        1,
        0,
        " source_code.p0"
    );

    attroff(COLOR_PAIR(2));


    mvhline(
        2,
        0,
        ACS_HLINE,
        COLS
    );


    /* =========================
       EDITOR AREA
       ========================= */

    int editor_top = 3;

    /*
     * Reserve the bottom part
     * for messages.
     */
    int message_top = LINES - 8;

    int editor_height =
        message_top - editor_top;


    editor_draw(
        editor,
        editor_top,
        editor_height
    );


    /* =========================
       MESSAGE AREA
       ========================= */

    mvhline(
        message_top,
        0,
        ACS_HLINE,
        COLS
    );


    attron(COLOR_PAIR(3));

    mvprintw(
        message_top + 1,
        2,
        "Messages / Output"
    );

    attroff(COLOR_PAIR(3));


    int max_visible_messages = 5;

    int start =
        message_count -
        max_visible_messages;

    if (start < 0)
        start = 0;


    int row =
        message_top + 2;


    for (
        int i = start;
        i < message_count;
        i++
    )
    {
        if (row >= LINES - 1)
            break;

        mvprintw(
            row,
            2,
            "%s",
            messages[i]
        );

        row++;
    }


    /* =========================
       STATUS BAR
       ========================= */

    attron(COLOR_PAIR(1));

    mvhline(
        LINES - 1,
        0,
        ' ',
        COLS
    );

    mvprintw(
        LINES - 1,
        1,
        "F2 Save | F9 Compile | Ctrl+R Run | Esc Exit"
    );

    attroff(COLOR_PAIR(1));


    /*
     * Refresh the screen.
     *
     * editor_draw() already placed
     * the cursor at the current
     * editing position.
     */

     editor_draw(
        editor,
        editor_top,
        editor_height
    );

    curs_set(2);

    refresh();
}
