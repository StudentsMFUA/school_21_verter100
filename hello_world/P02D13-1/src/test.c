#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25

void read_file(int initial_cells[HEIGHT][WIDTH]);
void display_cells(int initial_cells[HEIGHT][WIDTH]);
void change_cells(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]);
int find_cells_nearby(int initial_cells[HEIGHT][WIDTH], int y, int x);
void check_commands(char user_command, long long *speed, int *exit);
void copy(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]);
int its_life(int initial_cells[HEIGHT][WIDTH]);

int main(void) {
    int initial_cells[HEIGHT][WIDTH];
    int changed_cells[HEIGHT][WIDTH];
    int exit = 0;
    long long speed = 100000;
    char user_command = 0;

    read_file(initial_cells);
    if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("Error");
        return 0;
    }
    initscr();
    nodelay(stdscr, TRUE);
    while (!(user_command == 'q' || user_command == 'Q' || exit == 1)) {
        clear();

        display_cells(initial_cells);
        change_cells(initial_cells, changed_cells);
        copy(initial_cells, changed_cells);
        if (its_life(initial_cells) == 0) exit = 1;
        user_command = getch();
        check_commands(user_command, &speed, &exit);
        usleep(speed);
    }
    endwin();
    return 0;
}

void read_file(int initial_cells[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &initial_cells[i][j]);
        }
    }
}

void display_cells(int initial_cells[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (initial_cells[y][x] == 1) {
                mvprintw(y, x, "#");
            } else if (initial_cells[y][x] == 0) {
                mvprintw(y, x, " ");
            }
        }
    }
    mvprintw(27, 1, "EXIT: Q    FASTEN: +    SLOW DOWN: -    ");
}

void change_cells(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int nearby_cells = find_cells_nearby(initial_cells, y, x);

            if (initial_cells[y][x] == 1) {
                if (nearby_cells < 2 || nearby_cells > 3) {
                    changed_cells[y][x] = 0;
                } else {
                    changed_cells[y][x] = 1;
                }
            } else {
                if (nearby_cells == 3) {
                    changed_cells[y][x] = 1;
                } else {
                    changed_cells[y][x] = 0;
                }
            }
        }
    }
}

int find_cells_nearby(int initial_cells[HEIGHT][WIDTH], int y, int x) {
    int nearby_cells = 0;
    for (int y_nearby = y - 1; y_nearby <= y + 1; y_nearby++) {
        for (int x_nearby = x - 1; x_nearby <= x + 1; x_nearby++) {
            if (!(y_nearby == y && x_nearby == x)) {
                nearby_cells += initial_cells[(HEIGHT + y_nearby) % HEIGHT][(WIDTH + x_nearby) % WIDTH];
            }
        }
    }
    return nearby_cells;
}

void check_commands(char user_command, long long *speed, int *exit) {
    if (user_command == 'q' || user_command == 'Q') {
        *exit = 1;
    } else if ((user_command == '+' || user_command == '=') && *speed >= 10000) {
        *speed -= 10000;
    } else if ((user_command == '-' || user_command == '_') && *speed <= 1000000) {
        *speed += 10000;
    }
}

void copy(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            initial_cells[y][x] = changed_cells[y][x];
        }
    }
}

int its_life(int initial_cells[HEIGHT][WIDTH]) {
    int count = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (initial_cells[i][j] == 1) count++;
        }
    }
    return count;
}