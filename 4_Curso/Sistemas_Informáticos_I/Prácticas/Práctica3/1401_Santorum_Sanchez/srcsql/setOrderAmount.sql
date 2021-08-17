-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: October 8, 2019
--  File: setOrderAmount.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-- It may have to be changed (procedure, not a function) <<<<<======

CREATE OR REPLACE FUNCTION setOrderAmount()
    RETURNS void AS $$
    BEGIN
        -- Updating netamount values of orders table
        UPDATE orders
        SET netamount=S.sum_price
        FROM (
            SELECT orderid, sum(price) AS sum_price
            FROM orderdetail
            GROUP BY orderid
        ) S
        WHERE orders.orderid=S.orderid;

        -- Updating totalamount values of orders table (netamount + taxes)
        UPDATE orders
        SET totalamount=T.ta
        FROM (
            SELECT orderid, ROUND(
                                ((netamount*(tax/100)) + netamount)
                                , 2) AS ta
            FROM orders
        ) T
        WHERE orders.orderid=T.orderid;
    END;
$$ LANGUAGE plpgsql;
