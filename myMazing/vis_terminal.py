#!/usr/bin/env python3
"""
Fixed terminal maze visualizer. Proper alignment with fixed-width cells.
Uses curses for perfect rendering (Gnome-terminal friendly).
Paste maze → viz → 'r' regenerate, 'p' path, 'q' quit.
"""

import sys
import curses
from typing import List, Tuple
from collections import deque

# Directions: N=1, E=2, S=4, W=8
DIRS = [(0, -1, 1, "N"), (1, 0, 2, "E"), (0, 1, 4, "S"), (-1, 0, 8, "W")]


def parse_maze(filename: str):
    with open(filename, "r") as f:
        raw = [line.rstrip("\n") for line in f]

    parts = "\n".join(raw).split("\n\n", 1)
    if len(parts) != 2:
        raise ValueError(
            "Maze file must contain a blank line between grid and coordinates"
        )

    grid_text, coord_text = parts
    grid_lines = [line.strip() for line in grid_text.splitlines() if line.strip()]
    coord_lines = [line.strip() for line in coord_text.splitlines() if line.strip()]

    grid = [[int(ch, 16) for ch in row] for row in grid_lines]
    entry_line = coord_lines[0].split(",")
    exit_line = coord_lines[1].split(",")

    entry = (int(entry_line[0]), int(entry_line[1]))
    exit_pos = (int(exit_line[0]), int(exit_line[1]))
    return grid, entry, exit_pos


def find_path(
    grid: List[List[int]], start: Tuple[int, int], goal: Tuple[int, int]
) -> List[Tuple[int, int]]:
    """BFS shortest path (ignores walls for demo; adapt for real)."""
    height, width = len(grid), len(grid[0])
    queue = deque([start])
    parent = {start: None}

    while queue:
        x, y = queue.popleft()
        if (x, y) == goal:
            path = []
            at = goal
            while at:
                path.append(at)
                at = parent[at]
            return path[::-1]

        for dx, dy, wall, _ in DIRS:
            nx, ny = x + dx, y + dy
            if 0 <= nx < width and 0 <= ny < height and (nx, ny) not in parent:
                # Check wall open (demo: always pass)
                queue.append((nx, ny))
                parent[(nx, ny)] = (x, y)
    return []


class MazeViewer:
    def __init__(
        self, grid: List[List[int]], entry: Tuple[int, int], exit_pos: Tuple[int, int]
    ):
        self.grid = grid
        self.entry = entry
        self.exit_pos = exit_pos
        self.path = []
        self.show_path = False
        self.height, self.width = len(grid), len(grid[0])

    def run(self, stdscr):
        curses.curs_set(0)
        curses.start_color()
        curses.init_pair(1, curses.COLOR_WHITE, curses.COLOR_BLACK)  # Wall
        curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)  # Path
        curses.init_pair(3, curses.COLOR_CYAN, curses.COLOR_BLACK)  # Entry
        curses.init_pair(4, curses.COLOR_MAGENTA, curses.COLOR_BLACK)  # Exit

        while True:
            h, w = stdscr.getmaxyx()
            if h < self.height * 2 + 4 or w < self.width * 4 + 2:
                stdscr.addstr(0, 0, "Terminal too small! Resize >60x50")
                stdscr.refresh()
                stdscr.getch()
                continue

            stdscr.clear()
            self.draw_maze(stdscr)
            self.draw_ui(stdscr)
            stdscr.refresh()

            key = stdscr.getch()
            if key == ord("q"):
                break
            elif key == ord("p"):
                self.show_path = not self.show_path
                if self.show_path:
                    self.path = find_path(self.grid, self.entry, self.exit_pos)
            elif key == ord("r"):
                self.grid = [
                    [15 for _ in range(self.width)] for _ in range(self.height)
                ]  # Reset walls

    def draw_maze(self, stdscr):
        path_set = set(self.path) if self.show_path else set()
        for y in range(self.height):
            for x in range(self.width):
                # Cell position
                row = y * 2 + 1
                col = x * 4 + 1

                walls = self.grid[y][x]
                color = curses.color_pair(1)

                # Entry/Exit/Path override
                if (x, y) == self.entry:
                    stdscr.addstr(row, col, " E ", curses.color_pair(3) | curses.A_BOLD)
                elif (x, y) == self.exit_pos:
                    stdscr.addstr(row, col, " X ", curses.color_pair(4) | curses.A_BOLD)
                elif self.show_path and (x, y) in path_set:
                    stdscr.addstr(row, col, " . ", curses.color_pair(2))
                elif walls == 15:
                    stdscr.addstr(row, col, "███", color)
                else:
                    stdscr.addstr(row, col, "   ", color)

                # Top/Bottom walls
                top_bot = "─" * 3 if walls & 1 else "   "
                stdscr.addstr(
                    row - 1, col - 1, "┌" + top_bot + "┐" if x == 0 else top_bot + "┐"
                )
                if y == self.height - 1:
                    stdscr.addstr(
                        row + 1,
                        col - 1,
                        "└" + top_bot + "┘" if x == self.width - 1 else top_bot + "┘",
                    )

                # Side walls (right)
                if x < self.width - 1:
                    right_wall = "│" if walls & 2 else " "
                    stdscr.addstr(row, col + 3, right_wall, color)

    def draw_ui(self, stdscr):
        h, w = stdscr.getmaxyx()
        ui = f"Path: {'ON' if self.show_path else 'OFF'} | Size: {self.width}x{self.height} | Q=Quit P=Path R=Reset"
        stdscr.addstr(h - 1, 0, ui, curses.A_REVERSE)


def main(filename: str):
    try:
        grid, entry, exit_pos = parse_maze(filename)
        viewer = MazeViewer(grid, entry, exit_pos)
        curses.wrapper(viewer.run)
        print("Bye!")
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    filename = sys.argv[1] if len(sys.argv) > 1 else input("Maze file: ").strip()
    main(filename)
