#include "../lib/Simple_window.h"
#include "../lib/Graph.h"
#include <system_error>
#include <iostream>
#include <algorithm>

bool is_diagonal(int row, int col) {
    return (col == row);
}

int main()
{
    try
    {
        const int WIN_W{ 800 };
        const int WIN_H{ 1000 };
        const int CELL_SZ{ 100 };
        const int GRID_NUM_COLS{ 8 };
        constexpr int GRID_NUM_ROWS{ GRID_NUM_COLS };
        constexpr int GRID_SZ { CELL_SZ * GRID_NUM_COLS };
        const string IMG_PELIKAN = "img_drill/pelikan.jpg";
        const string IMG_PIGEON = "img_drill/pigeon.jpg";

        Graph_lib::Point tl{ 100, 100 };

        Simple_window win{ tl, 800, 1000, "Chapter 13" };

        Graph_lib::Lines grid;
        Graph_lib::Vector_ref<Graph_lib::Rectangle> rectangles;

        int offs_x{ 0 };
        int offs_y{ 0 };
        for (int row = 0; row <= GRID_NUM_ROWS; ++row) {
            offs_y = row * CELL_SZ;
            for (int col = 0; col <= GRID_NUM_COLS; ++col) {
                offs_x = col * CELL_SZ;
                if (row == 0) {
                    grid.add(Point{ offs_x, 0 }, Point{ offs_x, GRID_SZ });
                }
                if (col == 0) {
                    grid.add(Point{ 0, offs_y }, Point{ GRID_SZ, offs_y });
                }
                if (is_diagonal(row, col)) {
                    rectangles.push_back(
                        new Graph_lib::Rectangle{
                            Point{ offs_x, offs_y },
                            Point{ offs_x + CELL_SZ, offs_y + CELL_SZ }
                        }
                    );
                    rectangles[rectangles.size() - 1].set_fill_color(Graph_lib::Color::dark_red);
                    win.attach(rectangles[rectangles.size() - 1]);
                }
            }
        }

        win.attach(grid);

        Graph_lib::Image pelikan_01(Point{ 0, 300 }, IMG_PELIKAN);
        Graph_lib::Image pelikan_02(Point{ 300, 500 }, IMG_PELIKAN);
        Graph_lib::Image pelikan_03(Point{ 400, 0 }, IMG_PELIKAN);
        pelikan_01.set_mask(Point{ 25, 25 }, 200, 200);
        pelikan_02.set_mask(Point{ 25, 25 }, 200, 200);
        pelikan_03.set_mask(Point{ 25, 25 }, 200, 200);

        win.attach(pelikan_01);
        win.attach(pelikan_02);
        win.attach(pelikan_03);

        Graph_lib::Image pigeon(Point{ 0, 0}, IMG_PIGEON);
        pigeon.set_mask(Point{ 20, 20 }, 100, 100);

        win.attach(pigeon);

        for (int i = 0; i < GRID_NUM_COLS * GRID_NUM_ROWS; ++i) {
            int mod = i % GRID_NUM_COLS;
            if (mod > 0)
                pigeon.move(CELL_SZ, 0);
            else if (i > 0)
                pigeon.move(- (GRID_NUM_COLS-1) * CELL_SZ, CELL_SZ);
            win.wait_for_button();
        }

        win.wait_for_button();

        return 0;
    }
    catch (exception& e) {
        return 1;
    }
    catch (...) {
        return 2;
    }
}
