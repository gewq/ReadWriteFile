/**
\file Message.h
\brief Класс инкапсулирует данные о сообщении

Содержит поля:
- имя пользователя от кого сообщение
- имя пользователя кому сообщение
- текст сообщения
*/

#pragma once

#include <string>


class Message {
  public:
    /**
    Конструктор по-умолчанию
    */
    Message();

    /**
    Параметризованный конструктор
    \param[in] sender Ник пользователя от которого сообщение
    \param[in] receiver Ник пользователя кому адресовано сообщение
    \param[in] text Текст сообщения
    */
    Message(const std::string& sender,
            const std::string& receiver,
            const std::string& text);
    /**
    \return Ник пользователя от которого сообщение
    */
    const std::string& getSender() const;

    /**
    \return Ник пользователя кому сообщение
    */
    const std::string& getReceiver() const;

    /**
    \return Ник пользователя кому сообщение
    */
    const std::string& getText() const;

    /**
    Перегрузка оператора >> чтения из потока
    \param[in] inputStream Поток из которого читать данные
    \param[in] message Объект в который поместить прочитанные данные
    */
    friend std::fstream& operator >> (std::fstream& inputStream, Message& message);

    /**
    Перегрузка оператора << вывода в поток
    \param[in] outputStream Поток в который вывести данные
    \param[in] message Объект данные которого вывести в поток
    */
    friend std::ostream& operator << (std::ostream& outputStream, const Message& message);

  private:
    std::string sender_;		///<Имя пользователя от которого сообщение
    std::string receiver_;	///<Имя пользователя кому адресовано сообщение
    std::string text_;			///<Текст сообщения
};



namespace message {
  /**
  Запустить тестирование методов класса
  */
  void test();
}