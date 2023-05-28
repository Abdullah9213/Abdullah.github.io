
#include<iostream>
#include<string>
#include <windows.h> // for Sleep function
#include<fstream>
#include<sstream>
#include<cmath>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include"Header.h"
using namespace std;
void main_menu();
void Admin_Login();
void Admin_work();

void passenger_work(int i);
void passenger_login();
void passenger_signup();
void reset_passenger_password();
void input(string username, string password, string filename);
void input_signup(string username, string password, string filename);
bool validate_password(string p);
void Flight_schedule(int i);
void update_passenger_datails(int i);
string get_arrival(string x, int y, int z);
void update_flights_record_local()
{
	string cities[] = { "Lahore", "Peshawar", "Islamabad", "Karachi", "Quetta" };
	string directions[] = { "North", "South" };
	string option = "L";
	string filename[10];

	int index = 0;

	// Generate flight names
	for (int i = 0; i < 2; i++) {  // North/South
		for (int j = 0; j < 5; j++) {  // Cities

			filename[index] = "Flight_" + directions[i] + cities[j] + "_" + option+".txt";
			index++;

		}
	}
	
	//updating data
	for (int i = 0; i < 10; i++)
	{
		int num_flights = flight_num(filename[i]);

		ifstream i1_file(filename[i]);
		
		if (!i1_file) {
			cout << "Error opening the file." << endl;
			return;
		}
		else
		{
			string y1, y2, y3, y4, y5, y6;
			int x1, x2, x3, x4;
			bool z1;

			for (int j = 0; j < num_flights; j++)
			{
				i1_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;
				
				if (compare_times(y4, current_time_hours_min()) == true)
				{
					ofstream o2_file("In_Air.txt", ios::app);
					o2_file << y1 << ' ' << y2 << ' ' << y3 << ' ' << y4 << ' ' << y5 << ' ' << y6 << ' ' << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << ' ' << z1 << endl;
					o2_file.close();
					
				}
				else
				{
					ofstream o3_file("Temporary.txt", ios::app);

					o3_file << y1 << ' ' << y2 << ' ' << y3 << ' ' << y4 << ' ' << y5 << ' ' << y6 << ' ' << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << ' ' << z1 << endl;
					o3_file.close();
					

				}
				
				if (j == num_flights - 1)
				{
					
					ifstream i4_file("Temporary.txt");
					
					ofstream o6_file(filename[i]);
					
					int size_temp = flight_num("Temporary.txt");
					cout << "?";
					for (int k = 0; k < size_temp; k++)
					{
						i4_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;
						o6_file << y1 << ' ' << y2 << ' ' << y3 << ' ' << y4 << ' ' << y5 << ' ' << y6 << ' ' << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << ' ' << z1 << endl;


					}
					i4_file.close();
					o6_file.close();
					//cout << filename[i].c_str();
					remove(filename[i].c_str());
					bool Rename_Successful = rename("Temporary.txt", filename[i].c_str());

					if (Rename_Successful != 0) {
						cout << "Error In Renaming the Write File" << endl;
						return;
					}


				}
			}
			i1_file.close();
		}
		
	}

}

void update_flights_record_local_check()
{
	string filename = "In_Air.txt";
	int size = flight_num(filename)-1;
	
	fstream i1_file(filename);
	Flight* flights_Air = new Flight[size];
	string newstr;
	string f;
	string depart;
	if (!i1_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else
	{
		string y1, y2, y3, y4, y5, y6;
		int x1, x2, x3, x4;
		bool z1;
		i1_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;
		for (int i = 0; i < size; i++)
		{
			Airport Dep(y2);
			Airport Des(y3);
			Airplane Plane(y6, x1, x2, x1 + x2);
			bool status = flight_status(y4, x1, x2, z1);
			Flight x = Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1,status);
			
			if (compare_times(current_time_hours_min(), flights_Air[i].getArrivalTime()) == true)
			{
				string newstr1 = flights_Air[i].getDestinationCity();
				newstr = newstr1.substr(0, 4) + newstr.substr(6);
				newstr1 = "Flight_" + newstr + "_L.txt";
				f = addHoursToTime(flights_Air[i].getArrivalTime(), 2);
				f = addHoursToTime(flights_Air[i].getArrivalTime(), 2);
				depart = get_arrival(f,x3,x4);
				ofstream o1file(newstr1,ios::app);
				o1file << y1 << ' ' << y3 << ' ' << y2 << ' ' << y4 << ' ' << f << ' ' << depart << ' ' << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << ' ' << z1 << endl;



			}
			
			
		}
	}

}
void update_flights_record_seats()
{
	string cities[] = { "Lahore", "Peshawar", "Islamabad", "Karachi", "Quetta" };
	string directions[] = { "North", "South" };
	string options[] = { "I", "L" };
	string filename[20];

	int index = 0;

	// Generate flight names
	for (int i = 0; i < 2; i++) {  // North/South
		for (int j = 0; j < 5; j++) {  // Cities
			for (int k = 0; k < 2; k++) {  // I/L
				filename[index] = "Flight_" + directions[i] + cities[j] + "_" + options[k]+".txt";
				index++;
			}
		}
	}

	//updating data
	for (int i = 0; i < index; i++) {
		
		int num_flights = flight_num(filename[i]);
		ifstream i1_file(filename[i]);
		Flight* flights = new Flight[num_flights];
		//int f = 0;
		if (!i1_file) {
			cout << "Error opening the file." << endl;
			return ;
		}
		else
		{
			string y1, y2, y3, y4, y5, y6;
			int x1, x2, x3, x4;
			bool z1;

			for (int i = 0; i < num_flights-1; i++)
			{


				i1_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;
				//cout<< flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].getAvailableBusinessSeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;

				if (z1 == true)
				{
					x1 = 25;
					x2 = 5;
				}
				else { x1 = 50; x2 = 10; }
				Airport Dep(y2);
				Airport Des(y3);
				Airplane Plane(y6, x1, x2, x1 + x2);
				bool status = flight_status(y4, x1, x2, z1);
				Flight x = Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1,  status);//copy constructor used
				flights[i] = x;													// polymorphism
				
			}
			i1_file.close();
			ofstream o1file(filename[i]);
			//int num_flights = flight_num(filename)-1;
			if (!o1file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else
			{

				for (int i = 0; i < num_flights-1; i++)
				{

					o1file << flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].getAvailableBusinessSeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;

				}
				o1file.close();
		}


		
		}
		delete[] flights;
	}

}



void display_basic_details() 
{
	system("cls");
	cout << "\n\t\tBasic Details\n\nWelcome to NUCES Airline Flight System (NAFS)" << endl;
	cout << "NAFS is functional in five major cities of Pakistan: Islamabad, Lahore, Quetta, Peshawar, and Karachi." << endl;
	cout << "Each city has two airports located at the North and South." << endl;
	cout << "NAFS has 10 airplanes in each city whereas a maximum of 5 can land at a time in an airport." << endl;
	cout << "NAFS has established a network of flights in 25 countries around the globe." << endl;
	cout << "Due to COVID situation some countries have travel bans. NAFS greatly values its passengers and abides by the international travelling laws." << endl;
	cout << "50,000 passengers use NAFS annually." << endl;
	cout << "Ten Local flights and Five International flights take off from each airport daily depending on their schedule." << endl;
	cout << "Each plane of NAFS has a seating capacity of 50 passengers in economy class and 10 in business class." << endl;
	cout << "During COVID days, passengers are seated with a gap of one seat." << endl;
	cout << "To Go back,";
	system("pause");
	system("cls");
}


int main()
{

	string date;
	ifstream ifile("Date_check.txt");
	ifile >> date;
	ifile.close();
	
	if (compare_dates(getCurrentDate() , date)==true)
	{
		//cout<<
		update_flights_record_seats();
		date = getCurrentDate();
		ofstream ofile("Date_check.txt");
		ofile << date;
		ofile.close();
		
	}
	
	//update_flights_record_local();
	
	//update_flight_record_local_check();
	
	cout << "\n\t\tWELCOME TO NUCES-FAST AIRLINES" << endl;
	
	main_menu();
	cout << "Successfully Exited from Program...." << endl;
	return 0;
}

void main_menu()
{

	
	bool opt = true;
	do {
		system("cls");cout<< current_time_hours_min(); cout << "\n\tWELCOME TO NUCES-FAST AIRLINES\n" << endl;
		cout << "\n\t\tMain Menu\n\nPlease choose how you would like to continue: \n[1]As Admin\n[2]As Passenger\n[3]View Basic Detail about NAFS\n[4]See flight schedule\n[5]Exit\nEnter your choice: ";
		int opt1;
		cin >> opt1;
		if (opt1 == 1)
		{
			Admin_Login();


		}
		else if (opt1 == 2)
		{
			cout << "What do you want to do \n[1]Log IN \n[2]Sign UP\n[3]Go to main menu\n[4]Exit\nEnter your choice: ";
			int opt3;
			cin >> opt3;
			if (opt3 == 1)
			{
				passenger_login();
			}
			else if(opt3==2)
			{
				passenger_signup();
			}
			else if (opt3 == 3)
			{
				main_menu();
			}
		}
		else if (opt1 == 3)
		{
			display_basic_details();
			

		}
		
		else if (opt1 == 4)
		{
			Flight_schedule(-1);
		}
		else if(opt1 == 5)
		{
			exit(0);
		}
		else
		{
			cout << "Invalid entry. Kindly re_enter..." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
		}
	} while (opt == true);
}

void Admin_Login()
{
	system("cls");
	const int size_admin = 5;

	admin* Admin=new admin[size_admin];
	ifstream i_file(Admin[0].get_filename());
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else {
		string u, p;
		for (int i = 0; i < size_admin; i++)
		{
			
			i_file >> u >> p;


			Admin[i].set_username(u);
			Admin[i].set_password(p);
		}
		i_file.close();
	}
	
	bool opt2 = false;
	do {
		system("cls");
		string Admin_name;
		cout << "\n\t\tAdmin LOG IN\n\nUsername: ";
		cin.ignore();
		getline(cin, Admin_name);

		string Admin_password = "";
		char Admin_password_ch;
		int Length = 0;

		cout << "Password: ";
		do {
			Admin_password_ch = _getch();   // Get keystroke

			if (Admin_password_ch == 13) { // Enter key ascii

				break;
			}
			else if (Admin_password_ch == 8) { // Backspace key
				if (Length > 0) {         // Check if there are characters to remove
					Admin_password.pop_back();
					cout << "\b \b";     // Remove * from console
					Length--;
				}
			}
			else {                      // Other key
				Length++;
				Admin_password.push_back(Admin_password_ch);
				cout << "*";
			}
		} while (true);



		for (int i = 0; i < size_admin; i++)
		{
			if (Admin[i].get_username() == Admin_name && Admin[i].get_password() == Admin_password)
			{
				opt2 = true;
				Admin_work();
				break;
			}
		}
		system("CLS");
		if (opt2 == false)
		{

			cout << "Invalid username or password. Kindly select what do you want to do : \n[1]Re-enter username & password\n[2]Reset Password\n[3]Go to main menu\n[4]Exit\nKindly Enter your Choice:";
			int check;
			cin >> check;
			if (check == 1)
			{
				continue;
			}
			else if (check == 2)
			{
				bool check3 = false;
				do {
					cout << "Enter username: ";
					string admin_name;
					cin >> admin_name;



					bool found = false;
					int admin_position = -1;

					for (int i = 0; i < size_admin; i++)
					{


						if (Admin[i].get_username() == admin_name)
						{
							admin_position = i;
							found = true;
						}
					}
					if (found)
					{
						
						string new_password;
						cout << "Enter new password: ";

						char ch;
						do {
							check3 = true;
							ch = _getch(); // Get keystroke

							if (ch == 13) { // Enter key ascii
								break;
							}
							else if (ch == 8) { // Backspace key
								if (!new_password.empty()) { // Check if there are characters to remove
									new_password.pop_back();
									cout << "\b \b"; // Remove * from console
								}
							}
							else { // Other key
								new_password.push_back(ch);
								cout << "*";
							}
						} while (true);
						if (validate_password(new_password) == false)
						{
							system("clear");
							cout << endl<<"password format not followed. Kindly select what do you want to do : \n[1]Reset Password Again\n[2]Go to Log In\n[3]Go to main menu\n[4]Exit\nKindly Enter your Choice:";
							int check;
							cin >> check;
							if (check == 1)
							{
								check3 = false;
								continue;
							}
							else if (check == 2)
							{
								Admin_Login();
							}
							else if (check == 3)
							{
								main_menu();
							}
							else if (check == 4)
							{
								exit(0);
							}
						}
						Admin[admin_position].set_password(new_password);
						ofstream o_file(Admin[0].get_filename());
						if (!o_file) {
							cout << "Error opening the file." << endl;
							return;
						}
						else {
							for (int i = 0; i < size_admin; i++)
							{

								o_file <<  Admin[i].get_username() << ' ' << Admin[i].get_password() << endl;



							}
							o_file.close();

							cout << "\nPassword changed successfully!... redirecting to login" << endl;
							Sleep(5000); // 5000 milliseconds = 5 seconds
							system("cls");
							Admin_Login();
						}

						check3 = true;
						



					}
					else if (!found)
					{
						cout << "Admin with the given username not found!" << endl;

						cout << " So, password can't be reset.Select what do you want to do:\n[1]Reset again\n[2]Go to Admin Log In\n[3]Go to main menu\n[4]Exit" << endl;
						int check1;
						cin >> check1;
						if (check1 == 1)
						{
							check3 = false;
						}
						else if (check1 == 2)
						{

							Admin_Login();
						}
						else if (check1 == 3)
						{
							main_menu();
						}
						else if (check1 == 4)
						{
							exit(0);
						}
					}
					
				} while (check3 == false);
			}
			else if (check == 3)
			{
				main_menu();
			}
			else if (check == 4)
			{
				exit(0);
			}
			}
	} while (opt2 == false);
}



void passenger_login()
{
	system("cls");
	int size = passenger_size();
	cout << size;
	passenger* Passenger = new passenger[size];
	ifstream i_file(Passenger[0].get_filename());
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else {
		string u, p, p_num;
		bool x1, x2;
		for (int i = 0; i < size; i++)
		{

			i_file >> u >> p_num >> x1 >> x2 >> p;


			Passenger[i].set_username(u);
			Passenger[i].set_passport(p_num);
			Passenger[i].set_visa_stamp(x1);
			Passenger[i].set_is_exp(x2);
			Passenger[i].set_password(p);
		}
		i_file.close();

		bool opt4 = false;
		do {
			system("cls");
			cout << "\n\t\tLOG IN\n\nUsername(CNIC): ";
			string passenger_CNIC;
			cin.ignore();
			getline(cin, passenger_CNIC);
			string passenger_password = "";
			char ch_passenger_password;


			int Length = 0;

			cout << "Password: ";
			do {
				ch_passenger_password = _getch();   // Get keystroke

				if (ch_passenger_password == 13) { // Enter key ascii

					break;
				}
				else if (ch_passenger_password == 8) { // Backspace key
					if (Length > 0) {         // Check if there are characters to remove
						passenger_password.pop_back();
						cout << "\b \b";     // Remove * from console
						Length--;
					}
				}
				else {                      // Other key
					Length++;
					passenger_password.push_back(ch_passenger_password);
					cout << "*";
				}
			} while (true);
			for (int i = 0; i < size; i++)
			{
				if (Passenger[i].get_username() == passenger_CNIC && Passenger[i].get_password() == passenger_password)
				{
					opt4 = true;
					passenger_work(i);
					break;

				}
			}

			system("CLS");
			if (opt4 == false)
			{
				cout << "Invalid username or password. Kindly select what do you want to do : \n[1]Re-enter username & password\n[2]Reset Password\n[3]Go to main menu\n[4]Exit\nKindly Enter your Choice:";
				int check;
				cin >> check;
				if (check == 1)
				{
					continue;
				}
				else if (check == 2)
				{
					reset_passenger_password();
				}
				else if (check == 3)
				{
					main_menu();
				}
				else if (check == 4)
				{
					exit(0);
				}
			}

		} while (opt4 == false);
	}
}

void reset_passenger_password()
{
	system("cls");
	string passenger_password;
	string passenger_name;
	int size = passenger_size();
	passenger* Passenger = new passenger[size];
	ifstream i_file(Passenger[0].get_filename());
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else {
		string u, p, p_num;
		bool x1, x2;
		for (int i = 0; i < size; i++)
		{

			i_file >> u >> p_num >> x1 >> x2 >> p;


			Passenger[i].set_username(u);
			Passenger[i].set_passport(p_num);
			Passenger[i].set_visa_stamp(x1);
			Passenger[i].set_is_exp(x2);
			Passenger[i].set_password(p);
		}
		i_file.close();
		system("cls");
		cout << "\n\t\tReset Password\n\nEnter username: ";
		cin >> passenger_name;
		bool opt10 = false;
		int passenger_position;
		for (int i = 0; i < size; i++)
		{
			if (Passenger[i].get_username() == passenger_name)
			{
				opt10 = true;
				passenger_position = i;
				break;
			}
		}
		if (opt10 == true)
		{



			string passenger_password = "";
			char ch_passenger_password;


			int Length = 0;

			cout << "Enter new password :";
			do {
				ch_passenger_password = _getch();   // Get keystroke

				if (ch_passenger_password == 13) { // Enter key ascii

					break;
				}
				else if (ch_passenger_password == 8) { // Backspace key
					if (Length > 0) {         // Check if there are characters to remove
						passenger_password.pop_back();
						cout << "\b \b";     // Remove * from console
						Length--;
					}
				}
				else {                      // Other key
					Length++;
					passenger_password.push_back(ch_passenger_password);
					cout << "*";
				}
			} while (true);

			if (validate_password(passenger_password) == false)
			{
				system("cls");
				cout << endl<< "password format not followed. Kindly select what do you want to do : \n[1]Reset Password Again\n[2]Go to Log In\n[3]Go to main menu\n[4]Exit\nKindly Enter your Choice:";
				int check;
				cin >> check;
				if (check == 1)
				{
					reset_passenger_password();
				}
				else if (check == 2)
				{
					passenger_login();
				}
				else if (check == 3)
				{
					main_menu();
				}
				else if (check == 4)
				{
					exit(0);
				}
			}
			Passenger[passenger_position].set_password(passenger_password);
			ofstream o_file(Passenger[0].get_filename());
			if (!o_file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else {
				for (int i = 0; i < size; i++)
				{

					o_file <<  Passenger[i].get_username() << ' ' << Passenger[i].get_passport() << ' ' << Passenger[i].get_visa_stamp() << ' ' << Passenger[i].get_is_exp() << ' ' << Passenger[i].get_password() << endl;



				}
				o_file.close();
				cout << "Password changed successfully!...redirecting to log in" << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				system("cls");
				passenger_login();

			}
		}
		else
		{
			cout << "username not found... So, password can't be reset.Select what do you want to do:\n[1]Reset again\n[2]Go to passenger Log In\n[3]Go to main menu\n[4]Exit" << endl;
			int check1;
			cin >> check1;
			if (check1 == 1)
			{
				reset_passenger_password();
			}
			else if (check1 == 2)
			{
				passenger_login();
			}
			else if (check1 == 3)
			{
				main_menu();
			}
			else if (check1 == 4)
			{
				exit(0);
			}
		}


	}
}

void passenger_signup()
{
	system("cls");
	string p_number = "N/A";
	bool visa_Stamp = false;
	bool is_visa_valid = false;

	int size = passenger_size();
	
	passenger* Passenger = new passenger[size];
	
	ifstream i_file(Passenger[0].get_filename());
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else {
		string u, p;
		for (int i = 0; i < size; i++)
		{

			i_file >> u >> p;
			

			Passenger[i].set_username(u);
			Passenger[i].set_password(p);
			
		}
		i_file.close();
		

	bool opt5 = false;
	system("cls");
		cout << "\n\\t\tSIGN UP\n\nUsername(CNIC without dashes): ";
		
		string passenger_CNIC;
		cin.ignore();
		
			getline(cin, passenger_CNIC);
			if (passenger_CNIC.length() != 13 || validate_username_p(passenger_CNIC)==false)
			{
				system("cls");
				cout << "Invalid username(CNIC)Select what do you want to do:\n[1]Sign Up again\n[2]Go to passenger Log In\n[3]Go to main menu\n[4]Exit" << endl;
				int check1;
				cin >> check1;
				if (check1 == 1)
				{
					passenger_signup();
				}
				else if (check1 == 2)
				{
					passenger_login();
				}
				else if (check1 == 3)
				{
					main_menu();
				}
				else if (check1 == 4)
				{
					exit(0);
				}
				
			}
			bool x = false;
			for (int i = 0; i < size; i++)
			{
				if (Passenger[i].get_username() == passenger_CNIC)
				{
					x = true;
					break;
				}
			}
			if (x == true)
			{
				system("cls");
				cout << "username(CNIC) already exist. Select what do you want to do:\n[1]Sign Up again\n[2]Go to passenger Log In\n[3]Go to main menu\n[4]Exit" << endl;
				int check1;
				cin >> check1;
				if (check1 == 1)
				{
					passenger_signup();
				}
				else if (check1 == 2)
				{
					passenger_login();
				}
				else if (check1 == 3)
				{
					main_menu();
				}
				else if (check1 == 4)
				{
					exit(0);
				}
			}
			bool check_y = false;
			do {
				check_y = true;
				
				
				bool check_p;
				cout << "Do you have passport :\n[1]Yes\n[0]No\nEnter your choice: ";
				cin >> check_p;
				bool check_x;
				if (check_p == 1)
				{
					cout << "Enter passport number: ";
					cin >> p_number;

					check_x = validate_passport(p_number);

					if (check_x == false)
					{
						system("cls");
						cout << "Passport number not valid. What do you want to do: [1]Re-enter passport verification\n[2]Go to main menu\n[3]Exit.\nEnter your choice: ";
						int x;
						cin >> x;
						if (x == 1)
						{
							check_y = false;
							continue;
						}
						else if (x == 2)
						{
							main_menu();
						}
						else if (x == 3)
						{
							cout << "Exiting program...";
							exit(0);
						}
						else
						{
							Sleep(5000); // 5000 milliseconds = 5 seconds
							system("cls");
							main_menu();
						}
					}

					cout << "Is there a visa stamp on your passport:\n[1]Yes\n[0]No\nEnter your choice: ";
					cin >> visa_Stamp;
					cout << "is your visa valid(not expired till now :\n[1]Yes\n[0]No\nEnter your choice: ";
					cin >> is_visa_valid;
				}
				

			} while (check_y == false);
			
		string passenger_password="";
		char ch_passenger_password;
		
		
		int Length = 0;

		cout << "Password: ";
		do {
			ch_passenger_password = _getch();   // Get keystroke

			if (ch_passenger_password == 13) { // Enter key ascii

				break;
			}
			else if (ch_passenger_password == 8) { // Backspace key
				if (Length > 0) {         // Check if there are characters to remove
					passenger_password.pop_back();
					cout << "\b \b";     // Remove * from console
					Length--;
				}
			}
			else {                      // Other key
				Length++;
				passenger_password.push_back(ch_passenger_password);
				cout << "*";
			}

		} while (true);
		
		
		
			
		if (validate_password(passenger_password) == false)
		{
			system("cls");
			cout << endl<<"password format not followed. Select what do you want to do:\n[1]Sign Up again\n[2]Go to passenger Log In\n[3]Go to main menu\n[4]Exit" << endl;
			int check1;
			cin >> check1;
			if (check1 == 1)
			{
				passenger_signup();
			}
			else if (check1 == 2)
			{
				passenger_login();
			}
			else if (check1 == 3)
			{
				main_menu();
			}
			else if (check1 == 4)
			{
				exit(0);
			}
		}
		else
		{
					
					system("CLS");
					cout << "Username(CNIC): " << passenger_CNIC << endl;
					cout << "Password: ";
					for (int i = 0; passenger_password[i] != '\0'; i++)
					{
						cout << "*";
					}

					cout << endl;
					string re_p_password = "";

					char passenger_password_ch;


					Length = 0;

					cout << "Re-Enter Password: ";
					do {
						passenger_password_ch = _getch();   // Get keystroke

						if (passenger_password_ch == 13) { // Enter key ascii

							break;
						}
						else if (passenger_password_ch == 8) { // Backspace key
							if (Length > 0) {         // Check if there are characters to remove
								re_p_password.pop_back();
								cout << "\b \b";     // Remove * from console
								Length--;
							}
						}
						else {                      // Other key
							Length++;
							re_p_password.push_back(passenger_password_ch);
							cout << "*";
						}
					} while (true);
					cout << endl;

					if (re_p_password == passenger_password)
					{
						ifstream i_file(Passenger[0].get_filename());
						passenger* Passenger = new passenger[size + 1];
						if (!i_file) {
							cout << "Error opening the file." << endl;
							return;
						}
						else
						{
							string u, p,p_num;
							bool x1, x2;
							for (int i = 0; i <= size; i++)
							{
								if (i == size)
								{
									Passenger[i].set_username(passenger_CNIC);
									Passenger[i].set_passport(p_number);
									Passenger[i].set_visa_stamp(visa_Stamp);
									Passenger[i].set_is_exp(is_visa_valid);
									Passenger[i].set_password(passenger_password);
									break;
								}

								i_file >> u >>p_num>>x1>>x2>> p;


								Passenger[i].set_username(u);
								Passenger[i].set_passport(p_num);
								Passenger[i].set_visa_stamp(x1);
								Passenger[i].set_is_exp(x2);
								Passenger[i].set_password(p);
							}
							i_file.close();
							size += 1;

							ofstream o_file(Passenger[0].get_filename(),ios::app);
							if (!o_file)
							{
								cout << "Error opening the file." << endl;
								return;
							}
							else
							{
								
									o_file <<  Passenger[size-1].get_username() <<' '<< Passenger[size - 1].get_passport() << ' ' << Passenger[size - 1].get_visa_stamp() << ' ' << Passenger[size - 1].get_is_exp() << ' ' << Passenger[size - 1].get_password() << endl;

								
								o_file.close();

								cout << "Account created successfully...Redirecting to login page..." << endl;
								Sleep(5000); // 5000 milliseconds = 5 seconds
								system("cls");
								passenger_login();
							}

						}
					}
					else
					{
						cout << "Password does not match. Thus account creation failed. What do you want to do :\n[1]Sign Up again\n[2]Go to passenger Log In\n[3]Go to main menu\n[4]Exit" << endl;
						int check1;
						cin >> check1;
						if (check1 == 1)
						{
							passenger_signup();
						}
						else if (check1 == 2)
						{
							passenger_login();
						}
						else if (check1 == 3)
						{
							main_menu();
						}
						else if (check1 == 4)
						{
							exit(0);
						}

					}
				}
			}

		}



	void Flight_schedule(int i=-1)
	{
		system("cls");
		cout << "\n\t\tFlight Schedule\n\nSelect departure city:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
		int choice;
		cin >> choice;
		string city;
		switch (choice) {
		case 1:
			city = "Islamabad";

			break;
		case 2:
			city = "Lahore";
			break;
		case 3:
			city = "Karachi";
			break;
		case 4:
			city = "Quetta";
			break;
		case 5:
			city = "Peshawar";
			break;

		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			passenger_work(i); // Call the function recursively if an invalid choice is made
			break;
		}
		}

		cout << "Select airport:\n[1]North\n[2]South\nEnter your choice:  ";
		int choice1;
		cin >> choice1;
		string Airport1;
		switch (choice1) {
		case 1:
			Airport1 = "North";

			break;
		case 2:
			Airport1 = "South";
			break;
		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			passenger_work(i); // Call the function recursively if an invalid choice is made
			break;
		}
		}
		cout << "Choose travel route:\n[0]Local\n[1]International\nEnter your choice: ";
		bool t_r;
		cin >> t_r;
		string route;
		switch (t_r) {
		case 0:
			route = 'L';

			break;
		case 1:
			route = 'I';
			break;
		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			passenger_work(i); // Call the function recursively if an invalid choice is made
			break;
		}
		}
		string filename = "Flight_"+Airport1 + city + "_" + route+".txt";
		cout << filename;
		
		int num_flights = flight_num(filename)-1;
		
		ifstream i_file(filename);
		Flight* flights = new Flight[num_flights];
		if (!i_file) {
			cout << "Error opening the file." << endl;
			return;
		}
		else
		{
			string y1, y2, y3, y4, y5, y6;
			int x1, x2, x3, x4;
			bool z1;
			for (int i = 0; i < num_flights; i++)
			{


				i_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4>>z1;
				
				Airport Dep(y2);
				Airport Des(y3);
				Airplane Plane(y6, x1, x2,x1+x2);
				
				bool status = flight_status(y4,x1,x2,z1);
				
				flights[i] = Flight(y1,&Dep,&Des,y4,y5,Plane,x3,x4,z1,status);
				cout << "Flight # " << i + 1<<" : "<<endl;
				flights[i].printDetails();
				cout << "Availability status: ";
				if (status == true)
				{
					cout << "Available\n";
				}
				else cout << "Not Available\n";
				cout << endl;
				
			}
			i_file.close();
			cout << "To Go back,";
			system("pause");
		}
		

	}

	void update_passenger_datails(int i)
	{
		system("cls");

		string p_number = "N/A";
		bool visa_Stamp = false;
		bool is_visa_valid = false;

		int size = passenger_size();

		passenger* Passenger = new passenger[size];

		ifstream i_file(Passenger[0].get_filename());
		if (!i_file) {
			cout << "Error opening the file." << endl;
			return;
		}
		else {
			string u, p, p_num;
			bool x1, x2;


			for (int i = 0; i < size; i++)
			{

				i_file >> u >> p_num >> x1 >> x2 >> p;


				Passenger[i].set_username(u);
				Passenger[i].set_passport(p_num);
				Passenger[i].set_visa_stamp(x1);
				Passenger[i].set_is_exp(x2);
				Passenger[i].set_password(p);

			}
			i_file.close();
		}
		system("cls");
			cout << "\n\t\tDeatail Updating Panel\n\nWhat do you want to do: \n\n[1]Update Password\n[2]Update passport and visa details\n[3]Back to passenger details\nEnter your choice: ";
			int choice;
			cin >> choice;
			switch (choice) {

			case 1:
			{
				reset_passenger_password();

			}
			break;
			case 2:
			{
				bool check_y = false;
				do {
					check_y = true;


					bool check_p;
					cout << "Do you have passport :\n[1]Yes\n[0]No\nEnter your choice: ";
					cin >> check_p;
					bool check_x;
					if (check_p == 1)
					{
						cout << "Enter passport number: ";
						cin >> p_number;

						check_x = validate_passport(p_number);

						if (check_x == false)
						{
							system("cls");
							cout << "Passport number not valid. What do you want to do: [1]Re-enter passport verification\n[2]Go Back to passenger Panel\n[3]Exit.\nEnter your choice: ";
							int x;
							cin >> x;
							if (x == 1)
							{
								check_y = false;
								continue;
							}
							else if (x == 2)
							{
								passenger_work(i);
							}
							else if (x == 3)
							{
								cout << "Exiting program...";
								exit(0);
							}
							else
							{
								Sleep(5000); // 5000 milliseconds = 5 seconds
								system("cls");
								main_menu();
							}
						}

						cout << "Is there a visa stamp on your passport:\n[1]Yes\n[0]No\nEnter your choice: ";
						cin >> visa_Stamp;
						cout << "is your visa valid(not expired till now :\n[1]Yes\n[0]No\nEnter your choice: ";
						cin >> is_visa_valid;
						Passenger[i].set_passport(p_number);
						Passenger[i].set_is_exp(is_visa_valid);
						Passenger[i].set_visa_stamp(visa_Stamp);
						ofstream o_file(Passenger[0].get_filename(), ios::app);
						if (!o_file)
						{
							cout << "Error opening the file." << endl;
							return;
						}
						else
						{
							for(int x=0;x<size;x++)
							o_file <<  Passenger[x].get_username() << ' ' << Passenger[x].get_passport() << ' ' << Passenger[x].get_visa_stamp() << ' ' << Passenger[x].get_is_exp() << ' ' << Passenger[x].get_password() << endl;


							o_file.close();
						}
					}


				} while (check_y == false);
			}
			break;
			case 3:
				passenger_work(i);
				break;

			default:
				cout << "Invalid choice. Please enter a valid option." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i); // Call the function recursively if an invalid choice is made
				break;
			}
		}



		

		void seat_booking(int i)
		{
			system("cls");
			//cout << "1";

			int size = passenger_size();
			cout << size;
			passenger* Passenger = new passenger[size];
			ifstream i_file(Passenger[0].get_filename());
			if (!i_file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else {
				string u, p, p_num;
				bool x1, x2;
				for (int i = 0; i < size; i++)
				{

					i_file >> u >> p_num >> x1 >> x2 >> p;


					Passenger[i].set_username(u);
					Passenger[i].set_passport(p_num);
					Passenger[i].set_visa_stamp(x1);
					Passenger[i].set_is_exp(x2);
					Passenger[i].set_password(p);
				}
				
			}
			i_file.close();
			system("cls");
			cout << "\n\t\tSeat Booking Panel\n\nSelect departure city:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
			int choice;
			cin >> choice;
			string city;
			switch (choice) {
			case 1:
				city = "Islamabad";

				break;
			case 2:
				city = "Lahore";
				break;
			case 3:
				city = "Karachi";
				break;
			case 4:
				city = "Quetta";
				break;
			case 5:
				city = "Peshawar";
				break;

			default:
			{
				cout << "Invalid choice. Please enter a valid option." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i); // Call the function recursively if an invalid choice is made
				break;
			}
			}

			cout << "Select airport:\n[1]North\n[2]South\nEnter your choice:  ";
			int choice1;
			cin >> choice1;
			string Airport1;
			switch (choice1) {
			case 1:
				Airport1 = "North";

				break;
			case 2:
				Airport1 = "South";
				break;
			default:
			{
				cout << "Invalid choice. Please enter a valid option." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i); // Call the function recursively if an invalid choice is made
				break;
			}
			}
			cout << "Choose travel route:\n[0]Local\n[1]International\nEnter your choice: ";
			bool t_r;
			cin >> t_r;
			string route;
			switch (t_r) {
			case 0:
				route = 'L';

				break;
			case 1:
				route = 'I';
				break;
			default:
			{
				cout << "Invalid choice. Please enter a valid option." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i); // Call the function recursively if an invalid choice is made
				break;
			}
			}
			if (t_r == 1 && Passenger[i].get_passport() == "N/A")
			{
				cout << "You do not have passport for international flights.Redirecting to passenger panel." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i);
			}
			if (t_r == 1 && Passenger[i].get_visa_stamp() == false)
			{
				cout << "You do not have visa stamp for international flights.Redirecting to passenger panel." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i);
			}
			if (t_r == 1 && Passenger[i].get_is_exp() == false)
			{
				cout << "You visa is expired for international flights.Redirecting to passenger panel." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i);
			}
			string filename = "Flight_" + Airport1 + city + "_" + route + ".txt";
			cout << filename;

			int num_flights = flight_num(filename)-1;
			
			ifstream ifile(filename);
			Flight* flights = new Flight[num_flights];
			if (!i_file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else
			{
				string y1, y2, y3, y4, y5, y6;
				int x1, x2, x3, x4;
				bool z1;
				for (int i = 0; i < num_flights; i++)
				{


					ifile >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;

					Airport Dep(y2);
					Airport Des(y3);
					Airplane Plane(y6, x1, x2, x1 + x2);

					bool status = flight_status(y4, x1, x2, z1);

					flights[i] = Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1);
					cout << "Flight # " << i + 1 << " : " << endl;
					flights[i].printDetails_cost();
					cout << "Availability status: ";
					if (status == true)
					{
						cout << "Available\n";
					}
					else cout << "Not Available\n";
					cout << endl;

				}
				ifile.close();
			}
			

			
			cout << "Enter The flight ID you want to book: ";
			int ide;
			cin >> ide;
			
			if (num_flights <= ide)
			{
				cout << "how would you like to travel\n[E] Economy class\n[B] Business class\nEnter your choice: ";
				char ch;
				cin >> ch;
				bool gy = flights[ide-1].bookSeat(ch, t_r,i,filename,ide-1);
				if (gy == true)
				{
					cout << "1";
					cout << "Seat booked.redirecting to passenger pannel"<<endl;
					Sleep(5000); // 5000 milliseconds = 5 seconds
					passenger_work(i);

				}
				else
				{
					cout << "Seat not booked.redirecting to passenger pannel" << endl;
					Sleep(5000); // 5000 milliseconds = 5 seconds
					passenger_work(i);
				}
			}

		}
		void Erase_File_Line(const string& filename, int line_number) {
			ifstream Read_File(filename);
			ofstream Write_File("temp.txt");

			if (!Read_File.is_open()) {
				cout << "Read file not opened" << endl;
				return;
			}

			if (!Write_File.is_open()) {
				cout << "Write file not opened" << endl;
				return;
			}

			string line;
			int current_line_number = 1;
			while (getline(Read_File, line)) {
				if (current_line_number != line_number) {
					Write_File << line << endl;
				}
				current_line_number++;
			}

			Read_File.close();
			Write_File.close();

			remove(filename.c_str());
			int Rename_Successful = rename("temp.txt", filename.c_str());

			if (Rename_Successful != 0) {
				cout << "Error In Renaming the Write File" << endl;
				return;
			}

			cout << "Flight Entry Deleted Successfully" << endl;
		}
		
		void cancel_reservation(int i)
		{
			int size = passenger_size();
			ifstream i_file("passenger_Log_In.txt");
			passenger* Passenger = new passenger[size];
			if (!i_file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else
			{
				string u, p, p_num;
				bool x1, x2;
				for (int i = 0; i < size; i++)
				{


					i_file >> u >> p_num >> x1 >> x2 >> p;


					Passenger[i].set_username(u);
					Passenger[i].set_passport(p_num);
					Passenger[i].set_visa_stamp(x1);
					Passenger[i].set_is_exp(x2);
					Passenger[i].set_password(p);
				}
				i_file.close();


				cout << "You have the following latest bookings:" << endl;
				int x;
				ifstream i_file("booking_details.txt");
				string cnic, oa, da;
				float tp;
				int s = 0;
				if (!i_file)
				{
					Sleep(5000); // 5000 milliseconds = 5 seconds
					return;
				}
				else
				{

					while (!(i_file.eof())) {
						i_file >> cnic >> oa >> da >> tp;
						if (cnic == Passenger[i].get_username())
						{
							cout << "booking " << s + 1 << " : " << endl;
							cout << "Departure airport: " << oa << endl;
							cout << "Arrival airport: " << da << endl;
							cout << "Ticket Prize: " << tp << endl;
							s += 1;
						}
					}

					i_file.close();
					s -= 1;
					if (s == 0) {
						cout << "you have no booking...redirecting to passenger panel" << endl;
						Sleep(5000); // 5000 milliseconds = 5 seconds
						passenger_work(i);
					}

					cout << "Enter the booking number you want to cancel: ";
					cin >> x;


					if (s > x - 1 && x > 0)
					{
						cout << "Reservation cancelled" << endl;
						cout << "A refund amount of Rs " << tp - (tp * 25 / 100) << " has been transferred to your account with a deduction of 25% "<<"redirecting to passenger panel in page" << endl;
						Sleep(5000); // 5000 milliseconds = 5 seconds
						Erase_File_Line("booking_details.txt", x);
						


					}

				}
			}
		}
		void passenger_work(int i) {
			system("cls");
			cout << "\n\t\tPassenger Panel\n\nWhat do you want to do: \n[1]See flight schedule.\n[2]Seat Booking\n[3]Cancel Reservation\n[4]Update User details\n[5]Go to main menu\n[6]Exit\nEnter your choice: " << endl;
			int choice;
			cin >> choice;

			switch (choice) {
			case 1:
			{
				Flight_schedule(i);
				
				passenger_work(i);
			}
				break;
			case 2:
				seat_booking(i);
				
				break;
			case 3:
				cancel_reservation(i);
				break;
			case 4:
				update_passenger_datails(i);// function for updating user details
				break;
			case 5:
				main_menu();
				break;
			case 6:
				exit(0);
				break;
			default:
				cout << "Invalid choice. Please enter a valid option." << endl;
				Sleep(5000); // 5000 milliseconds = 5 seconds
				passenger_work(i); // Call the function recursively if an invalid choice is made
				break;
			
			}
		}


		string get_arrival(string x,int y,int z)
		{
			int a,b;
			string h="", m="";
			a = stoi(x);
			for (int i = 3; i <5; i++)
			{
				m[i] +=x[i] ;
			}
			b = stoi(m);
			int hr, min;
			hr =a + y;
			min = b + z;
			if (hr == 24 && min == 0) {}
			if (hr == 24 && min > 0) { hr = 1; }
			else if (hr > 24)
			{
				hr -= 24;
				if (min > 59) { min -= 60; hr += 1; }
			}
			else if (min > 59)
			{
				min -= 60;
				hr += 1;
			}
			string t1, t2, d2;
			if (hr >= 1 && hr <= 9)
			{
				t1 = '0' + to_string(hr);
			}
			else
			{
				t1 = to_string(hr);
			}
			if (min >= 0 && min <= 9)
			{
				t2 = '0' + to_string(min);
			}
			else
			{
				t2 = to_string(min);
			}
			d2 = t1 + ":" + t2;
			return d2;
		}

void change_flight_schedule()
{
	system("cls");
	cout << "\n\t\tChange Flight Schedule\n\nSelect departure city of flight:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
	int choice;
	cin >> choice;
	string city;
	switch (choice) {
	case 1:
		city = "Islamabad";

		break;
	case 2:
		city = "Lahore";
		break;
	case 3:
		city = "Karachi";
		break;
	case 4:
		city = "Quetta";
		break;
	case 5:
		city = "Peshawar";
		break;

	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}

	cout << "Select airport from where flight will take off:\n[1]North\n[2]South\nEnter your choice:  ";
	int choice1;
	cin >> choice1;
	string Airport1;
	switch (choice1) {
	case 1:
		Airport1 = "North";

		break;
	case 2:
		Airport1 = "South";
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	cout << "Choose travel route of flight:\n[0]Local\n[1]International\nEnter your choice: ";
	bool t_r;
	cin >> t_r;
	string route;
	switch (t_r) {
	case 0:
		route = 'L';

		break;
	case 1:
		route = 'I';
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	string filename = "Flight_" + Airport1 + city + "_" + route + ".txt";
	cout << filename;
	int num_flights = flight_num(filename)-1;
	ifstream i_file(filename);
	Flight* flights = new Flight[num_flights];
	int f = 0;
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else
	{
		string y1, y2, y3, y4, y5, y6;
		int x1, x2, x3, x4;
		bool z1;
		
		for (int i = 0; i < num_flights; i++)
		{


			i_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;

			Airport Dep(y2);
			Airport Des(y3);
			Airplane Plane(y6, x1, x2,x1+x2);
			bool status = flight_status(y4,x1,x2,z1);		
			Flight x=Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1,status);
			flights[i] = x;													//copy constructor used
			cout << "Flight # " << i + 1 << " : " << endl;
			flights[i].printDetails();
			cout << "Availability status: ";
			if (status == true)
			{
				cout << "Available\n";
			}
			else cout << "Not Available\n";
			cout << endl;
			f++;
		}
		i_file.close();
	}
	string d2; string d1;
	string t1, t2;
	cout << "Enter the flight number whose schedule you want to change:  ";
	int x;
	cin >> x;

	if (num_flights <= x) {
		//cout << "1";
		cout << "Enter Departure hour[1-24]: ";
		int hr;
		cin >> hr;
		cout << "Enter departure minutes[0-59]: ";
		int min;
		cin >> min;
		if(min<0||min>59){
			cout << "Invalid entry. Redirecting to admin panel...\n";
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work();
		}
		if (hr == 24 && min==0) { d2 = "24:00"; }
		else if (hr < 1 || hr>23)
		{
			cout << "Invalid entry. Redirecting to admin panel...\n";
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work();
		}
		else
		{
			if (hr >= 1 && hr <= 9)
			{
				t1 = '0' + to_string(hr);
			}
			else
			{
				t1 = to_string(hr);
			}
			if (min >= 0 && min <= 9)
			{
				t2 = '0' + to_string(min);
			}
			else
			{
				t2 = to_string(min);
			}
			d2 = t1 + ":" + t2;
			d1 = get_arrival(d2, flights[x - 1].get_t_h(), flights[x - 1].get_t_m());
			ofstream o_file(filename);

			if (!o_file) {
				cout << "Error opening the file." << endl;
				return;
			}
			else
			{


				for (int i = 0; i < num_flights; i++)
				{

					if (i == x - 1)
					{
						o_file << flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << d2 << ' ' << d1 << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;
						
						continue;
					}
					o_file <<  flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;

				}
				
				o_file.close();
			}

		}
			

	}
	else { cout << "flight ID not found. Redirecting to admin panel" << endl; Sleep(5000); // 5000 milliseconds = 5 seconds
	Admin_work(); }

}

void restrict_passenger_number()
{
	system("cls");
	cout << "\n\t\tChange Passenger number and covid Conditions\n\nSelect departure city of flight:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
	int choice;
	cin >> choice;
	string city;
	switch (choice) {
	case 1:
		city = "Islamabad";

		break;
	case 2:
		city = "Lahore";
		break;
	case 3:
		city = "Karachi";
		break;
	case 4:
		city = "Quetta";
		break;
	case 5:
		city = "Peshawar";
		break;

	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}

	cout << "Select airport from where flight will take off:\n[1]North\n[2]South\nEnter your choice:  ";
	int choice1;
	cin >> choice1;
	string Airport1;
	switch (choice1) {
	case 1:
		Airport1 = "North";

		break;
	case 2:
		Airport1 = "South";
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	cout << "Choose travel route of flight:\n[0]Local\n[1]International\nEnter your choice: ";
	bool t_r;
	cin >> t_r;
	string route;
	switch (t_r) {
	case 0:
		route = 'L';

		break;
	case 1:
		route = 'I';
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	string filename = "Flight_" + Airport1 + city + "_" + route + ".txt";
	//cout << filename;
	int num_flights = flight_num(filename)-1;
	//cout << num_flights;
	ifstream i_file(filename);
	Flight* flights = new Flight[num_flights];
	int f = 0;
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else
	{
		string y1, y2, y3, y4, y5, y6;
		int x1, x2, x3, x4;
		bool z1;

		for (int i = 0; i < num_flights; i++)
		{


			i_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;

			Airport Dep(y2);
			Airport Des(y3);
			Airplane Plane(y6, x1, x2,x1+x2);
			bool status = flight_status(y4,x1,x2,z1);
			Flight x = Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1,  status);
			flights[i] = x;													//copy constructor used
			cout << "Flight # " << i + 1 << " : " << endl;
			flights[i].printDetails();
			cout << "Availability status: ";
			if (status == true)
			{
				cout << "Available\n";
			}
			else cout << "Not Available\n";
			cout << endl;
			f++;
		}
		i_file.close();
	}
	cout << f;
	cout << "Enter flight number: ";
	int x;
	cin >> x;
	
	if (num_flights <= x )
	{

		if (flights[x-1].get_covid() == false)
		{
			cout << "This flight has no covid restictions" << endl;
			cout << "Number of available seats: " << flights[x - 1].getAvailableEconomySeats() + flights[x - 1].getAvailableBusinessSeats() << endl;
			/*if (flight_status(flights[x - 1].getOriginCity(), flights[x - 1].getAvailableEconomySeats(), flights[x - 1].getAvailableBusinessSeats(), flights[x - 1].get_covid()) == false)
			{
				cout << "Flight has already departed...Redirecting to admin panel\n";
				Admin_work();

			}*/

			cout << "Do you want to shift covid status and change the number of available seats:\n[1]Yes\n[0]No\nEnter your choice:  ";
			bool choice2;
			cin >> choice2;
			if (choice2 = 0)
			{
				cout << "Flight status and number of seats not changed ...Redirecting to admin panel\n";
				Sleep(5000); // 5000 milliseconds = 5 seconds
				Admin_work();
			}
			else
			{

				flights[x - 1].set_Available_Economy_Seats(flights[x - 1].getAvailableEconomySeats()+25);
				flights[x - 1].set_Available_Business_Seats(flights[x - 1].getAvailableBusinessSeats()+5);
				flights[x - 1].set_covid_status(1);
				cout << "Flight status and number of seats are now changed\nTotal Seats Available: "<< flights[x - 1].getAvailableEconomySeats() + flights[x - 1].getAvailableBusinessSeats() << endl;
				cout << "Economy Seats: " << flights[x - 1].getAvailableEconomySeats()<<endl;
				cout << "Business Seats: " << flights[x - 1].getAvailableBusinessSeats() << endl<<"Redirecting to admin panel\n";
				Sleep(5000); // 5000 milliseconds = 5 seconds
				Admin_work();

			}



		}
		else
		{

			cout << "This flight has covid restictions" << endl;
			cout << "Number of available seats: " << flights[x - 1].getAvailableEconomySeats() + flights[x - 1].getAvailableBusinessSeats() << endl;
		/*	if (flight_status(flights[x - 1].getOriginCity(), flights[x - 1].getAvailableEconomySeats(), flights[x - 1].getAvailableBusinessSeats(), flights[x - 1].get_covid()) == false)
			{
				cout << "Flight has already departed...Redirecting to admin panel\n";
				Admin_work();

			}*/
			if (flights[x - 1].getAvailableEconomySeats() + flights[x - 1].getAvailableBusinessSeats() < 30)
			{
				cout << "Number of booked passenger are too more for restriction...Redirecting to admin panel\n";
				Sleep(5000); // 5000 milliseconds = 5 seconds
				Admin_work();

			}
			cout << "Do you want to shift covid status and change the number of available seats:\n[1]Yes\n[1]No\nEnter your choice:  ";
			bool choice2;
			cin >> choice2;
			if (choice2 = 0)
			{
				cout << "Flight status and number of seats not changed ...Redirecting to admin panel\n";
				Sleep(5000); // 5000 milliseconds = 5 seconds
				Admin_work();
			}
			else
			{
				flights[x - 1].set_Available_Economy_Seats(flights[x - 1].getAvailableEconomySeats() - 25);
				flights[x - 1].set_Available_Business_Seats(flights[x - 1].getAvailableBusinessSeats() - 5);
				flights[x - 1].set_covid_status(0);
				cout << "Flight status and number of seats are now changed\nTotal Seats Available: " << flights[x - 1].getAvailableEconomySeats() + flights[x - 1].getAvailableBusinessSeats() << endl;
				cout << "Economy Seats: " << flights[x - 1].getAvailableEconomySeats() << endl;
				cout << "Business Seats: " << flights[x - 1].getAvailableBusinessSeats() << endl << "Redirecting to admin panel\n";
				Sleep(5000); // 5000 milliseconds = 5 seconds
				Admin_work();
			}
		}
		cout << "Do you want to shift covid status and change the number of available seats:\n[1]Yes\n[1]No\nEnter your choice:  ";
		bool choice2;
		if (choice2 = 0)
		{
			cout << "Flight status and number of seats not changed ...Redirecting to admin panel\n";
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work();
		}
		else
		{
			flights[x - 1].set_Available_Economy_Seats(flights[x - 1].getAvailableEconomySeats() + 25);
			flights[x - 1].set_Available_Business_Seats(flights[x - 1].getAvailableBusinessSeats() + 5);

			flights[x - 1].set_covid_status(1);

		}
		ofstream o_file(filename);

		if (!o_file) {
			cout << "Error opening the file." << endl;
			return;
		}
		else
		{



			for (int i = 0; i < num_flights; i++)
			{


				o_file <<  flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].getAvailableBusinessSeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;

			}
			o_file.close();
		}

	}
else
	{
		cout << "flight ID not found. Redirecting to admin panel" << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work();
	}



	
}

void add_new_route()
{
	system("cls");
	string city1,loc1;
	cout << "\n\t\tADD NEW ROUTE\n\nSelect departure city of flight:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
	int choice;
	cin >> choice;
	string city;
	switch (choice) {
	case 1:
		city = "Islamabad";

		break;
	case 2:
		city = "Lahore";
		break;
	case 3:
		city = "Karachi";
		break;
	case 4:
		city = "Quetta";
		break;
	case 5:
		city = "Peshawar";
		break;

	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}

	cout << "Select airport from where flight will take off:\n[1]North\n[2]South\nEnter your choice:  ";
	int choice1;
	cin >> choice1;
	string Airport1;
	switch (choice1) {
	case 1:
		Airport1 = "North";

		break;
	case 2:
		Airport1 = "South";
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	cout << "Choose travel route of flight:\n[0]Local\n[1]International\nEnter your choice: ";
	bool t_r;
	cin >> t_r;
	char route;
	switch (t_r) {
	case 0:
		route = 'L';

		break;
	case 1:
		route = 'I';
		break;
	default:
	{
		cout << "Invalid choice. Please enter a valid option." << endl;
		Sleep(5000); // 5000 milliseconds = 5 seconds
		Admin_work(); // Call the function recursively if an invalid choice is made
		break;
	}
	}
	string filename = "Flight_" + Airport1 + city + "_" + route + ".txt";
	//cout << filename;
	int num_flights = flight_num(filename) - 1;
	if ((num_flights >= 5 && route == 'I')||(num_flights >= 5 && route == 'L'))
	{
		system("clear");
		cout<<"Insufficient capacity...redirecting to admin panel"<<endl;
		Sleep(5000);
		Admin_work();
	}
	string destination;
	if (route == 'I')
	{
		cout << "Enter the destination airport: ";
		cin >> destination;
	}
	else
	{
		cout << "\nSelect Destination city of flight:\n[1]Islamabad\n[2]Lahore\n[3]Karachi\n[4]Quetta\n[5]Peshawar\nEnter your choice:  ";
		int choicex;
		cin >> choicex;

		switch (choicex) {
		case 1:
			city1 = "Islamabad";

			break;
		case 2:
			city1 = "Lahore";
			break;
		case 3:
			city1 = "Karachi";
			break;
		case 4:
			city1 = "Quetta";
			break;
		case 5:
			city1 = "Peshawar";
			break;

		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work(); // Call the function recursively if an invalid choice is made
			break;
		}
		}

		cout << "Select airport from where flight will take off:\n[1]North\n[2]South\nEnter your choice:  ";
		int choicey;
		cin >> choicey;

		switch (choicey) {
		case 1:
			loc1 = "North";

			break;
		case 2:
			loc1 = "South";
			break;
		default:
		{
			cout << "Invalid choice. Please enter a valid option." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work(); // Call the function recursively if an invalid choice is made
			break;
		}

		}
		destination = city1 + loc1;
	}
	cout << "Enter departure time:[12:00] ";
	string d_time;
	cin >> d_time;
	cout << "Enter Covid status[0/1]:";
	bool cov;
	cin >> cov;
	int s7;
	int s8;
	if (cov == true)
	{
		s7 = 25;
		s8 = 5;
	}
	else {
		s7 = 50;
		s8 = 10;
	}
	int s9, s10, s5;
	cout << "Enter estimated time in hours:";
	cin >> s9;
	cout << "Enter estimated time in mins:";
	cin>>s10 ;
	string a_time = get_arrival(d_time,s9,s10);
	//cout << num_flights;
	ofstream i_file(filename,ios::app);
	Flight* flights = new Flight[num_flights];
	int f = 0;
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	else
	{
		string y1="Pak-344", y2= Airport1 +'_' + city, y3=destination, y4= d_time, y5= a_time, y6= "NAFS-342";
		int x1=s7, x2=s8, x3=s9, x4=s10;
		bool z1=cov;

		


			i_file << y1 << ' ' << y2 << ' ' << y3 << ' ' << y4 << ' ' << y5 << ' ' << y6 << ' ' << x1 << ' ' << x2 << ' ' << x3 << ' ' << x4 << ' ' << z1 << endl;

			
		}
		i_file.close();
}

void Admin_work()
{
	int choice;
	do {
		system("cls");
		cout << "\n\t\tAdmin Panel" << endl;
		cout << "[1] Change flight schedule" << endl;
		cout << "[2] Add new route" << endl;
		cout << "[3] Restrict passenger numbers" << endl;
		cout << "[4] Update airline inquiry details" << endl;
		cout << "[5] Logout" << endl;
		cout << "[6] Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			change_flight_schedule();
			break;
		case 2:
			add_new_route();
			break;
		case 3:
			restrict_passenger_number();
			break;
		case 4:
			cout << "Airline Inquiry report already up to date...Redirecting to admin panel";
			Sleep(5000); // 5000 milliseconds = 5 seconds
			Admin_work();
			break;
		case 5:
			cout << "Logged out successfully!" << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			main_menu();
			break;
		case 6:
			cout << "Program termination successful.." << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			exit(0);
			break;

		default:
			cout << "Invalid choice. Please try again!" << endl;
			Sleep(5000); // 5000 milliseconds = 5 seconds
			break;
		}
	} while (choice != 5);

}


