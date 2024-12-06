#include <conio.h>
#include "AllHeader/Window.h"
#include "AllHeader/RandFunction.h"

int main()
{
    Window window(rand_range_int(7, 14), rand_range_int(6, 12));

    _getch();

    return 0;
}
