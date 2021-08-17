-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 29, 2019
--  File: clientesDistintos.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-- This query is impleneted in a procedure in another file
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;
-- 1406 ROWS with month=4, year=2015 and totalamount>100


-----------------------------------------------------------------------------
-- Only index on month
CREATE INDEX month_index ON ORDERS (DATE_PART('month', orderdate));

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX month_index;


-----------------------------------------------------------------------------
-- Only index on year
CREATE INDEX year_index ON ORDERS (DATE_PART('year', orderdate));

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX year_index;


-----------------------------------------------------------------------------
-- Only index on totalamount
CREATE INDEX totalamount_index ON ORDERS (totalamount);

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX totalamount_index;


-----------------------------------------------------------------------------
-- Only index on month followed by an index on year
CREATE INDEX month_index ON ORDERS (DATE_PART('month', orderdate));
CREATE INDEX year_index ON ORDERS (DATE_PART('year', orderdate));

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX month_index;
DROP INDEX year_index;


-----------------------------------------------------------------------------
-- Only index on year followed by an index on month
CREATE INDEX year_index ON ORDERS (DATE_PART('year', orderdate));
CREATE INDEX month_index ON ORDERS (DATE_PART('month', orderdate));

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX year_index;
DROP INDEX month_index;


-----------------------------------------------------------------------------
-- Index on pair (month, year)
CREATE INDEX monthyear_index ON ORDERS (DATE_PART('month', orderdate), DATE_PART('year', orderdate));

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

DROP INDEX monthyear_index;


-----------------------------------------------------------------------------
-- Index on tuple (month, year, totalamount)
CREATE INDEX monthyeartotal_index ON ORDERS (DATE_PART('month', orderdate), DATE_PART('year', orderdate), totalamount);

EXPLAIN
SELECT COUNT(DISTINCT(customerid))
FROM orders
WHERE DATE_PART('month', orderdate)=4
      AND DATE_PART('year', orderdate)=2015
      AND totalamount>100;

-- Uncomment this if you want to delete index
-- DROP INDEX monthyeartotal_index;
