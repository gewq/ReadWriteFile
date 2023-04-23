#include "../header/Message.h"

#include <assert.h>
#include <filesystem>
#include <fstream>


Message::Message(): sender_(""), receiver_(""), text_("")
{

}



Message::Message(const std::string& sender,
                 const std::string& receiver,
                 const std::string& text) :
  sender_(sender),
  receiver_(receiver),
  text_(text)
{
}



const std::string& Message::getSender() const
{
  return sender_;
}



const std::string& Message::getReceiver() const
{
  return receiver_;
}



const std::string& Message::getText() const
{
  return text_;
}



std::fstream& operator >> (std::fstream& inputStream, Message& message)
{
  inputStream >> message.sender_;
  inputStream >> message.receiver_;
  inputStream >> message.text_;
  return inputStream;
}



std::ostream& operator << (std::ostream& outputStream, const Message& message)
{
  outputStream << message.sender_;
  outputStream << '\t';
  outputStream << message.receiver_;
  outputStream << '\t';
  outputStream << message.text_;
  outputStream << '\n';
  return outputStream;
}



//========================================================================================================
static void testConstructorDefault();
static void testConstructorParameterized();
static void testWriteFile();
static void testReadFile();


void message::test()
{
  testConstructorDefault();
  testConstructorParameterized();
  testWriteFile();
  testReadFile();
}



static void testConstructorDefault()
{
  Message message;
  assert(message.getSender() == "");
  assert(message.getReceiver() == "");
  assert(message.getText() == "");
}



static void testConstructorParameterized()
{
  //Тест параметризованного конструктора и get-методов
  const std::string sender = "sender";
  const std::string receiver = "receiver";
  const std::string text = "text";

  Message message(sender, receiver, text);

  assert(message.getSender() == sender);
  assert(message.getReceiver() == receiver);
  assert(message.getText() == text);
}



static void testWriteFile()
{
  //Создать тестовый файл
  const std::string fileName = "test_message.txt";
  std::fstream file = std::fstream (fileName, std::ios::in | std::ios::out | std::ios::trunc);

  if (!file.is_open()) {
    assert(true == false);
  }

  //Создать тестовый объект
  Message message("sender", "receiver", "text");
  file << message;	//Записать объект в файл

  //Переместить указатель чтения в начало файла
  file.seekg(0, std::ios_base::beg);

  //Прочитать данные из файла
  std::string readSender = "";
  std::string readReceiver = "";
  std::string readText = "";
  file >> readSender;
  file >> readReceiver;
  file >> readText;

  //Прочитанные данные должны совпадать с записанными данными тестового пользователя
  assert(readSender == message.getSender());
  assert(readReceiver == message.getReceiver());
  assert(readText == message.getText());

  //Удалить тестовый файл
  file.close();
  std::filesystem::remove(fileName);
}



static void testReadFile()
{
  //Создать тестовый файл
  const std::string fileName = "test_message.txt";
  std::fstream file = std::fstream (fileName, std::ios::in | std::ios::out | std::ios::trunc);

  if (!file.is_open()) {
    assert(true == false);
  }

  //Создать тестовый объект
  Message message("sender", "receiver", "text");
  file << message;	//Записать объект в файл

  //Переместить указатель чтения в начало файла
  file.seekg(0, std::ios_base::beg);

  Message messageRead;
  file >> messageRead;

  //Прочитанные данные должны совпадать с записанными данными тестового пользователя
  assert(messageRead.getSender() == message.getSender());
  assert(messageRead.getReceiver() == message.getReceiver());
  assert(messageRead.getText() == message.getText());

  //Удалить тестовый файл
  file.close();
  std::filesystem::remove(fileName);
}