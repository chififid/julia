#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 101
#define HEIGHT 45
#define WINDOW_SIZE_STEP 0.2
#define ZOOM 2
#define ZOOM_STEP 0.2
#define STEPS 300
#define WINDOW_X_STEP 0.2
#define WINDOW_Y_STEP 0.2

int in_graph(double x, double y, double c_x, double c_y)
{
    int i;

    for (i = 0; i < STEPS; i++) {
        double n_x, n_y, len;

        n_x = x * x - y * y + c_x;
        n_y = 2 * x * y + c_y;

        x = n_x;
        y = n_y;

        len = sqrt(x * x + y * y);

        if (len > 2)
        {
            return i;
        }
   }

   return 0;
}

void print_graph(double zoom, int height, int width, double window_x_offset, double window_y_offset, double c_x, double c_y)
{
    int x, y;
    double center_x, center_y, x_step, y_step;
    char chars[] = "!~#$^&**()_+`=][|;':<>?/";
    int chars_len = sizeof(chars);

    x_step = (zoom * 2) / (double)width;
    y_step = (zoom * 2) / (double)height;
    center_x = ((double)width / 2.0);
    center_y = ((double)height / 2.0);

    for (y = -1; y <= height; y++) {
        for (x = -1; x <= width; x++) {
            int color;
            double point_x, point_y;

            point_x = (double)(x - center_x) * (double)x_step;
            point_y = (double)(y - center_y) * (double)y_step;
            if (x == -1 || x == width || y == -1 || y == height) {
                printf("|");
            } else {
                color = in_graph(point_x + window_x_offset, point_y + window_y_offset, c_x, c_y);

                if (color) {
                    printf("%c", chars[(int)(color / ((double)STEPS / (double)chars_len))]);
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Z: %f; X: %f; Y: %f;\n", zoom, window_x_offset, window_y_offset);
}

int main()
{
    int s, height = HEIGHT, width = WIDTH, op = -2;
    double zoom = ZOOM, c_x, c_y, window_x_offset = 0, window_y_offset = 0;

    for (c_x = 0, c_y = 0; op != -1 && c_x < 1 && c_y < 1;) {
        printf("\033[0d\033[2J");
        print_graph(zoom, height, width, window_x_offset, window_y_offset, c_x, c_y);

        s = scanf("%d", &op);
        if (s != 1) {
            fprintf(stderr, "Input error\n");
            exit(1);
        }

        if (op == 7) {
            zoom *= 1 + ZOOM_STEP;
        } else if (op == 9) {
            zoom *= 1 - ZOOM_STEP;
        } else if (op == 2) {
            height *= 1 - WINDOW_SIZE_STEP;
            width *= 1 - WINDOW_SIZE_STEP;
        } else if (op == 3) {
            height *= 1 + WINDOW_SIZE_STEP;
            width *= 1 + WINDOW_SIZE_STEP;
        } else if (op == 0) {
            s = scanf("%lf", &c_x);
            if (s != 1) {
                fprintf(stderr, "Input error\n");
                exit(1);
            }
            s = scanf("%lf", &c_y);
            if (s != 1)
            {
                fprintf(stderr, "Input error\n");
                exit(1);
            }
        } else if (op == 1) {
            c_x += 0.02;
            c_y += 0.02;
        } else if (op == 5) {
            window_y_offset += WINDOW_Y_STEP * zoom * 2;
        } else if (op == 8) {
            window_y_offset -= WINDOW_Y_STEP * zoom * 2;
        } else if (op == 6) {
            window_x_offset += WINDOW_X_STEP * zoom * 2;
        } else if (op == 4) {
            window_x_offset -= WINDOW_X_STEP * zoom * 2;
        }
    }

    return 0;
}
