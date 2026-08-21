#ifndef UI_H
#define UI_H

#include "editor.h"

void ui_init(void);
void ui_shutdown(void);

void ui_draw(Editor *editor);

void ui_set_message(const char *message);
void ui_clear_messages(void);

#endif