#include <stdio.h>
#include <string.h>
struct Account
{
    char name[100];
    char username[50];
    float balance;
    int account_number;
};
struct Account accounts[50];
int logged_in = -1;
int account_count = 0;
void create_account();
void check_amount();
void login();
void deposit();
void withdraw();
void transfer_money();
int main()
{
    int choice;
    while (1)
    {
        printf("1. Create account\n2. Login\n3. Check Amount\n4. Deposit\n5. Withdraw\n6. Transfer Money\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            login();
            break;
        case 3:
            check_amount();
            break;
        case 4:
            deposit();
            break;
        case 5:
            withdraw();
            break;
        case 6:
            transfer_money();
            break;
        case 7:
            printf("Exiting program. Thank you\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// creation of account
void create_account()
{
    if (account_count >= 50)
    {
        printf("Sorry, the maximum number of accounts has been reached.\n");
        return;
    }
    printf("Enter your name: ");
    getchar();
    fgets(accounts[account_count].name, sizeof(accounts[account_count].name), stdin);
    char new_username[50];
    while (1)
    {
        printf("Create your username: ");
        fgets(new_username, sizeof(new_username), stdin);
        int usernameExists = 0;
        // checking whether username already exists
        for (int i = 0; i < account_count; i++)
        {
            if (strcmp(new_username, accounts[i].username) == 0)
            {
                printf("Username already exists. Please enter another one.\n");
                usernameExists = 1;
                break;
            }
        }
        if (!usernameExists)
        {
            break;
        }
    }
    accounts[account_count].account_number = account_count + 1;
    strcpy(accounts[account_count].username, new_username);
    accounts[account_count].balance = 0;
    printf("Account created successfully!\n");
    printf("Account Number: %d\n", accounts[account_count].account_number);
    printf("Account Holder Name: %s", accounts[account_count].name);
    printf("Username: %s", accounts[account_count].username);
    printf("Initial balance: %.2f\n", accounts[account_count].balance);
    account_count++;
}

// user login
void login()
{
    char entered_username[50];
    printf("Enter your username: ");
    getchar();
    fgets(entered_username, 50, stdin);
    for (int i = 0; i < account_count; i++)
    {
        // username validation
        if (strcmp(entered_username, accounts[i].username) == 0)
        {
            logged_in = i;
            printf("Login successful!\n");
            return;
        }
    }
    printf("Account not found. Login failed.\n");
}

// checking Account Balance
void check_amount()
{
    if (logged_in != -1)
    {
        printf("Account Holder Name: %s", accounts[logged_in].name);
        printf("Username: %s", accounts[logged_in].username);
        printf("Current balance: %.2f\n", accounts[logged_in].balance);
    }
    else
    {
        printf("Please login first.\n");
    }
}

// Depositing money
void deposit()
{
    float amount;
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);
    if (logged_in != -1)
    {
        accounts[logged_in].balance += amount;
        printf("Deposit successful. Current balance: %.2f\n", accounts[logged_in].balance);
    }
    else
    {
        printf("Please login first.\n");
    }
}

// Withdrawal of money
void withdraw()
{
    float amount;
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    if (logged_in != -1)
    {
        if (amount > accounts[logged_in].balance)
        {
            printf("Insufficient funds. Withdrawal failed.\n");
        }
        else
        {
            accounts[logged_in].balance -= amount;
            printf("Withdrawal successful. Current balance: %.2f\n", accounts[logged_in].balance);
        }
    }
    else
    {
        printf("Please login first.\n");
    }
}

// Transfer of money
void transfer_money()
{
    float amount;
    int rec_acc;
    printf("Enter the amount to transfer: ");
    scanf("%f", &amount);
    printf("Enter the receiver's account number: ");
    scanf("%d", &rec_acc);
    if (logged_in != -1 && rec_acc > 0 && rec_acc <= account_count)
    {
        if (amount > accounts[logged_in].balance)
        {
            printf("Insufficient balance. Transfer failed.\n");
        }
        else
        {
            accounts[logged_in].balance -= amount;
            accounts[rec_acc - 1].balance += amount;
            printf("Transfer successful. Current balance: %.2f\n", accounts[logged_in].balance);
        }
    }
    else
    {
        printf("enter a valid receiver's account number.\n");
    }
}
