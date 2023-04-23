#pragma once

#include <fstream>
#include <filesystem>
#include <list>


namespace file {
  /**
  Заблокировать доступ к файлу для всех пользователей кроме текущего
  \param[in] fileName Имя файла
  */
  void lockAccessOthers(const std::string& fileName);

  /**
  Проверить есть ли у пользователя доступ на чтение/запись файла
  \param[in] fileRights Права на файл
  \return Признак наличия прав у пользователя на чтение/запись файла
  */
  bool isAccessGranted_User(std::filesystem::perms fileRights);

  /**
  Прочитать данные из файла и поместить в список
  \param[in] fileName Имя файла
  \param[in] data Список объектов, прочитанных из файла
  */
  template <typename T>
  void loadData(const std::string& fileName, std::list<T>& data)
  {
    //Нет прав на доступ к файлу
    if ( !file::isAccessGranted_User(std::filesystem::status(fileName).permissions()) ) {
      const std::string errorMessage = "Access to file " + fileName + " denied";
      throw errorMessage;
    }
    auto inputFile = std::fstream(fileName);
    //Файл не существует
    if (!inputFile.is_open()) {
      const std::string errorMessage = "File: " + fileName + " doesn't exist";
      throw errorMessage;
    }

    while (!inputFile.eof()) {
      T value;
      inputFile >> value;
      data.push_back(value);
    }
    inputFile.close();
  }
}