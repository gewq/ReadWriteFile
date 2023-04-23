#include "../header/User.h"

#include <assert.h>
#include <filesystem>
#include <fstream>


User::User() : name_(""), login_(""), password_("")
{
}



User::User(const std::string& name,
           const std::string& login,
           const std::string& password):
  name_(name), login_(login), password_(password)
{
}



std::string User::getName() const
{
  return name_;
}



std::string User::getLogin() const
{
  return login_;
}



std::string User::getPassword() const
{
  return password_;
}



std::fstream& operator >> (std::fstream& inputStream, User& user)
{
  inputStream >> user.name_;
  inputStream >> user.login_;
  inputStream >> user.password_;
  return inputStream;
}



std::ostream& operator << (std::ostream& outputStream, const User& user)
{
  outputStream << user.name_;
  outputStream << '\t';
  outputStream << user.login_;
  outputStream << '\t';
  outputStream << user.password_;
  outputStream << '\n';
  return outputStream;
}



//========================================================================================================
static void testConstructorDefault();
static void testConstructorParameterized();
static void testWriteFile();
static void testReadFile();


void user::test()
{
  testConstructorDefault();
  testConstructorParameterized();
  testWriteFile();
  testReadFile();
}



static void testConstructorDefault()
{
  User user;
  assert(user.getName() == "");
  assert(user.getLogin() == "");
  assert(user.getPassword() == "");
}



static void testConstructorParameterized()
{
  const std::string name = "name";
  const std::string login = "login";
  const std::string password = "password";

  User user(name, login, password);

  assert(user.getName() == name);
  assert(user.getLogin() == login);
  assert(user.getPassword() == password);
}



static void testWriteFile()
{
  //Создать тестовый файл
  const std::string fileName = "test_user.txt";
  std::fstream file = std::fstream (fileName, std::ios::in | std::ios::out | std::ios::trunc);

  if (!file.is_open()) {
    assert(true == false);
  }

  //Создать тестовый объект
  User user("name",  "login", "password");
  file << user;	//Записать объект в файл

  //Переместить указатель чтения в начало файла
  file.seekg(0, std::ios_base::beg);

  //Прочитать данные из файла
  std::string readName = "";
  std::string readLogin = "";
  std::string readPassword = "";
  file >> readName;
  file >> readLogin;
  file >> readPassword;

  //Прочитанные данные должны совпадать с записанными данными тестового пользователя
  assert(readName == user.getName());
  assert(readLogin == user.getLogin());
  assert(readPassword == user.getPassword());

  //Удалить тестовый файл
  file.close();
  std::filesystem::remove(fileName);
}



static void testReadFile()
{
  //Создать тестовый файл
  const std::string fileName = "test_user.txt";
  std::fstream file = std::fstream (fileName, std::ios::in | std::ios::out | std::ios::trunc);

  if (!file.is_open()) {
    assert(true == false);
  }

  //Создать тестовый объект
  User user("name",  "login", "password");
  file << user;	//Записать объект в файл

  //Переместить указатель чтения в начало файла
  file.seekg(0, std::ios_base::beg);

  User userRead;
  file >> userRead;

  //Прочитанные данные должны совпадать с записанными данными тестового пользователя
  assert(userRead.getName() == user.getName());
  assert(userRead.getLogin() == user.getLogin());
  assert(userRead.getPassword() == user.getPassword());

  //Удалить тестовый файл
  file.close();
  std::filesystem::remove(fileName);
}