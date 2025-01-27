#include <iostream>
#include "mathlibrary.h"

int main(int argc, char**argv){
    int number = argc;
    double sqrtnumber = mysqrt(number);
    double sq_sqrtnumber = square(sqrtnumber);
    std::cout<<"answer "<<number<<sqrtnumber<<sq_sqrtnumber;
}
