#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_COFFEE 100
int num_coffee = 0;

struct coffeestar
{
    char name[100];
    double price;
    int quantity;
} coffee[MAX_COFFEE];

void welcome()
{
    printf("\n\n");
    printf("\x1b[34m");
    printf("     ##             ###     ######  ##   ##  #######           ####     #######             ####     ###     ####### #######  \n");
    printf("\x1b[34m");
    Sleep(500);
    printf("     ##            ## ##      ##    ### ###   ##   #            ##       ##   #            ##  ##   ## ##     ##   #  ##   #  \n");
    printf("\x1b[36m");
    Sleep(500);
    printf("     ##           ##   ##     ##    #######   ##                ##       ##               ##       ##   ##    ##      ##      \n");
    printf("\x1b[36m");
    Sleep(500);
    printf("     ##           ##   ##     ##    ## # ##   ####              ##       ####             ##       ##   ##    ####    ####    \n");
    printf("\x1b[36m");
    Sleep(500);
    printf("##   ##           #######     ##    ##   ##   ##                ##       ##               ##       #######    ##      ##      \n");
    printf("\x1b[34m");
    Sleep(500);
    printf(" ## ##            ##   ##     ##    ##   ##   ##   #            ##  ##   ##   #            ##  ##  ##   ##    ##      ##   #  \n");
    printf("\x1b[34m");
    Sleep(500);
    printf("  ###    ####     ##   ##   ######  ### ###  #######           #######  #######             ####   ##   ##   ####    #######  \n");
    printf("         ####                                                                                                                 \n");
    printf("\x1b[0m");
    printf("\n");
    printf("                                        WELCOME TO OUR COFFEESHOP !                                                           \n");
    printf("          Our dedicated team is here to ensure you have a delightful coffee experience every time you visit.                  \n");
    printf("                                              since 1990                                                                      \n");

    Sleep(2500);
    system("cls");
}

void displayCoffeeMenu()
{
    printf("\n\n              * Coffee Menu *    \n");
    for (int i = 0; i < num_coffee; i++)
    {
        printf("%d. %s ", i + 1, coffee[i].name);
        printf(" = %.1lf Taka", coffee[i].price);
        printf("  (%d available)\n", coffee[i].quantity);
    }
}

void menu()
{
    printf("\n| M | e | n | u |\n");
    printf("-----------------\n");
    Sleep(30);
    printf("1. Display Coffee Menu\n");
    Sleep(30);
    printf("2. Order Coffee\n");
    Sleep(30);
    printf("3. Add Coffee Item\n");
    Sleep(30);
    printf("4. Delete Coffee Item\n");
    Sleep(30);
    printf("5. Edit Coffee Item from File\n");
    Sleep(30);
    printf("6. Save Coffee Data to File\n");
    Sleep(30);
    printf("7. Exit\n");
    Sleep(30);
    printf("8. Search Coffee by Name\n");
}

int searchCoffee(const char *targetName)
{
    for (int i = 0; i < num_coffee; i++)
    {
        if (strcmp(coffee[i].name, targetName) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addCoffee(const char *name, double price, int quantity)
{
    if (num_coffee < MAX_COFFEE)
    {
        strcpy(coffee[num_coffee].name, name);
        coffee[num_coffee].price = price;
        coffee[num_coffee].quantity = quantity;
        num_coffee++;
        printf("\nAdded %d %s for %.1lf Taka each to the inventory.\n", quantity, name, price);
    }
    else
    {
        printf("Inventory is full. Cannot add more items.\n");
    }
}

void replaceCoffee()
{
    char oldName[100];
    printf("Enter the name of the coffee to replace: ");
    scanf("%s", oldName);

    int foundIndex = searchCoffee(oldName);

    if (foundIndex != -1)
    {
        char newName[100];
        printf("Enter the name of the new coffee: ");
        scanf("%s", newName);

        printf("Replacing coffee item '%s' with new data.\n", oldName);
        strcpy(coffee[foundIndex].name, newName);

        double newPrice;
        int newQuantity;

        printf("Enter the new price : ");
        scanf("%lf", &newPrice);
        printf("Enter the new quantity : ");
        scanf("%d", &newQuantity);

        coffee[foundIndex].price = newPrice;
        coffee[foundIndex].quantity = newQuantity;

        printf("\nReplacement successful.\n");
    }
    else
    {
        printf("\nCoffee item '%s' not found in the inventory. Replacement failed.\n", oldName);
    }
}

void deleteCoffee(int index)
{
    if (index >= 0 && index < num_coffee)
    {
        printf("Deleted %s from the inventory.\n", coffee[index].name);
        for (int i = index; i < num_coffee - 1; i++)
        {
            strcpy(coffee[i].name, coffee[i + 1].name);
            coffee[i].price = coffee[i + 1].price;
            coffee[i].quantity = coffee[i + 1].quantity;
        }
        num_coffee--;
    }
    else
    {
        printf("Invalid index. Item deletion failed.\n");
    }
}

void orderCoffee()
{
    char targetName[100];
    printf("Enter the name of the coffee to order: ");
    scanf("%s", targetName);

    int foundIndex = searchCoffee(targetName);
    if (foundIndex != -1)
    {
        printf("%s found at serial %d\n", targetName, foundIndex + 1);
        printf("Price: %.1lf Taka, Quantity: %d available\n", coffee[foundIndex].price, coffee[foundIndex].quantity);

        int quantityToOrder;
        printf("Enter the quantity to order: ");
        scanf("%d", &quantityToOrder);

        if (quantityToOrder <= 0)
        {
            printf("Invalid quantity. Order canceled.\n");
        }
        else if (quantityToOrder <= coffee[foundIndex].quantity)
        {
            coffee[foundIndex].quantity -= quantityToOrder;
            printf("\n\n");
            printf("\x1b[33morder\x1b[0m ");
            Sleep(400);
            printf("\x1b[32mprocessing\x1b[0m");
            Sleep(600);
            printf("\n=====================================\n");
            printf("            Order Receipt            \n");
            printf("=====================================\n");
            Sleep(1000);
            printf("Coffee : %s\n", coffee[foundIndex].name);
            printf("Price per unit : %.1lf Taka\n", coffee[foundIndex].price);
            printf("Quantity ordered : %d\n", quantityToOrder);
            printf("Total cost : \x1b[35m %.1lf Taka \x1b[0m\n", quantityToOrder * coffee[foundIndex].price);
            Sleep(1000);
            printf("=====================================\n");
            printf("      Thank you for your order!      \n");
            printf("=====================================\n");
            printf("\n\n");
        }
        else
        {
            printf("Insufficient quantity in inventory.\n");
        }
    }
    else
    {
        printf("%s not found in the inventory. Order canceled.\n", coffee[foundIndex].name);
    }
}

void loadCoffeeDataFromFile()
{
    FILE *file = fopen("coffee_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char name[100];
    double price;
    int quantity;
    while (fscanf(file, "%[^,],%lf,%d\n", name, &price, &quantity) != EOF)
    {
        addCoffee(name, price, quantity);
    }
    fclose(file);
}

void saveCoffeeData()
{
    FILE *file = fopen("coffee_data.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < num_coffee; i++)
    {
        fprintf(file, "%s,%.1lf,%d\n", coffee[i].name, coffee[i].price, coffee[i].quantity);
    }
    fclose(file);
    printf("Coffee data saved to 'coffee_data.txt'.\n");
}

void searchCoffeeByName()
{
    char searchLetters[100];
    printf("Enter the starting letters to search for in coffee names: ");
    scanf("%s", searchLetters);

    printf("\nSearch results for names starting with '%s':\n", searchLetters);

    int foundCount = 0;
    for (int i = 0; i < num_coffee; i++)
    {
        if (strncmp(coffee[i].name, searchLetters, strlen(searchLetters)) == 0)
        {
            printf("%d. %s ", i + 1, coffee[i].name);
            printf(" = %.1lf Taka", coffee[i].price);
            printf("  (%d available)\n", coffee[i].quantity);
            foundCount++;
        }
    }

    if (foundCount == 0)
    {
        printf("No coffee items found with names starting with '%s'.\n", searchLetters);
    }
}


int main()
{
    loadCoffeeDataFromFile();
    system("cls");
    welcome();
    int choice;
    while (1)
    {
        menu();
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayCoffeeMenu();
            break;
        case 2:
            orderCoffee();
            break;
        case 3:
            printf("Enter the details for the new coffee item :\n");
            char newName[100];
            double newPrice;
            int newQuantity;
            printf("Enter coffee name: ");
            scanf("%s", newName);
            printf("Enter price: ");
            scanf("%lf", &newPrice);
            printf("Enter quantity: ");
            scanf("%d", &newQuantity);
            addCoffee(newName, newPrice, newQuantity);
            saveCoffeeData();
            break;
        case 4:
            printf("Enter the name of the coffee item to delete : ");
            char deleteName[100];
            scanf("%s", deleteName);
            int deleteIndex = searchCoffee(deleteName);
            if (deleteIndex != -1)
            {
                deleteCoffee(deleteIndex);
                saveCoffeeData();
            }
            else
            {
                printf("Coffee item '%s' not found in the inventory.\n", deleteName);
            }
            break;
        case 5:
            replaceCoffee();
            saveCoffeeData();
            break;
        case 6:
            saveCoffeeData();
            break;
        case 7:
            return 0;
        case 8:
            searchCoffeeByName();
            printf("\nPress Enter to go back to the main menu...");
            while (getchar() != '\n');     
            getchar(); 
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
