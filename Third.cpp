#include <iostream>
#include <cstdio>
#include <limits>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <thread>
#include <chrono>

void time(std::tm& local_future)
{
    std::cout << "Enter the amount of time to be clocked (format MM:SS): ";
    std::cin >> std::get_time(&local_future, "%M:%S");
    while(true)
    {
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter the correct time: ";
            std::cin >> std::get_time(&local_future, "%M:%S");
        }
        else
            break;
    }
}

void new_time(std::tm& local_future)
{
    if(local_future.tm_sec == 0)
    {
        local_future.tm_min = local_future.tm_min -1;
        local_future.tm_sec = 59;
    }
    else
        --local_future.tm_sec;
}

int main()
{
    std::time_t future = std::time(nullptr);
    std::tm local_future = *std::localtime(&future);
    std::cout << "Timer program." << std::endl;

    time(local_future);
    future = std::time(nullptr);
    while(local_future.tm_min != 0 || local_future.tm_sec != 0)
    {
//        std::time_t now = std::time(nullptr); 1 возможный вариант
//        if(future != now )
//        {
//            future = now;
            std::this_thread::sleep_for(std::chrono::seconds(1)) ;
//            Sleep(1000); 3 возможный вариант
            new_time(local_future);
            fflush(stdout);
            std::cout << std::put_time(&local_future, "Left: %M:%S\r");
//        }
    }

//    std::cout << std::put_time(&local_future, "Left: %M:%S") << std::endl;
    for (int i = 0; i < 3; ++i)
        std::cout << "DING! ";

    return 0;
}
