#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sys/stat.h> // chmod()
#include "class.h"

void setSecurePermissions(const std::string& filename) {
    // Установить права 0600 (rw-------)
    if (chmod(filename.c_str(), 0600) != 0) {
        perror(("Не удалось установить права доступа на файл " + filename).c_str());
    } else {
        std::cout << "[✓] Установлены права доступа rw------- на файл: " << filename << std::endl;
    }
}

int main() {
    const std::string userFile = "users.txt";
    const std::string msgFile = "messages.txt";

    std::vector<User> users = {
        {"Alice", "alice", "123"},
        {"Bob", "bob", "456"}
    };

    std::vector<Message> messages = {
		{"Hi Bob", "alice", "bob"},
        {"Hello Alice", "bob", "alice"}
    };
	
    // --- Сохранение ---
    {
		std::cout << "Сохраняем данные в файлы." << std::endl;
        std::ofstream userOut(userFile);
        if (!userOut.is_open()) {
            std::cerr << "[!] Ошибка: не удалось открыть " << userFile << " для записи." << std::endl;
            return 1;
        }
        for (const auto& user : users) user.save(userOut);
        userOut.close();
        setSecurePermissions(userFile);

        std::ofstream messageOut(msgFile);
        if (!messageOut.is_open()) {
            std::cerr << "[!] Ошибка: не удалось открыть " << msgFile << " для записи." << std::endl;
            return 1;
        }
        for (const auto& message  : messages) message.save(messageOut);
        messageOut.close();
        setSecurePermissions(msgFile);

        std::cout << "[✓] Файлы успешно сохранены." << std::endl;
    }

    // --- Загрузка и форматированный вывод ---
    {
		std::cout << "Читаем данные из файлов." << std::endl;
        std::ifstream userIn(userFile);
        if (!userIn.is_open()) {
            std::cerr << "[!] Ошибка: не удалось открыть " << userFile << " для чтения." << std::endl;
            return 1;
        }

        std::cout << std::endl << "[Пользователи]" << std::endl;
        std::cout << std::left
                  << std::setw(16) << "Имя"
                  << std::setw(16) << "Логин"
                  << std::setw(16) << "Пароль" << std::endl;
        std::cout << std::string(48, '-') << std::endl;

        while (userIn.peek() != EOF) {
            User user;
            user.load(userIn);
            if (!user._name.empty())
                std::cout << std::setw(16) << user._name
                          << std::setw(16) << user._login
                          << std::setw(16) << user._pass << std::endl;
        }

        std::ifstream messageIn(msgFile);
        if (!messageIn.is_open()) {
            std::cerr << "[!] Ошибка: не удалось открыть " << msgFile << " для чтения." << std::endl;
            return 1;
        }

        std::cout << std::endl << "[Сообщения]" << std::endl;
        std::cout << std::left
                  << std::setw(16) << "Отправитель"
                  << std::setw(16) << "Получатель"
                  << std::setw(32) << "Текст" << std::endl;
        std::cout << std::string(64, '-') << std::endl;

        while (messageIn.peek() != EOF) {
            Message message;
            message.load(messageIn);
            if (!message._text.empty())
                std::cout << std::setw(16) << message._sender
                          << std::setw(16) << message._receiver
                          << std::setw(32) << message._text << std::endl;
        }
    }

    return 0;
}
