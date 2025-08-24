#include "handleconsoleoperations.h"
#include <sstream>
#include <algorithm>

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

void HandleConsoleOperations::PrintSetTranslate(const std::set<std::string>& aTranslates) const
{
    mOstream << "{ " << *aTranslates.begin();
    std::for_each(std::next(aTranslates.begin()), aTranslates.end(), [&](const std::string& element)
                  {
                      mOstream << ", " << element;
                  });
    mOstream << " }";
}

HandleConsoleOperations::HandleConsoleOperations(std::istream& aIstream, std::ostream& aOstream)
    : mEngDir()
    , mIstream(aIstream)
    , mOstream(aOstream) {}

HandleConsoleOperations::~HandleConsoleOperations() = default;

void HandleConsoleOperations::Process()
{
    std::string commandLine;
    std::vector<std::string> args;
    std::string arg;

    while (true)
    {
        mOstream << ">";
        std::getline(mIstream, commandLine);
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
            mOstream << "Invalid input!\nUse 'help' for help\n";
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
        if(aArgs.size() != 3)
        {
            return ResultExecuteCommand::Invalid;
        }
        mEngDir.AddWordTranslate(aArgs[1], aArgs[2]);
        // if(const std::string* strold = mEngDir.AddWordTranslate(aArgs[1], aArgs[2]); strold)
        // {
        //     mOstream << "The translate of '" << aArgs[1] <<
        //         "' already exist - '" << *strold << "'\n";
        // }
        return ResultExecuteCommand::Ok;
    }
    case CommandType::Delete:
        if(aArgs.size() == 2)
        {
            if(!mEngDir.DeleteWordTranslate(aArgs[1]))
            {
                mOstream << "The word '" << aArgs[1] << "' is not in the dictionary\n";
            }
        }
        else if(aArgs.size() == 3)
        {
            if(!mEngDir.DeleteWordTranslate(aArgs[1], aArgs[2]))
            {
                mOstream << "The translate '" << aArgs[2] << "' of the word '" << aArgs[1] << "' is not in the dictionary\n";
            }
        }
        else
        {
            return ResultExecuteCommand::Invalid;
        }
        return ResultExecuteCommand::Ok;

    case CommandType::Find:
    {
        if(aArgs.size() != 2)
        {
            return ResultExecuteCommand::Invalid;
        }
        const std::set<std::string>* translate = mEngDir.FindTranslate(aArgs[1]);
        if (!translate)
        {
            mOstream << "The word '" << aArgs[1] << "' is not in the dictionary\n";
        }
        else
        {
            PrintSetTranslate(*translate);
            // mOstream << *translate << "\n";
        }
        return ResultExecuteCommand::Ok;
    }

    case CommandType::List:
    {
        if(aArgs.size() != 1)
        {
            return ResultExecuteCommand::Invalid;
        }
        std::map<std::string, std::set<std::string>> dict = mEngDir.GetDictionary();
        if(dict.empty())
        {
            mOstream << "The dictionary is empty\n";
        }
        for(const auto& item : dict)
        {
            mOstream/*.width(10)*/ << item.first << " -- ";
            PrintSetTranslate(item.second);
            mOstream << "\n";
        }
        return ResultExecuteCommand::Ok;
    }
    case CommandType::Help:
    {
        const char* help = "\n---------------------------------------------------------------------\n"
                           "\n"
                           "Enter 'add <word> <translate>' for add word to dictionary\n"
                           "Enter 'delete <word> <translate>' for delete translate of the word\n"
                           "Enter 'delete <word>' for delete word from dictionary\n"
                           "Enter 'find <word>' for find translate of word\n"
                           "Enter 'list' for get all dictionary\n"
                           "Enter 'help' for help\n"
                           "Enter 'quit' for quit\n"
                           "\n---------------------------------------------------------------------\n";
        mOstream << help;
        return ResultExecuteCommand::Ok;
    }

    case CommandType::Quit:
        return ResultExecuteCommand::Quit;

    case CommandType::Unknown:
        return ResultExecuteCommand::Invalid;
    }

    return ResultExecuteCommand::Invalid;
}
