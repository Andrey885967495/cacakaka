#include <iostream>   

#include <cstdint>   

#include <cstring>   

enum CommandID {

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

    DRAW_IMAGE,

};

#pragma pack(push, 1) 

struct ClearDisplay {

    uint16_t color;

};

struct DrawPixel {

    int16_t x0;

    int16_t y0;

    uint16_t color;

};

struct DrawLine {

    int16_t x0;

    int16_t y0;

    int16_t x1;

    int16_t y1;

    uint16_t color;

};

struct DrawRectangle {

    int16_t x0;

    int16_t y0;

    int16_t width;

    int16_t height;

    uint16_t color;

};

struct FillRectangle {

    int16_t x0;

    int16_t y0;

    int16_t width;

    int16_t height;

    uint16_t color;

};

struct DrawEllipse {

    int16_t x0;

    int16_t y0;

    int16_t radius_x;

    int16_t radius_y;

    uint16_t color;

};

struct FillEllipse {

    int16_t x0;

    int16_t y0;

    int16_t radius_x;

    int16_t radius_y;

    uint16_t color;

};

struct DrawCircle {

    int16_t x0;

    int16_t y0;

    int16_t radius;

    uint16_t color;

};



struct FillCircle {

    int16_t x0;

    int16_t y0;

    int16_t radius;

    uint16_t color;

};

struct DrawRoundedRectangle {

    int16_t x0;

    int16_t y0;

    int16_t width;

    int16_t height;

    int16_t radius;

    uint16_t color;

};

struct FillRoundedRectangle {

    int16_t x0;

    int16_t y0;

    int16_t width;

    int16_t height;

    int16_t radius;

    uint16_t color;

};

struct DrawText {

    int16_t x0;

    int16_t y0;

    uint16_t color;

    uint32_t font_number;

    char text[100];

};

struct DrawImage {

    int16_t x0;

    int16_t y0;

    int16_t width;

    int16_t height;

    char imagePath[256]; // Добавлено поле для пути к изображению 

};

#pragma pack(pop)   

struct CommandData {

    CommandID cmdID;

    union {

        ClearDisplay clear_display;

        DrawPixel draw_pixel;

        DrawLine draw_line;

        DrawRectangle draw_rectangle;

        FillRectangle fill_rectangle;

        DrawEllipse draw_ellipse;

        FillEllipse fill_ellipse;

        DrawCircle draw_circle;

        FillCircle fill_circle;

        DrawRoundedRectangle draw_rounded_rectangle;

        FillRoundedRectangle fill_rounded_rectangle;

        DrawText draw_text;

        DrawImage draw_image;

    };

};

CommandData parseCommand(uint8_t* input, size_t length) {

    CommandData cmdData;

    std::memcpy(&cmdData.cmdID, input, sizeof(CommandID));

    switch (cmdData.cmdID) {

    case CLEAR_DISPLAY:

        cmdData.clear_display.color = 65535;

        std::memcpy(input + length, &cmdData.clear_display, sizeof(ClearDisplay));

        length += sizeof(ClearDisplay);

        break;

    case DRAW_PIXEL:

        std::memcpy(&cmdData.draw_pixel, input + sizeof(CommandID), sizeof(DrawPixel));

        break;

    case DRAW_LINE:

        std::memcpy(&cmdData.draw_line, input + sizeof(CommandID), sizeof(DrawLine));

        break;

    case DRAW_RECTANGLE:

        std::memcpy(&cmdData.draw_rectangle, input + sizeof(CommandID), sizeof(DrawRectangle));

        break;

    case FILL_RECTANGLE:

        std::memcpy(&cmdData.fill_rectangle, input + sizeof(CommandID), sizeof(FillRectangle));

        break;

    case DRAW_ELLIPSE:

        std::memcpy(&cmdData.draw_ellipse, input + sizeof(CommandID), sizeof(DrawEllipse));

        break;

    case FILL_ELLIPSE:

        std::memcpy(&cmdData.fill_ellipse, input + sizeof(CommandID), sizeof(FillEllipse));

        break;

    case DRAW_CIRCLE:

        std::memcpy(&cmdData.draw_circle, input + sizeof(CommandID), sizeof(DrawCircle));

        break;

    case FILL_CIRCLE:

        std::memcpy(&cmdData.fill_circle, input + sizeof(CommandID), sizeof(FillCircle));

        break;

    case DRAW_ROUNDED_RECTANGLE:

        std::memcpy(&cmdData.draw_rounded_rectangle, input + sizeof(CommandID), sizeof(DrawRoundedRectangle));

        break;

    case FILL_ROUNDED_RECTANGLE:

        std::memcpy(&cmdData.fill_rounded_rectangle, input + sizeof(CommandID), sizeof(FillRoundedRectangle));

        break;

    case DRAW_TEXT:

        std::memcpy(&cmdData.draw_text, input + sizeof(CommandID), sizeof(DrawText));

        break;

    case DRAW_IMAGE:

        std::memcpy(&cmdData.draw_image, input + sizeof(CommandID), sizeof(DrawImage));

        break;

    default:

        std::cerr << "Unknown command ID: " << static_cast<int>(cmdData.cmdID) << std::endl;

        break;

    }

    return cmdData;

}

void printCommand(const CommandData& cmdData, CommandID cmdID) {

    switch (cmdID) {

    case CLEAR_DISPLAY:

        std::cout << "Command: CLEAR_DISPLAY, color: " << cmdData.clear_display.color << std::endl;

        break;

    case DRAW_PIXEL:

        std::cout << "Command: DRAW_PIXEL, x0: " << cmdData.draw_pixel.x0

            << ", y0: " << cmdData.draw_pixel.y0

            << ", color: " << cmdData.draw_pixel.color << std::endl;

        break;

    case DRAW_LINE:

        std::cout << "Command: DRAW_LINE, x0: " << cmdData.draw_line.x0

            << ", y0: " << cmdData.draw_line.y0

            << ", x1: " << cmdData.draw_line.x1

            << ", y1: " << cmdData.draw_line.y1

            << ", color: " << cmdData.draw_line.color << std::endl;

        break;

    case DRAW_RECTANGLE:

        std::cout << "Command: DRAW_RECTANGLE, x0: " << cmdData.draw_rectangle.x0

            << ", y0: " << cmdData.draw_rectangle.y0

            << ", width: " << cmdData.draw_rectangle.width

            << ", height: " << cmdData.draw_rectangle.height

            << ", color: " << cmdData.draw_rectangle.color << std::endl;

        break;

    case FILL_RECTANGLE:

        std::cout << "Command: FILL_RECTANGLE, x0: " << cmdData.fill_rectangle.x0

            << ", y0: " << cmdData.fill_rectangle.y0

            << ", width: " << cmdData.fill_rectangle.width

            << ", height: " << cmdData.fill_rectangle.height

            << ", color: " << cmdData.fill_rectangle.color << std::endl;

        break;

    case DRAW_ELLIPSE:

        std::cout << "Command: DRAW_ELLIPSE, x0: " << cmdData.draw_ellipse.x0

            << ", y0: " << cmdData.draw_ellipse.y0

            << ", radius_x: " << cmdData.draw_ellipse.radius_x

            << ", radius_y: " << cmdData.draw_ellipse.radius_y

            << ", color: " << cmdData.draw_ellipse.color << std::endl;

        break;

    case FILL_ELLIPSE:

        std::cout << "Command: FILL_ELLIPSE, x0: " << cmdData.fill_ellipse.x0

            << ", y0: " << cmdData.fill_ellipse.y0

            << ", radius_x: " << cmdData.fill_ellipse.radius_x

            << ", radius_y: " << cmdData.fill_ellipse.radius_y

            << ", color: " << cmdData.fill_ellipse.color << std::endl;

        break;

    case DRAW_CIRCLE:

        std::cout << "Command: DRAW_CIRCLE, x0: " << cmdData.draw_circle.x0

            << ", y0: " << cmdData.draw_circle.y0

            << ", radius: " << cmdData.draw_circle.radius

            << ", color: " << cmdData.draw_circle.color << std::endl;

        break;

    case FILL_CIRCLE:

        std::cout << "Command: FILL_CIRCLE, x0: " << cmdData.fill_circle.x0

            << ", y0: " << cmdData.fill_circle.y0

            << ", radius: " << cmdData.fill_circle.radius

            << ", color: " << cmdData.fill_circle.color << std::endl;

        break;

    case DRAW_ROUNDED_RECTANGLE:

        std::cout << "Command: DRAW_ROUNDED_RECTANGLE, x0: " << cmdData.draw_rounded_rectangle.x0

            << ", y0: " << cmdData.draw_rounded_rectangle.y0

            << ", width: " << cmdData.draw_rounded_rectangle.width

            << ", height: " << cmdData.draw_rounded_rectangle.height

            << ", radius: " << cmdData.draw_rounded_rectangle.radius

            << ", color: " << cmdData.draw_rounded_rectangle.color << std::endl;

        break;

    case FILL_ROUNDED_RECTANGLE:

        std::cout << "Command: FILL_ROUNDED_RECTANGLE, x0: " << cmdData.fill_rounded_rectangle.x0

            << ", y0: " << cmdData.fill_rounded_rectangle.y0

            << ", width: " << cmdData.fill_rounded_rectangle.width

            << ", height: " << cmdData.fill_rounded_rectangle.height

            << ", radius: " << cmdData.fill_rounded_rectangle.radius

            << ", color: " << cmdData.fill_rounded_rectangle.color << std::endl;

        break;

    case DRAW_TEXT:

        std::cout << "Command: DRAW_TEXT, x0: " << cmdData.draw_text.x0

            << ", y0: " << cmdData.draw_text.y0

            << ", color: " << cmdData.draw_text.color

            << ", font_number: " << cmdData.draw_text.font_number

            << ", text: " << cmdData.draw_text.text << std::endl;

        break;

    case DRAW_IMAGE:

        std::cout << "Command: DRAW_IMAGE, x0: " << cmdData.draw_image.x0

            << ", y0: " << cmdData.draw_image.y0

            << ", width: " << cmdData.draw_image.width

            << ", height: " << cmdData.draw_image.height << std::endl;

        break;

    default:

        std::cout << "Unknown command ID" << std::endl;

        break;

    }

}

int main() {

    const size_t MAX_INPUT_LENGTH = 1024;

    uint8_t input[MAX_INPUT_LENGTH];

    size_t length = 0;



    while (true) {



        std::cout << "Enter a command:\n"

            << " 0 - CLEAR_DISPLAY\n"

            << " 1 - DRAW_PIXEL\n"

            << " 2 - DRAW_LINE\n"

            << " 3 - DRAW_RECTANGLE\n"

            << " 4 - FILL_RECTANGLE\n"

            << " 5 - DRAW_ELLIPSE\n"

            << " 6 - FILL_ELLIPSE\n"

            << " 7 - DRAW_CIRCLE\n"

            << " 8 - FILL_CIRCLE\n"

            << " 9 - DRAW_ROUNDED_RECTANGLE\n"

            << " 10 - FILL_ROUNDED_RECTANGLE\n"

            << " 11 - DRAW_TEXT\n"

            << " 12 - DRAW_IMAGE\n"

            << "-1 - Exit\n"

            << "Please choose an option: ";



        int command;

        std::cin >> command;



        if (std::cin.fail() || command < -1 || command > 12) {

            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please try again." << std::endl;

            continue;

        }



        if (command == -1) {

            break;

        }



        CommandID cmdID = static_cast<CommandID>(command);

        std::memcpy(input + length, &cmdID, sizeof(CommandID));

        length += sizeof(CommandID);



        switch (cmdID) {

        case CLEAR_DISPLAY: {



            std::cout << "CLEAR_DISPLAY selected. Color set to white." << std::endl;

            break;

        }

        case DRAW_PIXEL: {

            DrawPixel drawPixel;

            std::cout << "Enter x0, y0, color: ";

            std::cin >> drawPixel.x0 >> drawPixel.y0 >> drawPixel.color;



            std::memcpy(input + length, &drawPixel, sizeof(DrawPixel));

            length += sizeof(DrawPixel);

            break;

        }



        case DRAW_LINE: {

            DrawLine drawLine;

            std::cout << "Enter x0, y0, x1, y1, color: ";

            std::cin >> drawLine.x0 >> drawLine.y0 >> drawLine.x1 >> drawLine.y1 >> drawLine.color;



            std::memcpy(input + length, &drawLine, sizeof(DrawLine));

            length += sizeof(DrawLine);

            break;

        }



        case DRAW_RECTANGLE: {

            DrawRectangle drawRectangle;

            std::cout << "Enter x0, y0, width, height, color: ";

            std::cin >> drawRectangle.x0 >> drawRectangle.y0 >> drawRectangle.width >> drawRectangle.height >> drawRectangle.color;



            std::memcpy(input + length, &drawRectangle, sizeof(DrawRectangle));

            length += sizeof(DrawRectangle);

            break;

        }



        case FILL_RECTANGLE: {

            FillRectangle fillRectangle;

            std::cout << "Enter x0, y0, width, height, color: ";

            std::cin >> fillRectangle.x0 >> fillRectangle.y0 >> fillRectangle.width >> fillRectangle.height >> fillRectangle.color;



            std::memcpy(input + length, &fillRectangle, sizeof(FillRectangle));

            length += sizeof(FillRectangle);

            break;

        }



        case DRAW_ELLIPSE: {

            DrawEllipse drawEllipse;

            std::cout << "Enter x0, y0, radius_x, radius_y, color: ";

            std::cin >> drawEllipse.x0 >> drawEllipse.y0 >> drawEllipse.radius_x >> drawEllipse.radius_y >> drawEllipse.color;



            std::memcpy(input + length, &drawEllipse, sizeof(DrawEllipse));

            length += sizeof(DrawEllipse);

            break;

        }



        case FILL_ELLIPSE: {

            FillEllipse fillEllipse;

            std::cout << "Enter x0, y0, radius_x, radius_y, color: ";

            std::cin >> fillEllipse.x0 >> fillEllipse.y0 >> fillEllipse.radius_x >> fillEllipse.radius_y >> fillEllipse.color;



            std::memcpy(input + length, &fillEllipse, sizeof(FillEllipse));

            length += sizeof(FillEllipse);

            break;

        }



        case DRAW_CIRCLE: {

            DrawCircle drawCircle;

            std::cout << "Enter x0, y0, radius, color: ";

            std::cin >> drawCircle.x0 >> drawCircle.y0 >> drawCircle.radius >> drawCircle.color;



            std::memcpy(input + length, &drawCircle, sizeof(DrawCircle));

            length += sizeof(DrawCircle);

            break;

        }



        case FILL_CIRCLE: {

            FillCircle fillCircle;

            std::cout << "Enter x0, y0, radius, color: ";

            std::cin >> fillCircle.x0 >> fillCircle.y0 >> fillCircle.radius >> fillCircle.color;



            std::memcpy(input + length, &fillCircle, sizeof(FillCircle));

            length += sizeof(FillCircle);

            break;

        }



        case DRAW_ROUNDED_RECTANGLE: {

            DrawRoundedRectangle drawRoundedRectangle;

            std::cout << "Enter x0, y0, width, height, radius, color: ";

            std::cin >> drawRoundedRectangle.x0 >> drawRoundedRectangle.y0 >> drawRoundedRectangle.width >> drawRoundedRectangle.height >> drawRoundedRectangle.radius >> drawRoundedRectangle.color;



            std::memcpy(input + length, &drawRoundedRectangle, sizeof(DrawRoundedRectangle));

            length += sizeof(DrawRoundedRectangle);

            break;

        }



        case FILL_ROUNDED_RECTANGLE: {

            FillRoundedRectangle fillRoundedRectangle;

            std::cout << "Enter x0, y0, width, height, radius, color: ";

            std::cin >> fillRoundedRectangle.x0 >> fillRoundedRectangle.y0 >> fillRoundedRectangle.width >> fillRoundedRectangle.height >> fillRoundedRectangle.radius >> fillRoundedRectangle.color;



            std::memcpy(input + length, &fillRoundedRectangle, sizeof(FillRoundedRectangle));

            length += sizeof(FillRoundedRectangle);

            break;

        }



        case DRAW_TEXT: {

            DrawText drawText;

            std::cout << "Enter x0, y0, color, font_number, text: ";

            std::cin >> drawText.x0 >> drawText.y0 >> drawText.color >> drawText.font_number;



            std::cin.ignore();

            std::cin.getline(drawText.text, sizeof(drawText.text));

            std::memcpy(input + length, &drawText, sizeof(DrawText));

            length += sizeof(DrawText);

            break;

        }

        case DRAW_IMAGE: {

            DrawImage drawImage;

            std::cout << "Enter x0, y0, width, height: ";

            std::cin >> drawImage.x0 >> drawImage.y0 >> drawImage.width >> drawImage.height;



            std::cout << "Enter the image path: ";

            std::cin.ignore();

            std::cin.getline(drawImage.imagePath, sizeof(drawImage.imagePath));



            std::memcpy(input + length, &drawImage, sizeof(DrawImage));

            length += sizeof(DrawImage);

            break;

        }



        default:

            std::cout << "Unknown command." << std::endl;

            break;

        }



        CommandData cmdData = parseCommand(input, length);

        printCommand(cmdData, cmdID);



        length = 0;

    }

    return 0;

}