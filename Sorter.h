#ifndef SORTER
#define SORTER

#include <mutex>
#include "olcPixelGameEngine.h"
#include "Constants.h"

class Sorter : public olc::PixelGameEngine {
public:
    Sorter();

    // TODO: Set to private
private:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

    void drawArray();

    void drawBar(int column, int height, olc::Pixel color, olc::Pixel border=olc::GREY);

    void drawText(int x, int y, std::string text, olc::Pixel color);

    void setArray();

    void randomizeArrayOrder();

    void reverseArray();

    void resetArray();

    // Utilities
    template<typename T>
    void swap(T &t1, T &t2);

    void stopSorting();

    void startSorting();

    void setupArray();

    // Sorting algorithms
    void bubbleSort();

    void selectionSort();

    void insertionSort();

    void quickSort(int left, int right);

    void mergeSort(int left, int right);

    void merge(int left, int middle, int right);

    void heapSort();

    void heapify(int n, int i);

    void bucketSort();

    void shellSort();

    void combSort();

    void cocktailSort();

    void gnomeSort();

    void bitonicSort();

    void bitonicMerge(int low, int cnt, int dir);

    byte array[COLUMNS]{}; // Will hold values from 1 to column count

    // Mutex for sorting algorithms
    std::mutex mtx1;
    std::mutex mtx2;

    bool sorting {false};
    bool stop {false};

    int arrayPointer = 0;
};

#endif //SORTER
