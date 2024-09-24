/*

unicode.c

Test if the console is correctly set to UTF-8 encoding.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <assert.h>
#include <stdio.h>
#include <string.h>
// On Windows: include windows.h.
#ifdef _WIN32
    #include <windows.h>
#endif

// Main function:
int main(void)
{
    // On Windows: set console to Unicode.
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif

    // Check character byte sizes:
    assert(strlen("o") == 1);
    assert(strlen("ő") == 2);
    assert(strlen("ꙑ") == 3);
    assert(strlen("🌍") == 4);


    // Print accented and special characters:
    char acc_str[] = "Test string: áéó ÁÉÓ αβγ ΑΒΓ абг АБГ グケゲ 🌲🌳🌴\n";
    printf("%s", acc_str);
}
