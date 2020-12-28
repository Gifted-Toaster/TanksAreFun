#include "LogWindow.h"

#define TEXT_RECT_WIDTH 225
#define VALUE_RECT_WIDTH 50
#define LOG_RECT_HEIGHT 50

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

void LogWindow::RenderText(int position, std::string current) 
{
    SDL_Surface* surfaceText = TTF_RenderText_Solid(Sans, current.c_str(), WHITE_COLOR); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceText); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 10;  //controls the rect's x coordinate 
    Message_rect.y = 10 + (LOG_RECT_HEIGHT * position); // controls the rect's y coordinte
    Message_rect.w = TEXT_RECT_WIDTH; // controls the width of the rect
    Message_rect.h = LOG_RECT_HEIGHT; // controls the height of the rect

    //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(Message);
}

void LogWindow::RenderValue(int position , int current) 
{
    SDL_Surface* surfaceValue = TTF_RenderText_Solid(Sans, std::to_string(current).c_str(), WHITE_COLOR);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(this->renderer, surfaceValue);

    SDL_Rect Message_rect;
    Message_rect.x = 10 + TEXT_RECT_WIDTH;
    Message_rect.y = 10 + (LOG_RECT_HEIGHT * position);
    Message_rect.w = VALUE_RECT_WIDTH; 
    Message_rect.h = LOG_RECT_HEIGHT;

    SDL_RenderCopy(this->renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceValue);
    SDL_DestroyTexture(Message);
}

void LogWindow::WriteLog(int position, std::pair<std::string , int> current)
{   
    RenderText(position , current.first);
    RenderValue(position, current.second);
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
