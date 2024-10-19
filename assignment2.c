#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Initializing constant values
#define MAX_STUDENTS 1000
#define MAX_EXAMS 500
#define MAX_GRADE 100
#define MAX_NAME 20
#define MIN_NAME 1
#define MAX_FACULTY 30
#define MIN_FACULTY 4
#define MAX_SOFTWARE 20
#define MIN_SOFTWARE 2
#define MIN_DURATION 40
#define MAX_DURATION 180
#define ASCII_Z 25
#define ASCII_A 0
#define NAME 0
#define FACULTY 1
#define SOFTWARE 2
#define AVERAGE_STR_LEN 100

typedef struct Student{
    int student_id;
    char name[MAX_NAME];
    char faculty[MAX_FACULTY];
}Student; //Struct Student like in task

typedef struct ExamGrade {
    int exam_id;
    int student_id;
    int grade;
}ExamGrade; //Struct ExamGrade like in task

typedef enum ExamType {
    WRITTEN,
    DIGITAL
}ExamType; //Enum ExamType like in task

union ExamInfo {
    int duration;
    char software[MAX_SOFTWARE];
}; //Union ExamInfo like in task

typedef struct Exam {
    int exam_id;
    ExamType exam_type;
    union ExamInfo exam_info;
}Exam; //Struct Exam like in task


//Array of structures
Student student[MAX_STUDENTS];
Exam exams[MAX_EXAMS];
ExamGrade grades[MAX_STUDENTS][MAX_EXAMS];

//Function that checks if there are any symbols except a-z (A-Z) in string \
and if name/faculty/software length is acceptable
int checkChar(char *sttr, int what_is) {
    int flag = 1;
    int len = strlen(sttr);//calculate length of the string
    if (sttr[strlen(sttr) - 1] == '\n') { //Check if there are '\n' in the end
        len = len - 1; //If yes, then decrease length by 1, cause program count '\n' like a symbol
    };
    switch (what_is) {

        case 0:
            if (len != 0) { //Check if string empty or not
                for (int i = 0; i < strlen(sttr); i++) { //Check every symbol of the string by loop and using ASCII
                    if ((((sttr[i] - 'A' < ASCII_A || sttr[i] - 'A' > ASCII_Z) && (sttr[i] - 'a' < ASCII_A || sttr[i] - 'a' > ASCII_Z)) && (sttr[i]!='\n')) || (len < MIN_NAME+1 || len > MAX_NAME-1)) {
                        flag = 0; //If it's not correct then break the loop and make flag = 0
                        break;
                    }
                }
            }

            else {
                flag = 0;
            }

        if (flag == 0) { //If loop was not terminated at any point, then flag = 1, and function don't return 0
            return 0; //If it was, then we return 0
        }

        break;
        case 1:
            if (len != 0) {//Check if string empty or not
                for (int i = 0; i < strlen(sttr); i++) {//Check every symbol of the string by loop and using ASCII
                    if ((((sttr[i] - 'A' < ASCII_A || sttr[i] - 'A' > ASCII_Z) && (sttr[i] - 'a' < ASCII_A || sttr[i] - 'a' > ASCII_Z)) && (sttr[i]!='\n')) || (len < MIN_FACULTY+1 || len > MAX_FACULTY-1)) {
                        flag = 0;//If it's not correct then break the loop and make flag = 0
                        break;
                    }
                }
            }

            else {
                flag = 0;
            }

        if (flag == 0) {//If loop was not terminated at any point, then flag = 1, and function don't return 0
            return 0; //If it was, then we return 0
        }

        break;
        case 2:
            if (len != 0) {//Check if string empty or not
                for (int i = 0; i < strlen(sttr); i++) {//Check every symbol of the string by loop and using ASCII
                    if ((((sttr[i] - 'A' < ASCII_A || sttr[i] - 'A' > ASCII_Z) && (sttr[i] - 'a' < ASCII_A || sttr[i] - 'a' > ASCII_Z)) && (sttr[i]!='\n')) || (len < MIN_SOFTWARE+1 || len > MAX_SOFTWARE-1)) {
                        flag = 0;//If it's not correct then break the loop and make flag = 0
                        break;
                    }
                }
            }

            else {
                flag = 0;
            }

        if (flag == 0) {//If loop was not terminated at any point, then flag = 1, and function don't return 0
            return 0; //If it was, then we return 0
        }

        break;
    }
    return 1;//If loop at 1 of the cases was terminated at any point, then flag = 0, and function can't get here\
    but if it wasn't terminated then all is correct, and we return 1.
}

//Function that just add its arguments to structure indexed by student id
void addStudent(int student_id, char* name, char* faculty,FILE *foup) {
    student[student_id].student_id = student_id;
    strcpy(student[student_id].name, name);
    strcpy(student[student_id].faculty, faculty);
    fprintf(foup, "Student: %d added\n", student_id);
};

//Function that just add its arguments to structure indexed by exam id
void addExam(int exam_id, ExamType exam_type, union ExamInfo exam_info, FILE *foup) {
    exams[exam_id].exam_id = exam_id;
    exams[exam_id].exam_type = exam_type;
    exams[exam_id].exam_info = exam_info;
    fprintf(foup, "Exam: %d added\n", exam_id);
};

//Function that just add its arguments to structure indexed by [student id][exam id] (Two-dimensional array of structures)
void addGrade(int exam_id, int student_id, int grade, FILE *foup) {
    grades[student_id][exam_id].student_id = student_id;
    grades[student_id][exam_id].exam_id = exam_id;
    grades[student_id][exam_id].grade = grade;
    fprintf(foup, "Grade %d added for the student: %d\n", grade, student_id);
}

//Function that just update values of structure indexed by exam id with its arguments
void updateExam(int exam_id, ExamType exam_type, union ExamInfo exam_info, FILE *foup) {
    exams[exam_id].exam_id = exam_id;
    exams[exam_id].exam_type = exam_type;
    exams[exam_id].exam_info = exam_info;
    fprintf(foup, "Exam: %d updated\n", exam_id);
}

//Function that just update values of structure indexed by [student id][exam id] (Two-dimensional array of structures) with its arguments
void updateGrade(int exam_id, int student_id, int grade, FILE *foup) {
    grades[student_id][exam_id].grade = grade;
    fprintf(foup, "Grade %d updated for the student: %d\n", grade, student_id);
}

//Function that search structure with index equal to student id and print variables of this structure
void searchStudent(int student_id, FILE *foup) {
    fprintf(foup, "ID: %d, Name: %s, Faculty: %s", student[student_id].student_id, student[student_id].name, student[student_id].faculty);
}

//Function that search structure with index equal to [student id][exam id] (Two-dimensional array of structures) and print variables of this structure
void searchGrade(int exam_id, int student_id, FILE *foup) {
    char exam_type_scope[AVERAGE_STR_LEN];
    if (exams[exam_id].exam_type == WRITTEN) {
        strcpy(exam_type_scope, "WRITTEN");
        fprintf(foup,"Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %d\n", exams[exam_id].exam_id, student[student_id].student_id, student[student_id].name, grades[student_id][exam_id].grade, exam_type_scope, exams[exam_id].exam_info.duration);
    }
    else {
        strcpy(exam_type_scope, "DIGITAL");
        fprintf(foup,"Exam: %d, Student: %d, Name: %s, Grade: %d, Type: %s, Info: %s", exams[exam_id].exam_id, student[student_id].student_id, student[student_id].name, grades[student_id][exam_id].grade, exam_type_scope, exams[exam_id].exam_info.software);
    }
}

int main() {
    //Opening the input and output files
    FILE *finp = fopen("input.txt", "r");
    FILE *foup = fopen("output.txt", "w");


    union ExamInfo exam_info; //Create variable of union ExamInfo type

    char Line[AVERAGE_STR_LEN]; //Create variable to storage our lines
    char *spf; //Pointer that will be used to point to Line variable

    //Each line include command (for example, ADD_STUDENT) and argument (id, name, etc.), so that's why we separate it by " " \
    and create variable that will contain command and arguments
    char command[AVERAGE_STR_LEN];
    char arg1[AVERAGE_STR_LEN];
    char arg2[AVERAGE_STR_LEN];
    char arg3[AVERAGE_STR_LEN];

    int num[MAX_STUDENTS] = {0}; //Arrays that will be used to keep information about the order of student addition.
    int ctn = 0;

    while (strcmp(fgets(Line, sizeof(Line), finp), "END")!=0) { //By this loop program can read and get lines until it gets line with command "End"
        spf = strtok (Line," "); //Get the part of Line before the first " "
        strcpy(command, spf); //Copy it to command variable

        //All this conditions check if there is '\n' in the end of the separated part of Line, because if it is, \
        then Line has ended and there is no need to continue filling the arguments
        if (command[strlen(command)-1] != '\n') {

            spf = strtok (NULL," ");
            strcpy(arg1, spf);

            if (arg1[strlen(arg1)-1] != '\n') {

                spf = strtok (NULL," ");
                strcpy(arg2, spf);

                if (arg2[strlen(arg2)-1] != '\n') {

                    spf = strtok (NULL," ");
                    strcpy(arg3, spf);

                }
            }
        }

        //If command is "ADD_STUDENT", then program checks if input valid; if it is, program calls function "addStudent"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "ADD_STUDENT") == 0) {
            //Copy arguments to local variables
            int student_id = strtol(arg1, NULL, 10);

            char student_name[MAX_NAME];
            strcpy(student_name, arg2);

            char student_faculty[MAX_FACULTY+1];
            strcpy(student_faculty, arg3);

            //Checking valid input and if student was added already
            if ((checkChar(student_name, NAME) == 1) && (checkChar(student_faculty, FACULTY) == 1) && (student_id > 0 && student_id < MAX_STUDENTS) && (student[student_id].student_id == 0)) {
                addStudent(student_id, student_name, student_faculty, foup);
                num[ctn] = student_id;
                ctn++;
            }
            else { //If it's not valid, program check where is the error exactly and print the appropriate message
                if (student[student_id].student_id != 0) {
                    fprintf(foup, "Student: %d already exists\n", student_id);
                    continue;
                }
                if ((student_id > 0 && student_id < MAX_STUDENTS)==0) {
                    fprintf(foup,"Invalid student id\n");
                    continue;
                }
                if (checkChar(student_name, NAME) == 0) {
                    fprintf(foup,"Invalid name\n");
                    continue;
                }
                if (checkChar(student_faculty, FACULTY) == 0) {
                    fprintf(foup,"Invalid faculty\n");
                    continue;
                }
            }
        }

        //If command is "ADD_EXAM", then program checks if input valid; if it is, program calls function "addExam"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "ADD_EXAM") == 0) {
            //Copy arguments to local variables
            int exam_id = strtol(arg1, NULL, 10);

            char exam_type[AVERAGE_STR_LEN];
            strcpy(exam_type, arg2);

            char software_scope[MAX_SOFTWARE];
            int duration_scope;

            if (strcmp(exam_type, "DIGITAL") == 0) { //Check the type of Exam
                strcpy(software_scope, arg3); //If it is digital, then arg3 is string
            }
            else { //If not, it's int.
                duration_scope = strtol(arg3, NULL, 10);
            }
            if (exams[exam_id].exam_id != 0) { //Check if exam was added already
                fprintf(foup,"Exam: %d already exists\n", exam_id);
                continue;
            }
            if ((exam_id > 0 && exam_id < MAX_EXAMS)) { //Checking if input valid
                if (strcmp(exam_type, "DIGITAL") == 0) { //Checking the exam type
                    if (checkChar(software_scope, SOFTWARE)) { //Checking if input valid
                        strcpy(exam_info.software, software_scope);
                        addExam(exam_id, DIGITAL, exam_info, foup); //If it is, the calling function
                    }
                    else { //If input is not valid, printing the erorr
                        fprintf(foup,"Invalid software\n");
                        continue;
                    }
                }
                else if (strcmp(exam_type, "WRITTEN") == 0){ ////Checking the exam type
                    if (MIN_DURATION<=duration_scope && duration_scope<=MAX_DURATION) {//Checking if input valid
                        exam_info.duration = duration_scope;
                        addExam(exam_id, WRITTEN, exam_info, foup);//If it is, the calling function
                    }
                    else {//If input is not valid, printing the erorr
                        fprintf(foup,"Invalid duration\n");
                        continue;
                    }
                }
                else {//If input is not valid, printing the erorr
                    fprintf(foup,"Invalid exam type\n");
                    continue;
                }
            }
            else {//If input is not valid, program try to find the mistake and print the appropriate message
                if ((exam_id > 0 && exam_id < MAX_EXAMS)==0) {
                    fprintf(foup,"Invalid exam id\n");
                    continue;
                }
                if (checkChar(exam_type, NAME) == 0) {
                    fprintf(foup,"Invalid exam type\n");
                    continue;
                }
            }
        }

        //If command is "ADD_GRADE", then program checks if input valid; if it is, program calls function "addGrade"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "ADD_GRADE") == 0) {
            //Copy arguments to local variables
            int exam_id = strtol(arg1, NULL, 10);
            int student_id = strtol(arg2, NULL, 10);
            int grade = strtol(arg3, NULL, 10);

            //Check if input is valid and if exam and student was added
            if ((student_id > 0 && student_id < MAX_STUDENTS) && (exam_id > 0 && exam_id < MAX_EXAMS) && (grade >= 0 && grade <= MAX_GRADE) && (exams[exam_id].exam_id != 0) && (student[student_id].student_id != 0)) {
                addGrade(exam_id,student_id,grade, foup); //If it is, then calling the function
            }
            else {//If input is not valid, program try to find the mistake and print the appropriate message
                if ((exams[exam_id].exam_id == 0) && (exam_id > 0 && exam_id < MAX_EXAMS)) {
                    fprintf(foup,"Exam not found\n");
                    continue;
                }
                if ((exam_id > 0 && exam_id < MAX_EXAMS)==0) {
                    fprintf(foup,"Invalid exam id\n");
                    continue;
                }
                if ((student[student_id].student_id == 0) && (student_id > 0 && student_id < MAX_STUDENTS)) {
                    fprintf(foup,"Student not found\n");
                    continue;
                }
                if ((student_id > 0 && student_id < MAX_STUDENTS)==0) {
                    fprintf(foup,"Invalid student id\n");
                    continue;
                }

                if ((grade >= 0 && grade <= MAX_GRADE) == 0) {
                    fprintf(foup,"Invalid grade\n");
                    continue;
                }
            }
        }

        //If command is "UPDATE_EXAM", then program checks if input valid; if it is, program calls function "updateExam"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "UPDATE_EXAM") == 0) {
            //Copy arguments to local variables
            int exam_id = strtol(arg1, NULL, 10);

            char exam_type[AVERAGE_STR_LEN];
            strcpy(exam_type, arg2);

            char software_scope[MAX_SOFTWARE];
            int duration_scope;

            if (strcmp(exam_type, "DIGITAL") == 0) { //Check the type of Exam
                strcpy(software_scope, arg3); //If it is digital, then arg3 is string
            }
            else { //If not, it's int.
                duration_scope = strtol(arg3, NULL, 10);
            }
            if (strcmp(exam_type, "DIGITAL") == 0) {
                if (checkChar(software_scope, SOFTWARE)) { //Checking if input valid
                    strcpy(exam_info.software, software_scope);
                    updateExam(exam_id, DIGITAL, exam_info, foup); //If it is, then calling the function
                }
                else { //if it's not, print the error message
                    fprintf(foup,"Invalid software\n");
                    continue;
                }
            }
            else if (strcmp(exam_type, "WRITTEN") == 0){
                if (MIN_DURATION<=duration_scope && duration_scope<=MAX_DURATION) {//Checking if input valid
                    exam_info.duration = duration_scope;
                    updateExam(exam_id, WRITTEN, exam_info, foup);//If it is, then calling the function
                }
                else {//if it's not, print the error message
                    fprintf(foup,"Invalid duration\n");
                    continue;
                }
            }
            else {//if input is not valid, print the error message
                fprintf(foup,"Invalid exam type\n");
                continue;
            }

        }

        //If command is "UPDATE_GRADE", then program checks if input valid; if it is, program calls function "updateGrade"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "UPDATE_GRADE") == 0) {
            //Copy arguments to local variables
            int exam_id = strtol(arg1, NULL, 10);
            int student_id = strtol(arg2, NULL, 10);
            int grade = strtol(arg3, NULL, 10);

            if (grade >= 0 && grade <= MAX_GRADE) { //Check if input is correct
                updateGrade(exam_id, student_id, grade, foup); //If it is, then calling the function
            }
            else {
                fprintf(foup,"Invalid grade\n"); //If it's not, the printing the error message
            }
        }

        //If command is "SEARCH_STUDENT", then program checks if input valid; if it is, program calls function "searchStudent"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "SEARCH_STUDENT") == 0) {
            //Copy arguments to local variables
            int student_id = strtol(arg1, NULL, 10);

            if ((student[student_id].student_id != 0) && (student_id > 0 && student_id < MAX_STUDENTS)){ //Check if input is valid and student was added
                searchStudent(student_id, foup); //If it is, then calling the function
            }
            else if ((student[student_id].student_id == 0) && (student_id > 0 && student_id < MAX_STUDENTS)) {
                fprintf(foup,"Student not found\n"); //If input is valid, but student wasn't added, then print the appropriate error.
            }
            else {
                fprintf(foup,"Invalid student id\n"); //If input is not valid, then printing the error
            }
        }

        //If command is "SEARCH_GRADE", then program checks if input valid; if it is, program calls function "searchGrade"; \
        if it's not, program prints the message for appropriate  error
        if (strcmp(command, "SEARCH_GRADE") == 0) {
            //Copy arguments to local variables
            int exam_id = strtol(arg1, NULL, 10);
            int student_id = strtol(arg2, NULL, 10);
            //Check if input is valid and student, exam were added
            if ((exams[exam_id].exam_id != 0) && (exam_id > 0 && exam_id < MAX_EXAMS) && (student[student_id].student_id != 0) && (student_id > 0 && student_id < MAX_STUDENTS)) {
                searchGrade(exam_id, student_id, foup); //If all is correct, then calling the function
            }
            else{ //If input is not valid, program try to find the mistake and print the appropriate message
                if ((exams[exam_id].exam_id == 0) && (exam_id > 0 && exam_id < MAX_EXAMS)) {
                    fprintf(foup,"Exam not found\n");
                    continue;
                }
                if ((exam_id > 0 && exam_id < MAX_EXAMS)==0) {
                    fprintf(foup,"Invalid exam id\n");
                    continue;
                }
                if ((student[student_id].student_id == 0) && (student_id > 0 && student_id < MAX_STUDENTS)) {
                    fprintf(foup,"Student not found\n");
                    continue;
                }
                if ((student_id > 0 && student_id < MAX_STUDENTS)==0) {
                    fprintf(foup,"Invalid student id\n");
                    continue;
                }
            }
        }

        //If command is "DELETE_STUDENT", then program just deletes everything that was connected with him (information, grades)
        if (strcmp(command, "DELETE_STUDENT") == 0) {
            //Copy arguments to local variables
            int student_id = strtol(arg1, NULL, 10);

            for (int i = 0; i < MAX_STUDENTS; i++) { //Deleting him from list of added students
                if (num[i] == student_id) {
                    num[i] = 0;
                }
            }

            //Deleting his grades (grades in structures that are indexed by his student id and any exam id), checking all exams idby loop
            for (int i = 0; i < MAX_EXAMS; i++) {
                grades[student_id][i].student_id = 0;
                grades[student_id][i].exam_id = 0;
                grades[student_id][i].grade = 0;
            }

            //Deleting information in structure that was indexed by his student id
            student[student_id].student_id = 0;
            strcpy(student[student_id].name, "");
            strcpy(student[student_id].faculty, "");
            fprintf(foup,"Student: %d deleted\n", student_id);
        }

        //If command is "LIST_ALL_STUDENTS", then program just prints information about students in order they were added
        if (strcmp(command, "LIST_ALL_STUDENTS\n") == 0) {
            for (int i = 0; i < MAX_STUDENTS; i++) { //By loop program get all student's id from ordered list of added students
                if (num[i]!=0) {
                    searchStudent(num[i], foup); //Use function "searchStudent" to get information from students id
                }
            }
        }

        //If command is "END", then program just stops working
        if ((strcmp(command, "END\n") == 0) || (strcmp(command, "END") == 0)) {
            //Closing the files
            fclose(finp);
            fclose(foup);
            return 0;
        }
    }
}