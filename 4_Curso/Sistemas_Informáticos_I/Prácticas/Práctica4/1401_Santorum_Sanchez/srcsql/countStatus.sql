-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 29, 2019
--  File: countStatus.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-- Query plan study without indexes
EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status IS NULL;

EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status='Shipped';

-- Creating index on column status in orders table
CREATE INDEX status_index ON orders (status);

-- Query plan study with indexes
EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status IS NULL;

EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status='Shipped';

-- Executing analyze on orders
ANALYZE orders;

-- Query plan study after executing analyze
EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status IS NULL;

EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status='Shipped';

-- Other two queries of apendix 2
EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status='Paid';

EXPLAIN
SELECT COUNT(*)
FROM orders
WHERE status='Processed';
