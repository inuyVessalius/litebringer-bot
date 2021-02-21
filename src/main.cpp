#include <litebringer_bot.hpp>

int main() {
    do {
        runAutoClicker();
    } while (GetAsyncKeyState(VK_ESCAPE) == 0);

    // camera();

    return 0;
}

