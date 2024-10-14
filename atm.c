#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BALANCE 100000
#define MAX_TRANSACTIONS 100
#define MAX_PASSCODE_LENGTH 10
#define MAX_RECIPIENT_LENGTH 100
#define MAX_TRANSACTION_LENGTH 200

typedef struct {
    double balance;
    char transaction_history[MAX_TRANSACTIONS][MAX_TRANSACTION_LENGTH];
    int transaction_count;
} ATM;

typedef enum {
    TRANSFER_TYPE_ACCOUNT,
    TRANSFER_TYPE_PHONE,
    TRANSFER_TYPE_CARD
} TransferType;

void init_atm(ATM *atm) {
    atm->balance = INITIAL_BALANCE;
    atm->transaction_count = 0;
}

char* deposit(ATM *atm, double amount) {
    atm->balance += amount;
    snprintf(atm->transaction_history[atm->transaction_count++], MAX_TRANSACTION_LENGTH, "Deposited $%.2f", amount);
    static char result[100];
    snprintf(result, sizeof(result), "Deposited $%.2f. New balance: $%.2f", amount, atm->balance);
    return result;
}

char* withdraw(ATM *atm, double amount) {
    if (amount <= atm->balance) {
        atm->balance -= amount;
        snprintf(atm->transaction_history[atm->transaction_count++], MAX_TRANSACTION_LENGTH, "Withdrawn $%.2f", amount);
        static char result[100];
        snprintf(result, sizeof(result), "Withdrawn $%.2f. New balance: $%.2f", amount, atm->balance);
        return result;
    } else {
        return "Insufficient funds";
    }
}

char* transfer(ATM *atm, double amount, const char *recipient, TransferType type) {
    if (amount <= atm->balance) {
        atm->balance -= amount;
        char transfer_type_str[20];
        switch (type) {
            case TRANSFER_TYPE_ACCOUNT:
                strcpy(transfer_type_str, "Account");
                break;
            case TRANSFER_TYPE_PHONE:
                strcpy(transfer_type_str, "Phone");
                break;
            case TRANSFER_TYPE_CARD:
                strcpy(transfer_type_str, "Card");
                break;
        }
        snprintf(atm->transaction_history[atm->transaction_count++], MAX_TRANSACTION_LENGTH, "Transferred $%.2f to %s via %s", amount, recipient, transfer_type_str);
        static char result[100];
        snprintf(result, sizeof(result), "Transferred $%.2f to %s via %s. New balance: $%.2f", amount, recipient, transfer_type_str, atm->balance);
        return result;
    } else {
        return "Insufficient funds";
    }
}

char* get_balance(ATM *atm) {
    static char result[50];
    snprintf(result, sizeof(result), "Current balance: $%.2f", atm->balance);
    return result;
}

void print_transaction_history(ATM *atm) {
    if (atm->transaction_count > 0) {
        printf("Transaction History:\n");
        for (int i = 0; i < atm->transaction_count; i++) {
            printf("%d. %s\n", i + 1, atm->transaction_history[i]);
        }
    } else {
        printf("Transaction history is empty.\n");
    }
}

void atm_interface() {
    ATM atm;
    init_atm(&atm);

    printf("Welcome to the ATM Simulator\n");
    printf("Code created by SnSarvesh🔥\n");

    char user_id[20];
    char pin[20];
    printf("Enter User ID: ");
    scanf("%s", user_id);
    printf("Enter PIN: ");
    scanf("%s", pin);

    if (strcmp(user_id, "123456") == 0 && strcmp(pin, "250206") == 0) {
        printf("Login successful!\n\n");

        while (1) {
            printf("ATM Operations:\n");
            printf("1. Deposit\n");
            printf("2. Withdraw\n");
            printf("3. Transfer\n");
            printf("4. Check Balance\n");
            printf("5. Transaction History\n");
            printf("6. Quit\n");

            int choice;
            printf("Enter your choice (1/2/3/4/5/6): ");
            scanf("%d", &choice);

            if (choice == 1) {
                double amount;
                printf("Enter the deposit amount: $");
                scanf("%lf", &amount);
                char pass_code[MAX_PASSCODE_LENGTH];
                printf("Enter 4 or 6 digit pass_code: ");
                scanf("%s", pass_code);
                printf("%s\npass_code: %s\n", deposit(&atm, amount), "****");
            } else if (choice == 2) {
                double amount;
                printf("Enter the withdrawal amount: $");
                scanf("%lf", &amount);
                char pass_code[MAX_PASSCODE_LENGTH];
                printf("Enter 4 or 6 digit pass_code: ");
                scanf("%s", pass_code);
                printf("%s\npass_code: %s\n", withdraw(&atm, amount), "****");
            } else if (choice == 3) {
                double amount;
                printf("Enter the transfer amount: $");
                scanf("%lf", &amount);
                char recipient[MAX_RECIPIENT_LENGTH];
                printf("Enter the recipient's name: ");
                scanf("%s", recipient);
                int transfer_type;
                printf("Select transfer type (1. Account, 2. Phone, 3. Card): ");
                scanf("%d", &transfer_type);
                TransferType type;
                switch (transfer_type) {
                    case 1:
                        type = TRANSFER_TYPE_ACCOUNT;
                        break;
                    case 2:
                        type = TRANSFER_TYPE_PHONE;
                        break;
                    case 3:
                        type = TRANSFER_TYPE_CARD;
                        break;
                    default:
                        printf("Invalid transfer type. Exiting...\n");
                        exit(0);
                }
                printf("%s\n", transfer(&atm, amount, recipient, type));
            } else if (choice == 4) {
                char pass_code[MAX_PASSCODE_LENGTH];
                printf("Enter 4 or 6 digit pass_code: ");
                scanf("%s", pass_code);
                printf("%s\npass_code: %s\n", get_balance(&atm), "****");
            } else if (choice == 5) {
                char pass_code[MAX_PASSCODE_LENGTH];
                printf("Enter 4 or 6 digit pass_code: ");
                scanf("%s", pass_code);
                print_transaction_history(&atm);
            } else if (choice == 6) {
                printf("Thank you for using ATM. Goodbye!\n");
                break;
            } else {
                printf("Invalid choice. Please enter a valid option.\n");
            }
        }
    } else {
        printf("Invalid User ID or PIN. Exiting...\n");
        exit(0);
    }
}

int main() {
    atm_interface();
    return 0;
}

