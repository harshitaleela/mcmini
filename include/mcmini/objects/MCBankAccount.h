#ifndef INCLUDE_MCMINI_OBJECTS_MCBANKACCOUNT_HPP
#define INCLUDE_MCMINI_OBJECTS_MCBANKACCOUNT_HPP

#include "mcmini/objects/MCVisibleObject.h"

struct MCBankAccountShadow {
  void *identity;
  int value;
  MCBankAccountShadow(void *identity, unsigned int value)
    : identity(identity), value(value)
  {}
};

struct MCBankAccount : public MCVisibleObject {
private:

  MCBankAccountShadow shadow;
  inline explicit MCBankAccount(MCBankAccountShadow shadow,
                                objid_t id)
    : MCVisibleObject(id), shadow(shadow)
  {}

public:

  ~MCBankAccount()                     = default;
  MCBankAccount(const MCBankAccount &) = default;

  explicit MCBankAccount(MCBankAccountShadow shadow)
    : MCVisibleObject(), shadow(shadow)
  {}

  std::shared_ptr<MCVisibleObject> copy() override;
  MCSystemID getSystemId() override;

  bool operator==(const MCBankAccount &other) const;
  bool operator!=(const MCBankAccount &other) const;

  void
  increment(int amount)
  {
    this->shadow.value += amount;
  }
  void
  decrement(int amount)
  {
    this->shadow.value -= amount;
  }
};

#endif // INCLUDE_MCMINI_OBJECTS_MCBANKACCOUNT_HPP
