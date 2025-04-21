#include <iostream>
#include <cmath>
#include <string>

std::string units[] = {"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
std::string units_female[] = {"", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string teens[] = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
std::string tens[] = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
std::string hundreds[] = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот",  "семьсот", "восемьсот", "девятьсот" };
std::string forms[] = {"", "тысяча", "тысячи", "тысяч", "миллион", "миллиона", "миллионов", "миллиард", "миллиарда", "миллиардов" };

std::string triplet(int num, bool female);
std::string num_to_word(long long num);
std::string getForm(int n, int num_seg);

int main()
{
    setlocale(LC_ALL, "");
    long long n;
    while (true) 
    {
        std::cout << "Введите число: ";
        std::cin >> n;
        std::cout << num_to_word(n) << std::endl;
    }
    return 0;
}

std::string triplet(int num, bool female) {
    std::string result;
    int h = num / 100;
    int t = (num / 10) % 10;
    int u = num % 10;

    if (h > 0) {
        result += hundreds[h] + " ";
    }

    if (t == 1) {
        result += teens[u] + " ";
    }
    else {
        if (t > 1) {
            result += tens[t] + " ";
        }
        if (u > 0) {
            result += (female ? units_female[u] : units[u]) + " ";
        }
    }

    return result;
}

std::string getForm(int n, int num_seg)
{
    int seg = (num_seg - 1) * 3 + 1;
    n %= 100;
    if (n >= 11 && n <= 19)
    {
        return *(forms + seg + 2);
    }
    switch (n % 10) 
    {
    case 1: return *(forms + seg);
    case 2:
    case 3:
    case 4: return *(forms + seg + 1);
    default: return *(forms + seg + 2);
    }
}

std::string num_to_word(long long num)
{
    std::string result;
    int len = (log10(num) + 1);
    int segments = (len + 2) / 3;
    for (int seg = segments - 1; seg >= 0; seg--) {
        long long power = pow(1000, seg);
        int current_segment = (num / power) % 1000;
        if (current_segment > 0) {
            bool female = (seg == 1); 
            result += triplet(current_segment, female);
            if (seg > 0) {
                std::string form = getForm(current_segment, seg);
                if (!form.empty()) {
                    result += form + " ";
                }
            }
        }

    }

    // Удаляем лишний пробел в конце
    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}
