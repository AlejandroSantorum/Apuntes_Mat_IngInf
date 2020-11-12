--creating de database
CREATE DATABASE libros;

--accessing the database created
\c libros

--Creating the temporary tables where we are copying the data
CREATE TABLE Temp_isbn_precios(
  ISBN varchar(20),
  precios varchar(15)
);

CREATE TABLE Temp_libros_final(
  author varchar(100),
  title varchar(300),
  format varchar(100),
  n_pages varchar(50),
  publishing_house varchar(100),
  publishing_date varchar(50),
  lang varchar(50),
  ISBN varchar(20)
);

CREATE TABLE Temp_usuarios(
  uid varchar(20),
  scrname varchar(50),
  full_name varchar(100),
  join_date varchar(100),
  credit_card varchar(50),
  expiration varchar(50)
);

CREATE TABLE Temp_ventas(
  sale_id varchar(20),
  user_id varchar(50),
  ISBN varchar(20),
  purchase_date varchar(50)
);
----------------------------------------------------------------

--Copying the data into temporary tables(It is important to have the file "datos_libreria" in your User file (ex. Users/Alejandro Santorum))
\copy Temp_isbn_precios from datos_libreria/isbns_precios.txt;

\copy Temp_libros_final from datos_libreria/LIBROS_FINAL.txt;

\copy Temp_usuarios from datos_libreria/usuarios.txt;

\copy Temp_ventas from datos_libreria/ventas.txt;
---------------------------------------------------------

--We create a auxiliary temporary table, just to help us to cast the price from varchar into float
CREATE TABLE Temp_books(
  ISBN varchar(20),
  Title varchar(200),
  Author varchar(200),
  Format varchar(64),
  N_pages varchar(100),
  Publishing_house varchar(100),
  Lang varchar(50),
  Price float
);

INSERT INTO Temp_books(
  SELECT Temp_libros_final.ISBN, Title, Author, Format, n_pages, Publishing_house, Lang, cast(replace(Temp_isbn_precios.Precios, ',','.') as Float)
  FROM Temp_libros_final, Temp_isbn_precios
  WHERE Temp_isbn_precios.ISBN = Temp_libros_final.ISBN AND left(Temp_isbn_precios.Precios, 1) <> ' '
  UNION
  SELECT Temp_libros_final.ISBN, Title, Author, Format, n_pages, Publishing_house, Lang, 10.0
  FROM Temp_libros_final, Temp_isbn_precios
  WHERE Temp_isbn_precios.ISBN = Temp_libros_final.ISBN AND left(Temp_isbn_precios.Precios, 1) = ' '
);
------------------------------------------------------------------

--Creating the final tables where the data will be stored
CREATE TABLE Books(
  ISBN varchar(20) PRIMARY KEY,
  Title varchar(200),
  Author varchar(200),
  Format varchar(64),
  N_pages varchar(100),
  Publishing_house varchar(100),
  Lang varchar(50),
  Price float
);

CREATE TABLE Users(
  User_id int PRIMARY KEY,
  Scrname varchar(50),
  Full_name varchar(200),
  Join_date date,
  Credit_card bigint,
  Expiration date
);

CREATE TABLE Sales(
  Sale_id int,
  User_id int,
  ISBN varchar(20),
  Purchase_date date,
  Super_sale_id serial PRIMARY KEY,
  FOREIGN KEY(ISBN) REFERENCES BOOKS(ISBN),
  FOREIGN KEY(User_id) REFERENCES USERS(user_id)
);

CREATE TABLE Discounts(
  Discount_id serial PRIMARY KEY,
  ISBN varchar(20),
  Initial_date date,
  Final_date date,
  Coef int,
  FOREIGN KEY(ISBN) REFERENCES BOOKS(ISBN)
);
------------------------------------------------------------------------

--This view filter the repeated ISBNS, Titles, Authors, etc
--because of the fact the data we recieve is poor, talking about quality
CREATE VIEW IntoBooks AS
  SELECT ISBN, min(Title) AS Title, min(Author) AS Author, min(Format) AS Format, min(n_pages) AS n_pages, min(Publishing_house) AS Publishing_house, min(Lang) AS Lang
  FROM temp_books
  GROUP BY ISBN;

--We insert all the data into the final tables
INSERT INTO Books(
  SELECT DISTINCT IntoBooks.ISBN, IntoBooks.Title, IntoBooks.Author, IntoBooks.Format, IntoBooks.n_pages, IntoBooks.Publishing_house, IntoBooks.Lang, Temp_books.price
  FROM IntoBooks, temp_books
  WHERE IntoBooks.ISBN = temp_books.ISBN
);

INSERT INTO Users --Introducing the Non Registered User into Users table
VALUES(0, 'NRU', 'Non_Registered_User', '1000-01-01', 0000000000000000, '1000-01-01');

INSERT INTO Users
  SELECT cast(uid AS int), min(scrname), min(full_name), min(cast(join_date AS date)), min(cast(credit_card AS bigint)), min(cast(expiration AS date))
  FROM temp_usuarios
  GROUP BY uid;

INSERT INTO Sales
  SELECT cast(Temp_ventas.sale_id AS int), cast(Temp_ventas.User_id AS INT), Books.ISBN, cast(Temp_ventas.Purchase_date AS date)
  FROM Temp_ventas, Books
  WHERE Books.ISBN = Temp_ventas.ISBN;

INSERT INTO Discounts (ISBN, Initial_date, Final_date, Coef)
VALUES('0753820870', '2010-01-15', '2014-10-10', 50), ('019871517X', '2012-01-01', '2014-12-30', 90);

DROP VIEW intobooks; --Once the database is already filled, we don´t need this auxiliary view.
-------------------------------------------------------------------------------

------------------------------------------------------------------------------
                          --Q U E R I E S--
--Now we are showing the queries required


--1.1 Given a title, how many editions does it have?(ex. Don Quixote)
SELECT COUNT(Books.ISBN) AS n_Editions
FROM Books WHERE Books.ISBN IN
(SELECT Books.ISBN
FROM Books
WHERE Title = 'Don Quixote');


--1.2 Given a title, in how many languages is the book written?(ex. Don Quixote)
SELECT COUNT(DISTINCT Lang) AS n_Languages
FROM Books
WHERE Books.ISBN IN
(SELECT Books.ISBN
FROM Books
WHERE Title = 'Don Quixote');


--2. How many books of author X were sold? (ex. Arturo Perez-Reverte)
SELECT COUNT(*) AS n_BooksSold
FROM Books, Sales
WHERE Books.author = 'Arturo Perez-Reverte' AND Books.ISBN = Sales.ISBN;


--3. How many books of author X were sold at a discount? (ex. Arturo Perez-Reverte)
SELECT COUNT(*) AS n_BooksAtDiscount
FROM Books, Sales, Discounts
WHERE Books.Author = 'Arturo Perez-Reverte' AND Books.ISBN = Sales.ISBN AND Sales.ISBN = Discounts.ISBN AND (Purchase_date BETWEEN Discounts.Initial_date AND Discounts.Final_date);


--4. How much money was earned by selling books of author X?(ex. Arturo Perez-Reverte)
CREATE VIEW Money_earned AS( --First, we get into a view the prices with a discount and the prices without it.
SELECT sum(Books.price) AS s1
FROM Books, Sales, Discounts
WHERE Sales.ISBN = Books.ISBN AND Sales.ISBN = Discounts.ISBN AND Books.author = 'Arturo Perez-Reverte' AND NOT(Purchase_date BETWEEN Discounts.Initial_date AND Discounts.Final_date)
UNION
SELECT sum(Books.price * Discounts.coef/100)
FROM Books, Sales, Discounts
WHERE Sales.ISBN = Books.ISBN AND Sales.ISBN = Discounts.ISBN AND Books.author = 'Arturo Perez-Reverte' AND(Purchase_date BETWEEN Discounts.Initial_date AND Discounts.Final_date));

SELECT sum(s1) AS Money_Earned_For_X_Author FROM Money_earned; --We sum the prices with discount and the other ones.

DROP VIEW Money_earned; --We delete the auxiliary view.


--5. How many books were sold to registered users?
SELECT COUNT(*) AS n_BooksSold_ToRegistered
FROM Sales, Users
WHERE Users.user_id = Sales.user_id AND Users.user_id <> 0;


--6. How many registered users have bought English books?
SELECT COUNT(DISTINCT Users.user_id) AS n_registeredUsers
FROM Sales, Users, Books
WHERE Users.user_id <> 0 AND Users.user_id = Sales.user_id AND Sales.ISBN = Books.ISBN AND (Books.Lang = 'English' OR Books.Lang = 'Inglés');


--7. How much money was earned by selling books in French?
CREATE VIEW Money_earned AS( --First, we get into a view the prices with a discount and the prices without it.
SELECT sum(Books.price) AS s1
FROM Books, Sales, Discounts
WHERE Sales.ISBN = Books.ISBN AND Books.lang = 'Francés' AND NOT(Purchase_date BETWEEN Discounts.Initial_date AND Discounts.Final_date)
UNION
SELECT sum(Books.price * Discounts.coef/100)
FROM Books, Sales, Discounts
WHERE Sales.ISBN = Books.ISBN AND Books.lang = 'Francés' AND(Purchase_date BETWEEN Discounts.Initial_date AND Discounts.Final_date));

SELECT sum(s1) AS Money_Earned_BooksFrench FROM Money_earned; --We sum the prices with discount and the other ones.

DROP VIEW Money_earned; --We delete the auxiliary view.


--8. In which days were books of the publisher Adelpi on sale?
SELECT Discounts.Initial_date, Discounts.Final_date --This example returns 0 because Adelpi doesn´t exist.
FROM Books, Discounts
WHERE Publishing_house = 'Adelpi';

SELECT Discounts.Initial_date, Discounts.Final_date --This gives us a non-null result.
FROM Books, Discounts
WHERE Publishing_house = 'Oxford University Press, U.S.A. ';


--9. Which registered users have never bought paperback books?
SELECT DISTINCT Users.full_name
FROM Users
WHERE User_id <> 0
EXCEPT
SELECT DISTINCT Users.full_name
FROM Users, Sales, Books
WHERE Users.user_id = Sales.user_id AND Sales.ISBN = Books.ISBN AND Users.user_id <> 0 AND Books.format LIKE '%Libro de bolsillo%';
