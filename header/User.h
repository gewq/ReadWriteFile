/**
\file User.h
\brief Класс содержит данные о пользователе
Класс инкапсулирует в себе параметры пользователя:
- Ник (имя) - по нику он будет известен другим пользователям
- Логин - имя по которому он будет заходить в чат
- Пароль
*/

#pragma once

#include <string>


class User {
  public:
    User();
    User(const std::string& name,
         const std::string& login,
         const std::string& password);

    /**
    \return Ник пользователя
    */
    std::string getName() const;

    /**
    \return Логин пользователя
    */
    std::string getLogin() const;

    /**
    \return Пароль
    */
    std::string getPassword() const;

    /**
    Перегрузка оператора >> чтения из потока
    \param[in] inputStream Поток из которого читать данные
    \param[in] user Объект в который поместить прочитанные данные
    */
    friend std::fstream& operator >> (std::fstream& inputStream, User& user);

    /**
    Перегрузка оператора << вывода в поток
    \param[in] outputStream Поток в который вывести данные
    \param[in] user Объект данные которого вывести в поток
    */
    friend std::ostream& operator << (std::ostream& outputStream, const User& user);

  private:
    std::string name_;			///<Ник
    std::string login_;			///<Логин
    std::string password_;	///<Пароль
};



namespace user {
  /**
  Запустить тестирование методов класса
  */
  void test();
}