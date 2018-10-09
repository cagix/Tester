#ifndef TESTER_UTILITY_H
#define TESTER_UTILITY_H

#include <memory>
#include <ostream>
#include <string>

namespace tester {

// Forward declare cell so there's no circular import.
class Cell;

// Easy point to Condition.
class Condition;
typedef std::unique_ptr<Condition> ConditionPtr;

// Base class for conditions.
class Condition {
public:
  // Construct with an operator.
  explicit Condition(std::string op) : op(std::move(op)) { }

  // Default virtual destructor.
  virtual ~Condition() = default;

  // Dump the condition.
  virtual void dump(std::ostream &os) = 0;

protected:
  // The operator.
  const std::string op;
};

// Comparing against a constant int.
template <typename T>
class LiteralCondition : public Condition {
public:
  // Construct with operator and value.
  LiteralCondition(std::string op, T value) : Condition(std::move(op)), value(value) { }

  void dump(std::ostream &os) override;

private:
  // The value to compare against.
  const T value;
};

// Comparing a constant against a cell's value.
class CellCondition : public Condition {
public:
  // Construct with operator and value.
  CellCondition(std::string op, const Cell &cell, int value)
      : Condition(std::move(op)), cell(cell), value(value) { }

  void dump(std::ostream &os) override;

private:
  // The cell to compare against.
  const Cell &cell;

  // The value to compare against.
  const int value;
};

std::string idxToColName(size_t idx);

std::string posToCellName(size_t col, size_t row);

} // End namespace tester

template <typename T>
void tester::LiteralCondition<T>::dump(std::ostream &os) {
  os << '"' << op << value << '"';
}

#endif //TESTER_UTILITY_H
