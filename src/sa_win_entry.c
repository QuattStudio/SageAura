/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/






#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern int main(int argc, char **argv);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    (void)hInst; (void)hPrev; (void)lpCmd; (void)nShow;
    return main(__argc, __argv);
}
#endif