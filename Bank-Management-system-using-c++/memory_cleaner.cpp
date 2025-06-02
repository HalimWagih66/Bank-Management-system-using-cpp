#include "memory_cleaner.h"
#include "bank_system.h"
#include "manage_users.h"
void MemoryCleaner::CleanUpSingleton()
{
	BankSystem::getInstance().destroyInstance();
	ManageUsers::getInstance().destroyInstance();
}
