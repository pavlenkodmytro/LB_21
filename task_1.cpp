#include <iostream> // Для роботи з введенням/виведенням (cin, cout)
#include <string>   // Для роботи з рядками (хоча тут не використовується напряму, може знадобитись)
#include <iomanip>  // Для маніпуляцій з виведенням (наприклад, setprecision для форматування відсотків)
#include <vector>   // Може бути корисним для зберігання багатьох об'єктів FlightBooking, хоча тут не використовується
#include <limits>   // Для std::numeric_limits (використовується для очищення буфера вводу)

// Оголошення класу FlightBooking
class FlightBooking {
public:
    // --- Конструктор класу ---
    // Ініціалізує об'єкт FlightBooking з заданими id, місткістю та кількістю заброньованих місць.
    // Також встановлює початковий стан прапорця зміни бронювань (reservationChanged) в false.
    FlightBooking(int id, int capacity, int reserved);

    // --- Метод для виведення статусу ---
    // Виводить інформацію про рейс: ID, заброньовані/загальна кількість місць та відсоток заповненості.
    // Додано 'const', оскільки метод не змінює стан об'єкта.
    void printStatus() const;

    // --- Завдання 2: Додані методи set ---
    // Метод для встановлення (зміни) кількості заброньованих місць.
    // Встановлює прапорець reservationChanged в true, якщо значення дійсно змінилося.
    void setReserved(int new_reserved);

    // Метод для встановлення (зміни) місткості літака.
    void setCapacity(int new_capacity);

    // Метод для встановлення (зміни) ID рейсу.
    // (Менш типовий для існуючого об'єкта, але додано для повноти завдання "додати метод set")
    void setId(int new_id);

    // --- Завдання 3: Додані нові методи ---
    // Метод get_percentage (замість get_aria, оскільки "aria" не має сенсу в контексті рейсу)
    // Повертає відсоток заброньованих місць від загальної місткості.
    // Додано 'const', оскільки метод не змінює стан об'єкта.
    double getPercentage() const;

    // Метод hasReservationChanged (замість changet, що є більш логічною назвою)
    // Перевіряє, чи змінювалась кількість заброньованих місць з моменту створення об'єкта або останнього виклику setReserved.
    // Повертає true, якщо зміни були, інакше false.
    // Додано 'const', оскільки метод не змінює стан об'єкта.
    bool hasReservationChanged() const;

    // --- Додаткові методи get (хороша практика для доступу до даних) ---
    // Повертають відповідні приватні члени класу.
    // Додано 'const', оскільки методи не змінюють стан об'єкта.
    int getId() const;
    int getCapacity() const;
    int getReserved() const;


private:
    // Приватні члени класу (дані)
    int id;                 // Ідентифікатор рейсу
    int capacity;           // Загальна місткість літака
    int reserved;           // Кількість заброньованих місць
    bool reservationChanged; // Прапорець для Завдання 3 (метод changet/hasReservationChanged)
                            // Показує, чи викликався метод setReserved з новим значенням.
};

// --- Реалізація методів класу FlightBooking ---

// Реалізація конструктора
FlightBooking::FlightBooking(int id, int capacity, int reserved) {
    // Використовуємо this-> для явного позначення членів класу
    this->id = id;
    // Перевірка: місткість не може бути нульовою або від'ємною
    this->capacity = (capacity > 0) ? capacity : 1; // Якщо capacity <= 0, встановлюємо 1, щоб уникнути ділення на нуль
    // Перевірка: кількість заброньованих місць не може бути від'ємною
    this->reserved = (reserved >= 0) ? reserved : 0;
    // Початково прапорець зміни встановлюємо в false
    this->reservationChanged = false;
    // Інформаційне повідомлення про створення об'єкта (для наочності)
    // std::cout << "// Створено об'єкт FlightBooking ID: " << this->id << std::endl;
}

// Реалізація методу printStatus
void FlightBooking::printStatus() const {
    // Виводимо звіт у вказаному форматі
    std::cout << "Flight " << this->id << ": "
              << this->reserved << "/" << this->capacity << " ("
              << std::fixed << std::setprecision(1) // Встановлюємо фіксовану точність (1 знак після коми)
              << this->getPercentage() << "%) seats taken." << std::endl;
    // Додатково виводимо стан прапорця зміни бронювань
    // std::cout << "   Reservation status changed: " << (this->reservationChanged ? "Yes" : "No") << std::endl;
}

// Реалізація методу setReserved
void FlightBooking::setReserved(int new_reserved) {
    // Перевіряємо, чи нове значення не від'ємне
    if (new_reserved >= 0) {
        // Перевіряємо, чи нове значення відрізняється від поточного
        if (this->reserved != new_reserved) {
            this->reserved = new_reserved;
            this->reservationChanged = true; // Встановлюємо прапорець, бо значення змінилося
            // std::cout << "// Кількість заброньованих місць для ID " << this->id << " змінено на " << this->reserved << std::endl;
        } else {
            // std::cout << "// Кількість заброньованих місць для ID " << this->id << " вже дорівнює " << new_reserved << ". Змін не відбулося." << std::endl;
        }
    } else {
        // Виводимо повідомлення про помилку, якщо намагаються встановити від'ємне значення
        std::cerr << "Error: Number of reserved seats cannot be negative for Flight ID " << this->id << "." << std::endl;
    }
}

// Реалізація методу setCapacity
void FlightBooking::setCapacity(int new_capacity) {
    // Місткість повинна бути позитивною
    if (new_capacity > 0) {
        this->capacity = new_capacity;
        // При зміні місткості прапорець reservationChanged не змінюємо,
        // оскільки він стосується саме зміни кількості *заброньованих* місць.
        // std::cout << "// Місткість для ID " << this->id << " змінено на " << this->capacity << std::endl;

        // Додаткова логіка: якщо нова місткість менша за кількість заброньованих місць,
        // можна або видати попередження, або скоригувати кількість заброньованих.
        // У цьому прикладі просто змінюємо місткість.
        if (this->reserved > this->capacity) {
             std::cerr << "Warning: Reserved seats (" << this->reserved
                       << ") exceed new capacity (" << this->capacity
                       << ") for Flight ID " << this->id << "." << std::endl;
             // Можна додати логіку коригування: this->reserved = this->capacity;
        }

    } else {
        std::cerr << "Error: Capacity must be positive for Flight ID " << this->id << "." << std::endl;
    }
}

// Реалізація методу setId
void FlightBooking::setId(int new_id) {
    this->id = new_id;
     // std::cout << "// ID для об'єкта змінено на " << this->id << std::endl;
    // Прапорець reservationChanged тут також не змінюємо.
}


// Реалізація методу getPercentage
double FlightBooking::getPercentage() const {
    // Перевіряємо, чи місткість не нульова, щоб уникнути ділення на нуль
    if (this->capacity == 0) {
        return 0.0; // Якщо місткість 0, відсоток заповненості 0
    }
    // Розраховуємо відсоток. Важливо привести одне з чисел до типу double,
    // щоб результат ділення був дробовим, а не цілочисельним.
    return (static_cast<double>(this->reserved) / this->capacity) * 100.0;
}

// Реалізація методу hasReservationChanged
bool FlightBooking::hasReservationChanged() const {
    // Просто повертаємо поточне значення прапорця
    return this->reservationChanged;
}

// Реалізація геттерів
int FlightBooking::getId() const { return this->id; }
int FlightBooking::getCapacity() const { return this->capacity; }
int FlightBooking::getReserved() const { return this->reserved; }


// --- Головна функція програми ---
int main() {
    // Встановлюємо українську локаль для коректного виведення (якщо потрібно)
    // setlocale(LC_ALL, "uk_UA.UTF-8"); // Може потребувати налаштувань системи

    // --- Виправлення помилки: Оголошуємо змінні перед використанням ---
    int initial_capacity = 0; // Початкова місткість, яку введе користувач
    int initial_reserved = 0; // Початкова к-сть бронювань, яку введе користувач

    // Запитуємо дані у користувача
    std::cout << "Введіть місткість рейсу: ";
    // Додаємо перевірку вводу, щоб переконатись, що введено число і воно додатне
    while (!(std::cin >> initial_capacity) || initial_capacity <= 0) {
        std::cerr << "Помилка: Будь ласка, введіть додатне ціле число для місткості: ";
        std::cin.clear(); // Скидаємо прапорці помилок потоку вводу
        // Ігноруємо залишок некоректного вводу в буфері до кінця рядка
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введіть кількість заброньованих місць: ";
     // Додаємо перевірку вводу, щоб переконатись, що введено число і воно невід'ємне
    while (!(std::cin >> initial_reserved) || initial_reserved < 0) {
        std::cerr << "Помилка: Будь ласка, введіть невід'ємне ціле число для заброньованих місць: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // --- Завдання 1: Створення об'єкта (з виправленим класом) ---
    // Створюємо перший об'єкт типу FlightBooking з даними від користувача
    FlightBooking booking1(1, initial_capacity, initial_reserved);

    std::cout << "\n--- Початковий статус Рейсу 1 ---" << std::endl;
    booking1.printStatus(); // Викликаємо метод для виведення статусу

    // --- Демонстрація роботи нових методів ---
    std::cout << "\n--- Демонстрація setReserved та hasReservationChanged ---" << std::endl;
    std::cout << "Чи змінювались бронювання для Рейсу " << booking1.getId() << "? "
              << (booking1.hasReservationChanged() ? "Так" : "Ні") << std::endl; // Використання hasReservationChanged

    // Використовуємо метод setReserved для зміни кількості бронювань
    int seats_to_add = 15;
    int new_reservation_count = booking1.getReserved() + seats_to_add;
    std::cout << "\nДодаємо " << seats_to_add << " нових бронювань..." << std::endl;
    booking1.setReserved(new_reservation_count); // Виклик setReserved

    // Перевіряємо статус після змін
    std::cout << "\nСтатус Рейсу " << booking1.getId() << " після додавання бронювань:" << std::endl;
    booking1.printStatus();
    std::cout << "Чи змінювались бронювання для Рейсу " << booking1.getId() << "? "
              << (booking1.hasReservationChanged() ? "Так" : "Ні") << std::endl; // Перевіряємо прапорець знову

    // Спроба встановити некоректне значення
    std::cout << "\nСпроба встановити -10 заброньованих місць..." << std::endl;
    booking1.setReserved(-10);
    std::cout << "Статус Рейсу " << booking1.getId() << " після спроби встановити від'ємне значення:" << std::endl;
    booking1.printStatus(); // Кількість місць не повинна була змінитись


    // --- Завдання 1: Створення кількох нових об'єктів ---
    std::cout << "\n--- Створення та статус нових рейсів ---" << std::endl;
    FlightBooking booking2(101, 200, 180); // Другий об'єкт
    FlightBooking booking3(205, 150, 75);  // Третій об'єкт
    FlightBooking booking4(333, 100, 110); // Четвертий об'єкт (переповнений)

    // Виводимо статус для нових об'єктів
    booking2.printStatus();
    booking3.printStatus();
    booking4.printStatus();

     // --- Демонстрація setCapacity ---
     std::cout << "\n--- Демонстрація setCapacity для Рейсу " << booking3.getId() << " ---" << std::endl;
     std::cout << "Поточна місткість: " << booking3.getCapacity() << std::endl;
     std::cout << "Встановлюємо нову місткість 160..." << std::endl;
     booking3.setCapacity(160);
     booking3.printStatus();
     std::cout << "Встановлюємо нову місткість 70 (менше заброньованих)..." << std::endl;
     booking3.setCapacity(70); // Це викличе попередження
     booking3.printStatus();


    return 0; // Сигнал операційній системі, що програма завершилась успішно
}
