#include "memory_cleaner.h"
#include "bank_system.h"
#include "manage_users.h"
// Cleans up singleton instances to free memory and prevent leaks
void MemoryCleaner::CleanUpSingleton()
{
    // Destroy the singleton instance of BankSystem
    BankSystem::getInstance().destroyInstance();

    // Destroy the singleton instance of ManageUsers
    ManageUsers::getInstance().destroyInstance();
}