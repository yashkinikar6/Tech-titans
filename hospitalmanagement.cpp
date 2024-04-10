#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations
class Doctor;
class Patient;

// Enum for appointment status
enum class AppointmentStatus {
    SCHEDULED,
    CANCELLED,
    COMPLETED
};

// Class to represent a Date
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    void display() const {
        cout << day << "/" << month << "/" << year;
    }
};

// Class to represent an Appointment
class Appointment {
private:
    Doctor* doctor;
    Patient* patient;
    Date date;
    AppointmentStatus status;

public:
    Appointment(Doctor* doc, Patient* pat, Date dt) : doctor(doc), patient(pat), date(dt), status(AppointmentStatus::SCHEDULED) {}

    void cancelAppointment() {
        status = AppointmentStatus::CANCELLED;
    }

    void completeAppointment() {
        status = AppointmentStatus::COMPLETED;
    }

    void display() const;
};

// Class to represent a Doctor
class Doctor {
private:
    string name;
    string specialization;
    vector<Appointment*> appointmentList; // Changed name from appointments to appointmentList

public:
    Doctor(string nm, string spec) : name(nm), specialization(spec) {}

    string getName() const {
        return name;
    }

    void addAppointment(Appointment* appointment) {
        appointmentList.push_back(appointment);
    }

    void displayAppointments() const;
};

// Class to represent a Patient
class Patient {
private:
    string name;
    vector<string> medicalHistory;

public:
    Patient(string nm) : name(nm) {}

    string getName() const {
        return name;
    }

    void addMedicalRecord(string record) {
        medicalHistory.push_back(record);
    }

    const vector<string>& getMedicalHistory() const {
        return medicalHistory;
    }
};

// Class to handle data input
class DataInput {
public:
    static bool askForData() {
        char choice;
        cout << "Do you want to insert new data? (y/n): ";
        cin >> choice;
        return (choice == 'y' || choice == 'Y');
    }

    static void inputData(Patient& patient) {
        string record;
        cout << "Enter patient's medical record: ";
        cin >> record;
        patient.addMedicalRecord(record);
    }
};

// Class to represent Hospital Management System
class HospitalManagementSystem {
private:
    vector<Doctor> doctors;
    vector<Patient> patients;

public:
    // Function to add a doctor to the system
    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
    }

    // Function to add a patient to the system
    void addPatient(const Patient& patient) {
        patients.push_back(patient);
    }

    // Function to add a new patient with data input handling
    void addNewPatient() {
        if (DataInput::askForData()) {
            string name;
            cout << "Enter patient's name: ";
            cin >> name;
            Patient newPatient(name);
            DataInput::inputData(newPatient);
            addPatient(newPatient);
        }
    }

    // Function to display all doctors and their appointments
    void displayDoctorsAndAppointments() const {
        for (const auto& doctor : doctors) {
            doctor.displayAppointments();
        }
    }

    // Function to display all patients
    void displayPatients() const {
        cout << "Patients in the system:" << endl;
        for (const auto& patient : patients) {
            cout << "Name: " << patient.getName() << endl;
            cout << "Medical History:" << endl;
            for (const auto& record : patient.getMedicalHistory()) {
                cout << "- " << record << endl;
            }
            cout << "---------------------" << endl;
        }
    }
};

// Implementation of display() function for Appointment class
void Appointment::display() const {
    cout << "Doctor: " << doctor->getName() << endl;
    cout << "Patient: " << patient->getName() << endl;
    cout << "Date: ";
    date.display();
    cout << endl;
    cout << "Status: ";
    switch (status) {
        case AppointmentStatus::SCHEDULED:
            cout << "Scheduled";
            break;
        case AppointmentStatus::CANCELLED:
            cout << "Cancelled";
            break;
        case AppointmentStatus::COMPLETED:
            cout << "Completed";
            break;
    }
    cout << endl;
}

// Implementation of displayAppointments() function for Doctor class
void Doctor::displayAppointments() const {
    cout << "Appointments for Dr. " << name << ":" << endl;
    for (const auto& appointment : appointmentList) {
        appointment->display();
    }
}

int main() {
    // Initialize Hospital Management System
    HospitalManagementSystem hospitalSystem;

    // Create Doctors
    Doctor doctor1("John Doe", "Cardiologist");
    Doctor doctor2("Jane Smith", "Pediatrician");

    // Add Doctors to the System
    hospitalSystem.addDoctor(doctor1);
    hospitalSystem.addDoctor(doctor2);

    // Add Patients to the System
    hospitalSystem.addNewPatient();
    hospitalSystem.addNewPatient();

    // Display Doctors and Appointments
    hospitalSystem.displayDoctorsAndAppointments();

    // Display Patients
    hospitalSystem.displayPatients();

    return 0;
}