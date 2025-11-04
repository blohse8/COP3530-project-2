// Written by Landen Parke, 11.2.25

#include "terminal.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void printLogo() {
    std::vector<std::string> logo = {
        "[38;5;151m                            ,,                              [39m",
        "[38;5;151m`7MMF'     A     `7MF'     *MM   MMP\"\"MM\"\"YMM               [39m",
        "[38;5;151m  `MA     ,MA     ,V        MM   P'   MM   `7               [39m",
        "[38;5;151m   VM:   ,VVM:   ,V .gP\"Ya  MM,dMMb.  MM  ,pW\"Wq.`7MMpdMAo. [39m",
        "[38;5;108m    MM.  M' MM.  M',M'   Yb MM    `Mb MM 6W'   `Wb MM   `Wb [39m",
        "[38;5;108m    `MM A'  `MM A' 8M\"\"\"\"\"\" MM     M8 MM 8M     M8 MM    M8 [39m",
        "[38;5;108m     :MM;    :MM;  YM.    , MM.   ,M9 MM YA.   ,A9 MM   ,AP [39m",
        "[38;5;108m      VF      VF    `Mbmmd' P^YbmdP'.JMML.`Ybmd9'  MMbmmd'  [39m",
        "[38;5;108m                                                   MM       [39m",
        "[38;5;108m                                                 .JMML.     [39m"
                    
    };
    printFrame();
    for (auto line: logo) {
        std::cout << "∥" << std::right << std::setw(95) << line << std::right << std::setw(26) << "∥" << std::endl;
    }
    printFrame();
}

void printFrame() {
    std::cout << "========================================================================================================" << std::endl;
}

void printFrameDash() {
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
}