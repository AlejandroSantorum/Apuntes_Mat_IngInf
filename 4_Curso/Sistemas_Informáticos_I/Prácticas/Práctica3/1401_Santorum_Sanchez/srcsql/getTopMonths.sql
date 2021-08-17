-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: October 7, 2019
--  File: getTopMonths.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-- ARG 1 : threshold for product amount
-- ARG 2 : threshold for totalamount
CREATE OR REPLACE FUNCTION getTopMonths(integer, integer)
    RETURNS TABLE (
        month integer,
        year integer,
        total_prod bigint,
        total_cash numeric
    )
    AS $$
    BEGIN
        RETURN QUERY SELECT
            CAST(m AS integer),
            CAST(yr AS integer),
            t_prod,
            t_cash
        FROM (
                SELECT DATE_PART('month', orderdate) as m,
                       DATE_PART('year', orderdate) as yr,
                       sum(quantity) as t_prod
                FROM orders INNER JOIN orderdetail
                    ON orders.orderid=orderdetail.orderid
                GROUP BY m, yr
            ) TotalProd
        NATURAL JOIN
            (
                SELECT DATE_PART('month', orderdate) as m,
                       DATE_PART('year', orderdate) as yr,
                       sum(totalamount) as t_cash
                FROM orders
                GROUP BY m, yr
            ) TotalCash
        WHERE (t_prod > $1)
             OR (t_cash > $2);
    END;
$$ LANGUAGE plpgsql;

-------------------------------------------------
