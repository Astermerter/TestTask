#ifndef sub
#define sub

#include <string>
#include <fstream> 
using namespace std;

class solution {
public:
    solution(); // инициализирующие конструкторы
    solution(int inp_digit, int inp_quantity_of_tests);

    int getDigit(); // геттеры / сеттеры для приватных переменных 
    int getQuantityOfTest();
    void setDigit(int inp_digit = -1);
    void setQuantityOfTests(int inp_quantity_of_tests = -1);

    void createMainFile(std::string file_name = "main.v"); // создает файл логики file_name.v файл на основе данных объекта
    void createTestFile(std::string file_name = "test.v"); // создает файл тестирования file_name.v файл на основе данных объекта
    void createFiles(std::string main_file_name = "main.v", std::string test_file_name = "test.v"); // создает два файла с названиями файл логики main_file_name.v и файл тестирования test_file_name.v по данным объекта

    void terminalInterface(); // активирует режим работы с объектом через консоль

private:
    int digit; // 0-inf
    int quantity_of_tests; // 0-inf
};


void createMainFileToDigitOne(std::string file_name); // создает файл логики file_name.v файл на основе данных объекта для размерности 1
void createMainFileToDigitMoreOne(int digit, std::string file_name);// создает файл логики file_name.v файл на основе данных объекта для любой размерности digit
void createTestFileToQOT(int quantity_of_test, int digit, std::string file_name = "test.v"); // создает file_name.v файл на основе данных объекта для размерности 1
void createTest(std::ofstream& test, int digit, int number_of_test); // создает один тест со случайными числами размерности digit для файла тестирования test
void createTest(std::ofstream& test, string first_num, string second_num, int number_of_test);// создает один тест с задаваемыми через консоль числами размерности digit для файла тестирования test
string randomNum(int digit); // возвращает случайное число размерности digit
void createIteration(ofstream& main, int count, int digit); // создание одной дополнительной итерации рекурсии алгоритма карацубы
int maxIteration(int digit); // определение максимальной итерации для выполнения алгоритма карацубы (больше чем на это количество итераций невозможно опуститься)
bool validator(const string& num, int digit); // проверяет, является ли введенная пользователем строка числом
void createSwitchMultiplication(ofstream& main, int number_of_iteration);
void createSmartDividing(ofstream& main, int digit);

#endif // !sub
