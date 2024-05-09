#include <iostream>
#include <vector>
#include <map>

// Объявление класса GasStation
class GasStation {
private:
    std::string name;
    int fuelLevel;
    int revenue;

public:
    GasStation(std::string name, int fuelLevel) : name(name), fuelLevel(fuelLevel), revenue(0) {}

    std::string getName() const {
        return name;
    }

    int getFuelLevel() const {
        return fuelLevel;
    }

    int getRevenue() const {
        return revenue;
    }

    void addFuel(int amount) {
        fuelLevel += amount;
    }

    void sellFuel(int amount, int price) {
        if (fuelLevel >= amount) {
            fuelLevel -= amount;
            revenue += amount * price;
            std::cout << "Продано " << amount << " литров бензина на заправке " << name << " за " << amount * price << " рублей\n\n";
        }
        else {
            std::cout << "На заправке " << name << " недостаточно бензина\n\n\n";
        }
    }

    void showInfo() const {
        std::cout << "Информация о заправке " << name << ":\n";
        std::cout << "Уровень бензина: " << fuelLevel << " литров\n";
        std::cout << "Прибыль: " << revenue << " рублей\n\n\n\n";
    }
};

// Объявление класса GasTransport
class GasTransport {
private:
    std::string transportType;
    int fuelCapacity;
    int fuelLevel;

public:
    GasTransport(std::string type, int capacity, int level) : transportType(type), fuelCapacity(capacity), fuelLevel(level) {}

    std::string getType() const {
        return transportType;
    }

    int getFuelLevel() const {
        return fuelLevel;
    }

    void refillFuel() {
        fuelLevel = fuelCapacity;
        std::cout << "Топливный бак транспорта " << transportType << " заполнен\n\n\n\n";
    }

    void consumeFuel(int amount) {
        if (fuelLevel >= amount) {
            fuelLevel -= amount;
            std::cout << "Транспорт " << transportType << " потребил " << amount << " литров бензина\n\n\n\n";
        }
        else {
            std::cout << "Недостаточно топлива в транспорте " << transportType << " для выполнения операции\n\n\n\n";
        }
    }

    void showInfo() const {
        std::cout << "Информация о транспорте " << transportType << ":\n";
        std::cout << "Емкость бака: " << fuelCapacity << " литров\n";
        std::cout << "Уровень бензина: " << fuelLevel << " литров\n\n\n\n";
    }
};

// Объявление класса GasDelivery
class GasDelivery {
private:
    GasStation& station;
    GasTransport& transport;
    int deliveryCost;

public:
    GasDelivery(GasStation& station, GasTransport& transport, int deliveryCost) : station(station), transport(transport), deliveryCost(deliveryCost) {}

    void deliverFuel(int amount) {
        if (transport.getFuelLevel() >= amount) {
            station.addFuel(amount);
            transport.consumeFuel(amount);
            std::cout << "Бензин доставлен\n\n";
            station.sellFuel(amount, deliveryCost); // Продажа бензина
            std::cout << "\nСтоимость доставки: " << deliveryCost << " рублей\n";
        }
        else {
            std::cout << "Недостаточно топлива в транспорте для доставки\n\n";
        }
    }
};

// Функция для создания новой заправки
void createGasStation(std::vector<GasStation>& stations) {
    std::string name;
    int fuelLevel;
    std::cout << "Введите название новой заправки: ";
    std::cin >> name;
    std::cout << "Введите уровень бензина на заправке: ";
    std::cin >> fuelLevel;
    GasStation newStation(name, fuelLevel);
    stations.push_back(newStation);
    std::cout << "Заправка успешно добавлена\n\n";
}

// Функция для создания нового транспорта
void createGasTransport(std::vector<GasTransport>& transports) {
    std::string type;
    int capacity, level;
    std::cout << "Введите тип нового транспорта: ";
    std::cin >> type;
    std::cout << "Введите емкость бака нового транспорта: ";
    std::cin >> capacity;
    std::cout << "Введите уровень бензина в баке нового транспорта: ";
    std::cin >> level;
    GasTransport newTransport(type, capacity, level);
    transports.push_back(newTransport);
    std::cout << "Транспорт успешно добавлен\n\n";
}

// Функция для обновления информации о заправке
void updateGasStation(std::vector<GasStation>& stations) {
    std::string name;
    std::cout << "Введите название заправки для изменения: ";
    std::cin >> name;
    bool found = false;
    for (auto& station : stations) {
        if (station.getName() == name) {
            int fuelLevel;
            std::cout << "Введите новый уровень бензина на заправке: ";
            std::cin >> fuelLevel;
            station.addFuel(fuelLevel - station.getFuelLevel());
            found = true;
            break;
        }
    }
    if (!found)
        std::cout << "Заправка с таким названием не найдена\n\n";
}

// Функция для обновления информации о транспорте
void updateGasTransport(std::vector<GasTransport>& transports) {
    std::string type;
    std::cout << "Введите тип транспорта для изменения: ";
    std::cin >> type;
    bool found = false;
    for (auto& transport : transports) {
        if (transport.getType() == type) {
            int fuelLevel;
            std::cout << "Введите новый уровень бензина в баке транспорта: ";
            std::cin >> fuelLevel;
            transport.consumeFuel(transport.getFuelLevel() - fuelLevel);
            found = true;
            break;
        }
    }
    if (!found)
        std::cout << "Транспорт с таким типом не найден\n\n";
}

// Функция для удаления заправки
void deleteGasStation(std::vector<GasStation>& stations) {
    std::string name;
    std::cout << "Введите название заправки для удаления: ";
    std::cin >> name;
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->getName() == name) {
            stations.erase(it);
            std::cout << "Заправка успешно удалена\n\n";
            return;
        }
    }
    std::cout << "Заправка с таким названием не найдена\n\n";
}

// Функция для удаления транспорта
void deleteGasTransport(std::vector<GasTransport>& transports) {
    std::string type;
    std::cout << "Введите тип транспорта для удаления: ";
    std::cin >> type;
    for (auto it = transports.begin(); it != transports.end(); ++it) {
        if (it->getType() == type) {
            transports.erase(it);
            std::cout << "Транспорт успешно удален\n\n";
            return;
        }
    }
    std::cout << "Транспорт с таким типом не найден\n\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<GasStation> stations; // Вектор для хранения заправок
    std::vector<GasTransport> transports; // Вектор для хранения транспорта

    bool isWorking = true;

    while (isWorking) {
        std::cout << "1 - Добавить новую заправку\n"
            << "2 - Добавить новый транспорт\n"
            << "3 - Изменить информацию о заправке\n"
            << "4 - Изменить информацию о транспорте\n"
            << "5 - Удалить заправку\n"
            << "6 - Удалить транспорт\n"
            << "7 - Посмотреть информацию о заправке\n"
            << "8 - Посмотреть информацию о транспорте\n"
            << "9 - Доставить бензин на заправку\n"
            << "a - Залить в транспорт бензин\n"
            << "b - Посмотреть прибыль\n"
            << "q - Закончить программу\n"
            << "Ваш выбор: ";

        char userInput;
        std::cin >> userInput;
        std::cout << "\n\n\n\n\n";
        switch (userInput) {
        case '1':
            createGasStation(stations);
            break;
        case '2':
            createGasTransport(transports);
            break;
        case '3':
            updateGasStation(stations);
            break;
        case '4':
            updateGasTransport(transports);
            break;
        case '5':
            deleteGasStation(stations);
            break;
        case '6':
            deleteGasTransport(transports);
            break;
        case '7':
        {
            std::cout << "Информация о заправках:\n";
            for (const auto& station : stations) {
                station.showInfo();
            }
            break;
        }
        case '8':
        {
            std::cout << "Информация о транспортах:\n";
            for (const auto& transport : transports) {
                transport.showInfo();
            }
            break;
        }
        case '9':
        {
            std::string stationName;
            std::cout << "Введите название заправки: ";
            std::cin >> stationName;
            std::string transportType;
            std::cout << "Введите тип транспорта: ";
            std::cin >> transportType;
            int amount;
            std::cout << "Введите количество литров бензина для доставки: ";
            std::cin >> amount;
            int deliveryCost;
            std::cout << "Введите стоимость доставки за литр: ";
            std::cin >> deliveryCost;
            for (auto& station : stations) {
                if (station.getName() == stationName) {
                    for (auto& transport : transports) {
                        if (transport.getType() == transportType) {
                            GasDelivery(station, transport, deliveryCost).deliverFuel(amount);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 'a':
        {
            std::string transportType;
            std::cout << "Введите тип транспорта для заправки: ";
            std::cin >> transportType;
            for (auto& transport : transports) {
                if (transport.getType() == transportType) {
                    transport.refillFuel();
                    break;
                }
            }
            break;
        }

        case 'b':
        {
            int totalRevenue = 0;
            for (const auto& station : stations) {
                totalRevenue += station.getRevenue();
            }
            std::cout << "Общая прибыль от всех заправок: " << totalRevenue << " рублей\n\n";
            break;
        }

        case 'q':
            isWorking = false;
            break;
        default:
            std::cout << "Неверный ввод\n";
        }
    }

    return 0;
}
