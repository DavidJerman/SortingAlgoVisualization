//
// Created by david on 1/22/2023.
//

#include "Sorter.h"

Sorter::Sorter() {
    sAppName = "Sorting Algorithms Visualization";
}

bool Sorter::OnUserCreate() {
    setArray();
    randomizeArrayOrder();
    drawArray();
    drawText(0, 0, "Sorting 101!", olc::DARK_GREEN);

    // Bubble sort in new thread
    std::thread t1(&Sorter::bubbleSort, this);
    t1.detach();

    return true;
}

bool Sorter::OnUserUpdate(float fElapsedTime) {
    mtx2.lock();
    drawArray();
    mtx1.unlock();
    return true;
}

void Sorter::drawArray() {
    for (int i = 0; i < COLUMNS; i++) {
        drawBar(i, COLUMNS, olc::BLACK, olc::BLACK);
        drawBar(i, array[i], olc::WHITE);
    }
}

void Sorter::drawBar(int column, int height, olc::Pixel color, olc::Pixel border) {
    if (height < 0) {
        return;
    }
    if (height > COLUMNS) {
        return;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < COLUMN_WIDTH; j++) {
            for (int k = 0; k < COLUMN_HEIGHT; k++) {
                if (j == 0 || j == COLUMN_WIDTH - 1)
                    Draw(column * COLUMN_WIDTH + j, ScreenHeight() - (i) * COLUMN_HEIGHT + k - COLUMN_HEIGHT, border);
                else
                    Draw(column * COLUMN_WIDTH + j, ScreenHeight() - (i) * COLUMN_HEIGHT + k - COLUMN_HEIGHT, color);
            }
        }
    }
}

void Sorter::drawText(int x, int y, std::string text, olc::Pixel color) {
    if (x < 0 || x >= ScreenWidth() || y < 0 || y >= ScreenHeight()) {
        return;
    }
    DrawString(x, y, text, color, 1);
}

void Sorter::setArray() {
    for (int i = 0; i < COLUMNS; i++) {
        array[i] = i + 1;
    }
}

// This might not be the best way to randomize an array, but it will do for now
void Sorter::randomizeArrayOrder() {
    for (unsigned char & i : array) {
        int randomIndex = rand() % COLUMNS;
        int temp = i;
        i = array[randomIndex];
        array[randomIndex] = temp;
    }
}

void Sorter::reverseArray() {
    for (int i = 0; i < COLUMNS; i++) {
        array[i] = COLUMNS - i;
    }
}

void Sorter::resetArray() {
    memset(array, 0, sizeof(array));
}

void Sorter::bubbleSort() {
    for (int i = 0; i < COLUMNS - 1; i++) {
        for (int j = 0; j < COLUMNS - i - 1; j++) {
            mtx1.lock();
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            mtx2.unlock();
        }
    }
}
