#pragma once
#include <exception>
using namespace std;

class ErrorBase_BasicErrors {
public:
    // Исключения для операций с файлами
    static const char* Error_1();
    static const char* Error_2();
    static const char* Error_3();
    static const char* Error_4();
    static const char* Error_5();
    static const char* Error_6();
    static const char* Error_7();
    static const char* Error_8();
    static const char* Error_9();
    static const char* Error_10();
    static const char* Error_11();
    static const char* Error_12();
    static const char* Error_13();
    static const char* Error_14();
    // Исключения для операций с папками
    static const char* Error_27();
    static const char* Error_28();
    static const char* Error_29();
    static const char* Error_30();
    static const char* Error_31();
    static const char* Error_32();
    static const char* Error_33();
    static const char* Error_34();
    // Исключения для операций с аттрибутами
    static const char* Error_41();
    static const char* Error_42();
    static const char* Error_43();
    static const char* Error_44();
    static const char* Error_45();
    static const char* Error_46();
    // Исключения для операция с разрешениями (правами)
    static const char* Error_48();
    static const char* Error_49();
    static const char* Error_50();
    static const char* Error_51();
    static const char* Error_52();
};

class ErrorBase_SystemErrors {
public:
    // Исключения для операций с файлами
    static const char* Error_15();
    static const char* Error_16();
    static const char* Error_17();
    static const char* Error_18();
    static const char* Error_19();
    static const char* Error_20();
    static const char* Error_21();
    static const char* Error_22();
    static const char* Error_23();
    static const char* Error_24();
    static const char* Error_25();
    static const char* Error_26();
    // Исключения для операций с папками
    static const char* Error_35();
    static const char* Error_36();
    static const char* Error_37();
    static const char* Error_38();
    static const char* Error_39();
    static const char* Error_40();
    // Исключениями для операций с аттрибутами и разрешениями
    static const char* Error_47();
    static const char* Error_53();
};

class Exception : public exception {
private:
    int ErrorCode;
    const char* message;
public:
    explicit Exception(const char* msg, int code) noexcept;
    const char* what() const noexcept override;
    int code() const noexcept;
};