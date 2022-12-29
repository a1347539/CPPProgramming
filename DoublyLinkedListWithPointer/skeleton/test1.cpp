#include <iostream>

using namespace std;

struct Train {
    int trainNumber;
    Train* prev;
    Train* next;
};

Train* initTrain();
void printTrain(Train*);
void sortTrain(Train*);
void deallocateTrain(Train*);
void deallocate_one(Train*);

bool swapCar(Train* head, int a, int b)
{
    int interval;
    Train* bcar;

    if (a < 1 || b < 1) {
        return false;
    }
    // if two positions are equal
    if (a == b) {
        return true;
    }

    // if first position is larger than the two position
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    interval = b-a;

    for (int temp = a; temp > 0; head = head->next, temp--) {
        if (head->next == nullptr) {
            return false;
        }
    }

    for (bcar = head; interval > 0; bcar = bcar->next, interval--) {
        if (bcar->next == nullptr) {
            return false;
        }
    }

    // cout << b << " " << a << " " << b-a << endl;
    interval = b-a;
    Train* headP = head->prev;
    Train* headN = head->next;
    cout << "swapping: " << head->trainNumber << " " << bcar->trainNumber << " interval: " << interval << endl;

    if (interval > 1) {
        head->prev->next = bcar;
        bcar->prev->next = head;

        if (bcar->next != nullptr) {
            bcar->next->prev = head;
        }
        head->next->prev = bcar;

        head->prev = bcar->prev;
        bcar->prev = headP;


        head->next = bcar->next;
        bcar->next = headN;
    } else {
        head->prev->next = bcar;
        if (bcar->next != nullptr) {
            bcar->next->prev = head;
        }

        head->next = bcar->next;
        bcar->prev = head->prev;

        bcar->next = head;
        head->prev = bcar;
    }
    return true;
}

void fun1(Train* train) {
    for (Train* t = train; t != nullptr; t = t->next) {
        cout << "Loop train number is: " << t-> trainNumber << endl;
        cout << "Train number is: " << train->trainNumber << endl;
    }
}

void fun2(Train* train) {
    for (int i = 0; i < 2; i++, train = train->next);
}


int main() {

    Train* train = initTrain();

    cout << "after init" << endl;
    cout << train->trainNumber << endl;
    fun2(train);
    cout << train->trainNumber << endl;


    cout << "done" << endl;
    return 0;
}


Train* initTrain() {
    Train* t1 = new Train;
    Train* t2 = new Train;
    Train* t3 = new Train;
    Train* t4 = new Train;
    Train* t5 = new Train;
    Train* t6 = new Train;
    Train* t7 = new Train;
    Train* t8 = new Train;
    Train* t9 = new Train;
    t1->trainNumber = 4; t1->next = t2; t1->prev = nullptr;
    t2->trainNumber = 1; t2->next = t3; t2->prev = t1;
    t3->trainNumber = 6; t3->next = t4; t3->prev = t2;
    t4->trainNumber = 2; t4->next = t5; t4->prev = t3;
    t5->trainNumber = 5; t5->next = nullptr; t5->prev = t4;
    // t6->trainNumber = 6; t6->next = t7; t6->prev = t5;
    // t7->trainNumber = 7; t7->next = t8; t7->prev = t6;
    // t8->trainNumber = 8; t8->next = t9; t8->prev = t7;
    // t9->trainNumber = 9; t9->next = nullptr;  t9->prev = t8;
    return t1;
}

void printTrain(Train *head) {
    cout << head->trainNumber << " ";
    for(; head->next; head = head->next) {
        cout << head->next->trainNumber << " ";
    }
    cout << endl;
    // for (; head; head = head->prev) {
    //     cout << head->trainNumber << " ";
    // }
    // cout << endl;
}

void trainInsert(Train *train, Train *sortedTrain) {
    // never insert at 1st position
    // sortedList is never empty
    // sortedTrain: On first time calling, sortedTrain is a list with only HEAD
    // train: train is the cart to be inserted at the sorted position
    for (; sortedTrain->next != nullptr; sortedTrain = sortedTrain->next) {
        // break if the next train > current train.
        // 1,2,7 
        // sortedTrain = 2, train = 4, sortedTrain->next = 7 > 4
        // break
        // for sorting in ascending order
        if (sortedTrain->next->trainNumber < train->trainNumber) { break; }
    }

    if (sortedTrain->next == nullptr) {
        train->next = nullptr;
    }
    else {
        train->next = sortedTrain->next;
        sortedTrain->next->prev = train;
    }

    sortedTrain->next = train;
    train->prev = sortedTrain;
}

void sortTrain(Train *head) {

    cout << "Sorting" << endl;
    Train *sortedTrain = new Train(*head);

    sortedTrain->next = nullptr;

    for (Train *i = head->next; i != nullptr; i = i->next) {
        Train *current = new Train(*i);
        current->next = current->prev = nullptr;
        trainInsert(current, sortedTrain);
    }

    deallocateTrain(head);

    *head = *sortedTrain;
}

void deallocateTrain(Train* head)
{
    if (head == nullptr) {
        return;
    }
    deallocateTrain(head->next);

    delete head;
    head = nullptr;
}