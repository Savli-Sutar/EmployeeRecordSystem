#include <stdio.h>
#include<stdlib.h> // For the function malloc() and free()
// Using struct to using different datatypes to store different data
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

int main(){
    int n;
    struct Employee *ptr;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    // the malloc measures the amount of employees there are (n), and allocaates that much memory only
    ptr = (struct Employee*) malloc(n * sizeof(struct Employee));
    if(ptr == NULL){
        return 1;
    }
    //Calling the function
    inputDetails(ptr,n);
    sortByExperience(ptr,n);
    displayEmployees(ptr,n);

     free(ptr); // Deallocates the previously allocated memory 
    return 0; 
}
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
   

    
    
   


