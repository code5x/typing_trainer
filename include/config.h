#ifndef CONFIG_H
#define CONFIG_H


/* Case sensitivity
   true  = case sensitive typing
   false = ignore case while typing
*/
#define CASE_SENSITIVE 1


/* Auto detect terminal width
   1 = auto detect
   0 = use TERMINAL_WIDTH value
*/
#define AUTO_DETECT_TERMINAL_WIDTH 1

/* Used only if AUTO_DETECT_TERMINAL_WIDTH == 0
   Must be > 0
*/
#define TERMINAL_WIDTH 80


/* Text colors */
#define COLOR_GREEN_R   0
#define COLOR_GREEN_G   200
#define COLOR_GREEN_B   0

#define COLOR_RED_R     200
#define COLOR_RED_G     0
#define COLOR_RED_B     0

#define COLOR_YELLOW_R  255
#define COLOR_YELLOW_G  255
#define COLOR_YELLOW_B  200

/* Background color for typing */
#define COLOR_BG_R      30
#define COLOR_BG_G      30
#define COLOR_BG_B      30


#endif
