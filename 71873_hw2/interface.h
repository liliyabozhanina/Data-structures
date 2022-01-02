#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

using std::string;


const char* EXPORT_FILE_NAME = "print.txt";
const char* TEMP_FILE_NAME = "temp_employee.dat";
const int MAX_PATH_SIZE = 256;
const int MAX_EMPLOYEE_NAME_LENGTH = 32;
const int MIN_EMPLOYEE_NAME_LENGTH = 2;
const int MAX_BOSS_NAME_LENGTH = 32;
const int MAX_OBJECT_NAME_LENGTH = 32;
const int MIN_OBJECT_NAME_LENGTH = 5;


struct Info
{
	char who[MAX_EMPLOYEE_NAME_LENGTH]; 
	char boss[MAX_BOSS_NAME_LENGTH];   
	char object_name[MAX_OBJECT_NAME_LENGTH];     
};

typedef int(*cmd_function)(fstream&, const char file_name[]);

int help(fstream&, const char file_name[]);
int load(fstream&, const char file_name[]);
int save(fstream&, const char file_name[]);
int find(fstream&, const char file_name[]);
int num_subordinates(fstream&, const char file_name[]);
int manager(fstream&, const char file_name[]);
int num_employees(fstream&, const char file_name[]);
int overloaded(fstream&, const char file_name[]);
int join (fstream&, const char file_name[]);
int fire(fstream&, const char file_name[]);
int hire(fstream&, const char file_name[]);
int salary(fstream&, const char file_name[]);
int incorporate(fstream&, const char file_name[]);
int modernize(fstream&, const char file_name[]);
int exit(fstream&, const char file_name[]);

struct Command
{
	
	char key;
	const char* name;
	cmd_function function;

} commands[] = {
		{'h', "HELP", help},
		{'l', "LOAD", load},
		{'s', "SAVE", save},
		{'f', "FIND", find},
		{'ns', "NUM_SUBORTINATES", num_subordinates},
		{'ma', "MANAGER", manager},
		{'ne', "NUM_EMPLOYEES", num_employees},
		{'o', "OVERLOADED", overloaded},
		{'j', "JOIN", join},
		{'fi', "FIRE", fire},
		{'hi', "HIRE", hire},
		{'s', "SALARY", salary},
		{'i', "INCORPORATE", incorporate},
		{'m', "MODERNIZE", modernize},
		{'e', "EXIT", exit},
		{0, NULL, NULL} 
};

struct TreeNode 
{
	char data;
	TreeNode* left;
	TreeNode* right;
	std::vector<TreeNode*> children;
};

TreeNode* constructTreeHelp(TreeNode*& root, const char*& charTree);
TreeNode* constructTree(const string& stringTree);
void convertToStringHelp(TreeNode*& root, string& res);
const string convertToString(TreeNode*& root);

class Hierarchy
{
public:
	Hierarchy(Hierarchy&& r) noexcept;
	Hierarchy(const Hierarchy& r);
	Hierarchy(const string& data);
	~Hierarchy() noexcept;
	void operator=(const Hierarchy&) = delete;

	string print()const;

	int longest_chain() const;
    int longest_chain_help(TreeNode* root);

	bool find(const string& name) const;

	int num_employees() const;
    int num_employees_help(TreeNode* root);

	int num_overloaded(int level = 20) const;

	string manager(const string& name) const;

	int num_subordinates(const string& name) const;

	unsigned long getSalary(const string& who) const;

	bool fire(const string& who);

	bool hire(const string& who, const string& boss);

	void incorporate();

	void modernize();

	Hierarchy join(const Hierarchy& right) const; 
private:
	char* who;
	char* boss;
	fstream file;
};