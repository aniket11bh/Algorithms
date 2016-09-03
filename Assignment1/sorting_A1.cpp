#include <iostream>

using namespace std;

struct Students {
    char roll[10];
    int artMarks;
    int scienceMarks;
};


void swap(Students *a, Students* b){
	Students temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Students A[], int size, int subject){

	int pivot;
	int i = size - 1;

	if (subject == 1){
		pivot = A[size-1].artMarks;
	}
	else {
		pivot = A[size-1].scienceMarks;
	}

	for (int j = size - 2; j >= 0; j--){
		if (A[j].artMarks < pivot ){
			i = i - 1;
			swap(&A[j],&A[i]);
		}
	}
	swap(&A[size-1],&A[i]);
	return i-1;
}

void insertionSort(Students A[], int size, int subject){
	// subject = 2 - sort a/c to science mark
	// subject = 1 - sort a/c to arts mark
	int i = 0;
	if (size <= 1) return;

	else{
		i = partition(A, size, subject);
		insertionSort(A, i+1, subject);
		insertionSort(A+i+2, size-i-2, subject);
	}
}

int main(){

    int numStudents = 0;
    int userOption = 0;
    int imark, fmark;

    cout << "Enter number of students : ";
    cin >> numStudents;

    struct Students students[numStudents];

    cout << "+++ Enter Initial list of students sorted by roll no. followed by artMarks, scienceMarks \n";
    for (int i=0; i<numStudents; i++){
        cin >> students[i].roll;
        cin >> students[i].artMarks;
        cin >> students[i].scienceMarks;
    }

    cout << "+++ Students details : \n";
    for (int i=0; i<numStudents; i++){
        cout << "\t" << students[i].roll << ", " << students[i].artMarks << ", "<< students[i].scienceMarks << "\n";
    }

    cout << "+++ Interval Search\n";
    do{
        cin >> userOption;

        if (userOption){
            if (userOption == 1){
                cout << "--- Interval query for arts\n";
				insertionSort(students, numStudents, 1);
            }
            else if (userOption == 2){
                cout << "--- Interval query for science\n";
				// insertionSort(students, numStudents, 0);
            }

            // cin >> imark >> fmark;
            // query(userOption, imark, fmark);
        }

        else {
            // Break the loop
        }
    }while (userOption);

	cout << "+++ Students details : \n";
	for (int i=0; i<numStudents; i++){
		cout << "\t" << students[i].roll << ", " << students[i].artMarks << ", "<< students[i].scienceMarks << "\n";
	}

    return 0;
}
