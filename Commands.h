#pragma once
#include "ProgramModes.h"

// Команды для работы с файлами
void CommandREAD_F(string& name);
void CommandWRITE_F(string& name);
void CommandCREATE_F(string& name);
void CommandDELETE_F(string& name);
void CommandCLEAR_F(string& name);
void CommandINFO_F(string& name);
void CommandMOVE_F(string& name);
void CommandRENAME_F(string& name);
void CommandCOPY_F(string& name);
// Команды для работы с папками
void CommandMKDIR(string& name);
void CommandRMDIR(string& name);
void CommandINFO_D(string& name);
void CommandMOVE_D(string& name);
void CommandRENAME_D(string& name);
void CommandCOPY_D(string& name);
// Команды для работы с файловой системой
void CommandLS(string& name);
void CommandCD(string& name);
void CommandECHO(const string& input);
void CommandPWD();
// Команды для работы с аттрибутами и разрешениями
void CommandSET_FA(string& name);
void CommandSET_DA(string& name);
void CommandSET_FP(string& name);
void CommandSET_DP(string& name);
// Основные команды
void CommandWWFS();
void CommandSTOP();
void CommandEXIT();
void CommandCLEAR();
void CommandMODE(ProgramMode CurrentMode);
void CommandHELP(ProgramMode Currentmode);