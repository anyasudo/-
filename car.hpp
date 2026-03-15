#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>

namespace mt {

    struct Radio;

    class Car {
    private:
        std::string brand_;
        std::string model_;
        std::string license_plate_;
        int mileage_;

        std::vector<std::string>* trunk_items_;
        Radio* car_radio_;

        bool check_license_format_(const std::string& plate) const;
        std::string generate_random_plate_() const;
        void group_duplicates_(std::vector<std::string>& items) const;

    public:
        // Конструкторы
        Car();
        Car(const std::string& brand, const std::string& model,
            const std::string& license_plate, int mileage = 0,
            const std::vector<std::string>& trunk_items = {});
        Car(const Car& other);

        // Оператор присваивания
        Car& operator=(const Car& other);

        // Деструктор
        ~Car();

        // Геттеры
        std::string get_brand() const { return brand_; }
        std::string get_model() const { return model_; }
        std::string get_license_plate() const { return license_plate_; }
        int get_mileage() const { return mileage_; }

        std::vector<std::string> get_trunk_items() const {
            return *trunk_items_;
        }

        // Методы для работы с магнитолой
        void set_radio(const Radio& radio);
        Radio get_radio() const;
        bool has_radio() const { return car_radio_ != nullptr; }
        void remove_radio();

        // Сеттеры
        void set_license_plate(const std::string& license_plate);
        void set_brand(const std::string& brand) { brand_ = brand; }
        void set_model(const std::string& model) { model_ = model; }
        void set_mileage(int mileage) { mileage_ = mileage; }

        // Методы
        void print_info() const;
        void add_to_trunk(const std::string& item);
        void remove_from_trunk(const std::string& item);
        void rollback_mileage(int x);

        // Операторы
        Car operator+(const Car& other) const;
        Car operator-(const Car& other) const;
        Car operator/(const Car& other) const;
        bool operator==(const Car& other) const;
        bool operator!=(const Car& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Car& car);
    };

} // namespace mt

#endif // CAR_HPP
