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
    // Insertion sort
    if (GetKey(olc::Key::I).bPressed || GetKey(olc::Key::K3).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::insertionSort, this);
        t1.detach();
    }
    // Shell sort
    if (GetKey(olc::Key::H).bPressed || GetKey(olc::Key::K4).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::shellSort, this);
        t1.detach();
    }
    // Radix sort
    if (GetKey(olc::Key::R).bPressed || GetKey(olc::Key::K5).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::radixSort, this);
        t1.detach();
    }
    // Bogosort
    if (GetKey(olc::Key::G).bPressed || GetKey(olc::Key::K6).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::bogoSort, this);
        t1.detach();
    }
    // Counting sort
    if (GetKey(olc::Key::C).bPressed || GetKey(olc::Key::K7).bPressed) {
        stop = true;
        mtx1.lock();
        setupArray();
        mtx1.unlock();
        std::thread t1(&Sorter::countingSort, this);
        t1.detach();
    }
    return true;
}

void Sorter::drawArray() {
    for (int i = 0; i < BARS; i++) {
        drawBar(i, BARS, olc::BLACK, olc::BLACK);
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
    if (height > BARS) {
        return;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < BAR_WIDTH; j++) {
            for (int k = 0; k < BAR_HEIGHT; k++) {
                if (j == 0 || j == BAR_WIDTH - 1)
                    Draw(column * BAR_WIDTH + j, ScreenHeight() - (i) * BAR_HEIGHT + k - BAR_HEIGHT, border);
                else
                    Draw(column * BAR_WIDTH + j, ScreenHeight() - (i) * BAR_HEIGHT + k - BAR_HEIGHT, color);
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
    for (int i = 0; i < BARS; i++) {
        array[i] = i + 1;
    }
}

// This might not be the best way to randomize an array, but it will do for now
void Sorter::randomizeArrayOrder() {
    for (unsigned char &i: array) {
        int randomIndex = rand() % BARS;
        int temp = i;
        i = array[randomIndex];
        array[randomIndex] = temp;
    }
}

void Sorter::reverseArray() {
    for (int i = 0; i < BARS; i++) {
        array[i] = BARS - i;
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
    for (int i = 0; i < BARS - 1; i++) {
        for (int j = 0; j < BARS - i - 1; j++) {
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
    for (int i = 0; i < BARS; i++) {
        s = i;
        for (int j = i + 1; j < BARS; j++) {
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

void Sorter::setupArray() {
    resetArray();
    setArray();
    randomizeArrayOrder();
    drawArray();
}

bool Sorter::isSorted() {
    for (int i = 0; i < BARS - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}


void Sorter::stopSorting() {
    mtx1.unlock();
    arrayPointer = 0;
    sorting = false;
    stop = true;
    drawArray();
}

void Sorter::startSorting() {
    sorting = true;
    stop = false;
}

void Sorter::insertionSort() {
    startSorting();
    int j;
    for (int i = 1; i < BARS; i++) {
        j = i;
        while (j > 0 && array[j - 1] > array[j]) {
            mtx1.lock();
            arrayPointer = j;
            swap(array[j], array[j - 1]);
            mtx2.unlock();
            if (stop)
                return stopSorting();
            j--;
        }
    }
    return stopSorting();
}

struct Node {
    int value;
    Node *next;
};

void Sorter::bucketSort() {
    startSorting();
    // Count phase
    int max = array[0], min = array[0];
    for (int i = 1; i < BARS; i++) {
        mtx1.lock();
        arrayPointer = i;
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
        mtx2.unlock();
    }
    // Create lists
    auto range = (max - min) / BARS;
    std::vector<Node*> bucketList(range);
    // Init
    for (auto &node: bucketList)
        node = nullptr;
    // Add items to buckets
    for (unsigned char &number : array) {
        auto index = number - min;
        auto ptr = bucketList[index];
        if (!bucketList[index])
            bucketList[index] = new Node {number, nullptr};
        else {
            while (!ptr->next) ptr = ptr->next;
            ptr->next = new Node {number, nullptr};
        }
    }
    // Empty the buckets

    return stopSorting();
}

void Sorter::countingSort() {
    startSorting();
    int max = array[0], min = array[0];
    for (int i = 1; i < BARS; i++) {
        mtx1.lock();
        arrayPointer = i;
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
        mtx2.unlock();
    }
    int range = max - min + 1;
    int count[range];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < BARS; i++) {
        mtx1.lock();
        arrayPointer = i;
        count[array[i] - min]++;
        mtx2.unlock();
    }
    for (int i = 0, j = 0; i < range; i++) {
        arrayPointer = j;
        mtx1.lock();
        if (count[i]--)
            array[j++] = i + min;
        mtx2.unlock();
    }
    return stopSorting();
}

/**
 * Radix sort implementation on bit level
 */
void Sorter::radixSort() {
    startSorting();
    // Binary radix
    for (int bit = 0; bit < sizeof(byte); bit++) {
        // Bucket sort

    }
    return stopSorting();
}

void Sorter::shellSort() {
    startSorting();
    // Magic
    return stopSorting();
}

void Sorter::bogoSort() {
    startSorting();
    while (!isSorted()) {
        mtx1.lock();
        randomizeArrayOrder();
        mtx2.unlock();
        if (stop)
            return stopSorting();
    }
    return stopSorting();
}
