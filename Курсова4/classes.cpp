#include "classes.h"
#include <fstream>
#include <sstream>
#include <iostream>

Database::Database(const std::string& vehicles, const std::string& drivers, const std::string& routes, const std::string& mileage, const std::string& repair, const std::string& employees, const std::string& cargo)
            : vehicles_file(vehicles), drivers_file(drivers), routes_file(routes), mileage_file(mileage), repair_file(repair), employees_file(employees), cargo_file(cargo) {}


std::vector<Vehicle> Database::getVehicles() {
    std::vector<Vehicle> vehicles;
    std::ifstream in(vehicles_file);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            Vehicle vehicle;
            if (iss >> vehicle.vehicle_id >> vehicle.type >> vehicle.make >> vehicle.model >> vehicle.capacity >> vehicle.weight_capacity >> vehicle.fuel_type >> vehicle.mileage) {
                vehicles.push_back(vehicle);
            }
        }
        in.close();
    }
    return vehicles;
}

std::vector<Driver> Database::getDrivers() {
    std::vector<Driver> drivers;
    std::ifstream in(drivers_file);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            Driver driver;
            if (iss >> driver.driver_id >> driver.name) {
                int vehicle_id;
                while (iss >> vehicle_id) {
                    driver.vehicle_ids.push_back(vehicle_id);
                }
                drivers.push_back(driver);
            }
        }
        in.close();
    }
    return drivers;
}

std::vector<MileageRecord> Database::getMileageRecords() {
    std::vector<MileageRecord> records;
    std::ifstream in("mileage.txt");
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            MileageRecord record;
            if (iss >> record.vehicle_id >> record.type >> record.make >> record.date >> record.mileage) {
                records.push_back(record);
            }
        }
        in.close();
    }
    return records;
}

std::vector<Repair> Database::loadRepairsFromFile() {
    std::vector<Repair> repairs;

    std::ifstream in("repair.txt");
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            int vehicle_id;
            std::string type;
            std::string make;
            std::string repair_date;
            double cost;

            if (iss >> vehicle_id >> type >> make >> repair_date >> cost) {
                Repair repair(vehicle_id, type, make, repair_date, cost);
                repairs.push_back(repair);
            }
        }
        in.close();
    }

    return repairs;
}

std::vector<Employee> Database:: loadEmployeesFromFile() {
    std::vector<Employee> employees;
    std::ifstream in("employees.txt");
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            Employee employee;
            if (iss >> employee.id >> employee.name >> employee.position >> employee.managerId) {
                employees.push_back(employee);
            }
        }
        in.close();
    }
    return employees;
}

std::vector<CargoTransportation> Database::getCargoTransportationsFromFile() {

    std::vector<CargoTransportation> cargoTransportations;
    std::ifstream in("cargo.txt");
    if (in.is_open()) {
        int id, vehicle;
        std::string cargo, date;
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            if (iss >> id >> vehicle >> cargo >> date) {
                cargoTransportations.emplace_back(id, vehicle, cargo, date);
            }
        }
        in.close();
    }

    return cargoTransportations;
}


void Database::addVehicle(const Vehicle& vehicle) {
    std::ofstream out(vehicles_file, std::ios::app);
    if (out.is_open()) {
        out << vehicle.vehicle_id << " " << vehicle.type << " " << vehicle.make << " " << vehicle.model << " "
            << vehicle.capacity << " " << vehicle.weight_capacity << " " << vehicle.fuel_type << " " << vehicle.mileage << std::endl;
        out.close();
        std::cout << "Vehicle added successfully." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << vehicles_file << std::endl;
    }
}

void Database::addDriver(const Driver& driver) {
    std::ofstream out(drivers_file, std::ios::app);
    if (out.is_open()) {
        out << driver.driver_id << " " << driver.name << " ";
        for (int vehicleId : driver.vehicle_ids) {
            out << vehicleId << " ";
        }
        out << std::endl;
        out.close();
        std::cout << "Driver added successfully." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << drivers_file << std::endl;
    }
}

std::vector<Driver> Database::getDriversByVehicleId(int vehicle_id) {
    std::vector<Driver> drivers;
    std::vector<Driver> allDrivers = getDrivers();
    for (const Driver& driver : allDrivers) {
        if (std::find(driver.vehicle_ids.begin(), driver.vehicle_ids.end(), vehicle_id) != driver.vehicle_ids.end()) {
            drivers.push_back(driver);
        }
    }
    return drivers;
}

std::vector<Route> Database::getRoutes() {
    std::vector<Route> routes;
    std::ifstream in(routes_file);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            Route route;
            std::string vehicleIds;
            if (iss >> route.route_id >> route.name >> route.start_point >> route.end_point >> route.distance >> vehicleIds) {
                std::istringstream vehicleIss(vehicleIds);
                int vehicleId;
                while (vehicleIss >> vehicleId) {
                    route.vehicle_ids.push_back(vehicleId);
                }
                routes.push_back(route);
            }
        }
        in.close();
    }
    return routes;
}

void Database::addRoute(const Route& route) {
    std::ofstream out(routes_file, std::ios::app);
    if (out.is_open()) {
        out << route.route_id << " " << route.name << " " << route.start_point << " " << route.end_point << " "
            << route.distance << " ";
        for (int vehicleId : route.vehicle_ids) {
            out << vehicleId << " ";
        }
        out << std::endl;
        out.close();
        std::cout << "Route added successfully." << std::endl;
    }
    else {
        std::cerr << "Error opening file: " << routes_file << std::endl;
    }
}
int Database::getTotalDriverCount() {
    std::vector<Driver> drivers = getDrivers();
    return drivers.size();
};
