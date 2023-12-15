#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <regex>
using namespace std;

const int MAX_GUESTS = 100;

int temp = 1;

bool isValidDate(const std::string &date)
{
    // Define a regular expression pattern for DDMMYYYY format
    std::regex datePattern("^(0[1-9]|[12][0-9]|3[01])(0[1-9]|1[0-2])\\d{4}$");

    // Check if the date matches the pattern
    return std::regex_match(date, datePattern);
}

struct Guest
{
    string name;
    string age;
    string mobileNumber;
    string entryDate;
    string exitDate;
    int roomNumber;
    bool checkedIn;
    bool checkedOut;
};

class HotelReservation
{
private:
    Guest guests[MAX_GUESTS];
    int numGuests;
    int totalRooms;
    vector<int> availableRooms;

public:
    HotelReservation(int totalRooms) : numGuests(0), totalRooms(totalRooms)
    {
        for (int i = totalRooms; i > 0; --i)
        {
            availableRooms.push_back(i);
        }
    }

    // check date function
    bool isValidDate(const string &date)
    {
        // Check if the date has the correct length
        if (date.size() != 8)
        {
            return false;
        }

        // Extract day, month, and year from the date string
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(2, 2));
        int year = stoi(date.substr(4, 4));

        // Check if month is valid (1 to 12)
        if (month < 1 || month > 12)
        {
            return false;
        }

        // Check if day is valid for the given month
        if (day < 1 || day > 31)
        {
            return false;
        }

        // Additional checks for specific months with fewer days
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
            return false;
        }

        // Check for February
        if (month == 2)
        {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            {
                // Leap year
                if (day > 29)
                {
                    return false;
                }
            }
            else
            {
                // Non-leap year
                if (day > 28)
                {
                    return false;
                }
            }
        }

        // If all checks pass, the date is valid
        return true;
    }

    int addGuest()
    {
        if (numGuests < MAX_GUESTS)
        {
            if (availableRooms.empty())
            {
                cout << "No available rooms. Cannot add more guests." << endl;
                return 0;
            }

            cout << "Enter guest name: ";
            getline(cin >> ws, guests[numGuests].name);
            int i = 0;
            while (i < guests[numGuests].name.size())
            {
                if ((guests[numGuests].name[i] >= 'a' && guests[numGuests].name[i] <= 'z') || (guests[numGuests].name[i] <= 'Z' && guests[numGuests].name[i] >= 'A') || guests[numGuests].name[i] == ' ')
                {
                    i++;
                }
                else
                {
                    cout << "Error occured , Invalid Name\n";
                    addGuest();
                    break;
                }
            }
            if (i == guests[numGuests].name.size())
            {
                cout << "Enter guest age: ";
                cin >> guests[numGuests].age;
                i = 0;
                while (i != guests[numGuests].age.size())
                {
                    if (guests[numGuests].age[i] >= '0' && guests[numGuests].age[i] <= '9')
                    {
                        i++;
                    }
                    else
                    {
                        cout << "Invalid Age...Enter again...\n";
                        i = 0;
                        cout << "Enter guest age: ";
                        cin >> guests[numGuests].age;
                    }
                }
                int i = 0;
                while (i != 10)
                {
                    cout << "Enter guest mobile number: ";
                    cin >> guests[numGuests].mobileNumber;
                    while (i < guests[numGuests].mobileNumber.size())
                    {
                        if (guests[numGuests].mobileNumber[i] >= '0' && guests[numGuests].mobileNumber[i] <= '9')
                            i++;
                        else
                            break;
                    }
                    if (i != 10)
                        cout << "Invalid Mobile Number....Enter again...\n";
                }
                i = 0;
                /* while (i != 8)
                 {*/
            reEnterDate:
                cout << "Enter guest entry date in format DDMMYYYY: \n";
                cin >> guests[numGuests].entryDate;

                if (guests[numGuests].entryDate.size() != 8)
                {
                    cout << "Invalid Date....Enter again...\n";
                    goto reEnterDate;
                }

                // Check if the entered entry date is valid
                if (!isValidDate(guests[numGuests].entryDate))
                {
                    cout << "Invalid entry date. Please enter a valid date." << endl;
                    goto reEnterDate;
                }

                // }
                i = 0;

            reEnterExitDate:
                cout << "Enter guest exit date in format DDMMYYYY: ";
                cin >> guests[numGuests].exitDate;

                if (guests[numGuests].exitDate.size() != 8)
                {

                    cout << "Invalid Date....Enter again...\n";
                    goto reEnterExitDate;
                }

                // Check if the entered entry date is valid
                if (!isValidDate(guests[numGuests].exitDate))
                {
                    cout << "Invalid entry date. Please enter a valid date." << endl;
                    goto reEnterExitDate;
                }

                if (stoi(guests[numGuests].exitDate) < stoi(guests[numGuests].entryDate))
                {
                    cout << endl
                         << "Please check date! There might be some issue..." << endl
                         << endl;
                    goto reEnterExitDate;
                }

                //}
                guests[numGuests].checkedIn = true;
                guests[numGuests].checkedOut = false;

                // Assign a room to the guest
                guests[numGuests].roomNumber = availableRooms.back();
                availableRooms.pop_back();

                cout << "Guest " << guests[numGuests].name << " has been added to the reservation and checked in." << endl;
                cout << "Room number: " << guests[numGuests].roomNumber << endl;

                numGuests++;
            }
            else
            {
                cout << "Maximum number of guests reached." << endl;
            }
        }
    }

    void displayGuests()
    {
        if (numGuests == 0)
        {
            cout << "No guests in the reservation." << endl;
        }
        else
        {
            cout << setw(20) << left << "Name"
                 << setw(5) << left << "Age"
                 << setw(15) << left << "Mobile Number"
                 << setw(12) << left << "Entry Date"
                 << setw(12) << left << "Exit Date"
                 << setw(10) << left << "Check-In"
                 << setw(10) << left << "Check-Out"
                 << setw(10) << left << "Room No." << endl;

            for (int i = 0; i < numGuests; i++)
            {
                cout << setw(20) << left << guests[i].name
                     << setw(5) << left << guests[i].age
                     << setw(15) << left << guests[i].mobileNumber
                     << setw(12) << left << guests[i].entryDate
                     << setw(12) << left << guests[i].exitDate
                     << setw(10) << left << (guests[i].checkedIn ? "Yes" : "No")
                     << setw(10) << left << (guests[i].checkedOut ? "Yes" : "No")
                     << setw(10) << left << guests[i].roomNumber << endl;
            }
        }
    }

    void checkOut()
    {
        string guestName;
        cout << "Enter guest name for check-out: ";
        getline(cin >> ws, guestName);

        for (int i = 0; i < numGuests; i++)
        {
            if (guests[i].name == guestName)
            {
                if (guests[i].checkedOut)
                {
                    cout << "Guest " << guestName << " is already checked out." << endl;
                }
                else
                {
                    guests[i].checkedOut = true;
                    // Mark the room as available again
                    availableRooms.push_back(guests[i].roomNumber);
                    cout << "Guest " << guestName << " has been checked out." << endl;
                }
                return;
            }
        }

        cout << "Guest " << guestName << " not found." << endl;
    }

    void displayAvailableRooms()
    {
        cout << "Available Rooms: ";
        if (availableRooms.empty())
        {
            cout << "No available rooms." << endl;
        }
        else
        {
            for (int room : availableRooms)
            {
                cout << room << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int totalRooms;
    cout << "Enter the total number of rooms in the hotel: ";
    cin >> totalRooms;

    HotelReservation hotel(totalRooms);

    while (true)
    {
        cout << "\nHotel Management System" << endl;
        cout << "1. Add Guest" << endl;
        cout << "2. Display Guests" << endl;
        cout << "3. Check Out" << endl;
        cout << "4. Display Available Rooms" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice (1/2/3/4/5): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            hotel.addGuest();
            break;

        case 2:
            hotel.displayGuests();
            break;

        case 3:
            hotel.checkOut();
            break;

        case 4:
            hotel.displayAvailableRooms();
            break;

        case 5:
            cout << "Exiting the program. Thank you!" << endl;
            return 0;

        default:
            cout << "Invalid choice. Please enter 1, 2, 3, 4, or 5." << endl;
        }
    }

    return 0;
}