-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 29, 2019
--  File: updPromo.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

-- Creating column promo in customers table
ALTER TABLE public.customers
ADD promo float DEFAULT 0;


-- Trigger function: It performs a discount on the cart products price of
--                   the user who has received a promotional discount
CREATE OR REPLACE FUNCTION updPromo_func()
RETURNS TRIGGER AS $$
    BEGIN

        -- 1st we update orders (to force deadlock)
        UPDATE orders
        SET netamount=aux_tb.value
        FROM (
            SELECT orderdetail.orderid, sum(orderdetail.quantity * (products.price * (1-(NEW.promo/100)))) as value
            FROM orders, orderdetail, products
            WHERE orders.orderid=orderdetail.orderid AND orderdetail.prod_id=products.prod_id
            GROUP BY orderdetail.orderid
        ) AS aux_tb
        WHERE orders.customerid=NEW.customerid
            AND orders.status IS NULL
            AND orders.orderid=aux_tb.orderid;

        ------------------------------------
        -- Uncomment this if you want to create a deadlock with borraCliente page
        -- PERFORM pg_sleep(30);
        ------------------------------------

        -- 3rd: Update orders totalamount
        UPDATE orders
        SET totalamount=netamount * (1+(tax/100))
        WHERE customerid=NEW.customerid
            AND orders.status IS NULL;

        -- 2nd we update orderdetail
        UPDATE orderdetail
        SET price=products.price * (1-(NEW.promo/100)) -- discount
        FROM products, orders, customers
        WHERE orders.customerid=NEW.customerid -- NEW.customerid is equal to customers.customerid
            AND orders.status IS NULL -- cart item
            AND orders.orderid=orderdetail.orderid
            AND orderdetail.prod_id=products.prod_id;

    RETURN NEW;
    END;
$$ LANGUAGE plpgsql;


-- Init trigger
CREATE TRIGGER updPromo_trigger
AFTER UPDATE
ON customers
FOR EACH ROW
WHEN (OLD.promo IS DISTINCT FROM NEW.promo)
EXECUTE PROCEDURE updPromo_func();
