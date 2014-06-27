#include "CellSetIterator.hpp"
#include "CellSet.hpp"

#include <QDebug>

namespace Game
{

/**
 * Creates an empty and unusable iterator.
 */
CellSetIterator::CellSetIterator()
    : cellSet(0), index(0)
{

}

/**
 * Creates a new iterator for the given cell set, starting at the given index.
 *
 * @param cellSet Cell set.
 * @param index Position of the iterator. Default 0 (first item).
 */
CellSetIterator::CellSetIterator(const CellSet* cellSet, unsigned int index)
    : cellSet(cellSet), index(index)
{

}

/**
 * Copy constructor.
 *
 * @param orig Original object.
 */
CellSetIterator::CellSetIterator(const CellSetIterator& orig)
    : cellSet(orig.cellSet), index(orig.index)
{

}

/**
 * Frees all used resources.
 */
CellSetIterator::~CellSetIterator()
{

}

/**
 * Advances the iterator to the next cell and returns an iterator pointing to the next cell.
 *
 * @return Iterator pointing to the next cell.
 */
CellSetIterator& CellSetIterator::operator++()
{
	this->index++;

	return *this;
}

/**
 * Advances the iterator to the next cell and returns an iterator to the current cell.
 *
 * @return Iterator pointing to the current cell.
 */
CellSetIterator CellSetIterator::operator++(int)
{
	CellSetIterator current(*this);

	this->index++;

	return current;
}

/**
 * Makes the previous cell current and returns an iterator to the previous cell.
 *
 * @return Iterator pointing to the previous cell.
 */
CellSetIterator& CellSetIterator::operator--()
{
	this->index--;

	return *this;
}

/**
 * Makes the previous cell current and returns an iterator to the current cell.
 *
 * @return Iterator pointing to the current cell.
 */
CellSetIterator CellSetIterator::operator--(int)
{
	CellSetIterator current(*this);

	this->index--;

	return current;
}

/**
 * Returns the content of the current cell.
 *
 * @return Content of the current cell.
 */
unsigned int CellSetIterator::operator*() const
{
	return this->getContent();
}

/**
 * Returns whether this iterator is equal to the given iterator.
 *
 * @param it The iterator to compare to.
 * @return When they are equal true, otherwise false.
 */
bool CellSetIterator::operator==(const CellSetIterator& it) const
{
	return this->index == it.index && this->cellSet == it.cellSet;
}

/**
 * Returns whether this iterator is not equal to the given iterator.
 *
 * @param it The iterator to compare to.
 * @return When they are equal false, otherwise true.
 */
bool CellSetIterator::operator!=(const CellSetIterator& it) const
{
	return this->index != it.index || this->cellSet != it.cellSet;
}

/**
 * Returns whether this iterator is positioned before the given iterator.
 *
 * @param it Iterator to compare to.
 * @return When it is positioned before the given iterator true, otherwise false.
 */
bool CellSetIterator::operator<(const CellSetIterator& it) const
{
	return this->index < it.index;
}

/**
 * Returns whether this iterator is positioned before or at the same position as the given iterator.
 *
 * @param it Iterator to compare to.
 * @return When it is positioned before/at the same position the given iterator true, otherwise false.
 */
bool CellSetIterator::operator<=(const CellSetIterator& it) const
{
	return this->index <= it.index;
}

/**
 * Returns whether this iterator is positioned after the given iterator.
 *
 * @param it Iterator to compare to.
 * @return When it is positioned before/at the same position the given iterator true, otherwise false.
 */
bool CellSetIterator::operator>(const CellSetIterator& it) const
{
	return this->index > it.index;
}

/**
 * Returns whether the iterator is positioned after or at the same position as the given iterator.
 *
 * @param it Iterator to compare to.
 * @return When it is positioned after/at the same position the given iterator true, otherwise false.
 */
bool CellSetIterator::operator>=(const CellSetIterator& it) const
{
	return this->index >= it.index;
}

/**
 * Returns the index of the current cell.
 *
 * @return The index.
 */
unsigned int CellSetIterator::getIndex() const
{
	return this->index;
}

/**
 * Returns the content of the current cell.
 *
 * @return Content of the current cell.
 */
unsigned int CellSetIterator::getContent() const
{
	return this->cellSet->getContent(this->index);
}

/**
 * Returns the X position of the current cell.
 *
 * @return X position.
 */
unsigned int CellSetIterator::getXPosition() const
{
	return this->cellSet->getCellXPosition(this->index);
}

/**
 * Returns the Y position of the current cell.
 *
 * @return Y position.
 */
unsigned int CellSetIterator::getYPosition() const
{
	return this->cellSet->getCellYPosition(this->index);
}

/**
 * Advances the iterator to the next cell.
 */
void CellSetIterator::next()
{
	this->index++;
}

/**
 * Makes the previous cell current.
 */
void CellSetIterator::previous()
{
	this->index--;
}

}
