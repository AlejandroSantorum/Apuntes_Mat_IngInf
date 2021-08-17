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
    IF TG_OP='INSERT' OR TG_OP='UPDATE' THEN
        UPDATE orders
        SET netamount=netamount+(NEW.price*NEW.quantity),
            orderdate=now()::date
        WHERE orderid=NEW.orderid;
        RETURN NEW;
    ELSE
        nprods := (SELECT COUNT(*) FROM orderdetail WHERE orderdetail.orderid=OLD.orderid);
        IF nprods=0 THEN
            DELETE FROM orders
            WHERE orders.orderid=OLD.orderid;
        ELSE
            UPDATE orders
            SET netamount=netamount-(OLD.price*OLD.quantity)
            WHERE orderid=OLD.orderid;
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
