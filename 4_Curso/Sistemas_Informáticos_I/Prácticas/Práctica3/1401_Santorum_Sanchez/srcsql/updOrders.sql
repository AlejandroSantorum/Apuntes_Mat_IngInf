-------------------------------------------------------------------------
-- Authors:
--          · Alejandro Santorum Varela
--          · Rafael Sanchez Sanchez
--  Date: November 14, 2019
--  File: updOrders.sql
--  Project: Computer Systems I Assignments
-------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION updOrders_func()
RETURNS TRIGGER AS $$
DECLARE
    nprods integer;
BEGIN
    IF TG_OP='UPDATE' THEN
        UPDATE orders
        SET netamount=netamount+(NEW.price*(NEW.quantity-OLD.quantity)),
            orderdate=now()::date,
            totalamount=round((netamount+(NEW.price*(NEW.quantity-OLD.quantity)))*(1+(tax/100)), 2)
        WHERE orderid=NEW.orderid;
        RETURN NEW;
    ELSIF TG_OP='INSERT' THEN
        UPDATE orders
        SET netamount=netamount+(NEW.price*NEW.quantity),
            orderdate=now()::date,
            totalamount=round((netamount+(NEW.price*NEW.quantity))*(1+(tax/100)), 2)
        WHERE orderid=NEW.orderid;
        RETURN NEW;
    ELSE
        nprods := (SELECT COUNT(*) FROM orderdetail WHERE orderdetail.orderid=OLD.orderid);
        IF nprods > 0 THEN
            UPDATE orders
            SET netamount=netamount-(OLD.price*OLD.quantity),
                totalamount=round((netamount-(OLD.price*OLD.quantity))*(1+(tax/100)), 2)
            WHERE orderid=OLD.orderid;
        ELSE
            UPDATE orders
            SET netamount=0.0,
                totalamount=0.0
            WHERE orderid=OLD.orderid;
        ----- WE DO NOT DELETE orderid EVEN IF THE CART IS EMPTY BECAUSE orderid IDENTIFIES THE CART
        -- ELSE
            -- DELETE FROM orders
            -- WHERE orders.orderid=OLD.orderid;
        ---------------------------------------------------------------------------------------
        END IF;
        RETURN NEW;
    END IF;
END;
$$ LANGUAGE plpgsql;


CREATE TRIGGER updOrders
AFTER INSERT OR DELETE OR UPDATE
ON orderdetail
FOR EACH ROW
EXECUTE PROCEDURE updOrders_func();
