#include <bits/stdc++.h>
using namespace std;

// -----------------------------
// Structures
// -----------------------------
struct Course {
    string name;
    int credits;
    int difficulty;
};

struct Student {
    string name;
    vector<pair<Course, int>> completedCourses; // course + marks
};

// -----------------------------
// Global Data
// -----------------------------
vector<Course> courseList;
vector<Student> students;

// -----------------------------
// GPA CALCULATION
// -----------------------------
double calculateGPA(Student &s) {
    double totalPoints = 0;
    int totalCredits = 0;

    for (auto &c : s.completedCourses) {
        int marks = c.second;
        int grade;

        if (marks >= 90) grade = 10;
        else if (marks >= 80) grade = 9;
        else if (marks >= 70) grade = 8;
        else if (marks >= 60) grade = 7;
        else if (marks >= 50) grade = 6;
        else grade = 0;

        totalPoints += grade * c.first.credits;
        totalCredits += c.first.credits;
    }

    return totalCredits ? totalPoints / totalCredits : 0;
}

// -----------------------------
// GREEDY COURSE PLANNER
// -----------------------------
void greedyPlanner(int maxCredits) {
    vector<Course> sortedCourses = courseList;

    sort(sortedCourses.begin(), sortedCourses.end(), [](Course a, Course b) {
        return a.difficulty < b.difficulty;
    });

    int total = 0;
    cout << "\nGreedy Selected Courses:\n";

    for (auto &c : sortedCourses) {
        if (total + c.credits <= maxCredits) {
            cout << c.name << endl;
            total += c.credits;
        }
    }
}

// -----------------------------
// DYNAMIC PROGRAMMING PLANNER
// -----------------------------
void dpPlanner(int maxCredits) {
    int n = courseList.size();

    vector<vector<int>> dp(n + 1, vector<int>(maxCredits + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= maxCredits; w++) {
            if (courseList[i - 1].credits <= w) {
                dp[i][w] = max(
                    courseList[i - 1].difficulty + dp[i - 1][w - courseList[i - 1].credits],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nDP Optimized Course Plan Value: " << dp[n][maxCredits] << endl;
}

// -----------------------------
// STUDY PLANNER (Simple AI)
// -----------------------------
void studyPlanner(Student &s) {
    cout << "\nStudy Plan for " << s.name << ":\n";

    for (auto &c : s.completedCourses) {
        if (c.second < 70)
            cout << "Focus more on: " << c.first.name << endl;
        else
            cout << "Maintain: " << c.first.name << endl;
    }
}

// -----------------------------
// ADD COURSE
// -----------------------------
void addCourse() {
    Course c;
    cout << "Enter course name: ";
    cin >> c.name;
    cout << "Enter credits: ";
    cin >> c.credits;
    cout << "Enter difficulty (1-10): ";
    cin >> c.difficulty;

    courseList.push_back(c);
}

// -----------------------------
// ADD STUDENT
// -----------------------------
void addStudent() {
    Student s;
    cout << "Enter student name: ";
    cin >> s.name;

    int n;
    cout << "Number of completed courses: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Course c;
        int marks;

        cout << "Course name: ";
        cin >> c.name;
        cout << "Credits: ";
        cin >> c.credits;
        cout << "Marks: ";
        cin >> marks;

        s.completedCourses.push_back({c, marks});
    }

    students.push_back(s);
}

// -----------------------------
// LEADERBOARD (Sorting)
// -----------------------------
void showLeaderboard() {
    vector<pair<string, double>> leaderboard;

    for (auto &s : students) {
        leaderboard.push_back({s.name, calculateGPA(s)});
    }

    sort(leaderboard.begin(), leaderboard.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    cout << "\nLeaderboard:\n";
    for (auto &p : leaderboard) {
        cout << p.first << " - GPA: " << p.second << endl;
    }
}

// -----------------------------
// MAIN MENU
// -----------------------------
int main() {
    int choice;

    while (true) {
        cout << "\n--- EduPortal Menu ---\n";
        cout << "1. Add Course\n";
        cout << "2. Add Student\n";
        cout << "3. Calculate GPA\n";
        cout << "4. Study Planner\n";
        cout << "5. Greedy Course Planner\n";
        cout << "6. DP Course Planner\n";
        cout << "7. Leaderboard\n";
        cout << "8. Exit\n";

        cin >> choice;

        if (choice == 1) addCourse();
        else if (choice == 2) addStudent();

        else if (choice == 3) {
            for (auto &s : students)
                cout << s.name << " GPA: " << calculateGPA(s) << endl;
        }

        else if (choice == 4) {
            for (auto &s : students)
                studyPlanner(s);
        }

        else if (choice == 5) {
            int maxCredits;
            cout << "Enter max credits: ";
            cin >> maxCredits;
            greedyPlanner(maxCredits);
        }

        else if (choice == 6) {
            int maxCredits;
            cout << "Enter max credits: ";
            cin >> maxCredits;
            dpPlanner(maxCredits);
        }

        else if (choice == 7) showLeaderboard();

        else if (choice == 8) break;
    }

    return 0;
}
