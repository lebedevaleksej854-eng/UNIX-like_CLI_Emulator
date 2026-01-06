#define WIN32_LEAN_AND_MEAN

#include "ErrorHandling.h"
#include "UserInterface.h"
#include "ProgramModes.h"
#include "CommandsList.h"
#include "Commands.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void ShowWelcomeMessage() {
    cout << "Welcome to Console Application.\n"
         << "UNIX-like CLI Emulator [Version 1].\n\n";
}

int main() {
    setlocale(LC_ALL, "RU");

    ShowWelcomeMessage();
    ProgramMode CurrentMode = ProgramMode::PRIMARY_MODE;
    bool ProgramRunning = true;

    string user_input;
    while (ProgramRunning) {
        switch (CurrentMode) {
        case ProgramMode::PRIMARY_MODE: {
            string command = UserCommand(PrimaryModeCommands, user_input);
            // Основные команды
            if (command == "wwfs") {
                CommandWWFS();
                CurrentMode = ProgramMode::FS_MODE;
            }
            else if (command == "stop") {
                CommandSTOP();
                ProgramRunning = false;
            }
            else if (command == "clear") {
                CommandCLEAR();
                ShowWelcomeMessage();
            }
            else if (command == "mode") {
                CommandMODE(CurrentMode);
            }
            else if (command == "help") {
                CommandHELP(CurrentMode);
            }
            break;
        }
        case ProgramMode::FS_MODE: {
            string command = UserCommand(FSModeCommands, user_input);
            // Команды для работы с файлами
            if (command == "rd -f") {
                CommandREAD_F(user_input);
            }
            else if (command == "wt -f") {
                CommandWRITE_F(user_input);
            }
            else if (command == "crt -f") {
                CommandCREATE_F(user_input);
            }
            else if (command == "del -f") {
                CommandDELETE_F(user_input);
            }
            else if (command == "clr -f") {
                CommandCLEAR_F(user_input);
            }
            else if (command == "info -f") {
                CommandINFO_F(user_input);
            }
            else if (command == "mv -f") {
                CommandMOVE_F(user_input);
            }
            else if (command == "rn -f") {
                CommandRENAME_F(user_input);
            }
            else if (command == "cp -f") {
                CommandCOPY_F(user_input);
            }
            // Команды для работы с папками
            else if (command == "mkdir") {
                CommandMKDIR(user_input);
            }
            else if (command == "rmdir") {
                CommandRMDIR(user_input);
            }
            else if (command == "info -d") {
                CommandINFO_D(user_input);
            }
            else if (command == "mv -d") {
                CommandMOVE_D(user_input);
            }
            else if (command == "rn -d") {
                CommandRENAME_D(user_input);
            }
            else if (command == "cp -d") {
                CommandCOPY_D(user_input);
            }
            // Команды для работы с файловой системой
            else if (command == "ls") {
                CommandLS(user_input);
            }
            else if (command == "cd") {
                CommandCD(user_input);
            }
            else if (command == "echo") {
                CommandECHO(user_input);
            }
            else if (command == "pwd") {
                CommandPWD();
            }
            // Команды для работы с аттрибутами
            else if (command == "set att -f") {
                CommandSET_FA(user_input);
            }
            else if (command == "set att -d") {
                CommandSET_DA(user_input);
            }
            else if (command == "set perm -f") {
                CommandSET_FP(user_input);
            }
            else if (command == "set perm -d") {
                CommandSET_DP(user_input);
            }
            // Основные команды
            else if (command == "exit") {
                CommandEXIT();
                CurrentMode = ProgramMode::PRIMARY_MODE;
            }
            else if (command == "stop") {
                CommandSTOP();
                ProgramRunning = false;
            }
            else if (command == "clear") {
                CommandCLEAR();
                ShowWelcomeMessage();
            }
            else if (command == "mode") {
                CommandMODE(CurrentMode);
            }
            else if (command == "help") {
                CommandHELP(CurrentMode);
            }
            break;
        }
        }
    }
    cout << "Программа завершена. Нажмите Enter...";
    cin.get();
    return 0;
}