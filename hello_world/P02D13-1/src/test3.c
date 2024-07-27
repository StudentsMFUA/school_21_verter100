#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 25
#define HEIGHT 80
void read_file(int initial_cells[HEIGHT][WIDTH]);
void change_cells(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]);
int search_neighbour(int initial_cells[HEIGHT][WIDTH], int y, int x);
void change_speed(char key, int *time_speed, int *flag);
int its_life(int initial_cells[HEIGHT][WIDTH]);
void copy(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]);
int comparison(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]);
void display_cells(int initial_cells[HEIGHT][WIDTH]);

int main(void) {
  int speed = 100, flag = 0;
  int initial_cells[HEIGHT][WIDTH];
  int changed_cells[HEIGHT][WIDTH];
  read_file(initial_cells);
  if (freopen("/dev/tty", "r", stdin) == NULL) {
        printf("Error");
        flag = 1;
  } 
  initscr();
  nodelay(stdscr, true); 
  while (flag == 0) {
    char key = getch();
    usleep(speed * 1000); 
    clear();
    change_speed(key, &speed, &flag);
    display_cells(initial_cells[HEIGHT][WIDTH]);
    change_cells(initial_cells, changed_cells);
    //if(comparison(initial_cells, changed_cells) == 0)
        //flag = 1; 
   copy(initial_cells, changed_cells);  
    //if(its_life(initial_cells) == 0)
        //flag = 1;  
  }
  endwin();
  return 0;
}

void read_file(int initial_cells[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int file_text = getchar() - 48;
      initial_cells[y][x] = file_text;
    }
  }
}

void display_cells(int initial_cells[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
                if(initial_cells[i][j] == 1)
                    printw("0");
                else
                    printw("-");
        }
            printw("\n");
    }
}

void change_cells(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (initial_cells[i][j] == 0 && search_neighbour(initial_cells, i, j) == 3)
                changed_cells[i][j] = 1;
            else if (initial_cells[i][j] == 1 &&
                     (search_neighbour(initial_cells, i, j) == 3 || search_neighbour(initial_cells, i, j) == 2))
                changed_cells[i][j] = 1;
            else
                changed_cells[i][j] = 0;
        }
    }
}

int search_neighbour(int initial_cells[HEIGHT][WIDTH], int y, int x) {
  int count = 0;
  for (int y_nearby_cell = y - 1; y_nearby_cell <= y + 1; y_nearby_cell++) {
    for (int x_nearby_cell = x - 1; x_nearby_cell <= x + 1; x_nearby_cell++) {
      if (!(y_nearby_cell == y && x_nearby_cell == x)) {
        count += initial_cells[(HEIGHT + y_nearby_cell) % HEIGHT]
                              [(WIDTH + x_nearby_cell) % WIDTH];
      }
    }
  }
  return count;
}

void change_speed(char key, int *time_speed, int *flag) { 
    if ((key == '-' || key == '_') && *time_speed < 1000)
        *time_speed += 15;
    else if ((key == '+' || key == '=') && *time_speed > 10)
        *time_speed -= 15;
    else if (key == 'q' || key == 'Q')
        *flag = 1;
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
void copy(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
      initial_cells[y][x] = changed_cells[y][x];
      }
    }
}
int comparison(int initial_cells[HEIGHT][WIDTH], int changed_cells[HEIGHT][WIDTH]){
    int count = 0;
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(initial_cells[i][j] != changed_cells[i][j])
                count++;
        }
    }
    return count;

}
