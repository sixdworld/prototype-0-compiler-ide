#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#include "ui.h"
#include "editor.h"


/*
 * Compile the code currently in the editor.
 *
 * The editor contents are written to a temporary
 * file so source_code.p0 is NOT overwritten.
 */
void run_compiler(Editor *editor)
{
    FILE *pipe;
    char buffer[256];

    /*
     * Save current editor contents to temporary file.
     */
    if (
        editor_save(
            editor,
            "/tmp/p0_editor.p0"
        ) != 0
    )
    {
        ui_clear_messages();

        ui_set_message(
            "Error: Could not create temporary source file."
        );

        return;
    }


    ui_clear_messages();

    ui_set_message(
        "Compiling..."
    );

    ui_draw(editor);


    /*
     * Run the existing P0 compiler.
     */
    pipe = popen(
        "./compiler /tmp/p0_editor.p0 2>&1",
        "r"
    );

    if (pipe == NULL)
    {
        ui_set_message(
            "Error: Could not start compiler."
        );

        return;
    }


    /*
     * Read compiler output.
     */
    while (
        fgets(
            buffer,
            sizeof(buffer),
            pipe
        ) != NULL
    )
    {
        buffer[
            strcspn(
                buffer,
                "\n"
            )
        ] = '\0';

        if (strlen(buffer) > 0)
        {
            ui_set_message(buffer);
        }
    }


    int status = pclose(pipe);


    if (status == 0)
    {
        ui_set_message(
            "Compilation finished."
        );
    }
    else
    {
        ui_set_message(
            "Compilation failed."
        );
    }
}


/*
 * Handle mouse clicks on the top menu.
 */
static int handle_menu_click(
    MEVENT *event,
    Editor *editor
)
{
    /*
     * Only handle clicks on the
     * top menu row.
     */
    if (event->y != 0)
    {
        return 0;
    }


    /*
     * FILE
     */
    if (
        event->x >= 0 &&
        event->x <= 5
    )
    {
        ui_clear_messages();

        ui_set_message(
            "File menu selected."
        );

        return 1;
    }


    /*
     * EDIT
     */
    if (
        event->x >= 8 &&
        event->x <= 13
    )
    {
        ui_clear_messages();

        ui_set_message(
            "Edit menu selected."
        );

        return 1;
    }


    /*
     * COMPILE
     */
    if (
        event->x >= 17 &&
        event->x <= 25
    )
    {
        run_compiler(editor);

        return 1;
    }


    /*
     * RUN
     *
     * The actual interpreter will be
     * connected here later.
     */
    if (
        event->x >= 30 &&
        event->x <= 34
    )
    {
        ui_clear_messages();

        ui_set_message(
            "Run: interpreter not connected yet."
        );

        ui_draw(editor);

        return 1;
    }


    return 0;
}


int main(void)
{
    int ch;

    Editor editor;


    /*
     * Start with a completely blank editor.
     *
     * source_code.p0 is NOT loaded.
     */
    editor_init(&editor);


    /*
     * Start ncurses UI.
     */
    ui_init();


    ui_set_message(
        "Welcome to P0 Compiler IDE"
    );


    while (1)
    {
        /*
         * Draw the entire interface.
         */
        ui_draw(&editor);


        /*
         * Wait for keyboard input.
         */
        ch = getch();


        /*
         * =========================
         * MOUSE
         * =========================
         */
        if (ch == KEY_MOUSE)
        {
            MEVENT event;

            if (getmouse(&event) == OK)
            {
                if (
                    event.bstate &
                    BUTTON1_CLICKED
                )
                {
                    if (
                        handle_menu_click(
                            &event,
                            &editor
                        )
                    )
                    {
                        continue;
                    }
                }
            }
        }


        /*
         * =========================
         * ESC = EXIT
         * =========================
         */
        if (ch == 27)
        {
            ui_shutdown();

            return 0;
        }


        /*
         * =========================
         * F2 = SAVE
         *
         * Explicitly saves the document
         * to source_code.p0.
         * =========================
         */
        if (ch == KEY_F(2))
        {
            if (
                editor_save(
                    &editor,
                    "source_code.p0"
                ) == 0
            )
            {
                ui_clear_messages();

                ui_set_message(
                    "File saved."
                );
            }
            else
            {
                ui_clear_messages();

                ui_set_message(
                    "Error: Could not save file."
                );
            }

            continue;
        }


        /*
         * =========================
         * F9 = COMPILE
         *
         * Compiles the current editor
         * contents without modifying
         * source_code.p0.
         * =========================
         */
        if (ch == KEY_F(9))
        {
            run_compiler(&editor);

            continue;
        }


        /*
         * =========================
         * CTRL + R = RUN
         *
         * The interpreter will be
         * connected here later.
         * =========================
         */
        if (ch == 18)
        {
            ui_clear_messages();

            ui_set_message(
                "Run: interpreter not connected yet."
            );

            ui_draw(&editor);

            continue;
        }


        /*
         * =========================
         * EDITOR INPUT
         * =========================
         */
        editor_handle_key(
            &editor,
            ch
        );
    }


    ui_shutdown();

    return 0;
}