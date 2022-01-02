#include "interface.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace std;

Hierarchy::Hierarchy(Hierarchy&& r) noexcept
{
	this->boss = r.boss;
	this->who = r.who;
}

Hierarchy::Hierarchy(const Hierarchy& r) : who(NULL), boss(NULL)
{
	this->boss = r.boss;
	this->who = r.who;
}

Hierarchy::~Hierarchy() noexcept
{
	if (file.is_open());
	file.close();
	delete[] who;
	delete[] boss;
}

string Hierarchy::print() const
{
	cout << "Employee's name: " << who << endl;
	cout << "Manager's name: " << boss << endl;
}

int Hierarchy::longest_chain() const
{
	return this->longest_chain_help.root;
}

int Hierarchy::longest_chain_help(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	int leftHeight = longest_chain_help(root->left);
	int rightHeight = longest_chain_help(root->right);

	return 1 + max(leftHeight, rightHeight);
}

int Hierarchy::num_employees() const
{
	return this->num_employees_help.root;
}

int Hierarchy::num_employees_help(TreeNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}

	size_t count = 1;
	size_t children = root->children.size();
	for (size_t i = 0; i < children; i++)
	{
		count += num_employees_help(root->children[i]);
	}
	return count;
}

int Hierarchy::num_overloaded(int level = 20) const
{
	unsigned count = 0;
	if (this->manager > level)
	{
		count++;
	}
	return count;
}

string Hierarchy::manager(const string& name) const
{
	return this->manager.name;
}

int Hierarchy::num_subordinates(const string& name) const
{
	return this->num_employees.name;
}

unsigned long Hierarchy::getSalary(const string& who) const
{
	return 500 * this->num_subordinates + 50 * (this->num_subordinates - this->num_employees);
}

bool Hierarchy::fire(const string& who)
{
	if (who == "Uspeshnia")
	{
		cout << who << "This is a manager!" << endl;
		return false;
	}
	else 
	{
		cout << who << " was fired." << endl;
		return true;
	}
}

bool Hierarchy::hire(const string& who, const string& boss)
{
	if (this->who = this->boss)
	{
		return true;
	}
	else
	{
		cout << "This employee works with another manager." << endl;
		return false;
	}
}

int validate_employee_name(char employee_name)
{
	return employee_name >= MIN_EMPLOYEE_NAME_LENGTH && employee_name <= MAX_EMPLOYEE_NAME_LENGTH;
}

int validate_object_name(char object_name)
{
	return object_name >= MIN_OBJECT_NAME_LENGTH && object_name <= MAX_OBJECT_NAME_LENGTH;
}

int get_count(fstream& file)
{
	long int offset;
	file.clear();
	if (!file.seekg(0, ios::end))    
	{
		return -1;
	}
	offset = file.tellg();          
	assert(offset % sizeof(Info) == 0);
	return offset / sizeof(Info);
}

int read_at(fstream& file, Info& info, int pos)
{
	file.clear();
	file.seekg(pos * sizeof(info));
	return !file.read((char*)&info, sizeof(info));
}

int shift_out(long int start, long int count, fstream& file)
{
	Info info;
	file.clear();
	for (int pos = count - 1; pos >= start; --pos)
	{
		file.seekg(pos * sizeof(info));
		file.read((char*)&info, sizeof(info));
		file.seekp((pos + 1) * sizeof(info));
		file.write((char*)&info, sizeof(info));
		if (!file) return 1;
	}
	return 0;
}

void ignore_spaces(istream& in)
{
	char ch;
	do
	{
		ch = in.get();
	} 
	while (in && isspace(ch));
	in.putback(ch);
}

istream& operator>>(istream& in, Info& info)
{
	ignore_spaces(in);
	in.getline(info.who, MAX_EMPLOYEE_NAME_LENGTH, ' ');
	return in;
}

ostream& operator<<(ostream& out, const Info& info)
{
	out << setw(MAX_EMPLOYEE_NAME_LENGTH - 1) << setiosflags(ios::left)
		<< info.who << resetiosflags(ios::left)
		<< setprecision(2) << endl;
	return out;
}

int modernize(fstream& file, const char file_name[])
{
	char object_name;
	char new_object_name;
	cout << "Object name: ";
	cin >> object_name;
	if (!validate_object_name(object_name))
	{
		cout << object_name << " is not a valid name!" << endl;
		return 0;
	}
	long int count = get_count(file);
	Info info;
	if (read_at(file, info, count))
	{
		cout << "Failed to read data!" << endl;
		return 1;
	}
	if (info.object_name != &object_name)
	{
		cout << "There is no object with such a name!" << endl;
		return 0;
	}
	cout << "Object name: " << endl;
	cout << info;
	cout << "New object name: ";
	cin >> new_object_name;
	if (!validate_object_name(new_object_name))
	{
		cout << new_object_name << " is not a valid name!" << endl;
		return 0;
	}

	*info.object_name = new_object_name;
	file.seekp(sizeof(Info));
	if (!file.write((char*)&info, sizeof(info)))
	{
		cout << "Failed to save data!" << endl;
		return 1;
	}
	return 0;
}

int exit(fstream& file, const char file_name[])
{
	file.close();
	return 1;
}

TreeNode* constructTreeHelp(TreeNode*& root, const char*& charTree)
{
	char ch = *charTree;
	root->data = ch;
	charTree++;

	if (*charTree == '[')
	{
		charTree++;
		while (*charTree != ']')
		{
			if (*charTree == '(')
			{
				charTree++;
				TreeNode* child = new TreeNode();
				constructTreeHelp(child, charTree);
				root->children.push_back(child);
			}
			charTree++;
		}
		charTree++;
	}
	return root;
}

TreeNode* constructTree(const string& stringTree)
{
	TreeNode* root = new TreeNode();
	const char* charTree = stringTree.c_str() + 1;
	return constructTreeHelp(root, charTree);
}

void convertToStringHelp(TreeNode*& root, string& res)
{
	if (root == nullptr)
	{
		return;
	}

	res += root->data;
	size_t size = root->children.size();
	if (size > 0)
	{
		res += "[";
		for (size_t i = 0; i < size; i++)
		{
			res += "(";
			convertToStringHelp(root->children[i], res);
			res += ")";
		}
		res += "]";
	}
}

const string convertToString(TreeNode*& root)
{
	string resultString;
	resultString += '(';
	convertToStringHelp(root, resultString);
	resultString += ')';

	return resultString;
}

int load(fstream& file, const char file_name[])
{
	Info info;
	file.clear();
	file.seekg(0);
	cout << setw(MAX_EMPLOYEE_NAME_LENGTH) << setiosflags(ios::left)
		 << "Employee name" << '|' << resetiosflags(ios::left)
		 << setw(MAX_BOSS_NAME_LENGTH) << setiosflags(ios::left)
		 << "Manager name" << '|' << resetiosflags(ios::left)
		 << setw(MAX_OBJECT_NAME_LENGTH) << setiosflags(ios::left)
		 << "Object name" << resetiosflags(ios::left) << endl;
	while (file.read((char*)&info, sizeof(info)))
		//cout << info;
	return 0;
}

int save(fstream& file, const char file_name[])
{
	Info info;
	ofstream output(EXPORT_FILE_NAME);
	if (!output)
	{
		cout << "It cannot be opened " << EXPORT_FILE_NAME;
		return 1;
	}
	output << setw(MAX_EMPLOYEE_NAME_LENGTH) << setiosflags(ios::left)
		<< "Employee name" << '|' << resetiosflags(ios::left)
		<< setw(MAX_BOSS_NAME_LENGTH) << setiosflags(ios::left)
		<< "Manager name" << '|' << resetiosflags(ios::left)
		<< setw(MAX_OBJECT_NAME_LENGTH) << setiosflags(ios::left)
		<< "Object name" << resetiosflags(ios::left) << endl;
	file.clear();
	file.seekg(0);

	while (file.read((char*)&info, sizeof(info)))
	{
		if (!(output << info))
		{
			cout << "Writing to text file failed!" << endl;
			output.close();
			return 1;
		}
	}
	output.close();
	cout << "The information is saved in " << EXPORT_FILE_NAME << endl;
	return 0;
}

int find(fstream& file, const char file_name[])
{
	char employee_name;
	cout << "Search name: ";
	cin >> employee_name;
	if (!validate_employee_name(employee_name))
	{
		cout << setprecision(2) << employee_name
			<< " the name is not valid!" << endl;
		return 0;
	}
	file.clear();
	file.seekg(0);

	Info info;
	bool found = false;
	while (file.read((char*)&info, sizeof(info)))
	{
		if (employee_name)
		{
			cout << "Employee name: " << endl;
			cout << info;
			found = true;
		}
	}

	if (!found)
	{
		cout << "No employee with such a name was found!" << endl;
	}
	return 0;
}

int hire(fstream& file, const char file_name[])
{
	Info info;
	cout << "Enter an employee name: " << endl;
	cin >> info;

	long int count = get_count(file);
	if (count < 0)
	{
		cout << "Failed to take the number of records!" << endl;
		return count;
	}

	Info tmp_info = { 0, };
	if (tmp_info.who == info.who)
	{
		cout << "An employee with such a name already exists."
			" Data will be changed." << endl;
	}

	file.seekp(sizeof(info));
	if (!file.write((char*)&info, sizeof(info)))
	{
		cout << "Failed to save data!" << endl;
		return 1;
	}
	return 0;
}

int help(fstream& file, const char file_name[])
{
	cout << "\t\t MENU\n";
	for (int i = 0; commands[i].name; ++i)
	{
		cout << commands[i].key << " : "    
			<< commands[i].name << "\n";   
	}
}

int read_command()
{
	char key = -1;
	cin >> key;
	if (!cin) return 1;
	for (int i = 0; commands[i].name; ++i)
	{
		if (commands[i].key == key)
			return i;
	}
	cout << "Unknown command!" << endl;
	return -1;
}

int execute_command(int command, fstream& file,
	const char file_name[])
{
	if (command >= 0 && commands[command].function)
	{
		return commands[command].function(file, file_name);
	}
	return 0;
}

void initialize(fstream& file, char file_name[MAX_PATH_SIZE])
{
	cout << "Input file name: ";
	cin.getline(file_name, MAX_PATH_SIZE);
	file.open(file_name, ios::in | ios::out | ios::binary);
	if (!file) 
	{
		file.open(file_name, ios::in | ios::out | ios::binary | ios::trunc);
	}
}

int main()
{
	char file_name[MAX_PATH_SIZE];
	fstream file;

	initialize(file, file_name);
	int command, result = 0;

	do
	{
		help(file, file_name);
		command = read_command();
		if (command < 0) continue;
		result = execute_command(command, file, file_name);
	} while (result == 0);  

	exit(EXIT_SUCCESS);
	string stringTree = "(Uspeshnia[(Gosho[(Pesho[Alex])(Dancho[(Boris)(Kamen)])])(Misho)(Slavi[(Slav1[Mecho])(Slav2)])])";
	TreeNode* tree = constructTree(stringTree);

	string convertedTree = convertToString(tree);
	cout << convertedTree;
}