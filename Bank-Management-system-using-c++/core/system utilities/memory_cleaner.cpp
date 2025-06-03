#include "memory_cleaner.h"
#include "../../features/bank system/bank_system.h"
#include "../../features/manage users/manage_users.h"


// Cleans up singleton instances to free memory and prevent leaks
void MemoryCleaner::CleanUpSingleton()
{
    // Destroy the singleton instance of BankSystem
    BankSystem::getInstance().destroyInstance();

    // Destroy the singleton instance of ManageUsers
    ManageUsers::getInstance().destroyInstance();
}