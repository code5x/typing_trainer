#ifndef RENDERER_H
#define RENDERER_H

/* Render correct typed character */
void render_correct_char(char expected);

/* Render wrong typed character */
void render_wrong_char(char expected);

/* Render preview / guide text (yellow, no bg) */
void render_preview_text(const char *text);

/* Reset rendering */
void render_reset(void);

#endif
