-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: October 7, 2019
--  File: getTopVentas.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION getTopVentas(integer)
    RETURNS TABLE (
        prod_id integer,
        annio integer,
        title varchar,
        maxSales integer)
    AS $$

    BEGIN
        RETURN QUERY SELECT
            Auxiliar.prod_id,
            cast(yr as integer),
            movietitle,
            cast(MaxAmountYear as integer)

            FROM
                imdb_movies,
                (
                    SELECT APYT.movieid, MaxAmountPerYearTable.MaxAmountYear, MaxAmountPerYearTable.yr, APYT.prod_id as prod_id
                    FROM (
                        SELECT movieid, DATE_PART('year', orderdate) as yr, sum(quantity) as amount_per_year, products.prod_id as prod_id
                        FROM orders, orderdetail, products
                        WHERE orders.orderid=orderdetail.orderid
                            AND orderdetail.prod_id=products.prod_id
                            AND DATE_PART('year', orderdate) >= $1
                            GROUP BY yr, products.prod_id
                    ) APYT
                    INNER JOIN
                        (SELECT yr, max(amount_per_year) as MaxAmountYear
                        FROM
                            (
                                SELECT movieid, DATE_PART('year', orderdate) as yr, sum(quantity) as amount_per_year
                                FROM orders, orderdetail, products
                                WHERE orders.orderid=orderdetail.orderid
                                    AND orderdetail.prod_id=products.prod_id
                                    AND DATE_PART('year', orderdate) >= $1
                                    GROUP BY yr, products.prod_id
                            ) APYT2
                        GROUP BY yr) MaxAmountPerYearTable
                    ON APYT.yr=MaxAmountPerYearTable.yr
                    AND APYT.amount_per_year=MaxAmountPerYearTable.MaxAmountYear
                ) AS Auxiliar

            WHERE
                imdb_movies.movieid=Auxiliar.movieid;

    END;
$$ LANGUAGE plpgsql;


---------------------------- STRUCTURED QUERY VERSION ----------------------------
-- TODO
-- CREATE VIEW AmountPerYearTable AS
-- SELECT movieid, DATE_PART('year', orderdate) as yr, sum(quantity) as amount_per_year
-- FROM orders, orderdetail, products
-- WHERE orders.orderid=orderdetail.orderid
--     AND orderdetail.prod_id=products.prod_id
--     AND DATE_PART('year', orderdate) >= $1
--     GROUP BY yr, products.prod_id;
--
-- CREATE VIEW Maximums AS
-- SELECT APYT.movieid, MaxAmountPerYearTable.MaxAmountYear, MaxAmountPerYearTable.yr
-- FROM AmountPerYearTable APYT INNER JOIN
--     (SELECT yr, max(amount_per_year) as MaxAmountYear
--     FROM AmountPerYearTable
--     GROUP BY yr) MaxAmountPerYearTable
-- ON APYT.yr=MaxAmountPerYearTable.yr
-- AND APYT.amount_per_year=MaxAmountPerYearTable.MaxAmountYear;
--
-- SELECT yr, movietitle, MaxAmountYear
-- FROM imdb_movies, Maximums
-- WHERE imdb_movies.movieid=Maximums.movieid;
--
-- DROP VIEW Maximums;
-- DROP VIEW AmountPerYearTable;
---------------------------- STRUCTURED QUERY VERSION ----------------------------
