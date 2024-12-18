#include "Mouse.h"

void MouseKeyPressEvents(SDL_Event* SDL_event, AllObjectsClass* allObjectsClass) {
    if (SDL_event->type == SDL_MOUSEBUTTONDOWN || SDL_event->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        switch (SDL_event->button.button) {
        case SDL_BUTTON_LEFT:
            if (SDL_event->type == SDL_MOUSEBUTTONDOWN) {
                printf("MOUSE LEFT DOWN: (%d, %d)\n", x, y);
                SelectPickedMouseObject(allObjectsClass, x, y);
            }
            else {
                printf("MOUSE LEFT UP: (%d, %d)\n", x, y);
                //SelectPickedMouseObject(allObjectsClass, x, y);
            }
            break;
        case SDL_BUTTON_RIGHT:
            if (SDL_event->type == SDL_MOUSEBUTTONDOWN) {
                printf("MOUSE RIGHT DOWN: (%d, %d)\n", x, y);
            }
            else {
                printf("MOUSE RIGHT UP: (%d, %d)\n", x, y);
            }
            break;
        }
    }
}
