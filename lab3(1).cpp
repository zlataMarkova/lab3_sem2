// lab3(1).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
using namespace std;
#include <string>
#include <stack>
#include <cstdlib>
struct Stack
{
	char symb;
	Stack* next = 0;
};
int Prior(char symb)
{
	switch (symb) {
	case '(':
		return 1;
	case '+': case '-':
		return 2;
	case '*': case '/':
		return 3;
	default: return 0;
	}
}
Stack *In(Stack *p, char symb)//записывает на стек(на веpшину котоpого указывает HEAD) символ a.Возвpащает указатель на новую веpшину стека
{
	Stack *curr = new Stack;
	curr->symb = symb;
	curr->next = p;
	return curr;
}

char Out(Stack **head)//удаляет символ с веpшины стека.Возвpащает удаляемый символ. Изменяет указатель на веpшину стека
{
	Stack *curr;
	char a;
	if (*head == NULL) return '\0';
	curr = *head;
	a = curr->symb;
	*head = curr->next;
	free(curr);
	return a;
}
void OPN(char *in, char *out) {
	Stack *stck = NULL;
	int i = 0, j = 0;
	int n = strlen(in);
	while (in[i] != '\0' && in[i] != '=') {
		if (isdigit(in[i]))
		{
			out[j] = in[i];
			if (!(isdigit(in[i + 1])))
			{
				out[j + 1] = ' ';
				j++;
			}
			j++;
		}
		if (in[i] <= 'z' and in[i] >= 'a')
		{
			cout << "Введите значение " << in[i] << ":";
			char perem[100] = { 0 };
			cin >> perem;
			for (int k = 0; k < strlen(perem); k++)
			{
				out[j] = perem[k];
				j++;
			}
			if (!(isdigit(in[i + 1])))
			{
				out[j] = ' ';
				j++;
			}
		}
		if (in[i] == '+' or in[i] == '-' or in[i] == '*' or in[i] == '/')
		{
			if (stck == NULL or Prior(stck->symb) < Prior(in[i]))
				stck = In(stck, in[i]);
			else
			{
				while (stck != NULL && (Prior(stck->symb) >= Prior(in[i])))
				{
					out[j] = Out(&stck);
					j++;
				}
				stck = In(stck, in[i]);
			}
		}
		if (in[i] == '(') {
			stck = In(stck, '(');
		}
		if (in[i] == ')')
		{
			while ((stck->symb) != '(')
			{
				out[j] = Out(&stck);
				j++;
			}
			Out(&stck);
		}
		i++;
	}
	if (isdigit(in[i]) and (in[i + 1] == '+' or in[i + 1] == '*' or in[i + 1] == '-' or in[i + 1] == '/'))
		out[i + 1] = ' ';
	while (stck != NULL)
	{
		out[j] = Out(&stck);
		j++;
	}
	int count_num1 = 0;
	int count_operat1 = 0;
	n = strlen(out);
	for (int i = 0; i < n; i++)
	{
		if (out[i] == ' ')
			count_num1++;
		if (out[i] == '+' or out[i] == '-' or out[i] == '*' or out[i] == '/')
			count_operat1++;
	}
	if (count_num1 - count_operat1 == 1 and (out[n-1] == '+' or out[n-1] == '-' or out[n-1] == '*' or out[n-1] == '/') and isdigit(out[0]))
	{
		cout << "Выражение верно!";
		cout << "\n";
		cout << out;
	}
	else
		cout << "Выражение не верно!";
}

void PPN(char *in, char *out, char *rever1)
{
	int j = 0;
	char rever[100] = { 0 };
	char values[100] = { 0 };
	int i = 0;
	while (in[i] != '\0' && in[i] != '=')
	{
		if (in[i] <= 'z' and in[i] >= 'a')
		{
			cout << "Введите значение " << in[i] << ":";
			char perem[100] = { 0 };
			cin >> perem;
			for (int k = 0; k < strlen(perem); k++)
			{
				values[j] = perem[k];
				j++;
			}
		}
		if (!(in[i] <= 'z' and in[i] >= 'a'))
		{
			
			values[j] = in[i];
			j++;
		}
		i++;
	}
	//cout << "\n" << values << "\n";
	int n = strlen(values);
	//cout << n;
	j = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (values[i] == '(')
			rever[j] = ')';
		if (values[i] == ')')
			rever[j] = '(';
		if (values[i] != ')' and values[i] != '(')
			rever[j] = values[i];
		j++;
	}
	//cout << "\n" << rever << "\n";
	Stack *stck = NULL;
	i = 0;
	j = 0;
	while (rever[i] != '\0' && rever[i] != '=') {
		if (isdigit(rever[i])) {
			out[j] = rever[i];
			if (!(isdigit(rever[i + 1])))
			{
				out[j + 1] = ' ';
				j++;
			}
			j++;
		}
		if (rever[i] == '+' or rever[i] == '-' or rever[i] == '*' or rever[i] == '/')
		{
			if (stck == NULL or Prior(stck->symb) < Prior(rever[i]))
				stck = In(stck, rever[i]);
			else
			{
				while (stck != NULL && (Prior(stck->symb) >= Prior(rever[i])))
				{
					out[j] = Out(&stck);
					j++;
				}
				stck = In(stck, rever[i]);
			}
		}
		if (rever[i] == '(') {
			stck = In(stck, '(');
		}
		if (rever[i] == ')')
		{
			while ((stck->symb) != '(')
			{
				out[j] = Out(&stck);
				j++;
			}
			Out(&stck);
		}
		i++;
	}
	while (stck != NULL)
	{
		out[j] = Out(&stck);
		j++;
	}
	//cout << "\n" << out << "\n";
	j = 0;
	
	n = strlen(out);
	for (int i = n - 1; i >= 0; i--)
	{
		rever1[j] = out[i];
		j++;
	}
	int count_num = 0;
	int count_operat = 0;
	n = strlen(rever1);
	for (int i = 0; i < n; i++)
	{
		if (rever1[i] == ' ')
			count_num++;
		if (rever1[i] == '+' or rever1[i] == '-' or rever1[i] == '*' or rever1[i] == '/')
			count_operat++;
	}
	if (count_num - count_operat == 1 and (rever1[0] == '+' or rever1[0] == '-' or rever1[0] == '*' or rever1[0] == '/') and  isdigit(rever1[n-1]))
	{
		cout << "Выражение верно!";
		cout << "\n";
		cout << rever1;
	}
	else
		cout << "Выражение не верно!";
}
float Math(char sign, float s1, float s2) {
	switch (sign) {
	case '+':
		cout << (s1 + s2) << endl;
		return s1 + s2;
	case '-':
		cout << (s1 - s2) << endl;
		return s1 - s2;
	case '*':
		cout << (s1 * s2) << endl;
		return s1 * s2;
	case '/':
		cout << (s1 / s2) << endl;
		return s1 / s2;
	}
}
void OPNCount(string& out) {
	stack <float> stackOut;
	string num;
	float s1, s2;
	int i = 0, x;
	while (out[i] != '\0') {
		if (out[i] == ' ') i++;
		else if (isdigit(out[i])) {
			num += out[i];
			i++;
			while (isdigit(out[i])) {
				num += out[i];
				i++;
			}
			x = stoi(num);
			stackOut.push(x);
			num.clear();
		}
		else if (out[i] == '+' || out[i] == '-' || out[i] == '*' || out[i] == '/') {
			s2 = stackOut.top();
			stackOut.pop();
			s1 = stackOut.top();
			stackOut.pop();
			cout << s1 << out[i] << s2 << " = ";
			stackOut.push(Math(out[i], s1, s2));
			i++;
		}
	}
	cout << "Ответ: " << stackOut.top() << endl;
}
void PPNCount(string& out) {
	stack <float> stackOut;
	string num;
	float s1, s2;
	int i = 0, x;
	reverse(out.begin(), out.end());
	while (out[i] != '\0') {
		if (isdigit(out[i])) {
			while (out[i] != ' ')
			{
				num += out[i];
				i++;
			}
			reverse(num.begin(), num.end());
			x = stoi(num);
			stackOut.push(x);
			num.clear();
		}
		else if (out[i] == '+' || out[i] == '-' || out[i] == '*' || out[i] == '/') {
			s1 = stackOut.top();
			stackOut.pop();
			s2 = stackOut.top();
			stackOut.pop();
			cout << s1 << out[i] << s2 << " = ";
			stackOut.push(Math(out[i], s1, s2));
			i++;
		}
		else if (out[i] == ' ') i++;
	}
	reverse(out.begin(), out.end());
	cout << "Ответ: " << stackOut.top() << endl;
}
void CountNot(string &in, char *out)
{
	int i = 0;
	int j = 0, x;
	while (in[i] != '\0' && in[i] != '=') {
		if (in[i] <= 'z' and in[i] >= 'a')
		{
			cout << "Введите значение " << in[i] << ":";
			char perem[100] = { 0 };
			cin >> perem;
			for (int k = 0; k < strlen(perem); k++)
			{
				out[j] = perem[k];
				j++;
			}
			if (!(isdigit(in[i + 1])))
			{
				out[j] = ' ';
				j++;
			}
		}
		else 
		{
			if (isdigit(in[i]))
			{
				out[j] = in[i];
				if (!(isdigit(in[i + 1])))
				{
					out[j+1] = ' ';
					j++;
				}
			}
			else if (!(isdigit(in[i])))
				out[j] = in[i];
			j++;
		}
		
		i++;
	}

	cout << out<<"\n";
	string str = string(out);
	//cout << str.size();
	stack <float> stackNum;
	stack <char> stackOper;
	string num;
	char oper;
	float s1, s2;
	i = 0;
	while (str[i] != '\0')
	{

		
		if (isdigit(str[i])) 
		{
			num += str[i];
			//cout << num<<"x\n";
			//cout << str[i]<<"\n";
			i++;
			while (isdigit(str[i])) {
				num += str[i];
				i++;
			}
			x = stoi(num);
			//cout << x;
			stackNum.push(x);
			num.clear();
		}
		else if (str[i] == ' ')
		{
			//cout << i<<"\n";
			i++;
		}
		
		else if (str[i] == '+' or str[i] == '-' or str[i] == '*' or str[i] == '/')
		{
			//cout << str[i]<<"a";
			//cout << Prior(stackOper.top())<<"Aaa\n"<<stackOper.top()<<"\n";
			if (stackOper.empty() || (Prior(stackOper.top()) < Prior(str[i])))
			{
				//cout << str[i]<<"n";
				stackOper.push(str[i]);
				//cout << stackOper.top();
				i++;
			}
			else {
				//cout << "[ei";
				s2 = stackNum.top();
				stackNum.pop();
				s1 = stackNum.top();
				stackNum.pop();
				oper = stackOper.top();
				stackOper.pop();
				cout << s1 << oper << s2 << " = ";
				stackNum.push(Math(oper, s1, s2));
				stackOper.push(str[i]);
				i++;
			}
		}
		else if (str[i] == '(')
		{
			stackOper.push(str[i]);
			//cout << stackOper.top();
			i++;
		}

		else if (str[i] == ')')
		{
			s2 = stackNum.top();
			stackNum.pop();
			s1 = stackNum.top();
			//cout << stackNum.top();
			stackNum.pop();
			oper = stackOper.top();
			stackOper.pop();
			cout << s1 << oper << s2 << " = ";
			stackNum.push(Math(oper, s1, s2));
			//cout << stackOper.top();
			if (stackOper.top() == '(')
				stackOper.pop();
			//cout << stackOper.top()<<"e";
			i++;
		}
	}
	
	while (!(stackOper.empty()))
	{
		if (stackOper.top() == '(')
			stackOper.pop();
		//cout << "d";
		s2 = stackNum.top();
		stackNum.pop();
		s1 = stackNum.top();
		stackNum.pop();
		oper = stackOper.top();
		stackOper.pop();
		cout << s1 << oper << s2 << " = ";
		stackNum.push(Math(oper, s1, s2));
		i++;
	}
	//cout << stackNum.top();
	cout << "Ответ:" << stackNum.top();
	
}
int main()
{
	setlocale(0, "");
	char in[100] = { 0 };
	char out[100] = { 0 };
	char rever1[100] = { 0 };
	Stack* stck = NULL;
	int i = 0, j = 0;
	cout << "Введите выражение: ";
	gets_s(in);
	int count_num2 = 0, count_operat2 = 0;
	int count_brackets1 = 0, count_brackets2 = 0;
	int m = strlen(in);
	int zero = 0;
	for (int i = 0; i < m; i++)
	{
		if (in[i] == '+' or in[i] == '-' or in[i] == '*' or in[i] == '/')
		{
			count_operat2++;
		}
		if (((isdigit(in[i])) or (in[i] <= 'z' and in[i] >= 'a')) and !(isdigit(in[i + 1])))
		{
			count_num2++;
		}
		if (in[i] == '(')
			count_brackets1++;
		if (in[i] == ')')
			count_brackets2++;
		if (in[i] == '/' and in[i + 1] == '0')
			zero++;
	}
	//cout << count_num2 << " " << count_operat2;
	if (count_num2 - count_operat2 == 1 and count_brackets1==count_brackets2 and zero==0)
	{
		cout << "Выражение верно!\n";
		cout << "1)Преобразовать в Обратную Польскую Нотацию\n2)Преобразовать в Прямую Польскую Нотацию\n3)Просто посчитать\n";
		cout << "Ваш Выбор:";
		int choose;
		cin >> choose;
		string RevPol, StraigPol, Notation;
		switch (choose)
		{
		case 1:
			OPN(in, out);
			RevPol = string(out);
			cout << "\n";
			OPNCount(RevPol);
			break;
		case 2:
			PPN(in, out, rever1);
			StraigPol = string(rever1);
			cout << "\n";
			PPNCount(StraigPol);
			break;
		case 3:
			Notation = string(in);
			CountNot(Notation, out);
			break;
		}
	}
	else
		cout << "Выражение не верно!";
	cout << "\n";
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
