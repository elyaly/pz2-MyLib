
#include <iostream>
#include "..\\MyLib\Header.h"

int main() {
    // 1. Реалізація власного типу даних великого числа
    BigInteger bigInt;

    // Введення числа в десятковій формі
    std::string decimalValue = "12345678901234567890";

    // Встановлення числа з десяткового рядка
    bigInt.setDecimal(decimalValue);

    // Отримання числа у шістнадцятковій системі
    std::string hexValue = bigInt.getHex();

    std::cout << "Вхідне значення у десятковій формі: " << decimalValue << std::endl;
    std::cout << "Значення, зчитане із об'єкту у шістнадцятковій системі: " << hexValue << std::endl;

    
    // 2. Реалізація побітових операцій
    BigInteger numberA;
    BigInteger numberB;
    BigInteger numberC;

    numberA.setHex("51bf608414ad5726a3c1bec098f77b1b54ffb2787f8d528a74c1d7fde6470ea4");
    numberB.setHex("403db8ad88a3932a0b7e8189aed9eeffb8121dfac05c3512fdb396dd73f6331c");

    numberC = numberA.XOR(numberB);

    std::cout << "XOR result: " << numberC.getHex() << std::endl;
    
    
    // 3. Реалізація арифметичних операцій
    // Тестові приклади для операцій ADD і SUB
    BigInteger numberD;
    BigInteger numberE;
    BigInteger numberF;

    numberD.setHex("36f028580bb02cc8272a9a020f4200e346e276ae664e45ee80745574e2f5ab80");
    numberE.setHex("70983d692f648185febe6d6fa607630ae68649f7e6fc45b94680096c06e4fadb");

    numberF = numberD.ADD(numberE);
    std::cout << "ADD result: " << numberF.getHex() << std::endl;

    numberF = numberD.SUB(numberE);
    std::cout << "SUB result: " << numberF.getHex() << std::endl;
    return 0;
}