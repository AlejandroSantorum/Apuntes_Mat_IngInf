import os
import random
import sys, traceback
import datetime
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select
from sqlalchemy.exc import IntegrityError
from psycopg2.errors import UniqueViolation

# Configure sqlalchemy engine
# db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False)
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1?client_encoding=utf8", echo=False)
db_meta = MetaData(bind=db_engine)
# load tables
db_tb_movies = Table('imdb_movies', db_meta, autoload=True, autoload_with=db_engine)
db_tb_customers = Table('customers', db_meta, autoload=True, autoload_with=db_engine)
db_tb_orders = Table('orders', db_meta, autoload=True, autoload_with=db_engine)
db_tb_orderdetail = Table('orderdetail', db_meta, autoload=True, autoload_with=db_engine)
db_tb_products = Table('products', db_meta, autoload=True, autoload_with=db_engine)
db_tb_genres = Table('genres', db_meta, autoload=True, autoload_with=db_engine)


def db_userData(email):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        # Search for the user with the given email
        query = select([db_tb_customers]).where(text("email=\'"+email+"\'"))
        customer_rows = db_conn.execute(query)

        db_conn.close() # Close the connection
        if customer_rows.rowcount == 0:
            customer_rows.close()
            return None # Given customer is not registered

        # Email is primary key, so it is an unique result (if any)
        userdata = list(customer_rows)[0]
        ret_userdata = {
            'customerid': userdata[0],
            'nickname': userdata[15],
            'password': userdata[16],
            'mail': userdata[10],
            'ccard': userdata[13],
            'cash': userdata[-1],
            'address': userdata[3],
        }
        customer_rows.close()
        return ret_userdata
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_initCart(customerid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()
        query_str = 'SELECT orderid FROM orders WHERE customerid='+str(customerid)+' AND status IS NULL'
        ret = db_conn.execute(query_str)

        if ret.rowcount == 0:
            ret.close()
            query_str = 'INSERT INTO orders(customerid, orderdate) ' +\
                        'VALUES('+str(customerid)+', now()::date)'
            ret2 = db_conn.execute(query_str)
            ret2.close()
            query_str = 'SELECT orderid FROM orders WHERE customerid='+str(customerid)+' AND status IS NULL'
            ret_orderid = db_conn.execute(query_str)
            orderid = list(ret_orderid)[0][0]
            ret_orderid.close()
        else:
            orderid = list(ret)[0][0]
            ret.close()

        db_conn.close()
        return int(orderid)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None

def db_getCart(orderid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        # Search for the cart of the user of the given orderid
        query_str = 'SELECT prod_id, quantity, price FROM orderdetail '
        query_str += 'WHERE orderid='+str(orderid)
        cart_rows = db_conn.execute(query_str)

        if cart_rows.rowcount == 0:
            cart_rows.close()
            db_conn.close() # Close the connection
            return {} # Given customer has nothing in cart (returning empty cart)

        ret_list = list(cart_rows)
        ret_dict = {}
        for tuple in ret_list:
            # {prod_id: (amount, price)}
            ret_dict[tuple[0]] = (int(tuple[1]), float(tuple[2]))
        cart_rows.close()
        db_conn.close() # Close the connection
        return ret_dict

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_saveCart(sess_cart, orderid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = 'INSERT INTO orderdetail(orderid, prod_id, quantity, price ) VALUES'

        values_str = ','.join(["('"+ str(orderid) + "','" + str(id) + "','" + str(sess_cart[id][0]) + "','" + str(sess_cart[id][1]) +"')" for id in sess_cart.keys() ])

        query_str += (values_str + ' ON CONFLICT (orderid, prod_id) DO UPDATE SET quantity=excluded.quantity')
        ret = db_conn.execute(query_str)
        db_conn.close()
        ret.close()
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None



SEP = "\'"
COMA = ", "
def _build_query_values(*argv):
    l = len(argv)
    qry_val = ""
    for i in range(l):
        if i != l-1:
            qry_val += SEP+argv[i]+SEP+COMA
        else:
            qry_val += SEP+argv[i]+SEP
    return qry_val


def db_registerUser(username, password, email, firstname, lastname, address1,
                    city, region, country, ccard_type, ccard_num, ccard_exp):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query = db_tb_customers.insert().values(
                                        firstname=firstname,
                                        lastname=lastname,
                                        address1=address1,
                                        city=city,
                                        country=country,
                                        region=region,
                                        email=email,
                                        creditcardtype=ccard_type,
                                        creditcard=ccard_num,
                                        creditcardexpiration=ccard_exp,
                                        username=username,
                                        password=password,
                                        age=random.randint(16, 75),
                                        income=random.randint(9999, 99999)
                                        )
        ret = db_conn.execute(query)

        db_conn.close() # Close the connection
        return True
    except IntegrityError as e: # Checking if the email is already registered
        assert isinstance(e.orig, UniqueViolation)
        return False
    except: # Other exceptions
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)
        return False #TODO: Maybe return None to differenciate from False?


def db_getGenres():
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query = select([db_tb_genres.c.genre.distinct()])
        genres_ret = db_conn.execute(query)

        db_conn.close()

        genres_lst = []
        for item in genres_ret:
            genres_lst.append(item[0])
        genres_ret.close()
        return list(genres_lst)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


#TODO: Check what happens if the user searches with genre filter but no search string
def db_search(search_str=None, genre=None):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        if not search_str and not genre:
            year = datetime.date.today().year
            search_query = "SELECT prod_id, title FROM getTopVentas("+str(year-3)+")"
        elif not genre:
            search_query = text("SELECT prod_id, movietitle " +
                                "FROM imdb_movies NATURAL JOIN products " +
                                "WHERE movietitle LIKE ('%"+search_str+"%')")
        elif not search_str:
            search_query = text("SELECT prod_id, movietitle " +
                                "FROM genres NATURAL JOIN imdb_moviegenres " +
                                "NATURAL JOIN imdb_movies NATURAL JOIN products " +
                                "WHERE genre='"+genre+"'")
        else:
            search_query = text("SELECT prod_id, movietitle " +
                                "FROM genres NATURAL JOIN imdb_moviegenres "+
                                "NATURAL JOIN imdb_movies NATURAL JOIN products " +
                                "WHERE genre='"+genre+"' AND movietitle LIKE ('%"+search_str+"%')")

        ret = db_conn.execute(search_query)
        films = [{'id': f[0], 'titulo': f[1], 'animal':f[0]%40+1, 'theme':f[0]%16} for f in list(ret)]
        db_conn.close() # Close the connection
        return films

    except: # Other exceptions
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)
        return None

def db_getProductDetails(prod_id):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        search_query = text("SELECT movietitle, year, directorname, price, prod_id, description " +
                            "FROM products NATURAL JOIN imdb_movies NATURAL JOIN " +
                            "imdb_directormovies NATURAL JOIN imdb_directors WHERE " +
                            "prod_id = " + str(prod_id))
        ret = db_conn.execute(search_query)
        f = list(ret)[0]
        film = {'titulo': f[0], 'anio': f[1], 'director': f[2], 'precio': f[3], 'id': f[4],
                'description': f[5], 'animal': f[4]%40+1, 'theme': f[4]%16}
        db_conn.close() # Close the connection
        return film

    except: # Other exceptions
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)
        return None

def db_insertItemCart(orderid, prod_id, unit_price, quantity):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query = db_tb_orderdetail.insert().values(
                                        orderid=orderid,
                                        prod_id=prod_id,
                                        price=unit_price,
                                        quantity=quantity
                                        )
        ret = db_conn.execute(query)

        db_conn.close() # Close the connection
        ret.close()
        return True
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return False #TODO: Maybe return None to differenciate from False?


def db_deleteItemCart(prod_id, orderid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = 'DELETE FROM orderdetail WHERE prod_id='+str(prod_id)+' AND orderid='+str(orderid)
        ret = db_conn.execute(query_str)
        ret.close()
        db_conn.close()

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_getProdsTitles(prodid_lst):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = 'SELECT prod_id, movietitle FROM imdb_movies NATURAL JOIN products WHERE '
        where_str = ' OR '.join(["prod_id='"+ str(id) + "'" for id in prodid_lst])
        query_str += where_str

        ret = db_conn.execute(query_str)

        list_ret = list(ret)
        dict_ret = {i[0]:i[1] for i in list_ret}

        ret.close()
        db_conn.close()
        return dict_ret

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_getHistory(customerid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = "SELECT movietitle, address1, quantity, orderdetail.price, orderdate, products.prod_id " + \
                    "FROM imdb_movies, customers, products, orderdetail, orders " + \
                    "WHERE orders.customerid="+str(customerid)+" AND orders.status IS NOT NULL " + \
                    "AND orders.orderid=orderdetail.orderid AND orderdetail.prod_id=products.prod_id " +\
                    "AND products.movieid=imdb_movies.movieid AND customers.customerid="+str(customerid)

        hist_ret = db_conn.execute(query_str)

        hist_list = list(hist_ret)
        hist_ret.close()

        hist_dict = [{
            'titulo': str(item[0]),
            'address': item[1],
            'amount': int(item[2]),
            'price': float(item[3]),
            'date': item[4],
            'animal': 1+item[5]%40,
            'theme': item[5]%16
        } for item in hist_list]

        db_conn.close() # Close the connection
        return hist_dict
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None

def db_checkStock(sess_cart):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = 'SELECT prod_id, stock FROM products WHERE '
        where_str = ' OR '.join(["prod_id='"+ str(id) + "'" for id in sess_cart.keys()])
        query_str += where_str

        ret = db_conn.execute(query_str)

        list_ret = list(ret)
        dict_ret = {i[0]:i[1] for i in list_ret}
        for prod_id in sess_cart.keys():
            if sess_cart[prod_id][0] > dict_ret[prod_id]:
                ret.close()
                db_conn.close()
                return False
        ret.close()
        db_conn.close()
        return True

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_placeOrder(orderid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = "UPDATE orders SET status='Paid' WHERE "
        query_str += "orders.orderid="+str(orderid)

        ret = db_conn.execute(text(query_str))
        ret.close()
        db_conn.close()
        return True

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None

def db_updateCash(customerid, cash):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = "UPDATE customers SET cash='"+str(cash)+"' WHERE "
        where_str = "customerid="+str(customerid)
        query_str += where_str

        ret = db_conn.execute(text(query_str))
        ret.close()
        db_conn.close()
        return True

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_updateAddress(customerid, address):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = "UPDATE customers SET address1='"+str(address)+"' WHERE "
        where_str = "customerid="+str(customerid)
        query_str += where_str

        ret = db_conn.execute(text(query_str))
        ret.close()
        db_conn.close()
        return True

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


def db_getTotalOrder(orderid):
    try:
        # Connect to database
        db_conn = None
        db_conn = db_engine.connect()

        query_str = "SELECT totalamount FROM orders WHERE orderid="+str(orderid)

        ret = db_conn.execute(text(query_str))
        ret_lst = list(ret)
        ret.close()
        db_conn.close()

        if(len(ret_lst)):
            return float(ret_lst[0][0])

        return 0

    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return None


# if __name__ == "__main__":
#     # print(db_userData('mail@mail.es'))
#     # print(db_registerUser('hallow', '123456789', 'mail@mail.es', 'alex', 'santo', 'plaza marina', 'lalin', 'pont', 'espana', 'visa', '1234567891234567', '222203'))
#     # print(db_insertItemCart(181791, 9, 19, 2))
#
#     # title_part = "George"
#     # print(db_search(title_part))
#     # print("=======================")
#
#     # print(db_getGenres(), "|||", len(db_getGenres()))
#
#     hist_ret = db_getHistory(5)
#     print(hist_ret, "|||", len(hist_ret))
#     print("\n=====\n", hist_ret[0])
