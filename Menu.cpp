#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

#define MAX_APP 100
#define appFILE "appointment.dat"
#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define SPECIALIZATION_LEN 50
#define GENDER_LEN 10
#define pfile "pdata.dat"
#define APfile "appdata.dat"
#define docfile "docdata.dat"
#define ACHfile "cityhospital.dat"

#define MAX_USERS 100
#define PATIENT_FILE "patient_M.dat"
#define USRNM_LEN 50
#define PSWD_LEN 20
#define NAME_LEN 50
#define GEN_LEN 6

#define CITY "fileCity.dat"
#define HOSPITAL "fileHospital.dat"
#define MAX_HOSPITAL 100
#define MAX_CITY 50
#define NAME_LENGTH 20
#define ADDRESS 50

typedef struct{
	int appointmentID;
	int patientID;
	int doctorID;
	char date[10];
	int cancel;
}Appointment;

typedef struct{
    char username[USRNM_LEN];
    char password[PSWD_LEN];
    char name[NAME_LEN];
    int age;
    char phoneno[15];
    char gender[GEN_LEN];
    int patientID;
    int delete_p;
}patient;

typedef struct{
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char name[NAME_LEN];
    char specialization[SPECIALIZATION_LEN];
    int docID;
    int hospitalID;
} Doctor;

typedef struct{
	int hospitalID;
	char hospitalName[NAME_LENGTH];
	char hospitalAddress[ADDRESS];
	int cityID;
}Hospital;

typedef struct{
	char cityName[NAME_LENGTH];
	int cityID;
}City;


int patientCount = 0;
int doctorCount = 0;
int cityCount = 0;
int hospitalCount = 0;
int appointmentCount = 0;

int presentDoctorID = -1;
int presentPatinetID = -1;

char newUsername[50];
char newPassword[20] = {'0'};


patient patients[MAX_USERS];
Doctor doctors[MAX_USERS];
Appointment appointments[MAX_APP];
Hospital hospitals[MAX_HOSPITAL];
City cities[MAX_CITY];


void patient_menu(char ch);
void patient_options();
void patient_load();
void patient_register();
void patient_details();
void patient_save();
int patient_login(int *ID);
void patient_edit(int id);
void patient_doctor_display();

void doctor_menu(char ch, int id);
void doctorOptions(int ID);
void doctor_register();
void doctor_display();
void doctor_save();
void doctors_load();
int doctor_login();
void doctor_edit(int ID);
void doctor_appointment_list(int ID);

void admin_menu(char ch);
void admin_edit_patient();
void city();
void city_load();
void city_add();
void city_display();
void city_list();
void city_edit();
void city_save();
void hospital();
void hospital_load();
void hospital_add();
void hospital_display();
void hospital_edit();
void hospital_save();

void setScreen();
void askForSecretPassword(char *k);

void appointment_book(int ID);
//hospital foundHospital(int ID);
void appointment_list();
void appointment_load();
void appointment_save();
void appointment_edit(int ID, int appID);
void appointmentCancel(int ID, int appID);

void viewAppointmentByPatientID(int ID);
void viewAppointmentByDoctorID(int ID);
int getDoctorsByCityID(int cityID);
Doctor getDoctorByDoctorID(int ID);
City getCityByCityID(int ID);
Hospital getHospitalByHospitalID(int ID);

int main() {

	setScreen();
	doctors_load();
	patient_load();
	city_load();
	hospital_load();
	appointment_load();
    int id, ID;
    char ch, mainch;
    do {
		system("cls");
		cout << "\n\t\t====================================================================\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
		cout << "\n\t\t=========================    MAIN MENU    ==========================\n\n\n";
		cout << "																			\n\n";
		cout << "\t|Press 1 to Select Patient Menu	|" << endl;
		cout << "\t|Press 2 to Select Doctor Menu	|" << endl;
		cout << "\t|Press 3 to Select Admin menu	|" << endl;
		cout << "\t|Press 4 to EXIT		|" << endl;
		cout << "\n\t\t\t Please Pick a Menu: ";

        mainch = getche();
        cout << endl;
        
        switch (mainch) {
            case '1':
            	patient_menu(ch);
                break;
            case '2':
            	doctor_menu(ch, id);
				break;
            case '3':
            	admin_menu(ch);
              	break;
            case '4':
            	cout <<"\tProgram exited";
            	exit(0);
            default:
                cout <<"\n\tInvalid choice!!"<< endl;
                cout <<"\tPress any key to Continue"; getch();
                break;
        }
    } while (mainch!='4');
    return 0;
}

void setScreen(){
	system("mode con COLS=700"); //This function with its parameters changes the console area/size.
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE); //This function maximizes the console to full screen.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 	//These two lines are used to change the text and screen color of console.
    SetConsoleTextAttribute(hConsole,(1 << 4) | 15);
}

void doctor_register(){
	Doctor newDoctor;
	City newCity;
	Hospital newHospital;
	int ID, status = 0;
	char response;
	
	hospital_display();
	cout << "\n\tHospital ID: "; cin >> newDoctor.hospitalID;
	cout << "\tUser name: "; cin >> newDoctor.username;
	cout << "\tPassword: "; cin >> newDoctor.password;
	cin.ignore();
	cout << "\tName: "; cin.getline(newDoctor.name,50);
	cout << "\tSpecialization: "; cin.getline(newDoctor.specialization,50);
	cout << endl;
	
	cout << "\n\tPress 'y' to Register\n\tPress any key to Cancel\n\t"; response = getche();
	if (response == 'y' || response == 'Y'){
		newDoctor.docID = doctorCount + 1;
		doctors[doctorCount] = newDoctor;
		doctorCount++;
		cout << "\n\tDoctor successfully saved!\n";
	}
}

void doctor_display(){
	if (doctorCount == 0){
		cout << "\nNo doctors info available.\n";
		return;
	}
	else{
		cout << "\n\n_____________________________________________________________________________________________________________________________\n";
		cout << setw(20) << "DoctorId" 
			<< setw(20) << "Username" 
			<< setw(20) << "Password" 
			<< setw(20) << "Name" 
			<< setw(30) << "Specialization"
			<< setw(15) << "Hospital ID" << endl;
		cout << "_____________________________________________________________________________________________________________________________\n";
		for(int i = 0; i < doctorCount; i++)
					cout << setw(20) << doctors[i].docID 
						<< setw(20) << doctors[i].username 
						<< setw(20) << doctors[i].password 
						<< setw(20) << doctors[i].name 
						<< setw(30) << doctors[i].specialization
						<< setw(15) << doctors[i].hospitalID << endl;
	}
}

void doctor_save(){
	fstream file;
	file.open(docfile, ios::out | ios::app | ios::binary);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&doctors[doctorCount - 1]), sizeof(Doctor));
		file.close();
	}
	else{
		cout << "\n\tERROR!\n";
	}
}

void doctors_load(){
	fstream file;
	file.open(docfile, ios::in | ios::binary);

	int size = 0;
	file.seekg(0, ios::end);
	size = (int)file.tellg();
	file.seekg(0, ios::beg);
		
	while(file.tellg() < size){
		file.read(reinterpret_cast<char*>(&doctors[doctorCount]), sizeof(Doctor));
		doctorCount++;
	}
	file.close();
}

int doctor_login(){
	if (doctorCount == 0){
        return -1;
    }
	char usernameLogin[USERNAME_LEN];
	char passwordLogin[PASSWORD_LEN] = {'1'};
	for (int i = 0; i < 50; i++)
		passwordLogin[i] = '\0';
	cout << "\n\tEnter Username: "; cin >> usernameLogin;
	askForSecretPassword(passwordLogin);
	for(int i = 0; i < doctorCount; i++){
	if(strcmp(usernameLogin, doctors[i].username) == 0 && strcmp(passwordLogin, doctors[i].password) == 0){
			presentDoctorID = doctors[i].docID;
			cout << "\n\tSuccessfully Logged in!";
			return doctors[i].docID;	
		}
	}
	return -2;
}

void doctor_menu(char ch, int id){
    do {
        system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Doctor MENU      ____________________\n\n\n";
		cout << "\t|Press 1 to LOGIN as a Doctor		|" << endl;
		cout << "\t|Press 2 to Register as Doctor		|" << endl;
		cout << "\t|Press 3 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";

        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':
                id = doctor_login();
                if (id > 0)
                    doctorOptions(id);
                else if (id = -1){
                	cout << "\n\tNo registered doctors found!\n";
                	getchar();
				}
                else {
                    cout <<"\n\tLogin failed!\n";
                    cout <<"\tPress any key to Continue"; getch();
                }
                break;
            case '2':
            	doctor_register();
            	doctor_save();
                break;
            case '3':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
                cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '3');
}

void doctorOptions(int ID){
	char ch;
    do {
    system("cls");
	cout << "\n\t\t____________________________________________________________________\n\n\n";
	cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
    cout <<" \n\t\t               " << doctors[ID - 1].username << " [" << ID << "] successfully Logged In:\n\n";
	cout << "\n\t\t_________________________      Doctor Options      ___________________\n\n\n";
	cout << "\t|Press 1 to View Appointments		|" << endl;
	cout << "\t|Press 2 to Edit personal Information	|" << endl;
	cout << "\t|Press 3 to View hospitals		|" << endl;
	cout << "\t|Press 4 to View personal Information	|" << endl;
	cout << "\t|Press 5 to Logout			|" << endl;
	cout << "\n\t\t\t Please enter your choice: ";

    ch = getche();
	cout << endl;
    switch (ch) {
        case '1': 
        	viewAppointmentByDoctorID(ID);
            break;
        case '2':
        	doctor_edit(ID);
        	break;
        case '3':
            hospital_display();
            getchar();
            break;
        case '4':
        	cout << "\n\n\t______________________________________________________________________________________________________________________________________________________\n";
			cout << setw(20) << "DoctorId" 
				<< setw(20) << "Username" 
				<< setw(20) << "Password" 
				<< setw(20) << "Name" 
				<< setw(30) << "Specialization"
				<< setw(15) << "Hospital ID"
				<< setw(25) << "Hospital Name" << endl;
			cout << "\t______________________________________________________________________________________________________________________________________________________\n";
			cout << setw(20) << doctors[ID-1].docID
				<< setw(20) << doctors[ID-1].username 
				<< setw(20) << doctors[ID-1].password 
				<< setw(20) << doctors[ID-1].name 
				<< setw(30) << doctors[ID-1].specialization
				<< setw(15) << doctors[ID-1].hospitalID
				<< setw(25) << hospitals[doctors[ID-1].hospitalID - 1].hospitalName << endl;
			getchar();
            break;
        case '5':
        	cout <<"\n\tLogged out\n";
            break;
        default:
            cout <<"\n\tInvalid choice!!\n";
            cout <<"\tPress any key to Continue"; getch();
    	}
	} while (ch != '5');
}

void getDoctors(){
	
	int doctorID;
	Doctor newDoctor;
	char response;
	
	if(doctorCount == 0){
		cout << "\n\tNo patients in the list to edit!\n";
		getchar();
		return;
	}
	
	cout << "\nEnter doctor's id to edit: "; cin >> doctorID;
	for (int i = 0; i < doctorCount; i++) {
		if (doctors[i].docID == doctorID) {
            cout << "patient found: "<< doctorID <<endl ;
			cout << "\n\n_____________________________________________________________________________________________________________________________\n";
			cout << setw(20) << "DoctorId" 
				<< setw(20) << "Username" 
				<< setw(20) << "Password" 
				<< setw(20) << "Name" 
				<< setw(30) << "Specialization"
				<< setw(2) << "Hospital ID" << endl;
			cout << "_____________________________________________________________________________________________________________________________\n";
			cout << setw(20) << doctors[i].docID 
				<< setw(20) << doctors[i].username 
				<< setw(20) << doctors[i].password 
				<< setw(20) << doctors[i].name 
				<< setw(30) << doctors[i].specialization
				<< setw(2) << doctors[i].hospitalID << endl;
			
			cout << "\n\tNew Record:\n";
			cout << "\tUsername: "; cin >> newDoctor.username;
			cout << "\tPassword: "; cin >> newDoctor.password;
			cout << "\tName: "; cin >> newDoctor.name;
			cout << "\tSpecialization: "; cin >> newDoctor.specialization;
			cout << endl;
			hospital_display();
			cout << endl;
			cout << "\tHospital ID: "; cin >> newDoctor.hospitalID;
			
			cout << "\n\tAre you sure to update the patient (y/n)?: "; cin >> response;
			if(response == 'y' or response == 'Y')
				doctors[i] = newDoctor;
				
			fstream file;
			file.open(docfile, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(Doctor)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&doctors[i]), sizeof(Doctor));
				file.close();
			}
			else
				cout << "\n\tERROR\n";
				
			break;
			return;
        }
    }
    cout << "Patient against given id not found!\n";
    getchar();
	
}

void doctor_edit(int ID){
	Doctor newDoctor;
	char response;
	int id = ID - 1;
	if (doctorCount == 0){
        cout << "\tNo registered doctors found!\n";
        getchar();
        return;
    }

	cout << "\n\n\t_____________________________________________________________________________________________________________________________\n";
	cout << setw(20) << "DoctorId" 
		<< setw(20) << "Username" 
		<< setw(20) << "Password" 
		<< setw(20) << "Name" 
		<< setw(30) << "Specialization"
		<< setw(15) << "Hospital ID" << endl;
	cout << "\t_____________________________________________________________________________________________________________________________\n";
	cout << setw(20) << doctors[id].docID
		<< setw(20) << doctors[id].username 
		<< setw(20) << doctors[id].password 
		<< setw(20) << doctors[id].name 
		<< setw(30) << doctors[id].specialization
		<< setw(15) << doctors[id].hospitalID << endl;
		
    cout << "\n\n\tNew information:\n";
    newDoctor.docID = ID;
    cout << "\n\tUser name: "; cin >> newDoctor.username;
	cout << "\tPassword: "; cin >> newDoctor.password;
	cin.ignore();
	cout << "\tName: "; cin.getline(newDoctor.name,50);
	cout << "\tSpecialization: "; cin.getline(newDoctor.specialization,50);
	cout << "\tHospital ID: "; cin >> newDoctor.hospitalID;
	
	cout << "\n\tPress 'y' to save information\n\tPress any key to Cancel\n\t"; response = getche();
	if(response == 'y' || response == 'Y'){
	
		doctors[id] = newDoctor;
		fstream file;
		file.open(docfile, ios::out | ios::binary);
		
		if(file.is_open())
		{
			int fp = sizeof(Doctor)*id;
			file.seekg(fp);
			file.write(reinterpret_cast<char*>(&doctors[id]), sizeof(Doctor));
			cout << "\n\tInformation changed!\n";
			file.close();
		}
		else
			cout << "\n\tERROR\n";
		getchar();
	}
}


void patient_menu(char ch){
	do {
		int id;
		system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Patient MENU      ___________________\n\n\n";
		cout << "\t|Press 1 to LOGIN as a Patient		|" << endl;
		cout << "\t|Press 2 to Register as Patient		|" << endl;
		cout << "\t|Press 3 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";
        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':
            	patient_options();
                break;
            case '2': // register Pateient
            	patient_register();
            	patient_save();
				cout << "\tPress any key to Continue"; getch();
                break;
            case '3':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
                cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '3');
}

void patient_register(){
	
	if (patientCount >= MAX_USERS) {
        cout << "\tWe can't register more patients. Sorry!\n";
        return;
    }
    
    patient newPatient;
    
    cout << "\n\n\tEnter patient's username: "; cin >> newPatient.username;
	cout << "\tEnter patient's password: "; cin >> newPatient.password;
	cin.ignore();
	cout << "\tEnter patient's name: "; cin.getline(newPatient.name,50);
//	cout << "\tEnter patient's name: "; cin >> newPatient.name;
	cout << "\tEnter patient's age: "; cin >> newPatient.age;
	cout << "\tEnter patient's phoneNo: "; cin >> newPatient.phoneno;
	cout << "\tEnter patient's gender (M = Male/ F = Female/O = Other): "; cin >> newPatient.gender;
    newPatient.patientID = patientCount + 1;
    newPatient.delete_p = 0;
    
    patients[patientCount++] = newPatient;
    cout << "\tPatient registered successfully! Patient ID: " << newPatient.patientID << "\n";
}

void patient_details() {
    if (patientCount == 0){
        cout << "\tNo registered patients found!\n";
        getchar();
    }
    else {
    	cout << "\n\n_____________________________________________________________________________________________________________________________\n";
    	cout <<setw(20) <<"Patient ID" <<setw(20) <<"Username" <<setw(20) << "Password" <<setw(25) <<"Name" <<setw(20) << "Age" <<setw(20) << "Gender\n" << endl;
    	cout << "_____________________________________________________________________________________________________________________________\n";
        for (int i = 0; i < patientCount; i++) {
            cout <<setw(20) << patients[i].patientID
				<<setw(20)	<< patients[i].username 
				<<setw(20)	<< patients[i].password
				<<setw(25)	<< patients[i].name 
				<<setw(20)	<< patients[i].age
				<<setw(20)	<< patients[i].gender	<< endl;
        }
        getchar();
    }
}

void patient_save() {

	fstream file;
	file.open(PATIENT_FILE, ios::out | ios::binary | ios::app );
	
	if(file.is_open())
	{
		file.write(reinterpret_cast<char*>(&patients[patientCount - 1]), sizeof(patient));
		file.close();
	}
	else
		cout << "\n\tERROR\n";

}

void patient_load(){

	fstream file;
	file.open(PATIENT_FILE, ios::in | ios::binary);
	if(file.is_open())
	{
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&patients[patientCount]), sizeof(patient));
			patientCount++;
		}
		file.close();
	}
	else
		cout << "\n\tERROR\n";	
}

int patient_login(int *ID){
	
	if (patientCount == 0){
        cout << "\tNo registered patients found!\n";
        getchar();
        return 1;
    }
	for (int i = 0; i < 20; i++)
		newPassword[i] = '\0';
	cout << "\n\tUsername: "; cin >> newUsername;
	askForSecretPassword(newPassword);
	
	for(int i = 0; i < patientCount; i++){
		if (strcmp(newUsername, patients[i].username) == 0 && strcmp(newPassword, patients[i].password) == 0){
			*ID = patients[i].patientID;
			return 0;
		}
	}
	
	cout << "\n\tNot logged in! Invalid username or password.\n";
	getchar();getchar();
	return 1;
}

void askForSecretPassword(char *k){
	char ch;
	int i;
	cout << "\tPassword: ";
	ch = _getch();
	while(i != PSWD_LEN){
		if (ch == 13)
			break;
	  	*(k+i) = ch;
	  	cout << '*';
	  	ch = _getch();
	  	i++;
	}
}

void admin_edit_patient() {
    
	int patient_id;
	patient new_patient;
	char response;
	
	if(patientCount == 0){
		cout << "\n\tNo patients in the list to edit!\n";
		getchar();
		return;
	}
	
	cout << "\n\tEnter patient's id to edit: "; cin >> patient_id;
	for (int i = 0; i < patientCount; i++) {
		if (patients[i].patientID == patient_id ) {
            cout << "\tPatient found: "<< patient_id <<endl ;
		    cout <<setw(20) <<"Patient ID" <<setw(20) <<"Username" <<setw(20) << "Password" <<setw(20) <<"Name" <<setw(20) << "Age" <<setw(20) << "Gender\n" << endl;
        	cout <<setw(20) << patients[i].patientID
				<<setw(20)	<< patients[i].username 
				<<setw(20)	<< patients[i].password
				<<setw(20)	<< patients[i].name 
				<<setw(20)	<< patients[i].age
				<<setw(20)	<< patients[i].gender	<< endl;
					
		    new_patient.patientID =  patients[i].patientID;
		    cout << "\n\n\tEnter patient's username: "; cin >> new_patient.username;
			cout << "\tEnter patient's password: "; cin >> new_patient.password;
			cout << "\tEnter patient's name: "; cin >> new_patient.name;
			cout << "\tEnter patient's age: "; cin >> new_patient.age;
			cout << "\tEnter patient's phoneNo: "; cin >> new_patient.phoneno;
			cout << "\tEnter patient's gender (male/female/other): "; cin >> new_patient.gender;
			
			cout << "\n\tAre you sure to update the patient (y/n)?: "; cin >> response;
			if(response == 'y' or response == 'Y')
				patients[i] = new_patient;
				
			fstream file;
			file.open(PATIENT_FILE, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(patient)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&patients[i]), sizeof(patient));
				file.close();
			}
			else
				cout << "\n\tERROR\n";
				
			break;
			return;
        }
    }
    cout << "\tPatient against given id not found!\n";
    getchar();
}

void patient_edit(int id){
	if (patientCount == 0){
        cout << "\tNo registered doctors found!\n";
        getchar();
        return;
    }
	for(int i = 0; i < patientCount; i++){
		if(id == patients[i].patientID){
			cout << "\n\tPrevious patient ID: " << patients[i].patientID;
			cout << "\n\tPrevious patinet Username: " << patients[i].username;
			cout << "\n\tPrevious patient password: " << patients[i].password;
			cout << "\n\tPrevious patinet Name: " << patients[i].name;
			cout << "\n\tPrevious patient phoneNo: " << patients[i].phoneno;
			cout << "\n\tPrevious patinet age: " << patients[i].age;
			cout << "\n\tPrevious patinet Gender: " << patients[i].gender;
			
			patient newPatient;
		    
		    newPatient.patientID = patients[i].patientID;
		    cout << "\n\n\tEnter new patient's username: "; cin >> newPatient.username;
			cout << "\tEnter new patient's password: "; cin >> newPatient.password;
			cin.ignore();
			cout << "\tEnter patient's name: "; cin.getline(newPatient.name,50);
			cout << "\tEnter new patient's age: "; cin >> newPatient.age;
			cout << "\tEnter new patient's phoneNo: "; cin >> newPatient.phoneno;
			cout << "\tEnter new patient's gender (M = Male/ F = Female/O = Other): "; cin >> newPatient.gender;
			patients[i] = newPatient;
			
			fstream file;
			file.open(PATIENT_FILE, ios::out | ios::binary);
			
			if(file.is_open())
			{
				int fp = sizeof(patient)*i;
				file.seekg(fp);
				file.write(reinterpret_cast<char*>(&patients[i]), sizeof(patient));
				file.close();
			}
			else
				cout << "\tERROR\n";
			
			cout << "\n\tInformation changed!\n";
			getchar();
			break;
		}
	}
}

void patient_options(){
	char ch, choice;
	int ID, appID = 0;
	int status = patient_login(&ID);
	if (status == 0){
		cout << "\n\tSuccessfully Logged in!\n"; getchar();
		do {
			system("cls");
			cout << "\n\t\t____________________________________________________________________\n\n\n";
			cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
            cout <<" \n\t\t               "<< newUsername <<" ["<< ID <<"] successfully Logged In:\n\n";
			cout << "\n\t\t_________________________      Patient Options      ___________________\n\n\n";
    		cout << "\t|Press 1 to Book Appointment		|" << endl;
			cout << "\t|Press 2 to Cancel appointment		|" << endl;
			cout << "\t|Press 3 to Edit Personal Information	|" << endl;
			cout << "\t|Press 4 to Edit Appointment Information|" << endl;
			cout << "\t|Press 5 to View Personal Information	|" << endl;
			cout << "\t|Press 6 to View Appointment Information|" << endl;
			cout << "\t|Press 7 to View Doctors Information	|" << endl;
			cout << "\t|Press 8 to Logout			|" << endl;
			cout << "\n\t\t\t Please enter your choice: ";
            ch = getche();
            cout << endl;
            switch (ch) {
                case '1':
					appointment_book(ID);
                    break;
                case '2':
                	cout << "\n\tEnter appointment ID to cancel: "; cin >> appID;
					appointmentCancel(ID, appID);
                    break;
                case '3':
                    patient_edit(ID);
                    break;
                case '4':
                	cout << "\n\tEnter appointment ID to edit: "; cin >> appID;
					appointment_edit(ID, appID);
                    break;
                case '5':
                	cout << "\n\tPatient ID: " << patients[ID - 1].patientID;
					cout << "\n\tPatinet Username: " << patients[ID - 1].username;
					cout << "\n\tPatient password: " << patients[ID - 1].password;
					cout << "\n\tPatinet Name: " << patients[ID - 1].name;
					cout << "\n\tPatient phoneNo: " << patients[ID - 1].phoneno;
					cout << "\n\tPatinet age: " << patients[ID - 1].age;
					cout << "\n\tPatinet Gender: " << patients[ID - 1].gender;
                    break;
                case '6':
					viewAppointmentByPatientID(ID);
					getchar();
                    break;
                    
                case '7':
                   	patient_doctor_display();
					getchar();
                    break;
            
                case '8':
                    cout << "\n\tLogged out\n";
                    break;
                default:
                    cout << "\n\tInvalid choice!!\n";
                    cout << "\n\tPress any key to Continue"; getch();
            }
            cout << "\n\tPress any key to Continue"; getch();
	    } while (ch != '8');
	}
	else{
        cout <<"\n\tLogin failed!\n";
	}
}

void patient_doctor_display(){
	if (doctorCount == 0){
		cout << "\nNo doctors info available.\n";
		return;
	}
	else{
		cout << "\n\n_____________________________________________________________________________________________________________________________\n";
		cout << setw(20) << "DoctorId"
			<< setw(20) << "Name" 
			<< setw(30) << "Specialization"
			<< setw(15) << "Hospital ID" << endl;
		cout << "_____________________________________________________________________________________________________________________________\n";
		for(int i = 0; i < doctorCount; i++)
					cout << setw(20) << doctors[i].docID
						<< setw(20) << doctors[i].name 
						<< setw(30) << doctors[i].specialization
						<< setw(15) << doctors[i].hospitalID << endl;
	}
}

void admin_menu(char ch){
    cout <<"\n\tEntered as an admin\n";
    do {
    	string userAdmin;
    	string passwordAdmin;
    	system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
        cout << "\n\t\t_________________________      Admin MENU      ____________________\n\n\n";
		cout << "\t|Press 1 to LOGIN as an Admin		|" << endl;
		cout << "\t|Press 2 Back to Main Menu		|" << endl;
		cout << "\n\t\t\t Please enter your choice: ";
        ch = getche();
        cout << endl;
        switch (ch) {
            case '1':
            	system("cls");
				cout << "\n\t\t____________________________________________________________________\n\n\n";
				cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
		        cout << "\n\t\t_________________________      Admin MENU      ____________________\n\n\n";
		        cout << "\tEnter Username: "; cin >> userAdmin;
		        cout << "\tEnter Password: "; cin >> passwordAdmin;
		        
                if (userAdmin == "ADMIN" && passwordAdmin == "admin") {
                    do {
                    	system("cls");
                    	cout << "\n\t\t____________________________________________________________________\n\n\n";
						cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
	                    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
						cout << "\n\t\t_________________________      ADMIN OPTIONS      ___________________\n\n\n";
	            		cout << "\t|Press 1 to Patient Management		|" << endl;
	            		cout << "\t|Press 2 to Doctor Management		|" << endl;
	            		cout << "\t|Press 3 to Appointment Management	|" << endl;
						cout << "\t|Press 4 to City Management		|" << endl;
						cout << "\t|Press 5 to Hospital Management		|" << endl;
						cout << "\t|Press 6 to Logout			|" << endl;																	
						cout << "\n\t\t\t Please enter your choice: ";

                        ch = getche();
        				cout << endl;
        				int status = 0;
                        switch (ch) {
                            case '1':
                            	do{
	                            	system("cls");
			                    	cout << "\n\t\t____________________________________________________________________\n\n\n";
									cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
				                    cout <<	"\n\t\t               Successfully Logged In as ADMIN\n\n";
									cout << "\n\t\t_____________  ADMIN OPTIONS -> Patient Management   _______________\n\n\n";
									cout << "\n\t|Press 1 for register patient 			|"
										<< "\n\t|Press 2 for listing all patients information	|"
										<< "\n\t|Press 3 for specific patinet information	|"
										<< "\n\t|Press 4 for editing patient record		|"
										<< "\n\t|Press 5 to go back to ADMIN OPTIONS		|"
										<< "\n\n\tEnter choice no: ";
									ch = getche();
									switch (ch){
										case '1':
											patient_register();
											patient_save();
											patient_details();
											break;
										case '2':
											patient_details();
											break;
										case '3':
											cout << "\n\tSpecific patinet information\n";
											int newID;
											cout << "\tEnter patient ID: "; cin >> newID;
											for(int i = 0; i < patientCount; i++){
												if(newID == patients[i].patientID){
													cout << "\n\tPatient ID: " << patients[i].patientID;
													cout << "\n\tPatinet Username: " << patients[i].username;
													cout << "\n\tPatient password: " << patients[i].password;
													cout << "\n\tPatinet Name: " << patients[i].name;
													cout << "\n\tPatient phoneNo: " << patients[i].phoneno;
													cout << "\n\tPatinet Gender: " << patients[i].gender;		
													break;
												}
											}
											break;
										case '4':
											cout << "\n\tEditing doctors information\n";
											admin_edit_patient();
											break;
										case '5':
											status = 1;
											break;
										default:
											cout << "\nInvalid option!\n";
									}
								}while (status == 0);
                                break;
                            case '2':
                            	do{
	                            	system("cls");
			                    	cout << "\n\t\t____________________________________________________________________\n\n\n";
									cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
				                    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
									cout << "\n\t\t_____________  ADMIN OPTIONS -> Doctor Management   ________________\n\n\n";
									cout << "\n\t|Press 1 for register doctor			|"
										<< "\n\t|Press 2 for listing all doctors information	|"
										<< "\n\t|Press 3 for specific doctor information	|"
										<< "\n\t|Press 4 for editing doctor record		|"
										<< "\n\t|Press 5 to go back to ADMIN OPTIONS		|"
										<< "\n\n\tEnter choice no: ";
									ch = getche();
									switch (ch){
										case '1':
											doctor_register();
											doctor_save();
											break;
										case '2':
											doctor_display();
											getchar();
											break;
										case '3':
											cout << "\n\tSpecific doctor information\n";
											int newID;
											cout << "\tEnter doctor ID: "; cin >> newID;
											for(int i = 0; i < doctorCount; i++){
												if(newID == doctors[i].docID){
													cout << "\n\tDoctor ID: " << doctors[i].docID;
													cout << "\n\tDoctor Username: " << doctors[i].username;
													cout << "\n\tDoctor password: " << doctors[i].password;
													cout << "\n\tDoctor Name: " << doctors[i].name;
													cout << "\n\tDoctor Specialization: " << doctors[i].specialization;		
													break;
												}
											}
											break;
										case '4':
											cout << "\n\tEdit doctor information\n";
											getDoctors();
											break;
										case '5':
											status = 1;
											break;
										default:
											cout << "\n\tInvalid option!\n";
									}
								}while (status == 0);
                                break;
                            case '3':
                            	do{							
	                            	system("cls");
			                    	cout << "\n\t\t____________________________________________________________________\n\n\n";
									cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
				                    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
									cout << "\n\t\t_____________  ADMIN OPTIONS -> Appointment Management   ________________\n\n\n";
									cout << "\n\t|Press 1 to list patient appointments		|"
										<< "\n\t|Press 2 for list doctors appointments		|"
										<< "\n\t|Press 3 for editing patients appointment	|"
										<< "\n\t|Press 4 for editing doctor appointment		|"
										<< "\n\t|Press 5 to go back to ADMIN OPTIONS		|"
										<< "\n\n\tEnter choice no: ";
									ch = getche();
									switch (ch){
										case '1':
											appointment_list();
											break;
										case '2':
											cout << "\n\tlist doctors appointments\n";
											break;
										case '3':
											cout << "\n\tediting patients appointment\n";
											break;
										case '4':
											cout << "\n\tediting doctor appointment\n";
											break;
										case '5':
											status = 1;
											break;
										default:
											cout << "\n\tInvalid option!\n";
									}
								}while (status == 0);
                                break;
                            case '4':
                            	city();
                                break;
			                case '5':
                            	hospital();
                                break;                      
                            case '6':
                                cout <<"\n\tLogged out\n";
                                cout <<"\tPress any key to Continue"; getch();
                                break;
                            default:
                                cout <<"\n\tInvalid choice!!\n";
                                cout <<"\tPress any key to Continue"; getch();
                        }
                    } while (ch != '6');
                } else {
                    cout <<"\n\tLogin Failed!\n";
                    cout <<"\n\tPress any key to continue.";
                    getchar();getchar();
                }
                break;
            case '2':
            	system("cls");
                break;
            default:
                cout <<"\n\tInvalid choice\n";
            	cout <<"\tPress any key to Continue"; getch();
        }
    } while (ch != '2');
}

//City Hospital ------------

void city(){
	char choice;
	int num = 0;

	do{
		system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
	    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
		cout << "\n\t\t_____________________  ADMIN OPTIONS -> City   _____________________\n\n\n";
		cout << "\n\t|Press 1 to enter city			|"
			 << "\n\t|Press 2 to display city		|"
			 << "\n\t|Press 3 to edit city			|"
			 << "\n\t|Press 4 to go back to ADMIN OPTION	|"
			 << "\n\n\tEnter choice: ";
		choice = getche();
			 
		switch(choice){
			case '1':
				city_add();
				city_save();
				getchar();
				break;
			case '2':
				city_display();			
				getchar();
				break;
			case '3':
				city_edit();
				getchar();
				break;
			case '4':
				num = 1;
				break;
			default:
				cout << "\n\tInvalid Input\n";
				getchar();
				getchar();
		}
	}while(num == 0);
}

void hospital(){
	char choice;
	int num = 0;

	do{
		system("cls");
		cout << "\n\t\t____________________________________________________________________\n\n\n";
		cout << "\n\t\t               WELCOME TO HOSPITAL APPOINTMENT SYSTEM               \n\n\n";
	    cout <<" \n\t\t               Successfully Logged In as ADMIN\n\n";
		cout << "\n\t\t____________________  ADMIN OPTIONS -> Hospital  ___________________\n\n\n";
		cout <<	"\n\t|Press 1 to enter hospital		|"
			 <<	"\n\t|Press 2 to display hospital		|"
			 <<	"\n\t|Press 3 to edit hospital		|"
			 << "\n\t|Press 4 to go back to ADMIN OPTION	|"
			 << "\n\n\tEnter choice: ";
		choice = getche();
			 
		switch(choice){
			case '1':
				hospital_add();
				hospital_save();
				getchar();
				break;
			case '2':
				hospital_display();
				getchar();
				break;
			case '3':
				hospital_edit();
				getchar();
				break;
			case '4':
				num = 1;
				break;
			default:
				cout << "\n\tInvalid Input\n";
				getchar();
				getchar();
		}
	}while(num == 0);
}

void city_load(){
	fstream file;
	file.open(CITY, ios::in | ios::binary);
	cityCount = 0;
	
	if(file.is_open()){
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&cities[cityCount]), sizeof(City));
			cityCount++;
		}
		file.close();
	}
	else
		cout << "\n\tERROR!\n";
}

void hospital_load(){
	fstream file;
	file.open(HOSPITAL, ios::in | ios::binary);
	
	hospitalCount = 0;
	if(file.is_open()){
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			file.read(reinterpret_cast<char*>(&hospitals[hospitalCount]), sizeof(Hospital));
			hospitalCount++;
		}
		file.close();
	}
	else
		cout << "\n\tERROR!\n";
}

void city_add(){
	City newCity;
	cout << "\tAdd city name: "; cin >> newCity.cityName;
	newCity.cityID = cityCount + 1;
	cities[cityCount++] = newCity;
	cout << "\n\tCity successfully saved! City ID: " << cityCount;
}

void hospital_add(){
	Hospital newHospital;
	int cityID;
	City temp;

	cout << "\n\tEnter City id: "; cin >> cityID;
	temp = getCityByCityID(cityID);
	if (temp.cityID > 0){
		cout <<"\t\t\t(" << temp.cityName<<")";
		newHospital.cityID = cityID;
	}
	else
	{
		cout << "\tInvalid City ID entered, check valid cities. anter try again. ";
		city_display();
		return;
	}
	
	cin.ignore();
	cout << "\n\tEnter hospital name: "; cin.getline(newHospital.hospitalName,20);
	cout << "\tEnter hospital address: "; cin.getline(newHospital.hospitalAddress,50);
	int status = 1;
	newHospital.hospitalID = hospitalCount + 1;
	hospitals[hospitalCount++] = newHospital;
	cout << "\n\tHospital successfully saved! Hospital ID: " << hospitalCount;
}

void hospital_display(){
	if (hospitalCount == 0){
        cout << "\tNo registered hospitals found!\n";
        getchar();
    }
    else {
    	cout << endl;
    	cout << "\t_______________________________________________________________________________________________________\n";
    	cout <<setw(20) <<"Hospital ID" <<setw(20) <<"Hospital Name" <<setw(45) << "Address" <<setw(20) <<"City Name" << endl;
    	cout << "\t_______________________________________________________________________________________________________\n";
        for (int i = 0; i < hospitalCount; i++) {
            cout <<setw(20) << hospitals[i].hospitalID
				<<setw(20)	<< hospitals[i].hospitalName 
				<<setw(45)	<< hospitals[i].hospitalAddress
				<<setw(12)	<< hospitals[i].cityID<< " - "<< cities[hospitals[i].cityID -1].cityName	<< endl;
        }
    	cout << "\t_______________________________________________________________________________________________________\n";
    }
}

void city_display(){
	if (cityCount == 0){
        cout << "\tNo cities found!\n";
        getchar();
    }
    else {
    	cout << endl;
    	cout <<setw(20) <<"City ID" <<setw(20) <<"City Name" << endl;
    	cout << "\t___________________________________________\n";
        for (int i = 0; i < cityCount; i++) {
            cout <<setw(20) << cities[i].cityID
				<<setw(20)	<< cities[i].cityName << endl;
        }
        cout << "\t___________________________________________\n";
    }
}

void city_edit(){
	
	if (cityCount == 0){
        cout << "\tNo registered cities found!\n";
        getchar();
        return;
    }
	
	int cityID;
	City temp;
	char response;

	cout << "\n\tEnter City id: "; cin >> cityID;
	temp = getCityByCityID(cityID);
	if (temp.cityID > 0){
		cout <<"\t\t\t(" << temp.cityName<<")";
	}
	else
	{
		cout << "\tInvalid City ID entered, check valid cities. anter try again. ";
		city_display();
		return;
	}
	
	cout << "\n\tNew City name: "; cin >> temp.cityName;
	
	cout << "\n\tPress 'y' to Save the changes\n\tPress any key to Cancel.\n\t"; response = getche();
		if(response == 'y' or response == 'Y'){
			cities[cityID - 1] = temp;

			fstream f;
			f.open(CITY, ios::out | ios::binary | ios::in );
				
			if(f.is_open())
			{
				f.seekg(0, ios::beg);

				f.seekg((cityID - 1)*sizeof(City),ios::cur);
				f.write(reinterpret_cast<char*>(&temp), sizeof(City));
				f.close();
			}
			else
				cout << "ERROR\n";				

				cout << "\n\tCity Updated!"; 
			}
}

void hospital_edit(){
	
	if (hospitalCount == 0){
        cout << "\tNo registered hospitals found!\n";
        getchar();
        return;
    }
	
	int cityID, hospitalID;
	City tempCity;
	Hospital tempHospital;
	char response;

	cout << "\n\tEnter Hospital ID: "; cin >> hospitalID;
	tempHospital = getHospitalByHospitalID(hospitalID);
	if (tempHospital.hospitalID > 0){
		cout <<"\t\t\t(" << tempHospital.hospitalName<<")";
	}
	else
	{
		cout << "\tInvalid Hospital ID entered, check valid hospitals. anter try again. ";
		return;
	}

	cin.ignore();
	cout << "\n\tNew hospital name: "; cin.getline(tempHospital.hospitalName,20);
	cout << "\n\tNew hospital address: "; cin.getline(tempHospital.hospitalAddress,50);

	cout << "\n\tEnter City ID: "; cin >> cityID;
	tempCity = getCityByCityID(cityID);
	if (tempCity.cityID > 0){
		cout <<"\t\t\t(" << tempCity.cityName<<")";
		tempHospital.cityID = tempCity.cityID;
	}
	else
	{
		cout << "\tInvalid City ID entered, check valid cities. anter try again. ";
		return;
	}
	
	cout << "\n\tPress 'y' to Save the changes\n\tPress any key to Cancel.\n"; response = getche();
	if(response == 'y' or response == 'Y'){
		hospitals[hospitalID - 1] = tempHospital;

		fstream f;
		f.open(appFILE, ios::out | ios::binary | ios::in );
		
		if(f.is_open())
		{
			f.seekg(0, ios::beg);

			f.seekg((hospitalID - 1)*sizeof(Hospital),ios::cur);
			f.write(reinterpret_cast<char*>(&tempHospital), sizeof(Hospital));
			f.close();
		}
		else
			cout << "ERROR\n";				

		cout << "\n\tHospital Updated!"; 
	}
	
	
//	fstream file;
//	file.open(HOSPITAL, ios::in | ios::out | ios::binary);
//	
//	if(file.is_open()){
//		for(int i = 0; i < hospitalCount; i++){
//			if(newID == hospitals[i].hospitalID){
//				cin.ignore();
//				cout << "\n\tNew hospital name: "; cin.getline(hospitals[i].hospitalName,20);
//				cout << "\n\tNew hospital address: "; cin.getline(hospitals[i].hospitalAddress,50);
//				cout << "\n\tNew City ID: "; cin >> hospitals[i].cityID;
//				int fp = sizeof(Hospital)*i;
//				file.seekg(fp);
//				
//				file.write(reinterpret_cast<char*>(&hospitals[i]), sizeof(Hospital));
//				file.close();
//				cout << "\n\tHospital data changed!\n";
//				break;
//			}
//		}
//	}
//	else
//		cout << "\n\tERROR!\n";
}

void city_save(){
	fstream file;
	file.open(CITY, ios::out | ios::binary | ios::app);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&cities[cityCount - 1]),sizeof(City));
		file.close();
	}
	else{
		cout << "\n\tERROR!\n";
	}
}

void hospital_save(){
	fstream file;
	file.open(HOSPITAL, ios::out | ios::binary | ios::app);
	
	if(file.is_open()){
		file.write(reinterpret_cast<char*>(&hospitals[hospitalCount - 1]),sizeof(Hospital));
		file.close();
	}
	else{
		cout << "\n\tERROR!\n";
	}
}

void city_list(){
	
	if (cityCount == 0){
        cout << "\tNo registered cities found!\n";
        getchar();
        return;
    }
	
	int j = 0;
	for(int i = 0; i < cityCount; i++){
		cout << setw(12) << "ID: " << cities[i].cityID << " | Name: " << setw(20) << cities[i].cityName;
		j++;
		if(j == 3){
			cout << endl;
			j = 0;
		}
		else
			cout << "   ||";
	}
}

void appointment_book(int ID){
	Appointment newAppointment;
	Doctor newDoctor;
	newAppointment.patientID = ID;
	newAppointment.cancel = 1;
	char response;
	cout << "\n\tBook Appointment\n\n";
	
	cout << "\n\tEnter doctor ID: "; cin >> newAppointment.doctorID;
	newDoctor = getDoctorByDoctorID(newAppointment.doctorID);
	if (newDoctor.docID > 0){
		cout <<"\t\t\t(" << newDoctor.name<<")";
	}
	else
	{
		cout << "\tInvalid Doctor ID entered, check valid doctors and try again. ";
		return;
	}
	
	cout << "\n\n\tEnter the date which you will attend appointment (dd-mm-yyyy): "; cin >> newAppointment.date;
	newAppointment.appointmentID = appointmentCount + 1;
	newAppointment.cancel = 1;
	
	cout << "\n\tAre you sure to book appointment (y/n)?: "; cin >> response;
	if(response == 'y' or response == 'Y'){
		appointments[appointmentCount++] = newAppointment;
		appointment_save();
		cout << "\n\tAppointment Booked! Appointment ID: " << appointmentCount; 
	}
}

void doctor_appointment_list(int ID){
	
	if (appointmentCount == 0){
        cout << "\tNo appointment of patients found!\n";
        getchar();
        return;
    }
	
	int j = 0;
	cout << "\n";
	for(int i = 0; i < doctorCount; i++){
		if(ID == doctors[i].hospitalID){
			cout << doctors[i].docID << "   " << doctors[i].name << "   " << doctors[i].specialization << endl;
		}
	}
	cout << "\n";
}

City getCityByCityID(int ID){
	City city;
	for(int i = 0; i < cityCount; i++){
		if(ID == cities[i].cityID){
			city = cities[i];	
		}
	}
	return city;
}

int getDoctorsByCityID(int cityID){
	int status = 0;
	
	for(int i = 0; i < doctorCount; i++){
		if(cityID == hospitals[doctors[i].hospitalID - 1].cityID)
			status++;
	}
	
	if(status == 0){
		cout << "\n\tSorry, no doctors available for this city!";
		return -1;
	}
	
	cout << "\n\n\tList of doctors of " << cities[cityID-1].cityName << ":\n";
	cout << "\t" << setw(10) << "Doctor ID"
		<< setw(20) << "Doctor Name"
		<< setw(20) << "Speciaization"
		<< setw(20) << "Hospital\n";
	cout << "\t____________________________________________________________________________________\n";
	for(int i = 0; i < doctorCount; i++){
		if(cityID == hospitals[doctors[i].hospitalID - 1].cityID){
			cout << "\t" << setw(10) << doctors[i].docID
				<< setw(20) << doctors[i].name
				<< setw(20) << doctors[i].specialization
				<< setw(20) << hospitals[doctors[i].hospitalID].hospitalName << endl;
				status++;
		}
	}
	cout << "\n\t____________________________________________________________________________________\n";
	return 0;
}

Doctor getDoctorByDoctorID(int ID){
	Doctor doctor;
	for(int i = 0; i < doctorCount; i++){
		if(ID == doctors[i].docID){
			doctor = doctors[i];
			break;
		}
	}
	return doctor;
}

Hospital getHospitalByHospitalID(int ID){
	Hospital hospital;
	for(int i = 0; i < hospitalCount; i++){
		if(ID == hospitals[i].hospitalID){
			hospital = hospitals[i];
			break;
		}
	}
	return hospital;
}

void appointment_list(){
	string status;
	if (appointmentCount == 0){
		cout << "\n\tNo appointment info available!\n";
		getchar();
		return;
	}
	cout << "\n\n";
	cout << setw(20)<< "AppointmentID" << setw(13) << "PatientID" << setw(25) << "Patinet name" << setw(25) << "Doctor" << setw(15) << "Date" << setw(20) << "City" << setw(20) << "Hospital" << setw(20) << "Status";
	cout << "\n\t____________________________________________________________________________________________________________________________________________________________";
	for(int i = 0; i < appointmentCount; i++){
		cout << "\n";
		status = (appointments[i].cancel == 0) ? "Cancelled" : "Not Cancelled";
		cout << setw(20) << appointments[i].appointmentID
			<< setw(13) << appointments[i].patientID
			<< setw(25) << patients[appointments[i].patientID - 1].name
			<< setw(25) << doctors[appointments[i].doctorID - 1].name
			<< setw(15) << appointments[i].date
			<< setw(20) << cities[hospitals[appointments[i].doctorID - 1].cityID - 1].cityName
			<< setw(20) << hospitals[appointments[i].doctorID - 1].hospitalName
			<< setw(20) << status ;
			
	}
	cout << "\n\t____________________________________________________________________________________________________________________________________________________________";
	getchar();getchar();
}

void appointment_save(){
	fstream file;
	file.open(appFILE, ios::out | ios::binary);
	if(file.is_open()){
		for(int i = 0; i < appointmentCount; i++){
			file.write(reinterpret_cast<char*>(&appointments[i]), sizeof(Appointment));
		}
		file.close();
	}
	else
		cout << "\nERROR!\n";
}

void appointment_load(){
	fstream file;
	file.open(appFILE, ios::in | ios::binary);
	
	if(file.is_open()){
		int size = 0;
		file.seekg(0, ios::end);
		size = (int)file.tellg();
		file.seekg(0, ios::beg);
		while(file.tellg() < size){
			cout << file.tellg() << " > " << size << " : " << sizeof(Appointment) << "\n";
			file.read(reinterpret_cast<char*>(&appointments[appointmentCount]), sizeof(Appointment));
			appointmentCount++;
		}
		file.close();
	}
	else
		cout << "\nERROR!\n";
}

void appointment_edit(int ID, int appID){
	bool found = 0;
	char response;
	cout << "\n\tEdit appointment information:\n";

	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].patientID && appID == appointments[i].appointmentID && appointments[i].cancel == 1){
		   	found = 1;
			cout << "\n\n";
			cout << setw(10)<< "Appt.ID" << setw(20) << "Patient" << setw(12) << "DoctorID" << setw(20) << "Doctor Name" << setw(15) << "Date" << setw(15) << "City" << setw(20) << "Hospital";
			cout << "\n__________________________________________________________________________________________________________________________\n";
			cout << setw(10) << appointments[i].appointmentID
				<< setw(20) << patients[ID - 1].name
				<< setw(12) << appointments[i].doctorID
				<< setw(20) << doctors[appointments[i].doctorID - 1].name
				<< setw(15) << appointments[i].date
				<< setw(15) << cities[hospitals[doctors[appointments[i].doctorID - 1].hospitalID - 1].cityID - 1].cityName
				<< setw(20) << hospitals[doctors[appointments[i].doctorID - 1].hospitalID - 1].hospitalName;
			cout << "\n__________________________________________________________________________________________________________________________";
			
			Appointment newAppointment;
			Doctor newDoctor;
			newAppointment.patientID = ID;
			newAppointment.appointmentID = appID;
			newAppointment.cancel = appointments[i].cancel;
			cout << endl;
			
			cout << "Enter doctor ID: "; cin >> newAppointment.doctorID;
			newDoctor = getDoctorByDoctorID(newAppointment.doctorID);
			if (newDoctor.docID > 0){
				cout <<"\t\t\t(" << newDoctor.name<<")";
			}
			else
			{
				cout << "\tInvalid Doctor ID entered, check valid doctors and try again. ";
				return;
			}
			
			cout << "\n\n\tEnter the date which you will attend appointment (dd-mm-yyyy): "; cin >> newAppointment.date;
			
			cout << "\n\tPress 'y' to Save the changes\n\tPress any key to Cancel.\n"; response = getche();
			if(response == 'y' or response == 'Y'){
				appointments[i] = newAppointment;

				fstream f;
				f.open(appFILE, ios::out | ios::binary | ios::in );
				
				if(f.is_open())
				{
					f.seekg(0, ios::beg);
	
					f.seekg(i*sizeof(Appointment),ios::cur);
					f.write(reinterpret_cast<char*>(&newAppointment), sizeof(Appointment));
					f.close();
				}
				else
					cout << "ERROR\n";				

				cout << "\n\tAppointment Updated!"; 
			}
					
			break;
		}
	}
	
	if (found != 1){
		cout << "Requested appointment against provided appt.ID not found.";
	}
	
}

void viewAppointmentByPatientID(int ID){
	int patientAppointmentCount = 0;
	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].patientID && appointments[i].cancel == 1){
			patientAppointmentCount++;
		}
	}
	
	if (patientAppointmentCount == 0){
		cout << "\n\tYour appointment information is not available.";
		return;
	}
	
	cout << "\n\tView appointment information:\n";
   	cout << "\n\n";
	cout << setw(10)<< "Appt.ID" << setw(20) << "Patient" << setw(12) << "DoctorID" << setw(20) << "Doctor Name" << setw(15) << "Date" << setw(15) << "City" << setw(20) << "Hospital";
	cout << "\n__________________________________________________________________________________________________________________________";

	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].patientID && appointments[i].cancel == 1){
			cout << "\n";
			cout << setw(10) << appointments[i].appointmentID
				<< setw(20) << patients[ID - 1].name
				<< setw(12) << appointments[i].doctorID
				<< setw(20) << doctors[appointments[i].doctorID - 1].name
				<< setw(15) << appointments[i].date
				<< setw(15) << cities[hospitals[doctors[appointments[i].doctorID - 1].hospitalID - 1].cityID - 1].cityName
				<< setw(20) << hospitals[doctors[appointments[i].doctorID - 1].hospitalID - 1].hospitalName;
		}
	}
	cout << "\n__________________________________________________________________________________________________________________________";
}

void appointmentCancel(int ID, int appID){
	char response;

	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].patientID && appID == appointments[i].appointmentID && appointments[i].cancel == 1){
		   	cout << "\n\tPress 'y' to Cancel appointment\n\tPress any key to exit\n\t"; cin >> response;
		   	if(response == 'y' || response == 'Y'){
		   		appointments[appID-1].cancel = 0;
		   		
		   		fstream f;
				f.open(appFILE, ios::out | ios::binary | ios::in );
				
				if(f.is_open())
				{
					f.seekg(0, ios::beg);
	
					f.seekg((appID-1)*sizeof(Appointment),ios::cur);
					f.write(reinterpret_cast<char*>(&appointments[appID-1]), sizeof(Appointment));
					f.close();
				}
				else
					cout << "ERROR\n";				

				cout << "\n\tAppointment Cancelled!";
				getchar();
			}
		   	return;
		}
	}
	cout << "\n\tWrong appointment ID provided!";
	getchar();
}

void viewAppointmentByDoctorID(int ID){
	int doctorAppointmentCount = 0;
	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].doctorID && appointments[i].cancel == 1){
			doctorAppointmentCount++;
		}
	}
	
	if (doctorAppointmentCount == 0){
		cout << "\n\tYour appointment information is not available.";
		return;
	}
	
	cout << "\n\tView appointment information:\n";
   	cout << "\n\n";
   	cout << "\n\t________________________________________________________________________________________________";
	cout << setw(15) << "Appt.ID" << setw(25) << "Patient" << setw(15) << "Date" << setw(20) << "Phone#" << setw(20) << "Gender";
	cout << "\n\t________________________________________________________________________________________________";

	for(int i = 0; i < appointmentCount; i++){
		if(ID == appointments[i].doctorID && appointments[i].cancel == 1 && patients[appointments[i].patientID - 1].delete_p == 0){
			cout << "\n";
			cout << setw(15) << appointments[i].appointmentID
				<< setw(25) << patients[appointments[i].patientID - 1].name
				<< setw(15) << appointments[i].date
				<< setw(20) << patients[appointments[i].patientID - 1].phoneno
				<< setw(20) << patients[appointments[i].patientID - 1].gender;
		}
	}
	cout << "\n\t________________________________________________________________________________________________";
	cin.ignore();
}
