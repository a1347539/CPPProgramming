//modify and submit this file only
#include "pa3.h"
#include <iostream>
using namespace std;
//you are NOT allowed to include any additional library; see FAQ

TrainCar* createTrainHead()
{
    return new TrainCar{ HEAD, 0, 0, nullptr, nullptr };
}

bool addCar(TrainCar* head, int position, CarType type, int maxLoad)
{
    if (type == HEAD || position < 1 || maxLoad < 1 || head == nullptr) {
        return false;
    }

    for (; position > 1; head = head->next, position--) {
        // for when position > train length //
        if (head->next == nullptr) {
            return false;
        }
    }
    // now head is the car before the inserting position //

    //check if the car before the inserting position is the last car //
    if (head->next == nullptr) {
        head->next = new TrainCar{ type, maxLoad, 0, head, nullptr };
        return true;
    }

    // for setting the prev pointer //
    head->next->prev = new TrainCar{ type, maxLoad, 0, head, head->next };
    // for setting the next pointer //
    head->next = head->next->prev;
    return true;
}

bool deleteCar(TrainCar* head, int position)
{
    if (position < 1) {
        return false;
    }

    for (; position > 0; head = head->next, position--) {
        if (head->next == nullptr) {
            return false;
        }
    }

    if (head->next == nullptr) {
        // for deleting the last car //
        head->prev->next = nullptr;
    } else {
        // for deleting an in-between car //
        head->prev->next = head->next;
        head->next->prev = head->prev;
    }

    // deallocation // 
    delete head;

    return true;
}

bool swapCar(TrainCar* head, int a, int b)
{
    int interval;
    TrainCar* bcar;

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

    interval = b-a;
    TrainCar* headP = head->prev;
    TrainCar* headN = head->next;

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

void trainInsert(TrainCar *train, TrainCar *sortedTrain, bool ascending) {
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
        if (ascending) {
            if (sortedTrain->next->load > train->load) { break; }
        }
        else {
            if (sortedTrain->next->load < train->load) { break; }
        }
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

void sortTrain(TrainCar* head, bool ascending)
{
    // cout << "debug" << endl;
    TrainCar *sortedTrain = new TrainCar(*head);
    
    sortedTrain->next = nullptr;

    for (TrainCar *i = head->next; i != nullptr; i = i->next) {
        TrainCar *current = new TrainCar(*i);
        current->next = current->prev = nullptr;
        trainInsert(current, sortedTrain, ascending);
    }

    // cout << "all head pointers" << endl;
    // for (TrainCar *i = head; i != nullptr; i = i->next) {
    //     cout << i << " ";
    // }
    // cout << endl << "all sortedTrain pointers" << endl;

    // for (TrainCar *i = sortedTrain; i != nullptr; i = i->next) {
    //     cout << i << " ";
    // };
    // cout << endl;

    deallocateTrain(head->next);
    head->next = nullptr;
    head->next = sortedTrain->next;
    head->next->prev = head;

    // cout << "sortedTrain storing: " << sortedTrain << " head storing: " << head << endl;
    // cout << "sortedTrain address: " << &sortedTrain << " head address: " << &head << endl;

    delete sortedTrain;

}

bool load(TrainCar* head, CarType type, int amount)
{
    if (amount == 0) {
        for (TrainCar *i = head; i->next != nullptr; i = i->next) {
            if (i->type == type) {
                return true;
            }
        }
        return false;
    }

    int maxSpace = 0;

    for (TrainCar *i = head; i != nullptr; i = i->next) {
        if (i->type == type) {
            maxSpace += (i->maxLoad-i->load);
        }
    }

    if (maxSpace == 0) { return false; }
    if (amount > maxSpace) {return false; }

    for (;head != nullptr; head = head->next) {
        if (head->type == type) {
            if (amount > head->maxLoad - head->load) {
                amount -= head->maxLoad - head->load;
                head->load = head->maxLoad;
            } else {
                head->load += amount;
                return true;
            }
        }
    }
    return true;
}

bool unload(TrainCar* head, CarType type, int amount)
{
    int amountOnTrain = 0;

    for (TrainCar *i = head; i != nullptr; i = i->next) {
        if (i->type == type) {
            amountOnTrain += i->load;
        }
    }

    if (amountOnTrain < amount) {
        return false;
    }

    for (; head->next != nullptr; head = head->next);

    for (TrainCar *i = head; i != nullptr; i = i->prev) {
        if (i->type == type) {
            if (amount < i->load) {
                i->load -= amount;
                return true;
            }
            amount -= i->load;
            i->load = 0;
        }
    }
    return true;
}

void addToTheEnd(TrainCar* head, CarType type, int load, int maxLoad) {
    //assuming head exist.
    for (; head->next != nullptr; head = head->next);
    // now I have head as the last element before the nullptr

    head->next = new TrainCar{ type, maxLoad, load, head, nullptr };

}

void printCargoStats(const TrainCar* head)
{
    const char enumToStringMapping[6][8] = {"HEAD", "OIL", "COAL", "WOOD", "STEEL", "SUGAR"};

    TrainCar *tempHead = new TrainCar{ HEAD, 0, 0, nullptr, nullptr };
    bool exist = false;
    int tempTrainLength = 1;

    for (head = head->next; head != nullptr; head = head->next) {
        exist = false;
        for (TrainCar *i = tempHead; i != nullptr; i = i->next) {
            if (i->type == head->type) {
                exist = true;
                i->load += head->load;
                i->maxLoad += head->maxLoad;
            }
        }
        if (!exist) {
            addToTheEnd(tempHead, head->type, head->load, head->maxLoad);
        }
    }

    TrainCar *i;
    for (i = tempHead->next; i->next !=nullptr; i = i->next) {
        cout << enumToStringMapping[i->type] << ":" << i->load << "/" << i->maxLoad << ",";
    }
    cout << enumToStringMapping[i->type] << ":" << i->load << "/" << i->maxLoad << endl;

    deallocateTrain(tempHead);
}

void divide(const TrainCar* head,  TrainCar* results[CARGO_TYPE_COUNT]) 
{
    int dividedTrainNum = 0;
    int counter = 0;
    int existFlag[CARGO_TYPE_COUNT] = {0, 0, 0, 0, 0};
    int typePosition[CARGO_TYPE_COUNT] = {0, 0, 0, 0, 0};

    for (const TrainCar *i = head->next; i != nullptr; i = i->next, counter++) {
        if (existFlag[i->type-1] == 0) {
            results[dividedTrainNum] = createTrainHead(); 
            // dividedTrainNum is the index of the cargo type in results
            // the index is referenced by the cargo type in typePosition.
            typePosition[i->type-1] = dividedTrainNum;
            dividedTrainNum++;
            existFlag[i->type-1] = 1;
        }
        addToTheEnd(results[typePosition[i->type-1]], i->type, i->load, i->maxLoad);
        // cout << existFlag[counter] << endl;
    }

    for (int i = dividedTrainNum; i < CARGO_TYPE_COUNT; i++) {
        results[i] = nullptr;
    }
}

int pow(int x, int power)
{
    int result = 1;
    for (; power > 0; power--, result *= x);
    return result;
}

void findSubset(const TrainCar *head, int sequenceInDec, int depth, int upperBound, int records[]) {
    // depth is the n-th recursion

    // cout << "seq: " << sequenceInDec << " depth: " << depth << " bound: " << upperBound << endl;

    // base case when out of bound
    if (upperBound < 0) {
        return;
    }

    if (upperBound < records[1]) {
        records[0] = sequenceInDec; 
        records[1] = upperBound;
    }

    if (head == nullptr) {
        return;
    }

    // 1 = include, 2 = not include
    // cout << "include" << endl;
    findSubset(head->next, sequenceInDec+1*pow(2, depth), depth+1, upperBound-head->load, records);
    // cout << "not include" << endl;
    findSubset(head->next, sequenceInDec, depth+1, upperBound, records);
}

TrainCar* optimizeForMaximumPossibleCargos(const TrainCar* head, int upperBound)
{
    TrainCar *optTrain = createTrainHead();

    // first: seq, second: upperbound
    int records[2] = { 0, upperBound };
    findSubset(head->next, 0, 0, upperBound, records);
    // cout << records[0] << " " << records[1] << endl;
    int temp = records[0];
    for (TrainCar *i = head->next; i != nullptr; i = i->next, temp = temp/2) {
        if (i->load == 0) {
            addToTheEnd(optTrain, i->type, i->load, i->maxLoad);
            continue;
        }
        if (temp%2 == 1) {
            addToTheEnd(optTrain, i->type, i->load, i->maxLoad);
            //cout << "add car: " << enumToStringMapping[head->type] << head->load << endl;
        }
    }

    return optTrain;
}

void deallocateTrain(TrainCar* head)
{
    if (head == nullptr) {
        return;
    }
    deallocateTrain(head->next);
    if (head != nullptr) { 
        delete head; 
        head = nullptr;
    }
}
