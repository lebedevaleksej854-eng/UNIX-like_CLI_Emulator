#include "CommandsList.h"

const set<string>PrimaryModeCommands = {
	"wwfs", "clear", "stop", 
	"mode", "help"
};

const set<string>FSModeCommands = {
	// Операции с файлами
	"rd -f", "wt -f", "crt -f",
	"del -f", "clr -f", "info -f",
	"mv -f", "rn -f", "cp -f",
	// Операции с папками
	"mkdir", "rmdir", "info -d",
	"mv -d", "rn -d", "cp -d",
	// Операции с аттрибутами и разрешениями
	"set att -f", "set att -d",
	"set perm -f", "set perm -d",
	// Специальные операции
	"ls", "cd", "echo", "pwd",
	// Основные операции
	"clear", "exit", "stop",
	"mode", "help"
};