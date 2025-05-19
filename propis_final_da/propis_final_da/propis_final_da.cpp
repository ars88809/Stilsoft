#include <iostream>
#include <string>
#include <cmath>

std::string triplet(int num);
std::string thousands_triplet(int num);
std::string getThousandForm(int num);
std::string getLargeForm(int num, int level);
std::string numToWord(int num);

const char* numbers[4][10] = {
    {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"},         
    {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"},
    {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"},
    {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"}
};

const char* thousands_forms[5][10] = {
    {"", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"},     
    {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"},
    {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"},
    {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"},
    { "тысяч", "тысяча", "тысячи" }
};

const char* large_forms[2][3] = {
    {"миллионов", "миллион", "миллиона"},  
    {"миллиардов", "миллиард", "миллиарда"} 
};

int main()
{
    setlocale(LC_ALL, "");
    long long numb;
    std::cin >> numb;
    std::cout << numToWord(numb);
}

std::string triplet(int num)
{
    std::string sbor;
    if ((num / 10) % 10 == 1)
    {
        sbor += numbers[3][num / 100 % 10];
        sbor += " ";
        sbor += numbers[1][num % 10];
    }
    else
    {
        sbor += numbers[3][num / 100 % 10];
        sbor += " ";
        sbor += numbers[2][num / 10 % 10];
        sbor += " ";
        sbor += numbers[0][num % 10];
    }
    return sbor;
}

std::string thousands_triplet(int num)
{
    std::string sbor;
    if ((num / 10) % 10 == 1)
    {
        sbor += thousands_forms[3][num / 100 % 10];
        sbor += " ";
        sbor += thousands_forms[1][num % 10];
    }
    else
    {
        sbor += thousands_forms[3][num / 100 % 10];
        sbor += " ";
        sbor += thousands_forms[2][num / 10 % 10];
        sbor += " ";
        sbor += thousands_forms[0][num % 10];
    }
    sbor += " " + getThousandForm(num);
    return sbor;
}

std::string getThousandForm(int num) {
    int last_two = num % 100;
    int last_one = num % 10;

    int index = (last_two >= 11 && last_two <= 14) ? 0 : (last_one == 1 ? 1 : (last_one >= 2 && last_one <= 4 ? 2 : 0));

    return thousands_forms[4][index];
}

std::string getLargeForm(int num, int level) {
    int last_two = num % 100;
    int last_one = num % 10;

    int index = (last_two >= 11 && last_two <= 14) ? 0 : (last_one == 1 ? 1 : (last_one >= 2 && last_one <= 4 ? 2 : 0));

    return large_forms[level][index];
}

std::string numToWord(int num)
{

    std::string sbor;
    int temp = num;
    int seg = 0;
    while (temp > 0) 
    {
        temp /= 1000;
        seg++;
    }

    for (int parts = seg; parts > 0; parts--)
    {
        long long power = 1;
        for (int i = 1; i < parts; i++)
        {
            power *= 1000;
        }

        int current_part = (num / power) % 1000;
        if (current_part == 0) continue;

        if (parts == 2)
        { 
            sbor += thousands_triplet(current_part);
        }
        else 
        {
            sbor += triplet(current_part);
            if (parts > 2)
            {
                sbor +=  ' ' + getLargeForm(current_part, abs(parts - 4));
            }
        }
        sbor += " ";
    }


    while (!sbor.empty() && sbor.back() == ' ') sbor.pop_back();
    while (!sbor.empty() && sbor.front() == ' ') sbor.erase(0, 1);


    return sbor;
}
