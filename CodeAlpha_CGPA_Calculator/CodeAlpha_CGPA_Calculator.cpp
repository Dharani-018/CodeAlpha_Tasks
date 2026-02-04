#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Course {
    string name;
    float grade;
    int credits;
};

class CGPACalculator {
private:
    vector<Course> courses;
    float totalPoints = 0;
    int totalCredits = 0;

public:
    void inputCourses() {
        int numCourses;
        cout << "Enter the number of courses: ";
        cin >> numCourses;

        for (int i = 0; i < numCourses; ++i) {
            Course c;
            cout << "\nEnter details for course " << i + 1 << ":" << endl;
            cout << "Course Name: ";
            cin.ignore();
            getline(cin, c.name);
            
            cout << "Grade Points (e.g., A=4, B=3): ";
            cin >> c.grade;
            
            cout << "Credit Hours: ";
            cin >> c.credits;

            courses.push_back(c);
            totalPoints += (c.grade * c.credits);
            totalCredits += c.credits;
        }
    }

    void displayReport() {
        cout << "\n" << string(40, '=') << endl;
        cout << left << setw(20) << "Course" << setw(10) << "Grade" << "Credits" << endl;
        cout << string(40, '-') << endl;

        for (const auto& c : courses) {
            cout << left << setw(20) << c.name 
                 << setw(10) << fixed << setprecision(1) << c.grade 
                 << c.credits << endl;
        }

        float gpa = (totalCredits > 0) ? (totalPoints / totalCredits) : 0;

        cout << string(40, '-') << endl;
        cout << "Total Credits: " << totalCredits << endl;
        cout << "Semester GPA:  " << fixed << setprecision(2) << gpa << endl;
        cout << string(40, '=') << endl;
    }
};

int main() {
    CGPACalculator calc;
    calc.inputCourses();
    calc.displayReport();
    return 0;
}