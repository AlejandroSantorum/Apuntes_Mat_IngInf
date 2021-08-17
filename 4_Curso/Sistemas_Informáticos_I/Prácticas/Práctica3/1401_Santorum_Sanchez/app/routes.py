#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from app import database as db
from flask import render_template, request, url_for, redirect, session, flash
import json
import os
import sys
import random
import pickle
import hashlib
from collections import OrderedDict
from datetime import date

USERS_FOLDER = 'usuarios'
DATA_FILE = 'datos.dat'
HIST_FILE = 'historial.json'
CATALOGUE_FILE = 'catalogue/catalogo.json'
PHOTO_FILE = 'avatar.jpg'
STATIC_IMG = 'static/img'


@app.route('/', methods=['GET', 'POST'])
@app.route('/index.html', methods=['GET', 'POST'])
def index():
    films = None
    genres = db.db_getGenres()
    if request.method == 'POST':
        # Get the search result
        title = request.form.get('title')
        category = request.form.get('category')

        if (not title) and category == 'Ninguno':
            return redirect(url_for('index'))

        if category == 'Ninguno':
            films = db.db_search(title)
        elif not title:
            films = db.db_search(None, category)
        else:
            films = db.db_search(title, category)

        if not title:
            title = 'Peliculas en la catergoría: '+category
        return render_template('index.html', title='Búsqueda', films=films, search_query=title, genres=genres)

    else:
        # Get the last films
        if not session.get('topventas'):
            films = db.db_search()
            session['topventas'] = films
        else:
            films = session['topventas']

        return render_template('index.html', title='Home', films=films, search_query=None, genres=genres)


@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        # Getting data from form
        nick = request.form.get('nickname')
        passwd = request.form.get('password')
        mail = request.form.get('mail')
        name = request.form.get('name')
        surname = request.form.get('surname')
        addr = request.form.get('address')
        city = request.form.get('city')
        region = request.form.get('region')
        country = request.form.get('country')
        ccard_type = request.form.get('card_type')
        ccard = request.form.get('ccard')
        expiry = request.form.get('expiry_date')
        # Validate fields TODO: CHECK ALL OF THEM
        if not (nick and passwd and mail and ccard and addr):
            flash('Por favor, rellene todos los campos obligatorios')
            return render_template('register.html')
        # Acommodate data
        expiry = '20'+expiry[-2:]+expiry[:2]

        if not db.db_registerUser(nick, passwd, mail, name, surname, addr,\
                                  city, region, country, ccard_type, ccard,\
                                  expiry):
            flash('Ya existe un usuario registrado con este e-mail')
            return render_template('register.html')

        return redirect(url_for('index'))
    else:
        return render_template('register.html')


@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        # Getting data from form
        email = request.form.get('email')
        passwd = request.form.get('password')
        # Checking user data
        # Validate fields
        if not (email and passwd):
            flash('Por favor, rellene todos los campos')
            return render_template('login.html')

        # Gets the user data from the db
        userdata = db.db_userData(email)
        # Checks if user is registered
        if not userdata:
            flash('Usuario no registrado')
            return render_template('login.html')

        # Checks if the password matches
        if passwd != userdata['password']:
            flash('Contraseña incorrecta')
            return render_template('login.html')



        userdata['orderid'] = db.db_initCart(userdata['customerid'])

        userdata['cart'] = db.db_getCart(userdata['orderid'])

        # Sessions
        session['nickname'] = userdata['nickname']
        session['mail'] = userdata['mail']
        session['ccard'] = userdata['ccard']
        session['cash'] = userdata['cash']
        session['address'] = userdata['address']
        session['customerid'] = userdata['customerid']
        session['orderid'] = userdata['orderid']
        # session['photo'] = os.path.isfile(os.path.join(app.root_path, STATIC_IMG, slug_nick, PHOTO_FILE))
        session['photo'] = False

        if session.get('cart'):
            ### DEBUG PLS
            userdata['cart'].update(session['cart'])
            session['cart'].update(userdata['cart'])
            _update_cart()

        else:
            session['cart'] = userdata['cart']
        return redirect(url_for('index'))
    else:
        last_email = request.cookies.get('last_email')
        return render_template('login.html', last_email=last_email)

def _update_cart():
    db.db_saveCart(session['cart'], session['orderid'])

def _update_userdata(*argv):
    slug_nick = session['nickname'].lower()
    # Reading userdata
    with open(os.path.join(app.root_path, USERS_FOLDER, slug_nick, DATA_FILE), 'rb') as file:
        userdata = pickle.load(file)
    # Updating
    for arg in argv:
        userdata[arg] = session[arg]
        userdata[arg] = session[arg]
    # Storing updates
    with open(os.path.join(app.root_path, USERS_FOLDER, slug_nick, DATA_FILE), 'wb') as file:
        pickle.dump(userdata, file)


@app.route('/logout', methods=['POST'])
def logout():
    # Storing current cart data into user data file
    # _update_userdata('cash', 'cart', 'address')
    resp = redirect(url_for('index'))
    resp.set_cookie('last_email', session['mail'])
    # Deleting user data at current session
    session.pop('nickname', None)
    session.pop('customerid', None)
    session.pop('orderid', None)
    session.pop('mail', None)
    # Deleting cart data in case another user logs in
    session.pop('cart', None)
    session.pop('topventas', None)
    return resp


@app.route('/product/<id>', methods=['GET', 'POST'])
def product(id):
    if (id == 'connectedusers'): # TODO: Check this
        return connectedusers()
    film = db.db_getProductDetails(id)
    if request.method == 'POST':
        if int(request.form.get('amount')) < 0:
            return render_template('product.html', title=film['titulo'], film=film)

        if not session.get('cart'):
            session['cart'] = {int(id): (int(request.form.get('amount')), float(film['precio']))}

        elif session.get('cart').get(int(id)) is not None: # If item is already added
            session['cart'][int(id)] = (int(request.form.get('amount')), session['cart'][int(id)][1])

            if( int(request.form.get('amount')) == 0):
                session['cart'].pop(int(id), None)

        else:
            session['cart'][int(id)] = (int(request.form.get('amount')), float(film['precio']))

        if session.get('mail'):
            if int(request.form.get('amount')) == 0:
                db.db_deleteItemCart(id, session['orderid'])
            else:
                _update_cart()

    return render_template('product.html', title=film['titulo'], film=film)


@app.route('/cart', methods=['GET', 'POST'])
def cart():
    total = -1
    films = []
    if not session.get('cart'):
        session['cart'] = {}
    else:
        if request.method == 'POST': # Delete item from cart
            prod_id = request.form.get('prod_id')
            session['cart'].pop(int(prod_id), None)
            if session.get('mail'):
                db.db_deleteItemCart(prod_id, session['orderid'])

        if session['cart']:
            title_dict = db.db_getProdsTitles(session['cart'].keys())

            films = [{'id':prod_id, 'titulo':title_dict[prod_id],'amount': session['cart'][prod_id][0], 'precio': session['cart'][prod_id][1], 'animal': 1+prod_id%40, 'theme': prod_id%16}  for prod_id in session['cart'].keys()]

        if session.get('mail'):
            total = db.db_getTotalOrder(session['orderid'])

    return render_template('cart.html', films=films, total=total)


@app.route('/purchase', methods=['POST'])
def purchase():
    if not session.get('mail'):
        return redirect(url_for('login'))

    if not session.get('cart'):
        return redirect(url_for('index'))

    total = 0

    if not db.db_checkStock(session['cart']):
        # There's not enough stock
        flash('No se dispone de suficiente stock suficiente de algún producto.')
        return redirect(url_for('cart'));

    total = db.db_getTotalOrder(session['orderid'])
    # If there's not enough cash, cancel
    if session['cash'] < total:
        flash('No dispone de saldo para esta compra.')
        return redirect(url_for('cart'))

    # Place the order and empty the cart
    db.db_placeOrder(session['orderid'])
    session['orderid'] = db.db_initCart(session['customerid'])
    session['cart'] = db.db_getCart(session['orderid'])

    # Updates user cash
    session['cash'] -= total
    session['cash'] = round(session['cash'], 2)
    db.db_updateCash(session['customerid'], session['cash'])
    return redirect(url_for('index'))



@app.route('/history', methods=['GET'])
def history():
    if not session.get('mail'):
        return redirect(url_for('login'))

    history = db.db_getHistory(session['customerid'])

    dates = [f['date'] for f in history]
    dates.sort(reverse=True)
    grouped_history = OrderedDict()
    for date in dates:
        grouped_history[date] = []
    for f in history:
        grouped_history[f['date']].append(f)

    return render_template('history.html', history=grouped_history)


@app.route('/profile', methods=['GET', 'POST'])
def profile():
    if not session.get('nickname'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        if request.form.get('address'):
            session['address'] = request.form.get('address')
            db.db_updateAddress(session['customerid'], session['address'])

        elif request.form.get('cash'):
            try:
                session['cash'] += float(request.form.get('cash'))
                session['cash'] = round(session['cash'], 2)
                db.db_updateCash(session['customerid'], session['cash'])
            except ValueError:
                flash('Por favor, introduzca un valor válido para el saldo')

    return render_template('profile.html')


@app.route('/connectedusers', methods=['GET'])
def connectedusers():
    return str(random.randint(10, 1000))
