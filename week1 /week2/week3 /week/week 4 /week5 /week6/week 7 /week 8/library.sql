SELECT title FROM books 
JOIN book_authors ON books.id = book_authors.book_id
JOIN authors ON book_authors.author_id = authors.id
WHERE authors.last_name = 'Orwell';  
SELECT first_name, last_name, fine 
FROM members 
JOIN loans ON members.id = loans.member_id 
WHERE fine > 0; SELECT genres.name, COUNT(books.id) 
FROM genres 
JOIN books ON genres.id = books.genre_id 
GROUP BY genres.name;
