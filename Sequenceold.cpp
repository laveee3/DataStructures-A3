// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_Sp14
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity) : data(0), used(0), current_index(0), capacity(DEFAULT_CAPACITY) 
   {
      if (initial_capacity <= 0)
		{
			initial_capacity = 1;
		}
//		data = new value_type[initial_capacity];
		data = new value_type[DEFAULT_CAPACITY];
   }

   sequence::sequence(const sequence& source) : data(source.data), used(source.used), current_index(source.current_index), capacity(source.capacity)
   {
		data = new value_type[source.capacity];	
		copy(source.data, source.data + used, data);	
   }

   sequence::~sequence()
   {
      delete [] data;
   }


   void sequence::resize(size_type new_capacity)
   {
		if (new_capacity < capacity)
			new_capacity = capacity;

		if (new_capacity < used)
			new_capacity = used;

		if (new_capacity <= 0)
			new_capacity = 1;
		
		if (capacity == new_capacity)
			return;		

		value_type *larger_array = new value_type[new_capacity];
		copy(data, data + used, larger_array);
		delete [] data;
		data = larger_array;
		capacity = new_capacity;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::start()
   {
		current_index = 0;	
   }


   void sequence::advance()
   {
      assert (is_item());

		current_index++;
   }

   void sequence::insert(const value_type& entry)
   {
      if (used == capacity)   
		{ 
			resize((capacity * 1.25) + 1);
		}

		if (size() == 0)
		{
			data[0] = entry;	
			used ++;
			current_index = 0;
			return;
		}	
		
		if (!is_item())
		{				
			current_index = 0;
			data[current_index] = entry;
			used ++;
		}
		else
		{
			for (size_type i = (used); i > current_index; i--)
				data[i] = data[i - 1];
			data[current_index] = entry;	
			used ++;		
		}
		return;
   }

   void sequence::attach(const value_type& entry)
   {
		if (used == capacity)   
			resize((capacity * 1.25) + 1);

		if (size() == 0)
		{
			data[0] = entry;	
			used ++;
			current_index = 0;
			return;
		}	

		if (!is_item())
		{				
			current_index = used;
			data[current_index] = entry;
		}
		else
		{
			for (size_type i = used; i > (current_index + 1); i--)
				data[i] = data[i - 1];
			data[current_index + 1] = entry;	
		}
		used ++;
		current_index ++;
		return;
   }

   void sequence::remove_current()
   {
      assert (is_item() == true);

		if (current_index == used - 1)
			used--;
		else 
		{
			for (size_type i = current_index ; i < (used - 1); i++)
			{
				data[i] = data[i + 1];	
			}
			used--;
		}	
		return;	
   }

   sequence& sequence::operator=(const sequence& source)
   {
    	value_type *new_data;
	
		if (this == &source)
			return *this;
	
		if (capacity != source.capacity)
		{
			new_data = new value_type[source.capacity];
			delete [] data;
			data = new_data;
			capacity = source.capacity;
		}	
		used = source.used;
		copy(source.data, source.data + used, data);
		current_index = source.current_index;
				
		return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      return used;
   }

   bool sequence::is_item() const
   {
		if (current_index >= 0 && current_index < used)
      	return true;
		else
			return false;
   }

   sequence::value_type sequence::current() const
   {
		assert (is_item() == true);
      return data[current_index];
   }
}

