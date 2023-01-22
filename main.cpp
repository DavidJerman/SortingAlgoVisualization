#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "Sorter.h"
#include "Constants.h"

int main() {

    Sorter sorter;
    if (sorter.Construct(COLUMNS * COLUMN_WIDTH, COLUMNS * COLUMN_HEIGHT, PIXEL_WIDTH, PIXEL_HEIGHT, false, true))
        sorter.Start();

    return 0;
}
