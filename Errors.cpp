#include "Errors.h"

// ErrorBase_BasicErrors implementations
const char* ErrorBase_BasicErrors::Error_1() {
    return "    --------------------\n"
        "Ошибка. Неверное имя файла.\n"
        "Имя файла не может быть пустым.\n";
}
const char* ErrorBase_BasicErrors::Error_2() {
    return "    --------------------\n"
        "Ошибка. Неверное расширение файла.\n"
        "Ожидается расширение документа: txt.\n";
}
const char* ErrorBase_BasicErrors::Error_3() {
    return "    --------------------\n"
        "Ошибка. Указанный файл не существует.\n"
        "Файл с таким названием не был найден.\n";
}
const char* ErrorBase_BasicErrors::Error_4() {
    return "    --------------------\n"
        "Ошибка. Указанный путь не существует.\n"
        "Файл с указанным путем не был найден.\n";
}
const char* ErrorBase_BasicErrors::Error_5() {
    return "    --------------------\n"
        "Ошибка. Указанный путь ведет к директории.\n"
        "Ожидается файл, а не какая-либо директория.\n";
}
const char* ErrorBase_BasicErrors::Error_6() {
    return "    --------------------\n"
        "Ошибка. Файл с таким названием уже существует.\n"
        "Укажите другое название или удалите существующий файл.\n";
}
const char* ErrorBase_BasicErrors::Error_7() {
    return "    --------------------\n"
        "Ошибка. Указанный путь ведет к файлу.\n"
        "Ожидается директория, а не файл.\n";
}
const char* ErrorBase_BasicErrors::Error_8() {
    return "    --------------------\n"
        "Ошибка. Размер файла превышает допустимый лимит.\n";
}
const char* ErrorBase_BasicErrors::Error_9() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на удаление файла.\n";
}
const char* ErrorBase_BasicErrors::Error_10() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на чтение файла.\n";
}
const char* ErrorBase_BasicErrors::Error_11() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на запись в файл.\n";
}
const char* ErrorBase_BasicErrors::Error_12() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на изменения файла.\n";
}
const char* ErrorBase_BasicErrors::Error_13() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на копирование файла.\n";
}
const char* ErrorBase_BasicErrors::Error_14() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на перемещение файла.\n";
}
// Исключения для операций с папками
const char* ErrorBase_BasicErrors::Error_27() {
    return "    --------------------\n"
        "Ошибка. Неверное имя папки.\n"
        "Имя папки не может быть пустым.\n";
}
const char* ErrorBase_BasicErrors::Error_28() {
    return "    --------------------\n"
        "Ошибка. Указанная папка не существует.\n"
        "Папка с таким названием не была найдена.\n";
}
const char* ErrorBase_BasicErrors::Error_29() {
    return "    --------------------\n"
        "Ошибка. Указанный путь не существует.\n"
        "Папка с таким путем не была найдена.\n";
}
const char* ErrorBase_BasicErrors::Error_30() {
    return "    --------------------\n"
        "Ошибка. Папка с таким названием уже существует.\n"
        "Укажите другое название или удалите существующую папку.\n";
}
const char* ErrorBase_BasicErrors::Error_31() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на удаление папки.\n";
}
const char* ErrorBase_BasicErrors::Error_32() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на перемещение папки.\n";
}
const char* ErrorBase_BasicErrors::Error_33() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на изменения папки.\n";
}
const char* ErrorBase_BasicErrors::Error_34() {
    return "    --------------------\n"
        "Ошибка. Отсутствуют права на копирование папки.\n";
}
// Исключения для операций с аттрибутами
const char* ErrorBase_BasicErrors::Error_41() {
    return "    --------------------\n"
        "Ошибка. Не удалось получить аттрибуты.\n";
}
const char* ErrorBase_BasicErrors::Error_42() {
    return "    --------------------\n"
        "Ошибка. Указан неизвестный аттрибут.\n";
}
const char* ErrorBase_BasicErrors::Error_43() {
    return "    --------------------\n"
        "Ошибка. Не указан путь для установки аттрибута.\n";
}
const char* ErrorBase_BasicErrors::Error_44() {
    return "    --------------------\n"
        "Ошибка. Не указаны путь и аттрибут для установки.\n";
}
const char* ErrorBase_BasicErrors::Error_45() {
    return "    --------------------\n"
        "Ошибка. Не указан аттрибут для установки.\n";
}
const char* ErrorBase_BasicErrors::Error_46() {
    return "    --------------------\n"
        "Ошибка. Указан неверный формат команды.\n";
}
// Исключения для операций с разрешениями (правами)
const char* ErrorBase_BasicErrors::Error_48() {
    return "    --------------------\n"
        "Ошибка. Не удалось получить разрешения.\n";
}
const char* ErrorBase_BasicErrors::Error_49() {
    return "    --------------------\n"
        "Ошибка. Указано неизвестное разрешение.\n";
}
const char* ErrorBase_BasicErrors::Error_50() {
    return "    --------------------\n"
        "Ошибка. Не указан путь для установки разрешения.\n";
}
const char* ErrorBase_BasicErrors::Error_51() {
    return "    --------------------\n"
        "Ошибка. Не указан путь и разрешение для установки.\n";
}
const char* ErrorBase_BasicErrors::Error_52() {
    return "    --------------------\n"
        "Ошибка. Не указано разрешение для установки.\n";
}

// ErrorBase_SystemErrors implementations
const char* ErrorBase_SystemErrors::Error_15() {
    return "    --------------------\n"
        "Возникла ошибка во время открытия файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_16() {
    return "    --------------------\n"
        "Возникла ошибка во время чтения файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_17() {
    return "    --------------------\n"
        "Возникла ошибка во время записи данных в файл.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_18() {
    return "    --------------------\n"
        "Возникла ошибка во время создания файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_19() {
    return "    --------------------\n"
        "Возникла ошибка во время удаления файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_20() {
    return "    --------------------\n"
        "Возникла ошибка во время получения данных о файле.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_21() {
    return "    --------------------\n"
        "Возникла ошибка во время чтения директории.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_22() {
    return "    --------------------\n"
        "Возникла ошибка во время смены директории.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_23() {
    return "    --------------------\n"
        "Возникла ошибка во время очистки файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_24() {
    return "    --------------------\n"
        "Возникла ошибка во время копирования файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_25() {
    return "    --------------------\n"
        "Возникла ошибка во время перемещения файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_26() {
    return "    --------------------\n"
        "Возникла ошибка во время переименования файла.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
// Исключения для операций с папками
const char* ErrorBase_SystemErrors::Error_35() {
    return "    --------------------\n"
        "Возникла ошибка во время создания папки.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_36() {
    return "    --------------------\n"
        "Возникла ошибка во время удаления папки.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_37() {
    return "    --------------------\n"
        "Возникла ошибка во время получения данных о папке.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_38() {
    return "    --------------------\n"
        "Возникла ошибка во время перемещения папки.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_39() {
    return "    --------------------\n"
        "Возникла ошибка во время изменения папки.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_40() {
    return "    --------------------\n"
        "Возникла ошибка во время копирования папки.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
// Исключения для операций с аттрибутами и разрешениями
const char* ErrorBase_SystemErrors::Error_47() {
    return "    --------------------\n"
        "Возникла ошибка во время установки аттрибута.\n"
        "Возникла системная или аппаратная ошибка.\n";
}
const char* ErrorBase_SystemErrors::Error_53() {
    return "    --------------------\n"
        "Возникла ошибка во время установки разрешения.\n"
        "Возникла системная или аппаратная ошибка.\n";
}

// Exception implementations
Exception::Exception(const char* msg, int code) noexcept : message(msg), ErrorCode(code) {}

const char* Exception::what() const noexcept {
    return message;
}
int Exception::code() const noexcept {
    return ErrorCode;
}