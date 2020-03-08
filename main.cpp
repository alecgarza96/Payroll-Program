/*
 Name: Alec Garza
 Program Status: Complete
 Program Description: This program declares a struct to contain employee information.
 This struct data members are input by the user and written to
 an array of structs containing the employee data. The program outputs
 employee data and payroll information upon completion.
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int NUM_WORKERS = 4; //int constant representing number of workers


//employee information struct protoype
struct employeeInfo{
    int idNum; //int representing employee ID number
    string name; //string representing employee name
    float hourlyPay; //float representing hourly pay
    int employeeType; //int representing employee type (0 for union, 1 for mgmt)
};

//employeeInfo struct array declaration
employeeInfo employees[NUM_WORKERS];

//array declaration for employee pay data
float employeePay[NUM_WORKERS];

//input: terminal value and struct array
//processing: get user input string data and write to array
//output: return string data representing employee name
string getName(int k, employeeInfo employees[]){
    //user prompt for input
    cout << "Enter employee name: ";
    //getline to retrieve string data and assign to respective index in struct array
    getline(cin.ignore(), employees[k].name);
    
    return employees[k].name;
}

//input struct array and getName function
//processing: prompt user for employee data and write to struct array
//output: none
void employeeProccessing(employeeInfo employees[], string getName(int, employeeInfo[])){
    int k = 0; //terminal variable to control loop count
    
    //count-controlled loop
    for(k=0;k<NUM_WORKERS;k++){
        
        //retrieve employee ID number
        cout << "Enter employee ID number: ";
        cin >> employees[k].idNum;
        
        //validate ID number input
        while(employees[k].idNum < 0){
            cout << "Incorrect Value. Try again: ";
            cin >> employees[k].idNum;
        }
        
        //call to getName function
        getName(k, employees);
        
        //retrieve pay rate per employee
        cout << "Enter hourly pay: ";
        cin >> employees[k].hourlyPay;
        
        //valdidate employee pay rate input
        while(employees[k].hourlyPay < 0){
            cout << "Incorrect Value. Try again: ";
            cin >> employees[k].hourlyPay;
        }
        
        //retrieve employee type
        cout << "Enter employee type: ";
        cin >> employees[k].employeeType;
        
        //validate employee type input
        while(!(employees[k].employeeType == 0 || employees[k].employeeType == 1)){
            cout << "Incorrect Value. Try again: ";
            cin >> employees[k].employeeType;
        }
        cout << "\n";
    }
    
}

//input: employee struct array
//processing: prompt user for hours worked by each employee and calculate gross pay
//output: return array containing employee gross pay
float payrollProcessing(employeeInfo[]){
    int k = 0; //terminal variable to control loop count
    
    //count controlled loop to calculate gross pay
    for(k=0;k<NUM_WORKERS;k++){
        int hoursWorked; //hours worked per employee
        float grossPay; //gross pay per employee
        
        //retrieve hours worked
        cout << "Enter hours worked for " << employees[k].name << ": ";
        cin >> hoursWorked;
        
        //validate hours worked input
        while(hoursWorked < 0){
            cout << "Invalid value. Try again: ";
            cin >> hoursWorked;
        }
        
        //decision branch to process overtime pay for union and management employees
        if((hoursWorked > 40) && (employees[k].employeeType == 0)){
            //union employee gross pay calculation
            grossPay = (40 * employees[k].hourlyPay)+((hoursWorked-40)*(1.5*employees[k].hourlyPay));
        }
        else{
            //management employee gross pay calculation
            grossPay = hoursWorked * employees[k].hourlyPay;
        }
        
        employeePay[k] = grossPay;
    }
    
    return employeePay[k];
}

//input: none
//processing: format header for output data
//output: none
void formatOutput(){
    
    cout << left << "Payroll Report" << endl;
    cout << "\n";
    
    cout << left << "ID" << setw(2) << " " << "Name" << right << setw(10) << " " << "Gross Pay" << setw(3) << " " << "Taxes" << setw(3) << " " << "Net Pay" << endl;
    
}


//input: employee struct array and payroll array
//processing: calcalate taxes paid and net pay before displaying formatted employee data output.
//            calculate sum of total gross and net pay
//output: displays data
void displayOutput(employeeInfo[], float employeePay[]){
    int k = 0; //terminal variable for count controlled loop
    const float TAX = .15; //constant variable representing tax rate
    float taxesPaid = TAX*employeePay[k]; //calculates the taxes paid per employee
    float netPay = employeePay[k] - (TAX*employeePay[k]); //uses gross pay and taxesPaid to calculate net pay
    float totalGross = 0; //accumulator variable for total gross pay
    float totalNet = 0; //accumulator variable for tota net pay
    
    //count controlled loop to display employee data
    for(k=0; k<NUM_WORKERS; k++){
        //set format to two decimal places
        cout << fixed << setprecision(2);
        
        cout << setw(5) << left << employees[k].idNum << right << " " << employees[k].name << setw(12) << " " << employeePay[k] << setw(4) << right << " " << taxesPaid << setw(4) << right << " " << netPay
        << endl;
        
        //add gross and net pay to respective accumulator variables
        totalGross += employeePay[k];
        totalNet += netPay;
        
    }
    
    cout << "\n";
    
    //display total gross and net pay
    cout << "Total Gross Pay: " << totalGross << endl;
    cout << "Total Net Pay: " << totalNet << endl;
    
}

int main(){
    
    //call to employee processing function
    employeeProccessing(employees, getName);
    
    //call to payroll processing function
    payrollProcessing(employees);
    
    //call to format output function
    formatOutput();
    
    //call to display output function
    displayOutput(employees, employeePay);
    
    return 0;
}
