/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2017-2018 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Menus.h"
#include "Setup.h"

namespace Menus {
    class GameMenu : public GUI::Form {
    private:
        GUI::label title;
        GUI::button resumebtn, exitbtn;

        void onLoad() override {
            glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            title = GUI::label(GetStrbyKey("NEWorld.pause.caption"), -225, 225, 0, 16, 0.5, 0.5, 0.25, 0.25);
            resumebtn = GUI::button(GetStrbyKey("NEWorld.pause.continue"), -200, 200, -35, -3, 0.5, 0.5, 0.5, 0.5);
            exitbtn = GUI::button(GetStrbyKey("NEWorld.pause.back"), -200, 200, 3, 35, 0.5, 0.5, 0.5, 0.5);
            registerControls(3, &title, &resumebtn, &exitbtn);
        }

        void onUpdate() override {
            MutexUnlock(Mutex);
            //Make update thread realize that it should pause
            MutexLock(Mutex);
            if (resumebtn.clicked) {
                GUI::PopPage();
                glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glDepthFunc(GL_LEQUAL);
                glEnable(GL_CULL_FACE);
                setupNormalFog();
                double dmx, dmy;
                glfwGetCursorPos(MainWindow, &dmx, &dmy);
                mx = (int)(dmx / stretch), my = (int)(dmy / stretch);
                updateThreadPaused = false;
            }
            AudioSystem::SpeedOfSound = AudioSystem::Air_SpeedOfSound;
            EFX::EAXprop = Generic;
            EFX::UpdateEAXprop();
            float Pos[] = {0.0f, 0.0f, 0.0f};
            AudioSystem::Update(Pos, false, false, Pos, false, false);
            if (exitbtn.clicked) {
                GUI::BackToMain();
                updateThreadPaused = false;
            }
        }
    };

    void gamemenu() { PushPage(new GameMenu); }
}
