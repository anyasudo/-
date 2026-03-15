#ifndef GARAGE_HPP
#define GARAGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "car.hpp"

namespace mt {

    struct Radio {
        std::string model_name;
        std::string description;
        double price;

        // Конструкторы
        Radio();
        Radio(const std::string& name, const std::string& desc, double pr);
        Radio(const Radio& other);

        // Деструктор
        ~Radio();

        // Методы
        void print_info() const;

        friend std::ostream& operator<<(std::ostream& os, const Radio& radio);
    };

    class AutoWorkshop {
    private:
        std::string address_;
        std::vector<Radio> available_radios_;
        std::vector<Car*> attached_cars_;

    public:
        // Конструкторы
        AutoWorkshop();
        AutoWorkshop(const std::string& address);
        AutoWorkshop(const AutoWorkshop& other);

        // Деструктор
        ~AutoWorkshop();

        // Геттеры
        std::string get_address() const { return address_; }
        std::vector<Radio> get_available_radios() const { return available_radios_; }
        std::vector<Car*> get_attached_cars() const { return attached_cars_; }

        // Сеттеры
        void set_address(const std::string& address) { address_ = address; }

        // Методы для работы с магнитолами
        void add_radio(const Radio& radio);
        void remove_radio(const std::string& model_name);
        void print_available_radios() const;

        // Методы для работы с машинами
        void attach_car(Car* car);
        void detach_car(const std::string& license_plate);

        // Метод прикручивания магнитолы
        bool install_radio_to_car(const std::string& license_plate, const std::string& radio_model);

        // Метод вывода информации
        void print_info() const;
    };

} // namespace mt

#endif // GARAGE_HPP