-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 8, 2019
--  File: updInventory.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------

CREATE OR REPLACE FUNCTION updInv_func()
RETURNS TRIGGER AS $$
DECLARE
    mod_quantity integer;
    rec RECORD;
BEGIN

    -- Updating final purchase orderdate
    UPDATE orders
    SET orderdate=NOW()::date
    WHERE orderid=OLD.orderid;

    -- Updating products (inventory) information
    FOR rec IN
        SELECT prod_id, quantity
        FROM orderdetail
        WHERE OLD.orderid=orderdetail.orderid
    LOOP
        UPDATE products
        SET stock=stock-rec.quantity,
            sales=sales+rec.quantity
        WHERE prod_id=rec.prod_id;

        mod_quantity := (SELECT stock FROM products WHERE products.prod_id=rec.prod_id);

        IF mod_quantity=0 THEN
            INSERT INTO alerts(prod_id) VALUES (rec.prod_id);
        END IF;
    END LOOP;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER updInventory
AFTER UPDATE
ON orders
FOR EACH ROW
WHEN (OLD.status IS DISTINCT FROM NEW.status)
EXECUTE PROCEDURE updInv_func();
