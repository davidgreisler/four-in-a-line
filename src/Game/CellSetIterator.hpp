#ifndef CELLSETITERATOR_HPP
#define CELLSETITERATOR_HPP

namespace Game
{

class CellSet;

/**
 * Iterator for cell sets.
 *
 * Provides an iterator for cell sets. The iterator can be advanced to the next cell with next() or
 * the ++ operator, previous() or the -- operator can be used to make the previous cell the current.
 *
 * The current index can be retrieved with getIndex(), the content of the current cell is returned
 * by getContent(), or the * operator.
 *
 * It is possible to retrieve the x/y coordinates of the current cell with getXPosition() and
 * getYPosition().
 *
 * This class is reentrant but not thread-safe.
 */
class CellSetIterator
{
	public:
		CellSetIterator();
		CellSetIterator(const CellSet* cellSet, unsigned int index = 0);
		CellSetIterator(const CellSetIterator& orig);
		virtual ~CellSetIterator();

		unsigned int getIndex() const;
		unsigned int getContent() const;
		unsigned int operator*() const;

		unsigned int getXPosition() const;
		unsigned int getYPosition() const;

		void next();
		void previous();

		CellSetIterator& operator++();
		CellSetIterator operator++(int);
		CellSetIterator& operator--();
		CellSetIterator operator--(int);

		bool operator==(const CellSetIterator& it) const;
		bool operator!=(const CellSetIterator& it) const;
		bool operator<(const CellSetIterator& it) const;
		bool operator<=(const CellSetIterator& it) const;
		bool operator>(const CellSetIterator& it) const;
		bool operator>=(const CellSetIterator& it) const;

	private:
		/**
		 * Reference to the cell set used by the iterator.
		 */
		const CellSet* cellSet;

		/**
		 * Current position of the iterator.
		 */
		unsigned int index;

};

}

#endif // CELLSETITERATOR_HPP
