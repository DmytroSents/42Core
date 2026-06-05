#include "src/utils.h"
#include "mazegen/mazegen.h"
#include <locale.h>

#define CP_PATH  1
#define CP_WALL  2
#define CP_ENTRY 3
#define CP_EXIT  4
#define CP_PAT   5

static int show_path     = 0;
static int cur_scheme    = 0;

static short wall_colors[] = {
    COLOR_WHITE,
    COLOR_CYAN,
    COLOR_YELLOW,
    COLOR_GREEN,
};

/* ------------------------------------------------------------------ */
/*  forward-declare so get_path_char is visible to ncurses_render      */
/* ------------------------------------------------------------------ */
static const char *get_path_char(t_param *p, t_cell grid[][p->height],
                                 int x, int y);

/* ------------------------------------------------------------------ */

static void init_colors(void)
{
    start_color();
    use_default_colors();
    init_pair(CP_PATH,  COLOR_GREEN,  COLOR_BLACK);
    init_pair(CP_WALL,  wall_colors[cur_scheme], COLOR_BLACK);
    init_pair(CP_ENTRY, COLOR_CYAN,   COLOR_BLACK);
    init_pair(CP_EXIT,  COLOR_RED,    COLOR_BLACK);
    init_pair(CP_PAT,   COLOR_YELLOW, COLOR_BLACK);
}

static void cycle_wall_color(void)
{
    cur_scheme = (cur_scheme + 1) % (int)(sizeof(wall_colors) / sizeof(*wall_colors));
    init_pair(CP_WALL, wall_colors[cur_scheme], COLOR_BLACK);
}

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

    if (n && s && !e && !w) return " ║ ";
    if (e && w && !n && !s) return "═══";
    if (n && e && !s && !w) return " ╚═";
    if (n && w && !e && !s) return "═╝ ";
    if (s && e && !n && !w) return " ╔═";
    if (s && w && !n && !e) return "═╗ ";
    // if (n && e && w && !s)  return "═╩═";
    // if (s && e && w && !n)  return "═╦═";
    // if (n && s && e && !w)  return " ╠═";
    // if (n && s && w && !e)  return "═╣ ";
    // if (n && s && e && w)   return "═╬═";

    return " . ";
}

static void ncurses_render(t_param *p, t_cell grid[][p->height])
{
    clear();

    for (int y = 0; y < p->height; y++)
    {
        /* top wall row */
        move(y * 2, 0);
        attron(COLOR_PAIR(CP_WALL));
        for (int x = 0; x < p->width; x++)
        {
            printw("+");
            printw(grid[x][y].walls & WALL_N ? "---" : "   ");
        }
        printw("+");
        attroff(COLOR_PAIR(CP_WALL));

        /* cell row */
        move(y * 2 + 1, 0);
        for (int x = 0; x < p->width; x++)
        {
            attron(COLOR_PAIR(CP_WALL));
            printw(grid[x][y].walls & WALL_W ? "|" : " ");
            attroff(COLOR_PAIR(CP_WALL));

            if (x == p->entry[0] && y == p->entry[1])
            {
                attron(COLOR_PAIR(CP_ENTRY) | A_BOLD);
                printw("[E]");
                attroff(COLOR_PAIR(CP_ENTRY) | A_BOLD);
            }
            else if (x == p->exit[0] && y == p->exit[1])
            {
                attron(COLOR_PAIR(CP_EXIT) | A_BOLD);
                printw("{X}");
                attroff(COLOR_PAIR(CP_EXIT) | A_BOLD);
            }
            else if (show_path && grid[x][y].c_type == PATH_SHRT)
            {
                attron(COLOR_PAIR(CP_PATH) | A_BOLD);
                printw("%s", get_path_char(p, grid, x, y));
                attroff(COLOR_PAIR(CP_PATH) | A_BOLD);
            }
            else if (grid[x][y].c_type == FT_CELL)
            {
                attron(COLOR_PAIR(CP_PAT) | A_BOLD);
                printw("42*");
                attroff(COLOR_PAIR(CP_PAT) | A_BOLD);
            }
            else
                printw("   ");
        }
        attron(COLOR_PAIR(CP_WALL));
        printw(grid[p->width - 1][y].walls & WALL_E ? "|" : " ");
        attroff(COLOR_PAIR(CP_WALL));
    }

    /* bottom border */
    move(p->height * 2, 0);
    attron(COLOR_PAIR(CP_WALL));
    for (int x = 0; x < p->width; x++)
    {
        printw("+");
        printw(grid[x][p->height - 1].walls & WALL_S ? "---" : "   ");
    }
    printw("+");
    attroff(COLOR_PAIR(CP_WALL));

    /* status bar */
    mvprintw(p->height * 2 + 2, 0,
        "[R] Regen  [P] Path:%-3s  [C] Color  [Q] Quit",
        show_path ? "ON" : "OFF");
    refresh();
}

/* ------------------------------------------------------------------ */

static void do_regen(t_param *p, t_stack *stack,
                     t_cell grid[][p->height], char **path_str)
{
    /* wipe grid */
    grid_init(p, grid);
    stack->first = 0;
    stack->count = 0;

    apply_42pattern(p, grid);
    DFS_GEN(stack, p, grid);
    reset_cell_type(p, grid);

    /* replace caller's path_str */
    free(*path_str);
    *path_str = BFS_PATH(stack, p, grid);

    show_path = 0;
}

/* ------------------------------------------------------------------ */

void run_interactive(t_param *p, t_stack *stack,
                     t_cell grid[][p->height], char **path_str)
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (!has_colors())
    {
        endwin();
        fprintf(stderr, "Terminal does not support colors\n");
        return;
    }
    init_colors();
    ncurses_render(p, grid);

    int ch;
    while ((ch = getch()) != 'q' && ch != 'Q')
    {
        if (ch == 'r' || ch == 'R')
            do_regen(p, stack, grid, path_str);
        else if (ch == 'p' || ch == 'P')
            show_path = !show_path;
        else if (ch == 'c' || ch == 'C')
            cycle_wall_color();

        ncurses_render(p, grid);
    }
    endwin();
}

/* ------------------------------------------------------------------ */
/* non-ncurses fallback kept for reference / testing                   */
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