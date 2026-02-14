#include <fstream>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
const int MAX = 100;
const int userSize = 100;

//Function Protptypes
int startMenu();

// ADMIN
void adminSignup();
bool adminSignIn();
void adminPortal();

// STUDENT
void studentSignup();
bool studentSignIn();
void studentPortal();
// USERS
void saveUsers();
void loadUsers();
string userRole[userSize];

// FEATURES
void campusmap();
void timetable();
void tips();
void FAQs();

// STUDENT MANAGEMENT
void addStudent(string name, string roll, string prog);
void searchStudent(const string &roll);
void updateStudent(const string &rollToUpdate);
void listStudents();
void saveStudents();
void loadStudents();

// COURSES MANAGEMENT
void addCourse(string &code, string &title, string &instructor);
void updateCourse(const string &codeToUpdate);
void listCourses();
void searchCourse(const string &codeToSearch);
void loadCourses();
void saveCourses();
string uN, uP;

// TEACHERS
const int MAX_TEACHERS = 50;
int teacherCount = 0;

string teacherName[MAX_TEACHERS];
string teacherID[MAX_TEACHERS];

// ASSIGNMENTS (mapping teacher to course)
string assignTeacher[MAX * 2]; 
string assignCourse[MAX * 2];
int assignmentCount = 0;

// EXTRAS DONE
void pause();
void clearScreen();
void setColor(int colorCode);

//Arrays
string stuName[MAX];
string stuRoll[MAX];
string stuProg[MAX];
string couCode[MAX];
string couTitle[MAX];
string couInstructor[MAX];
string userName[userSize];
string userPassword[userSize];
string userStatus[userSize];

// TEACHER MANAGEMENT
void addTeacher();
void assignCourseToTeacher();
void viewTeacherCourses();
void viewCourseTeachers();
void saveTeachers();
void loadTeachers();
void saveAssignments();
void loadAssignments();

string days[5] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY"};

string timetableA[5][4] = {
    {"PF", "ICT", "AP LAB", "------"},
    {"F.ENG", "AP PHY", "DS", "------"},
    {"------", "DS", "PF", "F.ENG"},
    {"ICT", "AP LAB", "------", "BASIC-M"},
    {"PF", "------", "------", "------"}};

string timetableB[5][4] = {
    {"DS", "PF", "ICT", "------"},
    {"F.ENG", "AP PHY", "------", "DS"},
    {"PF", "DS", "ICT", "F.ENG"},
    {"ICT", "AP LAB", "------", "BASIC-M"},
    {"PF", "------", "------", "------"}};

//COUNTERS
int stuCount = 0;
int couCount = 0;
int userCount = 0;
int main()
{
    system("cls");
    loadStudents();
    loadCourses();
    loadUsers();
    loadTeachers();
    loadAssignments();
    int choice;
    while (true)
    {
        choice = startMenu();
        if (choice == 1)
            adminSignup();
        else if (choice == 2)
        {
            if (adminSignIn())
            {                  
                adminPortal();
            }
        }

        else if (choice == 3)
            studentSignup();
        else if (choice == 4)
        {
            if (studentSignIn())
            {
                studentPortal();
            }
        }
        else if (choice == 5)
            break;
        else
            setColor(12);
        cout << "invalid choice\n";
    }
    return 0;
}

// START MENU
int startMenu()
{
    clearScreen();
    setColor(11);
    cout << R"(
  _____          __  __  _____   _    _   _____  
 / ____|   /\   |  \/  ||  __ \ | |  | | / ____| 
| |       /  \  | \  / || |__) || |  | || (___   
| |      / /\ \ | |\/| ||  ___/ | |  | | \___ \  
| |____ / ____ \| |  | || |     | |__| | ____) | 
 \_____/_/    \_\_|  |_||_|      \____/ |_____/  
    )";
	cout << endl;
    setColor(11);
    cout << " ===========================================================================" << endl;
    setColor(13);
    cout << "                   NAVIGATION & MANAGEMENT SYSTEM     " << endl;
    setColor(11);
    cout << " ===========================================================================" << endl;
    setColor(7);
    int choice;
    cout << " Select one of the following options to proceed:" << endl;
    setColor(11);
    cout << "| MAIN MENU |\n";
    setColor(7);
    setColor(14);
    cout << "1. ";
    setColor(7);
    cout << "ADMIN Sign UP\n";
    setColor(14);
    cout << "2. ";
    setColor(7);
    cout << "ADMIN Sign IN\n";
    setColor(14);
    cout << "3. ";
    setColor(7);
    cout << "STUDENT Sign UP\n";
    setColor(14);
    cout << "4. ";
    setColor(7);
    cout << "STUDENT Sign In\n";
    setColor(14);
    cout << "5. ";
    setColor(7);
    cout << "EXIT\n";
    setColor(8);
    cout << " Select one: ";
    cin >> choice;
    return choice;
}

void adminSignup()
{
    clearScreen();
    setColor(5);
    cout << "=========================================================================" << endl;
    setColor(11);
    cout << R"(
  ___  ____  __  __ _____ _   _    _____ _____ _____  _   _ _   _ _____  
 / _ \|  _ \   \/  |_   _| \ | |  /  ___|_   _|  __ \| \ | | | | | ___ \
/ /_\ \ | | | .  . | | | |  \| |  \ `--.  | | | |  \/|  \| | | | | |_/ /
|  _  | | | | |\/| | | | | . ` |   `--. \ | | | | __ | . ` | | | |  __/
| | | | |/ /| |  | |_| |_| |\  |  /\__/ /_| |_| |_\ \| |\  | |_| | |    
\_| |_/___/ \_|  |_/\___/\_| \_/  \____/ \___/ \____/\_| \_/\___/\_|                                                                                                                  )";
    cout << endl;
    setColor(5);
    cout << "==========================================================================" << endl;
    setColor(7);

    if (userCount >= userSize)
    {
        setColor(12);
        cout << "User limit reached\n";
        pause();
        return;
    }

    string uN, uP;

    cout << "Enter username: ";
    cin >> uN;

    // DUPLICATE CHECK
    for (int i = 0; i < userCount; i++)
    {
        if (userName[i] == uN)
        {
            setColor(12);
            cout << "Username already exists\n";
            pause();
            return;
        }
    }

    cout << "Enter password: ";
    cin >> uP;

 
    userName[userCount]     = uN;
    userPassword[userCount] = uP;
    userRole[userCount]     = "ADMIN";
    userCount++;

    saveUsers();
    setColor(10);
    cout << "Admin registered successfully.\n";
    pause();
}

// ADMIN SIGNIN
bool adminSignIn()
{
    clearScreen();
    setColor(5);
    cout << "========================================================================" << endl;

    setColor(11);
    cout << R"(
  ___  ____ ___  __ _____ _   _    _____ _____ _____  _   _ _____ _   _
 / _ \|  _  \  \/  |_   _| \ | |  /  ___|_   _|  __ \| \ | |_   _| \ | |
/ /_\ \ | | | .  . | | | |  \| |  \ `--.  | | | |  \/|  \| | | | |  \| |
|  _  | | | | |\/| | | | | . ` |   `--. \ | | | | __ | . ` | | | | . ` |
| | | | |/ /| |  | |_| |_| |\  |  /\__/ /_| |_| |_\ \| |\  |_| |_| |\  |
\_| |_/___/ \_|  |_/\___/\_| \_/  \____/ \___/ \____/\_| \_/\___/\_| \_/
                                                                       
                                                                         )";
    cout << endl;

    setColor(5);
    cout << "==========================================================================" << endl;

    setColor(7);
    string uN, uP;
    cout << "Enter username: ";
    cin >> uN;
    cout << "Enter password: ";
    cin >> uP;

    for (int i = 0; i < userCount; i++)
    {
        if (userName[i] == uN && userPassword[i] == uP)
        {
            if (userRole[i] != "ADMIN")
            {
                setColor(12);
                cout << "Access denied. Not an admin account.\n";
                pause();
                return false;
            }

            setColor(10);
            cout << "Admin login successful.\n";
            pause();
            return true;
        }
    }

    setColor(12);
    cout << "Invalid credentials.\n";
    pause();
    return false;
}

// ADMIN PORTAL

void adminPortal()
{
    while (true)
    {

        system("cls");
        setColor(5); // Purple
        cout << "====================================================================" << endl;

        setColor(11); // Cyan
        cout << R"(
  ___   ____   __  __  _____  _   _   _____  _____  _____  _____  ___   _
 / _ \ |  _ \ |  \/  ||_   _|| \ | | | ___ \|  _  || ___ \|_   _|/ _ \ | |    
/ /_\ \| | | || .  . |  | |  |  \| | | |_/ /| | | || |_/ /  | | / /_\ \| |    
|  _  || | | || |\/| |  | |  | . ` | |  __/ | | | ||    /   | | |  _  || |    
| | | || |/ / | |  | | _| |_ | |\  | | |    \ \_/ /| |\ \   | | | | | || |____
\_| |_/|___/  |_|  |_/ \___/ \_| \_/ \_|     \___/ \_| \_|  \_/ \_| |_/\_____/)";
        cout << endl;

        // Purple bottom border
        setColor(5); // Purple
        cout << "=====================================================================" << endl;
        setColor(14);
        cout << "1. ";
        setColor(7);
        cout << "Manage Students\n";
        setColor(14);
        cout << "2. ";
        setColor(7);
        cout << "Manage Courses\n";
        setColor(14);
        cout << "3. ";
        setColor(7);
        cout << "Manage Teachers\n";
        setColor(14);
        cout << "4. ";
        setColor(7);
        cout << "Back to Main Menu\n";
        cout << "SELECT ONE" << endl;
        int option;
        cin >> option;
        if (option == 1)
        {
            while (true)

            {
                system("cls");
                setColor(5);
                cout << "=======================================================================================" << endl;

                setColor(11);
                cout << R"(
 _____  _                _            _     _    _                                                   _
/  ___|| |              | |          | |   | \__/ |                                                 | |  
\ `--. | |__  _   _   __| | __ _ __  | |_  | .  . | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_
 `--. \|  __|| | | | / _` |/ _ \ '_ \| __| | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|
/\__/ /| |_  | |_| || (_| |  __/ | | | |_  | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_
\____/ \___| \__,__| \__,_|\___|_| |_|\__| \_|  |_/\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|
                                                                 _/ |                              
                                                                |___/                              
                                                                         )";
                cout << endl;
                setColor(5);
                cout << "========================================================================================" << endl;
                setColor(14);
                cout << "1. ";
                setColor(7);
                cout << "Add Student\n";
                setColor(14);
                cout << "2. ";
                setColor(7);
                cout << "Search Student\n";
                setColor(14);
                cout << "3. ";
                setColor(7);
                cout << "Update Student\n";
                setColor(14);
                cout << "4. ";
                setColor(7);
                cout << "listStudent\n";
                setColor(14);
                cout << "5. ";
                setColor(7);
                cout << "Back\n";

                cout << "Select one" << endl;
                int select;
                cin >> select;
                cin.ignore();
                if (select == 1)
                {
                    string name, roll, prog;
                    addStudent(name, roll, prog);
                }
                else if (select == 2)
                {
                    string roll;
                    cout << "Enter roll to search: ";
                    cin >> roll;
                    searchStudent(roll);
                }
                else if (select == 3)
                {
                    string roll;
                    cout << "Enter roll to update: ";
                    cin >> roll;
                    updateStudent(roll);
                }
                else if (select == 4)
                {
                    listStudents();
                }
                else if (select == 5)
                {
                    break;
                    return;
                }
                else
                {
                    setColor(12);
                    cout << "Invalid input";

                    getch();
                }
            }
           
        }

        else if (option == 2)
        {
            while (true)
            {
                system("cls");
                setColor(5);
                cout << "===============================================================================" << endl;
                setColor(11);
                cout << R"(
 _____                              __  __                                                       _  
/  __ \                            |  \/  |                                                     | |  
| /  \/ ___  _   _  _ __ ___  ___  | .  . | __ _ _ __   __ _  __ _  ___  _ __ ___    ___  _ __  | |_
| |    / _ \| | | || '__/ __|/ _ \ | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \| '_ ` _ \  / _ \| '_ \ | __|
| \__/\ (_) | |_| || |  \__ \  __/ | |  | | (_| | | | | (_| | (_| |  __/| | | | | ||  __/| | | || |_
 \____/\___/ \____||_|  |___/\___| \_|  |_/\__,_|_| |_|\__,_|\__, |\___||_| |_| |_| \___||_| |_|\___|
                                                             __/ |                              
                                                            |___/                     )";
                cout << endl;
                setColor(5);
                cout << "=================================================================================" << endl;
                setColor(7);
                setColor(14);
                cout << "1. ";
                setColor(7);
                cout << "Add Course\n";
                setColor(14);
                cout << "2. ";
                setColor(7);
                cout << "List Course\n";
                setColor(14);
                cout << "3. ";
                setColor(7);
                cout << "Update Course\n";
                setColor(14);
                cout << "4. ";
                setColor(7);
                cout << "Search Course\n";
                setColor(14);
                cout << "5. ";
                setColor(7);
                cout << "Back\n";

                cout << "Select one" << endl;
                int select;
                cin >> select;
                if (select == 1)
                {
                    string code, title, instructor;
                    addCourse(code, title, instructor);
                }
                else if (select == 2)
                {
                    listCourses();
                }
                else if (select == 3)
                {
                    string code;
                    cout << "Enter course code to update: ";
                    cin >> code;
                    updateCourse(code);
                }
                else if (select == 4)
                {
                    string code;
                    cout << "Enter course code to search: ";
                    cin >> code;
                    searchCourse(code);
                }
                else if (select == 5)
                {
                    break;
                }
                else
                {
                    setColor(12);
                    cout << "Invalid ";
                    getch();
                }
            }
        }

        else if (option == 3)
        {
            while (true)
            {
                system("cls");
                setColor(5);
                cout << "=======================================================================================" << endl;
                setColor(11);
                cout << R"(
 _____ _____  ___    _____  _   _  _____  _____          _____  _____  _____  _____   ___   _
|_   _|  ___|/ _ \  / ___ \| | | ||  ___|| ___ \ ,      | ___ \|  _  || ___ \|_   _| / _ \ | |    
  | | | |__ / /_\ \| /   \/| |_| || |__  | |_/ /  ___   | |_/ /| | | || |_/ /  | |  / /_\ \| |    
  | | |  __||  _  || |     |  _  ||  __| |    /  /   \  |  __/ | | | || |  /   | |  |  _  || |    
  | | | |___| | | || \___/\| | | || |___ | |\ \  `--..  | |    \ \_/ /| |\ \   | |  | | | || |____
  \_/ \____/\_| |_/ \_____/\_| |_/\____/ \_| \_| \___/  \_|     \___/ \_| \_|  \_/  \_| |_/\______|
                                                )";
                cout << endl;
                setColor(5);
                cout << "=======================================================================================" << endl;
                setColor(7);
                cout << "1. Add Teacher\n";
                cout << "2. Assign Course to Teacher\n";
                cout << "3. View Teacher Courses\n";
                cout << "4. View Course Teachers\n";
                cout << "5. Back\n";
                int select;
                cin >> select;
                if (select == 1)
                    addTeacher();
                else if (select == 2)
                    assignCourseToTeacher();
                else if (select == 3)
                    viewTeacherCourses();
                else if (select == 4)
                    viewCourseTeachers();
                else if (select == 5)
                    break;
                else
                {
                    cout << "Invalid input\n";
                    pause();
                }
            }
        }
        else if (option == 4)
        {
            break; // go back to main menu
        }
        else
        {
            setColor(12);
            cout << "Invalid choice";
            getch();
        }
    }
}
// STUDENT SIGNUP
void studentSignup()
{
    clearScreen();
    setColor(5);
    setColor(5);
    cout << "==================================================================================" << endl;

    setColor(11);
    cout << R"(
 _____ _____ _   _ _____ _____ _   _ _____   _____ _____ _____  _   _ _   _ _____
/  ___|_   _| | | |  _  \  ___| \ | |_   _| /  ___|_   _|  __ \| \ | | | | | ___ \
\ `--.  | | | | | | | | | |__ |  \| | | |   \ `--.  | | | |  \/|  \| | | | | |_/ /
 `--. \ | | | | | | | | |  __|| . ` | | |    `--. \ | | | | __ | . ` | | | |  __/
/\__/ / | | | |_| | |/ /| |___| |\  | | |   /\__/ /_| |_| |_\ \| |\  | |_| | |    
\____/  \_/  \___/|___/ \____/\_| \_/ \_/   \____/ \___/ \____/\_| \_/\___/\_|    )";
    cout << endl;

    setColor(5);
    cout << "====================================================================================" << endl;

    setColor(7);
    if (userCount >= userSize)
    {
        setColor(12);
        cout << "User limit reached\n";
        pause();
        return;
    }

    string uN, uP;
    cout << "Enter username: ";
    cin >> uN;

    // DUPLICATE CHECK
    for (int i = 0; i < userCount; i++)
    {
        if (userName[i] == uN)
        {
            setColor(12);
            cout << "Username already exists\n";
            pause();
            return;
        }
    }

    cout << "Enter password: ";
    cin >> uP;

    userName[userCount] = uN;
    userPassword[userCount] = uP;
    userRole[userCount] = "STUDENT";

    userCount++;
    saveUsers();
    setColor(10);
    cout << "Student registered successfully.\n";
    pause();
}

// STUDENT SIGNIN
bool studentSignIn()
{
    clearScreen();
    setColor(5);
    cout << "=====================================================================================" << endl;

    setColor(11);
    cout << R"(
 _____ _____ _   _ _____ _____ _   _ _____   _____ _____ _____  _   _ _____ _   _  
/  ___|_   _| | | |  _  \  ___| \ | |_   _| /  ___|_   _|  __ \| \ | |_   _| \ | |
\ `--.  | | | | | | | | | |__ |  \| | | |   \ `--.  | | | |  \/|  \| | | | |  \| |
 `--. \ | | | | | | | | |  __|| . ` | | |    `--. \ | | | | __ | . ` | | | | . ` |
/\__/ / | | | |_| | |/ /| |___| |\  | | |   /\__/ /_| |_| |_\ \| |\  |_| |_| |\  |
\____/  \_/  \___/|___/ \____/\_| \_/ \_/   \____/ \___/ \____/\_| \_/\___/\_| \_/                                                              
                                                                                  )";
    cout << endl;
    setColor(5);
    cout << "======================================================================================" << endl;
    string uN, uP;
    cout << "ENTER USERNAME: ";
    cin >> uN;
    cout << "ENTER PASSWORD: ";
    cin >> uP;

    for (int i = 0; i < userCount; i++)
    {
        if (userName[i] == uN && userPassword[i] == uP)
        {
            if (userRole[i] != "STUDENT")
            {
                setColor(12);
                cout << "Access denied. Not a student account.\n";
                pause();
                return false;
            }
            setColor(10);
            cout << "LOGIN SUCCESSFUL\n";
            pause();
            return true;
        }
    }

    setColor(12);
    cout << "INVALID CREDENTIALS\n";
    pause();
    return false;
}

// STUDENT PORTAL
void studentPortal()
{
    while (true)
    {
        clearScreen();
        setColor(13);
        setColor(5);
        cout << "======================================================================" << endl;

        setColor(11); // Cyan
        cout << R"(
 _____ _____ _   _ _____ _____ _   _ _____  ______ _____ _____ _____ ___   _    
/  ___|_   _| | | |  _  \  ___| \ | |_   _| | ___ \  _  | ___ \_   _/ _ \ | |    
\ `--.  | | | | | | | | | |__ |  \| | | |   | |_/ / | | | |_/ / | |/ /_\ \| |    
 `--. \ | | | | | | | | |  __|| . ` | | |   |  __/| | | |    /  | ||  _  || |    
/\\_/ / | | | |_| | |/ /| |___| |\  | | |   | |   \ \_/ / |\ \  | || | | || |____
\____/  \_/  \___/|___/ \____/\_| \_/ \_/   \_|    \___/\_| \_| \_/\_| |_/\_____/)";
        cout << endl;
        setColor(5);
        cout << "========================================================================" << endl;

        // Reset to default
        setColor(7);

        setColor(14);
        cout << "1. ";
        setColor(7);
        cout << "VIEW CAMPUS MAP\n";
        setColor(14);
        cout << "2. ";
        setColor(7);
        cout << "VIEW TIMETABLE\n";
        setColor(14);
        cout << "3. ";
        setColor(7);
        cout << "FAQs\n";
        setColor(14);
        cout << "4. ";
        setColor(7);
        cout << "VIEW COURSES\n";
        setColor(14);
        cout << "5. ";
        setColor(7);
        cout << "SEARCH COURSES\n";
        setColor(14);
        cout << "6. ";
        setColor(7);
        cout << "LOGOUT\n";

        int choice;
        cout << "Select one to proceed";
        cin >> choice;
        if (choice == 1)
            campusmap();
        else if (choice == 2)
            timetable();
        else if (choice == 3)
            FAQs();
        else if (choice == 4)
        {
            if (couCount == 0)
            {
                setColor(12);
                cout << "No courses available.\n";
            }
            else
            {
                for (int i = 0; i < couCount; i++)
                {
                    cout << couCode[i] << " | " << couTitle[i] << " | " << couInstructor[i] << endl;
                }
            }
            pause();
        }
        else if (choice == 5)
        {
            string code;
            cout << "Enter course code: ";
            cin >> code;
            bool found = false;
            for (int i = 0; i < couCount; i++)
            {
                if (couCode[i] == code)
                {
                    cout << couCode[i] << " | " << couTitle[i] << " | " << couInstructor[i] << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Course not found.\n";
            pause();
        }
        else if (choice == 6)
            break;
        else
        {
            setColor(12);
            cout << "Invalid option.\n";
            pause();
        }
    }
}

void timetable()
{
    system("cls");
    string section;
    cout << "Enter your section (A/B): ";
    cin >> section;

    string(*selectedTimetable)[4]; // pointer to selected 2D array

    if (section == "A")
        selectedTimetable = timetableA;
    else if (section == "B")
        selectedTimetable = timetableB;
    else
    {
        setColor(12);
        cout << "Invalid section.\n";
        pause();
        return;
    }
    setColor(5);
    cout << "======================================================" << endl;

    setColor(11);
    cout << R"(
 _____ _____ _    _  _____ _____ ___   _____ _      _____
|_   _|_   _|  \/  ||  ___|_   _/ _ \ | ___ \ |    |  ___|
  | |   | | | .  . || |__   | |/ /_\ \| |_/ / |    | |__  
  | |   | | | |\/| ||  __|  | ||  _  || ___ \ |    |  __|
  | |  _| |_| |  | || |___  | || | | || |_/ / |____| |___
  \_/  \___/\_|  |_/\____/  \_/\_| |_/\____/\_____/\____/
                                              )";
    cout << endl;

    setColor(5);
    cout << "======================================================" << endl;

    setColor(7);
    cout << "|   Day     | 8-9 AM | 9-10 AM | 10-12 PM | 2-4 PM   |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "| " << days[i];
        for (int j = 0; j < 4; j++)
        {
            cout << " | " << selectedTimetable[i][j];
        }
        cout << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "Press any key to return to menu...";
    getch();
}

void campusmap()
{
    system("cls");
    setColor(5);
    cout << "======================================================" << endl;
    setColor(11);
    cout << R"(
 _____   _____ _______   __  __  ___  _____
|_   _|/  ___|__   __|  |  \/  | / _ \ |  __ \
  | |  \  `--.  | |     | .  . |/ /_\ \| |_/ /
  | |   `--.  \ | |     | |\/| ||  _  ||  __/
 _| |_ /\\_/  / | |     | |  | || | | || |
|_____|\_____/  \_/     \_|  |_/\_| |_/\_|     )";
    cout << endl;

    setColor(5);
    cout << "======================================================" << endl;
    setColor(7);
    cout << "                                                           " << endl;
    cout << "                 [ MAIN GATE ]                            " << endl;
    cout << "                      |                                   " << endl;
    cout << "                      v                                   " << endl;
    cout << "                [ RAZA BLOCK ]                            " << endl;
    cout << "                      |                                   " << endl;
    cout << "          -----------------------------                   " << endl;
    cout << "          |               |            |                  " << endl;
    cout << "          v               V            v                  " << endl;
    cout << "   [ Block 2 ]                       [ Block 6 ]          " << endl;
    cout << "          |                           |                   " << endl;
    cout << "          v                           v                   " << endl;
    cout << "   [ BLOCK 3 ]                       [ BLOCK 7  ]         " << endl;
    cout << "          |                           |                   " << endl;
    cout << "          v                           v                   " << endl;
    cout << "   [ lIBRARY]                        [ CAFETERIA ]        " << endl;
    cout << "          |                           |                   " << endl;
    cout << "          v                           v                   " << endl;
    cout << "          -----------------------------                   " << endl;
    cout << "                      |                                   " << endl;
    cout << "                      v                                   " << endl;
    cout << "                [ HOSTELS AREA ]                          " << endl;
    setColor(13);
    cout << "==========================================================" << endl;
    setColor(7);
    cout << "Press any key to return to menu...";
    getch();
}

   
void FAQs()
{
    system("cls");
    setColor(13);
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    setColor(11);
    cout << "                  FREQUENTLY ASKED QUESTIONS (FAQs)" << endl;
    setColor(13);
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    setColor(7);
    cout << "\n";
    setColor(14);
    cout << "Q1: ";
    setColor(7);
    cout << "What is the best time to visit the cafe?" << endl;
    setColor(14);
    cout << "A1: ";
    setColor(7);
    cout << "Avoid 12:00 PM, it is the rush hour!" << endl;
    cout << "\n";
    setColor(14);
    cout << "Q2: ";
    setColor(7);
    cout << "Where can we study peacefully?" << endl;
    setColor(14);
    cout << "A2: ";
    setColor(7);
    cout << "The LIBRARY is best for quiet study." << endl;
    cout << "\n";
    setColor(14);
    cout << "Q3: ";
    setColor(7);
    cout << "Where to hang out with friends?" << endl;
    setColor(14);
    cout << "A3: ";
    setColor(7);
    cout << "CAFETERIA, RAZA BLOCK LAWN, and PORTAL CAFE." << endl;
    cout << "\n";
    setColor(14);
    cout << "Q4: ";
    setColor(7);
    cout << "Is there a gymnasium?" << endl;
    setColor(14);
    cout << "A4: ";
    setColor(7);
    cout << "Yes, there is one in campus." << endl;
    cout << "\n";
    setColor(14);
    cout << "Q5: ";
    setColor(7);
    cout << "Should you join societies in 1st semester?" << endl;
    setColor(14);
    cout << "A5: ";
    setColor(7);
    cout << "Yes, but balance them with studies." << endl;
    cout << "\n";
    setColor(14);
    cout << "Q6: ";
    setColor(7);
    cout << "Is grading system relative or absolute?" << endl;
    setColor(14);
    cout << "A6: ";
    setColor(7);
    cout << "Grading system is relative for theory and absolute for labs." << endl;
    cout << "\n";
    setColor(14);
    cout << "Q7: ";
    setColor(7);
    cout << "Is there WiFi available?" << endl;
    setColor(14);
    cout << "A7: ";
    setColor(7);
    cout << "Yes, EDUROAM is available after registration." << endl;

    cout << "\nPress any key to return to menu...";
    getch();

    getch();
}

// STUDENT MANAGEMENT
void addStudent(string name, string roll, string prog)
{

    cout << "Name :";
    getline(cin, name);
    cout << "Roll :";
    getline(cin, roll);
    cout << "Program : ";
    getline(cin, prog);

    stuName[stuCount] = name;
    stuRoll[stuCount] = roll;
    stuProg[stuCount] = prog;
    stuCount++;

    saveStudents();
    cout << "Student added.\n";
    pause();
}

void searchStudent(const string &roll)
{
    for (int i = 0; i < stuCount; ++i)
    {
        if (stuRoll[i] == roll)
        {
            cout << "\nName   : " << stuName[i]
                 << "\nRoll   : " << stuRoll[i]
                 << "\nProgram: " << stuProg[i] << "\n";
            pause();
            return;
        }
    }
    setColor(12);
    cout << "Not found\n";
}

void updateStudent(const string &rollToUpdate)
{
    for (int i = 0; i < stuCount; ++i)
    {
        if (stuRoll[i] == rollToUpdate)
        {
            cin.ignore();
            cout << "New name: ";
            getline(cin, stuName[i]);
            cout << "New program: ";
            getline(cin, stuProg[i]); // direct update

            saveStudents();
            cout << "Updated.\n";
            pause();
            return;
        }
    }
    setColor(12);
    cout << "Not found.\n";
}

void listStudents()
{
    if (stuCount == 0)
    {
        setColor(12);
        cout << "No students available.\n";
        pause();
        return;
    }

    cout << "\n===== STUDENT LIST =====\n";
    for (int i = 0; i < stuCount; i++)
    {
        cout << i + 1 << ". "
             << stuName[i] << " | "
             << stuRoll[i] << " | "
             << stuProg[i] << endl;
    }
    pause();
}
void saveStudents()
{
    ofstream fout;
    fout.open("students.txt");
    fout << stuCount << endl;
    for (int i = 0; i < stuCount; i++)
    {
        fout << stuName[i] << endl;
        fout << stuRoll[i] << endl;
        fout << stuProg[i] << endl;
    }
    fout.close();
}
void loadStudents()
{
    ifstream fin;
    fin.open("students.txt");
    if (!fin)
        return;
    fin >> stuCount;
    fin.ignore();
    for (int i = 0; i < stuCount; i++)
    {
        getline(fin, stuName[i]);
        getline(fin, stuRoll[i]);
        getline(fin, stuProg[i]);
    }
    fin.close();
}

// COURSE MANAGEMENT

void addCourse(string &code, string &title, string &instructor)
{
    if (couCount >= MAX)
    {
        cout << "\nList full.\n";
        return;
    }
    cin.ignore();
    cout << "Course code: ";
    getline(cin, code);
    cout << "Title: ";
    getline(cin, title);
    cout << "Instructor: ";
    getline(cin, instructor);

    // Add to global arrays
    couCode[couCount] = code;
    couTitle[couCount] = title;
    couInstructor[couCount] = instructor;
    couCount++;

    saveCourses();
    cout << "Course added.\n";
}

void listCourses()
{
    if (couCount == 0)
    {
        cout << "\nNo courses.\n";
        return;
    }
    for (int i = 0; i < couCount; ++i)
    {
        cout << couCode[i] << '\t' << couTitle[i] << '\t' << couInstructor[i] << '\n';
    }
    getch();
}
void updateCourse(const string &codeToUpdate)
{
    for (int i = 0; i < couCount; ++i)
    {
        if (couCode[i] == codeToUpdate)
        {
            cout << "New title: ";
            cin >> couTitle[i];
            cout << "New instructor: ";
            cin >> couInstructor[i];

            saveCourses();
            cout << "Course updated.\n";
            pause();
            return;
        }
    }
    setColor(12);
    cout << "Course not found.\n";
}

void searchCourse(const string &codeToSearch)
{
    for (int i = 0; i < couCount; ++i)
    {
        if (couCode[i] == codeToSearch)
        {
            cout << couCode[i] << " | "
                 << couTitle[i] << " | "
                 << couInstructor[i] << endl;
            pause();
            return;
        }
    }
    setColor(12);
    cout << "Course not found.\n";
}
void saveCourses()
{
    ofstream fout;
    fout.open("courses.txt");
    fout << couCount << endl;
    for (int i = 0; i < couCount; i++)
    {
        fout << couCode[i] << endl;
        fout << couTitle[i] << endl;
        fout << couInstructor[i] << endl;
    }
    fout.close();
}
void loadCourses()
{
    ifstream fin;
    fin.open("courses.txt");
    if (!fin)
        return;
    fin >> couCount;
    fin.ignore();
    for (int i = 0; i < couCount; i++)
    {
        getline(fin, couCode[i]);
        getline(fin, couTitle[i]);
        getline(fin, couInstructor[i]);
    }
    fin.close();
}
// USERS
void saveUsers()
{
    ofstream fout;
    fout.open("users.txt");
    fout << userCount << endl;
    for (int i = 0; i < userCount; i++)
    {
        fout << userName[i] << endl;
        fout << userPassword[i] << endl;
        fout << userRole[i] << endl;
        fout << userStatus[i] << endl;
    }
    fout.close();
}

void loadUsers()
{
    ifstream fin;
    fin.open("users.txt");
    if (!fin)
        return;
    fin >> userCount;
    fin.ignore();
    for (int i = 0; i < userCount; i++)
    {
        getline(fin, userName[i]);
        getline(fin, userPassword[i]);
        getline(fin, userRole[i]);
        getline(fin, userStatus[i]);
    }
    fin.close();
}

//================TEACHER FUNCTIONS==============
void addTeacher()
{
    if (teacherCount >= MAX_TEACHERS)
    {
        cout << "Teacher limit reached.\n";
        pause();
        return;
    }

    string name, id;
    cin.ignore();
    cout << "Enter Teacher Name: ";
    getline(cin, name);
    cout << "Enter Teacher ID: ";
    getline(cin, id);

    // Check duplicate ID
    for (int i = 0; i < teacherCount; i++)
    {
        if (teacherID[i] == id)
        {
            cout << "Teacher ID already exists.\n";
            pause();
            return;
        }
    }

    teacherName[teacherCount] = name;
    teacherID[teacherCount] = id;
    teacherCount++;

    saveTeachers();
    cout << "Teacher added.\n";
    pause();
}
void assignCourseToTeacher()
{
    if (teacherCount == 0 || couCount == 0)
    {
        cout << "No teachers or courses available.\n";
        pause();
        return;
    }

    string tid, code;
    cout << "Enter Teacher ID: ";
    cin >> tid;
    cout << "Enter Course Code: ";
    cin >> code;

    // Check teacher exists
    bool teacherFound = false;
    for (int i = 0; i < teacherCount; i++)
        if (teacherID[i] == tid)
            teacherFound = true;
    if (!teacherFound)
    {
        cout << "Teacher not found.\n";
        pause();
        return;
    }

    // Check course exists
    bool courseFound = false;
    for (int i = 0; i < couCount; i++)
        if (couCode[i] == code)
            courseFound = true;
    if (!courseFound)
    {
        cout << "Course not found.\n";
        pause();
        return;
    }

    // Prevent duplicate assignment
    for (int i = 0; i < assignmentCount; i++)
        if (assignTeacher[i] == tid && assignCourse[i] == code)
        {
            cout << "Already assigned.\n";
            pause();
            return;
        }

    assignTeacher[assignmentCount] = tid;
    assignCourse[assignmentCount] = code;
    assignmentCount++;

    saveAssignments();
    cout << "Course assigned to teacher.\n";
    pause();
}
void viewTeacherCourses()
{
    string tid;
    cout << "Enter Teacher ID: ";
    cin >> tid;
    bool found = false;

    for (int i = 0; i < assignmentCount; i++)
    {
        if (assignTeacher[i] == tid)
        {
            found = true;
            for (int j = 0; j < couCount; j++)
            {
                if (couCode[j] == assignCourse[i])
                {
                    cout << couCode[j] << " | " << couTitle[j] << endl;
                }
            }
        }
    }

    if (!found)
        cout << "No courses assigned to this teacher.\n";
    pause();
}
void viewCourseTeachers()
{
    string code;
    cout << "Enter Course Code: ";
    cin >> code;
    bool found = false;

    for (int i = 0; i < assignmentCount; i++)
    {
        if (assignCourse[i] == code)
        {
            found = true;
            for (int j = 0; j < teacherCount; j++)
            {
                if (teacherID[j] == assignTeacher[i])
                {
                    cout << teacherID[j] << " | " << teacherName[j] << endl;
                }
            }
        }
    }

    if (!found)
        cout << "No teachers assigned to this course.\n";
    pause();
}
void saveTeachers()
{
    ofstream fout;
    fout.open("teachers.txt");
    fout << teacherCount << endl;
    for (int i = 0; i < teacherCount; i++)
        fout << teacherName[i] << endl
             << teacherID[i] << endl;
    fout.close();
}

void loadTeachers()
{
    ifstream fin;
    fin.open("teachers.txt");
    if (!fin)
        return;
    fin >> teacherCount;
    fin.ignore();
    for (int i = 0; i < teacherCount; i++)
    {
        getline(fin, teacherName[i]);
        getline(fin, teacherID[i]);
    }
    fin.close();
}

void saveAssignments()
{
    ofstream fout;
    fout.open("assignments.txt");
    fout << assignmentCount << endl;
    for (int i = 0; i < assignmentCount; i++)
        fout << assignTeacher[i] << endl
             << assignCourse[i] << endl;
    fout.close();
}

void loadAssignments()
{
    ifstream fin;
    fin.open("assignments.txt");
    if (!fin)
        return;
    fin >> assignmentCount;
    fin.ignore();
    for (int i = 0; i < assignmentCount; i++)
    {
        getline(fin, assignTeacher[i]);
        getline(fin, assignCourse[i]);
    }
    fin.close();
}

// EXTRAS
void clearScreen()
{

    system("cls");
}

void pause()
{
    cout << "\nPress any key to continue...";
    getch();
}

void setColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}