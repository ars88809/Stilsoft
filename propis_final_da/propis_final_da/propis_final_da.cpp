#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

std::string unitsMale[] = { "", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string unitsFemale[] = { "", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string teens[] = { "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
std::string tens[] = { "", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
std::string hundreds[] = { "", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот",  "семьсот", "восемьсот", "девятьсот" };
std::string thousands[] = { "", "тысяча", "тысячи", "тысяч" };
std::string millions[] = { "", "миллион", "миллиона", "миллионов" };
std::string billions[] = { "", "миллиард", "миллиарда", "миллиардов" };
int second_teens[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19 };

std::string getWordForm(int num, std::string forms[]);
std::string numToWords(int num, bool isFemale = false);
std::string numberToWords(long long num);

int main()
{
    setlocale(LC_ALL, "");
    long long num;
    std::cout << "введи число ";
    std::cin >> num;
    std::cout << numberToWords(num) << std::endl;

    return 0;
}

// Функция для выбора правильной формы
std::string getWordForm(int num, std::string forms[])
{
    int lastTwoDigits = num % 100;
    int lastDigit = num % 10;

    if (lastTwoDigits == *(second_teens + lastTwoDigits - 11))
    {
        return forms[3];
    }
    return forms[lastDigit == 1 ? 1 : (lastDigit >= 2 && lastDigit <= 4 ? 2 : 3)];
}

// Функция для преобразования чисел в текст
std::string numToWords(int num, bool isFemale)
{
    if (num == 0)
    {
        return "";
    }

    std::ostringstream result;

    result << hundreds[num / 100];
    num %= 100;

    if (num >= 10 && num < 20)
    {
        result << (result.str().empty() ? "" : " ") << teens[num - 10];
        return result.str();
    }

    result << (result.str().empty() ? "" : " ") << tens[num / 10];
    num %= 10;

    result << (result.str().empty() ? "" : " ") << (isFemale ? unitsFemale[num] : unitsMale[num]);

    return result.str();
}

// Основная функция
std::string numberToWords(long long num)
{
    if (num == 0)
    {
        return "ноль";
    }

    std::ostringstream result;

    int parts[] = { pow(10, 9), pow(10, 6), pow(10, 3) };
    std::string* wordForms[] = { billions, millions, thousands, nullptr };

    for (int i = 0; i < 3; ++i)
    {
        if (num >= parts[i])
        {
            int partValue = num / parts[i];
            result << (result.str().empty() ? "" : " ") << numToWords(partValue, i == 2);
            result << ' ' << getWordForm(partValue, wordForms[i]);
            num %= parts[i];
        }
    }

    result << (result.str().empty() ? "" : " ") << numToWords(num);

    return result.str();
}
