# Patient COVID Positive Checker
# Developed using Python but already tried this in C in my first year

def load_patients():
    patients = []
    try:
        with open("patients.txt", "r") as file:
            for line in file:
                data = line.strip().split(",")
                patient = {
                    "id": data[0],
                    "name": data[1].lower(),
                    "age": data[2],
                    "gender": data[3],
                    "address": data[4],
                    "contact": data[5],
                    "test_date": data[6],
                    "status": data[7]
                }
                patients.append(patient)
    except FileNotFoundError:
        print("Patient data file not found.")
    return patients


def display_patient(p):
    print("\n--- Patient COVID Details ---")
    print("Name        :", p["name"].title())
    print("Age         :", p["age"])
    print("Gender      :", p["gender"])
    print("Address     :", p["address"])
    print("Contact     :", p["contact"])
    print("Test Date   :", p["test_date"])
    print("COVID Status:", p["status"])
    print("------------------------------")


def symptom_check():
    print("\n--- Symptom Check ---")
    cold = int(input("Cold (0-No, 1-Yes): "))
    fever = int(input("Fever (0-No, 1-Yes): "))
    throat = int(input("Throat Pain (0-No, 1-Yes): "))
    body_pain = int(input("Body Pain (0-No, 1-Yes): "))
    breathing = int(input("Breathing Issue (0-No, 1-Yes): "))

    count = cold + fever + throat + body_pain + breathing

    if count >= 3:
        print("\nHealth Advice: High symptoms detected. Doctor consultation required.")
    else:
        print("\nHealth Advice: Mild symptoms. Home rest advised.")

    return count


def billing(symptom_count):
    print("\n--- Billing Section ---")
    consultation_fee = 200
    test_fee = 500 if symptom_count >= 3 else 0
    medicine_fee = 300 if symptom_count >= 2 else 150

    total = consultation_fee + test_fee + medicine_fee

    print("Consultation Fee : Rs.", consultation_fee)
    print("Medicine Fee     : Rs.", medicine_fee)
    print("COVID Test Fee   : Rs.", test_fee)
    print("-------------------------------")
    print("Total Bill       : Rs.", total)
    print("-------------------------------")


def search_patient(patients):
    choice = input("\nSearch by ID or Name? (id/name): ").lower()

    if choice == "id":
        key = input("Enter Patient ID: ")
        for p in patients:
            if p["id"] == key:
                display_patient(p)
                symptoms = symptom_check()
                billing(symptoms)
                return

    elif choice == "name":
        key = input("Enter Patient Name: ").lower()
        for p in patients:
            if p["name"] == key:
                display_patient(p)
                symptoms = symptom_check()
                billing(symptoms)
                return

    print("Patient not found.")


def main():
    patients = load_patients()

    while True:
        print("\n1. Search Patient")
        print("2. Exit")
        choice = input("Enter choice: ")

        if choice == "1":
            search_patient(patients)
        elif choice == "2":
            print("Exiting system.")
            break
        else:
            print("Invalid choice.")


main()

