#include <iostream>
#include <locale>
#include "car.hpp"
#include "garage.hpp"

void print_personal_assessment() {
    std::cout << "Интерес: 9/10" << std::endl;
    std::cout << "Наполненность: 10/10" << std::endl;
    std::cout << "Сложность: 10/10 (((((" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Ru");

    try {

        // Создаем автомастерскую
        std::cout << "\n--- СОЗДАНИЕ АВТОМАСТЕРСКОЙ ---" << std::endl;
        mt::AutoWorkshop workshop("ул. Ленина, д. 10");

        // Добавляем магнитолы в мастерскую
        std::cout << "\n--- ДОБАВЛЕНИЕ МАГНИТОЛ ---" << std::endl;
        mt::Radio radio1("Pioneer DEH-80PRS", "CD/MP3-ресивер с USB", 15000);
        mt::Radio radio2("Sony MEX-XB120", "Bluetooth-ресивер с усилителем", 12000);
        mt::Radio radio3("JVC KD-X352", "Цифровой медиа-ресивер", 8000);

        workshop.add_radio(radio1);
        workshop.add_radio(radio2);
        workshop.add_radio(radio3);

        // Создаем машины
        std::cout << "\n--- СОЗДАНИЕ МАШИН ---" << std::endl;
        mt::Car car1("Toyota", "Camry", "А123ВС", 50000,
            { "аптечка", "огнетушитель", "знак аварийной остановки" });
        mt::Car car2("BMW", "X5", "М456ОР", 75000,
            { "домкрат", "баллонный ключ", "запаска" });
        mt::Car car3("Lada", "Vesta", "Х789ТУ", 15000,
            { "коврики", "ароматизатор", "зарядка для телефона" });

        // Прикрепляем машины к мастерской
        std::cout << "\n--- ПРИКРЕПЛЕНИЕ МАШИН ---" << std::endl;
        workshop.attach_car(&car1);
        workshop.attach_car(&car2);
        workshop.attach_car(&car3);

        // устанавливаем магнитолы в машины через мастерскую
        std::cout << "\n--- УСТАНОВКА МАГНИТОЛ ЧЕРЕЗ МАСТЕРСКУЮ ---" << std::endl;
        workshop.install_radio_to_car("А123ВС", "Pioneer DEH-80PRS");
        workshop.install_radio_to_car("М456ОР", "Sony MEX-XB120");

        // Проверяем что магнитолы действительно установились
        std::cout << "\n--- ПРОВЕРКА УСТАНОВКИ МАГНИТОЛ ---" << std::endl;
        std::cout << "car1: " << car1 << std::endl;
        std::cout << "car2: " << car2 << std::endl;
        std::cout << "car3: " << car3 << " (без магнитолы)" << std::endl;

        // Тестируем методы работы с магнитолой напрямую
        std::cout << "\n--- ТЕСТИРОВАНИЕ МЕТОДОВ CAR ДЛЯ МАГНИТОЛЫ ---" << std::endl;

        // Проверяем наличие
        std::cout << "car1 имеет магнитолу? " << (car1.has_radio() ? "Да" : "Нет") << std::endl;
        std::cout << "car3 имеет магнитолу? " << (car3.has_radio() ? "Да" : "Нет") << std::endl;

        // Получаем информацию о магнитоле
        try {
            mt::Radio r = car1.get_radio();
            std::cout << "Магнитола car1: " << r << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        // Пробуем получить магнитолу из car3 (должна быть ошибка)
        try {
            mt::Radio r = car3.get_radio();
            std::cout << "Магнитола car3: " << r << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка (ожидаемо): " << e.what() << std::endl;
        }

        // Удаляем магнитолу
        std::cout << "\n--- УДАЛЕНИЕ МАГНИТОЛЫ ---" << std::endl;
        car1.remove_radio();
        std::cout << "После удаления: " << car1 << std::endl;

        // Устанавливаем магнитолу напрямую 
        std::cout << "\n--- УСТАНОВКА МАГНИТОЛЫ НАПРЯМУЮ ---" << std::endl;
        car3.set_radio(mt::Radio("Alpine CDE-175", "Простой CD-ресивер", 5000));
        std::cout << "После установки: " << car3 << std::endl;

        // Выводим информацию о мастерской
        std::cout << "\n--- ИНФОРМАЦИЯ О МАСТЕРСКОЙ ---" << std::endl;
        workshop.print_info();

        // Личная оценка
        print_personal_assessment();


    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    return 0;
}
