#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

void spamInput(int virtualKey, bool isMouse) {
    INPUT input = {0};
    if (isMouse) {
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = (virtualKey == VK_LBUTTON ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);
        SendInput(1, &input, sizeof(INPUT));

        input.mi.dwFlags = (virtualKey == VK_LBUTTON ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);
        SendInput(1, &input, sizeof(INPUT));
    } else {
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = virtualKey;

        SendInput(1, &input, sizeof(INPUT));
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

int main() {
    bool f6Held = false;
    bool inputSelected = false;
    int selectedInput = 0;
    bool isMouse = false;
    float timing;

    printf("Hold down F6 and whatever other button you want to spam, and it will spam it as long as F6 is held.");
    printf("Anything below 1 is unstable, but fast.");
    printf("\n\nInput the delay between inputs: ");
    scanf("%f", &timing);

    while (true) {
        if (GetAsyncKeyState(VK_F6) & 0x8000) {
            if (!f6Held) {
                f6Held = true;
                inputSelected = false;
                selectedInput = 0;
            }

            if (!inputSelected) {
                for (int vk = 0x08; vk <= 0xFE; ++vk) {
                    if (GetAsyncKeyState(vk) & 0x8000 && vk != VK_F6) {
                        selectedInput = vk;
                        inputSelected = true;
                        isMouse = false;
                        break;
                    }
                }

                if (!inputSelected) {
                    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                        selectedInput = VK_LBUTTON;
                        inputSelected = true;
                        isMouse = true;
                    } else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                        selectedInput = VK_RBUTTON;
                        inputSelected = true;
                        isMouse = true;
                    }
                }
            }

            if (inputSelected && selectedInput != 0) {
                Sleep(timing);
                spamInput(selectedInput, isMouse);
            }
        } else {
            if (f6Held) {
                f6Held = false;
                inputSelected = false;
                selectedInput = 0;
                isMouse = false;
            }
        }
        if (!timing >= 1.0f) {Sleep(1);}
    }

    return 0;
}
