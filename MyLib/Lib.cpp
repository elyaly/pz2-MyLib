
/*---------------------------------------------------------------*/
// 1. ��������� �������� ���� ����� �������� �����
#include <iostream>
#include <string>
#include <vector>
#include "Header.h"


BigInteger::BigInteger() {
    // ���������� ��'���
}

void BigInteger::setDecimal(const std::string& decimalString) {
    data.clear();
    // ���������� ���������� ����� � ���������������
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
// 2. ��������� �������� ��������
BigInteger BigInteger::INV() const {
    BigInteger result;
    result.data = data; // ������� ���
    for (unsigned int& digit : result.data) {
        digit = ~digit; // �������� ������� �������
    }
    return result;
}

BigInteger BigInteger::XOR(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // ������� ���
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] ^= other.data[i]; // �������� ������� XOR
    }
    return result;
}

BigInteger BigInteger::OR(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // ������� ���
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] |= other.data[i]; // �������� ������� OR
    }
    return result;
}

BigInteger BigInteger::AND(const BigInteger& other) const {
    BigInteger result;
    result.data = data; // ������� ���
    for (size_t i = 0; i < data.size(); i++) {
        result.data[i] &= other.data[i]; // �������� ������� AND
    }
    return result;
}

BigInteger BigInteger::shiftR(int n) const {
    BigInteger result;
    result.data = data; // ������� ���
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
    result.data = data; // ������� ���
    int carry = 0;
    for (int i = data.size() - 1; i >= 0; i--) {
        int temp = data[i];
        result.data[i] = (temp << n) | carry;
        carry = temp >> (32 - n);
    }
    return result;
}

/*---------------------------------------------------------------*/
// 3. ��������� ������������ ��������
// ����� ��� ��������� �����
BigInteger BigInteger::ADD(const BigInteger& other) const {
    BigInteger result;
    result.data.reserve(std::max(data.size(), other.data.size()) + 1); // ����� ���� ��� ���������� �� ��������� ��������
    unsigned int carry = 0;

    // ��������� ����� ����� �� ������� ��������
    for (size_t i = 0; i < std::max(data.size(), other.data.size()); i++) {
        unsigned int sum = carry;
        if (i < data.size()) sum += data[i];
        if (i < other.data.size()) sum += other.data[i];
        carry = sum >> 32; // �������� �������
        result.data.push_back(sum & 0xFFFFFFFF); // �������� ���� 32 ���
    }

    // ���� � ������� �������, ������ ���� �� ������� ����
    if (carry > 0) {
        result.data.push_back(carry);
    }

    return result;
}

// ����� ��� �������� �����
BigInteger BigInteger::SUB(const BigInteger& other) const {
    BigInteger result;
    result.data.reserve(std::max(data.size(), other.data.size())); // ����� ���� ��� ����������
    unsigned int borrow = 0;

    // ³������� ����� ����� �� ������� ������
    for (size_t i = 0; i < std::max(data.size(), other.data.size()); i++) {
        unsigned int diff = borrow;
        if (i < data.size()) diff += data[i];
        if (i < other.data.size()) diff -= other.data[i];
        if (diff > 0xFFFFFFFF) {
            borrow = 1; // ���� diff > 0xFFFFFFFF, ������������ �����
        }
        else {
            borrow = 0;
        }
        result.data.push_back(diff & 0xFFFFFFFF); // �������� ���� 32 ���
    }

    // ����������� ����� � ���������� �����, ���� �������
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

    // ��������� ������ ������ ����� � ���� ����������
    while (!result.data.empty() && result.data.back() == 0) {
        result.data.pop_back();
    }

    return result;
}


// ����� ��� ������ ����� �� �������
//BigInteger BigInteger::MOD(const BigInteger& other) const {
//    BigInteger result = *this;
//    while (result >= other) {
//        result = result.SUB(other);
//    }
//    return result;
//}
