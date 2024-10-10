#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::string unitsMale[] = { "", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string unitsFemale[] = { "", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
std::string teens[] = { "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
std::string tens[] = { "", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
std::string hundreds[] = { "", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };
std::string thousands[] = { "", "тысяча", "тысячи", "тысяч" };
std::string millions[] = { "", "миллион", "миллиона", "миллионов" };
std::string billions[] = { "", "миллиард", "миллиарда", "миллиардов" };

// Функция для выбора правильной формы
std::string getWordForm(int num, std::string forms[]) {
    int lastTwoDigits = num % 100;
    if (lastTwoDigits >= 11 && lastTwoDigits <= 19) {
        return forms[3];
    }

    int lastDigit = num % 10;
    if (lastDigit == 1) {
        return forms[1];
    }
    else if (lastDigit >= 2 && lastDigit <= 4) {
        return forms[2];
    }
    else {
        return forms[3];
    }
}

// Функция для преобразования чисел в текст
std::string numToWords(int num, bool isFemale = false) {
    if (num == 0) {
        return "";
    }

    std::ostringstream result;

    result << hundreds[num / 100];
    num %= 100;

    if (num >= 10 && num < 20) {
        result << (result.str().empty() ? "" : " ") << teens[num - 10];
        return result.str();
    }

    result << (result.str().empty() ? "" : " ") << tens[num / 10];
    num %= 10;

    result << (result.str().empty() ? "" : " ") << (isFemale ? unitsFemale[num] : unitsMale[num]);

    return result.str();
}

// Основная функция
std::string numberToWords(long long num) {
    if (num == 0) {
        return "ноль";
    }

    std::ostringstream result;

    if (num >= 1000000000) {
        int billionPart = num / 1000000000;
        result << numToWords(billionPart) << ' ' << getWordForm(billionPart, billions);
        num %= 1000000000;
    }

    if (num >= 1000000) {
        int millionPart = num / 1000000;
        result << (result.str().empty() ? "" : " ") << numToWords(millionPart) << ' ' << getWordForm(millionPart, millions);
        num %= 1000000;
    }

    if (num >= 1000) {
        int thousandPart = num / 1000;
        result << (result.str().empty() ? "" : " ") << numToWords(thousandPart, true) << ' ' << getWordForm(thousandPart, thousands);
        num %= 1000;
    }

    result << (result.str().empty() ? "" : " ") << numToWords(num);

    return result.str();
}

int main() {
    setlocale(LC_ALL, "");
    long long num;
    std::cin >> num;
    std::cout << numberToWords(num) << std::endl;

    return 0;
}