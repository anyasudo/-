#include "garage.hpp"

namespace mt {

    // Реализация методов структуры Radio 
    Radio::Radio() : model_name("Неизвестно"), description(""), price(0.0) {
        std::cout << "Вызван конструктор Radio по умолчанию" << std::endl;
    }

    Radio::Radio(const std::string& name, const std::string& desc, double pr)
        : model_name(name), description(desc), price(pr) {
        std::cout << "Вызван конструктор Radio с параметрами" << std::endl;
    }

    Radio::Radio(const Radio& other)
        : model_name(other.model_name), description(other.description), price(other.price) {
        std::cout << "Вызван конструктор Radio копирования" << std::endl;
    }

    Radio::~Radio() {
        std::cout << "Вызван деструктор Radio для " << model_name << std::endl;
    }

    void Radio::print_info() const {
        std::cout << "Магнитола: " << model_name << std::endl;
        std::cout << "Описание: " << description << std::endl;
        std::cout << "Цена: " << price << " руб." << std::endl;
    }

    std::ostream& operator<<(std::ostream& os, const Radio& radio) {
        os << "Магнитола \"" << radio.model_name << "\" - "
            << radio.description << " (" << radio.price << " руб.)";
        return os;
    }

    // Реализация методов класса AutoWorkshop

    AutoWorkshop::AutoWorkshop() : address_("Неизвестный адрес") {
        std::cout << "Вызван конструктор AutoWorkshop по умолчанию" << std::endl;
    }

    AutoWorkshop::AutoWorkshop(const std::string& address) : address_(address) {
        std::cout << "Вызван конструктор AutoWorkshop с параметрами" << std::endl;
    }

    AutoWorkshop::AutoWorkshop(const AutoWorkshop& other)
        : address_(other.address_), available_radios_(other.available_radios_) {
        std::cout << "Вызван конструктор AutoWorkshop копирования" << std::endl;
    }

    AutoWorkshop::~AutoWorkshop() {
        std::cout << "Вызван деструктор AutoWorkshop для мастерской по адресу: "
            << address_ << std::endl;
        attached_cars_.clear();
    }

    void AutoWorkshop::add_radio(const Radio& radio) {
        available_radios_.push_back(radio);
        std::cout << "Магнитола добавлена в ассортимент: " << radio.model_name << std::endl;
    }

    void AutoWorkshop::remove_radio(const std::string& model_name) {
        auto it = std::find_if(available_radios_.begin(), available_radios_.end(),
            [&model_name](const Radio& r) { return r.model_name == model_name; });

        if (it != available_radios_.end()) {
            std::cout << "Магнитола удалена из ассортимента: " << it->model_name << std::endl;
            available_radios_.erase(it);
        }
        else {
            std::cout << "Магнитола с моделью " << model_name << " не найдена" << std::endl;
        }
    }

    void AutoWorkshop::print_available_radios() const {
        std::cout << "Доступные магнитолы в мастерской (" << available_radios_.size() << "):" << std::endl;
        if (available_radios_.empty()) {
            std::cout << "  Нет доступных магнитол" << std::endl;
        }
        else {
            for (size_t i = 0; i < available_radios_.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << available_radios_[i] << std::endl;
            }
        }
    }

    void AutoWorkshop::attach_car(Car* car) {
        if (car == nullptr) {
            std::cout << "Ошибка: передан нулевой указатель на машину" << std::endl;
            return;
        }

        auto it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
            [car](const Car* c) { return c->get_license_plate() == car->get_license_plate(); });

        if (it != attached_cars_.end()) {
            std::cout << "Машина с гос. номером " << car->get_license_plate()
                << " уже прикреплена к мастерской" << std::endl;
            return;
        }

        attached_cars_.push_back(car);
        std::cout << "Машина " << car->get_brand() << " " << car->get_model()
            << " (гос. номер: " << car->get_license_plate() << ") прикреплена к мастерской" << std::endl;
    }

    void AutoWorkshop::detach_car(const std::string& license_plate) {
        auto it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
            [&license_plate](const Car* c) { return c->get_license_plate() == license_plate; });

        if (it != attached_cars_.end()) {
            std::cout << "Машина " << (*it)->get_brand() << " " << (*it)->get_model()
                << " (гос. номер: " << license_plate << ") откреплена от мастерской" << std::endl;
            attached_cars_.erase(it);
        }
        else {
            std::cout << "Машина с гос. номером " << license_plate << " не найдена в мастерской" << std::endl;
        }
    }

    bool AutoWorkshop::install_radio_to_car(const std::string& license_plate, const std::string& radio_model) {
        auto car_it = std::find_if(attached_cars_.begin(), attached_cars_.end(),
            [&license_plate](const Car* c) { return c->get_license_plate() == license_plate; });

        if (car_it == attached_cars_.end()) {
            std::cout << "Машина с гос. номером " << license_plate
                << " не прикреплена к этой мастерской" << std::endl;
            return false;
        }

        auto radio_it = std::find_if(available_radios_.begin(), available_radios_.end(),
            [&radio_model](const Radio& r) { return r.model_name == radio_model; });

        if (radio_it == available_radios_.end()) {
            std::cout << "Магнитола с моделью " << radio_model
                << " отсутствует в мастерской" << std::endl;
            return false;
        }

        (*car_it)->set_radio(*radio_it);
        return true;
    }

    void AutoWorkshop::print_info() const {
        std::cout << "\n=== ИНФОРМАЦИЯ ОБ АВТОМАСТЕРСКОЙ ===" << std::endl;
        std::cout << "Адрес: " << address_ << std::endl;

        std::cout << "\n-- Доступные магнитолы --" << std::endl;
        print_available_radios();

        std::cout << "\n-- Прикрепленные машины (" << attached_cars_.size() << ") --" << std::endl;
        if (attached_cars_.empty()) {
            std::cout << "  Нет прикрепленных машин" << std::endl;
        }
        else {
            for (size_t i = 0; i < attached_cars_.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << *attached_cars_[i] << std::endl;
            }
        }
        std::cout << "====================================\n" << std::endl;
    }

} // namespace mt
