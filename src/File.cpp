#include "../header/File.h"


void file::lockAccessOthers(const std::string& fileName)
{
  //Заблокировать права на доступ к файлам у всех кроме текущего пользователя
  std::filesystem::permissions(fileName,
                               std::filesystem::perms::group_read |
                               std::filesystem::perms::group_write |
                               std::filesystem::perms::group_exec |
                               std::filesystem::perms::others_read |
                               std::filesystem::perms::others_write |
                               std::filesystem::perms::others_exec,
                               std::filesystem::perm_options::remove);
}



bool file::isAccessGranted_User(std::filesystem::perms fileRights)
{
  //У пользователя есть права на чтение / запись
  if ( ((fileRights & std::filesystem::perms::owner_write) != std::filesystem::perms::none) &&
       ((fileRights & std::filesystem::perms::owner_read) != std::filesystem::perms::none)) {
    return true;
  }
  return false;
}