#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <regex>
#include <unordered_map>

using namespace std;

class Employee
{
private:
    string id;
    string name;
    double salary;

public:
    Employee(string empId, string empName, double empSalary) : id(empId), name(empName), salary(empSalary) {}

    virtual void calculateSalary() = 0;

    void setId(const string &empId)
    {
        id = empId;
    }
    void setName(const string &empName)
    {
        name = empName;
    }
    void setSalary(double empSalary)
    {
        salary = empSalary;
    }

    string getId() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    double getSalary() const
    {
        return salary;
    }
};

unordered_map<string, unique_ptr<Employee>> employees;

bool isValidNumber(const string &input)
{
    if (input.empty())
        return false;
    regex pattern("^(?!0(\\.0{1,2})?$)[0-9]+(\\.[0-9]{1,2})?$");
    return regex_match(input, pattern);
}

bool isValidString(const string &input)
{
    if (input.empty())
        return false;
    regex pattern("^[A-Za-z ]+$");
    return regex_match(input, pattern);
}

bool isValidId(const string &input)
{
    if (input.length() != 3)
        return false;
    if ((isdigit(input[0]) && isdigit(input[1]) && isdigit(input[2])) ||
        (isupper(input[0]) && isupper(input[1]) && isupper(input[2])))
    {
        return true;
    }
    return false;
}

class FullTimeEmployee : public Employee
{
public:
    FullTimeEmployee(string id, string name, double salary) : Employee(id, name, salary) {}

    void calculateSalary() override
    {

        string tempId, tempName;
        double tempSalary;

        cout << "\n------ Full-time Employee ------\n";
        for (;;)
        {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end())
            {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;)
        {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName))
            {
                setName(tempName);
                break;
            }
        }

        for (;;)
        {
            cout << "Input salary: $";
            string tempSalaryStr;
            getline(cin, tempSalaryStr);
            if (!isValidNumber(tempSalaryStr))
            {
                cout << "Invalid salary. Please enter a valid number.\n";
                continue;
            }
            tempSalary = stod(tempSalaryStr);
            break;
        }
        setSalary(tempSalary);
        cout << "Total Salary: $" << getSalary() << "\n";
    }
};

class PartTimeEmployee : public Employee
{
private:
    double hourlyWage;
    int workHours;

public:
    PartTimeEmployee(string id, string name, double salary, double hourlyWage, int workHours) : Employee(id, name, salary), hourlyWage(hourlyWage), workHours(workHours) {}

    void setHourlyWage(double hourlyWage)
    {
        this->hourlyWage = hourlyWage;
    }
    void setWorkHours(int workHours)
    {
        this->workHours = workHours;
    }

    double getHourlyWage() const
    {
        return hourlyWage;
    }
    int getWorkHours() const
    {
        return workHours;
    }

    void calculateSalary() override
    {

        string tempId, tempName, tempHourlyWage, tempWorkHours;
        cout << "\n------ Part-time Employee ------\n";
        for (;;)
        {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end())
            {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;)
        {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName))
            {
                setName(tempName);
                break;
            }
            cout << "Invalid name. Please enter letters only.\n";
        }

        for (;;)
        {
            cout << "Input Hourly Wage: $";
            getline(cin, tempHourlyWage);
            if (!isValidNumber(tempHourlyWage))
            {
                cout << "Invalid input. Please enter a valid hourly wage.\n";
                continue;
            }
            setHourlyWage(stod(tempHourlyWage));
            break;
        }

        for (;;)
        {
            cout << "Input number of hours worked: ";
            getline(cin, tempWorkHours);
            if (!isValidNumber(tempWorkHours))
            {
                cout << "Invalid input. Please enter a valid hours work.\n";
                continue;
            }
            setWorkHours(stoi(tempWorkHours));
            break;
        }

        setSalary(getHourlyWage() * getWorkHours());
        cout << "Total Salary: $" << getSalary() << "\n";
    }
};

class ContractEmployee : public Employee
{
private:
    double contractPayment;
    int numProject;

public:
    ContractEmployee(string id, string name, double salary, double contractPayment, int numProject) : Employee(id, name, salary), contractPayment(contractPayment), numProject(numProject) {}

    void setContractPayment(double contractPayment)
    {
        this->contractPayment = contractPayment;
    }
    void setNumProject(int numProject)
    {
        this->numProject = numProject;
    }

    double getContractPayment() const
    {
        return contractPayment;
    }
    int getNumProject() const
    {
        return numProject;
    }

    void calculateSalary() override
    {

        string tempId, tempName, tempContractPayment, tempNumProject;

        cout << "\n------ Contractual Employee ------\n";
        for (;;)
        {
            cout << "Input a 3-digit ID (000 | ABC): ";
            getline(cin, tempId);
            if (!isValidId(tempId))
            {
                cout << "Invalid ID. Please enter a valid 3-digit number or uppercase letters.\n";
                continue;
            }
            if (employees.find(tempId) != employees.end())
            {
                cout << "ID already exists. Please enter a different ID.\n";
                continue;
            }
            break;
        }
        setId(tempId);

        for (;;)
        {
            cout << "Input your name (letters only): ";
            getline(cin, tempName);
            if (isValidString(tempName))
            {
                setName(tempName);
                break;
            }
            cout << "Invalid name. Please enter letters only.\n";
        }

        for (;;)
        {
            cout << "Input Contract Payment per Project: $";
            getline(cin, tempContractPayment);
            if (!isValidNumber(tempContractPayment))
            {
                cout << "Invalid input. Please enter a contract payment.\n";
                continue;
            }
            setContractPayment(stod(tempContractPayment));
            break;
        }

        for (;;)
        {
            cout << "Input number of project: ";
            getline(cin, tempNumProject);
            if (!isValidNumber(tempNumProject))
            {
                cout << "Invalid input. Please enter a valid number of project.\n";
                continue;
            }
            setNumProject(stoi(tempNumProject));
            break;
        }

        setSalary(getContractPayment() * getNumProject());
        cout << "Total Salary: $" << getSalary() << "\n";
    }
};

void displayPayrollReport()
{
    cout << "\n------ Employee Payroll Report ------\n";
    if (employees.empty())
    {
        cout << "No employee data available.\n";
        return;
    }
    for (const auto &pair : employees)
    {
        if (FullTimeEmployee *emp = dynamic_cast<FullTimeEmployee *>(pair.second.get()))
        {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Fixed Monthly Salary: $" << emp->getSalary() << "\n";
        }
        else if (PartTimeEmployee *emp = dynamic_cast<PartTimeEmployee *>(pair.second.get()))
        {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Hourly Wage: $" << emp->getHourlyWage() << "\n";
            cout << "Hours Worked: " << emp->getWorkHours() << "\n";
            cout << "Total Salary: $" << emp->getSalary() << "\n";
        }
        else if (ContractEmployee *emp = dynamic_cast<ContractEmployee *>(pair.second.get()))
        {
            cout << "\nEmployee: " << emp->getName() << " (ID: " << emp->getId() << ")\n";
            cout << "Contract Payment per Project: $" << emp->getContractPayment() << "\n";
            cout << "Projects Completed: " << emp->getNumProject() << "\n";
            cout << "Total Salary: $" << emp->getSalary() << "\n";
        }
    }
}

void displayEmployeeTypeMenu(int numChoice);

void displayMenu()
{
    cout << "\n- - - - - - - - - - - Menu - - - - - - - - - - -\n";
    cout << "1. Full-time Employee\n2. Part-time Employee\n3. Contractual Employee\n4. Display Payroll Report\n5. Exit\n";
    for (;;)
    {
        cout << "Input number of choice: ";
        string choice;
        getline(cin, choice);
        if (!isValidNumber(choice))
        {
            cout << "Invalid input. Please enter a valid choice.\n";
            continue;
        }
        int numChoice = stoi(choice);
        if (numChoice < 1 || numChoice > 5)
        {
            cout << "Invalid choice. Please enter a number between 1 and 5.\n";
            continue;
        }
        displayEmployeeTypeMenu(numChoice);
        break;
    }
}

void displayEmployeeTypeMenu(int numChoice)
{
    switch (numChoice)
    {
    case 1:
    {
        FullTimeEmployee fTimeEmp("", "", 0);
        fTimeEmp.calculateSalary();
        employees.insert({fTimeEmp.getId(), make_unique<FullTimeEmployee>(fTimeEmp.getId(), fTimeEmp.getName(), fTimeEmp.getSalary())});
        displayMenu();
        break;
    }
    case 2:
    {
        PartTimeEmployee pTimeEmp("", "", 0, 0, 0);
        pTimeEmp.calculateSalary();
        employees.insert({pTimeEmp.getId(), make_unique<PartTimeEmployee>(pTimeEmp.getId(), pTimeEmp.getName(), pTimeEmp.getSalary(), pTimeEmp.getHourlyWage(), pTimeEmp.getWorkHours())});
        displayMenu();
        break;
    }
    case 3:
    {
        ContractEmployee contractEmp("", "", 0, 0, 0);
        contractEmp.calculateSalary();
        employees.insert({contractEmp.getId(), make_unique<ContractEmployee>(contractEmp.getId(), contractEmp.getName(), contractEmp.getSalary(), contractEmp.getContractPayment(), contractEmp.getNumProject())});
        displayMenu();
        break;
    }
    case 4:
    {
        displayPayrollReport();
        displayMenu();
        break;
    }
    case 5:
    {
        return;
        exit(0);
    }
    default:
    {
        cout << "Invalid choice. Please enter a valid number.\n";
        displayMenu();
        break;
    }
    }
}

int main()
{
    try
    {
        displayMenu();
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
    }
    return 0;
}
