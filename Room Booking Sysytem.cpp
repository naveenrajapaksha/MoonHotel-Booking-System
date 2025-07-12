#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Define structs to represent Room and Booking
struct Room {
    string id;
    string type;
    float price; // Added price of the room
    bool isAvailable;
};

struct Booking {
    string guestName;
    string roomId;
    float totalAmount;
    int duration;
};

// Function prototypes
void showOptions();
void displayRooms(const vector<Room>& rooms);
void bookRoom(vector<Room>& rooms, vector<Booking>& bookings);
void displayBookings(const vector<Booking>& bookings);
bool login();
void saveData(const vector<Room>& rooms, const vector<Booking>& bookings);
void loadData(vector<Room>& rooms, vector<Booking>& bookings);

int main() {
    // Check login credentials
    if (!login()) {
        cout << "Login failed. Exiting program." << endl;
        return 1;  // Return error code 1 for login failure
    }

    // Initialize rooms and bookings
    vector<Room> rooms;
    Room room1 = {"101", "Single Room",   2000.0, true};
    Room room2 = {"102", "Double Room",   3500.0, true};
    Room room3 = {"103", "Twin Room",     2300.0, true};
    Room room4 = {"104", "Family Room",   4000.0, true};
    Room room5 = {"105", "Standard Room", 3200.0, true};
    Room room6 = {"106", "Deluxe Room",   5800.0, true};
    Room room7 = {"107", "AC Room",       10000.0, true};
    Room room8 = {"108", "NON-AC Room",   8000.0, true};
    // Add more rooms as needed
    rooms.push_back(room1);
    rooms.push_back(room2);
    rooms.push_back(room3);
    rooms.push_back(room4);
    rooms.push_back(room5);
    rooms.push_back(room6);
    rooms.push_back(room7);
    rooms.push_back(room8);
    vector<Booking> bookings;

    // Load existing data from file
    loadData(rooms, bookings);

    bool exitProgram = false;
    int choice;

    while (!exitProgram) {
        showOptions();
        cin >> choice;

        switch (choice) {
            case 1:
                displayRooms(rooms);
                break;
            case 2:
                bookRoom(rooms, bookings);
                break;
            case 3:
                displayBookings(bookings);
                break;
            case 4:
                exitProgram = true;
                cout << "Exiting program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    // Save data before exiting
    saveData(rooms, bookings);

    return 0;
}

void showOptions() {
    cout << "===== Moon Hotel Management System =====" << endl;
    cout << "1. Display Available Rooms" << endl;
    cout << "2. Book a Room" << endl;
    cout << "3. Display Bookings" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayRooms(const vector<Room>& rooms) {
    cout << "===== Available Rooms =====" << endl;
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].isAvailable) {
            cout << "Room ID: " << rooms[i].id << " | Type: " << rooms[i].type << " | Price: Rs " << rooms[i].price << endl;
        }
    }
}

void bookRoom(vector<Room>& rooms, vector<Booking>& bookings) {
    string guestName;
    int duration, numRooms;

    cout << "Enter guest name: ";
    cin >> guestName;

    cout << "Enter the number of nights of stay: ";
    cin >> duration;

    cout << "Enter the number of rooms to book: ";
    cin >> numRooms;

    // Display available rooms
    displayRooms(rooms);

    // Book multiple rooms
    for (int i = 0; i < numRooms; ++i) {
        cout << "Enter room ID to book (Room " << i + 1 << "): ";
        string roomId;
        cin >> roomId;

        // Check if the room is available
        bool roomFound = false;
        for (size_t j = 0; j < rooms.size(); ++j) {
            if (rooms[j].id == roomId && rooms[j].isAvailable) {
                roomFound = true;
                rooms[j].isAvailable = false;  // Book the room
                float totalAmount = rooms[j].price * duration;  // Calculate total amount for the booking
                bookings.push_back(Booking{guestName, roomId, totalAmount, duration});
                cout << "Room " << roomId << " booked successfully! Total Amount: Rs " << totalAmount << endl;
                break;
            }
        }

        if (!roomFound) {
            cout << "Room " << roomId << " not available or invalid room ID." << endl;
        }
    }
}

void displayBookings(const vector<Booking>& bookings) {
    cout << "===== Booked Rooms =====" << endl;
    for (size_t i = 0; i < bookings.size(); ++i) {
        cout << "Guest Name: " << bookings[i].guestName << " | Room ID: " << bookings[i].roomId
             << " | Total Amount: Rs " << bookings[i].totalAmount << " | Duration: " << bookings[i].duration << " nights" << endl;
    }
}

bool login() {
    string username, password;
    cout << "===== Welcome to Moon Hotel Management System =====" << endl;
    cout << "             ===== System Login =====" << endl;
    cout << "===== Enter username: ";
    cin >> username;
    cout << "===== Enter password: ";
    cin >> password;

    // Check username and password
    if (username == "naveen" && password == "naveen") {
        cout << "LOGIN SUCCESSFULL!!" << endl;
        return true;
    } else {
        cout << "Invalid username or password. Login failed." << endl;
        return false;
    }
}

void saveData(const vector<Room>& rooms, const vector<Booking>& bookings) {
    ofstream outFile("hotel_data.txt");

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // Save rooms data
    for (size_t i = 0; i < rooms.size(); ++i) {
        outFile << "Room," << rooms[i].id << ',' << rooms[i].type << ',' << rooms[i].price << ',' << rooms[i].isAvailable << '\n';
    }

    // Save bookings data
    for (size_t i = 0; i < bookings.size(); ++i) {
        outFile << "Booking," << bookings[i].guestName << ',' << bookings[i].roomId << ',' << bookings[i].totalAmount << ',' << bookings[i].duration << '\n';
    }

    cout << "Data saved successfully!" << endl;
    outFile.close();
}

void loadData(vector<Room>& rooms, vector<Booking>& bookings) {
    ifstream inFile("hotel_data.txt");

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        if (getline(ss, token, ',')) {
            if (token == "Room") {
                Room room;
                getline(ss, room.id, ',');
                getline(ss, room.type, ',');
                ss >> room.price;
                ss.ignore(); // Skip the comma
                ss >> boolalpha >> room.isAvailable;
                rooms.push_back(room);
            } else if (token == "Booking") {
                Booking booking;
                getline(ss, booking.guestName, ',');
                getline(ss, booking.roomId, ',');
                ss >> booking.totalAmount;
                ss.ignore(); // Skip the comma
                ss >> booking.duration;
                bookings.push_back(booking);
            }
        }
    }

    cout << "Data loaded successfully!" << endl;
    inFile.close();
}

