#pragma once
#include "ProgramModes.h"

#include <string>
#include <vector>
#include <set>

using namespace std;

vector<string> LoadingMessages(const string& command);
void LoadingEffect(const vector<string>& messages);
void ClearConsole();
string GetUserInput();
string UserCommand(const set<string>& ValidCommands, string& user_input);
string ExpandEnvironmentVariables(const string& input);
string ExpandPath(const string& path);