#include "head.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;

solution::solution()
{
	digit = 1;
	quantity_of_tests = 1;
}
solution::solution(int inp_digit, int inp_quantity_of_tests)
{
	if (inp_digit > 0)
		digit = inp_digit;
	else
		digit = 1;

	if (inp_quantity_of_tests > 0)
		quantity_of_tests = inp_quantity_of_tests;
	else
		quantity_of_tests = 1;
}

int solution::getDigit()
{
	return digit;
}
int solution::getQuantityOfTest()
{
	return quantity_of_tests;
}
void solution::setDigit(int inp_digit)
{
	if (inp_digit < 1)
	{
		do {
			cout << "Input digit numbers (int > 0)" << endl;
			cin >> digit;
		} while (digit < 0);
	}
	else
		digit = inp_digit;

}
void solution::setQuantityOfTests(int inp_quantity_of_tests)
{
	if (quantity_of_tests < 1)
	{
		do {
			cout << "Input quantity of tests  (int > 0)" << endl;
			cin >> quantity_of_tests;
		} while (quantity_of_tests < 0);
	}
	else
		quantity_of_tests = inp_quantity_of_tests;
}


void solution::createMainFile(string file_name)
{
	int digit = solution::getDigit();
	if (digit == 1)
		createMainFileToDigitOne(file_name);
	else if (digit > 1)
		createMainFileToDigitMoreOne(digit, file_name);
	else
		cout << "Please, rebind digit from " << digit << " to digit > 0" << endl;
}

void solution::createTestFile(string file_name)
{
	int quantity_of_tests = solution::getQuantityOfTest();
	int digit = solution::getDigit();

	if (quantity_of_tests > 0)
		if (digit > 0)
			createTestFileToQOT(quantity_of_tests, digit, file_name);
		else
			cout << "Please, rebind digit from " << digit << " to digit > 0" << endl;
	else
		cout << "Please, rebind quantity_of_tests from " << quantity_of_tests << " to quantity_of_tests > 0" << endl;
}

void solution::createFiles(std::string main_file_name, std::string test_file_name)
{
	solution::createMainFile(main_file_name);
	solution::createTestFile(test_file_name);
}

void solution::terminalInterface()
{
	cout << "Welcome to Verilog file generator" << endl;
	/*cout << "Input \"input_file_name.v\" (if you want to use \"main.v\" just press Enter)" << endl;
	string answer;
	getline(cin, answer);
	if (answer.empty())
		answer = "main.v";
	cout << "Input \"test_file_name.v\" (if you want to use \"test.v\" just press Enter)" << endl;
	string answer2;
	getline(cin, answer2);
	if (answer2.empty())
		answer2 = "test.v";*/
	int inp_digit;
	do {
		cout << "Input digit numbers (int > 0)" << endl;
		cin >> inp_digit;
	} while (inp_digit < 0);
	solution::setDigit(inp_digit);

	int inp_quantity_of_tests;
	do {
		cout << "Input quantity of tests  (int > 0)" << endl;
		cin >> inp_quantity_of_tests;
	} while (inp_quantity_of_tests < 0);
	solution::setQuantityOfTests(inp_quantity_of_tests);

	solution::createFiles();
}

// =============================================================

void createMainFileToDigitOne(string file_name)
{
	ofstream main(file_name);

	if (main.is_open())
	{
		main << "module main(\n";
		main << "\tinput [3:0] first_num,\n";
		main << "\tinput [3:0] second_num,\n";
		main << "\toutput reg [6:0] solution\n";
		main << ");\n";
		main << "\talways @(*) begin\n";
		main << "\t\tsolution = first_num * second_num;\n";
		main << "\tend\n";
		main << "endmodule\n";
		main.close();
		cout << "File " << file_name << " was created" << endl;
	}
	else
	{
		cout << "Something went wrong..." << endl;
	}
}
void createMainFileToDigitMoreOne(int digit,string file_name)
{
	ofstream main(file_name);

	if (main.is_open())
	{
		main << "module main(\n";
		main << "\tinput ["<< (int(log2(pow(10, digit)))+1) <<":0] first_num, \n"; // производится расчет сколько бит необходимо для записи любого числа разрядности digit
		main << "\tinput ["<< (int(log2(pow(10, digit))) + 1) <<":0] second_num,\n";
		main << "\toutput reg ["<< (int(log2(pow(10, 2*(digit)))) + 1) <<":0] solution\n"; // аналогично, но для произведения 
		main << ");\n";
		main << "\treg ["<< (int(log2(digit)) + 1) <<":0] n = "<< digit <<";\n";
		main << "\treg ["<< (int(log2(int(digit/2))) + 1) <<":0] m;\n";
		main << "\treg ["<< (digit % 2 ? (int(log2(pow(10, (int(digit / 2) + 1)))) + 1) : (int(log2(pow(10, (int(digit / 2))))) + 1)) <<":0] F_F_P;\n"; // =( сложное выражение для того чтобы правильно выделить память для вспомогательных переменных
		main << "\treg ["<< (digit % 2 ? (int(log2(pow(10, (int(digit / 2) + 1)))) + 1) : (int(log2(pow(10, (int(digit / 2))))) + 1)) <<":0] F_S_P;\n";
		main << "\treg ["<< (digit % 2 ? (int(log2(pow(10, (int(digit / 2) + 1)))) + 1) : (int(log2(pow(10, (int(digit / 2))))) + 1)) <<":0] S_F_P;\n";
		main << "\treg ["<< (digit % 2 ? (int(log2(pow(10, (int(digit / 2) + 1)))) + 1) : (int(log2(pow(10, (int(digit / 2))))) + 1)) <<":0] S_S_P;\n";
		main << "\treg ["<< (int(log2(pow(10, digit + 1))) + 1) <<":0] p1;\n";
		main << "\treg ["<< (int(log2(pow(10, digit + 1))) + 1) <<":0] p2;\n";
		main << "\treg ["<< (int(log2(pow(10, ((digit + 1) / 2 + 1) * 2))) + 1) <<":0] p3;\n";
		main << "\treg ["<< (int(log2(pow(10, ((digit + 1) / 2 + 1) * 2))) + 1) <<":0] p4;\n";
		main << "\treg ["<< (int(log2(pow(10, (digit / 2)))) + 1) <<":0] buf1;\n"; // вычисление правильного количества памяти на вспомогательные переменные
		main << "\treg ["<< (int(log2(pow(10, digit))) + 1) <<":0] buf2;\n";
		main << "\treg ["<< (int(log2(int(digit / 2))) + 1) <<":0] i;\n";
		main << "\talways @(*) begin\n";
		main << "\t\tm = n >> 1;\n";
		main << "\t\tsolution = 0;\n";
		main << "\t\tbuf1 = 10;\n";
		main << "\t\tbuf2 = 10;\n";
		main << "\t\tfor (i = 0; i < m - 1; i++) begin\n";
		main << "\t\t\tbuf1 = buf1 * 10;\n";
		main << "\t\tend\n";
		main << "\t\tfor (i = 0; i < 2 * m - 1; i++) begin\n";
		main << "\t\t\tbuf2 = buf2 * 10;\n";
		main << "\t\tend\n";
		main << "\t\tF_F_P = first_num / buf1;\n";
		main << "\t\tF_S_P = first_num % buf1;\n";
		main << "\t\tS_F_P = second_num / buf1;\n";
		main << "\t\tS_S_P = second_num % buf1;\n";
		main << "\t\tp1 = F_F_P * S_F_P;\n";
		main << "\t\tp2 = F_S_P * S_S_P;\n";
		main << "\t\tp3 = (F_F_P + F_S_P)*(S_F_P + S_S_P);\n";
		main << "\t\tp4 = p3 - p2 - p1;\n";
		main << "\t\tsolution = p1 * buf2 + p4 * buf1 + p2;\n";
		main << "\tend\n";
		main << "endmodule\n";
		main.close();
		cout << "File " << file_name << " was created" << endl;
	}
	else
	{
		cout << "Something went wrong..." << endl;
	}
}


void createTestFileToQOT(int quantity_of_test, int digit, string file_name)
{
	ofstream test(file_name);
	bool random_test = 0;
	long long first_num, second_num;

	cout << "Input type of tests (1 - random / 0 - manual entry)" << endl;
	cin >> random_test;
	
	if (test.is_open())
	{
		test << "module test;\n";
		test << "\treg ["<< (int(log2(pow(10, digit))) + 1) <<":0] first_num;\n";
		test << "\treg ["<< (int(log2(pow(10, digit))) + 1) <<":0] second_num;\n";
		test << "\twire ["<< (int(log2(pow(10, 2 * (digit)))) + 1) <<":0] solution;\n";
		test << "\tmain uut(\n";
		test << "\t\t.first_num(first_num),\n";
		test << "\t\t.second_num(second_num),\n";
		test << "\t\t.solution(solution)\n";
		test << "\t);\n";
		test << "\tinitial begin\n";
		if (random_test == 1)
		{
			for (int i = 0; i < quantity_of_test; i++)
				createTest(test, digit);
		}
		else
		{
			for (int i = 0; i < quantity_of_test; i++)
			{
				do {
					cout << "Input first num > 0 and " << digit << " digit" << endl;
					cin >> first_num;
				} while (pow(10, digit - 1) > first_num || first_num > pow(10,digit) - 1);
				do {
					cout << "Input second num > 0 and " << digit << " digit" << endl;
					cin >> second_num;
				} while (pow(10, digit - 1) > second_num || second_num > pow(10, digit) - 1);
				createTest(test, first_num, second_num);
			}
		}
		test << "\tend\n";
		test << "endmodule\n";

		test.close();
		cout << "File " << file_name << " was created" << endl;
	}
	else
	{
		cout << "Something went wrong..." << endl;
	}
}

void createTest(ofstream& test, int digit) // перегружаю функцию чтобы было удобнее писать
{
	int buf = randomNum(digit);
	test << "\t\tfirst_num = " << buf << ";\n";
	buf = randomNum(digit);
	test << "\t\tsecond_num = "<< buf <<";\n";
	test << "\t\t#10;\n";
	test << "\t\t$display(\"solution %d * %d is %d\", first_num, second_num, solution);\n";
}
void createTest(ofstream &test, long long first_num, long long second_num)
{
	test << "\t\tfirst_num = "<< first_num <<";\n";
	test << "\t\tsecond_num = "<< second_num <<";\n";
	test << "\t\t#10;\n";
	test << "\t\t$display(\"solution %d * %d is %d\", first_num, second_num, solution);\n";
}

long long randomNum(int digit)
{
	long long min_value = pow(10, digit - 1);
	long long max_value = pow(10, digit) - 1;
	random_device rd;
	mt19937 gen(rd()); // генератор случайных чисел на основе алгоритма Mersenne Twister
	uniform_int_distribution<> dist(min_value, max_value); 

	return dist(gen);
}