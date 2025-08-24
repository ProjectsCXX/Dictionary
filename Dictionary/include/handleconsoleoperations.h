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

private:
    void PrintSetTranslate(const std::set<std::string>& aTranslates) const;
public:
    HandleConsoleOperations(std::istream& aIstream, std::ostream& aOstream);
    ~HandleConsoleOperations();

    ResultExecuteCommand ExecuteInput(const std::vector<std::string>& aArgs);
    void Process();
};
