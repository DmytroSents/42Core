/*
 * render_win.c  –  Windows/PowerShell port of the ncurses renderer
 *
 * Replaces ncurses with the Win32 Console API.
 * Compile (MSVC):  cl render_win.c mazegen\*.c src\utils.c /Fe:maze.exe
 * Compile (MinGW): gcc render_win.c mazegen/*.c src/utils.c -o maze.exe
 *
 * Run from PowerShell:  .\maze.exe
 * Keys: R = regen  P = path on/off  C = cycle color  Q = quit
 */

#include "src/utils.h"
#include "mazegen/mazegen.h"

#include <windows.h>
#include <stdio.h>
#include <locale.h>

/* ------------------------------------------------------------------ */
/*  Color-pair indices (reuse the same logical names)                  */
/* ------------------------------------------------------------------ */
#define CP_PATH  0
#define CP_WALL  1
#define CP_ENTRY 2
#define CP_EXIT  3
#define CP_PAT   4
#define CP_STATUS 5

/* Win32 console color attributes for each pair (foreground | background) */
static WORD color_pairs[] = {
    /* CP_PATH  */ FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    /* CP_WALL  */ FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    /* CP_ENTRY */ FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    /* CP_EXIT  */ FOREGROUND_RED | FOREGROUND_INTENSITY,
    /* CP_PAT   */ FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    /* CP_STATUS*/ FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

/* Available wall color schemes (cycle with C key) */
static WORD wall_schemes[] = {
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, /* white  */
    FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,                  /* cyan   */
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,                   /* yellow */
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,                                    /* green  */
};
static int  cur_scheme = 0;
static int  show_path  = 0;

/* ------------------------------------------------------------------ */
/*  Console helpers                                                     */
/* ------------------------------------------------------------------ */
static HANDLE hOut;

static void con_init(void)
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Enable UTF-8 so box-drawing characters render correctly */
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    /* Enable virtual-terminal processing (Windows 10 1511+) so ANSI
     * sequences also work if ever needed.                            */
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING
                              | DISABLE_NEWLINE_AUTO_RETURN);

    /* Hide cursor */
    CONSOLE_CURSOR_INFO ci = { 1, FALSE };
    SetConsoleCursorInfo(hOut, &ci);
}

static void con_goto(int col, int row)
{
    COORD c = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(hOut, c);
}

static void con_attr(int pair)
{
    WORD attr = (pair == CP_WALL) ? wall_schemes[cur_scheme]
                                  : color_pairs[pair];
    SetConsoleTextAttribute(hOut, attr);
}

static void con_reset(void)
{
    /* Light-grey: default PowerShell foreground */
    SetConsoleTextAttribute(hOut,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

/* Print a UTF-8 string at (col, row) with a given color pair */
static void con_print(int col, int row, int pair, const char *s)
{
    con_goto(col, row);
    con_attr(pair);
    /* WriteConsoleA with UTF-8 codepage handles box-drawing chars */
    DWORD written;
    WriteConsoleA(hOut, s, (DWORD)strlen(s), &written, NULL);
    con_reset();
}

/* ------------------------------------------------------------------ */
/*  Path character selection (identical logic to the original)         */
/* ------------------------------------------------------------------ */
static const char *get_path_char(t_param *p, t_cell grid[][p->height],
                                 int x, int y)
{
    int walls = grid[x][y].walls;

    #define IS_PATH(cx, cy) \
        (grid[cx][cy].c_type == PATH_SHRT \
        || ((cx) == p->entry[0] && (cy) == p->entry[1]) \
        || ((cx) == p->exit[0]  && (cy) == p->exit[1]))

    int n = !(walls & WALL_N) && (y > 0)             && IS_PATH(x,   y-1);
    int e = !(walls & WALL_E) && (x < p->width - 1)  && IS_PATH(x+1, y);
    int s = !(walls & WALL_S) && (y < p->height - 1) && IS_PATH(x,   y+1);
    int w = !(walls & WALL_W) && (x > 0)             && IS_PATH(x-1, y);

    #undef IS_PATH

    if (n && s && !e && !w) return " \xe2\x95\x91 ";   /* ║ */
    if (e && w && !n && !s) return "\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90"; /* ═══ */
    if (n && e && !s && !w) return " \xe2\x95\x9a\xe2\x95\x90"; /* ╚═ */
    if (n && w && !e && !s) return "\xe2\x95\x90\xe2\x95\x9d "; /* ═╝  */
    if (s && e && !n && !w) return " \xe2\x95\x94\xe2\x95\x90"; /* ╔═ */
    if (s && w && !n && !e) return "\xe2\x95\x90\xe2\x95\x97 "; /* ═╗  */

    return " . ";
}

/* ------------------------------------------------------------------ */
/*  Full-screen render                                                  */
/* ------------------------------------------------------------------ */
static void win_render(t_param *p, t_cell grid[][p->height])
{
    /* Clear screen by filling with spaces */
    COORD home = { 0, 0 };
    DWORD total = (p->width * 4 + 2) * (p->height * 2 + 4);
    DWORD written;
    FillConsoleOutputCharacterA(hOut, ' ', total, home, &written);
    FillConsoleOutputAttribute(hOut,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        total, home, &written);

    char buf[16];

    for (int y = 0; y < p->height; y++)
    {
        int screen_row = y * 2;

        /* ---- top wall row ---- */
        int col = 0;
        for (int x = 0; x < p->width; x++)
        {
            con_print(col, screen_row, CP_WALL, "+");
            con_print(col + 1, screen_row, CP_WALL,
                      grid[x][y].walls & WALL_N ? "---" : "   ");
            col += 4;
        }
        con_print(col, screen_row, CP_WALL, "+");

        /* ---- cell row ---- */
        col = 0;
        int cell_row = screen_row + 1;
        for (int x = 0; x < p->width; x++)
        {
            /* west wall */
            con_print(col, cell_row, CP_WALL,
                      grid[x][y].walls & WALL_W ? "|" : " ");
            col++;

            /* cell content */
            if (x == p->entry[0] && y == p->entry[1])
                con_print(col, cell_row, CP_ENTRY, "[E]");
            else if (x == p->exit[0] && y == p->exit[1])
                con_print(col, cell_row, CP_EXIT, "{X}");
            else if (show_path && grid[x][y].c_type == PATH_SHRT)
                con_print(col, cell_row, CP_PATH,
                          get_path_char(p, grid, x, y));
            else if (grid[x][y].c_type == FT_CELL)
                con_print(col, cell_row, CP_PAT, "42*");
            else
                con_print(col, cell_row, CP_STATUS, "   ");

            col += 3;
        }
        /* east border */
        con_print(col, cell_row, CP_WALL,
                  grid[p->width - 1][y].walls & WALL_E ? "|" : " ");
    }

    /* ---- bottom border ---- */
    int bot_row = p->height * 2;
    int col = 0;
    for (int x = 0; x < p->width; x++)
    {
        con_print(col, bot_row, CP_WALL, "+");
        con_print(col + 1, bot_row, CP_WALL,
                  grid[x][p->height - 1].walls & WALL_S ? "---" : "   ");
        col += 4;
    }
    con_print(col, bot_row, CP_WALL, "+");

    /* ---- status bar ---- */
    snprintf(buf, sizeof(buf), "%-3s", show_path ? "ON" : "OFF");
    con_goto(0, bot_row + 2);
    con_reset();
    printf("[R] Regen  [P] Path:%s  [C] Color  [Q] Quit", buf);
    fflush(stdout);
}

/* ------------------------------------------------------------------ */
/*  Regenerate maze                                                     */
/* ------------------------------------------------------------------ */
static void do_regen(t_param *p, t_stack *stack,
                     t_cell grid[][p->height], char **path_str)
{
    grid_init(p, grid);
    stack->first = 0;
    stack->count = 0;

    apply_42pattern(p, grid);
    DFS_GEN(stack, p, grid);
    reset_cell_type(p, grid);

    free(*path_str);
    *path_str = BFS_PATH(stack, p, grid);

    show_path = 0;
}

/* ------------------------------------------------------------------ */
/*  Input loop – replaces getch() with ReadConsoleInput                */
/* ------------------------------------------------------------------ */
static int read_key(void)
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD count;
    while (1) {
        ReadConsoleInputA(hIn, &ir, 1, &count);
        if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
            return (unsigned char)ir.Event.KeyEvent.uChar.AsciiChar;
    }
}

/* ------------------------------------------------------------------ */
/*  Public entry point – same signature as the original                */
/* ------------------------------------------------------------------ */
void run_interactive(t_param *p, t_stack *stack,
                     t_cell grid[][p->height], char **path_str)
{
    con_init();
    win_render(p, grid);

    int ch;
    while (1)
    {
        ch = read_key();
        if (ch == 'q' || ch == 'Q') break;

        if      (ch == 'r' || ch == 'R') do_regen(p, stack, grid, path_str);
        else if (ch == 'p' || ch == 'P') show_path = !show_path;
        else if (ch == 'c' || ch == 'C') {
            cur_scheme = (cur_scheme + 1) % (int)(sizeof(wall_schemes)
                                                  / sizeof(*wall_schemes));
        }
        win_render(p, grid);
    }

    /* Restore console on exit */
    con_reset();
    con_goto(0, p->height * 2 + 4);
    CONSOLE_CURSOR_INFO ci = { 10, TRUE };
    SetConsoleCursorInfo(hOut, &ci);
}

/* ------------------------------------------------------------------ */
/*  Plain-text fallback (unchanged – works on all platforms)           */
/* ------------------------------------------------------------------ */
void render_maze(t_param *p, t_cell grid[][p->height])
{
    for (int y = 0; y < p->height; y++)
    {
        for (int x = 0; x < p->width; x++)
        {
            printf("+");
            printf(grid[x][y].walls & WALL_N ? "---" : "   ");
        }
        printf("+\n");

        for (int x = 0; x < p->width; x++)
        {
            printf(grid[x][y].walls & WALL_W ? "|" : " ");
            if (x == p->entry[0] && y == p->entry[1])      printf("[E]");
            else if (x == p->exit[0] && y == p->exit[1])   printf("{X}");
            else if (grid[x][y].c_type == PATH_SHRT)
                printf("%s", get_path_char(p, grid, x, y));
            else if (grid[x][y].c_type == FT_CELL)         printf("42*");
            else                                            printf("   ");
        }
        printf(grid[p->width - 1][y].walls & WALL_E ? "|\n" : " \n");
    }
    for (int x = 0; x < p->width; x++)
    {
        printf("+");
        printf(grid[x][p->height - 1].walls & WALL_S ? "---" : "   ");
    }
    printf("+\n");
}
