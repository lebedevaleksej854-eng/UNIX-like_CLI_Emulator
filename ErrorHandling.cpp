#define WIN32_LEAN_AND_MEAN

#include "ErrorHandling.h"
#include "UserInterface.h"
#include "ConsoleColor.h"

#include <system_error>
#include <windows.h>
#include <iostream>
#include <cerrno>

using namespace std;

// Функция для явной проверки аттрибутов файла
bool CheckFileReadOnly(const string& filename) {
    DWORD attributes = GetFileAttributesA(filename.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        return false; // Файл не существует или ошибка доступа
    }
    return (attributes & FILE_ATTRIBUTE_READONLY);
}

// Функция для проверки прав доступа к файлу
bool CheckFileAccessRights(const string& filename, DWORD desiredAccess) {
    HANDLE hFile = CreateFileA(
        filename.c_str(),
        desiredAccess,
        FILE_SHARE_READ,  // Минимальные права для проверки
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        return true;
    }
    DWORD error = GetLastError();
    return false;  // Нет доступа или другая ошибка
}

// Функция для проверки прав доступа к папке
bool CheckDirectoryAccess(const string& dirPath, DWORD desiredAccess) {
    HANDLE hDir = CreateFileA(
        dirPath.c_str(),
        desiredAccess,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,  // Важно для директорий!
        NULL
    );
    if (hDir == INVALID_HANDLE_VALUE) {
        return false;
    }
    CloseHandle(hDir);
    return true;
}

// Реализация исключений для операции "чтение"
void CheckPreOpenErrors_Read(string& name) {
    filesystem::path path(name);

    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void CheckOpenProcessErrors_Read(const string& name, ifstream& file) {
    try {
        uintmax_t size = filesystem::file_size(name);
        if (size > 100 * 1024 * 1024) { // 100MB лимит
            throw Exception(ErrorBase_BasicErrors::Error_8(), 8);
        }
    }
    catch (const filesystem::filesystem_error&) {
        // Продолжаем пытаться открыть файл, даже если не удалось получить размер
    }
    file.open(name);

    if (!file.is_open()) {
        switch (errno) {
        case EACCES:
            throw Exception(ErrorBase_BasicErrors::Error_10(), 10);
        case EIO:
            throw Exception(ErrorBase_SystemErrors::Error_15(), 15);
        default:
            throw Exception(ErrorBase_SystemErrors::Error_15(), 15);
        }
    }
}
void CheckReadProcessErrors(const string& name, ifstream& file) {
    char ch;
    while (file.get(ch)) {
        if (file.bad()) {
            throw Exception(ErrorBase_SystemErrors::Error_16(), 16);
        }
        cout << ch;
    }
}

// Реализация исключений для операции "запись"
void CheckPreOpenErrors_Write(string& name) {
    filesystem::path path(name);

    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void CheckOpenProcessErrors_Write(const string& name, ofstream& file) {
    try {
        uintmax_t size = filesystem::file_size(name);
        if (size > 100 * 1024 * 1024) { // 100MB лимит
            throw Exception(ErrorBase_BasicErrors::Error_8(), 8);
        }
    }
    catch (const filesystem::filesystem_error&) {
        // Продолжаем пытаться открыть файл, даже если не удалось получить размер
    }

    file.open(name, ofstream::app);

    if (!file.is_open()) {
        switch (errno) {
        case EACCES:
            throw Exception(ErrorBase_BasicErrors::Error_11(), 11);
        case EIO:
            throw Exception(ErrorBase_SystemErrors::Error_15(), 15);
        default:
            throw Exception(ErrorBase_SystemErrors::Error_15(), 15);
        }
    }
}
void CheckWriteProcessErrors(ofstream& file) {
    SetConsoleCP(1251);

    string input;
    input = GetUserInput();

    SetConsoleCP(866);

    file << input;
    file << "\n";

    if (file.fail() || file.bad()) {
        throw Exception(ErrorBase_SystemErrors::Error_17(), 17);
    }
    file.flush();
    if (file.fail()) {
        throw Exception(ErrorBase_SystemErrors::Error_17(), 17);
    }
}

// Реализация исключений для операции "создание"
void CheckPreOpenErrors_Create(string& name) {
    filesystem::path path(name);                
    
    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (filesystem::exists(name) && filesystem::is_regular_file(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_6(), 6);
    }
}
void CheckCreationProcessErrors(const string& name, ofstream& file) {
    file.open(name, ios::out);
    if (!file.is_open()) {
        switch (errno) {
        case EIO:
            throw Exception(ErrorBase_SystemErrors::Error_18(), 18);
        default:
            throw Exception(ErrorBase_SystemErrors::Error_18(), 18);
        }
    }
}

// Реализация исключений для операции "удаление"
void CheckPreOpenErrors_Delete(string& name) {
    filesystem::path path(name);

    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void CheckDeleteProcessErrors(string& name) {
    // ЯВНАЯ проверка перед удалением
    if (CheckFileReadOnly(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_9(), 9);
    }
    // Проверка прав DELETE на файл
    else if (!CheckFileAccessRights(name, DELETE)) {
        throw Exception(ErrorBase_BasicErrors::Error_9(), 9);
    }
    error_code ec;
    if (!filesystem::remove(name, ec)) {
        if (ec == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_9(), 9); // Ошибка. Отсутствуют права на удаление файла
        }
        else if (ec == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_19(), 19);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_19(), 19);
        }
    }
}

// Реализация исключений для операции "очистка"
void CheckPreOpenErrors_Clear(string& name) {
    filesystem::path path(name);

    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void CheckClearProcessErrors(const string& name, ofstream& file) {
    file.open(name, ios::trunc);

    if (!file.is_open()) {
        switch (errno) {
        case EACCES:
            throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
        case EIO:
            throw Exception(ErrorBase_SystemErrors::Error_23(), 23);
        default:
            throw Exception(ErrorBase_SystemErrors::Error_23(), 23);
        }
    }
}

// Реализация исключений, а также сторонних функций, для операции "получение"
void CheckPreOpenErrors_Info(string& name) {
    filesystem::path path(name);

    if (name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
string FormatFileSize(uintmax_t size) {
    const char* units[] = { "Б", "КБ", "МБ", "ГБ", "ТБ" };
    int unitIndex = 0;
    double formattedSize = static_cast<double>(size);

    while (formattedSize >= 1024.0 && unitIndex < 4) {
        formattedSize /= 1024.0;
        unitIndex++;
    }
    stringstream ss;
    ss << fixed << setprecision(2) << formattedSize << " " << units[unitIndex];
    return ss.str();
}
string FormatTime(const filesystem::file_time_type& fileTime) {
    auto systemTime = chrono::clock_cast<chrono::system_clock>(fileTime);
    auto timeT = chrono::system_clock::to_time_t(systemTime);

    stringstream ss;
    ss << put_time(localtime(&timeT), "%d.%m.%Y %H:%M:%S");
    return ss.str();
}
string FileType(const filesystem::path& path) {
    try {
        if (filesystem::is_regular_file(path)) {
            return "Обычный файл";
        }
        else {
            return "Неизвестный тип";
        }
    }
    catch (...) {
        return "Тип не определен";
    }
}
void DisplayFileInfo(const string& name) {
    try {
        filesystem::path path(name);
        auto AbsolutePath = filesystem::absolute(path);
        filesystem::path CurrentPath = filesystem::current_path();

        filesystem::path RelativePath;
        try {
            // Вычисляем относительный путь от текущей директории к файлу
            RelativePath = filesystem::relative(AbsolutePath, CurrentPath);
        }
        catch (...) {
            // Если не удается вычислить путь, то используем исходный ввод
            RelativePath = name;
        }
        // Если файл находится в текущей директории, добавляем "current directory\"
        if (RelativePath.string() == path.filename().string() || RelativePath.string() == ".") {
            RelativePath = "Current_Directory\\" + path.filename().string();
        }
        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << "     ИНФОРМАЦИЯ О ФАЙЛЕ\n"
             << "    --------------------\n";
        ConsoleColor::GetInstance().ResetColor();

        cout << "Имя файла: " << path.filename().string() << "\n"
             << "Тип файла: " << FileType(path) << "\n"
             << "Размер файла: " << FormatFileSize(filesystem::file_size(path)) << "\n"
             << "Расширение файла: " << path.extension().string() << "\n";
        cout << "\n"
             << "Полный путь к файлу: " << filesystem::absolute(path).string() << "\n"
             << "Относительный путь к файлу: " << RelativePath.string() << "\n"
             << "Корневой путь в файлу: " << AbsolutePath.root_path().string() << "\n";
        cout << "\n"
             << "Дата последнего изменения: " << FormatTime(filesystem::last_write_time(path)) << ".\n";

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
             << " ИНФОРМАЦИЯ ПОЛУЧЕНА УСПЕШНО\n"
             << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const filesystem::filesystem_error&) {
        throw Exception(ErrorBase_SystemErrors::Error_20(), 20);
    }
}

// Реализация исключений для операции "перемещение файла"
void CheckPreOpenErrors_MOVE(const string& source_path, const string& destination_path) {
    filesystem::path src_path(source_path);
    filesystem::path dest_path(destination_path);

    // Проверка исходного файла
    if (source_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (source_path.size() < 4 || source_path.substr(source_path.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
    else if (!src_path.parent_path().empty() && !filesystem::exists(src_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (filesystem::exists(source_path) && filesystem::is_directory(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    // Проверка пути назначения
    if (destination_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (!dest_path.parent_path().empty() && !filesystem::exists(dest_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (filesystem::exists(destination_path) && filesystem::is_regular_file(destination_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_6(), 6); // Файл уже существует
    }
    else if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
        // Если назначение - директория, создаем полный путь с именем файла
        filesystem::path dest_dir(destination_path);
        filesystem::path new_dest = dest_dir / src_path.filename();

        // Проверяем, существует ли файл с таким именем в целевой директории
        if (filesystem::exists(new_dest) && filesystem::is_regular_file(new_dest)) {
            throw Exception(ErrorBase_BasicErrors::Error_6(), 6); // Файл уже существует
        }
    }
}
void CheckMoveProcessErrors(const string& source_path, const string& destination_path) {
    // ЯВНАЯ проверка перед перемещением
    if (CheckFileReadOnly(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_14(), 14);
    }
    // Проверка прав на исходный файл (DELETE + READ)
    else if (!CheckFileAccessRights(source_path, DELETE | GENERIC_READ)) {
        throw Exception(ErrorBase_BasicErrors::Error_14(), 14);
    }
    try {
        filesystem::path src_path(source_path);
        filesystem::path dest_path(destination_path);

        // Если назначение - директория, добавляем имя исходного файла
        if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
            dest_path = filesystem::path(destination_path) / src_path.filename();
        }
        // Создаем родительские директории, если их нет
        if (dest_path.has_parent_path()) {
            filesystem::create_directories(dest_path.parent_path());
        }
        // Выполняем перемещение
        filesystem::rename(source_path, dest_path);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_14(), 14);
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_25(), 25);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_25(), 25);
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_25(), 25);
    }
}

// Реализация исключений для операции "переименование"
void CheckPreOpenErrors_RENAME(const string& old_name, const string& new_name) {
    filesystem::path old_path(old_name);
    filesystem::path new_path(new_name);

    // Проверка исходного файла
    if (old_name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (old_name.size() < 4 || old_name.substr(old_name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(old_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
    else if (!old_path.parent_path().empty() && !filesystem::exists(old_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (filesystem::exists(old_name) && filesystem::is_directory(old_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    // Проверка нового имени
    if (new_name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (new_name.size() < 4 || new_name.substr(new_name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!new_path.parent_path().empty() && !filesystem::exists(new_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (filesystem::exists(new_name) && filesystem::is_regular_file(new_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_6(), 6);
    }
    else if (filesystem::exists(new_name) && filesystem::is_directory(new_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
}
void CheckRenameProcessErrors(const string& old_name, const string& new_name) {
    // ЯВНАЯ проверка перед перемещением
    if (CheckFileReadOnly(old_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
    }
    // Проверка прав на исходный файл
    else if (!CheckFileAccessRights(old_name, DELETE | GENERIC_READ)) {
        throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
    }
    try {
        // Создаем родительские директории для нового пути, если их нет
        filesystem::path new_path(new_name);
        if (new_path.has_parent_path()) {
            filesystem::create_directories(new_path.parent_path());
        }
        // Выполняем переименование
        filesystem::rename(old_name, new_name);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_26(), 26);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_26(), 26);
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_26(), 26);
    }
}

// Реализация исключений для операции "копирование"
void CheckPreOpenErrors_CP(const string& source_path, const string& destination_path) {
    filesystem::path src_path(source_path);
    filesystem::path dest_path(destination_path);

    if (source_path.empty() || destination_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_1(), 1);
    }
    else if (filesystem::exists(source_path) && filesystem::is_directory(destination_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!src_path.parent_path().empty() && !filesystem::exists(src_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (!dest_path.parent_path().empty() && !filesystem::exists(dest_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (source_path.size() < 4 || source_path.substr(source_path.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (destination_path.size() < 4 || destination_path.substr(destination_path.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
    else if (filesystem::exists(destination_path) && filesystem::is_regular_file(destination_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_6(), 6);
    }
}

void CheckCopyProcessErrors(const string& source_path, const string& destination_path) {
    // Проверка прав на чтение исходного файла
    if (!CheckFileAccessRights(source_path, GENERIC_READ)) {
        throw Exception(ErrorBase_BasicErrors::Error_13(), 13);
    }
    try {
        filesystem::path path(destination_path);
        if (path.has_parent_path()) {
            filesystem::create_directories(path.parent_path());
        }
        filesystem::copy_file(source_path, destination_path, filesystem::copy_options::overwrite_existing);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_13(), 13);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_24(), 24);
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_24(), 24);
    }
}

// Реализация исключений для операции "создание директории"
void CheckPreOpenErrors_MKDIR(const string& dir_path) {
    filesystem::path path(dir_path);

    if (dir_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29);
    }
    else if (filesystem::exists(dir_path) && filesystem::is_directory(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_30(), 30);
    }
    else if (filesystem::exists(dir_path) && filesystem::is_regular_file(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void CheckMkdirProcessErrors(const string& dir_path) {
    try {
        // Создаем директорию (включая все родительские директории)
        bool created = filesystem::create_directories(dir_path);

        if (!created && filesystem::exists(dir_path)) {
            // Если директория уже существует (редкий случай)
            throw Exception(ErrorBase_BasicErrors::Error_30(), 30);
        }
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_35(), 35);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_35(), 35);
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_35(), 35);
    }
}

// Реализация исключений для операции "удаление директории"
void CheckPreOpenErrors_RMDIR(const string& dir_path) {
    filesystem::path path(dir_path);

    if (dir_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27);
    }
    else if (!filesystem::exists(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29);
    }
    else if (filesystem::exists(dir_path) && filesystem::is_regular_file(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void CheckRmdirProcessErrors(const string& dir_path) {
    // ЯВНАЯ проверка перед перемещением
    if (!CheckDirectoryAccess(dir_path, DELETE)) {
        throw Exception(ErrorBase_BasicErrors::Error_31(), 31);
    }
    try {
        // Проверяем, не пуста ли директория
        if (!filesystem::is_empty(dir_path)) {
            // Для простоты удаляем рекурсивно
            filesystem::remove_all(dir_path);
        }
        else {
            filesystem::remove(dir_path);
        }
        // Проверяем, удалилась ли директория
        if (filesystem::exists(dir_path)) {
            throw Exception(ErrorBase_BasicErrors::Error_31(), 31);
        }
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_31(), 31);
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_36(), 36);
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_36(), 36);
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_36(), 36);
    }
}

// Реализация исключений для операции "получение инф. о папке"
void CheckPreOpenErrors_INFO_D(const string& dir_path) {
    filesystem::path path(dir_path);

    if (dir_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27);
    }
    else if (!filesystem::exists(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29);
    }
    else if (filesystem::exists(dir_path) && filesystem::is_regular_file(dir_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void DisplayDirectoryInfo(const string& dir_path) {
    try {
        filesystem::path path(dir_path);
        auto AbsolutePath = filesystem::absolute(path);
        filesystem::path CurrentPath = filesystem::current_path();

        filesystem::path RelativePath;
        try {
            // Вычисляем относительный путь от текущей директории к файлу
            RelativePath = filesystem::relative(AbsolutePath, CurrentPath);
        }
        catch (...) {
            // Если не удается вычислить путь, то используем исходный ввод
            RelativePath = dir_path;
        }
        // Если файл находится в текущей директории, добавляем "current directory\"
        if (RelativePath.string() == path.filename().string() || RelativePath.string() == ".") {
            RelativePath = "Current_Directory\\" + path.filename().string();
        }
        // Собираем статистику о папке
        int file_count = 0;
        int dir_count = 0;
        uintmax_t total_size = 0;

        // Рекурсивно обходим директорию для подсчета
        for (const auto& entry : filesystem::recursive_directory_iterator(dir_path,
            filesystem::directory_options::skip_permission_denied)) {
            try {
                if (filesystem::is_regular_file(entry.status())) {
                    file_count++;
                    total_size += filesystem::file_size(entry.path());
                }
                else if (filesystem::is_directory(entry.status())) {
                    dir_count++;
                }
            }
            catch (...) {
                // Пропускаем файлы, к которым нет доступа
                continue;
            }
        }
        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << "     ИНФОРМАЦИЯ О ПАПКЕ\n"
            << "    --------------------\n";
        ConsoleColor::GetInstance().ResetColor();

        cout << "Имя папки: " << path.filename().string() << ".\n"
             << "Тип: директория.\n"
             << "Количество файлов: " << file_count << ".\n"
             << "Количество подпапок: " << dir_count << ".\n";
        cout << "\n"
             << "Полный путь к папке: " << AbsolutePath.string() << ".\n"
             << "Относительный путь: " << RelativePath.string() << ".\n"
             << "Корневой путь к папке: " << AbsolutePath.root_path().string() << ".\n";
        cout << "\n"
             << "Дата последнего изменения: " << FormatTime(filesystem::last_write_time(path)) << ".\n";

        ConsoleColor::GetInstance().green();
        cout << "    --------------------\n"
            << " ИНФОРМАЦИЯ ПОЛУЧЕНА УСПЕШНО\n"
            << "    --------------------\n\n";
        ConsoleColor::GetInstance().ResetColor();
    }
    catch (const filesystem::filesystem_error&) {
        throw Exception(ErrorBase_SystemErrors::Error_37(), 37); // новая ошибка
    }
}

// Реализация исключений для операции "перемещение папки"
void CheckPreOpenErrors_MOVE_D(const string& source_path, const string& destination_path) {
    filesystem::path src_path(source_path);
    filesystem::path dest_path(destination_path);

    // Проверка исходной папки
    if (source_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!filesystem::exists(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28); // Ошибка. Указанная папка не существует
    }
    else if (!src_path.parent_path().empty() && !filesystem::exists(src_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    else if (filesystem::exists(source_path) && filesystem::is_regular_file(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
    }
    // Проверка пути назначения
    if (destination_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!dest_path.parent_path().empty() && !filesystem::exists(dest_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    // Проверка на существование папки в месте назначения
    filesystem::path final_dest = dest_path;

    // Если назначение - существующая директория, добавляем имя исходной папки
    if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
        final_dest = filesystem::path(destination_path) / src_path.filename();
    }
    // Проверяем, существует ли папка с таким именем в целевом месте
    if (filesystem::exists(final_dest)) {
        if (filesystem::is_directory(final_dest)) {
            throw Exception(ErrorBase_BasicErrors::Error_30(), 30); // Ошибка. Папка с таким названием уже существует
        }
        else {
            throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
        }
    }
}
void CheckMoveProcessErrors_D(const string& source_path, const string& destination_path) {
    // ЯВНАЯ проверка перед перемещением
    if (!CheckDirectoryAccess(source_path, DELETE | READ_CONTROL)) {
        throw Exception(ErrorBase_BasicErrors::Error_32(), 32);
    }
    try {
        filesystem::path src_path(source_path);
        filesystem::path dest_path(destination_path);

        // Определяем конечный путь назначения
        filesystem::path final_dest = dest_path;

        // Если назначение - существующая директория, добавляем имя исходной папки
        if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
            final_dest = filesystem::path(destination_path) / src_path.filename();
        }
        // Создаем родительские директории, если их нет
        if (final_dest.has_parent_path()) {
            filesystem::create_directories(final_dest.parent_path());
        }
        // Выполняем перемещение папки
        filesystem::rename(source_path, final_dest);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_32(), 32); // Ошибка. Отсутствуют права на перемещение папки
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_38(), 38); // Критическая ошибка перемещения
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_38(), 38); // Критическая ошибка перемещения
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_38(), 38); // Критическая ошибка перемещения
    }
}

// Реализация исключений для операции "переименование папки"
void CheckPreOpenErrors_RENAME_D(const string& old_name, const string& new_name) {
    filesystem::path old_path(old_name);
    filesystem::path new_path(new_name);

    // Проверка исходной папки
    if (old_name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!filesystem::exists(old_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28); // Ошибка. Указанная папка не существует
    }
    else if (!old_path.parent_path().empty() && !filesystem::exists(old_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    else if (filesystem::exists(old_name) && filesystem::is_regular_file(old_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
    }
    // Проверка нового имени
    if (new_name.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!new_path.parent_path().empty() && !filesystem::exists(new_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    else if (filesystem::exists(new_name) && filesystem::is_regular_file(new_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
    }
    else if (filesystem::exists(new_name) && filesystem::is_directory(new_name)) {
        throw Exception(ErrorBase_BasicErrors::Error_30(), 30); // Ошибка. Папка с таким названием уже существует
    }
}
void CheckRenameProcessErrors_D(const string& old_name, const string& new_name) {
    // ЯВНАЯ проверка перед перемещением
    if (!CheckDirectoryAccess(old_name, DELETE)) {
        throw Exception(ErrorBase_BasicErrors::Error_33(), 33);
    }
    try {
        // Создаем родительские директории для нового пути, если их нет
        filesystem::path new_path(new_name);
        if (new_path.has_parent_path()) {
            filesystem::create_directories(new_path.parent_path());
        }
        // Выполняем переименование папки
        filesystem::rename(old_name, new_name);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_33(), 33); // Ошибка. Отсутствуют права на изменения папки
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_39(), 39); // Критическая ошибка переименования
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_39(), 39); // Критическая ошибка переименования
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_39(), 39); // Критическая ошибка переименования
    }
}

// Реализация исключений для операции "копирование папки"
void CheckPreOpenErrors_CP_D(const string& source_path, const string& destination_path) {
    filesystem::path src_path(source_path);
    filesystem::path dest_path(destination_path);

    // Проверка исходной папки
    if (source_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!filesystem::exists(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28); // Ошибка. Указанная папка не существует
    }
    else if (!src_path.parent_path().empty() && !filesystem::exists(src_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    else if (filesystem::exists(source_path) && filesystem::is_regular_file(source_path)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
    }
    // Проверка пути назначения
    if (destination_path.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_27(), 27); // Ошибка. Неверное имя папки (пустое)
    }
    else if (!dest_path.parent_path().empty() && !filesystem::exists(dest_path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29); // Ошибка. Указанный путь не существует
    }
    // Проверка на существование папки в месте назначения
    filesystem::path final_dest = dest_path;

    // Если назначение - существующая директория, добавляем имя исходной папки
    if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
        final_dest = filesystem::path(destination_path) / src_path.filename();
    }
    // Проверяем, существует ли папка с таким именем в целевом месте
    if (filesystem::exists(final_dest)) {
        if (filesystem::is_directory(final_dest)) {
            throw Exception(ErrorBase_BasicErrors::Error_30(), 30); // Ошибка. Папка с таким названием уже существует
        }
        else {
            throw Exception(ErrorBase_BasicErrors::Error_7(), 7); // Ошибка. Указанный путь ведет к файлу
        }
    }
}
void CheckCopyProcessErrors_D(const string& source_path, const string& destination_path) {
    // ЯВНАЯ проверка перед перемещением
    if (!CheckDirectoryAccess(source_path, DELETE)) {
        throw Exception(ErrorBase_BasicErrors::Error_34(), 34);
    }
    try {
        filesystem::path src_path(source_path);
        filesystem::path dest_path(destination_path);

        // Определяем конечный путь назначения
        filesystem::path final_dest = dest_path;

        // Если назначение - существующая директория, добавляем имя исходной папки
        if (filesystem::exists(destination_path) && filesystem::is_directory(destination_path)) {
            final_dest = filesystem::path(destination_path) / src_path.filename();
        }
        // Создаем родительские директории, если их нет
        if (final_dest.has_parent_path()) {
            filesystem::create_directories(final_dest.parent_path());
        }
        // Выполняем рекурсивное копирование папки
        filesystem::copy(source_path, final_dest,
            filesystem::copy_options::recursive |
            filesystem::copy_options::overwrite_existing);
    }
    catch (const filesystem::filesystem_error& ex) {
        if (ex.code() == make_error_code(errc::permission_denied)) {
            throw Exception(ErrorBase_BasicErrors::Error_34(), 34); // Ошибка. Отсутствуют права на копирование папки
        }
        else if (ex.code() == make_error_code(errc::io_error)) {
            throw Exception(ErrorBase_SystemErrors::Error_40(), 40); // Критическая ошибка копирования
        }
        else {
            throw Exception(ErrorBase_SystemErrors::Error_40(), 40); // Критическая ошибка копирования
        }
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_40(), 40); // Критическая ошибка копирования
    }
}

// Реализация исключений для операций ls и cd
void CheckPreOpenErrors_LS(string& name) {
    if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (!filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void CheckPreOpenErrors_CD(string& name) {
    if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (!filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}

// Реализация исключений для операции "установка аттрибута" (set att -f)
void CheckPreOpenErrors_SetAttribute(string& name) {
    filesystem::path path(name);

    if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void ParseSetAttributeInput(const string& input, string& filename, string& attribute) {
    filename.clear();
    attribute.clear();

    if (input.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_44(), 44);
    }
    string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    if (trimmed.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_44(), 44);
    }
    // Проверяем, есть ли пробел (для разделения файла и атрибута)
    // Но сначала проверяем случай с кавычками
    bool has_quotes = (trimmed[0] == '"');

    if (!has_quotes) {
        // Без кавычек: ищем обычный пробел
        size_t space_pos = trimmed.find(' ');

        if (space_pos == string::npos) {
            // Нет пробела - одно слово
            string word_lower = trimmed;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);

            // Проверяем, является ли это известным атрибутом
            if (word_lower == "read_only" || word_lower == "readonly" ||
                word_lower == "hidden" || word_lower == "normal") {
                throw Exception(ErrorBase_BasicErrors::Error_43(), 43);
            }
            // Проверяем, заканчивается ли на .txt
            if (trimmed.size() >= 4 && trimmed.substr(trimmed.size() - 4) == ".txt") {
                throw Exception(ErrorBase_BasicErrors::Error_45(), 45);
            }
            // Все остальное - неверный формат
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
        }
    }
    // Разбираем строку
    istringstream iss(trimmed);

    // Читаем первую часть (может быть в кавычках или без)
    if (iss.peek() == '"') {
        char quote;
        iss >> quote; // Читаем открывающую кавычку
        getline(iss, filename, '"'); // Читаем до закрывающей кавычки

        // Проверка на пустые кавычки
        if (filename.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указан файл
        }
    }
    else {
        iss >> filename;

        if (filename.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46); // Неверный формат
        }
        // Проверяем, не является ли первое слово атрибутом
        string filename_lower = filename;
        transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), ::tolower);

        if (filename_lower == "read_only" || filename_lower == "readonly" ||
            filename_lower == "hidden" || filename_lower == "normal") {
            throw Exception(ErrorBase_BasicErrors::Error_43(), 43);
        }
    }
    // Читаем атрибут
    iss >> attribute;

    // Проверки
    if (filename.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указан файл
    }
    if (attribute.empty()) {
        // Специальная проверка для случая с кавычками
        // Если был путь в кавычках, но нет атрибута
        if (has_quotes) {
            throw Exception(ErrorBase_BasicErrors::Error_45(), 45); // Не указан атрибут
        }
        else {
            // Для случая без кавычек: проверяем, похоже ли имя файла на файл
            if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt") {
                throw Exception(ErrorBase_BasicErrors::Error_45(), 45);
            }
            else {
                throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
            }
        }
    }
    // Проверка атрибута
    string attr_lower = attribute;
    transform(attr_lower.begin(), attr_lower.end(), attr_lower.begin(), ::tolower);

    if (!(attr_lower == "read_only" || attr_lower == "readonly" ||
        attr_lower == "hidden" || attr_lower == "normal")) {
        throw Exception(ErrorBase_BasicErrors::Error_42(), 42); // Неизвестный аттрибут
    }
    // Проверяем, нет ли лишних слов
    string extra;
    if (iss >> extra) {
        throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
    }
}
void CheckSetAttributeProcessErrors(const string& name, const string& attribute) {
    try {
        DWORD current_attributes = GetFileAttributesA(name.c_str());
        if (current_attributes == INVALID_FILE_ATTRIBUTES) {
            throw Exception(ErrorBase_BasicErrors::Error_41(), 41);
        }
        DWORD new_attributes = current_attributes;

        // Определяем какой аттрибут установить
        string attr_lower = attribute;
        transform(attr_lower.begin(), attr_lower.end(), attr_lower.begin(), ::tolower);

        if (attr_lower == "read_only" || attr_lower == "readonly") {
            new_attributes |= FILE_ATTRIBUTE_READONLY;
        }
        else if (attr_lower == "hidden") {
            new_attributes |= FILE_ATTRIBUTE_HIDDEN;
        }
        else if (attr_lower == "normal") {
            new_attributes = FILE_ATTRIBUTE_NORMAL;
        }
        else {
            throw Exception(ErrorBase_BasicErrors::Error_42(), 42); // Неизвестный аттрибут
        }
        // Устанавливаем новые аттрибуты
        if (!SetFileAttributesA(name.c_str(), new_attributes)) {
            DWORD error = GetLastError();
            if (error == ERROR_ACCESS_DENIED) {
                throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
            }
            else {
                throw Exception(ErrorBase_SystemErrors::Error_47(), 47);
            }
        }
    }
    catch (const Exception&) {
        throw; // Перебрасываем уже обработанные исключения
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_47(), 47); // Критическая ошибка
    }
}

// Реализация исключений для операции "установка аттрибута" (set att -d)
void CheckPreOpenErrors_SetAttribute_D(string& name) {
    filesystem::path path(name);

    if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28);
    }
    else if (filesystem::exists(name) && filesystem::is_regular_file(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void ParseSetAttributeInput_D(const string& input, string& dirname, string& attribute) {
    dirname.clear();
    attribute.clear();

    if (input.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_44(), 44);
    }
    string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    if (trimmed.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_44(), 44);
    }
    // Проверяем, есть ли пробел (для разделения папки и атрибута)
    // Но сначала проверяем случай с кавычками
    bool has_quotes = (trimmed[0] == '"');

    if (!has_quotes) {
        // Без кавычек: ищем обычный пробел
        size_t space_pos = trimmed.find(' ');

        if (space_pos == string::npos) {
            // Нет пробела - одно слово
            string word_lower = trimmed;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);

            // Проверяем, является ли это известным атрибутом
            if (word_lower == "read_only" || word_lower == "readonly" ||
                word_lower == "hidden" || word_lower == "normal") {
                throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указана папка
            }
            // Для папок не проверяем .txt, проверяем другие признаки
            // Проверяем, содержит ли путь символы, характерные для папок
            if (trimmed.find('\\') != string::npos) {
                // Похоже на путь к папке без атрибута
                throw Exception(ErrorBase_BasicErrors::Error_45(), 45); // Не указан атрибут
            }
            else {
                string forbidden_chars = "\\/*?\"<>|";
                bool has_forbidden_char = false;
                bool has_valid_chars = false;

                for (char c : trimmed) {
                    if (forbidden_chars.find(c) != string::npos) {
                        has_forbidden_char = true;
                        break;
                    }
                    if (isalnum(c) || c == '_' || c == '-' || c == ' ' || c == '.') {
                        has_valid_chars = true;
                    }
                }
                if (has_forbidden_char) {
                    // Содержит запрещенные символы - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                // Проверяем, не пустая ли строка и не состоит ли только из точек
                if (trimmed.empty() || trimmed == "." || trimmed == "..") {
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                error_code ec;
                if (filesystem::exists(trimmed, ec) &&
                    filesystem::is_directory(trimmed, ec)) {
                    // Существующая папка без атрибута
                    throw Exception(ErrorBase_BasicErrors::Error_45(), 45);
                }
                else {
                    // Все остальное - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
            }
        }
    }
    // Разбираем строку
    istringstream iss(trimmed);

    // Читаем первую часть (может быть в кавычках или без)
    if (iss.peek() == '"') {
        char quote;
        iss >> quote; // Читаем открывающую кавычку
        getline(iss, dirname, '"'); // Читаем до закрывающей кавычки

        // Проверка на пустые кавычки
        if (dirname.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указана папка
        }
    }
    else {
        iss >> dirname;

        if (dirname.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46); // Неверный формат
        }
        // Проверяем, не является ли первое слово атрибутом
        string dirname_lower = dirname;
        transform(dirname_lower.begin(), dirname_lower.end(), dirname_lower.begin(), ::tolower);

        if (dirname_lower == "read_only" || dirname_lower == "readonly" ||
            dirname_lower == "hidden" || dirname_lower == "normal") {
            throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указана папка
        }
    }
    // Читаем атрибут
    iss >> attribute;

    // Проверки
    if (dirname.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_43(), 43); // Не указана папка
    }
    if (attribute.empty()) {
        // Специальная проверка для случая с кавычками
        // Если был путь в кавычках, но нет атрибута
        if (has_quotes) {
            throw Exception(ErrorBase_BasicErrors::Error_45(), 45); // Не указан атрибут
        }
        else {
            // Для случая без кавычек: проверяем, похоже ли имя папки на путь
            if (dirname.find('\\') != string::npos) {
                throw Exception(ErrorBase_BasicErrors::Error_45(), 45); // Не указан атрибут
            }
            else {
                string forbidden_chars = "\\/*?\"<>|";
                bool has_forbidden_char = false;
                bool has_valid_chars = false;

                for (char c : trimmed) {
                    if (forbidden_chars.find(c) != string::npos) {
                        has_forbidden_char = true;
                        break;
                    }
                    if (isalnum(c) || c == '_' || c == '-' || c == ' ' || c == '.') {
                        has_valid_chars = true;
                    }
                }
                if (has_forbidden_char) {
                    // Содержит запрещенные символы - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                // Проверяем, не пустая ли строка и не состоит ли только из точек
                if (trimmed.empty() || trimmed == "." || trimmed == "..") {
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                error_code ec;
                if (filesystem::exists(trimmed, ec) &&
                    filesystem::is_directory(trimmed, ec)) {
                    // Существующая папка без атрибута
                    throw Exception(ErrorBase_BasicErrors::Error_45(), 45);
                }
                else {
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46); // Неверный формат
                }
            }
        }
    }
    // Проверяем атрибут (те же атрибуты, что и для файлов)
    string attr_lower = attribute;
    transform(attr_lower.begin(), attr_lower.end(), attr_lower.begin(), ::tolower);

    if (!(attr_lower == "read_only" || attr_lower == "readonly" ||
        attr_lower == "hidden" || attr_lower == "normal")) {
        throw Exception(ErrorBase_BasicErrors::Error_42(), 42); // Неизвестный аттрибут
    }
    // Проверяем, нет ли лишних слов
    string extra;
    if (iss >> extra) {
        throw Exception(ErrorBase_BasicErrors::Error_46(), 46); // Неверный формат
    }
}
void CheckSetAttributeProcessErrors_D(const string& name, const string& attribute) {
    try {
        DWORD current_attributes = GetFileAttributesA(name.c_str());
        if (current_attributes == INVALID_FILE_ATTRIBUTES) {
            throw Exception(ErrorBase_BasicErrors::Error_41(), 41);
        }
        DWORD new_attributes = current_attributes;

        // Определяем какой аттрибут установить
        string attr_lower = attribute;
        transform(attr_lower.begin(), attr_lower.end(), attr_lower.begin(), ::tolower);

        if (attr_lower == "read_only" || attr_lower == "readonly") {
            new_attributes |= FILE_ATTRIBUTE_READONLY;
        }
        else if (attr_lower == "hidden") {
            new_attributes |= FILE_ATTRIBUTE_HIDDEN;
        }
        else if (attr_lower == "normal") {
            new_attributes = FILE_ATTRIBUTE_DIRECTORY;
        }
        else {
            throw Exception(ErrorBase_BasicErrors::Error_42(), 42); // Неизвестный аттрибут
        }
        // Устанавливаем новые аттрибуты
        if (!SetFileAttributesA(name.c_str(), new_attributes)) {
            DWORD error = GetLastError();
            if (error == ERROR_ACCESS_DENIED) {
                throw Exception(ErrorBase_BasicErrors::Error_12(), 12);
            }
            else {
                throw Exception(ErrorBase_SystemErrors::Error_47(), 47);
            }
        }
    }
    catch (const Exception&) {
        throw; // Перебрасываем уже обработанные исключения
    }
    catch (...) {
        throw Exception(ErrorBase_SystemErrors::Error_47(), 47); // Критическая ошибка
    }
}

// Реализация исключений для операции "Установка разрешений (прав)" (set perm -f)
void CheckPreOpenErrors_SetPermission(string& name) {
    filesystem::path path(name);

    if (filesystem::exists(name) && filesystem::is_directory(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_5(), 5);
    }
    else if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_4(), 4);
    }
    else if (name.size() < 4 || name.substr(name.size() - 4) != ".txt") {
        throw Exception(ErrorBase_BasicErrors::Error_2(), 2);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_3(), 3);
    }
}
void ParseSetPermissionInput(const string& input, string& filename, string& permission) {
    filename.clear();
    permission.clear();

    if (input.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_51(), 51); // Не указаны файл и разрешение
    }
    string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    if (trimmed.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_51(), 51);
    }
    bool has_quotes = (trimmed[0] == '"');

    if (!has_quotes) {
        size_t space_pos = trimmed.find(' ');

        if (space_pos == string::npos) {
            // Нет пробела - одно слово
            string word_lower = trimmed;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);

            // Проверяем, является ли это известным разрешением
            if (word_lower == "read" || word_lower == "write" || word_lower == "full" ||
                word_lower == "deny" || word_lower == "normal") {
                throw Exception(ErrorBase_BasicErrors::Error_50(), 50); // Не указан файл
            }
            // Проверяем, заканчивается ли на .txt
            if (trimmed.size() >= 4 && trimmed.substr(trimmed.size() - 4) == ".txt") {
                throw Exception(ErrorBase_BasicErrors::Error_52(), 52); // Не указано разрешение
            }
            // Все остальное - неверный формат
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
        }
    }
    // Разбираем два слова
    istringstream iss(trimmed);

    // Читаем первую часть (может быть в кавычках или без)
    if (iss.peek() == '"') {
        char quote;
        iss >> quote;
        getline(iss, filename, '"');

        if (filename.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_50(), 50);
        }
    }
    else {
        iss >> filename;

        if (filename.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
        }
        // Проверяем, не является ли первое слово разрешением
        string filename_lower = filename;
        transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), ::tolower);

        if (filename_lower == "read" || filename_lower == "write" || filename_lower == "full" ||
            filename_lower == "deny" || filename_lower == "normal") {
            throw Exception(ErrorBase_BasicErrors::Error_50(), 50);
        }
    }
    // Читаем разрешение
    iss >> permission;

    if (permission.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_52(), 52);
    }
    // Проверяем разрешение
    string perm_lower = permission;
    transform(perm_lower.begin(), perm_lower.end(), perm_lower.begin(), ::tolower);

    if (!(perm_lower == "read" || perm_lower == "write" || perm_lower == "full" ||
        perm_lower == "deny" || perm_lower == "normal")) {
        throw Exception(ErrorBase_BasicErrors::Error_49(), 49); // Неизвестное разрешение
    }
    // Проверяем, нет ли лишних слов
    string extra;
    if (iss >> extra) {
        throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
    }
}
void CheckSetPermissionProcessErrors(const string& name, const string& permission) {
    // Пока что операция работает как команда-заглушка, иммитируя процесс установки разрешения
}

// Реализация исключений для операции "Установка разрешений (прав)" (set perm -d)
void CheckPreOpenErrors_SetPermission_D(string& name) {
    filesystem::path path(name);

    if (!path.parent_path().empty() && !filesystem::exists(path.parent_path())) {
        throw Exception(ErrorBase_BasicErrors::Error_29(), 29);
    }
    else if (!filesystem::exists(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_28(), 28);
    }
    else if (filesystem::exists(name) && filesystem::is_regular_file(name)) {
        throw Exception(ErrorBase_BasicErrors::Error_7(), 7);
    }
}
void ParseSetPermissionInput_D(const string& input, string& dirname, string& permission) {
    dirname.clear();
    permission.clear();

    if (input.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_51(), 51); // Не указаны папка и разрешение
    }
    string trimmed = input;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    trimmed.erase(trimmed.find_last_not_of(" \t") + 1);

    if (trimmed.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_51(), 51);
    }
    bool has_quotes = (trimmed[0] == '"');

    if (!has_quotes) {
        size_t space_pos = trimmed.find(' ');

        if (space_pos == string::npos) {
            // Нет пробела - одно слово
            string word_lower = trimmed;
            transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);

            // Проверяем, является ли это известным разрешением
            if (word_lower == "read" || word_lower == "write" || word_lower == "full" ||
                word_lower == "deny" || word_lower == "normal") {
                throw Exception(ErrorBase_BasicErrors::Error_50(), 50); // Не указана папка
            }
            // Для папок не проверяем .txt, проверяем другие признаки
            if (trimmed.find('\\') != string::npos) {
                // Похоже на путь к папке без разрешения
                throw Exception(ErrorBase_BasicErrors::Error_52(), 52); // Не указано разрешение
            }
            else {
                string forbidden_chars = "\\/*?\"<>|";
                bool has_forbidden_char = false;
                bool has_valid_chars = false;

                for (char c : trimmed) {
                    if (forbidden_chars.find(c) != string::npos) {
                        has_forbidden_char = true;
                        break;
                    }
                    if (isalnum(c) || c == '_' || c == '-' || c == ' ' || c == '.') {
                        has_valid_chars = true;
                    }
                }
                if (has_forbidden_char) {
                    // Содержит запрещенные символы - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                // Проверяем, не пустая ли строка и не состоит ли только из точек
                if (trimmed.empty() || trimmed == "." || trimmed == "..") {
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                error_code ec;
                if (filesystem::exists(trimmed, ec) &&
                    filesystem::is_directory(trimmed, ec)) {
                    // Существующая папка без атрибута
                    throw Exception(ErrorBase_BasicErrors::Error_52(), 52);
                }
                else {
                    // Все остальное - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }

            }
        }
    }
    // Разбираем два слова
    istringstream iss(trimmed);

    // Читаем первую часть (может быть в кавычках или без)
    if (iss.peek() == '"') {
        char quote;
        iss >> quote;
        getline(iss, dirname, '"');

        if (dirname.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_50(), 50);
        }
    }
    else {
        iss >> dirname;

        if (dirname.empty()) {
            throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
        }
        // Проверяем, не является ли первое слово разрешением
        string dirname_lower = dirname;
        transform(dirname_lower.begin(), dirname_lower.end(), dirname_lower.begin(), ::tolower);

        if (dirname_lower == "read" || dirname_lower == "write" || dirname_lower == "full" ||
            dirname_lower == "deny" || dirname_lower == "normal") {
            throw Exception(ErrorBase_BasicErrors::Error_50(), 50);
        }
    }
    // Читаем разрешение
    iss >> permission;

    if (dirname.empty()) {
        throw Exception(ErrorBase_BasicErrors::Error_50(), 50);
    }
    if (permission.empty()) {
        // Специальная проверка для случая с кавычками
        // Если был путь в кавычках, но нет атрибута
        if (has_quotes) {
            throw Exception(ErrorBase_BasicErrors::Error_52(), 52);
        }
        else {
            // Для случая без кавычек: проверяем, похоже ли имя папки на путь
            if (dirname.find('\\') != string::npos) {
                throw Exception(ErrorBase_BasicErrors::Error_52(), 52);
            }
            else {
                string forbidden_chars = "\\/*?\"<>|";
                bool has_forbidden_char = false;
                bool has_valid_chars = false;

                for (char c : trimmed) {
                    if (forbidden_chars.find(c) != string::npos) {
                        has_forbidden_char = true;
                        break;
                    }
                    if (isalnum(c) || c == '_' || c == '-' || c == ' ' || c == '.') {
                        has_valid_chars = true;
                    }
                }
                if (has_forbidden_char) {
                    // Содержит запрещенные символы - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                // Проверяем, не пустая ли строка и не состоит ли только из точек
                if (trimmed.empty() || trimmed == "." || trimmed == "..") {
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
                error_code ec;
                if (filesystem::exists(trimmed, ec) &&
                    filesystem::is_directory(trimmed, ec)) {
                    // Существующая папка без атрибута
                    throw Exception(ErrorBase_BasicErrors::Error_52(), 52);
                }
                else {
                    // Все остальное - неверный формат
                    throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
                }
            }
        }
    }
    // Проверяем разрешение
    string perm_lower = permission;
    transform(perm_lower.begin(), perm_lower.end(), perm_lower.begin(), ::tolower);

    if (!(perm_lower == "read" || perm_lower == "write" || perm_lower == "full" ||
        perm_lower == "deny" || perm_lower == "normal")) {
        throw Exception(ErrorBase_BasicErrors::Error_49(), 49); // Неизвестное разрешение
    }
    // Проверяем, нет ли лишних слов
    string extra;
    if (iss >> extra) {
        throw Exception(ErrorBase_BasicErrors::Error_46(), 46);
    }
}
void CheckSetPermissionProcessErrors_D(const string& name, const string& permission) {
    // Пока что операция работает как команда-заглушка, иммитируя процесс установки разрешения
}