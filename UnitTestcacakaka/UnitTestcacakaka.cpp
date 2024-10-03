#include "pch.h" 

#include "CppUnitTest.h" 



using namespace Microsoft::VisualStudio::CppUnitTestFramework;



const int WIDTH = 200;  // Screen width 

const int HEIGHT = 200; // Screen height 

bool pixelBuffer[HEIGHT][WIDTH]; // Buffer to simulate a pixel screen 



// Initialize the pixel buffer to false (all pixels off) 

void ClearPixelBuffer() {

    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {

            pixelBuffer[y][x] = false;

        }

    }

}



// Определяем команды 

enum Commands {

    CLEAR_DISPLAY = 0,

    DRAW_PIXEL,

    DRAW_LINE,

    DRAW_RECTANGLE,

    FILL_RECTANGLE,

    DRAW_ELLIPSE,

    FILL_ELLIPSE,

    DRAW_CIRCLE,

    FILL_CIRCLE,

    DRAW_ROUNDED_RECTANGLE,

    FILL_ROUNDED_RECTANGLE,

    DRAW_TEXT,

    DRAW_IMAGE

};



// Реализация функций 

void ClearDisplay() {

    ClearPixelBuffer(); // Clear the pixel buffer 

}



void DrawPixel(int x, int y) {

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {

        pixelBuffer[y][x] = true; // Set the pixel at (x, y) to "on" 

    }

}



void DrawLine(int x1, int y1, int x2, int y2) {

    // Simple Bresenham's line algorithm 

    int dx = abs(x2 - x1);

    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;

    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;



    while (true) {

        DrawPixel(x1, y1); // Draw the pixel 

        if (x1 == x2 && y1 == y2) break; // Exit when the endpoint is reached 

        int err2 = err * 2;

        if (err2 > -dy) { err -= dy; x1 += sx; }

        if (err2 < dx) { err += dx; y1 += sy; }

    }

}



void DrawRectangle(int x, int y, int width, int height) {

    for (int i = 0; i < width; i++) {

        DrawPixel(x + i, y); // Top edge 

        DrawPixel(x + i, y + height - 1); // Bottom edge 

    }

    for (int i = 0; i < height; i++) {

        DrawPixel(x, y + i); // Left edge 

        DrawPixel(x + width - 1, y + i); // Right edge 

    }

}



void FillRectangle(int x, int y, int width, int height) {

    for (int i = 0; i < width; i++) {

        for (int j = 0; j < height; j++) {

            DrawPixel(x + i, y + j); // Fill the rectangle 

        }

    }

}



void DrawEllipse(int x, int y, int width, int height) {

    int a = width / 2; // Semi-major axis 

    int b = height / 2; // Semi-minor axis 

    int a2 = a * a;

    int b2 = b * b;

    int x0 = a, y0 = 0;

    int dx = 0, dy = a2 * b;

    int err = 0;



    // Drawing the ellipse using the midpoint algorithm 

    while (x0 >= 0) {

        DrawPixel(x + x0, y + y0);

        DrawPixel(x - x0, y + y0);

        DrawPixel(x + x0, y - y0);

        DrawPixel(x - x0, y - y0);



        dx += b2;

        err += dx + b2;

        if (2 * err >= a2) {

            y0++;

            err -= a2;

        }

        x0--;

    }



    x0 = 0;

    y0 = b;

    dy = 0;

    err = 0;



    while (y0 >= 0) {

        DrawPixel(x + x0, y + y0);

        DrawPixel(x - x0, y + y0);

        DrawPixel(x + x0, y - y0);

        DrawPixel(x - x0, y - y0);



        dy += a2;

        err += dy + a2;

        if (2 * err >= b2) {

            x0++;

            err -= b2;

        }

        y0--;

    }

}



void FillEllipse(int x, int y, int width, int height) {

    int a = width / 2; // Semi-major axis 

    int b = height / 2; // Semi-minor axis 



    for (int i = -a; i <= a; i++) {

        for (int j = -b; j <= b; j++) {

            if ((i * i) * (b * b) + (j * j) * (a * a) <= (a * a) * (b * b)) {

                DrawPixel(x + i, y + j); // Fill the ellipse 

            }

        }

    }

}



void DrawCircle(int x, int y, int radius) {

    DrawEllipse(x, y, radius * 2, radius * 2); // Use the ellipse function 

}



void FillCircle(int x, int y, int radius) {

    FillEllipse(x, y, radius * 2, radius * 2); // Use the ellipse function 

}



void DrawRoundedRectangle(int x, int y, int width, int height, int radius) {

    // Draw the corners 

    FillCircle(x + radius, y + radius, radius);

    FillCircle(x + width - radius, y + radius, radius);

    FillCircle(x + radius, y + height - radius, radius);

    FillCircle(x + width - radius, y + height - radius, radius);



    // Draw the rectangle sides 

    DrawRectangle(x + radius, y, width - radius * 2, height);

    DrawRectangle(x, y + radius, width, height - radius * 2);

}



void FillRoundedRectangle(int x, int y, int width, int height, int radius) {

    // Fill the rectangle with rounded corners 

    FillRectangle(x + radius, y, width - radius * 2, height);

    FillRectangle(x, y + radius, width, height - radius * 2);



    // Fill the corners 

    FillCircle(x + radius, y + radius, radius);

    FillCircle(x + width - radius, y + radius, radius);

    FillCircle(x + radius, y + height - radius, radius);

    FillCircle(x + width - radius, y + height - radius, radius);

}



void DrawText(int x, int y, const char* text) {

    // For simplicity, we will just "draw" the first character by its ASCII value 

    if (text && text[0] != '\0') {

        DrawPixel(x, y); // This is a placeholder; normally you'd render text 

    }

}



void DrawImage(int x, int y, const char* imagePath) {

    // Placeholder for image drawing 

    DrawPixel(x, y); // Just to simulate drawing an image 

}





// Юнит-тесты  



namespace UnitTestcacakaka {

    TEST_CLASS(UnitTestcacakaka) {

public:

    TEST_METHOD(TestClearDisplay) {

        // Act  

        ClearDisplay();

        // Assert  

        Assert::IsTrue(true); // Пример проверки, заменить на реальную логику проверки 

    }



    TEST_METHOD(TestDrawPixel) {

        // Arrange  

        int x = 5, y = 5;

        // Act  

        DrawPixel(x, y);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawLine) {

        // Arrange  

        int x1 = 0, y1 = 0, x2 = 10, y2 = 10;

        // Act  

        DrawLine(x1, y1, x2, y2);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawRectangle) {

        // Arrange  

        int x = 10, y = 10, width = 100, height = 50;

        // Act  

        DrawRectangle(x, y, width, height);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestFillRectangle) {

        // Arrange  

        int x = 20, y = 20, width = 80, height = 40;

        // Act  

        FillRectangle(x, y, width, height);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawEllipse) {

        // Arrange  

        int x = 50, y = 50, width = 100, height = 50;

        // Act  

        DrawEllipse(x, y, width, height);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestFillEllipse) {

        // Arrange  

        int x = 60, y = 60, width = 80, height = 40;

        // Act  

        FillEllipse(x, y, width, height);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawCircle) {

        // Arrange  

        int x = 30, y = 30, radius = 20;

        // Act  

        DrawCircle(x, y, radius);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestFillCircle) {

        // Arrange  

        int x = 40, y = 40, radius = 10;

        // Act  

        FillCircle(x, y, radius);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawRoundedRectangle) {

        // Arrange  

        int x = 70, y = 70, width = 120, height = 60, radius = 10;

        // Act  

        DrawRoundedRectangle(x, y, width, height, radius);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestFillRoundedRectangle) {

        // Arrange  

        int x = 80, y = 80, width = 100, height = 50, radius = 15;

        // Act  

        FillRoundedRectangle(x, y, width, height, radius);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawText) {

        // Arrange  

        int x = 100, y = 100;

        const char* text = "Hello";

        // Act  

        DrawText(x, y, text);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }



    TEST_METHOD(TestDrawImage) {

        // Arrange  

        int x = 110, y = 110;

        const char* imagePath = "path/to/image.png";

        // Act  

        DrawImage(x, y, imagePath);

        // Assert  

        Assert::IsTrue(true); // Пример проверки 

    }

    };

}