#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>  // std::strningstream
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace quantity {
	static const string kilogram = "kg";
	static const string piece = "p";
}

static const char start = '1';
static const char end = '2';

class Product {
public:
	enum class type { fruit, vegetable };
	type kind;
	string name;
	string quantity;

	Product(type k, string n, string q, double c, size_t pc)
		:kind(k), name(n), cost(c), quantity(q), product_code(pc) {}

	void set_cost(double c) { cost = c; }
	double get_cost() { return cost; }
	int get_product_code() { return product_code; }

private:
	double cost;
	size_t const product_code;
};
void main_menu();
void sub_menu();
double main_while(vector<Product>& products);
vector<string> read_from_file();
vector<Product> parsing_text(vector<string>& v_line);
Product::type check_product_type(string& t);
string check_product_quantity(string& k);

int main()
try {
	vector<Product> products;
	vector<string> file_text = read_from_file();
	products = parsing_text(file_text);

	main_menu();
	double sum = 0;
	sum = main_while(products);
	cout <<"suma: "<< sum;
	cout << "\nThanks for using my program";

}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "exception\n";
}
void main_while() {

}

void main_menu()
{
	cout << "=============" << endl;
	cout << "=MAIN MENU=" << endl;
	cout << "=============" << endl;
	cout << "1.Calculate" << endl;
	cout << "2.Finish" << endl;
}

void sub_menu()
{
	cout << "1.Next product" << endl;
	cout << "2.Finish" << endl;
}

double main_while(vector<Product>& products) {
	double sum = 0;
	char choice;
	while (cin >> choice && choice == start) {
		cout << "\nInsert product code: ";
		size_t code;
		cin >> code;
		for (std::vector<Product>::iterator i = products.begin(); i < products.end(); i++) {
			if (i->get_product_code() == code) {
				cout << "koszt " << i->name << ": " << i->get_cost() << endl;
				sum += i->get_cost();
				sub_menu();
				break;
			}
		}
	}
	return sum;
}

vector<string> read_from_file()
{
	vector<string> ft;
	ifstream file("data.txt");
	string line;
	if (!file)
		cerr << "Error: Failed to open the input file\n";
	while (getline(file, line))
		ft.push_back(line);
	return ft;
}

vector<Product> parsing_text(vector<string>& v_line)
{
	vector<Product> v_product;
	for (size_t i = 0; i < v_line.size(); i++)
	{
		stringstream sstream(v_line[i]);
		string type, name, quantity;
		double cost = 0;
		size_t code = 0;
		sstream >> type >> name >> quantity >> cost >> code;
		Product::type kind = check_product_type(type);
		quantity = check_product_quantity(quantity);
		v_product.push_back(Product(kind, name, quantity, cost, code));
	}
	return v_product;
}

Product::type check_product_type(string& t)
{
	if (t == "f")
		return Product::type::fruit;
	else
		return Product::type::vegetable;
}

string check_product_quantity(string& k)
{
	if (k == "kg") 
		return quantity::kilogram;
	else 
		return quantity::piece;
}
