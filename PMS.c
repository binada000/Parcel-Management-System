#include <stdio.h>
#include <string.h>

struct Parcel {
    int id;
    char destination[50];
    float weight;
    int isDelivered;
};

struct Vehicle {
    int id;
    char type[30];
    int capacity;
    int isAvailable;
};

struct Rider {
    int id;
    char name[50];
    char phone[15];
    int isAvailable;
    char assignedZone[50];
};

struct Hub {
    int id;
    char zoneName[50];
    char manager[50];
};

struct Route {
    int routeId;
    int parcelId;
    int riderId;
    int vehicleId;
    float estimatedDistance;
    int isCompleted;
};

// Global Arrays
struct Parcel parcels[100];
int pCount = 0;

struct Vehicle vehicles[100];
int vCount = 0;

struct Rider riders[100];
int rCount = 0;

struct Hub hubs[100];
int hCount = 0;

struct Route routes[100];
int rtCount = 0;

// ========================================
// SECTION 1 - MANAGE PARCELS
// ========================================

// for adding parcel
void addParcel() {
    printf("Enter Parcel ID: ");
    scanf("%d", &parcels[pCount].id);

    printf("Enter Destination Zone: ");
    scanf(" %[^\n]", parcels[pCount].destination);

    printf("Enter Weight (kg): ");
    scanf("%f", &parcels[pCount].weight);

    parcels[pCount].isDelivered = 0;
    pCount++;

    printf("Parcel added successfully!\n");
}

// print all parcels
void viewParcels() {
    printf("\n--- Parcel List ---\n");
    for (int i = 0; i < pCount; i++) {
        printf("ID: %d | Dest: %s | Weight: %.2fkg | Status: %s\n",
               parcels[i].id, parcels[i].destination, parcels[i].weight,
               parcels[i].isDelivered == 1 ? "Delivered" : "Not Delivered");
    }
}

// search parcel using ID
void searchParcel() {
    int sId, found = 0;
    printf("Enter Parcel ID to search: ");
    scanf("%d", &sId);

    for (int i = 0; i < pCount; i++) {
        if (parcels[i].id == sId) {
            printf("Found - Dest: %s, Weight: %.2fkg | Status: %s\n",
                   parcels[i].destination, parcels[i].weight,
                   parcels[i].isDelivered == 1 ? "Delivered" : "Not Delivered");
            found = 1; break;
        }
    }
    if (!found) printf("Parcel not found.\n");
}

// change parcel status to delivered
void updateParcelStatus() {
    int sId;
    printf("Enter Parcel ID to mark as Delivered: ");
    scanf("%d", &sId);

    for (int i = 0; i < pCount; i++) {
        if (parcels[i].id == sId) {
            parcels[i].isDelivered = 1;
            printf("Parcel marked as Delivered!\n");
            return;
        }
    }
    printf("Parcel not found.\n");
}

// remove parcel from list
void removeParcel() {
    int sId, foundIndex = -1;
    printf("Enter Parcel ID to remove: ");
    scanf("%d", &sId);

    for (int i = 0; i < pCount; i++) {
        if (parcels[i].id == sId) { foundIndex = i; break; }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < pCount - 1; i++) parcels[i] = parcels[i + 1];
        pCount--;
        printf("Parcel ID %d has been removed successfully!\n", sId);
    } else {
        printf("Parcel not found. Cannot remove.\n");
    }
}

// ========================================
// SECTION 2 - MANAGE VEHICLES
// ========================================

// for adding a vehicle
void addVehicle() {
    printf("Enter Vehicle ID: ");
    scanf("%d", &vehicles[vCount].id);
    printf("Enter Vehicle Type (Van/Bike): ");
    scanf(" %[^\n]", vehicles[vCount].type);
    printf("Enter Capacity (kg): ");
    scanf("%d", &vehicles[vCount].capacity);
    vehicles[vCount].isAvailable = 1;
    vCount++;
    printf("Vehicle registered!\n");
}

// print all vehicles
void viewVehicles() {
    printf("\n--- Vehicle Fleet ---\n");
    for (int i = 0; i < vCount; i++) {
        printf("ID: %d | Type: %s | Capacity: %dkg | Available: %s\n",
               vehicles[i].id, vehicles[i].type, vehicles[i].capacity,
               vehicles[i].isAvailable == 1 ? "Yes" : "No");
    }
}

// search vehicle using ID
void searchVehicle() {
    int sId, found = 0;
    printf("Enter Vehicle ID to search: ");
    scanf("%d", &sId);

    for (int i = 0; i < vCount; i++) {
        if (vehicles[i].id == sId) {
            printf("Found - Type: %s, Capacity: %dkg | Available: %s\n",
                   vehicles[i].type, vehicles[i].capacity, vehicles[i].isAvailable == 1 ? "Yes" : "No");
            found = 1; break;
        }
    }
    if (!found) printf("Vehicle not found.\n");
}

// change vehicle available or not
void updateVehicleStatus() {
    int sId, found = 0;
    printf("Enter Vehicle ID to update status: ");
    scanf("%d", &sId);

    for (int i = 0; i < vCount; i++) {
        if (vehicles[i].id == sId) {
            found = 1;
            printf("Current Status: %s\n", vehicles[i].isAvailable == 1 ? "Available" : "Unavailable");
            printf("Enter New Status (1 for Available, 0 for Unavailable): ");
            scanf("%d", &vehicles[i].isAvailable);
            printf("Vehicle availability status updated successfully!\n");
            break;
        }
    }
    if (!found) printf("Vehicle not found.\n");
}

// show only van or bike
void filterVehiclesByType() {
    char searchType[30];
    int found = 0;
    printf("Enter Vehicle Type to filter by (e.g., Van/Bike): ");
    scanf(" %[^\n]", searchType);

    printf("\n--- Filtered Vehicle Fleet (%s) ---\n", searchType);
    for (int i = 0; i < vCount; i++) {
        if (strcmp(vehicles[i].type, searchType) == 0) {
            printf("ID: %d | Type: %s | Capacity: %dkg | Available: %s\n",
                   vehicles[i].id, vehicles[i].type, vehicles[i].capacity,
                   vehicles[i].isAvailable == 1 ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) printf("No vehicles found matching type '%s'.\n", searchType);
}

// ========================================
// SECTION 3 - MANAGE RIDERS
// ========================================

// for adding rider, zone is unassigned at first
void addRider() {
    printf("Enter Rider ID: ");
    scanf("%d", &riders[rCount].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", riders[rCount].name);
    printf("Enter Phone: ");
    scanf(" %[^\n]", riders[rCount].phone);
    riders[rCount].isAvailable = 1;
    strcpy(riders[rCount].assignedZone, "Unassigned");
    rCount++;
    printf("Rider added successfully!\n");
}

// print all riders
void viewRiders() {
    printf("\n--- Rider List ---\n");
    for (int i = 0; i < rCount; i++) {
        printf("ID: %d | Name: %s | Phone: %s | Available: %s | Zone: %s\n",
               riders[i].id, riders[i].name, riders[i].phone,
               riders[i].isAvailable == 1 ? "Yes" : "No", riders[i].assignedZone);
    }
}

// search rider using ID
void searchRider() {
    int sId, found = 0;
    printf("Enter Rider ID to search: ");
    scanf("%d", &sId);

    for (int i = 0; i < rCount; i++) {
        if (riders[i].id == sId) {
            printf("Found - Name: %s, Phone: %s | Zone: %s\n", riders[i].name, riders[i].phone, riders[i].assignedZone);
            found = 1; break;
        }
    }
    if (!found) printf("Rider not found.\n");
}

// give a zone to the rider
void assignRiderToZone() {
    int sId, found = 0;
    printf("Enter Rider ID to assign a zone: ");
    scanf("%d", &sId);

    for (int i = 0; i < rCount; i++) {
        if (riders[i].id == sId) {
            found = 1;
            printf("Current Zone: %s\n", riders[i].assignedZone);
            printf("Enter New Zone Name: ");
            scanf(" %[^\n]", riders[i].assignedZone);
            printf("Rider assigned to Zone '%s' successfully!\n", riders[i].assignedZone);
            break;
        }
    }
    if (!found) printf("Rider not found.\n");
}

// remove rider from list
void removeRider() {
    int sId, foundIndex = -1;
    printf("Enter Rider ID to remove: ");
    scanf("%d", &sId);

    for (int i = 0; i < rCount; i++) {
        if (riders[i].id == sId) { foundIndex = i; break; }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < rCount - 1; i++) riders[i] = riders[i + 1];
        rCount--;
        printf("Rider ID %d has been removed successfully!\n", sId);
    } else {
        printf("Rider not found. Cannot remove.\n");
    }
}

// ========================================
// SECTION 4 - MANAGE CITY HUBS
// ========================================

// for adding a hub
void addHub() {
    printf("Enter Hub ID: ");
    scanf("%d", &hubs[hCount].id);
    printf("Enter Zone Name: ");
    scanf(" %[^\n]", hubs[hCount].zoneName);
    printf("Enter Manager Name: ");
    scanf(" %[^\n]", hubs[hCount].manager);
    hCount++;
    printf("Hub established successfully!\n");
}

// print all hubs
void viewHubs() {
    printf("\n--- City Hubs ---\n");
    for (int i = 0; i < hCount; i++) {
        printf("ID: %d | Zone: %s | Manager: %s\n", hubs[i].id, hubs[i].zoneName, hubs[i].manager);
    }
}

// search hub using ID
void searchHub() {
    int sId, found = 0;
    printf("Enter Hub ID to search: ");
    scanf("%d", &sId);

    for (int i = 0; i < hCount; i++) {
        if (hubs[i].id == sId) {
            printf("Found - Zone: %s, Manager: %s\n", hubs[i].zoneName, hubs[i].manager);
            found = 1; break;
        }
    }
    if (!found) printf("Hub not found.\n");
}

// edit hub zone and manager name
void updateHubManager() {
    int sId, found = 0;
    printf("Enter Hub ID to update Details: ");
    scanf("%d", &sId);

    for (int i = 0; i < hCount; i++) {
        if (hubs[i].id == sId) {
            found = 1;
            printf("Current Zone Name: %s\n", hubs[i].zoneName);
            printf("Enter New Zone Name: ");
            scanf(" %[^\n]", hubs[i].zoneName);
            printf("Current Manager Name: %s\n", hubs[i].manager);
            printf("Enter New Manager Name: ");
            scanf(" %[^\n]", hubs[i].manager);
            printf("Hub Details updated successfully!\n");
            break;
        }
    }
    if (!found) printf("Hub not found.\n");
}

// remove hub from list
void removeHub() {
    int sId, foundIndex = -1;
    printf("Enter Hub ID to remove: ");
    scanf("%d", &sId);

    for (int i = 0; i < hCount; i++) {
        if (hubs[i].id == sId) { foundIndex = i; break; }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < hCount - 1; i++) hubs[i] = hubs[i + 1];
        hCount--;
        printf("Hub ID %d has been removed successfully!\n", sId);
    } else {
        printf("Hub not found. Cannot remove.\n");
    }
}

// ========================================
// SECTION 5 - MANAGE DELIVERY ROUTES
// ========================================

// make a new route with parcel rider and vehicle
void createRoute() {
    printf("Enter Route ID: ");
    scanf("%d", &routes[rtCount].routeId);
    printf("Enter Parcel ID: ");
    scanf("%d", &routes[rtCount].parcelId);
    printf("Enter Rider ID: ");
    scanf("%d", &routes[rtCount].riderId);
    printf("Enter Vehicle ID: ");
    scanf("%d", &routes[rtCount].vehicleId);
    printf("Enter Est. Distance (km): ");
    scanf("%f", &routes[rtCount].estimatedDistance);

    routes[rtCount].isCompleted = 0;
    rtCount++;
    printf("Delivery Route Assigned!\n");
}

// print all routes
void viewRoutes() {
    printf("\n--- Active Delivery Routes ---\n");
    for (int i = 0; i < rtCount; i++) {
        char statusStr[20];
        if (routes[i].isCompleted == 1) strcpy(statusStr, "Delivered");
        else strcpy(statusStr, "Not Delivered");

        printf("Route ID: %d | Parcel: %d | Rider: %d | Vehicle: %d | Dist: %.2fkm | Status: %s\n",
               routes[i].routeId, routes[i].parcelId, routes[i].riderId,
               routes[i].vehicleId, routes[i].estimatedDistance, statusStr);
    }
}

// get total cost using distance
void calculateDeliveryCost() {
    int sId, found = 0;
    printf("Enter Route ID to calculate Cost: ");
    scanf("%d", &sId);

    for (int i = 0; i < rtCount; i++) {
        if (routes[i].routeId == sId) {
            found = 1;
            float baseCost = 200.0, costPerKm = 50.0, totalCost;
            totalCost = baseCost + (routes[i].estimatedDistance * costPerKm);

            printf("\n===== DELIVERY COST ESTIMATION =====\n");
            printf("Route ID           : %d\n", routes[i].routeId);
            printf("Parcel ID          : %d\n", routes[i].parcelId);
            printf("Estimated Distance : %.2f km\n", routes[i].estimatedDistance);
            printf("------------------------------------\n");
            printf("Base Fare          : LKR %.2f\n", baseCost);
            printf("Distance Fare      : LKR %.2f\n", routes[i].estimatedDistance * costPerKm);
            printf("Total Delivery Cost: LKR %.2f\n", totalCost);
            printf("====================================\n");
            break;
        }
    }
    if (!found) printf("Route not found.\n");
}

// set route as done, parcel also becomes delivered
void markRouteComplete() {
    int sId, foundRoute = 0, foundParcel = 0;
    printf("Enter Route ID to mark as Completed: ");
    scanf("%d", &sId);

    for (int i = 0; i < rtCount; i++) {
        if (routes[i].routeId == sId) {
            foundRoute = 1;
            routes[i].isCompleted = 1;
            int targetParcelId = routes[i].parcelId;

            for (int j = 0; j < pCount; j++) {
                if (parcels[j].id == targetParcelId) {
                    parcels[j].isDelivered = 1;
                    foundParcel = 1; break;
                }
            }

            if (foundParcel) {
                printf("Route ID %d marked as COMPLETED and connected Parcel ID %d is DELIVERED!\n", sId, targetParcelId);
            } else {
                printf("Route ID %d marked as COMPLETED!\n", sId);
                printf("[WARNING] Connected Parcel ID %d does not exist in 'Manage Parcels'.\n", targetParcelId);
            }
            break;
        }
    }
    if (!foundRoute) printf("Route not found.\n");
}

// sort routes from shortest to longest distance
void sortRoutesByDistance() {
    if (rtCount == 0) { printf("No routes available to sort.\n"); return; }
    struct Route temp;

    for (int i = 0; i < rtCount - 1; i++) {
        for (int j = 0; j < rtCount - i - 1; j++) {
            if (routes[j].estimatedDistance > routes[j + 1].estimatedDistance) {
                temp = routes[j]; routes[j] = routes[j + 1]; routes[j + 1] = temp;
            }
        }
    }

    printf("\n--- Routes Sorted By Distance (Shortest First) ---\n");
    for (int i = 0; i < rtCount; i++) {
        char statusStr[20];
        if (routes[i].isCompleted == 1) strcpy(statusStr, "Delivered");
        else strcpy(statusStr, "Not Delivered");

        printf("Route ID: %d | Parcel: %d | Rider: %d | Vehicle: %d | Dist: %.2fkm | Status: %s\n",
               routes[i].routeId, routes[i].parcelId, routes[i].riderId,
               routes[i].vehicleId, routes[i].estimatedDistance, statusStr);
    }
}

int main() {
    int choice;

    do {
        printf("\n=============================================\n");
        printf(" SMART CITY LOGISTICS & DELIVERY SYSTEM \n");
        printf("=============================================\n");
        printf("1. Manage Parcels\n");
        printf("2. Manage Vehicles\n");
        printf("3. Manage Riders\n");
        printf("4. Manage City Hubs\n");
        printf("5. Manage Delivery Routes\n");
        printf("0. Exit System\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\n-- Parcels --\n1. Add 2. View 3. Search 4. Update Status 5. Remove\nSelect: ");
                int pChoice; scanf("%d", &pChoice);
                if (pChoice == 1) addParcel();
                else if (pChoice == 2) viewParcels();
                else if (pChoice == 3) searchParcel();
                else if (pChoice == 4) updateParcelStatus();
                else if (pChoice == 5) removeParcel();
                break;

            case 2:
                printf("\n-- Vehicles --\n1. Add 2. View 3. Search 4. Update Status 5. Filter\nSelect: ");
                int vChoice; scanf("%d", &vChoice);
                if (vChoice == 1) addVehicle();
                else if (vChoice == 2) viewVehicles();
                else if (vChoice == 3) searchVehicle();
                else if (vChoice == 4) updateVehicleStatus();
                else if (vChoice == 5) filterVehiclesByType();
                break;

            case 3:
                printf("\n-- Riders --\n1. Add 2. View 3. Search 4. Assign Zone 5. Remove\nSelect: ");
                int rChoice; scanf("%d", &rChoice);
                if (rChoice == 1) addRider();
                else if (rChoice == 2) viewRiders();
                else if (rChoice == 3) searchRider();
                else if (rChoice == 4) assignRiderToZone();
                else if (rChoice == 5) removeRider();
                break;

            case 4:
                printf("\n-- Hubs --\n1. Add 2. View 3. Search 4. Update Manager & Zone 5. Remove Hub\nSelect: ");
                int hChoice; scanf("%d", &hChoice);
                if (hChoice == 1) addHub();
                else if (hChoice == 2) viewHubs();
                else if (hChoice == 3) searchHub();
                else if (hChoice == 4) updateHubManager();
                else if (hChoice == 5) removeHub();
                break;

            case 5:
                printf("\n-- Routes --\n1. Create 2. View 3. Calc Cost 4. Complete 5. Sort\nSelect: ");
                int rtChoice; scanf("%d", &rtChoice);
                if (rtChoice == 1) createRoute();
                else if (rtChoice == 2) viewRoutes();
                else if (rtChoice == 3) calculateDeliveryCost();
                else if (rtChoice == 4) markRouteComplete();
                else if (rtChoice == 5) sortRoutesByDistance();
                break;

            case 0:
                printf("Exiting System...\n"); break;
            default:
                printf("Invalid Choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}