#include "ErrorHandling.h"
#include "UserInterface.h"
#include "ConsoleColor.h"
#include "CommandsList.h"
#include "Commands.h"

#include <iostream>
#include <string>

using namespace std;

void CommandSTOP() {
    auto messages = LoadingMessages("stop");
    LoadingEffect(messages);
}

void CommandWWFS() {
    auto messages = LoadingMessages("wwfs");
    LoadingEffect(messages);
}

string RemoveQuotes(const string& input) {
    string result = input;
    if (!result.empty()) {
        if (result.front() == '"' && result.back() == '"') {
            result = result.substr(1, result.size() - 2);
        }
        else if (result.front() == '"') {
            result = result.substr(1);
        }
        else if (result.back() == '"') {
            result.pop_back();
        }
    }
    return result;
}

void CommandREAD_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("rd -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 6 && input.substr(0, 6) == "rd -f ") {
        name = input.substr(6);
    }
    else if (input == "rd -f") {
        name = GetUserInput();
    }
    else if (input.find("rd -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    ifstream file;
    try {
        CheckPreOpenErrors_Read(name);

        CheckOpenProcessErrors_Read(name, file);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "      Данные из файла:\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();

        CheckReadProcessErrors(name, file);

        ConsoleColor::GetInstance().green();
        cout << "\n"
            << "    --------------------\n"
            << "   Файл успешно прочитан.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();

        if (file.is_open()) {
            file.close();
        }
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    SetConsoleOutputCP(866);
}

void CommandWRITE_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("wt -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 6 && input.substr(0, 6) == "wt -f ") {
        name = input.substr(6);
    }
    else if (input == "wt -f") {
        name = GetUserInput();
    }
    else if (input.find("wt -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    ofstream file;
    try {
        CheckPreOpenErrors_Write(name);

        CheckOpenProcessErrors_Write(name, file);

        CheckWriteProcessErrors(file);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "Данные успешно записаны в файл: " << name << "\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();

        if (file.is_open()) {
            file.close();
        }
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandCREATE_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("crt -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 7 && input.substr(0, 7) == "crt -f ") {
        name = input.substr(7);
    }
    else if (input == "crt -f") {
        name = GetUserInput();
    }
    else if (input.find("crt -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    ofstream file;
    try {
        CheckPreOpenErrors_Create(name);

        if (path.has_parent_path()) {
            filesystem::create_directories(path.parent_path());
        }
        CheckCreationProcessErrors(name, file);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "Файл успешно создан: " << name << "\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();

        if (file.is_open()) {
            file.close();
        }
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandDELETE_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("del -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 7 && input.substr(0, 7) == "del -f ") {
        name = input.substr(7);
    }
    else if (input == "del -f") {
        name = GetUserInput();
    }
    else if (input.find("del -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    try {
        CheckPreOpenErrors_Delete(name);

        CheckDeleteProcessErrors(name);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "Файл успешно удален: " << name << "\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandCLEAR_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("clr -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 7 && input.substr(0, 7) == "clr -f ") {
        name = input.substr(7);
    }
    else if (input == "clr -f") {
        name = GetUserInput();
    }
    else if (input.find("clr -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    ofstream file;
    try {
        CheckPreOpenErrors_Clear(name);

        CheckClearProcessErrors(name, file);

        file.close();

        ifstream check_file(name);
        if (check_file.is_open()) {
            check_file.seekg(0, ios::end);
            streampos file_size = check_file.tellg();
            check_file.close();

            ConsoleColor::GetInstance().green();
            cout << "    --------------------\n"
                << "Файл успешно очищен: " << name << "\n"
                << "    --------------------\n\n";
            ConsoleColor::GetInstance().ResetColor();
        }
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandINFO_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("info -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 8 && input.substr(0, 8) == "info -f ") {
        name = input.substr(8);
    }
    else if (input == "info -f") {
        name = GetUserInput();
    }
    else if (input.find("info -f ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    try {
        CheckPreOpenErrors_Info(name);

        DisplayFileInfo(name);
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandMOVE_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("mv -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string source_path, destination_path;

    source_path = GetUserInput();
    source_path = RemoveQuotes(source_path);

    destination_path = GetUserInput();
    destination_path = RemoveQuotes(destination_path);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_MOVE(source_path, destination_path);

        CheckMoveProcessErrors(source_path, destination_path);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Файл успешно перемещен.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandRENAME_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("rn -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string old_name, new_name;

    old_name = GetUserInput();
    old_name = RemoveQuotes(old_name);

    new_name = GetUserInput();
    new_name = RemoveQuotes(new_name);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_RENAME(old_name, new_name);

        CheckRenameProcessErrors(old_name, new_name);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Файл успешно переименован.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandCOPY_F(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("cp -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string source_path, destination_path;

    source_path = GetUserInput();
    source_path = RemoveQuotes(source_path);

    destination_path = GetUserInput();
    destination_path = RemoveQuotes(destination_path);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_CP(source_path, destination_path);

        CheckCopyProcessErrors(source_path, destination_path);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Файл успешно скопирован.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandMKDIR(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("mkdir");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 6 && input.substr(0, 6) == "mkdir ") {
        name = input.substr(6);
    }
    else if (input == "mkdir") {
        name = GetUserInput();
    }
    else if (input.find("mkdir ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_MKDIR(name);

        CheckMkdirProcessErrors(name);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Директория успешно создана.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandRMDIR(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("rmdir");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 6 && input.substr(0, 6) == "rmdir ") {
        name = input.substr(6);
    }
    else if (input == "rmdir") {
        name = GetUserInput();
    }
    else if (input.find("mkdir ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_RMDIR(name);

        CheckRmdirProcessErrors(name);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Директория успешно удалена.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandINFO_D(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("info -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input.size() > 8 && input.substr(0, 8) == "info -d ") {
        name = input.substr(8);
    }
    else if (input == "info -d") {
        name = GetUserInput();
    }
    else if (input.find("info -d ") == 0) {
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        name = RemoveQuotes(name);
    }
    else {
        name = input;
    }
    name = RemoveQuotes(name);
    SetConsoleCP(866);

    filesystem::path path(name);

    try {
        CheckPreOpenErrors_INFO_D(name);

        DisplayDirectoryInfo(name);
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandMOVE_D(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("mv -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string source_path, destination_path;

    source_path = GetUserInput();
    source_path = RemoveQuotes(source_path);
    source_path = ExpandPath(source_path);

    destination_path = GetUserInput();
    destination_path = RemoveQuotes(destination_path);
    destination_path = ExpandPath(destination_path);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_MOVE_D(source_path, destination_path);

        CheckMoveProcessErrors_D(source_path, destination_path);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Папка успешно перемещена.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandRENAME_D(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("rn -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string old_name, new_name;

    old_name = GetUserInput();
    old_name = RemoveQuotes(old_name);
    old_name = ExpandPath(old_name);

    new_name = GetUserInput();
    new_name = RemoveQuotes(new_name);
    new_name = ExpandPath(new_name);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_RENAME_D(old_name, new_name);

        CheckRenameProcessErrors_D(old_name, new_name);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Папка успешно переименована.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandCOPY_D(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("cp -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);

    string source_path, destination_path;

    source_path = GetUserInput();
    source_path = RemoveQuotes(source_path);
    source_path = ExpandPath(source_path);

    destination_path = GetUserInput();
    destination_path = RemoveQuotes(destination_path);
    destination_path = ExpandPath(destination_path);

    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_CP_D(source_path, destination_path);

        CheckCopyProcessErrors_D(source_path, destination_path);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "  Папка успешно скопирована.\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandLS(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("ls");
    LoadingEffect(messages);

    ConsoleColor::GetInstance().ResetColor();
    string CurrentDirectory = filesystem::current_path().string();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);

    if (input == "ls") {
        CurrentDirectory = filesystem::current_path().string();
    }
    else if (input.find("ls ") == 0) {
        CurrentDirectory = input.substr(3);
        CurrentDirectory.erase(0, CurrentDirectory.find_first_not_of(" \t"));
        CurrentDirectory.erase(CurrentDirectory.find_last_not_of(" \t") + 1);
        CurrentDirectory = RemoveQuotes(CurrentDirectory);
        CurrentDirectory = ExpandPath(CurrentDirectory);
    }
    else {
        CurrentDirectory = input;
    }
    SetConsoleCP(866);

    try {
        if (CurrentDirectory != filesystem::current_path().string()) {
            CheckPreOpenErrors_LS(CurrentDirectory);
        }
        cout << "    --------------------\n"
             << "Содержимое директории " << "'" << CurrentDirectory << "'" << ":\n\n";

        int DirCount = 0;
        int FileCount = 0;

        error_code ec;
        auto dir_iter = filesystem::directory_iterator(CurrentDirectory, ec);
        if (ec) {
            throw Exception(ErrorBase_SystemErrors::Error_20(), 20);
        }
        for (const auto& entry : filesystem::directory_iterator(CurrentDirectory)) {
            string filename = entry.path().filename().string();
            string type = entry.is_directory() ? "[DIR]  " : "[FILE] ";
            string size;

            if (!entry.is_directory()) {
                try {
                    uintmax_t file_size = entry.file_size();
                    string size_str;

                    if (file_size < 1024) {
                        size_str = to_string(file_size) + " B";
                    }
                    else if (file_size < 1024 * 1024) {
                        size_str = to_string(file_size / 1024) + " KB";
                    }
                    else {
                        size_str = to_string(file_size / (1024 * 1024)) + " MB";
                    }
                    size = " (" + size_str + ")";
                    FileCount++;
                }
                catch (...) {
                    size = " (недоступен)";
                    FileCount++;
                }
            }
            else {
                DirCount++;
            }
            cout << type << " " << filename << size << endl;
        }
        cout << "\nИтого: " << DirCount << " папок, " << FileCount << " файлов\n"
             << "    --------------------\n\n";
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
             << "Код ошибки: " << ex.code() << ".\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandCD(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("cd");
    LoadingEffect(messages);

    ConsoleColor::GetInstance().ResetColor();
    string CurrentDirectory = filesystem::current_path().string();

    SetConsoleCP(1251);
    string input = RemoveQuotes(name);
    string TargetPath;

    if (input == "cd") {
        TargetPath = getenv("USERPROFILE");
    }
    else if (input.find("cd ") == 0) {
        TargetPath = input.substr(3);
        TargetPath.erase(0, TargetPath.find_first_not_of(" \t"));
        TargetPath.erase(TargetPath.find_last_not_of(" \t") + 1);
        TargetPath = RemoveQuotes(TargetPath);
        TargetPath = ExpandPath(TargetPath);
    }
    else {
        TargetPath = input;
    }
    SetConsoleCP(866);

    try {
        CheckPreOpenErrors_CD(TargetPath);

        filesystem::path NewPath;

        if (TargetPath == "..") {
            NewPath = filesystem::path(CurrentDirectory).parent_path();
        }
        else if (TargetPath == "." || TargetPath.empty()) {
            NewPath = CurrentDirectory;
        }
        else {
            NewPath = filesystem::path(TargetPath);

            if (!NewPath.is_absolute()) {
                NewPath = filesystem::path(CurrentDirectory) / NewPath;
            }
        }
        error_code ec;
        filesystem::current_path(NewPath, ec);
        if (ec) {
            throw Exception(ErrorBase_SystemErrors::Error_21(), 21);
        }
        CurrentDirectory = filesystem::absolute(NewPath).string();

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "Текущая директория: " << CurrentDirectory << "\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
            << "Код ошибки: " << ex.code() << ".\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandECHO(const string& input) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("echo");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    if (input.length() > 5) {
        string result;
        string expression = input.substr(5); // Убираем "echo "

        if (expression.find('%') != string::npos) {
            result = ExpandEnvironmentVariables(expression);
            cout << "    --------------------\n"
                 << "Результат: " << result << "\n"
                 << "    --------------------\n\n";
        }
        else {
            result = expression;
            ConsoleColor::GetInstance().red();
            cout << "    --------------------\n"
                 << "Неверный ввод: использован аргумент " << result << ".\n"
                 << "Аргумент должен быть в формате %VAR%.\n"
                 << "    --------------------\n\n";
            ConsoleColor::GetInstance().ResetColor();
        }
    }
    else {
        ConsoleColor::GetInstance().yellow();
        cout << "     Доступные переменные окружения Windows\n"
             << "\n> СИСТЕМНЫЕ ПЕРЕМЕННЫЕ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %USERPROFILE%              - Домашняя директория\n"
             << "  %USERNAME%                 - Имя текущего пользователя\n"
             << "  %COMPUTERNAME%             - Имя компьютера\n"
             << "  %OS%                       - Версия операционной системы\n"
             << "  %PROCESSOR_ARCHITECTURE%   - Архитектура процессора\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> ПУТИ СИСТЕМЫ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %WINDIR%          - Директория Windows\n"
             << "  %SYSTEMROOT%      - Корневая директория системы\n"
             << "  %SYSTEMDRIVE%     - Системный диск (обычно C:)\n"
             << "  %HOMEDRIVE%       - Домашний диск\n"
             << "  %HOMEPATH%        - Путь к домашней директории\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> ПРОГРАММЫ И ДАННЫЕ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %PROGRAMFILES%         - Директория Program Files\n"
             << "  %PROGRAMFILES(X86)%    - Директория Program Files (x86)\n"
             << "  %PROGRAMDATA%          - Общие данные программ\n"
             << "  %COMMONPROGRAMFILES%   - Общие файлы программ\n"
             << "  %APPDATA%              - Данные приложений\n"
             << "  %LOCALAPPDATA%         - Локальные данные приложений\n"
             << "  %PUBLIC%               - Общая папка\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> ВРЕМЕННЫЕ ФАЙЛЫ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %TEMP%            - Временные файлы пользователя\n"
             << "  %TMP%             - Альтернативная временная директория\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> СЕТЬ И ПУТИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %PATH%          - Пути поиска исполняемых файлов\n";
        cout << "  %PATHEXT%       - Расширения исполняемых файлов\n";
        cout << "  %COMSPEC%       - Командная оболочка\n";
        cout << "  %ONEDRIVE%      - Директория OneDrive (если есть)\n";
        cout << "  %HOMESHARE%     - Сетевой домашний каталог\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> РАЗНОЕ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  %NUMBER_OF_PROCESSORS%   - Количество процессоров\n";
        cout << "  %PROCESSOR_LEVEL%        - Уровень процессора\n";
        cout << "  %PROCESSOR_IDENTIFIER%   - Идентификатор процессора\n";
        cout << "  %PROCESSOR_REVISION%     - Ревизия процессора\n";
        ConsoleColor::GetInstance().yellow();
        cout << "\n> Подсказка: переменные работают в командах cd и ls\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandPWD() {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("pwd");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    filesystem::path current_path = filesystem::current_path();
    string current_dir = current_path.string();

    cout << "Current directory: ";
    ConsoleColor::GetInstance().yellow();
    cout << current_dir << "\n\n";
    ConsoleColor::GetInstance().ResetColor();
}

void CommandEXIT() {
    auto messages = LoadingMessages("exit");
    LoadingEffect(messages);
}

void CommandMODE(ProgramMode CurrentMode) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("mode");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    cout << "Current mode: ";
    switch (CurrentMode) {
    case ProgramMode::PRIMARY_MODE:
        ConsoleColor::GetInstance().yellow();
        cout << "PRIMARY_MODE";
        ConsoleColor::GetInstance().ResetColor();
        break;
    case ProgramMode::FS_MODE:
        ConsoleColor::GetInstance().yellow();
        cout << "FS_MODE";
        ConsoleColor::GetInstance().ResetColor();
        break;
    }
    cout << "\n\n";
}

void CommandCLEAR() {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("clear");
    LoadingEffect(messages);

    ConsoleColor::GetInstance().ResetColor();
    ClearConsole();
}

void CommandHELP(ProgramMode CurrentMode) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("help");
    LoadingEffect(messages);

    ConsoleColor::GetInstance().ResetColor();

    cout << "    --------------------\n"
         << "     Available commands\n"
         << "    --------------------\n";
    switch (CurrentMode) {
    case ProgramMode::PRIMARY_MODE:
        ConsoleColor::GetInstance().yellow();
        cout << "        PRIMARY MODE\n\n"
             << "> БАЗОВЫЕ ОПЕРАЦИИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  wwfs      - Перейти в режим FS_MODE\n"
             << "  stop      - Завершить работу программы\n"
             << "  clear     - Очистить консоль программы\n"
             << "  mode      - Показать текущий режим работы\n"
             << "  help      - Справка по доступным командам\n"
             << "Итого: 6 базовых операций.\n";
        break;
    case ProgramMode::FS_MODE:
        ConsoleColor::GetInstance().yellow();
        cout << "      FILE SYSTEM MODE\n\n"
             << "> ФАЙЛОВЫЕ ОПЕРАЦИИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  rd -f         - Прочитать файл\n"
             << "  wt -f         - Записать в файл\n"
             << "  crt -f        - Создать файл\n"
             << "  del -f        - Удалить файл\n"
             << "  clr -f        - Очистить файл\n"
             << "  info -f       - Получить данные о файле\n"
             << "  mv -f         - Переместить файл\n"
             << "  rn -f         - Переименовать файл\n"
             << "  cp -f         - Копировать файл\n"
             << "  set att -f    - Установить аттрибут\n"
             << "  set perm -f   - Установить разрешение\n"
             << "Итого: 11 файловых операций.\n\n";

        ConsoleColor::GetInstance().yellow();
        cout << "> ОПЕРАЦИИ С ПАПКАМИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  mkdir         - Создать папку\n"
             << "  rmdir         - Удалить папку\n"
             << "  info -d       - Получить информацию о папке\n"
             << "  mv -d         - Переместить папку\n"
             << "  rn -d         - Переименовать папку\n"
             << "  cp -d         - Копировать папку\n"
             << "  set att -d    - Установить аттрибут\n"
             << "  set perm -d   - Установить разрешение\n"
             << "Итого: 8 операций с папками.\n\n";

        ConsoleColor::GetInstance().yellow();
        cout << "> СПЕЦИАЛЬНЫЕ ОПЕРАЦИИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  ls [path]      - Показать содержание директории\n"
             << "  cd [path]      - Поменять текущую директорию\n"
             << "  echo %VAR%     - Показать переменные окружения\n"
             << "  pwd            - Показать текущую директорию\n"
             << "Итого: 4 специальные операции.\n\n";
        
        ConsoleColor::GetInstance().yellow();
        cout << "> БАЗОВЫЕ ОПЕРАЦИИ:\n";
        ConsoleColor::GetInstance().ResetColor();
        cout << "  stop      - Завершить работу программы\n"
             << "  exit      - Вернуться в основной режим\n"
             << "  clear     - Очистить консоль программы\n"
             << "  mode      - Показать текущий режим работы\n"
             << "  help      - Справка по доступным командам\n"
             << "Итого: 5 базовых операций.\n";
        break;
    }
    cout << "\n    --------------------\n\n";
}

void CommandSET_FA(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("set att -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = name;

    if (input == "set att -f") {
        name = "";
    }
    else if (input.size() > 11 && input.substr(0,11) == "set att -f ") {
        name = input.substr(11);
    }
    else if (input.find("set att -f ") == 0) {
        size_t pos = input.find("set att -f ");
        if (pos != string::npos) {
            name = input.substr(pos + 11);
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
        }
        else {
            name = input;
        }
    }
    else {
        name = input;
    }
    SetConsoleCP(866);

    try {
        string filename, attribute;

        ParseSetAttributeInput(name, filename, attribute);

        CheckPreOpenErrors_SetAttribute(filename);

        CheckSetAttributeProcessErrors(filename, attribute);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << "Аттрибут успешно установлен.\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
             << "Код ошибки: " << ex.code() << ".\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandSET_DA(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("set att -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = name;

    if (input == "set att -d") {
        name = "";
    }
    else if (input.size() > 11 && input.substr(0, 11) == "set att -d ") {
        name = input.substr(11);
    }
    else if (input.find("set att -d ") == 0) {
        size_t pos = input.find("set att -d ");
        if (pos != string::npos) {
            name = input.substr(pos + 11);
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
        }
        else {
            name = input;
        }
    }
    else {
        name = input;
    }
    SetConsoleCP(866);

    try {
        string dirname, attribute;

        ParseSetAttributeInput_D(name, dirname, attribute);

        CheckPreOpenErrors_SetAttribute_D(dirname);

        CheckSetAttributeProcessErrors_D(dirname, attribute);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << "Аттрибут успешно установлен.\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
             << "Код ошибки: " << ex.code() << ".\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandSET_FP(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("set perm -f");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = name;

    if (input == "set perm -f") {
        name = "";
    }
    else if (input.size() > 12 && input.substr(0, 12) == "set perm -f ") {
        name = input.substr(12);
    }
    else if (input.find("set perm -f ") == 0) {
        size_t pos = input.find("set perm -f ");
        if (pos != string::npos) {
            name = input.substr(pos + 12);
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
        }
        else {
            name = input;
        }
    }
    else {
        name = input;
    }
    SetConsoleCP(866);

    try {
        string filename, permission;

        ParseSetPermissionInput(name, filename, permission);

        CheckPreOpenErrors_SetPermission(filename);

        CheckSetPermissionProcessErrors(filename, permission);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << "Разрешение успешно установлено.\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
             << "Код ошибки: " << ex.code() << ".\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}

void CommandSET_DP(string& name) {
    ConsoleColor::GetInstance().yellow();
    auto messages = LoadingMessages("set perm -d");
    LoadingEffect(messages);
    ConsoleColor::GetInstance().ResetColor();

    SetConsoleCP(1251);
    string input = name;

    if (input == "set perm -d") {
        name = "";
    }
    else if (input.size() > 12 && input.substr(0, 12) == "set perm -d ") {
        name = input.substr(12);
    }
    else if (input.find("set perm -d ") == 0) {
        size_t pos = input.find("set perm -d ");
        if (pos != string::npos) {
            name = input.substr(pos + 12);
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
        }
        else {
            name = input;
        }
    }
    else {
        name = input;
    }
    SetConsoleCP(866);

    try {
        string dirname, permission;

        ParseSetPermissionInput_D(name, dirname, permission);

        CheckPreOpenErrors_SetPermission_D(dirname);

        CheckSetPermissionProcessErrors_D(dirname, permission);

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << "Разрешение успешно установлено.\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const Exception& ex) {
        ConsoleColor::GetInstance().red();
        cout << ex.what() << "\n"
             << "Код ошибки: " << ex.code() << ".\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
}