/**
\file main.cpp
\brief Чтение / запись объектов User и Message в файл

Программа может считывать из файла при своей загрузке и
записывать в файл состояния объектов классов User и Message
(для каждого класса свой файл).
Названия файлов с данными классов User и Message задаются пользователем
через командную строку.
Прочитать или записать информацию в файлы может только пользователь,
который запускает программу для этого блокируются права на чтение/запись
этих входных файлов.
*/

#include <iostream>
#include <list>

#include "../header/User.h"
#include "../header/Message.h"
#include "../header/Logic.h"
#include "../header/File.h"

/**
Запустить тесты модулей программы
*/
static void runTests();

/**
Начальная настройка программы. Получение имён входных файлов.
Их чтение и вывод содержимого
\param[in] argc Количество аргументов командной строки
\param[in] argv Значения аргументов командной строки
*/
static void initialize(int argc, const char** argv);


int main(int argc, const char** argv)
{
  runTests();
  try {
    initialize(argc, argv);
    bool isRun = true;
    while(isRun) {
      logic::process(isRun);
    }
  }
  catch(const std::string& exception) {
    std::cerr << "Error: " << exception << std::endl;
  }
  catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Undefined exception" << std::endl;
  }

  return EXIT_SUCCESS;
}



static void runTests()
{
  user::test();
  message::test();
}



static void initialize(int argc, const char** argv)
{
  //Не переданы параметры через командную строку
  if (argc < 3) {
    const std::string errorMessage = "Please specify input files: <users_data> <messages_data>";
    throw errorMessage;
  }
  //Слишком много параметров командной строки
  else if (argc > 3) {
    const std::string errorMessage = "Too many input parameters.";
    throw errorMessage;
  }

  //Прочитать имена входных файлов
  const std::string userDataFileName = argv[1];
  const std::string messageDataFileName = argv[2];

  auto userFile = std::ofstream (userDataFileName, std::ios::in);
  auto messageFile = std::ofstream (messageDataFileName, std::ios::in);
	//Файлы не существуют - создать
  if (!userFile.is_open()) {
    userFile = std::ofstream (userDataFileName, std::ios::in | std::ios::trunc);
    userFile.close();
  }
  if (!messageFile.is_open()) {
    messageFile = std::ofstream (messageDataFileName, std::ios::in | std::ios::trunc);
    messageFile.close();
  }

  //Заблокировать доступ к этим файлам для всех пользователей кроме текущего
  file::lockAccessOthers(userDataFileName);
  file::lockAccessOthers(messageDataFileName);

  //Загрузить и вывести данные из файлов
  std::list<User> users;
  std::list<Message> messages;
  file::loadData<User>(userDataFileName, users);
  file::loadData<Message>(messageDataFileName, messages);
	
	std::cout << "Users:\n";
  for (const auto& user : users) {
    std::cout << user;
  }
	std::cout << "Messages:\n";
  for (const auto& message : messages) {
    std::cout << message;
  }
  
  logic::initialize(userDataFileName, messageDataFileName);
}