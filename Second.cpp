#include <iostream>
#include<algorithm>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <cmath>

struct birthday
{
    std::string name;
    std::tm date;
};

void checkName(std::string& name)
{
    while(true)
    {
        auto it = find_if(name.begin(), name.end(),[](char const &c)
        {
            return !std::isalpha(c);
        }
        );
        if(it == name.end())
            break;
        std::cout << "Enter the correct name: ";
        getline(std::cin, name);
    }
}

void registr(std::string& name)
{
    for (int i = 1; i < name.size(); ++i)
    {
        if(!(name[i]>='a' && name[i]<='z'))
            name[i] = tolower(name[i]);
    }

    name[0] = toupper(name[0]);
}

void input_date(std::tm& date, const std::tm& today)
{
    std::time_t t= std::time(nullptr);
    date =*std::localtime(&t);
    std::cout << "Enter a friend`s bithday in format YYYY/MM/DD: ";
    std::cin >> std::get_time(&date, "%Y/%m/%d");
    while(true)
    {
        if(std::cin.fail() || (date.tm_year > today.tm_year)
            || (date.tm_year == today.tm_year && date.tm_mon > today.tm_mon)
            || (date.tm_year == today.tm_year && date.tm_mon == today.tm_mon && date.tm_mday > today.tm_mday))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter the correct date: ";
            std::cin >> std::get_time(&date, "%Y/%m/%d");
        }
        else
            break;
    }
}

int calculation(std::tm& day, int& now)
{
    int number = 0;
    for(int i = 0; i < day.tm_mon; i++)
    {
        if (i == (day.tm_mon - 1))
            number+= day.tm_mday;
        else if( i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 9)
            number+= 31;
        else if (i == 3 || i == 5 || i == 8 || i == 10)
            number +=30;
        else if(i == 2)
        {
            if((now%4 == 0 || now%400 == 0) && !(now%100 ==0))
                number +=29;
            else
                number+=28;
        }
    }
    return number;
}

int difference(std::tm& birthday, std::tm& now)
{
    return abs(calculation(birthday, now.tm_year) - calculation(now, now.tm_year));
}

void search(std::vector<birthday>& mates)
{
    const int now =0;
    int min =1;
    for (int i = min+1; i < mates.size(); ++i) {
        if((abs(mates[i].date.tm_mon - mates[now].date.tm_mon) < abs(mates[min].date.tm_mon - mates[now].date.tm_mon))
            || (abs(mates[i].date.tm_mon - mates[now].date.tm_mon) == abs(mates[min].date.tm_mon - mates[now].date.tm_mon)
                && (difference(mates[i].date, mates[now].date) < difference(mates[min].date,mates[now].date))))
            min = i;
    }

    if(((mates[min].date.tm_mon - mates[now].date.tm_mon) < 0) || ((mates[min].date.tm_mon == mates[now].date.tm_mon)
        && (mates[min].date.tm_mday < mates[now].date.tm_mday)))
        std::cout << "The nearest bithday has passed: " << std::put_time(&mates[min].date, "%m/%d") << std::endl;
    else if(mates[min].date.tm_mday == mates[now].date.tm_mday)
        std::cout << "Today "<< std::put_time(&mates[min].date, "%m/%d") << " birthday " << mates[min].name << std::endl;
    else
        std::cout <<  "The nearest birthday: " << std::put_time(&mates[min].date, "%m/%d") << " for " << mates[min].name << std::endl;
}

int main()
{
    std::vector<birthday> mates;
    birthday when;
    std::time_t now = time(nullptr);
    when.date =*localtime(&now);
    when.name = "now";
    mates.push_back(when);

    std::cout << "The program reminds of a bithday."<<std::endl;
    do
    {
        std::cout << "Enter the friend`s name: ";
        getline(std::cin, when.name);

        if (when.name == "end")
            break;

        checkName(when.name);
        registr(when.name);

        input_date(when.date , mates[0].date);

        mates.push_back(when);
        std::cout << "day: " << std::put_time(&mates[mates.size()-1].date, "%m/%d") << " " << mates[mates.size()-1].name << std::endl;
        std::cout << mates[mates.size()-1].date.tm_yday << std::endl;
        std::cin.get();
    } while(true);

    search(mates);

    return 0;
}
