#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
protected:
    string firstName, lastName;
    float gpa;
    int gradYear, enrolledYear;
    string gradSemester, enrolledSemester;
    bool isUndergrad;

public:
    Student() : firstName(""), lastName(""), gpa(0.0), gradYear(0), enrolledYear(0),
                gradSemester(""), enrolledSemester(""), isUndergrad(true) {}

    virtual ~Student() {}

    void setName(string first, string last) { firstName = first; lastName = last; }
    void setGPA(string g) { gpa = stof(g); }
    void setGraduation(int y, string s) { gradYear = y; gradSemester = s; }
    void setEnrollment(int y, string s) { enrolledYear = y; enrolledSemester = s; }
    void setStatus(bool status) { isUndergrad = status; }

    string getFullName() const { return firstName + " " + lastName; }
    float getGPA() const { return gpa; }
    string getGraduation() const { return gradSemester + " " + to_string(gradYear); }
    string getEnrollment() const { return enrolledSemester + " " + to_string(enrolledYear); }
    string getStatus() const { return isUndergrad ? "Undergrad" : "Grad"; }
};

class Art_Student : public Student {
    string emphasis;
public:
    void setEmphasis(string e) { emphasis = e; }
    string getEmphasis() const { return emphasis; }
};

class Physics_Student : public Student {
    string concentration;
public:
    void setConcentration(string c) { concentration = c; }
    string getConcentration() const { return concentration; }
};

int main() {
    vector<Art_Student*> arts;
    vector<Physics_Student*> physics;

    for(int i = 0; i < 5; i++) {
        Art_Student* a = new Art_Student;
        a->setName("Art" + to_string(i), "Student");
        a->setGPA(to_string(3.0 + i*0.2));
        a->setEnrollment(2020 + i, "Fall");
        a->setGraduation(2024 + i, "Spring");
        a->setStatus(i % 2);
        a->setEmphasis((i % 3 == 0) ? "Art Studio" : 
                      (i % 3 == 1) ? "Art History" : "Art Education");
        arts.push_back(a);
    }

    for(int i = 0; i < 5; i++) {
        Physics_Student* p = new Physics_Student;
        p->setName("Physics" + to_string(i), "Student");
        p->setGPA(to_string(3.5 + i*0.1));
        p->setEnrollment(2019 + i, "Spring");
        p->setGraduation(2023 + i, "Fall");
        p->setStatus(i % 2);
        p->setConcentration((i % 2) ? "Biophysics" : "Earth and Planetary Sciences");
        physics.push_back(p);
    }

    ofstream out("student_info.dat");
    for(auto* a : arts) {
        out << "Art Student," << a->getFullName() << "," << a->getGPA() << ","
            << a->getEnrollment() << "," << a->getGraduation() << ","
            << a->getStatus() << "," << a->getEmphasis() << "\n";
    }

    for(auto* p : physics) {
        out << "Physics Student," << p->getFullName() << "," << p->getGPA() << ","
            << p->getEnrollment() << "," << p->getGraduation() << ","
            << p->getStatus() << "," << p->getConcentration() << "\n";
    }

    for(auto* a : arts) delete a;
    for(auto* p : physics) delete p;

    return 0;
}
