#include <stdio.h>

#define MAX 50

struct Employee {
    int id;
    char name[50];
    int type; /* 1 = Regular, 2 = Contract */
    float basicPay;
    float hoursWorked;
    float hourlyRate;
    float hra;
    float da;
    float pf;
    float tax;
    float grossSalary;
    float totalDeductions;
    float netSalary;
};

int addEmployee(struct Employee emp[], int count);
void calculateSalary(struct Employee emp[], int i);
float calculateTax(int type, float gross);
void displayPaySlip(struct Employee emp[], int count);
void displaySalaryReport(struct Employee emp[], int count);

int main() {
    struct Employee emp[MAX];
    int count = 0;
    int choice;

    do {
        printf("\n=== EMPLOYEE PAYROLL SYSTEM ===\n");
        printf("1. Add Employee Record\n");
        printf("2. Generate Individual Pay Slip\n");
        printf("3. Display Full Salary Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                count = addEmployee(emp, count);
                break;
            case 2:
                displayPaySlip(emp, count);
                break;
            case 3:
                displaySalaryReport(emp, count);
                break;
            case 4:
                printf("Exiting Payroll System.\n");
                break;
            default:
                printf("Invalid choice! Please enter 1 to 4.\n");
        }
    } while (choice != 4);

    return 0;
}

int addEmployee(struct Employee emp[], int count) {
    if (count >= MAX) {
        printf("Employee limit reached!\n");
        return count;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp[count].id);

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp[count].name);

    printf("Select Employee Type (1 = Regular, 2 = Contract): ");
    scanf("%d", &emp[count].type);

    if (emp[count].type == 1) {
        printf("Enter Basic Pay: ");
        scanf("%f", &emp[count].basicPay);
        emp[count].hoursWorked = 0;
        emp[count].hourlyRate = 0;
    } else if (emp[count].type == 2) {
        printf("Enter Hours Worked: ");
        scanf("%f", &emp[count].hoursWorked);
        printf("Enter Hourly Rate: ");
        scanf("%f", &emp[count].hourlyRate);
        emp[count].basicPay = 0;
    } else {
        printf("Invalid employee type! Record not added.\n");
        return count;
    }

    calculateSalary(emp, count);
    printf("Employee record added successfully!\n");

    return count + 1;
}

void calculateSalary(struct Employee emp[], int i) {
    if (emp[i].type == 1) {
        emp[i].hra = 0.20 * emp[i].basicPay;
        emp[i].da  = 0.10 * emp[i].basicPay;
        emp[i].grossSalary = emp[i].basicPay + emp[i].hra + emp[i].da;

        emp[i].pf  = 0.12 * emp[i].basicPay;
        emp[i].tax = calculateTax(1, emp[i].grossSalary);
        emp[i].totalDeductions = emp[i].pf + emp[i].tax;
    } else {
        emp[i].hra = 0;
        emp[i].da  = 0;
        emp[i].grossSalary = emp[i].hoursWorked * emp[i].hourlyRate;

        emp[i].pf  = 0;
        emp[i].tax = calculateTax(2, emp[i].grossSalary);
        emp[i].totalDeductions = emp[i].tax;
    }

    emp[i].netSalary = emp[i].grossSalary - emp[i].totalDeductions;
}

float calculateTax(int type, float gross) {
    if (type == 1) {
        if (gross <= 25000) {
            return 0.0;
        } else if (gross <= 50000) {
            return 0.05 * gross;
        } else {
            return 0.10 * gross;
        }
    } else {
        if (gross <= 20000) {
            return 0.0;
        } else {
            return 0.10 * gross;
        }
    }
}

void displayPaySlip(struct Employee emp[], int count) {
    int searchId, i, found = 0;

    if (count == 0) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\nEnter Employee ID for Pay Slip: ");
    scanf("%d", &searchId);

    for (i = 0; i < count; i++) {
        if (emp[i].id == searchId) {
            found = 1;
            printf("\n----------------------------------------\n");
            printf("               PAY SLIP                 \n");
            printf("----------------------------------------\n");
            printf("Employee ID   : %d\n", emp[i].id);
            printf("Name          : %s\n", emp[i].name);
            printf("Type          : %s\n", (emp[i].type == 1) ? "Regular" : "Contract");
            printf("----------------------------------------\n");

            if (emp[i].type == 1) {
                printf("Basic Pay     : %10.2f\n", emp[i].basicPay);
                printf("HRA (20%%)     : %10.2f\n", emp[i].hra);
                printf("DA  (10%%)     : %10.2f\n", emp[i].da);
            } else {
                printf("Hours Worked  : %10.2f\n", emp[i].hoursWorked);
                printf("Hourly Rate   : %10.2f\n", emp[i].hourlyRate);
            }

            printf("Gross Salary  : %10.2f\n", emp[i].grossSalary);
            printf("----------------------------------------\n");
            printf("PF Deduction  : %10.2f\n", emp[i].pf);
            printf("Tax / TDS     : %10.2f\n", emp[i].tax);
            printf("Total Deduct. : %10.2f\n", emp[i].totalDeductions);
            printf("----------------------------------------\n");
            printf("NET SALARY    : %10.2f\n", emp[i].netSalary);
            printf("----------------------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", searchId);
    }
}

void displaySalaryReport(struct Employee emp[], int count) {
    int i;
    float totalNetPayroll = 0;

    if (count == 0) {
        printf("\nNo employee records available.\n");
        return;
    }

    printf("\n====================================================================\n");
    printf("                         SALARY REPORT                              \n");
    printf("====================================================================\n");
    printf("%-6s %-18s %-10s %10s %10s %10s\n",
           "ID", "Name", "Type", "Gross", "Deduct.", "Net Pay");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < count; i++) {
        printf("%-6d %-18s %-10s %10.2f %10.2f %10.2f\n",
               emp[i].id,
               emp[i].name,
               (emp[i].type == 1) ? "Regular" : "Contract",
               emp[i].grossSalary,
               emp[i].totalDeductions,
               emp[i].netSalary);
        totalNetPayroll += emp[i].netSalary;
    }

    printf("--------------------------------------------------------------------\n");
    printf("Total Employees: %d | Total Net Payroll: %.2f\n", count, totalNetPayroll);
    printf("====================================================================\n");
}
