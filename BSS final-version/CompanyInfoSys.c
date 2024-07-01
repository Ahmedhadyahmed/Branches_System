#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <Windows.h>


//change text color
void setColor(const char* color) {
    printf("%s", color);
}

//delaing time
void delay(int milliseconds) 
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}
// Function to validate if the input is a number
int isvalid(char *input) {
    for (int i = 0; input[i] != '\0'; i++)  //text contain on "text+\0" ;So we did to to avoid it and don't count it
    {
        if (!isdigit(input[i])) //isdigit is a func. that see of the string is digit or no. 0->digit/1->!not digit
        // a-> not 0-9 it's.
        {
            return 0;  // Return 0 if a non-digit character is found
        }
    }
    return 1;  // Return 1 if all characters are digits
}
//It will return 1/0 because i want it be true or false false ^^

// Structure to hold branch data
struct branchesData {
    char branch_name[50];  // Branch name
    char branchid[30];     // Branch ID
    char managerid[30];    // Manager ID
    float reve[12];        // Revenue for each month
};

// Sorting function to sort indices based on revenue
void sorting(float revenues[], int indices[], int n) 
// indices is the arrow who will point of the elements
{
    // Bubble sort algorithm to sort indices based on revenues
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (revenues[indices[i]] < revenues[indices[j]]) 
            {  // Sort in descending order
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Print the sorted month indices
    printf("Sorted month indices based on revenue: ");
    for (int i = 0; i < n; i++) {
        printf("Month %d : Revenue = %0.1f\n", indices[i] + 1,revenues[indices[i]]); 
    }
    printf("\n");
}

int main() 
{
    setColor("\033[1;34m");
    int n;
    char input[10];
    char User_name[10];
    printf("\t\t\t\tHello sir,can you tell me your name (first & second),pls ?\n");
    gets(User_name);
    delay(500);
    printf(".");
    delay(1500);
    printf(".");
    delay(2000);
    printf(".\n");
    printf("Oh 0o0 , Hello Mr/s ");
    puts(User_name);
    printf("\n");
    // Prompt user to insert the number of branches
    printf("Please insert the number of the branches: ");
    while (1)
    {
        scanf("%s", input);
        if (isvalid(input))
        {  // Validate the input
            n = atoi(input);  // Convert valid input to an integer
            if (n > 0) 
            {
                break;  // Exit the loop if a valid number is entered
            } else 
            {
                printf("Number must be greater than 0. Please reinsert it: ");
            }
        } 
        else 
        {
            printf("Invalid input. Please enter a valid number: ");
        }
    }

    // Allocate memory for branches data
    struct branchesData* branches = (struct branchesData*)malloc(n * sizeof(struct branchesData));
    // Check if memory allocation was successful
    if (branches == NULL)
    {
        printf("Memory allocation failed!");
        return 1;
    }

    // Clear the input buffer
    getchar();  // Consume leftover newline character
    system("cls");
    // Taking data from the users
    for (int i = 0; i < n; i++) 
    {

        // Get branch name
        printf("Branch's name: ");
        //fgets(branches[i].branch_name, sizeof(branches[i].branch_name), stdin);
        //branches[i].branch_name[strcspn(branches[i].branch_name, "\n")] = 0; // Remove newline character
        gets(branches[i].branch_name);

        // Get branch ID
        printf("Branch's Id: ");
        scanf("%s", branches[i].branchid);
        
        // Get branch manager ID
        printf("Branch Manager ID: ");
        scanf("%s", branches[i].managerid);

        // Get revenue for each month
        printf("Write the revenue for each month: \n");
        for (int j = 0; j < 12; j++) 
        {
            printf("Month %d: ", j + 1);
            scanf("%f", &branches[i].reve[j]);
        }
        printf("The %dth branch finished\n", i + 1);

        // Clear the input buffer for the next branch name input
        getchar();
    }

    // See what user wants to do now
    int choose;
    int continue_program = 1;

    // Main loop to perform operations based on user choice
    while (continue_program) 
    {
        // Display menu options
        printf("\n\tWhich operation do you want to start:\n");
        printf("1. Get the total sales of this year (Branches' names).\n");
        printf("2. Get the share of the market.\n");
        printf("3. Get the peak sales of every branch and print the branch with the highest peak sales.\n");
        printf("4. Choose a branch and display sorted month indices based on sales revenue.\n");
        printf("5. Want to edit a specific branch or add new branch.\n");
        printf("6. Exit\n");
        scanf("%d", &choose);
        system("cls");
        switch (choose) {
        case 1: {
            float total_sales[n];
            for (int i = 0; i < n; i++) {
                total_sales[i] = 0;  // Initialize total sales for each branch
            }

            // Calculate total sales for each branch
            printf("The total sales of this year: \n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 12; j++) {
                    total_sales[i] += branches[i].reve[j];
                }
            }

            // Print total sales for each branch
            for (int i = 0; i < n; i++) {
                printf("Branch %s (ID: %s): %.2f\n", branches[i].branch_name, branches[i].branchid, total_sales[i]);
            }
            break;
        }
        case 2: {
            float total_revenue = 0;
            // Calculate total revenue of all branches
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 12; j++) {
                    total_revenue += branches[i].reve[j];
                }
            }

            float percent_of_share;
            printf("Write the branch name that you want to know its share: ");
            getchar(); // Clear the input buffer
            char branch_name[50];
            fgets(branch_name, sizeof(branch_name), stdin);
            branch_name[strcspn(branch_name, "\n")] = 0; // Remove newline character

            int found = 0;

            // Find the specified branch and calculate its market share
            for (int i = 0; i < n; i++) {
                if (strcmp(branch_name, branches[i].branch_name) == 0) {
                    float branch_revenue = 0;
                    for (int j = 0; j < 12; j++) {
                        branch_revenue += branches[i].reve[j];
                    }
                    percent_of_share = (branch_revenue / total_revenue) * 100;
                    found = 1;
                    printf("The market share of %s (ID: %s) is %.3f%%\n", branch_name, branches[i].branchid, percent_of_share);
                    break;
                }
            }

            if (!found) {
                printf("Branch not found.\n");
            }
            break;
        }
        case 3: {
            float peak_sales[n];
            // Calculate peak sales for each branch
            for (int i = 0; i < n; i++) {
                peak_sales[i] = branches[i].reve[0];
                for (int j = 1; j < 12; j++) {
                    if (branches[i].reve[j] > peak_sales[i]) {
                        peak_sales[i] = branches[i].reve[j];
                    }
                }
            }

            // Print peak sales for each branch
            printf("The peak sales of each branch: \n");
            for (int i = 0; i < n; i++) {
                printf("Branch %s (ID: %s): %.2f\n", branches[i].branch_name, branches[i].branchid,
                peak_sales[i]);
            }

            // Find the branch with the highest peak sales
            float highest_peak = peak_sales[0];
            int highest_peak_index = 0;
            for (int i = 1; i < n; i++) {
                if (peak_sales[i] > highest_peak) {
                    highest_peak = peak_sales[i];
                    highest_peak_index = i;
                }
            }

            printf("The branch with the highest peak sales is %s (ID: %s) with %.2f sales.\n",
            branches[highest_peak_index].branch_name, branches[highest_peak_index].branchid, highest_peak);
            break;
        }
        case 4: {
            // Prompt user to choose a branch
            printf("Choose a branch (1 to %d): ", n);
            int branch;
            scanf("%d", &branch);
            branch -= 1;  // Convert 1-based index to 0-based index
            if (branch < 0 || branch >= n) {
                printf("Invalid branch number. Please choose a branch between 1 and %d.\n", n);
                break;
            }

            // Create an array of indices
            int indices[12];
            for (int i = 0; i < 12; i++) {
                indices[i] = i;
            }

            // Sort the indices based on the chosen branch's revenues
            sorting(branches[branch].reve, indices, 12);
            break;
        }
        case 5: {
            //ask the user if he want to edit any information
            printf("Choose what you want to do:\n 1.edit specific branch.\n2.add new branch.\n");
            int choice;
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
            {
                printf("Choose a branch to edit (1 to %d): ",n);
                int edit_branch;
                scanf("%d",&edit_branch);
                edit_branch -=1; //to return the index to the original one
                if (edit_branch < 0 || edit_branch >= n) 
                {
                    printf("Invalid branch number. Please choose a branch between 1 and %d.\n", n);
                    break;
                }
                //see which one i want to edit
                printf("\t\t\t\t\tWhat do you want to edit?\n");
                printf("1. Branch name\n");
                printf("2. Branch ID\n");
                printf("3. Branch Manager ID\n");
                printf("4. Monthly revenue\n");
                int edit_choce;
                scanf("%d",&edit_choce);
                switch (edit_choce)
                {
                case 1:
                {
                    printf("write the new name: ");
                    gets(branches[edit_branch].branch_name);
                    break;
                }
                case 2:
                {
                    printf("write the new Branch ID: ");
                    gets(branches[edit_branch].branchid);
                    break;
                }
                case 3:
                {
                    printf("write the new Manager ID: ");
                    gets(branches[edit_branch].managerid);
                    break;
                }
                case 4:
                {
                    printf("write the new renvenues: ");
                    for (int z = 0; z < 12; z++)
                    {
                        printf("Month %d : ",z+1);
                        //gets(branches[edit_branch].reve);
                        scanf("%d",&branches[edit_branch].reve[z]);
                        printf("\n");
                    }
                    
                    break;
                }
            }
            
            case 2:
            {
                printf("Write the how much branch you want to add: ");
                int added_branches;
                scanf("%d",&added_branches);
                int printfbegin =
                n += added_branches;
                struct branchesData* branches = (struct branchesData*)realloc
                (branches, n * sizeof(struct branchesData));
                for (int i = printfbegin+1; i < n; i++)
                {
                    printf("Name: ");
                    gets(branches[i].branch_name);
                    printf("\nBranch ID: ");
                    scanf("%d",&branches[i].branchid);
                    printf("\nManager ID: ");
                    scanf("%d",&branches[i].managerid);
                    printf("\nwrite the revenues of this month\n");
                    for (int p = 0; p < 12; p++)
                    {
                        printf("Month %d: ",p+1);
                        scanf("%d",&branches[i].reve[p]);
                    }
                    
                }
                
            }
        }
        case 6:
            continue_program = 0;  // Exit the program
            printf("Exiting the application.\n");
            break;
        default:
            printf("Invalid input :(\n");
            break;
        }

        if (continue_program) {
            // Ask the user if they want to continue
            printf("Do you want to continue? 0-for exit, 1-to stay: ");
            int continue_choice;
            scanf("%d", &continue_choice);
            if (continue_choice == 0) {
                continue_program = 0;  // Exit the program
                printf("Exiting the application.\n");
            }
        }
        system("cls");
    }

    // Free allocated memory
    free(branches);
    
    return 0;
}