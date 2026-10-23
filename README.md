# Arbitrary Precision Calculator

A program that can perform computation on numbers with any number of digits. The numbers must be passed to the program as command line arguments along with the desired operation. The following operators are supported :
* ### Addition : </br>
  **Format** : *number_1* + *number_2* </br>
  Example : 2901 + 9922
* ### Subtraction : </br>
  **Format** : *number_1* - *number_2* </br>
  Example : 2901 - 9922
* ### Multiplication : </br>
  **Format** : *number_1* X *number_2* </br>
  Example : 2901 X 9922
* ### Division : </br>
  **Format** : *number_1* / *number_2* </br>
  Example : 2901 / 9922
* ### Modulo : </br>
  **Format** : *number_1* % *number_2* </br>
  Example : 100 % 3
* ### Exponentiation : </br>
  **Format** : *number_1* ^ *number_2* </br>
  Example : 222 ^ 8

## Limitations
The program comes with following limitations:
+ The program only accepts positive integers.
+ Expressions with multiple operands and symbols are not allowed.

## Building
The build process for this project is managed by make. Upon building, a directory called *make-build* created which must contain the output binary for this project. It is named *ArbitraryPrecisionCalculator*. Furthermore, to properly build this project you must execute the make target *all*.
