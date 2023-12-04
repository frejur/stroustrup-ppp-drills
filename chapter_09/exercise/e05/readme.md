# Chapter 9, Exercise 5 to 9: A Library of classes

These exercises describe a set of classes and operators used to manage a virtual library.

### 5a. Create a class named 'Book':
- ISBN (String in the form of n-n-n-x, where n is an integer and x is a single letter or digit. Should be validated)

  The above "invariant" is a bit vague, so this version uses the following definition for a valid ISBN instead:
  - 4 groups of characters, separated by hyphens ("-").
  - A total number of exactly 10 characters.
  - The last group may only contain a single digit, or the letter 'X'.
  
    (Lowercase 'x' is allowed but converted to uppercase)
  - The first three groups may only contain digits.
  
  The official defintion of a valid ISBN is a lot more complex.
- Title (String. Should not be empty)
- Author (String. Should not be empty)
- Date (Let's use the type defined in the Chapter 9 drill)
- Check-out Status (Bool. Truthy is book is checked-out)

### 5b. Create member functions for 'Book':
- Getters
- Check out (Throw error if book is already checked-out)
- Check in (Throw error if book is already checked-in)

### 6.  Add operators to the Book class:
```
== ( and !=)    Truthy if both books have the same ISBN
<<              Print out Title, Author and ISBN
```

### 7a. Use a class Enum to create a Book attribute called "Genre":
- "Fiction", Non-Fiction", "Periodical", "Biography", "Children", "Misc"

  *(The original exercise doesn't include a "Misc" genre, this was added for variety and is the default value)*

### 7b. Update the 'Book' class:
- Initialize and validate Genre in constructor
- Add a getter function

### 8a. Create a 'Patron' class:
- Name (String. Should not be empty)
- Card Number (String. Only digits. Range: 100000 to 999999)
- Vector of \<Fee\>'s (Different from the original exercise. See 4c)

### 8b. Create member functions for 'Patron':
- Getters
- Has unpaid fees (Bool)
- Debt (Sum of fees)
- Add fee
- Mark fee as paid

### 8c. Create class 'Fee'

*(In the original exercise the fee of a Patron is just a sum of money that can be modified to match the Patron's current balance. This version keeps track of the fees using User-defined type 'Fee')*

- Date registered (\<Date\>)
- Date updated (\<Date\> Must be >= Date registered if not empty)
- Amount (Decimal number. Must be > 0)
- Comment (String. May be left empty)
- Is paid (Bool. Truthy if paid)

### 9a. Create a 'Library' class:
- Vector of \<Book\>'s
- Vector of \<Patron\>'s
- Vector of \<Transaction\>'s (See 9c)

### 9b. Create member functions for 'Library':
- Add Book
- Add Patron
- Blacklist (Return a list of names of all Patrons with unpaid fees)
- Check out Book

  *(Throw error if Book does not exist or is already checked-out. Also throw error if Patron does not exist. Lastly, check and throw an error if the Patron is on the blacklist. Then proceed to call Create transaction)*
- Check in Book

  *(Not in the original exercise. Similar to the above: Verify that the Book and Person exist, that the Book isn't already checked-in, and that the Patron is not blacklisted. Call Create transaction.)*
- Create transaction (Add transaction to vector. See 9c)

### 9c. Create a 'Transaction' struct:
- Book
- Patron
- Date
- \<Transaction_type\> (Not in the original exercise. See 9d)

### 9d. Create class Enum 'Transaction_type':
- Check-in
- Check-out

