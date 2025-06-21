#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Student {
    char name[50];
    char enrollNo[20];
    char address[100];
    char phoneNo[15];
    char email[50];
};

// Function to clear input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Function to validate email format
int isValidEmail(const char *email) {
    int atCount = 0;
    int dotCount = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') atCount++;
        if (email[i] == '.') dotCount++;
    }
    return atCount == 1 && dotCount >= 1;
}

// Function to validate phone number (only digits)
int isValidPhoneNumber(const char *phoneNo) {
    for (int i = 0; phoneNo[i] != '\0'; i++) {
        if (!isdigit(phoneNo[i])) return 0;
    }
    return 1;
}

// Function to read students from the file
int readStudentsFromFile(struct Student students[]) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", students[count].name, students[count].enrollNo,
                  students[count].address, students[count].phoneNo, students[count].email) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

// Function to save students back to the file
void saveStudentsToFile(struct Student students[], int count) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n", students[i].name, students[i].enrollNo, students[i].address, students[i].phoneNo, students[i].email);
    }

    fclose(file);
}

// Function to add a new student
void addStudent() {
    struct Student student;
    printf("Enter student details (name, enrollment number, address, phone, email):\n");

    clearInputBuffer();
    printf("Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';  // Remove newline character

    printf("Enrollment No: ");
    fgets(student.enrollNo, sizeof(student.enrollNo), stdin);
    student.enrollNo[strcspn(student.enrollNo, "\n")] = '\0';  // Remove newline character

    printf("Address: ");
    fgets(student.address, sizeof(student.address), stdin);
    student.address[strcspn(student.address, "\n")] = '\0';  // Remove newline character

    printf("Phone No: ");
    fgets(student.phoneNo, sizeof(student.phoneNo), stdin);
    student.phoneNo[strcspn(student.phoneNo, "\n")] = '\0';  // Remove newline character

    if (!isValidPhoneNumber(student.phoneNo)) {
        printf("Invalid phone number. It must contain only digits.\n");
        return;
    }

    printf("Email: ");
    fgets(student.email, sizeof(student.email), stdin);
    student.email[strcspn(student.email, "\n")] = '\0';  // Remove newline character

    if (!isValidEmail(student.email)) {
        printf("Invalid email format.\n");
        return;
    }

    FILE *file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", student.name, student.enrollNo, student.address, student.phoneNo, student.email);
    fclose(file);

    printf("Student added successfully!\n");
}

// Function to display all students
void displayStudents() {
    struct Student students[100];
    int studentCount = readStudentsFromFile(students);

    if (studentCount == 0) {
        printf("No students found.\n");
        return;
    }

    printf("\nStudent Details:\n");
    printf("Name\tEnroll No\tAddress\t\tPhone No\tEmail\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%s\t%s\t%s\t%s\t%s\n", students[i].name, students[i].enrollNo, students[i].address, students[i].phoneNo, students[i].email);
    }
}

// Function to search for a student by enrollment number
void searchStudent() {
    char enrollNo[20];
    printf("Enter enrollment number to search: ");
    clearInputBuffer();
    fgets(enrollNo, sizeof(enrollNo), stdin);
    enrollNo[strcspn(enrollNo, "\n")] = '\0';  // Remove newline character

    struct Student students[100];
    int studentCount = readStudentsFromFile(students);
    int found = 0;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].enrollNo, enrollNo) == 0) {
            printf("\nStudent found!\n");
            printf("Name: %s\n", students[i].name);
            printf("Enrollment No: %s\n", students[i].enrollNo);
            printf("Address: %s\n", students[i].address);
            printf("Phone No: %s\n", students[i].phoneNo);
            printf("Email: %s\n", students[i].email);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with enrollment number %s not found.\n", enrollNo);
    }
}

// Function to delete a student by enrollment number
void deleteStudent() {
    char enrollNo[20];
    printf("Enter enrollment number to delete: ");
    clearInputBuffer();
    fgets(enrollNo, sizeof(enrollNo), stdin);
    enrollNo[strcspn(enrollNo, "\n")] = '\0';  // Remove newline character

    struct Student students[100];
    int studentCount = readStudentsFromFile(students);
    int found = 0;

    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].enrollNo, enrollNo) != 0) {
            fprintf(file, "%s,%s,%s,%s,%s\n", students[i].name, students[i].enrollNo, students[i].address, students[i].phoneNo, students[i].email);
        } else {
            found = 1;
        }
    }

    fclose(file);

    if (found) {
        printf("Student with enrollment number %s deleted successfully!\n", enrollNo);
    } else {
        printf("Student with enrollment number %s not found.\n", enrollNo);
    }
}

// Function to modify a student's details
void modifyStudent() {
    char enrollNo[20];
    printf("Enter enrollment number to modify: ");
    clearInputBuffer();
    fgets(enrollNo, sizeof(enrollNo), stdin);
    enrollNo[strcspn(enrollNo, "\n")] = '\0';  // Remove newline character

    struct Student students[100];
    int studentCount = readStudentsFromFile(students);
    int found = 0;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].enrollNo, enrollNo) == 0) {
            printf("Modify student details:\n");

            printf("New Name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';  // Remove newline character

            printf("New Address: ");
            fgets(students[i].address, sizeof(students[i].address), stdin);
            students[i].address[strcspn(students[i].address, "\n")] = '\0';  // Remove newline character

            printf("New Phone No: ");
            fgets(students[i].phoneNo, sizeof(students[i].phoneNo), stdin);
            students[i].phoneNo[strcspn(students[i].phoneNo, "\n")] = '\0';  // Remove newline character

            if (!isValidPhoneNumber(students[i].phoneNo)) {
                printf("Invalid phone number. It must contain only digits.\n");
                return;
            }

            printf("New Email: ");
            fgets(students[i].email, sizeof(students[i].email), stdin);
            students[i].email[strcspn(students[i].email, "\n")] = '\0';  // Remove newline character

            if (!isValidEmail(students[i].email)) {
                printf("Invalid email format.\n");
                return;
            }

            found = 1;
            break;
        }
    }

    if (found) {
        saveStudentsToFile(students, studentCount);
        printf("Student details modified successfully!\n");
    } else {
        printf("Student with enrollment number %s not found.\n", enrollNo);
    }
}

// Main function
int main() {
    int choice;
    do {
        printf("Name : Prince kumar \nAdmission no. : 24SCSE2030311\n");
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Modify Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                modifyStudent();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
