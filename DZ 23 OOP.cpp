#include <iostream>
#include <iomanip>
#include <stdexcept>

class Time {
public:
    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int h, int m, int s) {
        if (h < 0 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            throw std::invalid_argument("Неверные значения времени");
        }
        hours = h;
        minutes = m;
        seconds = s;
    }

    Time(int totalSeconds) {
        hours = totalSeconds / 3600;
        minutes = (totalSeconds / 60) % 60;
        seconds = totalSeconds % 60;
    }

    void calculateTime(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;

        while (seconds >= 60) {
            seconds -= 60;
            minutes++;
        }

        while (minutes >= 60) {
            minutes -= 60;
            hours++;
        }

        while (hours >= 24) {
            hours -= 24;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    friend std::istream& operator>>(std::istream& is, Time& time);

private:
    int hours;
    int minutes;
    int seconds;
};

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setw(2) << std::setfill('0') << time.hours << ":"
        << std::setw(2) << std::setfill('0') << time.minutes << ":"
        << std::setw(2) << std::setfill('0') << time.seconds;
    return os;
}

std::istream& operator>>(std::istream& is, Time& time) {
    char separator;
    is >> time.hours >> separator >> time.minutes >> separator >> time.seconds;
    return is;
}

int main() {
    setlocale(LC_ALL, "ru");
    try {
        Time t1;
        std::cout << "Время (по умолчанию): " << t1 << std::endl;

        Time t2(10, 130, 100);
        std::cout << "Время (неверно): " << t2 << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    try {
        Time t3(3600);
        std::cout << "Время (в секундах): " << t3 << std::endl;

        Time t4;
        std::cout << "Время (до расчета): " << t4 << std::endl;
        t4.calculateTime(10, 130, 100);
        std::cout << "Время (после расчета): " << t4 << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}