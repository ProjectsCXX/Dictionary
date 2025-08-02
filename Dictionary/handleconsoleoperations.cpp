#include "handleconsoleoperations.h"
#include <iostream>
#include <sstream>

enum class CommandType
{
    Add,
    Delete,
    Find,
    List,
    Help,
    Quit,
    Unknown
};

enum class ResultExecuteCommand
{
    Ok,
    Quit,
    Invalid
};

static std::map<std::string, CommandType> commandMap = {
    {"add", CommandType::Add},
    {"delete", CommandType::Delete},
    {"find", CommandType::Find},
    {"list", CommandType::List},
    {"help", CommandType::Help},
    {"quit", CommandType::Quit}
};

HandleConsoleOperations::HandleConsoleOperations() = default;
HandleConsoleOperations::~HandleConsoleOperations() = default;

void HandleConsoleOperations::Process(std::istream& aIstream)
{
    std::string commandLine;
    std::vector<std::string> args;
    std::string arg;

    while (true)
    {
        std::cout << ">";
        std::getline(aIstream, commandLine);
        std::stringstream commandLineStream(commandLine);
        while(commandLineStream >> arg)
        {
            args.push_back(arg);
        }

        ResultExecuteCommand result = ExecuteInput(args);

        if (result == ResultExecuteCommand::Quit)
        {
            break;
        }
        if (result == ResultExecuteCommand::Invalid)
        {
            std::cout << "Invalid input!\nUse 'help' for help\n";
        }
        args.clear();
    }
}

ResultExecuteCommand HandleConsoleOperations::ExecuteInput(const std::vector<std::string>& aArgs)
{
    if(aArgs.empty())
    {
        return ResultExecuteCommand::Ok;
    }

    auto it = commandMap.find(aArgs[0]);
    CommandType commandType = it != commandMap.end() ? it->second : CommandType::Unknown;

    switch(commandType)
    {
    case CommandType::Add:
    {
        if(aArgs.size() != 3)1+
        {
            return ResultExecuteCommand::Invalid;
        }
        if(const std::string* strold = mEngDir.AddWordTranslate(aArgs[1], aArgs[2]); strold)
        {
            std::cout << "The translate of '" << aArgs[1] <<
                "' already exist - '" << *strold << "'\n";
        }
        return ResultExecuteCommand::Ok;
    }
    case CommandType::Delete:
        if(aArgs.size() != 2)
        {
            return ResultExecuteCommand::Invalid;
        }
        if(!mEngDir.DeleteWordTranslate(aArgs[1]))
        {
            std::cout << "The word '" << aArgs[1] << "' is not in the dictionary\n";
        }
        return ResultExecuteCommand::Ok;

    case CommandType::Find:
    {
        if(aArgs.size() != 2)
        {
            return ResultExecuteCommand::Invalid;
        }
        const std::string* translate = mEngDir.FindTranslate(aArgs[1]);
        if (!translate)
        {
            std::cout << "The word '" << aArgs[1] << "' is not in the dictionary\n";
        }
        else
        {
            std::cout << *translate << "\n";
        }
        return ResultExecuteCommand::Ok;
    }

    case CommandType::List:
    {
        if(aArgs.size() != 1)
        {
            return ResultExecuteCommand::Invalid;
        }
        std::map<std::string, std::string> dict = mEngDir.GetDictionary();
        if(dict.empty())
        {
            std::cout << "The dictionary is empty\n";
        }
        for(const auto& item : dict)
        {
            std::cout << item.first << " " << item.second << "\n";
        }
        return ResultExecuteCommand::Ok;
    }
    case CommandType::Help:
    {
        const char* help = "\n---------------------------------------------------------------------\n"
                           "\n"
                           "Enter 'add <word> <translate>' for add word to dictionary\n"
                           "Enter 'delete <word>' for delete word from dictionary\n"
                           "Enter 'find <word>' for find translate of word\n"
                           "Enter 'list' for get all dictionary\n"
                           "Enter 'help' for help\n"
                           "Enter 'quit' for quit\n"
                           "\n---------------------------------------------------------------------\n";
        std::cout << help;
        return ResultExecuteCommand::Ok;
    }

    case CommandType::Quit:
        return ResultExecuteCommand::Quit;

    case CommandType::Unknown:
        return ResultExecuteCommand::Invalid;
    }

    return ResultExecuteCommand::Invalid;
}
