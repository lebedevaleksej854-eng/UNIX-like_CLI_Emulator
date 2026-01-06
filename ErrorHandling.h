#pragma once
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "Errors.h"

#include <filesystem>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <string>

using namespace std;

// Дополнительные функции для проверок
bool CheckFileReadOnly(const string& filename);
bool CheckFileAccessRights(const string& filename, DWORD desiredAccess);
bool CheckDirectoryAccess(const string& dirPath, DWORD desiredAccess);

// Операция "Чтение файла" (rd -f)
void CheckPreOpenErrors_Read(string& name);
void CheckOpenProcessErrors_Read(const string& name, ifstream& file);
void CheckReadProcessErrors(const string& name, ifstream& file);

// Операция "Запись в файл" (wt -f)
void CheckPreOpenErrors_Write(string& name);
void CheckOpenProcessErrors_Write(const string& name, ofstream& file);
void CheckWriteProcessErrors(ofstream& file);

// Операция "Создание файла" (crf -f)
void CheckPreOpenErrors_Create(string& name);
void CheckCreationProcessErrors(const string& name, ofstream& file);

// Операция "Удаление файла" (del -f)
void CheckPreOpenErrors_Delete(string& name);
void CheckDeleteProcessErrors(string& name);

// Операция "Очистка файла" (clr -f)
void CheckPreOpenErrors_Clear(string& name);
void CheckClearProcessErrors(const string& name, ofstream& file);

// Операция "Получение информации о файле" (info -f)
void CheckPreOpenErrors_Info(string& name);
void DisplayFileInfo(const string& name);

// Операция "Перемещение файла" (mv -f)
void CheckPreOpenErrors_MOVE(const string& source_path, const string& destination_path);
void CheckMoveProcessErrors(const string& source_path, const string& destination_path);

// Операция "Переименование файла" (rn -f)
void CheckPreOpenErrors_RENAME(const string& old_name, const string& new_name);
void CheckRenameProcessErrors(const string& old_name, const string& new_name);

// Операция "Копирование файла" (cp -f)
void CheckPreOpenErrors_CP(const string& source_path, const string& destination_path);
void CheckCopyProcessErrors(const string& source_path, const string& destination_path);

// Операция "Создание папки" (mkdir)
void CheckPreOpenErrors_MKDIR(const string& dir_path);
void CheckMkdirProcessErrors(const string& dir_path);

// Операция "Удаление папки" (rmdir)
void CheckPreOpenErrors_RMDIR(const string& dir_path);
void CheckRmdirProcessErrors(const string& dir_path);

// Операция "Получение инф. о папке" (info -d)
void CheckPreOpenErrors_INFO_D(const string& dir_path);
void DisplayDirectoryInfo(const string& dir_path);

// Операция "Перемещение папки" (mv -d)
void CheckPreOpenErrors_MOVE_D(const string& source_path, const string& destination_path);
void CheckMoveProcessErrors_D(const string& source_path, const string& destination_path);

// Операция "Переименование папки" (rn -d)
void CheckPreOpenErrors_RENAME_D(const string& old_name, const string& new_name);
void CheckRenameProcessErrors_D(const string& old_name, const string& new_name);

// Операция "Копирование папки" (cp -d)
void CheckPreOpenErrors_CP_D(const string& source_path, const string& destination_path);
void CheckCopyProcessErrors_D(const string& source_path, const string& destination_path);

// Операция "Установка аттрибута" (set att -f)
void CheckPreOpenErrors_SetAttribute(string& name);
void ParseSetAttributeInput(const string& input, string& filename, string& attribute);
void CheckSetAttributeProcessErrors(const string& name, const string& attribute);

// Операция "Установка аттрибута" (set att -d)
void CheckPreOpenErrors_SetAttribute_D(string& name);
void ParseSetAttributeInput_D(const string& input, string& dirname, string& attribute);
void CheckSetAttributeProcessErrors_D(const string& name, const string& attribute);

// Операция "Установка разрешений (прав)" (set perm -f)
void CheckPreOpenErrors_SetPermission(string& name);
void ParseSetPermissionInput(const string& input, string& filename, string& permission);
void CheckSetPermissionProcessErrors(const string& name, const string& permission);

// Операция "Установка разрешений (прав)" (set perm -d)
void CheckPreOpenErrors_SetPermission_D(string& name);
void ParseSetPermissionInput_D(const string& input, string& dirname, string& permission);
void CheckSetPermissionProcessErrors_D(const string& name, const string& permission);

// Операция "Чтение содержимого директории" (ls)
void CheckPreOpenErrors_LS(string& name);

// Операция "Смена текущей директории" (cd)
void CheckPreOpenErrors_CD(string& name);