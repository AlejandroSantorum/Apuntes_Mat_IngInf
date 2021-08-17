-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: October 7, 2019
--  File: setPrice.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------


--- AUXILIARY VIEW MOVED TO ACTUALIZA.SQL ---

-- Creating a auxiliary table (view) to set updated price
-- CREATE VIEW new_price_table AS
-- SELECT orderdetail.orderid,
--        orderdetail.prod_id,
--        -- Current_price / ((1.02)^(current_year - order_year)) -> casted to numeric to be rounded later
--        ROUND(
--             CAST(
--                 (products.price * POWER(1.02, -(DATE_PART('year', now()::date) - DATE_PART('year', orderdate))))
--             AS numeric),
--         2) AS new_price
-- FROM products, orders, orderdetail
-- WHERE products.prod_id=orderdetail.prod_id
--     AND orders.orderid=orderdetail.orderid;
--------------------------------------------------------------------

-- Inserting into orderdetail.price the recalculated price
UPDATE orderdetail
SET price=new_price_table.new_price
FROM new_price_table
WHERE orderdetail.orderid=new_price_table.orderid
    AND orderdetail.prod_id=new_price_table.prod_id;



-- Droping auixliary table (view)
--DROP VIEW new_price_table;
