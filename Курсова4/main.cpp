#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <unordered_map>
#include "classes.h"

void showMenu() {
    std::cout << "1. Show vehicles" << std::endl;
    std::cout << "2. Show drivers" << std::endl;
    std::cout << "3. Add vehicle" << std::endl;
    std::cout << "4. Add driver" << std::endl;
    std::cout << "5. Show drivers by vehicle ID" << std::endl;
    std::cout << "6. Show Routes" << std::endl;
    std::cout << "7. Show mileage by date" << std::endl;
    std::cout << "8. Show repairs" << std::endl;
    std::cout << "9. Show employee hierarchy" << std::endl; // New option for displaying employee hierarchy
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void displayVehicles(const std::vector<Vehicle>& vehicles) {
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| ID  |    Type     |    Make        |    Model    |  Capacity  |  Weight Capacity  |  Fuel Type  |    Mileage    |" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------" << std::endl;

    for (const Vehicle& vehicle : vehicles) {
        std::cout << "| " << std::setw(3) << vehicle.vehicle_id << " |";
        std::cout << " " << std::setw(12) << vehicle.type << " |";
        std::cout << " " << std::setw(17) << vehicle.make << " |";
        std::cout << " " << std::setw(12) << vehicle.model << " |";
        std::cout << " " << std::setw(10) << vehicle.capacity << " |";
        std::cout << " " << std::setw(17) << vehicle.weight_capacity << " |";
        std::cout << " " << std::setw(11) << vehicle.fuel_type << " |";
        std::cout << " " << std::setw(12) << vehicle.mileage << " |";
        std::cout << std::endl;
    }

    std::cout << "--------------------------------------------------------------------------------------------------------------------------------" << std::endl;
}


void displayDrivers(const std::vector<Driver>& drivers) {
    std::cout << "----------------------------------" << std::endl;
    std::cout << "| Driver ID  |    Name           |" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    for (const Driver& driver : drivers) {
        std::cout << "| " << std::setw(10) << driver.driver_id << " |";
        std::cout << " " << std::setw(17) << driver.name << " |";
        std::cout << std::endl;
    }

    std::cout << "----------------------------------" << std::endl;
}

void displayDrivers(const std::vector<Driver>& drivers, const std::vector<Vehicle>& vehicles) {
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "| Driver ID  |    Name    |   Vehicle ID   |    Make    |    Type    |" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    for (const Driver& driver : drivers) {
        std::cout << "| " << std::setw(10) << driver.driver_id << " |";
        std::cout << " " << std::setw(10) << driver.name << " |";

        if (driver.vehicle_ids.empty()) {
            std::cout << " " << std::setw(13) << "-" << " |"; // Виводимо тире, якщо немає транспортних засобів
            std::cout << " " << std::setw(10) << "-" << " |";
            std::cout << " " << std::setw(10) << "-" << " |";
            std::cout << std::endl;
        }
        else {
            for (int vehicleId : driver.vehicle_ids) {
                auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
                    return vehicle.vehicle_id == vehicleId;
                    });

                if (vehicleIt != vehicles.end()) {
                    const Vehicle& vehicle = *vehicleIt;
                    std::cout << " " << std::setw(13) << vehicle.vehicle_id << " |";
                    std::cout << " " << std::setw(10) << vehicle.make << " |";
                    std::cout << " " << std::setw(10) << vehicle.type << " |";
                    std::cout << std::endl;
                }
            }
        }
    }

    std::cout << "------------------------------------------------------------------------" << std::endl;
}

void displayRoutes(const std::vector<Route>& routes, const std::vector<Vehicle>& vehicles) {
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
    std::cout << "| Route ID |       Name       |   Start Point   |    End Point    | Distance |      Vehicle IDs      |" << std::endl;
    std::cout << "-------------------------------------------------------------------------------------" << std::endl;

    for (const Route& route : routes) {
        std::cout << "| " << std::setw(8) << route.route_id << " |";
        std::cout << " " << std::setw(16) << route.name << " |";
        std::cout << " " << std::setw(15) << route.start_point << " |";
        std::cout << " " << std::setw(15) << route.end_point << " |";
        std::cout << " " << std::setw(8) << route.distance << " |";
        std::cout << " ";

        if (!route.vehicle_ids.empty()) {
            for (size_t i = 0; i < route.vehicle_ids.size(); ++i) {
                auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
                    return vehicle.vehicle_id == route.vehicle_ids[i];
                    });
                if (vehicleIt != vehicles.end()) {
                    const Vehicle& vehicle = *vehicleIt;
                    std::cout << vehicle.vehicle_id;
                    if (i < route.vehicle_ids.size() - 1) {
                        std::cout << ", ";
                    }
                }
            }
        }

        std::cout << std::endl;
    }

    std::cout << "-------------------------------------------------------------------------------------" << std::endl;
}


void displayMileage(const std::vector<MileageRecord>& records) {
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "| Vehicle ID | Type      | Make              | Date      | Mileage |" << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;

    for (const MileageRecord& record : records) {
        std::cout << "| " << std::setw(10) << record.vehicle_id << " |";
        std::cout << " " << std::setw(9) << record.type << " |";
        std::cout << " " << std::setw(17) << record.make << " |";
        std::cout << " " << std::setw(10) << record.date << " |";
        std::cout << " " << std::setw(7) << record.mileage << " |";
        std::cout << std::endl;
    }

    std::cout << "---------------------------------------------------------" << std::endl;
}

void displayRepairs(const std::vector<Repair>& repairs) {
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "| Vehicle ID  |     Type      |      Make       |   Date    | Cost  |" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    for (const Repair& repair : repairs) {
        std::cout << "| " << std::setw(11) << std::left << repair.vehicle_id << " |";
        std::cout << " " << std::setw(13) << std::left << repair.type << " |";
        std::cout << " " << std::setw(15) << std::left << repair.make << " |";
        std::cout << " " << std::setw(9) << std::left << repair.repair_date << " |";
        std::cout << " " << std::setw(5) << std::left << repair.cost << " |";
        std::cout << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
}

void displayInfo(const Employee& employee, const std::vector<Employee>& employees) {
    std::cout << "| " << std::setw(8) << employee.id << " |";
    std::cout << " " << std::setw(15) << employee.name << " |";
    std::cout << " " << std::setw(8) << employee.position << " |";
    std::cout << " " << std::setw(13) << employee.managerId << " |";
    std::cout << std::endl;
}

void displayHierarchy(const std::vector<Employee>& employees) {
    std::cout << "Employee Hierarchy:" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "| ID      | Name           | Position | Manager ID   |" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    for (const Employee& employee : employees) {
        std::cout << "| " << std::setw(8) << employee.id << " |";
        std::cout << " " << std::setw(15) << employee.name << " |";
        std::cout << " " << std::setw(8) << employee.position << " |";
        std::cout << " " << std::setw(13) << employee.managerId << " |";
        std::cout << std::endl;

        std::vector<Employee> subordinates;
        for (const Employee& subordinate : employees) {
            if (subordinate.managerId == employee.id) {
                subordinates.push_back(subordinate);
            }
        }

        if (!subordinates.empty()) {
            std::cout << "Subordinates:" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            std::cout << "| ID      | Name           | Position | Manager ID   |" << std::endl;
            std::cout << "-------------------------------------------------------" << std::endl;
            for (const Employee& subordinate : subordinates) {
                displayInfo(subordinate, employees);
            }
            std::cout << "-------------------------------------------------------" << std::endl;
        }
    }
}

void getVehicleInformation(Database& db) {
    std::vector<Vehicle> vehicles = db.getVehicles();

    std::map<std::string, int> categoryCount;
    int totalVehicles = 0;

    for (const Vehicle& vehicle : vehicles) {
        categoryCount[vehicle.type]++;
        totalVehicles++;
    }

    std::cout << "Vehicle Information:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Total Vehicles: " << totalVehicles << std::endl;
    std::cout << "-------------------------" << std::endl;

    for (const auto& entry : categoryCount) {
        std::string category = entry.first;
        int count = entry.second;

        std::cout << "Category: " << category << std::endl;
        std::cout << "Count: " << count << std::endl;
        std::cout << "-------------------------" << std::endl;

        // Search vehicles by category
        std::cout << "Vehicles in this category:" << std::endl;
        for (const Vehicle& vehicle : vehicles) {
            if (vehicle.type == category) {
                std::cout << "Vehicle ID: " << vehicle.vehicle_id << std::endl;
                std::cout << "Make: " << vehicle.make << std::endl;
                std::cout << "Model: " << vehicle.model << std::endl;
                std::cout << "Capacity: " << vehicle.capacity << std::endl;
                std::cout << "Weight Capacity: " << vehicle.weight_capacity << std::endl;
                std::cout << "Fuel Type: " << vehicle.fuel_type << std::endl;
                std::cout << "Mileage: " << vehicle.mileage << std::endl;
                std::cout << "-------------------------" << std::endl;
            }
        }
    }
}

void displayGarageInformation(Database& db) {
    std::vector<Vehicle> vehicles = db.getVehicles();
    std::cout << "Garage Information:" << std::endl;

    // Total vehicles
    int totalVehicles = vehicles.size();
    std::cout << "Total Vehicles: " << totalVehicles << std::endl;

    // Vehicles by category
    std::unordered_map<std::string, int> categoryCount;
    for (const Vehicle& vehicle : vehicles) {
        categoryCount[vehicle.type]++;
    }

    std::cout << "Vehicles by Category:" << std::endl;
    for (const auto& entry : categoryCount) {
        std::string category = entry.first;
        int count = entry.second;

        std::cout << "Category: " << category << std::endl;
        std::cout << "Count: " << count << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}

void displayTransportDistribution(const std::vector<Driver>& drivers, const std::vector<Vehicle>& vehicles) {
    std::unordered_map<std::string, int> categoryCount;

    // Отримати кількість транспортних засобів кожної категорії
    for (const Vehicle& vehicle : vehicles) {
        categoryCount[vehicle.type]++;
    }

    // Отримати розподіл транспорту за водіями
    std::unordered_map<std::string, int> driverCategoryCount;
    for (const Driver& driver : drivers) {
        for (int vehicleId : driver.vehicle_ids) {
            auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(), [&](const Vehicle& vehicle) {
                return vehicle.vehicle_id == vehicleId;
                });

            if (vehicleIt != vehicles.end()) {
                const Vehicle& vehicle = *vehicleIt;
                driverCategoryCount[vehicle.type]++;
            }
        }
    }
}

void displayCargoTransportation(std::vector<CargoTransportation>& cargoTransportations, int vehicleId, const std::string& startDate, const std::string& endDate) {
        std::cout << "Cargo Transportation Information:" << std::endl;
        std::cout << "--------------------------------" << std::endl;

        for (const CargoTransportation& transportation : cargoTransportations) {
            if (transportation.vehicleId == vehicleId && transportation.date >= startDate && transportation.date <= endDate) {
                std::cout << "Transportation ID: " << transportation.transportationId << std::endl;
                std::cout << "Vehicle ID: " << transportation.vehicleId << std::endl;
                std::cout << "Cargo: " << transportation.cargo << std::endl;
                std::cout << "Date: " << transportation.date << std::endl;
                std::cout << "--------------------------------" << std::endl;
            }
        }

        // Вивести інформацію про розподіл транспорту за категоріями
        std::cout << "Transport Distribution:" << std::endl;
        std::cout << "-----------------------" << std::endl;
        for (const auto& entry : categoryCount) {
            std::string category = entry.first;
            int total = entry.second;
            int assigned = driverCategoryCount[category];
            int unassigned = total - assigned;

            std::cout << "Category: " << category << std::endl;
            std::cout << "Total: " << total << std::endl;
            std::cout << "Assigned: " << assigned << std::endl;
            std::cout << "Unassigned: " << unassigned << std::endl;
            std::cout << "-----------------------" << std::endl;
        }
}



std::vector<MileageRecord> searchMileageRecords(const std::vector<MileageRecord>& records, const std::string& searchParam) {
    std::vector<MileageRecord> result;
    for (const MileageRecord& record : records) {
        if (std::to_string(record.vehicle_id) == searchParam || record.type == searchParam || record.date == searchParam) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<Repair> searchRepairs(const std::vector<Repair>& repairs, const std::string& searchParam, const std::string& startDate, const std::string& endDate) {
    std::vector<Repair> result;
    for (const Repair& repair : repairs) {
        if ((std::to_string(repair.vehicle_id) == searchParam || repair.type == searchParam || repair.make == searchParam) &&
            repair.repair_date >= startDate && repair.repair_date <= endDate) {
            result.push_back(repair);
        }
    }
    return result;
}

int main() {
    Database db("vehicles.txt", "drivers.txt", "routes.txt", "mileage.txt", "repair.txt", "employees.txt", "cargo.txt");
    int choice;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 0: {
            // Exit
            return 0;
        }
        case 1: {
            // Show vehicles
            std::vector<Vehicle> vehicles = db.getVehicles();
            displayVehicles(vehicles);
            break;
        }
        case 2: {
            // Show drivers
            std::vector<Driver> drivers = db.getDrivers();
            displayDrivers(drivers);
            // Show total number of drivers
            int totalDriverCount = db.getTotalDriverCount();
            std::cout << "Total number of drivers: " << totalDriverCount << std::endl;
            break;
        }
        case 3: {
            // Add vehicle
            break;
        }
        case 4: {
            // Add driver
            int id;
            std::string name;
            int numVehicles;

            std::cout << "Enter driver ID: ";
            std::cin >> id;
            std::cout << "Enter driver name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter the number of vehicles the driver manages: ";
            std::cin >> numVehicles;

            std::vector<int> vehicleIds;
            for (int i = 0; i < numVehicles; ++i) {
                int vehicleId;
                std::cout << "Enter vehicle ID: ";
                std::cin >> vehicleId;
                vehicleIds.push_back(vehicleId);
            }

            Driver driver(id, name, vehicleIds);
            db.addDriver(driver);
            break;
        }
        case 5: {
            // Show drivers by vehicle ID
            int vehicleId;
            std::cout << "Enter vehicle ID: ";
            std::cin >> vehicleId;
            std::vector<Driver> drivers = db.getDriversByVehicleId(vehicleId);
            displayDrivers(drivers, db.getVehicles());
            break;
        }
        case 6: {
            //Show Routes
            std::vector<Route> routes = db.getRoutes();
            displayRoutes(routes, db.getVehicles());
            break;

        }
        case 7: {
            // Show mileage by date
            std::vector<MileageRecord> records = db.getMileageRecords();
            std::cin.ignore();  // Ігнорувати попередній символ нового рядка
            std::string searchParam;
            std::cout << "Available data only for 01/01/2022-07/01/2022";
            std::cout << "Enter search parameter (id, type, or date): ";
            std::getline(std::cin >> std::ws, searchParam);  // Додайте std::ws перед getline для пропуску зайвих пробілів
            std::vector<MileageRecord> filteredRecords = searchMileageRecords(records, searchParam);
            displayMileage(filteredRecords);
            break;
        }
        case 8: {
            std::vector<Repair> repairs = db.loadRepairsFromFile();

            std::string searchParam;
            std::cout << "Enter search parameter (id, type, make or all for displaying data for all vehicles in exact period): ";
            std::cin.ignore();
            std::getline(std::cin, searchParam);

            std::string startDate, endDate;
            std::cout << "Enter start date (DD.MM.YY): ";
            std::cin >> startDate;
            std::cout << "Enter end date (DD.MM.YY): ";
            std::cin >> endDate;

            std::vector<Repair> searchResults = searchRepairs(repairs, searchParam, startDate, endDate);

            if (searchParam.empty()) {
                if (repairs.empty()) {
                    std::cout << "No repairs found." << std::endl;
                }
                else {
                    std::cout << "Repairs found for all vehicles:" << std::endl;
                    displayRepairs(repairs);
                }
            }
            else if (searchResults.empty()) {
                std::cout << "No repairs found for the specified search criteria." << std::endl;
            }
            else {
                std::cout << "Repairs found for the specified search criteria:" << std::endl;
                displayRepairs(searchResults);
            }

            break;
        }
        case 9: {
            std::vector<Employee> employees = db.loadEmployeesFromFile();

            std::string searchPosition;
            std::cout << "Enter the position to search: ";
            std::getline(std::cin, searchPosition);

            std::vector<Employee> searchResults;
            for (const Employee& employee : employees) {
                if (searchPosition == employee.position) {
                    searchResults.push_back(employee);

                    std::cout << "Employees found with the specified position:" << std::endl;
                    std::cout << "-------------------------------------------------------" << std::endl;
                    std::cout << "| ID      | Name           | Position | Manager ID   |" << std::endl;
                    std::cout << "-------------------------------------------------------" << std::endl;
                    for (const Employee& employee : searchResults) {
                        displayInfo(employee, employees);
                    }
                    std::cout << "-------------------------------------------------------" << std::endl;
                }
            }

            if (searchResults.empty()) {
                std::cout << "No employees found with the specified position." << std::endl;
            }
            displayHierarchy(employees);
            break;
        }

        case 10: {
            // Display garage information
            std::string searchPosition;
            std::cout << "Enter the position to search: ";
            std::getline(std::cin, searchPosition);

            std::vector<Vehicle> vehicles = db.getVehicles();
            displayGarageInformation(db);
            //getVehicleInformation(db);
            break;
        }
        case 11: {
            // Display transport distribution
                std::vector<Driver> drivers = db.getDrivers();
            std::vector<Vehicle> vehicles = db.getVehicles();
            displayTransportDistribution(drivers, vehicles);
            break;
        }

        case 12: {
            std::string startDate, endDate;
            int vehicleId;

            std::cout << "Enter vehicle ID: ";
            std::cin >> vehicleId;
            std::cout << "Enter start date (YYYY-MM-DD): ";
            std::cin >> startDate;
            std::cout << "Enter end date (YYYY-MM-DD): ";
            std::cin >> endDate;

            std::vector<CargoTransportation> cargoTransportations = db.getCargoTransportationsFromFile("cargo.txt");
            displayCargoTransportation(cargoTransportations, vehicleId, startDate, endDate);
            break;
        }

        default: {
            std::cout << "Invalid choice. Try again." << std::endl;
            break;
        }

        }
    }
        return 0;
    
}