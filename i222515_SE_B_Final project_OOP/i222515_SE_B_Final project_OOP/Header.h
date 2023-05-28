#pragma once
using namespace std;
class Airport;
class City;
class Airplane;
class Flight;
class admin
{
	string username;
	string password;
	string filename;
public:
	admin(string u = "", string p = "")
	{
		username = u;
		password = p;
		filename = "Admin_Log_In.txt";
	}

	void set_username(string u)
	{
		username = u;
	}
	void set_password(string p)
	{
		password = p;
	}
	string get_filename()
	{
		return filename;
	}
	string get_username()
	{
		return username;
	}
	string get_password()
	{
		return password;
	}

};
class passenger
{
private:
	string username;
	string password;
	string filename;
	string passport_num;
	bool visa_stamp;
	bool is_exp;
public:
	passenger(string u = "", string p = "",string p_n="N/A")
	{
		username = u;
		password = p;
		passport_num = p_n;
		filename = "passenger_Log_In.txt";
		visa_stamp = false;
		is_exp = false;
	}
	void set_username(string u)
	{
		username = u;
	}
	void set_password(string p)
	{
		password = p;
	}
	void set_passport(string p)
	{
		passport_num = p;
	}
	void set_visa_stamp(bool v_s)
	{
		visa_stamp = v_s;
	}
	void set_is_exp(bool i_exp)
	{
		is_exp = i_exp;
	}
	string get_username()
	{
		return username;
	}
	string get_filename()
	{
		return filename;
	}
	string get_password()
	{
		return password;
	}
	bool get_visa_stamp()
	{
		return visa_stamp;
	}
	bool get_is_exp()
	{
		return is_exp;
	}
	string get_passport()
	{
		return passport_num;
	}
	
};

string getCurrentDate() {
	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	int year = now.tm_year + 1900;
	int month = now.tm_mon + 1;
	int day = now.tm_mday;
	return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
}

int current_time_hours()
{
	time_t now = time(nullptr);
	struct tm local_time;
	localtime_s(&local_time, &now);
	int hours = local_time.tm_hour;
	int minutes = local_time.tm_min;
	int seconds = local_time.tm_sec;
//	cout << "Current time is: " << hours << endl;
	return hours;
}

string current_time_hours_min()
{
	time_t now = time(nullptr);
	struct tm local_time;
	localtime_s(&local_time, &now);
	int hours = local_time.tm_hour;
	int minutes = local_time.tm_min;
	int seconds = local_time.tm_sec;
	string time = to_string(hours) + ":" + to_string(minutes);
	return (time);

}
int current_time_minutes()
{
	time_t now = time(nullptr);
	struct tm local_time;
	localtime_s(&local_time, &now);
	int hours = local_time.tm_hour;
	int minutes = local_time.tm_min;
	int seconds = local_time.tm_sec;
//	cout << "Current time is: " << hours << ":" << minutes << ":" << seconds << endl;
	return minutes;
}
bool compare_dates(const string& date_str1, const string& date_str2) {
	string date_format = "%d-%m-%Y";  // Specify the format of your date strings

	tm date1 = {};
	istringstream date_stream1(date_str1);
	date_stream1 >> get_time(&date1, date_format.c_str());

	tm date2 = {};
	istringstream date_stream2(date_str2);
	date_stream2 >> get_time(&date2, date_format.c_str());

	if (mktime(&date1) > mktime(&date2)) {
		return true;
	}
	else if (mktime(&date1) <= mktime(&date2)) {
		return false;
	}
	
}
int current_time_seconds()
{
	time_t now = time(nullptr);
	struct tm local_time;
	localtime_s(&local_time, &now);
	int hours = local_time.tm_hour;
	int minutes = local_time.tm_min;
	int seconds = local_time.tm_sec;
//	cout << "Current time is: " << hours << ":" << minutes << ":" << seconds << endl;
	return seconds;
}
string getNextDate() {
	time_t now = time(0);
	struct tm next_tm;
	localtime_s(&next_tm, &now);

	next_tm.tm_mday++; // increment day

	mktime(&next_tm); // normalize

	char buffer[80];
	strftime(buffer, 80, "%d-%m-%Y", &next_tm);

	return buffer;
}

bool compare_times(const string& time1, const string& time2) {
	istringstream ss1(time1), ss2(time2);
	int hours1, minutes1, hours2, minutes2;
	char colon;

	ss1 >> hours1 >> colon >> minutes1;
	ss2 >> hours2 >> colon >> minutes2;

	int total_minutes1 = hours1 * 60 + minutes1;
	int total_minutes2 = hours2 * 60 + minutes2;

	return total_minutes1 > total_minutes2;
}
bool flight_status(string y4, int s, int y, bool z)
{
	
	string current_time = current_time_hours_min();
	


	bool q = false;

	if (compare_times(y4, current_time)==true)
	{
		q=true;
	}

	if (q == true && ((s + y > 0 && s + y <= 30 && z == 0) || (s + y > 0 && s + y <= 60 && z == 1)))
	{
		return true;
	}
	else return false;

}
class Airport {
private:
	string city;
public:
	Airport(string City)
		: city(City)
	{}
	Airport(const Airport& other) {
		city = other.city;
	}
	Airport& operator=(const Airport& other)
	{
		city = other.city;
		return *this;
	}
	string getCity() const { return city; }
	void setCity(string c)  {  city=c; }

};

class Airplane {
private:
	string ID;
	int Capacity;
	int economySeats;
	int businessSeats;
public:
	Airplane(string id="",int e_seats=50,int b_seats=10, int capacity = 60)
		
	{
		ID = id;
		Capacity = capacity;
		economySeats = e_seats;
		businessSeats = b_seats;
	}
	Airplane(const Airplane& other) {
		ID = other.ID;
		Capacity = other.Capacity;
		economySeats = other.economySeats;
		businessSeats = other.businessSeats;
	}
	Airplane& operator=(const Airplane& other)
	{
		ID = other.ID;
		Capacity = other.Capacity;
		economySeats = other.economySeats;
		businessSeats = other.businessSeats;
		return *this;
	}
	string get_Plane_ID() const { 
		return ID; 
	}
	int getCapacity() const { 
		return Capacity; 
	}
	int getAvailableEconomySeats() {
		return economySeats;
	}

	int getAvailableBusinessSeats() {
		return businessSeats;
	}
	void setCapacity(int capacity) {
		Capacity = capacity;
	}

	void setAvailableEconomySeats(int economySeats) {
		this->economySeats = economySeats;
	}

	void setAvailableBusinessSeats(int businessSeats) {
		this->businessSeats = businessSeats;
	}


};


class CostManager {
public:
	
	static float calculateTicketPrice(bool isInternational, int travelTimeHours, int travelTimeMinutes) {
		const float localTicketPricePerHour = 10000.0;
		const float internationalTicketPricePerHour = 20000.0;

		float travelTimeInHours = travelTimeHours + (static_cast<float>(travelTimeMinutes) / 60.0);

		float ticketPrice = 0.0;
		if (isInternational) {
			ticketPrice = internationalTicketPricePerHour * travelTimeInHours;
		}
		else {
			ticketPrice = localTicketPricePerHour * travelTimeInHours;
		}

		return ticketPrice;
	}

	static float calculateTax(bool isInternational) {
		const float localTaxPercentage = 0.05;
		const float internationalTaxPercentage = 0.1;

		float taxPercentage = 0.0;
		if (isInternational) {
			taxPercentage = internationalTaxPercentage;
		}
		else {
			taxPercentage = localTaxPercentage;
		}

		return taxPercentage;
	}
};

int flight_num(string filename)
{
	ifstream i_file(filename);

	int count = 0;
	if (!i_file) {
		cout << "Error opening the file." << filename<< endl;
		return count;
	}
	else {
		string y1, y2, y3, y4, y5, y6;
		int x1, x2, x3, x4;
		bool z1;
		while (!(i_file.eof()))
		{

			i_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;
			count++;

		}
	//	cout << count;
	//	cout << filename;
		return count;
		i_file.close();
	}
}


const int passenger_size()
{
	ifstream i_file("passenger_Log_In.txt");
	int count = 0;
	if (!i_file) {
		cout << "Error opening the file." << endl;
		return count;
	}
	else {
		string u, p, p_num;
		bool x1, x2;
		while (!(i_file.eof()))
		{

			i_file >> u >> p_num >> x1 >> x2 >> p;
			count++;

		}
		////cout << "1";
		i_file.close();

		return count;

	}
}

class Flight:public  CostManager {
private:
    string flightID;
    Airport* originAirport; // Aggregation by reference
    Airport* destinationAirport; // Aggregation by reference
    string departureTime;
    string arrivalTime;
    string timeTaken;
	int t_h;
	int t_m;
    bool isCovid;
	bool available;
    Airplane airplane; // Composition
    passenger* Passenger; //
    int numPassengers;
	bool route;
	
public:
	// Default Constructor
	Flight() {
		flightID = "";
		originAirport = nullptr;
		destinationAirport = nullptr;
		departureTime = "";
		arrivalTime = "";
		timeTaken = "";
		isCovid = false;
		Passenger = nullptr;
		numPassengers = 0;
		available = false;

	}
    Flight(string id, Airport* origin, Airport* destination, string departure,
           string arrival, Airplane airplane, int time_hrs , int time_min , bool covid, bool route=0, bool a=false)
        : flightID(id), originAirport(origin), destinationAirport(destination),
          departureTime(departure), arrivalTime(arrival),t_h(time_hrs),t_m(time_min), timeTaken(to_string(time_hrs) + " hour " + to_string(time_min) + " min"),
          isCovid(covid), airplane(airplane), numPassengers(0),available(a)
    {
       
    }
	Flight(const Flight& other) {
		t_h = other.t_h;
		t_m = other.t_m;
		flightID = other.flightID;
		originAirport = new Airport(*other.originAirport);
		destinationAirport = new Airport(*other.destinationAirport);
		departureTime = other.departureTime;
		arrivalTime = other.arrivalTime;
		timeTaken = other.timeTaken;
		isCovid = other.isCovid;
		airplane = other.airplane;
		numPassengers = other.numPassengers;
		t_h = other.t_h;
		t_m = other.t_m;
		available = other.available;
	
		
	}
	Flight& operator=(const Flight& other)
	{
		t_h = other.t_h;
		t_m = other.t_m;

		flightID = other.flightID;
		originAirport = new Airport(*other.originAirport);
		destinationAirport = new Airport(*other.destinationAirport);
		departureTime = other.departureTime;
		arrivalTime = other.arrivalTime;
		timeTaken = other.timeTaken;
		isCovid = other.isCovid;
		airplane = other.airplane;
		numPassengers = other.numPassengers;
		available = other.available;
		
		return *this;
	}
   
	// Getters
	string getFlightID() {
		return flightID;
	}

	string getOriginCity() {
		
		return originAirport->getCity();
	}
	
	string getDestinationCity() {
		return destinationAirport->getCity();
	}

	string getDepartureTime() {
		return departureTime;
	}

	string getArrivalTime() {
		return arrivalTime;
	}

	string getAirplaneID() {
		return airplane.get_Plane_ID();
	}

	int getAvailableEconomySeats() {
		return airplane.getAvailableEconomySeats();
	}

	int getAvailableBusinessSeats() {
		return airplane.getAvailableBusinessSeats();
	}
	bool set_Available() {
		return available;
	}
	string get_estimated_time()
	{
		return timeTaken;
	}
	int get_t_h()
	{
		return t_h;
	}
	int get_t_m()
	{
		return t_m;
	}
	bool get_covid() {
		return isCovid;
	}
	// Setters
	void set_estimated_time(int time_hrs , int time_min )
	{
		timeTaken = to_string(time_hrs) + " hour " + to_string(time_min) + " min";
		
	}
	void set_covid_status(bool x)
	{
		isCovid = x;
	}
	void setFlightID(string id) {
		flightID = id;
	}

	void setDepartureTime(string departure) {
		departureTime = departure;
	}

	void setArrivalTime(string arrival) {
		arrivalTime = arrival;
	}

	

	void set_Capacity(int capacity=60) {
		airplane.setCapacity( capacity) ;
	}

	void set_Available_Economy_Seats(int economySeats) {
		if(economySeats>0)
		airplane.setAvailableEconomySeats(  economySeats);
		else airplane.setAvailableEconomySeats(0);
	}

	void set_Available_Business_Seats(int businessSeats) {
		if(businessSeats>0)
		airplane.setAvailableBusinessSeats(businessSeats)  ;
		else airplane.setAvailableBusinessSeats(0);
	}

	bool covid_status()
	{
		return isCovid;
	}
	
	
	// Member Functions
	bool bookSeat(char classType,bool route_,int ax, string filename,int xa) {
		bool ds = false;
		int num_flights = flight_num(filename);
		ifstream i1_file(filename);
		Flight* flights = new Flight[num_flights];
		int f = 0;
		if (!i1_file) {
			cout << "Error opening the file." << endl;
			return false;
		}
		else
		{
			string y1, y2, y3, y4, y5, y6;
			int x1, x2, x3, x4;
			bool z1;

			for (int i = 0; i < num_flights; i++)
			{


				i1_file >> y1 >> y2 >> y3 >> y4 >> y5 >> y6 >> x1 >> x2 >> x3 >> x4 >> z1;

				Airport Dep(y2);
				Airport Des(y3);
				Airplane Plane(y6, x1, x2, x1 + x2);

				Flight x = Flight(y1, &Dep, &Des, y4, y5, Plane, x3, x4, z1);
				flights[i] = x;													//copy constructor used

			}
			i1_file.close();
		int size = passenger_size();
		//cout << size;
		Passenger = nullptr;
		Passenger = new passenger[size];
		ifstream i_file(Passenger[0].get_filename());
		if (!i_file) {
			cout << "Error opening the file." << endl;
			return false;
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








		if (classType == 'E') {
			
			
			if (flights[xa].getAvailableEconomySeats() > 0 ) {
				flights[xa].set_Available_Economy_Seats(flights[xa].getAvailableEconomySeats() -1);
				//cout << "1";

				ofstream ofile("booking_details.txt",ios::app);
				if (!ofile)
				{
					
					return false;
				}
				else
				{
					//cout << Passenger[ax].get_username() << ' ' << getOriginCity() << ' ' << getDestinationCity() << ' ' << calculateTicketPrice(route_, t_h, t_m) << endl;
					
					ofile << Passenger[ax].get_username() << ' ' << getOriginCity() << ' ' << getDestinationCity() << ' ' << calculateTicketPrice(route_, t_h, t_m) << endl;

				}
				
				ofile.close();
				ds = true;
			}
			else {
				ds = false;
			}
		}
		else if (classType == 'B') {
			if (flights[xa].getAvailableBusinessSeats() > 0) {
				flights[xa].set_Available_Business_Seats(flights[xa].getAvailableBusinessSeats()-1);
				

				ofstream o_file("booking_details.txt", ios::app);
				if (!o_file)
				{
					//system("pause");
					return false; 
				}
				else
				{
					o_file << Passenger[ax].get_username() << ' ' << getOriginCity() << ' ' << getDestinationCity() << ' ' << calculateTicketPrice(route_, t_h, t_m) << endl;
				}
				o_file.close();
				ds = true;
			}
			else {
				ds = false;
			}
		}
		else {
			ds = false;
		}

		
		}


		ofstream o1file(filename);
		//int num_flights = flight_num(filename);
		if (!o1file) {
			cout << "Error opening the file." << endl;
			return false;
		}
		else
		{
			
			for (int i = 0; i < num_flights; i++)
			{
				o1file << flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;
				
			}
			o1file.close();
		}
		if (ds == true)
		{

			ofstream o_file(filename);

			if (!o_file) {
				cout << "Error opening the file." << endl;
				return false;
			}
			else
			{


				for (int i = 0; i < num_flights; i++)
				{

					o_file << flights[i].getFlightID() << ' ' << flights[i].getOriginCity() << ' ' << flights[i].getDestinationCity() << ' ' << flights[i].getDepartureTime() << ' ' << flights[i].getArrivalTime() << ' ' << flights[i].getAirplaneID() << ' ' << flights[i].getAvailableEconomySeats() << ' ' << flights[i].get_t_h() << ' ' << flights[i].get_t_m() << ' ' << flights[i].get_covid() << endl;
				}
				o_file.close();
			}
		}

		return ds;
	}
	

	void printDetails() {
		cout << "Flight ID: " << flightID << endl;
		cout << "Origin City(Airport): " << getOriginCity() << endl;
		cout << "Destination City(Airport): " << getDestinationCity() << endl;
		cout << "Departure date: " << getCurrentDate()<<endl;
		cout << "Departure Time: " << departureTime << endl;
		cout << "Arrival Time: " << arrivalTime << endl;
		cout << "Airplane ID: " << airplane.get_Plane_ID() << endl;
		cout << "Available Economy Seats: " << getAvailableEconomySeats() << endl;
		cout << "Available Business Seats: " << getAvailableBusinessSeats() << endl;
		cout << "Estimated Journey time: " << timeTaken <<endl;
	}
	void printDetails_cost() {
		cout << "Flight ID: " << flightID << endl;
		cout << "Origin City(Airport): " << getOriginCity() << endl;
		cout << "Destination City(Airport): " << getDestinationCity() << endl;
		cout << "Departure date: " << getCurrentDate()<<endl;
		cout << "Departure Time: " << departureTime << endl;
		cout << "Arrival Time: " << arrivalTime << endl;
		cout << "Airplane ID: " << airplane.get_Plane_ID() << endl;
		cout << "Available Economy Seats: " << getAvailableEconomySeats() << endl;
		cout << "Available Business Seats: " << getAvailableBusinessSeats() << endl;
		cout << "Estimated Journey time: " << timeTaken << endl;

		cout << "Ticket price: " << calculateTicketPrice(route, t_h, t_m) << endl;
		cout << "Government tax: " << calculateTicketPrice(route, t_h, t_m)*calculateTax(route)<<endl;


	}
};



string addHoursToTime(const string& timeStr, int hoursToAdd) {
	time_t currentTime = time(nullptr);
	tm timeInfo = {};
	localtime_s(&timeInfo, &currentTime);

	istringstream timeStream(timeStr);
	char delimiter;
	int hours, minutes;
	timeStream >> hours >> delimiter >> minutes;

	timeInfo.tm_hour = (timeInfo.tm_hour + hours + hoursToAdd) % 24;
	timeInfo.tm_min = minutes;

	ostringstream updatedTimeStream;
	updatedTimeStream << put_time(&timeInfo, "%H:%M");
	return updatedTimeStream.str();
}

bool validate_passport(string passport_num) {
	// Check that passport number is 8 characters long and contains only digits
	if (passport_num.length() != 8) {
		return false;
	}
	for (int i = 0; i < 8; i++) {
		if (!isdigit(passport_num[i])) {
			return false;
		}
	}
	return true;
}



void input_signup(string username, string password, string filename)
{

}
void input(string username, string password, string filename)
{
	ofstream admin_file(filename, ios::app);
	if (!admin_file) {
		cout << "Error opening the file." << endl;
		return;
	}
	// Append data to the file

	admin_file << ' ' << username << ' ' << password << endl;
	admin_file.close();
}


void output(string username, string password, string filename)
{

}
bool validate_password(string p)
{
	bool upper = false;
	bool lower = false;
	bool integer = false;
	bool special = false;
	for (int i = 0; i < p.length(); i++)
	{
		if (p[i] >= 'A' && p[i] <= 'Z')
		{
			upper = true;
		}
		if (p[i] >= 'a' && p[i] <= 'z')
		{
			lower = true;
		}
		if (p[i] >= '0' && p[i] <= '9')
		{
			integer = true;
		}
		if (!(p[i] >= 'A' && p[i] <= 'Z') && !(p[i] >= 'a' && p[i] <= 'z') && !(p[i] >= '0' && p[i] <= '9') && p[i] != 32)
		{
			special = true;
		}

	}

	if (p.length() >= 8 && upper == true && lower == true && integer == true && special == true)
	{
		return true;

	}
	else return false;
}


bool validate_username_p(string p)
{
	bool integer = false;
	for (int i = 0; i < p.length(); i++)
	{
		if (p[i] >= '0' && p[i] <= '9')
		{
			integer = true;
		}
		else
		{
			integer = false;
			break;
		}

	}
	if (p.length() == 13 && integer == true)
	{
		return true;

	}
	else return false;
}

