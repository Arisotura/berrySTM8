/*
    Copyright 2024 Arisotura

    This file is part of berrySTM8.

    berrySTM8 is free software: you can redistribute it and/or modify it under
    the terms of the GNU General Public License as published by the Free
    Software Foundation, either version 3 of the License, or (at your option)
    any later version.

    berrySTM8 is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with berrySTM8. If not, see http://www.gnu.org/licenses/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "STM8.h"

using namespace std;



int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    printf("berrySTM8\n");

    STM8* stm = new STM8();

    if (!stm->LoadImage(0, "eeprom.bin"))
    {
        printf("failed to load EEPROM\n");
        delete stm;
        SDL_Quit();
        return -1;
    }
    if (!stm->LoadImage(1, "flash.bin"))
    {
        printf("failed to load FLASH\n");
        delete stm;
        SDL_Quit();
        return -1;
    }

    // TODO: the window should display I/O pins and shit

    SDL_Window* window = SDL_CreateWindow(
        "berrySTM8",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        854, 480,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    SDL_Texture* framebuf = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 854, 480);
    if (!framebuf)
    {
        printf("texture shat itself :(\n");
        return -1;
    }

    stm->Reset();

    stm->SetInput("PE0", 1); // pin 19
    stm->SetInput("PG3", 1); // pin 17
    stm->SetInput("PD2", 1); // pin 27
    stm->SetInput("PE5", 1); // sync button
    stm->SetInput("PE7", 1); // power button

    u32 keymask = 0;
    bool touch = false;
    int touchX = 0, touchY = 0;

    bool quit = false;
    for (;;)
    {
        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                if (evt.key.keysym.scancode == SDL_SCANCODE_P)
                    stm->SetInput("PE7", 0);
                break;

            case SDL_KEYUP:
                if (evt.key.keysym.scancode == SDL_SCANCODE_P)
                    stm->SetInput("PE7", 1);
                break;

            /*case SDL_KEYDOWN:
                for (int i = 0; keymap[i] != -1; i++)
                {
                    if (evt.key.keysym.scancode == keymap[i])
                        keymask |= (1<<i);
                }
                break;

            case SDL_KEYUP:
                for (int i = 0; keymap[i] != -1; i++)
                {
                    if (evt.key.keysym.scancode == keymap[i])
                        keymask &= ~(1<<i);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (evt.button.button == SDL_BUTTON_LEFT)
                {
                    touch = true;
                    touchX = evt.button.x;
                    touchY = evt.button.y;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (evt.button.button == SDL_BUTTON_LEFT)
                {
                    touch = false;
                    touchX = evt.button.x;
                    touchY = evt.button.y;
                }
                break;

            case SDL_MOUSEMOTION:
                if (touch)
                {
                    touchX = evt.motion.x;
                    touchY = evt.motion.y;
                }
                break;*/
            }
        }
        if (quit) break;

        /*WUP::SetKeyMask(keymask);
        WUP::SetTouchCoords(touch, touchX, touchY);

        // run emulation here
        WUP::RunFrame();

        {
            u32* src = WUP::GetFramebuffer();
            u8* dst;
            int stride;
            SDL_LockTexture(framebuf, nullptr, (void**)&dst, &stride);

            for (int y = 0; y < 480; y++)
            {
                memcpy(dst, src, 854*4);
                src += 854;
                dst += stride;
            }

            SDL_UnlockTexture(framebuf);
        }*/

        //stm->CPUExecute(64);
        stm->CPUExecute(65536);

        // redraw
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, framebuf, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(framebuf);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    delete stm;

    SDL_Quit();
    return 0;
}
