#define WIN32_LEAN_AND_MEAN

#include "UserInterface.h"
#include "ConsoleColor.h"

#include <windows.h>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

vector<string> LoadingMessages(const string& command) {
    if (command == "stop") {
        return {
            "    --------------------\n",
            "Saving current session...\n",
            "Closing open connections...\n",
            "Cleaning temporary files...\n",
            "Shutdown complete\n",
            "    --------------------\n"
        };
    }
    else if (command == "wwfs") {
        return {
            "    --------------------\n",
            "Entering file working mode...\n",
            "Preparing file environment...\n",
            "Analyzing system files...\n",
            "Ready for file operations\n",
            "    --------------------\n"
        };
    }
    else if (command == "script") {
        return {
            "    --------------------\n",
            "Entering script configuration mode...\n",
            "Loading script parameters...\n",
            "Initializing script environment...\n",
            "Ready for script configuration\n",
            "    --------------------\n"
        };
    }
    else if (command == "exit") {
        return {
            "    --------------------\n",
            "Exiting file mode...\n",
            "Saving file state...\n",
            "Closing file connections...\n",
            "Returning to intermediate mode\n",
            "    --------------------\n"
        };
    }
    else if (command == "--exit") {
        return {
            "    --------------------\n",
            "Exiting script configuration mode...\n",
            "Saving script parameters...\n",
            "Closing script environment...\n",
            "Returning to intermediate mode\n",
            "    --------------------\n"
        };
    }
    // Команды для работы с файлами
    else if (command == "rd -f") {
        return {
            "Reading a file...\n"
        };
    }
    else if (command == "wt -f") {
        return {
            "Writing to file...\n"
        };
    }
    else if (command == "crt -f") {
        return {
            "Creating file...\n"
        };
    }
    else if (command == "del -f") {
        return {
            "Deleting file...\n"
        };
    }
    else if (command == "clr -f") {
        return {
            "Clearing file contents...\n"
        };
    }
    else if (command == "info -f") {
        return {
            "Getting file info...\n"
        };
    }
    else if (command == "mv -f") {
        return {
            "Moving file...\n"
        };
    }
    else if (command == "rn -f") {
        return {
            "Rename file process...\n"
        };
    }
    else if (command == "cp") {
        return {
            "Copying file...\n"
        };
    }
    // Команды для работы с папками
    else if (command == "mkdir") {
        return {
            "Creating directory...\n"
        };
    }
    else if (command == "rmdir") {
        return {
            "Deleting directory...\n"
        };
    }
    else if (command == "info -d") {
        return {
            "Getting directory info...\n"
        };
    }
    else if (command == "mv -d") {
        return {
            "Moving directory...\n"
        };
    }
    else if (command == "rn -d") {
        return {
            "Rename directory process...\n"
        };
    }
    else if (command == "cp -d") {
        return {
            "Copying directory...\n"
        };
    }
    // Команды для работы с файловой системой
    else if (command == "ls") {
        return {
            "Listing directory contents...\n"
        };
    }
    else if (command == "cd") {
        return {
            "Changing directory...\n",
        };
    }
    else if (command == "echo") {
        return {
            "Processing environment variable...\n",
        };
    }
    else if (command == "pwd") {
        return {
            "Presenting working directory...\n"
        };
    }
    // Операции с аттрибутами и разрешениями
    else if (command == "set att -f") {
        return {
            "Setting file attribute...\n",
        };
    }
    else if (command == "set att -d") {
        return {
            "Setting directory attribute...\n"
        };
    }
    else if (command == "set perm -f") {
        return {
            "Setting file permissions...\n"
        };
    }
    else if (command == "set perm -d") {
        return {
            "Setting directory permissions...\n"
        };
    }
    // Остальные команды
    else if (command == "clear") {
        return {
            "Clearing console...\n"
        };
    }
    else if (command == "mode") {
        return {
            "Checking current mode...\n"
        };
    }
    else if (command == "help") {
        return {
            "Showing help info...\n"
        };
    }
    else {
        return {};
    }
}

void LoadingEffect(const vector<string>& messages) {
    for (const string& msg : messages) {
        cout << msg << endl;
        this_thread::sleep_for(chrono::milliseconds(350));
    }
}

void ClearConsole() {
    system("cls");
}

string ExpandEnvironmentVariables(const string& input) {
    string result = input;
    size_t start_pos = 0;

    // Обрабатываем формат %VARIABLE%
    while ((start_pos = result.find('%', start_pos)) != string::npos) {
        size_t end_pos = result.find('%', start_pos + 1);
        if (end_pos == string::npos) break;

        string var_name = result.substr(start_pos + 1, end_pos - start_pos - 1);

        // Получаем значение переменной окружения
        char buffer[4096];
        DWORD size = GetEnvironmentVariableA(var_name.c_str(), buffer, sizeof(buffer));

        if (size > 0 && size < sizeof(buffer)) {
            // Заменяем переменную на её значение
            result.replace(start_pos, end_pos - start_pos + 1, buffer);
            start_pos += size; // Продолжаем с новой позиции
        }
        else {
            // Переменная не найдена, оставляем как есть
            start_pos = end_pos + 1;
        }
    }
    return result;
}

string ExpandPath(const string& path) {
    string expanded = ExpandEnvironmentVariables(path);

    // Нормализуем разделители путей
    replace(expanded.begin(), expanded.end(), '/', '\\');

    return expanded;
}

string GetUserInput() {
    string input;
    char UserNameBuffer[256];
    DWORD UserNameSize = sizeof(UserNameBuffer);
    string UserName = "User";

    if (GetUserNameA(UserNameBuffer, &UserNameSize)) {
        UserName = UserNameBuffer;
    }
    string promnt = "C:\\Users\\" + UserName + "> ";
    cout << promnt;
    ConsoleColor::GetInstance().blue();
    getline(cin, input);
    ConsoleColor::GetInstance().ResetColor();
    cout << "\n";

    return input;
}

string UserCommand(const set<string>& ValidCommands, string& user_input) {
    while (true) {
        string input = GetUserInput();
        user_input = input; // оригинальный ввод

        string trimmed = input;
        trimmed.erase(0, trimmed.find_first_not_of(" \t"));
        trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

        // Проверка команд без аргументов (точное совпадение)
        if (ValidCommands.count(trimmed)) {
            return trimmed;
        }
        // Проверка команд с аргументами
        for (const string& cmd : ValidCommands) {
            if (cmd.find(' ') != string::npos) { // Команда с параметрами
                string CmdWithSpace = cmd + " ";
                if (trimmed.find(CmdWithSpace) == 0) {
                    // Проверяем, что после команды есть аргументы
                    string AfterCmd = trimmed.substr(CmdWithSpace.length());
                    if (!AfterCmd.empty()) {
                        return cmd;
                    }
                }
            }
            // Проверка специальных команд
            else if (cmd == "cd" || cmd == "ls" || cmd == "echo" ||
                cmd == "mkdir" || cmd == "rmdir") {
                string CmdWithSpace = cmd + " ";
                if (trimmed.find(CmdWithSpace) == 0) {
                    // Проверяем, что после команды есть аргументы
                    string AfterCmd = trimmed.substr(CmdWithSpace.length());
                    if (!AfterCmd.empty() && AfterCmd.find_first_not_of(" \t") != string::npos) {
                        return cmd;
                    }
                }
            }
        }
        if (input.empty()) {
            ConsoleColor::GetInstance().red();
            cout << "    --------------------\n"
                << "Неверный ввод: пустая строка.\n"
                << "    --------------------\n\n";
            ConsoleColor::GetInstance().ResetColor();
        }
        else {
            ConsoleColor::GetInstance().red();
            cout << "    --------------------\n"
                 << "Неверная команда: " << input << ".\n"
                 << "    --------------------\n\n";
            ConsoleColor::GetInstance().ResetColor();
        }
    }
}