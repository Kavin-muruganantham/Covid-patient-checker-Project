# Covid-patient-checker-Project
This C program collects a patient's personal details and checks for four symptoms: cold, fever, throat pain, and body pain. If all symptoms are present, the patient is marked as COVID positive and advised hospital admission. If only some symptoms are present, the result is COVID negative.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAME "patients.txt"
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char address[100];
    char contact[15];
    char testDate[15];
    int cold, fever, throatPain, bodyPain;
    char status[10];
} Patient;
void diagnose(Patient *p) {
    if (p->cold && p->fever && p->throatPain && p->bodyPain) {
        strcpy(p->status, "Positive");
    } else {
        strcpy(p->status, "Negative");
    }
}
void showPrescription(Patient p) {
    printf("\n--- Doctor's Prescription ---\n");
    if (strcmp(p.status, "Positive") == 0) {
        printf("Status: COVID POSITIVE\n");
        printf("→ Patient must be admitted in hospital.\n");
        printf("→ Stay in isolation ward.\n");
        printf("→ Monitor oxygen level and temperature daily.\n");
        printf("→ Take all prescribed medicines without skipping.\n");
        printf("→ Drink plenty of warm fluids.\n");
    } else if (p.cold || p.fever || p.throatPain || p.bodyPain) {
        printf("Status: COVID NEGATIVE (Symptomatic)\n");
        printf("→ Take rest at home for 5-7 days.\n");
        printf("→ Drink warm water and soups.\n");
        printf("→ Avoid cold drinks and exposure to dust.\n");
        printf("→ Continue prescribed medicines.\n");
        printf("→ Re-test if symptoms worsen.\n");
    } else {
        printf("No symptoms detected.\n");
        printf("→ Stay safe and maintain social distance.\n");
        printf("→ Follow COVID precautions.\n");
    }
}
void generateBill(Patient p) {
    int medicineCost = 0, bedCharge = 0;
    printf("\n--- Medical Bill ---\n");
    printf("Patient: %s (ID: %d)\n", p.name, p.id);
    printf("Date: %s\n", p.testDate);
    printf("Status: %s\n", p.status);
    printf("Symptoms: ");
    if (p.cold) printf("Cold ");
    if (p.fever) printf("Fever ");
    if (p.throatPain) printf("Throat Pain ");
    if (p.bodyPain) printf("Body Pain ");
    printf("\n");
    printf("\nMedicines:\n");
    if (p.cold) {
        printf(" - Cold Relief Syrup: ₹100\n");
        medicineCost += 100;
    }
    if (p.fever) {
        printf(" - Paracetamol Tablets: ₹80\n");
        medicineCost += 80;
    }
    if (p.throatPain) {
        printf(" - Lozenges: ₹50\n");
        medicineCost += 50;
    }
    if (p.bodyPain) {
        printf(" - Pain Reliever: ₹120\n");
        medicineCost += 120;
    }

    if (strcmp(p.status, "Positive") == 0) {
        bedCharge = 2000;
        printf(" - Hospital Bed Charges: ₹%d\n", bedCharge);
    }

    int total = medicineCost + bedCharge;
    printf("\nTotal Bill: ₹%d\n", total);
    showPrescription(p);
}
void savePatient(Patient p) {
    FILE *fp = fopen(FILENAME, "a");
    if (!fp) {
        printf("Error saving data.\n");
        return;
    }
    fprintf(fp, "%d %s %d %s %s %s %s %d %d %d %d %s\n",
        p.id, p.name, p.age, p.gender, p.address, p.contact, p.testDate,
        p.cold, p.fever, p.throatPain, p.bodyPain, p.status);
    fclose(fp);
}

void addPatient() {
    Patient p;
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar();
    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Gender: ");
    scanf("%s", p.gender);
    getchar();
    printf("Enter Address: ");
    fgets(p.address, sizeof(p.address), stdin);
    p.address[strcspn(p.address, "\n")] = '\0';
    printf("Enter Contact Number: ");
    scanf("%s", p.contact);
    printf("Enter Test Date (YYYY-MM-DD): ");
    scanf("%s", p.testDate);
    printf("\nEnter Symptoms (1 = Yes, 0 = No):\n");
    printf("Cold: "); scanf("%d", &p.cold);
    printf("Fever: "); scanf("%d", &p.fever);
    printf("Throat Pain: "); scanf("%d", &p.throatPain);
    printf("Body Pain: "); scanf("%d", &p.bodyPain);
    diagnose(&p);
    generateBill(p);
    savePatient(p);

    printf("\n✅ Patient data saved successfully.\n");
}
void searchByID(int id) {
    FILE *fp = fopen(FILENAME, "r");
    Patient p;
    int found = 0;
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    while (fscanf(fp, "%d %s %d %s %s %s %s %d %d %d %d %s",
        &p.id, p.name, &p.age, p.gender, p.address, p.contact,
        p.testDate, &p.cold, &p.fever, &p.throatPain, &p.bodyPain, p.status) != EOF) {
        if (p.id == id) {
            found = 1;
            generateBill(p);
            break;
        }
    }
    if (!found) printf("❌ No patient with ID %d found.\n", id);
    fclose(fp);
}
void searchByName(char *name) {
    FILE *fp = fopen(FILENAME, "r");
    Patient p;
    int found = 0;
    if (!fp) {
        printf("No records found.\n");
        return;
    }
    while (fscanf(fp, "%d %s %d %s %s %s %s %d %d %d %d %s",
        &p.id, p.name, &p.age, p.gender, p.address, p.contact,
        p.testDate, &p.cold, &p.fever, &p.throatPain, &p.bodyPain, p.status) != EOF) {
        if (strcmp(p.name, name) == 0) {
            found = 1;
            generateBill(p);
            break;
        }
    }
    if (!found) printf("❌ No patient with name '%s' found.\n", name);
    fclose(fp);
}
int main() {
    int choice, id;
    char name[50];
    while (1) {
        printf("\n==== COVID POSITIVE CHECKER ====\n");
        printf("1. Add New Patient\n");
        printf("2. Search by Patient ID\n");
        printf("3. Search by Patient Name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear newline

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                searchByID(id);
                break;
            case 3:
                printf("Enter Patient Name: ");
                scanf("%s", name);
                searchByName(name);
                break;
            case 4:
                printf("Exiting... Stay safe! 😷\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
