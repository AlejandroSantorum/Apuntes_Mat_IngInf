-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 29, 2019
--  File: clientesDistintosFunc.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-------------------------------------------------------------------------
-- clientesDistintos
-- Input:
--      month integer: month number
--      year integer: year number
--      total_thh: totalamount threshold
-- Output:
--      n_clients: total number of distinct clients that have orders
--                 in a given month.
-------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION clientesDistintos(month integer, year integer, total_thh numeric)
    RETURNS TABLE (
        n_clients bigint
    )
    AS $$
    BEGIN
        RETURN QUERY
        SELECT COUNT(DISTINCT(customerid))
        FROM orders
        WHERE DATE_PART('month', orderdate)=month
              AND DATE_PART('year', orderdate)=year
              AND totalamount>total_thh;
    END;
$$ LANGUAGE plpgsql;
