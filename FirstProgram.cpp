#include <iostream>
#include <cmath>  // For the pow() function
#include <iomanip> // For setting decimal precision
#include <fstream> // For file operations
#include <string>  // For string operations

using namespace std;

// Function to calculate the monthly payment
double calculateMonthlyPayment(double loanAmount, double annualInterestRate, int loanTenureYears) {
    double monthlyInterestRate = annualInterestRate / 12 / 100;
    int loanTenureMonths = loanTenureYears * 12;
    double monthlyPayment = loanAmount * monthlyInterestRate * pow(1 + monthlyInterestRate, loanTenureMonths) /
                            (pow(1 + monthlyInterestRate, loanTenureMonths) - 1);
    return monthlyPayment;
}

// Function to check loan eligibility
bool isEligible(double loanAmount, double income, int loanTenureYears) {
    double maxLoanAmount = income * 5;  // Maximum loan amount is 5 times monthly income
    return loanAmount <= maxLoanAmount;
}

// Function to display the loan summary
void displayLoanSummary(double loanAmount, double annualInterestRate, int loanTenureYears, double monthlyPayment, double totalPayment, double totalInterest, int age, double income) {
    cout << "\nLoan Summary:\n";
    cout << "-------------------------------------\n";
    cout << "Age Group: " << (age < 55 ? "Young" : "Old") << endl;
    cout << fixed << setprecision(2);  // Set decimal precision for currency
    cout << "Monthly Income: INR " << income << endl;
    cout << "Loan Amount: INR " << loanAmount << endl;
    cout << "Annual Interest Rate: " << annualInterestRate << "%" << endl;
    cout << "Loan Tenure: " << loanTenureYears << " years" << endl;
    cout << "Monthly Payment: " << monthlyPayment << endl;
    cout << "Total Payment: INR " << totalPayment << endl;
    cout << "Total Interest Paid: INR " << totalInterest << endl;
    cout << "-------------------------------------\n\n";
}

// Function to calculate new totals after early repayment
void calculateEarlyRepayment(double &totalPayment, double &totalInterest, double monthlyPayment, double earlyRepaymentAmount, int loanTenureYears, double annualInterestRate) {
    // Calculate new balance after early repayment
    totalPayment -= earlyRepaymentAmount;
    totalInterest = totalPayment - (totalPayment - earlyRepaymentAmount);
    // Display new totals
    cout << "\nAfter early repayment of INR " << earlyRepaymentAmount << ":\n";
    cout << "Updated Total Payment: INR " << totalPayment << endl;
    cout << "Updated Total Interest Paid: INR\n" << totalInterest << endl;
}

// Function to generate a detailed loan report
void generateLoanReport(double loanAmount, double annualInterestRate, int loanTenureYears, double monthlyPayment, double totalPayment, double totalInterest, int age, double income) {
    ofstream reportFile("Loan_Report.txt"); // Create a text file for the report

    if (reportFile.is_open()) {
        reportFile << fixed << setprecision(2);  // Set decimal precision for currency
        reportFile << "\n----------- Loan Report -----------\n";
        reportFile << "Age Group: " << (age < 55 ? "Young" : "Old") << endl;
        reportFile << "Monthly Income: INR " << income << endl;
        reportFile << "Loan Amount: INR " << loanAmount << endl;
        reportFile << "Annual Interest Rate: " << annualInterestRate << "%" << endl;
        reportFile << "Loan Tenure: " << loanTenureYears << " years" << endl;
        reportFile << "Monthly Payment: INR " << monthlyPayment << endl;
        reportFile << "Total Payment: INR " << totalPayment << endl;
        reportFile << "Total Interest Paid: INR " << totalInterest << endl;
        reportFile << "-----------------------------------\n\n";
        reportFile.close();
        cout << "Loan report generated successfully: Loan_Report.txt\n";
    } else {
        cout << "Unable to create report file.\n";
    }
}

int main() {
    double loanAmount, annualInterestRate = 0, monthlyPayment, totalPayment, totalInterest, income;
    int loanTenureYears, choice, loanType, age;
    bool loanTypeSelected = false;

    do {
        // Display main menu options
        cout << "\n--- Loan Application Menu ---\n";
        cout << "1. Document Details\n";
        cout << "2. Select Loan Category, Age Group, and Income\n";
        cout << "3. Enter Loan Details\n";
        cout << "4. Calculate Monthly Payment\n";
        cout << "5. View Loan Summary\n";
        cout << "6. Make Early Repayment\n";
        cout << "7. Generate Loan Report\n";
        cout << "8. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            int a;
                 cout <<"\n------ Do You Have These Documents ------\n";
                 cout <<"1. Personal Identification ( Any Valid Govt. ID ) \n";
                 cout <<"2. Proof Of Income\n";
                 cout <<"3. Collateral Document\n";
                 cout <<"4. Proof Of Admission Letter ( If you Are Student )\n";
                 cout <<"\n1. Yes\n";
                 cout <<"2. No\n";
                 cin >> a;
                 if(a==2){
                    cout <<"# You are not Eligible for taking a laon\n\n";
                    break;
                 }
                 else if(a==1){
                    cout <<"\3 \3 \3 Congratulations, You Meet The Criteria \3 \3 \3\n       You can Now Proceed To The Next Step\n";
                 }

                   break;

            case 2:  // Select loan category, age group, and income
                cout << "\nEnter your age: ";
                cin >> age;

                // Input validation for age
                if (age < 18 || age > 85 ) {
                    cout << "# You are not Eligible for taking a laon \n";
                    break;
                }

               else{
                 cout << "Enter your monthly income (in INR): ";
                cin >> income;

                // Input validation for income
                if (income <= 0) {
                    cout << "Invalid income entered. Please enter a positive income.\n";
                    break;
                }
               

                cout << "\n--- Loan Categories ---\n";
                cout << "1. Student Loan\n";
                cout << "2. Business Loan\n";
                cout << "3. Home Loan\n";
                cout << "4. Personal Loan\n";
                cout << "\nEnter your loan type: ";
                cin >> loanType;

                // Determine interest rate based on age and loan type
                if (age >= 18 && age <= 55) {  // Young age group
                    switch (loanType) {
                        case 1:
                            annualInterestRate = 11.0;  // Student Loan for young
                            cout << "\nYou selected Student Loan (3% interest for young).\n";
                            break;
                        case 2:  // Business Loan for young
                            annualInterestRate = (income >= 5000) ? 7.5 : 8.5;
                            cout << "\nYou selected Business Loan (" << (income >= 5000 ? "7.5%" : "8.5%") << " interest).\n";
                            break;
                        case 3:
                            annualInterestRate = 12.0;  // Home Loan for young
                            cout << "\nYou selected Home Loan (12% interest for young).\n";
                            break;
                        case 4:  // Personal Loan for young
                            annualInterestRate = (income >= 3000) ? 10.5 : 12.0;
                            cout << "\nYou selected Personal Loan (" << (income >= 3000 ? "10.5%" : "12.0%") << " interest).\n";
                            break;
                        default:
                            cout << "\nInvalid loan type selected. Please choose again.\n";
                            annualInterestRate = 0;  // Reset interest rate if invalid
                            break;
                    }
                }
                 else if (age <55) {  // Old age group
                    switch (loanType) {
                        case 1:
                            annualInterestRate = 5.5;  // Student Loan for old
                            cout << "\nYou selected Student Loan (5.5% interest for old).\n";
                            break;
                        case 2:  // Business Loan for old
                            annualInterestRate = (income >= 5000) ? 6.5 : 7.5;
                            cout << "\nYou selected Business Loan (" << (income >= 5000 ? "6.5%" : "7.5%") << " interest).\n";
                            break;
                        case 3:
                            annualInterestRate = 9.0;  // Home Loan for old
                            cout << "\nYou selected Home Loan (9.0% interest for old).\n";
                            break;
                        case 4:  // Personal Loan for old
                            annualInterestRate = (income >= 3000) ? 8.0 : 9.0;
                            cout << "\nYou selected Personal Loan (" << (income >= 3000 ? "8.0%" : "9.0%") << " interest).\n";
                            break;
                        default:
                            cout << "\nInvalid loan type selected. Please choose again.\n";
                            annualInterestRate = 0;  // Reset interest rate if invalid
                            break;
                    }
                }
                else {
                   cout << "# You are not Eligible for taking a loan\n";
                   break;
                }
        }

                loanTypeSelected = annualInterestRate != 0;  // True if a valid loan type is selected
                break;

            case 3:  // Input loan details
                if (!loanTypeSelected) {
                    cout << "\n\nPlease select a loan category and provide income details first (option 1).\n";
                } else {
                    cout << "\nEnter the loan amount: ";
                    cin >> loanAmount;

                    // Input validation for loan amount
                    if (loanAmount <= 0) {
                        cout << "\n\nInvalid loan amount entered. Please enter a positive amount.\n";
                        break;
                    }

                    cout << "\nEnter the loan tenure (in years): ";
                    cin >> loanTenureYears;

                    // Input validation for loan tenure
                    if (loanTenureYears <= 0) {
                        cout << "\n\nInvalid loan tenure entered. Please enter a positive number of years.\n";
                        break;
                    }

                }
                break;

            case 4:  // Calculate monthly payment
                if (loanAmount > 0 && loanTenureYears > 0 && loanTypeSelected) {
                    monthlyPayment = calculateMonthlyPayment(loanAmount, annualInterestRate, loanTenureYears);
                    totalPayment = monthlyPayment * loanTenureYears * 12;
                    totalInterest = totalPayment - loanAmount;
                    cout << "\n\nMonthly Payment Calculated Successfully!\n";
                } else {
                    cout << "\n\nPlease enter loan details first (option 2).\n";
                }
                break;

            case 5:  // View loan summary
                if (loanAmount > 0 && loanTenureYears > 0 && loanTypeSelected) {
                    displayLoanSummary(loanAmount, annualInterestRate, loanTenureYears, monthlyPayment, totalPayment, totalInterest, age, income);
                } else {
                    cout << "\n\nPlease calculate your payment first (option 3).\n";
                }
                break;

            case 6:  // Make early repayment
                if (totalPayment > 0) {
                    double earlyRepaymentAmount;
                    cout << "\n\nEnter the amount for early repayment: ";
                    cin >> earlyRepaymentAmount;

                    // Input validation for early repayment
                    if (earlyRepaymentAmount <= 0 || earlyRepaymentAmount > totalPayment) {
                        cout << "\n\nInvalid early repayment amount. Please enter a positive amount less than or equal to your total payment.\n";
                        break;
                    }

                    calculateEarlyRepayment(totalPayment, totalInterest, monthlyPayment, earlyRepaymentAmount, loanTenureYears, annualInterestRate);
                } else {
                    cout << "\n\nPlease view your loan summary first (option 4).\n";
                }
                break;

            case 7:  // Generate loan report
                if (loanAmount > 0 && loanTenureYears > 0 && loanTypeSelected) {
                    generateLoanReport(loanAmount, annualInterestRate, loanTenureYears, monthlyPayment, totalPayment, totalInterest, age, income);
                } else {
                    cout << "\n\nPlease calculate your payment first (option 3).\n";
                }
                break;

            case 8:  // Exit the program
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "\nInvalid choice. Please select a valid option.\n";
        }
    } while (choice != 8);

    return 0;
}