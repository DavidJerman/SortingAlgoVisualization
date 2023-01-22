//
// Created by david on 1/22/2023.
//

#include "Sorter.h"

Sorter::Sorter() {
    sAppName = "Sorting Algorithms Visualization";
}

bool Sorter::OnUserCreate() {
    resetArray();
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
    if (sorting && !stop) {
        mtx2.lock();
        drawArray();
        mtx1.unlock();
    }
    // Bubble sort
    if (GetKey(olc::Key::B).bPressed || GetKey(olc::Key::K1).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::bubbleSort, this);
        t1.detach();
    }
    // Selection sort
    if (GetKey(olc::Key::S).bPressed || GetKey(olc::Key::K2).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::selectionSort, this);
        t1.detach();
    }
    return true;
}

void Sorter::drawArray() {
    for (int i = 0; i < COLUMNS; i++) {
        drawBar(i, COLUMNS, olc::BLACK, olc::BLACK);
        if (i == arrayPointer)
            drawBar(i, array[i], olc::DARK_GREY);
        else
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
    for (unsigned char &i: array) {
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

template<typename T>
void Sorter::swap(T &t1, T &t2) {
    auto temp = t1;
    t1 = t2;
    t2 = temp;
}

void Sorter::bubbleSort() {
    startSorting();
    for (int i = 0; i < COLUMNS - 1; i++) {
        for (int j = 0; j < COLUMNS - i - 1; j++) {
            mtx1.lock();
            arrayPointer = j;
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
            mtx2.unlock();
            if (stop)
                return stopSorting();
        }
    }
    return stopSorting();
}

void Sorter::selectionSort() {
    startSorting();
    int s;
    for (int i = 0; i < COLUMNS; i++) {
        s = i;
        for (int j = i + 1; j < COLUMNS; j++) {
            mtx1.lock();
            arrayPointer = j;
            if (array[j] < array[s])
                s = j;
            mtx2.unlock();
            if (stop)
                return stopSorting();
        }
        if (s != i)
            swap(array[i], array[s]);
    }
    return stopSorting();
}

void Sorter::stopSorting() {
    mtx1.unlock();
    arrayPointer = 0;
    sorting = false;
    stop = true;
    drawArray();
}

void Sorter::setupArray() {
    resetArray();
    setArray();
    randomizeArrayOrder();
    drawArray();
}

void Sorter::startSorting() {
    sorting = true;
    stop = false;
}
