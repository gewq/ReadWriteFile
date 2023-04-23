#include "../header/Logic.h"

#include <iostream>
#include <fstream>
#include <string>

#include "../header/User.h"
#include "../header/Message.h"


namespace {
  std::string userDataFileName;
  std::string messageDataFileName;

  enum {
    EXIT,
    WRITE,
    READ
  };

  enum {
    USER = 1,
    MESSAGE
  };
}


static void handleExit(bool& isRun);
static void handleWrite();
static void handleRead();
static bool isCorrect(const std::string& stringToCheck);


void logic::initialize(const std::string& userFileName, const std::string& messageFileName)
{
  userDataFileName = userFileName;
  messageDataFileName = messageFileName;
}



void logic::process(bool& isRun)
{
  std::string input = "";
  std::cout << "0 - Exit | 1 - Write | 2 - Read: ";
  std::cin >> input;

  if (!isCorrect(input)) {
    std::cout << "Incorrect input\n";
    return;
  }
  int value = std::stoi(input);

  switch(value) {
    case EXIT:
      handleExit(isRun);
      break;
    case WRITE:
      handleWrite();
      break;
    case READ:
      handleRead();
      break;
    default:
      std::cout << "Incorrect input\n";
      break;
  }
}



static void handleExit(bool& isRun)
{
  isRun = false;
}



static void handleUser();
static void handleMessage();

static void handleWrite()
{
  std::string input = "";
  std::cout << "Choose type object to write: 1 - User | 2 - Message: ";
  std::cin >> input;

  if (!isCorrect(input)) {
    std::cout << "Incorrect input\n";
    return;
  }
  int typeObject = std::stoi(input);

  //Обработка выбора пользователя
  switch(typeObject) {
    case USER:
      handleUser();
      break;
    case MESSAGE:
      handleMessage();
      break;
    default:
      std::cout << "Incorrect input\n";
      break;
  }
}



static void handleRead()
{
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
}



static void handleUser()
{
  std::string name;
  std::string login;
  std::string password;

  std::cout << "Input Name: ";
  std::cin >> name;

  std::cout << "Input Login: ";
  std::cin >> login;

  std::cout << "Input Password: ";
  std::cin >> password;

  auto file = std::fstream (userDataFileName, std::ios::out | std::ios::app | std::ios::ate);
  if (!file.is_open()) {
    const std::string errorMessage = "File " + userDataFileName + " is not opened\n";
    throw errorMessage;
  }

  User user(name, login, password);
  file << user;

  file.close();
}



static void handleMessage()
{
  std::string sender;
  std::string receiver;
  std::string text;

  std::cout << "Input Sender: ";
  std::cin >> sender;

  std::cout << "Input Receiver: ";
  std::cin >> receiver;

  std::cout << "Input Text: ";
  std::cin >> text;

  auto file = std::fstream (messageDataFileName, std::ios::out | std::ios::app);
  if (!file.is_open()) {
    std::cout << "File: " << messageDataFileName << " is not opened\n";
    return;
  }

  Message message(sender, receiver, text);
  file << message;

  file.close();
}



static bool isCorrect(const std::string& stringToCheck)
{
  if (stringToCheck.size() > 1) {
    return false;
  }

  //Если содержит хотя бы один НЕразрешённый символ
  const std::string allowedChars = "0123456789";

  size_t pos = stringToCheck.find_first_not_of(allowedChars);
  //Найден хотя бы один НЕразрешённый символ
  if (pos != std::string::npos) {
    return false;
  }

  return true;
}