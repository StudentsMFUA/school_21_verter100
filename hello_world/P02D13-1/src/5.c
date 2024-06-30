#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25

void read_file(int initial_cells[HEIGHT][WIDTH]);
void display_cells(int speed, char user_command,
                   int initial_cells[HEIGHT][WIDTH]);
void change_cells(int initial_cells[HEIGHT][WIDTH]);
int find_cells_nearby(int initial_cells[HEIGHT][WIDTH], int y, int x);
void check_commands(char user_command, int *speed, int *exit);

int main(void) {
  int initial_cells[HEIGHT][WIDTH];

  int exit = 0;
  int speed = 500000;
  char user_command;

  read_file(initial_cells);
  if (freopen("/dev/tty", "r", stdin) == NULL) {
    printf("Error");
    return 0;
  }

  initscr();
  while (!(user_command == 'q' || user_command == 'Q')) {
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    display_cells(speed, user_command, initial_cells);
    change_cells(initial_cells);
    user_command = getch();
    check_commands(user_command, &speed, &exit);
    usleep(speed);
  }
  endwin();
  return 0;
}

void read_file(int initial_cells[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      char file_text = getchar() - 48;
      initial_cells[y][x] = file_text;
    }
  }
}

void display_cells(int speed, char user_command,
                   int initial_cells[HEIGHT][WIDTH]) {
  clear();
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
  mvprintw(27, 66, "SPEED: %d", speed);
}

void change_cells(int initial_cells[HEIGHT][WIDTH]) {
  int changed_cells[HEIGHT][WIDTH];

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
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      initial_cells[y][x] = changed_cells[y][x];
    }
  }
}

int find_cells_nearby(int initial_cells[HEIGHT][WIDTH], int y, int x) {
  int nearby_cells = 0;
  for (int y_nearby = y - 1; y_nearby <= y + 1; y_nearby++) {
    for (int x_nearby = x - 1; x_nearby <= x + 1; x_nearby++) {
      if (!(y_nearby == y && x_nearby == x)) {
        nearby_cells += initial_cells[(HEIGHT + y_nearby) % HEIGHT]
                                     [(WIDTH + x_nearby) % WIDTH];
      }
    }
  }
  return nearby_cells;
}

void check_commands(char user_command, int *speed, int *exit) {
  if (user_command == 'q' || user_command == 'Q') {
    *exit = 1;
  } else if ((user_command == '+' || user_command == '=') && *speed >= 100000) {
    *speed -= 100000;
  } else if ((user_command == '-' || user_command == '_') &&
             *speed <= 1000000) {
    *speed += 100000;
  }
}