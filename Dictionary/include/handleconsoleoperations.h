#pragma once
#include "dictionary.h"
#include <vector>

enum class CommandType;
enum class ResultExecuteCommand;

class HandleConsoleOperations
{
private:
    Dictionary mEngDir;
    std::ostream& mOstream;
    std::istream& mIstream;
    ResultExecuteCommand ExecuteInput(const std::vector<std::string>& aArgs);
public:
    HandleConsoleOperations(std::istream& aIstream, std::ostream& aOstream);
    ~HandleConsoleOperations();

    void Process();
};
