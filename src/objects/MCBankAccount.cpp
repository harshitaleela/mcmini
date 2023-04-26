#include "mcmini/objects/MCBankAccount.h"

std::shared_ptr<MCVisibleObject>
MCBankAccount::copy()
{
  return std::shared_ptr<MCVisibleObject>(new MCBankAccount(*this));
}

MCSystemID
MCBankAccount::getSystemId()
{
  return shadow.identity;
}

bool
MCBankAccount::operator==(const MCBankAccount &other) const
{
  return shadow.identity == other.shadow.identity;
}

bool
MCBankAccount::operator!=(const MCBankAccount &other) const
{
  return !(*this == other);
}