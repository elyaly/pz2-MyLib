
#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <string>
#include <vector>

class BigInteger {
private:
    std::vector<unsigned int> data; // ����� ����������� ����� �����

public:
    BigInteger();

    // ����� ��� ������������ ����� � ����������� �����
    void setDecimal(const std::string& decimalString);

    // ����� ��� ���������� ����� � �������������� ������
    std::string getHex() const;

    // ����� ��� ������������ ����� � ���������������� �����
    void setHex(const std::string& hexString);

    // ������ ��� �������� ��������
    BigInteger INV() const;
    BigInteger XOR(const BigInteger& other) const;
    BigInteger OR(const BigInteger& other) const;
    BigInteger AND(const BigInteger& other) const;
    BigInteger shiftR(int n) const;
    BigInteger shiftL(int n) const;

    // ������ ��� ����������� �������� 
    BigInteger ADD(const BigInteger& other) const;
    BigInteger SUB(const BigInteger& other) const;
    //BigInteger MUL(const BigInteger& other) const;
    // BigInteger DIV(const BigInteger& other) const;
    BigInteger MOD(const BigInteger& other) const;
};

#endif
