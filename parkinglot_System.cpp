#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/* ---------- Vehicle ---------- */
class Vehicle {
public:
    string number;
    string type;

    Vehicle(string num, string t) {
        number = num;
        type = t;
    }
};

/* ---------- Parking Slot ---------- */
class ParkingSlot {
public:
    int id;
    bool occupied;
    Vehicle* vehicle;

    ParkingSlot(int i) {
        id = i;
        occupied = false;
        vehicle = nullptr;
    }
};

/* ---------- Parking Lot ---------- */
class ParkingLot {
private:
    vector<ParkingSlot> slots;
    unordered_map<string, int> parked;  // vehicleNumber -> slotId

public:
    ParkingLot(int capacity) {
        for (int i = 1; i <= capacity; i++) {
            slots.push_back(ParkingSlot(i));
        }
    }

    void parkVehicle(Vehicle* v) {
        for (int i = 0; i < slots.size(); i++) {
            if (!slots[i].occupied) {
                slots[i].occupied = true;
                slots[i].vehicle = v;
                parked[v->number] = slots[i].id;

                cout << v->type << " (" << v->number
                     << ") parked at slot " << slots[i].id << endl;
                return;
            }
        }
        cout << "Parking Lot is Full!" << endl;
    }

    void removeVehicle(string vehicleNumber) {
        if (parked.find(vehicleNumber) == parked.end()) {
            cout << "Vehicle not found!" << endl;
            return;
        }

        int slotId = parked[vehicleNumber];
        slots[slotId - 1].occupied = false;
        slots[slotId - 1].vehicle = nullptr;
        parked.erase(vehicleNumber);

        cout << "Vehicle " << vehicleNumber
             << " exited from slot " << slotId << endl;
    }

    void display() {
        cout << "\n--- Parking Lot Status ---\n";
        for (int i = 0; i < slots.size(); i++) {
            if (slots[i].occupied) {
                cout << "Slot " << slots[i].id << ": "
                     << slots[i].vehicle->type << " ("
                     << slots[i].vehicle->number << ")\n";
            } else {
                cout << "Slot " << slots[i].id << ": Empty\n";
            }
        }
    }
};

int main() {
    ParkingLot lot(4);

    Vehicle* car1 = new Vehicle("Ap01AB1111", "Car");
    Vehicle* bike1 = new Vehicle("Ap02XY2222", "Bike");
    Vehicle* car2 = new Vehicle("AP03CD3333", "Car");

    lot.parkVehicle(car1);
    lot.parkVehicle(bike1);
    lot.parkVehicle(car2);

    lot.display();

    lot.removeVehicle("AP02XY2222");
    lot.display();

    return 0;
}
