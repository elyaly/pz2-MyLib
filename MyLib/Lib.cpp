
/*---------------------------------------------------------------*/
// 1. Реалізація власного типу даних великого числа
#include <iostream>
#include <string>
#include <vector>
#include "Header.h"


BigInteger::BigInteger() {
    // Ініціалізуємо об'єкт
}

void BigInteger::setDecimal(const std::string& decimalString) {
    data.clear();
    // Конвертуємо десятковий рядок у шістнадцятковий
    unsigned long long decimalValue = std::stoull(decimalString);
    while (decimalValue > 0) {
        unsigned int hexDigit = static_cast<unsigned int>(decimalValue % 0x100000000);
        data.push_back(hexDigit);
        decimalValue /= 0x100000000;
    }
}


std::string BigInteger::getHex() const {
    std::string hexString;
    for (int i = data.size() - 1; i >= 0; i--) {
        char buffer[9];
        snprintf(buffer, 9, "%08X", data[i]);
        hexString += buffer;
    }
    return hexString;
}

/*---------------------------------------------------------------*/
// 2. Реалізація побітових операцій
BigInteger BigInteger::INV() const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    for (unsigned int& digit : result.data) {
        digit = ~digit; // Виконуємо побітову інверсію
    }
    return result;
}

BigInteger BigInteger::XOR(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] ^= other.data[i]; // Виконуємо побітове XOR
    }
    return result;
}

BigInteger BigInteger::OR(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] |= other.data[i]; // Виконуємо побітове OR
    }
    return result;
}

BigInteger BigInteger::AND(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] &= other.data[i]; // Виконуємо побітове AND
    }
    return result;
}

BigInteger BigInteger::shiftR(int n) const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    int carry = 0;
    for (size_t i = 0; i < data.size(); i++) {
        int temp = data[i];
        result.data[i] = (temp >> n) | (carry << (32 - n));
        carry = temp << (32 - n);
    }
    return result;
}

BigInteger BigInteger::shiftL(int n) const {
    BigInteger result;
    result.data = data; // Копіюємо дані
    int carry = 0;
    for (int i = data.size() - 1; i >= 0; i--) {
        int temp = data[i];
        result.data[i] = (temp << n) | carry;
        carry = temp >> (32 - n);
    }
    return result;
}

/*---------------------------------------------------------------*/
// 3. Реалізація арифметичних операцій
// Метод для додавання чисел
BigInteger BigInteger::ADD(const BigInteger& other) const {
    BigInteger result;
    result.data.reserve(std::max(data.size(), other.data.size()) + 1); // Запас місця для результату та можливого переносу
    unsigned int carry = 0;

    // Додавання блоків чисел та обробка переносу
    for (size_t i = 0; i < std::max(data.size(), other.data.size()); i++) {
        unsigned int sum = carry;
        if (i < data.size()) sum += data[i];
        if (i < other.data.size()) sum += other.data[i];
        carry = sum >> 32; // Отримуємо перенос
        result.data.push_back(sum & 0xFFFFFFFF); // Зберігаємо нижні 32 біта
    }

    // Якщо є останній перенос, додаємо його як останній блок
    if (carry > 0) {
        result.data.push_back(carry);
    }

    return result;
}

// Метод для віднімання чисел
BigInteger BigInteger::SUB(const BigInteger& other) const {
    BigInteger result;
    result.data.reserve(std::max(data.size(), other.data.size())); // Запас місця для результату
    unsigned int borrow = 0;

    // Віднімання блоків чисел та обробка виносу
    for (size_t i = 0; i < std::max(data.size(), other.data.size()); i++) {
        unsigned int diff = borrow;
        if (i < data.size()) diff += data[i];
        if (i < other.data.size()) diff -= other.data[i];
        if (diff > 0xFFFFFFFF) {
            borrow = 1; // Якщо diff > 0xFFFFFFFF, встановлюємо винос
        }
        else {
            borrow = 0;
        }
        result.data.push_back(diff & 0xFFFFFFFF); // Зберігаємо нижні 32 біта
    }

    // Виправляємо винос в наступному блоку, якщо потрібно
    for (size_t i = 0; i < result.data.size(); i++) {
        if (borrow == 0) break;
        if (result.data[i] == 0) {
            result.data[i] = 0xFFFFFFFF;
        }
        else {
            borrow = 0;
            break;
        }
    }

    // Видаляємо можливі нульові блоки в кінці результату
    while (!result.data.empty() && result.data.back() == 0) {
        result.data.pop_back();
    }

    return result;
}


// Метод для взяття числа за модулем
//BigInteger BigInteger::MOD(const BigInteger& other) const {
//    BigInteger result = *this;
//    while (result >= other) {
//        result = result.SUB(other);
//    }
//    return result;
//}
