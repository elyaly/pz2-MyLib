
#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <string>
#include <vector>

class BigInteger {
private:
    std::vector<unsigned int> data; // Масив беззнакових цілих чисел

public:
    BigInteger();

    // Метод для встановлення числа з десяткового числа
    void setDecimal(const std::string& decimalString);

    // Метод для повернення числа у шістнадцятковій системі
    std::string getHex() const;

    // Метод для встановлення числа з шістнадцяткового рядка
    void setHex(const std::string& hexString);

    // Методи для побітових операцій
    BigInteger INV() const;
    BigInteger XOR(const BigInteger& other) const;
    BigInteger OR(const BigInteger& other) const;
    BigInteger AND(const BigInteger& other) const;
    BigInteger shiftR(int n) const;
    BigInteger shiftL(int n) const;

    // Методи для аріфметичних операцій 
    BigInteger ADD(const BigInteger& other) const;
    BigInteger SUB(const BigInteger& other) const;
    //BigInteger MUL(const BigInteger& other) const;
    // BigInteger DIV(const BigInteger& other) const;
    BigInteger MOD(const BigInteger& other) const;
};

#endif
