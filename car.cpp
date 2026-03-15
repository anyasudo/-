#include "car.hpp"
#include "garage.hpp"

namespace mt {

    bool Car::check_license_format_(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        std::string allowed_letters = "АВЕКМНОРСТУХ";

        bool first_ok = false;
        for (char letter : allowed_letters) {
            if (plate[0] == letter) {
                first_ok = true;
                break;
            }
        }

        bool digits_ok = true;
        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                digits_ok = false;
                break;
            }
        }

        bool last_ok = false;
        for (char letter1 : allowed_letters) {
            for (char letter2 : allowed_letters) {
                if (plate[4] == letter1 && plate[5] == letter2) {
                    last_ok = true;
                    break;
                }
            }
            if (last_ok) break;
        }

        return first_ok && digits_ok && last_ok;
    }

    std::string Car::generate_random_plate_() const {
        static const std::string letters = "АВЕКМНОРСТУХ";
        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<int> letter_dist(0, letters.size() - 1);
        static std::uniform_int_distribution<int> digit_dist(0, 9);

        std::string plate;

        do {
            plate.clear();
            plate += letters[letter_dist(rng)];
            plate += std::to_string(digit_dist(rng));
            plate += std::to_string(digit_dist(rng));
            plate += std::to_string(digit_dist(rng));
            plate += letters[letter_dist(rng)];
            plate += letters[letter_dist(rng)];
        } while (!check_license_format_(plate));

        return plate;
    }

    void Car::group_duplicates_(std::vector<std::string>& items) const {
        if (items.empty()) return;
        std::sort(items.begin(), items.end());
    }

    // Конструктор по умолчанию
    Car::Car() : brand_("Неизвестно"), model_("Неизвестно"),
        license_plate_("А000АА"), mileage_(0), car_radio_(nullptr) {
        trunk_items_ = new std::vector<std::string>();
        std::cout << "Вызван конструктор по умолчанию" << std::endl;
    }

    // Конструктор с параметрами
    Car::Car(const std::string& brand, const std::string& model,
        const std::string& license_plate, int mileage,
        const std::vector<std::string>& trunk_items) :
        brand_(brand), model_(model), license_plate_(license_plate),
        mileage_(mileage), car_radio_(nullptr) {

        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        trunk_items_ = new std::vector<std::string>(trunk_items);
        std::cout << "Вызван конструктор с параметрами" << std::endl;
    }

    // Конструктор копирования
    Car::Car(const Car& other) :
        brand_(other.brand_), model_(other.model_),
        license_plate_(other.license_plate_), mileage_(other.mileage_) {

        trunk_items_ = new std::vector<std::string>(*other.trunk_items_);

        // Копируем магнитолу если она есть
        if (other.car_radio_) {
            car_radio_ = new Radio(*other.car_radio_);
        }
        else {
            car_radio_ = nullptr;
        }

        std::cout << "Вызван конструктор копирования" << std::endl;
    }

    // Оператор присваивания
    Car& Car::operator=(const Car& other) {
        std::cout << "Вызван оператор присваивания" << std::endl;

        if (this != &other) {
            brand_ = other.brand_;
            model_ = other.model_;
            license_plate_ = other.license_plate_;
            mileage_ = other.mileage_;

            delete trunk_items_;
            trunk_items_ = new std::vector<std::string>(*other.trunk_items_);

            delete car_radio_;
            if (other.car_radio_) {
                car_radio_ = new Radio(*other.car_radio_);
            }
            else {
                car_radio_ = nullptr;
            }
        }

        return *this;
    }

    // Деструктор
    Car::~Car() {
        if (trunk_items_ != nullptr) {
            trunk_items_->clear();
            delete trunk_items_;
        }

        delete car_radio_;

        std::cout << "Вызван деструктор для " << brand_ << " " << model_ << std::endl;
    }

    void Car::set_license_plate(const std::string& license_plate) {
        if (!check_license_format_(license_plate)) {
            throw std::invalid_argument(
                "Гос. номер должен быть в формате: БУКВА + 3 ЦИФРЫ + 2 БУКВЫ\n"
                "Разрешенные буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х\n"
                "Пример: А123ВС, М456ОР, Х789ТУ");
        }

        license_plate_ = license_plate;
        std::cout << "Гос. номер успешно изменен на: " << license_plate_ << std::endl;
    }

    void Car::rollback_mileage(int x) {
        if (x > mileage_) {
            throw std::invalid_argument("Нельзя скрутить больше, чем есть пробега");
        }
        mileage_ -= x;
        std::cout << "Пробег скручен на " << x << " км. Текущий пробег: " << mileage_ << std::endl;
    }

    void Car::print_info() const {
        std::cout << "=== Информация об автомобиле ===" << std::endl;
        std::cout << "Марка: " << brand_ << std::endl;
        std::cout << "Модель: " << model_ << std::endl;
        std::cout << "Гос. номер: " << license_plate_ << std::endl;
        std::cout << "Пробег: " << mileage_ << " км" << std::endl;

        std::cout << "Магнитола: ";
        if (car_radio_) {
            std::cout << car_radio_->model_name << " (" << car_radio_->description << ") - "
                << car_radio_->price << " руб." << std::endl;
        }
        else {
            std::cout << "не установлена" << std::endl;
        }

        std::cout << "Вещи в багажнике (" << trunk_items_->size() << "): ";

        if (trunk_items_->empty()) {
            std::cout << "багажник пуст";
        }
        else {
            for (size_t i = 0; i < trunk_items_->size(); ++i) {
                std::cout << (*trunk_items_)[i];
                if (i < trunk_items_->size() - 1) {
                    std::cout << ", ";
                }
            }
        }
        std::cout << std::endl << "================================" << std::endl;
    }

    void Car::add_to_trunk(const std::string& item) {
        trunk_items_->push_back(item);
        std::cout << "Добавлено в багажник: " << item << std::endl;
    }

    void Car::remove_from_trunk(const std::string& item) {
        auto it = std::find(trunk_items_->begin(), trunk_items_->end(), item);
        if (it != trunk_items_->end()) {
            trunk_items_->erase(it);
            std::cout << "Удалено из багажника: " << item << std::endl;
        }
        else {
            std::cout << "Предмет " << item << " не найден в багажнике" << std::endl;
        }
    }

    // Методы для работы с магнитолой
    void Car::set_radio(const Radio& radio) {
        if (car_radio_) {
            *car_radio_ = radio;
            std::cout << "Магнитола заменена на: " << radio.model_name << std::endl;
        }
        else {
            car_radio_ = new Radio(radio);
            std::cout << "Магнитола установлена: " << radio.model_name << std::endl;
        }
    }

    Radio Car::get_radio() const {
        if (!car_radio_) {
            throw std::runtime_error("В машине нет магнитолы!");
        }
        return *car_radio_;
    }

    void Car::remove_radio() {
        if (car_radio_) {
            std::cout << "Магнитола удалена: " << car_radio_->model_name << std::endl;
            delete car_radio_;
            car_radio_ = nullptr;
        }
        else {
            std::cout << "В машине нет магнитолы для удаления" << std::endl;
        }
    }

    // Оператор +
    Car Car::operator+(const Car& other) const {
        std::cout << "Выполняется оператор +" << std::endl;

        Car result;
        result.brand_ = this->brand_;
        result.model_ = this->model_;
        result.license_plate_ = generate_random_plate_();
        result.mileage_ = (this->mileage_ + other.mileage_) / 2;

        result.trunk_items_->clear();
        *result.trunk_items_ = *this->trunk_items_;
        result.trunk_items_->insert(result.trunk_items_->end(),
            other.trunk_items_->begin(),
            other.trunk_items_->end());

        group_duplicates_(*result.trunk_items_);

        return result;
    }

    // Оператор -
    Car Car::operator-(const Car& other) const {
        std::cout << "Выполняется оператор -" << std::endl;

        Car result;
        result.brand_ = this->brand_;
        result.model_ = this->model_;
        result.license_plate_ = generate_random_plate_();
        result.mileage_ = abs(this->mileage_ - other.mileage_);

        result.trunk_items_->clear();

        std::vector<std::string> all_items = *this->trunk_items_;
        all_items.insert(all_items.end(), other.trunk_items_->begin(), other.trunk_items_->end());

        std::sort(all_items.begin(), all_items.end());
        auto last = std::unique(all_items.begin(), all_items.end());
        all_items.erase(last, all_items.end());

        *result.trunk_items_ = all_items;

        return result;
    }

    // Оператор /
    Car Car::operator/(const Car& other) const {
        std::cout << "Выполняется оператор /" << std::endl;

        Car result;
        result.brand_ = other.brand_;
        result.model_ = other.model_;
        result.license_plate_ = generate_random_plate_();
        result.mileage_ = (this->mileage_ + other.mileage_) / 2;

        result.trunk_items_->clear();

        for (const auto& item1 : *this->trunk_items_) {
            for (const auto& item2 : *other.trunk_items_) {
                if (item1 == item2) {
                    if (std::find(result.trunk_items_->begin(),
                        result.trunk_items_->end(), item1)
                        == result.trunk_items_->end()) {
                        result.trunk_items_->push_back(item1);
                    }
                    break;
                }
            }
        }

        return result;
    }

    bool Car::operator==(const Car& other) const {
        return license_plate_ == other.license_plate_;
    }

    bool Car::operator!=(const Car& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << "[" << car.brand_ << " " << car.model_ << ", " << car.license_plate_
            << ", пробег: " << car.mileage_ << " км";

        if (car.car_radio_) {
            os << ", магнитола: " << car.car_radio_->model_name;
        }
        else {
            os << ", магнитолы нет";
        }

        os << ", вещи:(";

        if (car.trunk_items_->empty()) {
            os << "пусто";
        }
        else {
            for (size_t i = 0; i < car.trunk_items_->size(); ++i) {
                os << (*car.trunk_items_)[i];
                if (i < car.trunk_items_->size() - 1) {
                    os << ", ";
                }
            }
        }

        os << ")]";
        return os;
    }

} // namespace mt