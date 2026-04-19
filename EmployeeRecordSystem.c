#include <stdio.h>
#include<stdlib.h> // For the function malloc() and free()
// Using struct to using different datatypes to store different data
#include<string.h>
struct Employee {
    int id;
    char name[50];
    char designation[50];
    float experience;
    float salary;
};
// Function Prototypes
void inputDetails(struct Employee * ptr, int n);
void sortByExperience(struct Employee * ptr, int n);
void displayEmployees(struct Employee * ptr, int n);
void searchById(struct Employee * ptr, int n, int targetId);
int deleteEmployee(struct Employee * ptr,int n, int targetId);
void updateEmployee(struct Employee *ptr, int n, int targetId);


int main(){
    int n, choice, searchId;
    struct Employee *ptr;

    printf("Enter number of employees: ");
    scanf("%d", &n);
    // the malloc measures the amount of employees there are (n), and allocaates that much memory only
    ptr = (struct Employee*) malloc(n * sizeof(struct Employee));
    if(ptr == NULL){
        printf("Memory allocation failed\n");
        return 1; // tells the system the operation failed
    }
    //Calling the function
    inputDetails(ptr,n);
    // inputing switch cases for menu-driven program
    do{
        printf("\n......Employee Record System......");
        printf("\n 1. Display all Employees (Sorted by experience) ");
        printf("\n 2. Search Employee by Id");
        printf("\n 3. Add a new Employee");
        printf("\n 4. Remove Employee");
        printf("\n 5. Edit/Update Employee Details");
        printf("\n 6. Exit");
        printf("\n Select an option\n");
        scanf("%d", &choice);
    
        

        switch (choice) {
            case 1:
            sortByExperience(ptr, n);
            displayEmployees(ptr, n);
            break;

            case 2:
            printf("Enter Employee Id:\n ");
            scanf("%d",&searchId);
            searchById(ptr,n,searchId);
            break;

            case 3:
            n++; // Increases the amount of employees
            //realloc changes the size of previously assigned memory block(increases in this case)
            ptr = (struct Employee*) realloc(ptr, n * sizeof(struct Employee));
            if (ptr == NULL){
                printf("Memory Allocation failed. \n System out of resources\n");
                return 1; // tells the system the operation failed
            }
            printf("\nEnter details for the new employee:\n");
            // Using (ptr + n -1) to point to the newly created slot
            inputDetails(ptr + (n - 1), 1);
            printf("Employee added successfully!\n");
            break;

            case 4:
            printf("Enter Id to delete: ");
            scanf("%d", &searchId);
            int new_n = deleteEmployee(ptr, n, searchId);
    
            if (new_n != n) { // If someone was actually deleted
              n = new_n;
            if (n > 0) { 
              ptr = (struct Employee*) realloc(ptr, n * sizeof(struct Employee));
            } else {
            // If the last employee was deleted, free the pointer
               free(ptr);
               ptr = NULL; 
             }
            }
            break;

            case 5:
            printf("Enter ID to edit: ");
                scanf("%d", &searchId);
                updateEmployee(ptr, n, searchId);
                break;

            case 6:
            printf(" Exiting the program...\n");
            break;

            default:
            printf("Invalid choice! Please try again.\n");

        }
    } while(choice != 6);

     free(ptr); // Deallocates the previously allocated memory 
    return 0; 
}
// adds all the data from the user to the system
void inputDetails(struct Employee * ptr, int n){
    int i;
    for(i = 0; i<n; i++){
        printf("\n Display the details of the Employee %d:\n", i+1);
        printf("ID: ");
        scanf(" %d", &(ptr+i)-> id); //Points to the specific ID slot
         while ((getchar()) != '\n');
        printf("Name: ");
        scanf(" %[^\n]s",(ptr+i)-> name); //Points to the specific Name slot
        while ((getchar()) != '\n');
        printf("Designation: ");
        scanf(" %[^\n]s",(ptr+i)-> designation); // Points to the specific Designation slot
        while ((getchar()) != '\n');
        printf("Experience(years): ");
        scanf(" %f",&(ptr+i)-> experience); //Points to the specific Experience slot
        while ((getchar()) != '\n');
        printf("Salary: ");
        scanf(" %f",&(ptr+i)-> salary); // Points to the specific  Salary slot
        while ((getchar()) != '\n'); 
    }

}
// sorting employee record according to experience
void sortByExperience(struct Employee * ptr, int n){
    int i,j;
    struct Employee temp;
    // Sprting by experience
    // using i for counter of the number of times passing through the list of employees
    // using j for comparing two consecutive memory locations in the list
    for(i = 0; i < n-1; i++){
        for(j = 0; j < n- i - 1; j++){
            if((ptr + j)-> experience < (ptr + j + 1)-> experience){
                // Swapping using call my reference
                temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }

        }
    }

}

void displayEmployees(struct Employee * ptr, int n){
    int i;
    // Display Sorted Employees
    printf("\n......Employees Sorted by Experience......\n");
    for(i = 0; i < n; i++){
        printf("%s | %.1f years exp | ID %05d | %.2f Rs/- | %s \n",(ptr + i)->name,(ptr + i)->experience,(ptr + i)->id,(ptr +i)->salary,(ptr + i)->designation);

    }

}
// searches details of employee with id
void searchById(struct Employee * ptr, int n, int targetId){
    int found = 0;
    int i;
    for(i = 0; i < n; i++){
        if((ptr + i)->id == targetId){
        printf("\n......Record Found......\n");
        printf(" Name: %s | Experience: %.1f years exp | ID: %05d |Salary: %.2f Rs/- | Designation: %s \n",(ptr + i)->name,(ptr + i)->experience,(ptr + i)->id,(ptr +i)->salary,(ptr + i)->designation);
        found = 1;
        break;

        }
    }
    if(!found){
        printf("\n Employee with Id %05d not found.\n",targetId);
    }
}
// deletes employee record from system
  int deleteEmployee(struct Employee * ptr, int n, int targetId){
    int foundIndex = -1; // by giving index the initial value -1 indicates the targetId is not present in the list
    for(int i = 0; i < n; i++){
        if ((ptr + i)->id == targetId){
            foundIndex = i; // changes the initial value to the one where the targetId is present
            break;
        }
    }
    if(foundIndex == -1){
        printf("Employee Id %05d not found.\n",targetId);
        return n; // returning original value as nothing was deleted
        
    }
    for (int i = foundIndex; i< n-1 ; i++){
        *(ptr + i) = *(ptr + i + 1);

    }
    printf("Employee Id %05d removed successfully.\n",targetId);
    return n-1; // returning new value as the slot was deleted
  } 
  // updates the details of the existing employees
  void updateEmployee(struct Employee * ptr, int n, int targetId){
    int i, found = 0;
    for(i = 0; i < n; i++) {
        if((ptr + i)->id == targetId) {
            found = 1;
            printf("\nRecord Found! Updating details for %s\n", (ptr + i)->name);
            
            printf("Enter New Designation: ");
            while ((getchar()) != '\n'); // Clear buffer
            scanf("%[^\n]s", (ptr + i)->designation);
            
            printf("Enter New Salary: ");
            scanf("%f", &(ptr + i)->salary);
            
            printf("Record updated successfully!\n");
            break;
        }
    }
    if(!found) printf("Employee with ID %05d not found.\n", targetId);
}
  

    
    
   


