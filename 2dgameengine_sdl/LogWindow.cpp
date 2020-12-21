#include "LogWindow.h"

LogWindow::LogWindow(int width, int height)
{
    window = SDL_CreateWindow(
        "Log Window",
        CONSOLE_WIDTH,
        CONSOLE_HEIGHT,
        300,
        600,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    this->renderer = SDL_CreateRenderer(window, -1, 0);
    if (!this->renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
}

int LogWindow::numberOfActiveLogs() const
{
    return dat.size();
}

void LogWindow::WriteLog(int position, std::pair<std::string , int> current)
{   
      // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
    std::string num = current.first + std::to_string(current.second);
    //std::string num2 = "Inactive number: " + std::to_string(data.activeEntity);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, num.c_str() , WHITE_COLOR); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 10;  //controls the rect's x coordinate 
    Message_rect.y = 10+(50*position); // controls the rect's y coordinte
    Message_rect.w = 275; // controls the width of the rect
    Message_rect.h = 50; // controls the height of the rect

    //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(this->renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void LogWindow::RenderLog()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    std::map<std::string, std::pair<std::string, int>>::iterator itr;
    int i = 0;
    for (itr = dat.begin(); itr != dat.end(); ++itr) {
        WriteLog(i , itr->second);
        i++;
    }

    SDL_RenderPresent(this->renderer);
}

void LogWindow::UpdateLog(std::string type , std::string title , int value)
{
    dat[type] = std::pair<std::string, int>(title, value);
}


void LogWindow::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
