#pragma once

#include "../header/File.h"


namespace logic{
	/**
	Настроить модуль на работу с файлами данных
	\param[in] userFileName Имя файла с данными пользователей
	\param[in] messageFileName Имя файла с данными сообщений
	*/
	void initialize(const std::string& userFileName, const std::string& messageFileName);

	/**
	Логика работы программы
	\param[in] isRun Признак продолжения работы
	*/
	void process(bool& isRun);
}