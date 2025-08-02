#pragma once
#include "englishdictionary.h"
#include <vector>

enum class CommandType;
enum class ResultExecuteCommand;

class HandleConsoleOperations
{
private:
    EnglishDictionary mEngDir;
    ResultExecuteCommand ExecuteInput(const std::vector<std::string>& aArgs);
public:
    HandleConsoleOperations();
    ~HandleConsoleOperations();

    void Process(std::istream& aIstream/*std::ostream* aOstream = nullptr*/);
};
