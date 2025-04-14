#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>

struct NumberRule
{
    int base; // разряд числа 
    int start; // начальная позиция для правила
    int count; // количество элементов
    bool female; // женский род
    std::vector<std::string> forms; // база знаний
};

const std::vector<NumberRule> rules =
{
    {100, 1, 9, false, {"сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"}},
    {10, 2, 8, false, {"двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"}},
    {1, 10, 10, false, {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"}},
    {1, 1, 2, true, {"одна", "две"}},
    {1, 1, 9, false, {"один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"}},
};

const std::map<int, std::vector<std::string>> classes =
{
    {3, {"тысяча", "тысячи", "тысяч"}},
    {6, {"миллион", "миллиона", "миллионов"}},
    {9, {"миллиард", "миллиарда", "миллиардов"}}
};

std::string convert_part(int num, bool female); // функция которая преобразует числа до 1000
std::string get_form(int num, int scale); // возвращает правильную форму слова
std::string number_to_words(long long num); // преобразует и собирает слово

int main()
{
    setlocale(LC_ALL, "");
    long long num;
    while (true)
    {
        std::cout << "Введите число: ";
        std::cin >> num;
        std::cout << number_to_words(num) << std::endl;
    }
    return 0;
}

std::string convert_part(int num, bool female) {
    if (num == 0) return "";

    std::string res;
    for (const auto& rule : rules) {
        if (num < rule.start) continue;
        if (rule.female && !female) continue; 

        int value = (num / rule.base) * rule.base;
        if (value >= rule.start * rule.base) {
            int index = (value / rule.base) - rule.start;
            if (rule.base == 1 && female && index < 2 && rule.female) {
                res += rule.forms[index] + " ";
                num -= value;
                break;
            }
            else if (index < static_cast<int>(rule.forms.size())) {
                res += rule.forms[index] + " ";
                num -= value;
                if (rule.start == 10 && rule.base == 1) {
                    num = 0;
                }
            }
        }
    }

    // Удаление лишнего пробела
    if (!res.empty() && res.back() == ' ') res.pop_back();
    return res;
}
std::string get_form(int num, int scale)
{
    auto i = classes.find(scale);
    if (i == classes.end()) return "";

    num = num % 100;
    if (num > 19) num %= 10;
    return i->second[num == 1 ? 0 : (num > 1 && num < 5) ? 1 : 2];
}

std::string number_to_words(long long num)
{
    if (num == 0) return "ноль";

    std::string result;
    for (auto i = classes.rbegin(); i != classes.rend(); ++i)
    {
        long long power = pow(10, i->first);
        int part = (num / power) % 1000;

        if (part > 0) {
            std::string words = convert_part(part, i->first == 3);
            result += words + " " + get_form(part, i->first) + " ";
        }
    }

    int last_part = num % 1000;
    if (last_part > 0) {
        std::string words = convert_part(last_part, false);
        if (!words.empty()) {
            result += words;
        }
    }

    while (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }
    return result.empty() ? "ноль" : result;
}
