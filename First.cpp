#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

struct track
{
    std::string task;
    std::time_t start;
    std::time_t stop;
};

void list(std::string& command)
{
    std::cout << "Select the command: " << std::endl;
    std::cout << "begin - start to task" << std::endl;
    std::cout << "end - complete the task" << std::endl;
    std::cout << "status - output of information aboud tasks" << std::endl;
    std::cout << "exit - exiting the program" << std::endl;
    std::cout << std::endl;
    std::cout << "Input of command: ";
    getline(std::cin, command);
}

void check(std::string& command)
{
    while(true)
    {
        auto it = std::find_if(command.begin(), command.end(),[](char const &c)
        {
            return !std::isalpha(c);
        });
        if(it == command.end())
            break;
        std::cout << "Enter the correct command: ";
        getline(std::cin, command);
    }
}

void reg(std::string& command)
{
    for (int i = 0; i < command.size(); ++i)
    {
        if(command[i]>='A' && command[i]<='Z')
            command[i] = tolower(command[i]);
    }
}

void begin (std::vector<track>& keeps)
{
    track execut;
    std::cout << "Enter the task: ";
    getline(std::cin, execut.task);

    if((!keeps.empty() && (execut.task != keeps[keeps.size()-1].task)) || keeps.empty())
    {
        execut.start = time(nullptr);
        if (!keeps.empty())
            keeps[keeps.size()-1].stop = time(nullptr);
        execut.stop = 0;
        keeps.push_back(execut);
    }
    else
        std::cout << "The command is already running!" << std::endl;
}

void end(std::time_t& stop)
{
    stop = time(nullptr);
}

void line()
{
    for (int i = 0; i < 50; ++i)
        std::cout <<"-";
    std::cout << std::endl;
}

void print_time(std::time_t& first, std::time_t& second)
{
    if((second-first) < 60)
        std::cout <<std::setw(6) << second-first << "S|"<<std::endl;
    else if((second-first) < (60*60))
        std::cout << std::setw(6) << (second-first)/60 << "M|" << std::endl;
    else if ((second - first) < (60*60*24))
        std::cout << std::setw(3) << (second-first)/(60*60) << "H" <<
            std::setw(2)<< ((second - first)/60) - (60* ((second-first)/(60*60)))<<"M|"<< std::endl;
}

void status(std::vector<track>& keeps)
{
    line();
    std::cout <<"|"<< std::setw(41) << "Task|" <<std::setw(8)<< "Time|" << std::endl;
    line();

    for (int i = 0; i < keeps.size(); ++i)
    {
        std::cout << "|"<<std::setw(40) << keeps[i].task <<"|";
        if (keeps[i].stop != 0)
            print_time(keeps[i].start, keeps[i].stop);
        else
            std::cout << "process|"<<std::endl;
        line();
    }
}

int main()
{
    std::string command;
    std::vector<track> keeps;
    std::cout << "The program keeps track of the task execultion time.\n" << std::endl;
    do
    {
        list(command);
        check(command);
        reg(command);
        std::cout << std::endl;

        if(command == "begin")
            begin(keeps);

        else if(command == "end" && (!keeps.empty() && keeps[keeps.size()-1].stop == 0))
            end(keeps[keeps.size()-1].stop);

        else if(command == "status" && !keeps.empty())
            status(keeps);

        std::cout << std::endl;
    }while(command != "exit");
    return 0;
}
