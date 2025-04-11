#include <iostream>
#include "constants.h"
#include "CNumber.h"

int main() {
    std::cout << "zad2: \n";

    CNumber c_num_0, c_num_1;
    c_num_0 = 368;
    c_num_1 = 1567;
    
    std::cout << "Przed c_num_0 = c_num_1: \n";
    std::cout << "c_num_0: ";
    c_num_0.printCNumber();
    std::cout << "\n";
    std::cout << "c_num_1: ";
    c_num_1.printCNumber();
    std::cout << "\n";

    std::cout << "\n";

    c_num_0 = c_num_1;

    std::cout << "Po c_num_0 = c_num_1: \n";
    std::cout << "c_num_0: ";
    c_num_0.printCNumber();
    std::cout << "\n";
    std::cout << "c_num_1: ";
    c_num_1.printCNumber();
    std::cout << "\n";

    /*
    zad2: program nie zakonczyl sie, bo oba obiekty wskazuja na ta sama tablice zaalokowana dynamicznie i przy wywolaniu
          destruktora na koncu dzialania programu doszlo do nieudanej proby podwojnego zwolnienia pamieci
    zad3: program zakonczyl sie, bo destruktor usuwajacy wskaznik na tablice zostal usuniety, wiec nie bylo proby
          podwojnego zwolnienia pamieci, lecz dochodzi wtedy do wycieku pamieci
    */

    std::cout << "\n";

    std::cout << "zad6: \n";
    CNumber c_num_2, c_num_3, c_num_4, c_num_5, c_num_6, c_num_7, c_num_8, c_num_9, c_num_10, c_num_11;
    c_num_2 = 29;
    std::cout << "c_num_2: ";
    c_num_2.printCNumber();
    std::cout << "\n"; 
    
    c_num_3 = c_num_2  - 16;
    std::cout << "c_num_3: ";
    c_num_3.printCNumber();
    std::cout << "\n"; 
   
    std::cout << c_num_2.sToStr() << "+" << c_num_3.sToStr() << "=";
    c_num_4 = c_num_2 + c_num_3;
    c_num_4.printCNumber();
    std::cout << "\n";

    std::cout << c_num_2.sToStr() << "-" << c_num_3.sToStr() << "=";
    c_num_5 = c_num_2 - c_num_3;
    c_num_5.printCNumber();
    std::cout << "\n";

    std::cout << c_num_2.sToStr() << "*" << c_num_3.sToStr() << "=";
    c_num_6 = c_num_2 * c_num_3;
    c_num_6.printCNumber();
    std::cout << "\n";

    std::cout << c_num_2.sToStr() << "/" << c_num_3.sToStr() << "=";
    c_num_7 = c_num_2 / c_num_3;
    c_num_7.printCNumber();
    std::cout << "\n";

    std::cout << "\n";

    //mod2
    std::cout << "mod2: \n" << "! CNumber wyswietlane za pomoca operatora '<<' ! \n";

    unsigned int u = 2;
    c_num_8 = 732;
    c_num_9 = c_num_8 << u;
    std::cout << c_num_8 << "<<" << u << "U=" << c_num_9 << "\n";

    c_num_10 = 1;
    c_num_11 = c_num_8 << c_num_10;
    std::cout << c_num_8 << "<<" << c_num_10 << "=" << c_num_11 << "\n";
    //mod2
}


