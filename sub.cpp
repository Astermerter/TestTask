#include "head.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
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
			if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
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
			if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
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
		cout << "Input digit numbers (4000 >= int >= 1)" << endl;
		cin >> inp_digit;
		if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
	} while (inp_digit < 1 or inp_digit > 4000);
	solution::setDigit(inp_digit);

	int inp_quantity_of_tests;
	do {
		cout << "Input quantity of tests  (10000 >= int >= 1)" << endl;
		cin >> inp_quantity_of_tests;
		if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
	} while (inp_quantity_of_tests < 1 or inp_quantity_of_tests > 10000);
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
		main << "\treg [3:0] buf2\n";
		main << "\talways @(*) begin\n";
		main << "\t\tfor (buf2 =0; buf2 < second_num; buf2++) begin\n";
		main << "\t\t\tsolution = solution + first_num;\n";
		main << "\t\tend\n";
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


void createMainFileToDigitMoreOne(int digit, string file_name)
{
	ofstream main(file_name);

	if (main.is_open())
	{
		main << "module main(\n";
		main << "\tinput [" << (static_cast<long long>((digit+2)*log2(10)) + 1) << ":0] first_num, \n"; // производится расчет сколько бит необходимо для записи любого числа разрядности digit
		main << "\tinput [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] second_num,\n";
		main << "\toutput reg [" << (static_cast<long long>((digit + 2) * 2 * log2(10)) + 1) << ":0] solution\n"; // аналогично, но для произведения 
		main << ");\n";
		main << "\tfunction [" << (static_cast<long long>((digit + 2) * 2 * log2(10)) + 1) << ":0] karatsuba;\n";
		main << "\t\tinput [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] num1;\n";
		main << "\t\tinput [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] num2;\n";
		main << "\t\treg [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] temp_num1;\n";
		main << "\t\treg [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] f1, f2, s1, s2; \n";
		main << "\t\treg [" << (static_cast<long long>((digit + 2) * 2 * log2(10)) + 1) << ":0] p1, p2, p3, p4;\n";
		main << "\t\treg [" << (static_cast<long long>(((digit + 2)+1) * log2(10)) + 1) << ":0] buf1, buf2, i, m, digit_count;\n";
		main << "\t\tbegin\n";
		main << "\t\t\tdigit_count = 0;\n";
		main << "\t\t\ttemp_num1 = num1; \n";
		main << "\t\t\twhile (temp_num1 > 0) begin\n";
		main << "\t\t\t\ttemp_num1 = temp_num1 / 10; \n";
		main << "\t\t\t\tdigit_count = digit_count + 1;\n";
		main << "\t\t\tend\n";
		main << "\t\t\tm = (digit_count) >> 1;\n";
		main << "\t\t\tif (digit_count > 1) begin\n";
		main << "\t\t\t\tbuf1 = 10;\n";
		main << "\t\t\t\tbuf2 = 10;\n";
		main << "\t\t\t\tfor (i = 0; i < m-1; i++) begin\n";
		main << "\t\t\t\t\tbuf1 = (buf1 << 3) + (buf1 << 1); \n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tfor (i = 0; i < (m << 1) - 1; i++) begin\n";
		main << "\t\t\t\t\tbuf2 = (buf2 << 3) + (buf2 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tf2 = num1 % buf1; \n";
		main << "\t\t\t\ts2 = num2 % buf1;\n";
		createSmartDividing(main, digit / 2);
		main << "\t\t\t\tp1 = pf1(f1, s1); \n";
		main << "\t\t\t\tp2 = pf1(f2, s2); \n";
		main << "\t\t\t\tp3 = pf1(f1 + f2, s1 + s2); \n";
		main << "\t\t\t\tp4 = p3 - p2 - p1;\n";
		main << "\t\t\t\tfor (i = 0; i < m; i++) begin\n";
		main << "\t\t\t\t\tp4 = (p4 << 3) + (p4 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tfor (i = 0; i < (m << 1); i++) begin\n";
		main << "\t\t\t\t\tp1 = (p1 << 3) + (p1 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tkaratsuba = p1 + p4 + p2;\n";
		main << "\t\t\tend else begin\n";
		main << "\t\t\t\tkaratsuba = 0;\n";
		main << "\t\t\t\tfor (i = 0; i < num2; i++) begin\n";
		main << "\t\t\t\t\tkaratsuba += num1;\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\tend\n";
		main << "\t\tend\n";
		main << "\tendfunction\n";

		int count = maxIteration(digit);
		int buf;
		/*do {
			buf = maxIteration(digit);
			cout << "Input count of recurs iteration karatsuba algorithm (" << buf << " >= int >= 1)" << endl;
			cin >> count;
			if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
		} while (count < 1 or count > maxIteration(digit));*/
		int i=2;
		for (i = 1; i < count - 1; i++)
			createIteration(main, i, (digit/(pow(2,i-1)) + 1));

		if (count == 1)
			count++;

		main << "\tfunction [" << (static_cast<long long>((2 * ((digit + 2) / (pow(2, i - 2)))) * log2(10)) + 2) << ":0] pf" << count - 1 << ";\n";
		main << "\t\tinput [" << (static_cast<long long>(((digit + 2) / (pow(2, i - 2))) * log2(10)) + 2) << ":0] num1;\n";
		main << "\t\tinput [" << (static_cast<long long>(((digit + 2) / (pow(2, i - 2))) * log2(10)) + 2) << ":0] num2;\n";
		main << "\t\treg [" << (static_cast<long long>(((digit + 2) / (pow(2, i - 2))) * log2(10)) + 2) << ":0] temp_num1;\n";
		main << "\t\treg [" << (static_cast<long long>(((digit + 2) / (pow(2, i - 2))) * log2(10)) + 2) << ":0] f1, f2, s1, s2; \n";
		main << "\t\treg [" << (static_cast<long long>((2 * (digit + 2) / (pow(2, i - 2))) * log2(10)) + 2) << ":0] p1, p2, p3, p4;\n";
		main << "\t\treg [" << (static_cast<long long>(((digit + 2) / (pow(2, i - 2))) * log2(10) + 1) + 2) << ":0] buf1, buf2, i, m, digit_count;\n";
		main << "\t\tbegin\n";
		main << "\t\t\tdigit_count = 0;\n";
		main << "\t\t\ttemp_num1 = num1; \n";
		main << "\t\t\twhile (temp_num1 > 0) begin\n";
		main << "\t\t\t\ttemp_num1 = temp_num1 / 10; \n";
		main << "\t\t\t\tdigit_count = digit_count + 1;\n";
		main << "\t\t\tend\n";
		main << "\t\t\tm = (digit_count) >> 1;\n";
		main << "\t\t\tif (digit_count > 1) begin\n";
		main << "\t\t\t\tbuf1 = 10;\n";
		main << "\t\t\t\tbuf2 = 10;\n";
		main << "\t\t\t\tfor (i = 0; i < m-1; i++) begin\n";
		main << "\t\t\t\t\tbuf1 = (buf1 << 3) + (buf1 << 1); \n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tfor (i = 0; i < (m << 1) - 1; i++) begin\n";
		main << "\t\t\t\t\tbuf2 = (buf2 << 3) + (buf2 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tf1 = num1 / buf1;\n";
		main << "\t\t\t\tf2 = num1 % buf1; \n";
		main << "\t\t\t\ts1 = num2 / buf1; \n";
		main << "\t\t\t\ts2 = num2 % buf1;\n";
		main << "\t\t\t\tp1 = 0;\n";
		main << "\t\t\t\tfor (i = 0; i < s1; i++) begin\n";
		main << "\t\t\t\t\tp1 +=f1;\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tp2 = 0;\n";
		main << "\t\t\t\tfor (i = 0; i < s2; i++) begin\n";
		main << "\t\t\t\t\tp2 +=f2;\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tp3 = 0;\n";
		main << "\t\t\t\tfor (i = 0; i < (s1 + s2); i++) begin\n";
		main << "\t\t\t\t\tp3 +=(f1 + f2);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tp4 = p3 - p2 - p1;\n";
		main << "\t\t\t\tfor (i = 0; i < m; i++) begin\n";
		main << "\t\t\t\t\tp4 = (p4 << 3) + (p4 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tfor (i = 0; i < (m << 1); i++) begin\n";
		main << "\t\t\t\t\tp1 = (p1 << 3) + (p1 << 1);\n";
		main << "\t\t\t\tend\n";
		main << "\t\t\t\tpf" << count - 1 << " = p1 + p4 + p2;\n";
		main << "\t\t\tend else begin\n";
		main << "\t\t\t\tpf" << count - 1 << " = 0;\n";
		createSwitchMultiplication(main, (count - 1));
		main << "\t\t\tend\n";
		main << "\t\tend\n";
		main << "\tendfunction\n";
		main << "\talways @(*) begin\n";
		main << "\t\t\tsolution = karatsuba(first_num, second_num);\n";
		main << "\t\tend\n";
		main << "endmodule\n";

		main.close();
		cout << "File " << file_name << " was created" << endl;
	}
	else
	{
		cout << "Something went wrong..." << endl;
	}
}
void createIteration(ofstream& main, int count, int digit)
{
	main << "\tfunction [" << (static_cast<long long>((2 * (digit + 2 + 2)) * log2(10)) + 2) << ":0] pf" << count << ";\n";
	main << "\t\tinput [" << (static_cast<long long>((digit + 2 + 2) * log2(10)) + 2) << ":0] num1;\n";
	main << "\t\tinput [" << (static_cast<long long>((digit + 2 + 2) * log2(10)) + 2) << ":0] num2;\n";
	main << "\t\treg [" << (static_cast<long long>((digit + 2 + 2)*log2(10)) + 2) << ":0] temp_num1;\n";
	main << "\t\treg [" << (static_cast<long long>((digit + 2 + 2)*log2(10)) + 2) << ":0] f1, f2, s1, s2; \n";
	main << "\t\treg [" << (static_cast<long long>((2 * (digit + 2 + 2)) * log2(10)) + 2) << ":0] p1, p2, p3, p4;\n";
	main << "\t\treg [" << (static_cast<long long>((digit + 2 + 2) * log2(10)) + 2) << ":0] buf1, buf2, i, m, digit_count;\n";
	main << "\t\tbegin\n";
	main << "\t\t\tdigit_count = 0;\n";
	main << "\t\t\ttemp_num1 = num1; \n";
	main << "\t\t\twhile (temp_num1 > 0) begin\n";
	main << "\t\t\t\ttemp_num1 = temp_num1 / 10; \n";
	main << "\t\t\t\tdigit_count = digit_count + 1;\n";
	main << "\t\t\tend\n";
	main << "\t\t\tm = (digit_count) >> 1;\n";
	main << "\t\t\tif (digit_count > 1) begin\n";
	main << "\t\t\t\tbuf1 = 10;\n";
	main << "\t\t\t\tbuf2 = 10;\n";
	main << "\t\t\t\tfor (i = 0; i < m-1; i++) begin\n";
	main << "\t\t\t\t\tbuf1 = (buf1 << 3) + (buf1 << 1); \n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tfor (i = 0; i < (m << 1) - 1; i++) begin\n";
	main << "\t\t\t\t\tbuf2 = (buf2 << 3) + (buf2 << 1);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tf2 = num1 % buf1; \n";
	main << "\t\t\t\ts2 = num2 % buf1;\n";
	createSmartDividing(main, ((digit+2)/2));
	main << "\t\t\t\tp1 = pf" << (count + 1) << "(f1, s1); \n";
	main << "\t\t\t\tp2 = pf" << (count + 1) << "(f2, s2); \n";
	main << "\t\t\t\tp3 = pf" << (count + 1) << "(f1 + f2, s1 + s2); \n";
	main << "\t\t\t\tp4 = p3 - p2 - p1;\n";
	main << "\t\t\t\tfor (i = 0; i < m; i++) begin\n";
	main << "\t\t\t\t\tp4 = (p4 << 3) + (p4 << 1);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tfor (i = 0; i < (m << 1); i++) begin\n";
	main << "\t\t\t\t\tp1 = (p1 << 3) + (p1 << 1);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tpf" << count << " = p1 + p4 + p2;\n";
	main << "\t\t\tend else begin\n";
	main << "\t\t\t\tpf" << count << " = 0;\n";
	createSwitchMultiplication(main, count);
	main << "\t\t\tend\n";
	main << "\t\tend\n";
	main << "\tendfunction\n";
}


void createTestFileToQOT(int quantity_of_test, int digit, string file_name)
{
	ofstream test(file_name);
	bool random_test = 0;
	string first_num, second_num;
	do {
		cout << "Input type of tests (1 - random / 0 - manual entry)" << endl;
		cin >> random_test;
		if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
	} while (random_test != 1 && random_test != 0);
	if (test.is_open())
	{
		test << "module test;\n";
		test << "\treg [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] first_num;\n";
		test << "\treg [" << (static_cast<long long>((digit + 2)*log2(10)) + 1) << ":0] second_num;\n";
		test << "\twire [" << (static_cast<long long>((digit + 2) * 2 * log2(10)) + 1) << ":0] solution; \n";
		test << "\tmain uut(\n";
		test << "\t\t.first_num(first_num),\n";
		test << "\t\t.second_num(second_num),\n";
		test << "\t\t.solution(solution)\n";
		test << "\t);\n";
		test << "\tinitial begin\n";
		if (random_test == 1)
		{
			for (int i = 0; i < quantity_of_test; i++)
				createTest(test, digit, i+1);
		}
		else
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (int i = 0; i < quantity_of_test; i++)
			{
				do {
					cout << "Input first num > 0 and " << digit << " digit, test " << i + 1 << endl; 
					getline(cin, first_num);
					if (first_num.empty()) { cout << "Invalid input. Input cannot be empty. Please try again." << endl; continue; }
					if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
				} while (validator(first_num, digit));
				do {
					cout << "Input second num > 0 and " << digit << " digit, test "<< i+1 << endl; 
					
					getline(cin, second_num);
					if (second_num.empty()) { cout << "Invalid input. Input cannot be empty. Please try again." << endl; continue; }
					if (cin.fail()) { cout << "Invalid input. Please enter a valid integer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
				} while (validator(second_num, digit));
				createTest(test, first_num, second_num, i+1);
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

void createTest(ofstream& test, int digit, int number_of_test) // перегружаю функцию чтобы было удобнее писать
{
	test << "\t\tfirst_num = " << randomNum(digit) << ";\n";
	test << "\t\tsecond_num = "<< randomNum(digit) <<";\n";
	test << "\t\t#10;\n";
	test << "\t\tif (solution == first_num*second_num) begin\n";
	test << "\t\t\t$display(\"Test Passed\"); // test "<< number_of_test <<"\n";
	test << "\t\tend else begin\n";
	test << "\t\t\t$display(\"Test error test " << number_of_test << "\");\n";
	test << "\t\tend\n";
}
void createTest(ofstream &test, string first_num, string second_num, int number_of_test)
{
	test << "\t\tfirst_num = "<< first_num <<";\n";
	test << "\t\tsecond_num = "<< second_num <<";\n";
	test << "\t\t#10;\n";
	test << "\t\tif (solution == first_num*second_num) begin\n";
	test << "\t\t\t$display(\"Test Passed\"); // test " << number_of_test << "\n";
	test << "\t\tend else begin\n";
	test << "\t\t\t$display(\"Test error test " << number_of_test << "\");\n";
	test << "\t\tend\n";
}

string randomNum(int digit)
{
	string num;
	if (digit <= 10)
	{
		long long min_value = pow(10, digit - 1);
		long long max_value = pow(10, digit) - 1;
		random_device rd;
		mt19937 gen(rd()); // генератор случайных чисел на основе алгоритма Mersenne Twister
		uniform_int_distribution<long long> dist(min_value, max_value);
		num = to_string(dist(gen));
	}
	else
	{
		long long min_value = pow(10, 9);
		long long max_value = pow(10, 10) - 1;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<long long> dist(min_value, max_value);
		num = to_string(dist(gen)) + randomNum(digit - 10);
	}

	return num;
}


int maxIteration(int digit) {
	vector<int> arr = { digit, digit }; 
	bool fl = 1;
	int f = 2;
	int s = 0;
	int dop = 2;

	int it = 1; 

	while (fl) {
		fl = 0;
		for (int i = s; i < f; ++i) {
			if (arr[i] > 1) {
				int n1 = arr[i] / 2 + arr[i] % 2;
				int n2 = arr[i] / 2;
				int n3 = max(n1, n2) + 1;

				arr.push_back(n1); arr.push_back(n2); arr.push_back(n3);

				if (n2 > 1)
					fl = 1; 
			}
			else { arr.push_back(0); arr.push_back(0); arr.push_back(0); }
		}
		s = f;
		dop = dop * 3;
		f = f + dop;
		it++;
	}
	it++;
	return it; 
}

bool validator(const string& num, int digit)
{
	bool fl = false;
	for (char c : num)
		if (!isdigit(c))
			fl = true;
	if (num.length() != digit)
		fl = true;
	return fl;
}

void createSwitchMultiplication(ofstream& main, int number_of_iteration)
{
	main << "\t\t\t\tif (num1 == 0) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = 0;\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 1) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = num2;\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 2) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = num2 << 1;\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 3) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = (num2 << 1)+(num2);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 4) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = num2 << 2;\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 5) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = (num2 << 2) + (num2);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 6) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = (num2 << 2) + (num2 << 1);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 7) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = (num2 << 2) + (num2 << 1) + (num2);\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 8) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = num2 << 3;\n";
	main << "\t\t\t\tend\n";
	main << "\t\t\t\tif (num1 == 9) begin\n";
	main << "\t\t\t\t\tpf" << number_of_iteration << " = (num2 << 3) + num2;\n";
	main << "\t\t\t\tend\n";
}

void createSmartDividing(ofstream& main, int digit)
{
	int quantity_of_interation = digit / 19;
	for (int i = 0; i < quantity_of_interation; i++)
	{
		if (i == 0)
			main << "\t\t\t\tif (m > " << quantity_of_interation * 19 << ") begin\n";
		else
			main << "\t\t\t\tend else if (m > " << (quantity_of_interation-i) * 19 << ") begin\n";
		for (int j = 0; j < quantity_of_interation - i; j++)
		{
			if (j == 0)
				main << "\t\t\t\t\tf1 = num1 / 10000000000000000000;\n";
			else
				main << "\t\t\t\t\tf1 = f1 / 10000000000000000000;\n";
		}
		main << "\t\t\t\t\tbuf1 = 10;\n";
		main << "\t\t\t\t\tfor (i = 0; i < m-" << (1 + (quantity_of_interation - i) * 19) << "; i++) begin\n";
		main << "\t\t\t\t\t\tbuf1 = (buf1 << 3) + (buf1 << 1);\n";
		main << "\t\t\t\t\tend\n";
		main << "\t\t\t\t\tf1 = f1 / buf1;\n";

		
	}
	if (quantity_of_interation >= 1)
	{
		main << "\t\t\t\tend else begin\n";
		main << "\t\t\t\t\tf1 = num1 / buf1;\n";
		main << "\t\t\t\tend\n";
	}
	else
		main << "\t\t\t\tf1 = num1 / buf1;\n";
	for (int i = 0; i < quantity_of_interation; i++)
	{
		if (i == 0)
			main << "\t\t\t\tif (m > " << quantity_of_interation * 19 << ") begin\n";
		else
			main << "\t\t\t\tend else if (m > " << (quantity_of_interation - i) * 19 << ") begin\n";
		for (int j = 0; j < quantity_of_interation - i; j++)
		{
			if (j == 0)
				main << "\t\t\t\t\ts1 = num2 / 10000000000000000000;\n";
			else
				main << "\t\t\t\t\ts1 = s1 / 10000000000000000000;\n";
		}
		main << "\t\t\t\t\tbuf1 = 10;\n";
		main << "\t\t\t\t\tfor (i = 0; i < m-" << (1 + (quantity_of_interation - i) * 19) << "; i++) begin\n";
		main << "\t\t\t\t\t\tbuf1 = (buf1 << 3) + (buf1 << 1);\n";
		main << "\t\t\t\t\tend\n";
		main << "\t\t\t\t\ts1 = s1 / buf1;\n";
		
	}
	if (quantity_of_interation >= 1)
	{
		main << "\t\t\t\tend else begin\n";
		main << "\t\t\t\t\ts1 = num2 / buf1;\n";
		main << "\t\t\t\tend\n";
	}
	else
		main << "\t\t\t\ts1 = num2 / buf1;\n";
}