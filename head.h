#ifndef sub
#define sub

#include <string>
#include <fstream> 
using namespace std;

class solution {
public:
    solution(); // ���������������� ������������
    solution(int inp_digit, int inp_quantity_of_tests);

    int getDigit(); // ������� / ������� ��� ��������� ���������� 
    int getQuantityOfTest();
    void setDigit(int inp_digit = -1);
    void setQuantityOfTests(int inp_quantity_of_tests = -1);

    void createMainFile(std::string file_name = "main.v"); // ������� ���� ������ file_name.v ���� �� ������ ������ �������
    void createTestFile(std::string file_name = "test.v"); // ������� ���� ������������ file_name.v ���� �� ������ ������ �������
    void createFiles(std::string main_file_name = "main.v", std::string test_file_name = "test.v"); // ������� ��� ����� � ���������� ���� ������ main_file_name.v � ���� ������������ test_file_name.v �� ������ �������

    void terminalInterface(); // ���������� ����� ������ � �������� ����� �������

private:
    int digit; // 0-inf
    int quantity_of_tests; // 0-inf
};


void createMainFileToDigitOne(std::string file_name); // ������� ���� ������ file_name.v ���� �� ������ ������ ������� ��� ����������� 1
void createMainFileToDigitMoreOne(int digit, std::string file_name);// ������� ���� ������ file_name.v ���� �� ������ ������ ������� ��� ����� ����������� digit
void createTestFileToQOT(int quantity_of_test, int digit, std::string file_name = "test.v"); // ������� file_name.v ���� �� ������ ������ ������� ��� ����������� 1
void createTest(std::ofstream& test, int digit); // ������� ���� ���� �� ���������� ������� ����������� digit ��� ����� ������������ test
void createTest(std::ofstream& test, long long first_num, long long second_num);// ������� ���� ���� � ����������� ����� ������� ������� ����������� digit ��� ����� ������������ test
long long randomNum(int digit); // ���������� ��������� ����� ����������� digit

#endif // !sub
