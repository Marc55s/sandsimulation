#include <stdlib.h>
#include "raylib.h"
#include "../include/mouse.h"

int diffx, diffy;

int min(int a, int b){
    return a > b ? b : a;
}

int max(int a, int b){
    return a < b ? b : a;
}
void container(Rectangle *rect) {
    static int x = -1, y = -1;  // Starting point of the rectangle
    static bool isDrawing = false;  // Tracks whether the rectangle is being drawn

    if (IsMouseButtonPressed(0)) {
        // Set the starting point when the mouse is pressed
        x = GetMouseX();
        y = GetMouseY();
        isDrawing = true;
    }

    if (isDrawing) {
        // Draw the rectangle while the mouse is being held down
        int diffx = GetMouseX();
        int diffy = GetMouseY();
        DrawRectangleLines(min(x, diffx), min(y, diffy), abs(diffx - x), abs(diffy - y), RED);
    }

    if (IsMouseButtonReleased(0) && isDrawing) {
        // Finalize the rectangle when the mouse is released
        int diffx = GetMouseX();
        int diffy = GetMouseY();
        *rect = (Rectangle) {
            min(x, diffx), min(y, diffy), abs(diffx - x), abs(diffy - y)
        };
        isDrawing = false;  // Stop drawing after the mouse is released
    }
}

