#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include <windows.h>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::ofstream;
using std::to_string;

std::mutex mtx;

string getHorario(){    //Pega o horario atual em formato de string
    auto t = std::time(nullptr);    //Peguei do stack overflow
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "Dia: %d-%m-%Y Horario: %H:%M:%S");
    auto str = oss.str();
    return str;
}