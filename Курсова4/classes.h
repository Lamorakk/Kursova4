#include <string>
#include <vector>

class Vehicle {
public:
    int vehicle_id;
    std::string type;
    std::string make;
    std::string model;
    int capacity;
    int weight_capacity;
    std::string fuel_type;
    int mileage;

    Vehicle() = default;

    Vehicle(int id, const std::string& t, const std::string& mk, const std::string& md, int cap, int weight_cap, const std::string& fuel_t)
        : vehicle_id(id), type(t), make(mk), model(md), capacity(cap), weight_capacity(weight_cap), fuel_type(fuel_t) {}
};

class Driver {
public:
    int driver_id;
    std::string name;
    std::vector<int> vehicle_ids;

    Driver() = default;

    Driver(int id, const std::string& n, const std::vector<int>& v_ids)
        : driver_id(id), name(n), vehicle_ids(v_ids) {}
};

class Employee {
public:
    int id;
    std::string name;
    std::string position;
    int managerId;

    Employee() = default;

    Employee(int empId, const std::string& empName, const std::string& empPosition, int empManagerId)
        : id(empId), name(empName), position(empPosition), managerId(empManagerId) {}
};
class Route {
public:
    int route_id;
    std::string name;
    std::string start_point;
    std::string end_point;
    int distance;
    std::vector<int> vehicle_ids;

    Route() = default;

    Route(int id, const std::string& n, const std::string& start, const std::string& end, int dist, const std::vector<int>& v_ids)
        : route_id(id), name(n), start_point(start), end_point(end), distance(dist), vehicle_ids(v_ids) {}
};

class MileageRecord {
public:
    int vehicle_id;
    std::string type;
    std::string make;
    std::string date;
    int mileage;

    MileageRecord() = default;

    MileageRecord(int id, const std::string& t, const std::string& m, const std::string& d, int mile)
        : vehicle_id(id), type(t), make(m), date(d), mileage(mile) {}
};

class Repair {
public:
    int vehicle_id;
    std::string type;
    std::string make;
    std::string repair_date;
    double cost;

    Repair(int id, const std::string& t, const std::string& m, const std::string& date, double c)
        : vehicle_id(id), type(t), make(m), repair_date(date), cost(c) {}
};

class Garage {
private:
    std::vector<Vehicle> vehicles;

public:
    void addVehicle(const Vehicle& vehicle);
};
class CargoTransportation {
public:
    int transportationId;
    int vehicleId;
    std::string cargo;
    std::string date;

    CargoTransportation(int id, int vehicle, const std::string& c, const std::string& d)
        : transportationId(id), vehicleId(vehicle), cargo(c), date(d) {}
};


class Database {
private:
    std::string vehicles_file;
    std::string drivers_file;
    std::string routes_file;
    std::string mileage_file;
    std::string repair_file;
    std::string employees_file;
    std::string cargo_file;


public:
    Database(const std::string& vehicles, const std::string& drivers, const std::string& routes, const std::string& mileage, const std::string& repair, const std::string& employees, const std::string& cargo);
    std::vector<Vehicle> getVehicles();
    std::vector<Driver> getDrivers();
    std::vector<Route> getRoutes();
    std::vector<MileageRecord> getMileageRecords();
    std::vector<Repair> loadRepairsFromFile();
    std::vector<Employee> loadEmployeesFromFile();
    std::vector<CargoTransportation> getCargoTransportationsFromFile();
    void addVehicle(const Vehicle& vehicle);
    void addDriver(const Driver& driver);
    void addRoute(const Route& route);
    std::vector<Driver> getDriversByVehicleId(int vehicle_id);
    int getTotalDriverCount();
};

std::string getVehicleMakeById(int vehicle_id);
std::string getVehicleTypeById(int vehicle_id);
